#include "log_ext.h"
#include <sys/stat.h>
#include <errno.h>
#include "output.h"
#include "prefilter.h"
#include "pixel_boundings.h"
#include "constants.h"

#ifdef _WIN32
#define MKDIR _mkdir
#include <direct.h>
#include <Windows.h>
#else
int MKDIR(const char *dirname)
{
	return mkdir(dirname, S_IRWXU|S_IRGRP|S_IXGRP);
}
#endif

namespace imago
{
	FunctionRecord::FunctionRecord(const std::string& n)
	{
		name = n;
		anchor = n;
		#ifdef _WIN32
		time = GetTickCount();
		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof (statex);
		GlobalMemoryStatusEx (&statex);
		memory = static_cast<size_t>(statex.ullAvailVirtual / 1024);
		#endif
	}

	std::string FunctionRecord::getPlatformSpecificInfo()
	{
		std::string result = "";
		#ifdef _WIN32
		char buf[64];
		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof (statex);
		GlobalMemoryStatusEx (&statex);
		size_t mem_current = static_cast<size_t>(statex.ullAvailVirtual / 1024);
		int mem_used = static_cast<int>(memory - mem_current);
		int time_used = GetTickCount() - time;
		sprintf(buf, " (memory: %iKb, time: %ims)", mem_used, time_used);
		result = buf;
		#endif
		return result;
	}
	
	///////////////////////////////////////////////////////


	log_ext::log_ext(const std::string folder)
	{
		Folder = folder;
		ImgIdent = CallIdent = 0;
		UseVirtualFS = false;
		pVFS = NULL;
		FileOutput = NULL;
	}

	log_ext::~log_ext()
	{
		if (UseVirtualFS)
		{
			// do nothing
		}
		else if (FileOutput != NULL)
		{
			fclose(FileOutput);
		}
	}

	bool log_ext::loggingEnabled() const 
	{
		return vars::getDebugSession();
	}

	void log_ext::appendText(const std::string& text)
	{
		if(!loggingEnabled()) return;

		dump(getStringPrefix() + "<b>" + filterHtml(text) + "</b>");
	}

	void log_ext::appendImage(const std::string& caption, const Image& img)
	{
		if(!loggingEnabled()) return;
      
		std::string htmlName;
		std::string imageName = generateImageName(&htmlName);
		  
		dumpImage(imageName, img);
      
		std::string table = "<table style=\"display:inline;\"><tbody><tr>";		
		table += "<td>" + filterHtml(caption) + "</td>";
		table += "<td><img src=\"" + htmlName + "\" /></td>";
		table += "</tr></tbody></table>";
      
		dump(getStringPrefix() + table);
	}
   
	void log_ext::appendGraph(const std::string& name, const segments_graph::SegmentsGraph& g)
	{
		if(!loggingEnabled()) return;
      
		Image output(vars::getImageWidth(), vars::getImageHeight());
		output.fillWhite();
		ImageDrawUtils::putGraph(output, g);
		appendImage(name, output);
	}

	void log_ext::appendMat(const std::string& caption, const cv::Mat& mat)
	{
		if(!loggingEnabled()) return;
      
		Image output;
		ImageUtils::copyMatToImage(mat, output);
		appendImage(caption, output);
	}
   
	void log_ext::appendSkeleton(const std::string& name, const Skeleton::SkeletonGraph& g)
	{
		if(!loggingEnabled()) return;
      
		Image output(vars::getImageWidth(), vars::getImageHeight());
		output.fillWhite();
		ImageDrawUtils::putGraph(output, g);
		appendImage(name, output);
	}
   
	void log_ext::appendSegment(const std::string& name, const Segment& seg)
	{
		if(!loggingEnabled()) return;
      
		Segment shifted;
		shifted.copy(seg);
		shifted.getX() = 0;
		shifted.getY() = 0;
      
		Image output(shifted.getWidth(), shifted.getHeight());
		ImageUtils::putSegment(output, shifted, false);
		appendImage(name, output);
	}	  

	void log_ext::appendPoints(const std::string& name, const Points2i& pts)
	{
		if(!loggingEnabled()) return;

		RectShapedBounding b(pts);
		Image output(b.getBounding().width+1, b.getBounding().height+1);
		output.fillWhite();
		for (size_t u = 0; u < pts.size(); u++)
			output.getByte(pts[u].x - b.getBounding().x, pts[u].y - b.getBounding().y) = 0;
		appendImage(name, output);
	}

	void log_ext::appendSegmentWithYLine(const std::string& name, const Segment& seg, int line_y)
	{
		if(!loggingEnabled()) return;

		Image output(vars::getImageWidth(), vars::getImageHeight());
		output.fillWhite();
		ImageUtils::putSegment(output, seg, false);
		ImageDrawUtils::putLineSegment(output, Vec2i(0, line_y), Vec2i(output.getWidth(), line_y), 64);

		appendImage(name, output);
	}

	void log_ext::enterFunction(const std::string& name)
	{
		if(!loggingEnabled()) return;

		FunctionRecord fr = FunctionRecord(name);
		fr.name = filterHtml(fr.name);
		fr.anchor = filterHtml(generateAnchor(name));

		char color[32];
		sprintf(color, "%u, %u, %u", rand()%20 + 236, rand()%20 + 237, rand()%20 + 236);

		dump(getStringPrefix(true) + "<div title=\"" + fr.name + "\" style=\"background-color: RGB(" + color + ");\" >"
			+ "<b><font size=\"+1\">Enter into <a href=\"#" + fr.anchor + "\">" 
			+ fr.name + "</a> function</font></b><div style=\"margin-left: 20px;\">");
		Stack.push_back(fr);
	}

	void log_ext::leaveFunction()
	{
		if(!loggingEnabled()) return;

		FunctionRecord fr = Stack.back();
		Stack.pop_back();

		dump(getStringPrefix() + "</div><b><font size=\"+1\">Leave from <a name=\"" + fr.anchor + "\">" 
			+ fr.name + "</a> function</font></b>" + fr.getPlatformSpecificInfo() + " </div>");
	}

	std::string log_ext::generateAnchor(const std::string& name)
	{
		char buf[1024] = {0};
		sprintf(buf, "%s_%lu", name.c_str(), CallIdent);
		CallIdent++;
		return buf;
	}

	std::string log_ext::generateImageName(std::string* html_name )
	{
		char path[1024] = {0};

		const std::string ImagesFolder = "htmlimgs";

		sprintf(path, "%s/%s", Folder.c_str(), ImagesFolder.c_str());
		if (!UseVirtualFS && MKDIR(path) != 0)
		{
			if (errno == EEXIST)
			{
				// that's ok
			}
			else
			{
				// folder cannot be created, skip image generation?
			}
		}

		if (html_name != NULL)
		{
			sprintf(path, "./%s/%lu.png", ImagesFolder.c_str(), ImgIdent);
			(*html_name) = path;
		}

		sprintf(path, "%s/%s/%lu.png", Folder.c_str(), ImagesFolder.c_str(), ImgIdent);

		ImgIdent++;
		return path;
	}

	std::string log_ext::getStringPrefix(bool paragraph) const
	{
		return paragraph ? "<p>" : "<br>";
	}

	void log_ext::dumpImage(const std::string& filename, const Image& data)
	{
		if (UseVirtualFS)
		{
			if (pVFS)
			{
            //FIX(Smolov): Removed Png(Jpeg)Loader/Saver
            //TODO: Check if it's still correct
            std::vector<byte> bin_data;
            std::string buf;
            ImageUtils::saveImageToBuffer(data, ".png", bin_data);
            std::copy(bin_data.begin(), bin_data.end(), buf.begin());
            pVFS->createNewFile(filename, buf);
			}
		}
		else
		{
			ImageUtils::saveImageToFile(data, filename.c_str());
		}
	}

	void log_ext::dump(const std::string& data)
	{
		const std::string log_file = Folder + "/log.html";

		if (UseVirtualFS)
		{
			if (pVFS != NULL)
			{
				pVFS->appendData(log_file, data + "\n");
			}
		}
		else
		{
			if (FileOutput == NULL)
			{
				FileOutput = fopen(log_file.c_str(), "w");
			}
			if (FileOutput != NULL)
			{
				fprintf(FileOutput, "%s\n", data.c_str());
				fflush(FileOutput);
			}
		}
	}

	std::string log_ext::filterHtml(const std::string source) const
	{
		std::string result;
		for (size_t u = 0; u < source.size(); u++)
		{
			char c = source[u];
			if (c == '<')
			{
				result += "&lt;";
			}
			else if (c == '>')
			{
				result += "&gt;";
			}
			else
				result.push_back(c);
		}
		return result;
	}

	///////////////////////////////////////////////////////

	static log_ext logExtInstance("."); // current folder

	log_ext& getLogExt()
	{
		return logExtInstance;
	}
};