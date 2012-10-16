#include "similarity_tools.h"

#include "exception.h"
#include "platform_tools.h"

namespace similarity_tools
{

	std::string similarity_tool_exe = "";
	std::string similarity_tool_param = "";

	void setExternalSimilarityTool(const std::string& tool, const std::string& param)
	{
		similarity_tool_exe = tool;
		similarity_tool_param = param;
	}

	std::string quote(const std::string input)
	{
		std::string result = input;
		if (!result.empty() && result[0] != '\"')
			result = '\"' + result + '\"';
		return result;
	}

	double getSimilarity(const LearningContext& ctx)
	{
		if (!similarity_tool_exe.empty())
		{
			std::string params = quote(ctx.output_file) + " " + quote(ctx.reference_file);
			if (!similarity_tool_param.empty())
			{
				params = quote(similarity_tool_param) + " " + params;
			}
			int retVal = platform::CALL(similarity_tool_exe, params);
			if (retVal >= 0 && retVal <= 100)
				return retVal;
			else
				throw imago::FileNotFoundException("Failed to call similarity tool " 
						  + similarity_tool_exe + " (" + imago::ImagoException::str(retVal) + ")");
		}
		else
		{
			// internal similarity function
			return ((double)(rand() % RAND_MAX) / (double)RAND_MAX); // TODO: temp
		}

		return 0.0;
	}
}
