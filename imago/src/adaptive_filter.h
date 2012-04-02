#pragma once

#include "image.h"
#include "color_channels.h"
#include "basic_2d_storage.h"
#include "pixel_boundings.h"

namespace imago
{
	class RGBStorage : public Basic2dStorage<RGBData>
	{
	public:
		RGBStorage(int w, int h);

		RGBStorage(const RGBStorage& src, int interpolation = 0);

		virtual ~RGBStorage();

		int getMaximalIntensityDiff(int channel, int x, int y, int iterations);

	private:
		Basic2dStorage<unsigned char> diff_cache;
	};

	

	 void RGB_based_init(Image &img, RGBStorage& rgb);
}