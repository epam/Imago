#include "filters_list.h"
#include "prefilter_basic.h"
#include "prefilter_retinex.h"

namespace imago
{
	FilterEntryDefinition::FilterEntryDefinition(const std::string& _name, int _priority, FilterFunction _f, const std::string& _config, ConditionFunction _c)
	{
		name = _name;
		priority = _priority;
		routine = _f;
		condition = _c;
		update_config_string = _config;
	}

	FilterEntries::FilterEntries()
	{
		push_back(FilterEntryDefinition("prefilter_binarized",   0,   prefilter_cv::prefilterBinarized, 
			                            "general.ImageAlreadyBinarized = 1;"));	

		push_back(FilterEntryDefinition("prefilter_retinex",     1,   prefilter_retinex::prefilterRetinex));

		push_back(FilterEntryDefinition("prefilter_basic",       2,   prefilter_cv::prefilterBasic));				
	}

	FilterEntries getFiltersList()
	{
		static FilterEntries result;
		return result;
	}
};
