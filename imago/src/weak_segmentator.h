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
	class WeakSegmentator : public Basic2dStorage<unsigned short int /*id*/>
	{
	public:		
		WeakSegmentator(int width, int height) : Basic2dStorage<unsigned short int>(width, height) {}		

		// addend data from image (img.isFilled() called)
		int appendData(const Image &img, int lookup_range, bool connectMode = false);
		
		// updates crop if required
		bool needCrop(const Settings& vars, Rectangle& crop, int winSize);		

		// returns neighbors of p with intensity == INK
		static Points2i getNeighbors(const Image& img, const Vec2i& p, int range = 1);
		
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
		void fill(const Image& img, int& id, int startx, int starty, int lookup_range, bool connectMode);
		
		// returns shortest path between two pixels
		Points2i getShortestPath(const Image& img, const Vec2i& start, const Vec2i& end);

		// returns 2 probably condensation point for integer vector
		static bool get2centers(const std::vector<int>& data, double &c1, double& c2);		
	};
}

#endif //_weak_segmentator_h
