#pragma once

namespace imago
{
	struct RGBData
	{
		static const int CHANNELS_COUNT = 4;
		unsigned char L[CHANNELS_COUNT];		
		RGBData(unsigned char R = 0, unsigned char G = 0, unsigned char B = 0, unsigned char I = 0)
		{
			L[0] = R;
			L[1] = G;
			L[2] = B;
			L[3] = I;
		}
	};
}
