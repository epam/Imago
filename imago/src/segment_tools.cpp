#include "segment_tools.h"
#include "log_ext.h"
#include "image.h"
#include "image_draw_utils.h"
#include "thin_filter2.h"

namespace imago
{
	Points2i SegmentTools::getAllFilled(const Segment& seg)
	{
		Points2i result;
		for (int x = 0; x < seg.getWidth(); x++)
		{
			for (int y = 0; y < seg.getHeight(); y++)
			{
				if (seg.getByte(x,y) == 0) // 0 = black
				{
					result.push_back(Vec2i(x,y));
				}
			}
		}
		return result;
	}

	int SegmentTools::getRealHeight(const Segment& seg)
	{
		int min_y = INT_MAX;
		int max_y = 0;
		Points2i p = getAllFilled(seg);
		for (Points2i::iterator it = p.begin(); it != p.end(); it++)
		{
			if (it->y < min_y) min_y = it->y;
			if (it->y > max_y) max_y = it->y;
		}
		int h = max_y - min_y;
		return h > 0 ? h : 0;
	}

	double SegmentTools::getPercentageUnderLine(const Segment& seg, int line_y)
	{
		int above = 0, below = 0;
		Points2i p = getAllFilled(seg);
		for (Points2i::iterator it = p.begin(); it != p.end(); it++)
			if (it->y + seg.getY() < line_y) above++;
			else if (it->y + seg.getY() > line_y) below++;
		return ((0.5 + below) / (1.0 + below + above));
	}

	Points2i SegmentTools::getInRange(const Segment& seg, Vec2i pos, int range)
	{
		Points2i result;
		int w = seg.getWidth();
		int h = seg.getHeight();
		for (int dx = -range; dx <= range; dx++)
		{
			for (int dy = -range; dy <= range; dy++)
			{
				if (dx == 0 && dy == 0) 
					continue;
				if (   pos.x + dx >= 0 && pos.y + dy >= 0 
					&& pos.x + dx  < w && pos.y + dy  < h
					&& seg.getByte(pos.x + dx, pos.y + dy) == 0)
				{
					result.push_back(Vec2i(pos.x + dx, pos.y + dy));
				}
			}
		}	
		return result;
	}

	Points2i SegmentTools::getEndpoints(Segment& seg)
	{
		logEnterFunction();

		Segment thinseg;
		thinseg.copy(seg);
		ThinFilter2 tf(thinseg);
		tf.apply();
		getLogExt().append("Thinned segment", thinseg);
		
		Points2i endpoints;

		Points2i all = getAllFilled(thinseg);
		for (Points2i::const_iterator it = all.begin(); it != all.end(); it++)
			if (getInRange(thinseg, *it, 1).size() == 1)
				endpoints.push_back(*it);

		getLogExt().append("Endpoints count", endpoints.size());

		if (getLogExt().loggingEnabled())
		{
			Segment endseg;
			endseg.copy(thinseg);
			for (Points2i::const_iterator it = endpoints.begin(); it != endpoints.end(); it++)
				ImageDrawUtils::putCircle(endseg, it->x, it->y, 5, 0); // circle radius 5 hardcoded, visual element only
			getLogExt().append("Segment with endpoints", endseg);
		}

		return endpoints;
	}

	/// returns true if changes made
	bool SegmentTools::makeSegmentConnected(Segment& seg)
	{
		logEnterFunction();

		bool changed = false;

		int w = seg.getWidth();
		int h = seg.getHeight();
		int d = std::min(w, h) / 8 + 1; // MAGIC
		getLogExt().append("w", w);
		getLogExt().append("h", h);
		getLogExt().append("d", d);

		Points2i to_connect = getEndpoints(seg);
	
		// looks like hardcore complexity code, but practically to_connect.size() is below 5
		for (Points2i::const_iterator it1 = to_connect.begin(); it1 != to_connect.end(); it1++)
			for (Points2i::const_iterator it2 = to_connect.begin(); it2 != to_connect.end(); it2++)
			{
				if (it1 == it2) 
					continue;
				if (Vec2i::distance(*it1, *it2) < 2*d) // MAGIC
				{
					Points2i p1 = getInRange(seg, *it1, 2*d);
					Points2i p2 = getInRange(seg, *it2, 2*d);
					for (Points2i::const_iterator pit1 = p1.begin(); pit1 != p1.end(); pit1++)
						for (Points2i::const_iterator pit2 = p2.begin(); pit2 != p2.end(); pit2++)
							if (Vec2i::distance(*pit1, *pit2) < 1.5*d) // MAGIC AGAIN
							{
								ImageDrawUtils::putLineSegment(seg, *pit1, *pit2, 0);
								changed = true;
							}
				}
			}

		return changed;
	}
}
