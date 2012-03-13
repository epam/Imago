#include "log_ext.h"
#include <direct.h>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace imago
{
	log_ext::FunctionRecord::FunctionRecord(std::string n)
	{
		name = n;
		anchor = n;
		#ifdef _WIN32
		time = GetTickCount();
		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof (statex);
		GlobalMemoryStatusEx (&statex);
		memory = statex.ullAvailVirtual / 1024;
		#endif
	}

	std::string log_ext::FunctionRecord::getPlatformSpecificInfo()
	{
		std::string result = "";
		#ifdef _WIN32
		char buf[64];
		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof (statex);
		GlobalMemoryStatusEx (&statex);
		int mem_used = memory - statex.ullAvailVirtual / 1024;
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
		output = NULL;
	}

	log_ext::~log_ext()
	{
		if (output != NULL)
		{
			fclose(output);
		}
	}

	void log_ext::appendSegmentWithYLine(const std::string& name, const Segment& seg, int line_y)
	{
		Image output(getSettings()["imgWidth"], getSettings()["imgHeight"]);
		output.fillWhite();
		ImageUtils::putSegment(output, seg, false);
		ImageDrawUtils::putLineSegment(output, Vec2i(0, line_y), Vec2i(output.getWidth(), line_y), 64);

		append(name, output);
	}

	bool log_ext::loggingEnabled() const 
	{
		return getSettings()["DebugSession"];
	}

	void log_ext::append(const std::string& text)
	{
		if(!loggingEnabled()) return;

		dump(getStringPrefix() + "<b>" + filterHtml(text) + "</b>");
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
		sprintf(buf, "%s_%d", name.c_str(), CallIdent);
		CallIdent++;
		return buf;
	}

	std::string log_ext::generateImageName(std::string* html_name )
	{
		char path[1024] = {0};

		const std::string ImagesFolder = "htmlimgs";

		sprintf(path, "%s/%s", Folder.c_str(), ImagesFolder.c_str());
		if (mkdir(path) != 0)
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
			sprintf(path, "./%s/%d.png", ImagesFolder.c_str(), ImgIdent);
			(*html_name) = path;
		}

		sprintf(path, "%s/%s/%d.png", Folder.c_str(), ImagesFolder.c_str(), ImgIdent);

		ImgIdent++;
		return path;
	}

	std::string log_ext::getStringPrefix(bool paragraph) const
	{
		return paragraph ? "<p>" : "<br>";
	}

	void log_ext::dump(const std::string& data)
	{
		if (output == NULL)
		{
			output = fopen((Folder + "/log.html").c_str(), "w");
		}
		if (output != NULL)
		{
			fprintf(output, "%s\n", data);
			fflush(output);
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