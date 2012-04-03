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
}