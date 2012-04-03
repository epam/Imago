#pragma once

namespace imago
{
	/* code organization constants. Fixed values, not method params. 
	*/
	const int    INK = 0;                      // preferred intensity means filled
	const int    BLANK = 255;                  // intensity means blank	
	
	typedef unsigned char GSData; // TODO...

	const int    INTENSITY_CHANNEL = 0; // intensity channel
	const int    R_CHANNEL = 1;
	const int    G_CHANNEL = 2;
	const int    B_CHANNEL = 3;

	struct RGBData
	{
		static const int CHANNELS_COUNT = 4;
		unsigned char L[CHANNELS_COUNT];		
		RGBData(unsigned char R = 0, unsigned char G = 0, unsigned char B = 0, unsigned char I = 0)
		{
			L[INTENSITY_CHANNEL] = I;
			if (CHANNELS_COUNT > R_CHANNEL) L[R_CHANNEL] = R;
			if (CHANNELS_COUNT > G_CHANNEL) L[G_CHANNEL] = G;
			if (CHANNELS_COUNT > B_CHANNEL) L[B_CHANNEL] = B;			
		}
	};
}
