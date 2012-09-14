#include "prefilter_entry.h"
#include "log_ext.h"
#include "prefilter_basic.h"
#include "filters_list.h"

namespace imago
{
	bool prefilterEntrypoint(Settings& vars, Image& raw)
	{
		logEnterFunction();

		bool result = false;
		
		vars.general.ImageWidth = vars.general.OriginalImageWidth = raw.getWidth();
		vars.general.ImageHeight = vars.general.OriginalImageHeight = raw.getHeight();

		vars.general.ImageAlreadyBinarized = false;
		vars.general.FilterIndex = 0;

		prefilter_cv::resampleImage(raw);		

		return applyNextPrefilter(vars, raw, false);
	}

	bool applyNextPrefilter(Settings& vars, Image& raw, bool iterateNext)
	{
		logEnterFunction();
		bool result = false;

		if (iterateNext)
		{
			vars.general.FilterIndex++;
		}

		FilterEntries filters = getFiltersList();

		for (; vars.general.FilterIndex < (int)filters.size(); vars.general.FilterIndex++)
		{
			int& u = vars.general.FilterIndex;

			getLogExt().append("use filter", filters[u].name);

			if (filters[u].condition != NULL &&
				filters[u].condition(raw) == false)
			{
				getLogExt().append("filter condition failed", filters[u].name);
				continue;
			}

			if (filters[u].routine(vars, raw))
			{
				getLogExt().append("filter success", filters[u].name);
				if (!filters[u].update_config_string.empty())
				{
					vars.fillFromDataStream(filters[u].update_config_string);
				}
				result = true;
				break;
			}
			else
			{
				getLogExt().append("filter failed", filters[u].name);
			}
		}

		return result;
	}
}
