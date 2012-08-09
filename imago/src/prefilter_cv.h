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
#ifndef _prefilter_cv_h
#define _prefilter_cv_h

#include "image_interface.h"
#include "image.h"
#include "settings.h"

namespace imago
{
	// selects prefilter by vars.filterType
	void prefilterEntrypoint(Settings& vars, Image& raw);

	namespace prefilter_cv
	{
		// required for prefilterCV implementation
		class ImgAdapter :  public ImageInterface
		{
		public:
			ImgAdapter(const Image& _raw, const Image& _bin) : raw(_raw), bin(_bin) { }
			virtual bool isFilled(int x, int y) const { return bin.getByte(x,y) == 0; }			
			virtual unsigned char getIntensity(int x, int y) const { return raw.getByte(x,y); }
			virtual int width() const { return std::min(raw.getWidth(), bin.getWidth()); }	
			virtual int height() const { return std::min(raw.getHeight(), bin.getHeight()); }
		private:
			const Image& raw;
			const Image& bin;
		};
	
		// returns true if result image is binarized
		// may change some pixels inensity if image is already binarized
		bool isBinarized(const Settings& vars, Image &image);

		// returns true if image was modified
		bool resampleImage(Image &image, bool binarized);   
  
		// filters image using cv adaptive filtering and cross-correlation
		void prefilterCV(const Settings& vars, Image& raw);
	}
}

#endif // _prefilter_cv_h
