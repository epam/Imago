#pragma once

#include "image.h"
#include "color_channels.h"
#include "basic_2d_storage.h"
#include "pixel_boundings.h"
#include "weak_segmentator.h"

namespace imago
{
	#pragma pack (push, 1)
	struct FilterPackedRecord
	{
		GrayscaleData intensity;
		unsigned char diffCache;
		FilterPackedRecord()
		{
			intensity = 0;
			diffCache = BLANK;
		}
	};
	#pragma pack (pop)

	class AdaptiveFilter : public Basic2dStorage<FilterPackedRecord>
	{
	public:
		static void process(Image& img);

		AdaptiveFilter(int width, int height) : Basic2dStorage<FilterPackedRecord>(width, height) { }

		virtual ~AdaptiveFilter() { }

		 // the really main method
		void filterImage(Image& img, bool allowCrop, double probablyInkPercentage, int lineThickness);

		
		// TODO: provide getters/setters
		friend class ImageAdapter; 
		friend class FilterImageStub;

	protected:		
		void interpolateImage(const AdaptiveFilter& src, int interpolation = 0);
		unsigned char getMaximalIntensityDiff(int x, int y);

		unsigned char getIntensityBound(double inkTresh, const Rectangle& crop, WeakSegmentator* ws = NULL);
		void normalizedOuput(Image& img, const Rectangle& crop, WeakSegmentator* ws = NULL);

	private:
		int diffIterations, diffStepRange;
	};
}