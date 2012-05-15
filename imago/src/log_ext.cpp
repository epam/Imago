#include "log_ext.h"
#include "output.h"
#include "prefilter.h"
#include "pixel_boundings.h"
#include "platform_tools.h"

namespace imago
{
	FunctionRecord::FunctionRecord(const std::string& n)
	{
		name = n;
		anchor = n;
		time_start = platform::TICKS();
		time_log_ms = 0;
		memory = platform::MEM_AVAIL();
	}

	std::string FunctionRecord::getPlatformSpecificInfo()
	{
		std::string result = "";
		char buf[128];
		int mem_delta = static_cast<int>(memory - platform::MEM_AVAIL());
		int total_time = (platform::TICKS() - time_start);
		sprintf(buf, " (memory: %iKb, work time: %ims, log time: %ims, total time: %ims)", 
			    mem_delta, total_time - time_log_ms, time_log_ms, total_time);
		result = buf;
		return result;
	}
	
	///////////////////////////////////////////////////////

#define LOG_TIME_START   unsigned int log_time_start = platform::TICKS() 
#define LOG_TIME_END     for (size_t u = 0; u < Stack.size(); u++) Stack[u].time_log_ms += (platform::TICKS() - log_time_start)

	log_ext::log_ext(const std::string folder)
	{
		Folder = folder;
		ImgIdent = CallIdent = 0;
		enabled = UseVirtualFS = false;
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
		return enabled;
	}

	void log_ext::setLoggingEnabled(bool value)
	{
		enabled = value;
	}

	void log_ext::appendText(const std::string& text)
	{
		if(!loggingEnabled()) return;

		LOG_TIME_START;
		dump(getStringPrefix() + "<b>" + filterHtml(text) + "</b>");
		LOG_TIME_END;
	}

	void log_ext::appendImage(const std::string& caption, const Image& img)
	{
		if(!loggingEnabled()) return;

		LOG_TIME_START;
		appendImageInternal(caption, img);
		LOG_TIME_END;
	}

	void log_ext::appendImageInternal(const std::string& caption, const Image& img)
	{		
		std::string htmlName;
		std::string imageName = generateImageName(&htmlName);
		  
		dumpImage(imageName, img);
      
		std::string table = "<table style=\"display:inline;\"><tbody><tr>";		
		table += "<td>" + filterHtml(caption) + "</td>";
		table += "<td><img src=\"" + htmlName + "\" /></td>";
		table += "</tr></tbody></table>";
      
		dump(getStringPrefix() + table);
	}
   
	void log_ext::appendGraph(const Settings& vars, const std::string& name, const segments_graph::SegmentsGraph& g)
	{
		if(!loggingEnabled()) return;
      
		LOG_TIME_START;
		Image output(vars.general.ImageWidth, vars.general.ImageHeight);
		output.fillWhite();
		ImageDrawUtils::putGraph(output, g);
		appendImageInternal(name, output);
		LOG_TIME_END;
	}

	void log_ext::appendMat(const std::string& caption, const cv::Mat& mat)
	{
		if(!loggingEnabled()) return;
      
		LOG_TIME_START;
		Image output;
		ImageUtils::copyMatToImage(mat, output);
		appendImageInternal(caption, output);
		LOG_TIME_END;
	}
   
	void log_ext::appendSkeleton(const Settings& vars, const std::string& name, const Skeleton::SkeletonGraph& g)
	{
		if(!loggingEnabled()) return;
     
		LOG_TIME_START;
		Image output(vars.general.ImageWidth, vars.general.ImageHeight);
		output.fillWhite();
		ImageDrawUtils::putGraph(output, g);
		appendImageInternal(name, output);
		LOG_TIME_END;
	}
   
	void log_ext::appendSegment(const std::string& name, const Segment& seg)
	{
		if(!loggingEnabled()) return;
      
		LOG_TIME_START;
		Segment shifted;
		shifted.copy(seg);
		shifted.getX() = 0;
		shifted.getY() = 0;
      
		Image output(shifted.getWidth(), shifted.getHeight());
		ImageUtils::putSegment(output, shifted, false);
		appendImageInternal(name, output);
		LOG_TIME_END;
	}	  

	void log_ext::appendPoints(const std::string& name, const Points2i& pts)
	{
		if(!loggingEnabled()) return;

		LOG_TIME_START;
		RectShapedBounding b(pts);
		Image output(b.getBounding().width+1, b.getBounding().height+1);
		output.fillWhite();
		for (size_t u = 0; u < pts.size(); u++)
			output.getByte(pts[u].x - b.getBounding().x, pts[u].y - b.getBounding().y) = 0;
		appendImageInternal(name, output);
		LOG_TIME_END;
	}

	void log_ext::appendSegmentWithYLine(const Settings& vars, const std::string& name, const Segment& seg, int line_y)
	{
		if(!loggingEnabled()) return;

		LOG_TIME_START;
		Image output(vars.general.ImageWidth, vars.general.ImageHeight);
		output.fillWhite();
		ImageUtils::putSegment(output, seg, false);
		ImageDrawUtils::putLineSegment(output, Vec2i(0, line_y), Vec2i(output.getWidth(), line_y), 64);

		appendImageInternal(name, output);
		LOG_TIME_END;
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
		char buf[MAX_LINE] = {0};
		sprintf(buf, "%s_%lu", name.c_str(), CallIdent);
		CallIdent++;
		return buf;
	}

	std::string log_ext::generateImageName(std::string* html_name )
	{
		char path[MAX_LINE] = {0};

		const std::string ImagesFolder = "htmlimgs";

		sprintf(path, "%s/%s", Folder.c_str(), ImagesFolder.c_str());
		if (!UseVirtualFS && platform::MKDIR(path) != 0)
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