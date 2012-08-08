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
#ifndef _adaptive_filter_h
#define _adaptive_filter_h

#include "image.h"
#include "color_channels.h"
#include "basic_2d_storage.h"
#include "pixel_boundings.h"
#include "weak_segmentator.h"
#include "settings.h"

namespace imago
{
	// basic filter operational type, stores pixel intensity and maximal diff to neighborns
	#pragma pack (push, 1)
	struct FilterPackedRecord
	{
		GrayscaleData intensity;
		unsigned char diffCache;
		FilterPackedRecord()
		{
			intensity = 0;
			diffCache = BLANK;
		}
	};
	#pragma pack (pop)

	// adaptive filter class
	class AdaptiveFilter : public Basic2dStorage<FilterPackedRecord>
	{
	public:
		// entry for processing images with default parameters
		static void process(const Settings& vars, Image& img);

		AdaptiveFilter(int width, int height) : Basic2dStorage<FilterPackedRecord>(width, height) { }
		virtual ~AdaptiveFilter() { }

		// filter image with specified parameters
		void filterImage(const Settings& vars, Image& img, bool allowCrop, double probablyInkPercentage, int lineThickness);		

		friend class ImageAdapter; 

	protected:		
		// does the 'arithmetic mean' interpolation
		void interpolateImage(const AdaptiveFilter& src, int interpolation = 0);

		// gets maximal intensity diff for specified pixel and its neighborns
		unsigned char getMaximalIntensityDiff(int x, int y);

		// gets intensity diff bound, allows to pass no more than inkTresh percents of cropped image
		unsigned char getIntensityBound(double inkTresh, const Rectangle& crop, WeakSegmentator* ws = NULL);

		// outputs cropped part of image data normalized into 0..255 scale
		void normalizedOuput(Image& img, const Rectangle& crop, WeakSegmentator* ws = NULL);

	private:
		int diffIterations, diffStepRange;
	};
}

#endif
