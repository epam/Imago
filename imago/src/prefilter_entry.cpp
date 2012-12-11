#include "prefilter_entry.h"
#include <opencv2/opencv.hpp>
#include "log_ext.h"
#include "prefilter_basic.h"
#include "filters_list.h"

namespace imago
{
	namespace PrefilterUtils
	{
		bool downscale(cv::Mat& image, int max_dim = 1920)
		{
			if (std::max(image.cols, image.rows) > max_dim)
			{
				int src_width = image.cols;	
				cv::Size size;

				if (image.cols > image.rows)
				{
					size.width = max_dim;
					size.height = imago::round((double)image.rows * ((double)max_dim / image.cols));
				}
				else
				{
					size.height = max_dim;
					size.width = imago::round((double)image.cols * ((double)max_dim / image.rows));
				}

				cv::resize(image, image, size);		
				return true;
			}
			return false; // not required
		}

		bool resampleImage(Image &image)
		{
			logEnterFunction();
			
			int dim = std::max(image.getWidth(), image.getHeight());
			if (dim > MaxImageDimensions)
			{
				cv::Mat mat;
				ImageUtils::copyImageToMat(image, mat);
				if (downscale(mat, MaxImageDimensions))
				{
					image.clear();
					ImageUtils::copyMatToImage(mat, image);
					return true;
				}
			}
			return false;
		}
	}

	bool prefilterEntrypoint(Settings& vars, Image& raw)
	{
		logEnterFunction();

		bool result = false;
		
		vars.general.ImageWidth = vars.general.OriginalImageWidth = raw.getWidth();
		vars.general.ImageHeight = vars.general.OriginalImageHeight = raw.getHeight();

		vars.general.ImageAlreadyBinarized = false;
		vars.general.FilterIndex = 0;

		PrefilterUtils::resampleImage(raw);		

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
