#include "filters_list.h"
#include "prefilter_basic.h"
#include "prefilter_handwritten.h"
#include "prefilter_adaptive.h"

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
		push_back(FilterEntryDefinition("prefilter_basic",       1,   prefilter_cv::prefilterBasic));
		push_back(FilterEntryDefinition("prefilter_handwritten", 2,   prefilterHandwritten));
		
		// TOO SLOW, better skip
		// push_back(FilterEntryDefinition("prefilter_adaptive",    3,   prefilterAdaptive));		
	}

	FilterEntries getFiltersList()
	{
		static FilterEntries result;
		return result;
	}
};
