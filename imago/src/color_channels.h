/****************************************************************************
 * Copyright (C) 2009-2012 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#pragma once
#ifndef _color_channels_h
#define _color_channels_h

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

#endif // _color_channels_h
