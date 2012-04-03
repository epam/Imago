#pragma once

namespace imago
{
	/* code organization constants. Fixed values, not method params. 
	*/
	const int    INK = 0;                      // preferred intensity means filled
	const int    BLANK = 255;                  // intensity means blank	
	
	typedef unsigned char GSData; // TODO...

	const int    INTENSITY_CHANNEL = 0; // intensity channel

	struct RGBData
	{
		static const int CHANNELS_COUNT = 4;
		unsigned char L[CHANNELS_COUNT];		
		RGBData(unsigned char R = 0, unsigned char G = 0, unsigned char B = 0, unsigned char I = 0)
		{
			L[INTENSITY_CHANNEL] = I;
			if (CHANNELS_COUNT > 1) L[1] = R;
			if (CHANNELS_COUNT > 2) L[2] = G;
			if (CHANNELS_COUNT > 3) L[3] = B;			
		}
	};
}
