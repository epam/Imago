#include "settings.h"
#include <algorithm>

#define FUZZ ; // marker for constants allowed to adjust automatically

namespace imago
{
	#include "settings_filters.inc"
	#include "settings_label_remover.inc"
	
	#include "settings_scanned.inc"
	#include "settings_handwritten.inc"
	#include "settings_highres.inc"	
}

namespace imago
{
	imago::GeneralSettings::GeneralSettings()
	{
		LogEnabled = LogVFSEnabled = ExtractCharactersOnly = false;
		IsHandwritten = true;
		UseProbablistics = false;
		OriginalImageWidth = OriginalImageHeight = ImageWidth = ImageHeight = 0;
		DefaultFilterType = ftCV;
	}

	imago::Settings::Settings()
	{
		updateCluster(ctHandwritten);
	}

	void imago::Settings::updateCluster(ClusterType ct)
	{
		int longestSide = std::max(general.OriginalImageWidth, general.OriginalImageHeight);

		if (ct == ctDetermine)
		{
			if (general.IsHandwritten)
			{
				if (longestSide > prefilterCV.HighResPassBound * MaxImageDimensions)
					ct = ctHighResolution;
				else
					ct = ctHandwritten;
			}
			else
			{
				ct = ctScanned;
			}
		}

		switch (ct)
		{
			case ctHighResolution: updateSettingsHighResolution(*this);
				break;
			case ctScanned: updateSettingsScanned(*this);
				break;
			case ctHandwritten: updateSettingsHandwritten(*this);
				break;
		}
	}
}
