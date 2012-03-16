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
		static Points2i getAllFilled(const Segment& seg);
		static int getRealHeight(const Segment& seg);
		static double getPercentageUnderLine(const Segment& seg, int line_y);
		static Points2i getInRange(const Segment& seg, Vec2i pos, int range);
		
		static Points2i getEndpoints(Segment& seg);
		static void logEndpoints(const Segment& seg, const Points2i& pts, int circle_radius);
		
		static bool makeSegmentConnected(Segment& seg, const Points2i& endpoints, double d1, double d2);		
   };
}

#endif // _segment_tools_h
