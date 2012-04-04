#pragma once

namespace imago
{	
	typedef unsigned char GrayscaleData;   // basic type represent AdaptiveFilter data
	
	const GrayscaleData INK = 0;           // preferred intensity means filled
	const GrayscaleData BLANK = 255;       // intensity means blank	

	#pragma pack (push, 1)
	struct RGBPackedRecord
	{
		unsigned char Reserved, R, G, B;
	};
	#pragma pack (pop)

	union RGBData
	{
		RGBPackedRecord RGB;
		unsigned int Color;
	};
}
