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
		   WaveMap(const Image& img);
		   virtual ~WaveMap();
		   void fillByStartPoint(const Vec2i& start);
		   bool isAccesssible(const Vec2i& finish);
		   Points2i getPath(const Vec2i& finish);
	   private:
		   int* wavemap;
	   };

		static Points2i getAllFilled(const Segment& seg);
		static int getRealHeight(const Segment& seg);
		static double getPercentageUnderLine(const Segment& seg, int line_y);
		static Points2i getInRange(const Image& seg, Vec2i pos, int range);
		
		static Points2i getEndpoints(const Segment& seg);
		static void logEndpoints(const Segment& seg, const Points2i& pts, int circle_radius = 5 /*visual size*/);
		
		static Vec2i getNearest(const Vec2i& start, const Points2i& pts);

		static bool fixBrokenPixels(Image &seg);

		static bool makeSegmentConnected(Segment& seg, const Points2i& endpoints, double d1, double d2);		
		
		static bool makeSegmentConnected(Segment& seg, const Image& original_image, double threshold = 0.50);
   };
}

#endif // _segment_tools_h
