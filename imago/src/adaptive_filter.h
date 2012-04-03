#pragma once

#include "image.h"
#include "color_channels.h"
#include "basic_2d_storage.h"
#include "pixel_boundings.h"
#include "weak_segmentator.h"

namespace imago
{
	class AdaptiveFilter : public Basic2dStorage<RGBData>
	{
	public:
		AdaptiveFilter(int w, int h);
		virtual ~AdaptiveFilter();
		void filterImage(Image& img);	

		friend class ImageAdapter;

	protected:		
		AdaptiveFilter(const AdaptiveFilter& src, int interpolation = 0);
		int getMaximalIntensityDiff(int channel, int x, int y, int iterations);

		int getIntensityBound(const Rectangle& crop, WeakSegmentator* ws = NULL);
		void normalizedOuput(Image& img, const WeakSegmentator& ws, const Rectangle& crop);

	private:
		Basic2dStorage<unsigned char> diff_cache;
	};

	class FilterImageStub
	{
	public:
		FilterImageStub(Image* img, int source_width, int source_height);
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