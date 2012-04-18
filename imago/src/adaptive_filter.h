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
		AdaptiveFilter(int width, int height) : Basic2dStorage<FilterPackedRecord>(width, height)
		{
			rgb = NULL;
		}

		virtual ~AdaptiveFilter()
		{
			if (rgb) delete rgb;
		}

		 // the really main method
		void filterImage(Image& img, bool allowCrop = true,
			             double probablyInkPercentage = 0.005,
						 int lineThickness = 6);

		
		// TODO: provide getters/setters
		friend class ImageAdapter; 
		friend class FilterImageStub;

	protected:		
		void interpolateImage(const AdaptiveFilter& src, int interpolation = 0);
		unsigned char getMaximalIntensityDiff(int x, int y);

		unsigned char getIntensityBound(double inkTresh, const Rectangle& crop, WeakSegmentator* ws = NULL);
		void normalizedOuput(Image& img, const Rectangle& crop, WeakSegmentator* ws = NULL);

	private:
		typedef Basic2dStorage<RGBData> RGBStorage;
		RGBStorage *rgb;
		int diffIterations, diffStepRange;
	};

	class FilterImageStub
	{
	public:
		FilterImageStub(Image* img_pointer, int source_width, int source_height);
		virtual ~FilterImageStub();
		
		static bool isAdaptiveFilterEnabled();
		static bool isColorLoadingRequired();
		
		void initPixel(int x, int y, unsigned char intensity);

		// inensity == 0 forcing automatical recalculation using R, G, B components
		void initPixel(int x, int y, unsigned char R, unsigned char G, unsigned char B, unsigned char intensity = 0);

	private:
		Image* imgptr;
		AdaptiveFilter* filterptr;
		int scale;
	};
}