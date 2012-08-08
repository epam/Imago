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
#ifndef _segment_tools_h
#define _segment_tools_h

#include "stl_fwd.h"
#include "segment.h"

namespace imago
{
   class SegmentTools
   {
   public:
	   class WaveMap : public Image
	   {
	   public:
		   // initialize wavemap by image pixels (0 = ink, 255 = white)
		   WaveMap(const Image& img);
		   virtual ~WaveMap();

		   // fill wavemap. max_length == maximal path length to find (affects performance)
		   // outer_mode: false - find path inside filled pixels
		   // outer_mode: true - find path outside filled pixels (filled has no penalty, blank - penalty==1)
		   void fillByStartPoint(const Vec2i& start, int max_length = -1, bool outer_mode = false);

		   // check the finish point is accessible (the path exists)
		   bool isAccesssible(const Vec2i& finish);

		   // returns path from start to finish
		   Points2i getPath(const Vec2i& finish);
	   private:
		   int* wavemap;
	   };

	   // return all filled points from segment
		static Points2i getAllFilled(const Segment& seg);

		// returns distance between two sets
		enum DistanceType { dtEuclidian, dtDeltaX, dtDeltaY };
		static double getRealDistance(const Segment& seg1, const Segment& seg2, DistanceType type = dtEuclidian);

		// returns real segment height (delta between top and bottom filled pixels)
		static int getRealHeight(const Segment& seg);

		// returns percentage of pixels with y > line_y
		static double getPercentageUnderLine(const Segment& seg, int line_y);

		// returns all filled pixels in range of [range x range] from pos
		static Points2i getInRange(const Image& seg, Vec2i pos, int range);
		
		// returns all endpoints
		static Points2i getEndpoints(const Segment& seg);

		// stores endpoints to log
		static void logEndpoints(const Segment& seg, const Points2i& pts, int circle_radius = 5 /*visual size*/);
		
		// return nearest pixel of pts from start point
		static Vec2i getNearest(const Vec2i& start, const Points2i& pts);

		// fills pixels inside by its neighborns value
		static bool fixBrokenPixels(Image &seg);

		// resolve issues with bad connected segments (works not fine)
		static bool makeSegmentConnected(Segment& seg, const Points2i& endpoints, double d1, double d2);				
		static bool makeSegmentConnected(Segment& seg, const Image& original_image, double threshold = 0.50);
   };
}

#endif // _segment_tools_h
