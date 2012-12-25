/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
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
#ifndef _image_interface_h
#define _image_interface_h

#include "stl_fwd.h"

namespace imago
{
	// the most generic image interface
	class ImageInterface
	{
	public:
		// check intenisty (or something) value is passed some bounds
		virtual bool isFilled(int x, int y) const = 0;

		// get raw intensity value 0..255
		virtual unsigned char getIntensity(int x, int y) const = 0; 

		// get the image dimensions
		virtual int width() const = 0;
		virtual int height() const = 0;
	};	
}

#endif // _image_interface_h

