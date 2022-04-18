/****************************************************************************
* Copyright (C) from 2009 to Present EPAM Systems.
*
* This file is part of Imago toolkit.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***************************************************************************/

#pragma once
#ifndef _weak_segmentator_h
#define _weak_segmentator_h

#include <map>
#include <vector>
#include "image.h"
#include "basic_2d_storage.h"
#include "rectangle.h"
#include "stl_fwd.h"
#include "settings.h"

namespace imago
{
	class WeakSegmentator : public Basic2dStorage<int /*id*/>
	{
	public:		
		static Points2i getLookupPattern(int range = 1, bool fill = true);

		WeakSegmentator(int width, int height) : Basic2dStorage<int>(width, height) {}		

		// addend data from image (img.isFilled() called)
		int appendData(const Image &img, const Points2i& lookup_pattern = getLookupPattern(), bool connectMode = false);
		
		// updates crop if required
		bool needCrop(const Settings& vars, Rectangle& crop, int winSize);		

		// decorner image by setting corner pixels to 'set_to' value
		static void decorner(Image &img, byte set_to);

		typedef std::map<int, Points2i> SegMap;
		SegMap SegmentPoints;		

	protected:				
		// returns area of bounding box of segment with id
		int getRectangularArea(int id);

		// check segment with id has rectangular structure
		bool hasRectangularStructure(const Settings& vars, int id, Rectangle& bound, int winSize);
		
	private:
		// returns filled pixels count
		void fill(const Image& img, int& id, int startx, int starty, const Points2i& lookup_pattern, bool connectMode);

		// returns 2 probably condensation point for integer vector
		static bool get2centers(const std::vector<int>& data, double &c1, double& c2);		
	};
}

#endif //_weak_segmentator_h
