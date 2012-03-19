#include "segment_tools.h"
#include "log_ext.h"
#include "image.h"
#include "image_draw_utils.h"
#include "thin_filter2.h"
#include <queue>

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
		if (below + above == 0) 
			return 0.0;
		else
			return ((double)(below) / (double)(below + above));
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

	void SegmentTools::logEndpoints(const Segment& seg, const Points2i& pts, int circle_radius)
	{
		if (getLogExt().loggingEnabled())
		{
			Segment endseg;
			endseg.copy(seg);
			for (Points2i::const_iterator it = pts.begin(); it != pts.end(); it++)
				ImageDrawUtils::putCircle(endseg, it->x, it->y, circle_radius, 64); 
			getLogExt().append("Segment with endpoints", endseg);
		}
	}

	Points2i SegmentTools::getEndpoints(Segment& seg)
	{
		Segment thinseg;
		thinseg.copy(seg);
		ThinFilter2 tf(thinseg);
		tf.apply();
		
		Points2i endpoints;

		Points2i all = getAllFilled(thinseg);
		for (Points2i::const_iterator it = all.begin(); it != all.end(); it++)
			if (getInRange(thinseg, *it, 1).size() == 1)
				endpoints.push_back(*it);

		return endpoints;
	}

	Points2i SegmentTools::getPath(const Segment& seg, Vec2i start, Vec2i finish)
	{
		logEnterFunction();

		Points2i result;
		const int w = seg.getWidth();
		const int h = seg.getHeight();
		int* wavemap = new int[w*h]();

		// TODO: add priority_queue here
		typedef std::queue<std::pair<Vec2i, int> > WorkVector;
		WorkVector v;
		v.push(std::make_pair(start, 1));
		while (!v.empty())
		{
			Vec2i cur_v = v.front().first;
			int cur_d = v.front().second;
			v.pop();
			int idx = cur_v.x + cur_v.y * w;
			if (cur_v.x >= 0 && cur_v.y >= 0 &&
				 cur_v.x < w && cur_v.y < h 
				&& seg.getByte(cur_v.x, cur_v.y) == 0
				&& (wavemap[idx] > cur_d || wavemap[idx] == 0))
			{
				wavemap[idx] = cur_d;

				#define lookup(dx,dy) v.push(std::make_pair(Vec2i(cur_v.x + (dx), cur_v.y + (dy)), cur_d+1));
				lookup(1,0); lookup(-1,0); lookup(0,1); lookup(0,-1);
				lookup(1,1); lookup(-1,1); lookup(1,-1); lookup(-1,-1);				
				#undef lookup
			}
		}		

		if (getLogExt().loggingEnabled())
		{
			Image temp(w, h);
			for (int x = 0; x < w; x++)
				for (int y = 0; y < h; y++)
					temp.getByte(x,y) = (10 * wavemap[x + y * w]) % 256;
			getLogExt().append("wavemap", temp);
		}

		while (true)
		{
			int end = wavemap[finish.x + finish.y * w];

			if (end == 0 || end == 1 || result.size() > h*w)
				break;

			result.push_back(finish);

			Points2i ways;
			#define lookup(dx,dy) ways.push_back(Vec2i(finish.x + dx, finish.y + dy));
			lookup(1,0); lookup(-1,0); lookup(0,1); lookup(0,-1);
			lookup(1,1); lookup(-1,1); lookup(1,-1); lookup(-1,-1);				
			#undef lookup

			int best_v = end;
			Vec2i best_w = finish;
			for (size_t u = 0; u < ways.size(); u++)
			{
				if (ways[u].x >= 0 && ways[u].x < w &&
					ways[u].y >= 0 && ways[u].y < h)
				{
					int value = wavemap[ways[u].x + ways[u].y * w];
					if (value != 0 && value < best_v)
					{
						best_v = value;
						best_w = ways[u];
					}
				}
			}
			finish = best_w;
		}

		delete[] wavemap;

		return result;
	}

	Vec2i SegmentTools::getNearest(Vec2i start, const Points2i& pts)
	{
		Vec2i result = pts[0];
		for (size_t u = 1; u < pts.size(); u++)
			if (Vec2i::distance(start, pts[u]) < Vec2i::distance(start, result))
				result = pts[u];
		return result;
	}

	bool SegmentTools::makeSegmentConnected(Segment& seg, const Image& original_image)
	{
		logEnterFunction();

		bool result = false;
		
		double line_thick = getSettings()["LineThickness"]; // already calculated
		getLogExt().append("line_thick", line_thick);		

		Points2i p = getEndpoints(seg);

		// 60x60 max - performance issue else
		if (p.size() >= 2 && seg.getWidth() < 60 && seg.getHeight() < 60)
		{
			Image src_crop(seg.getWidth(), seg.getHeight());

			double intensity_filled = 0.0, intensity_blank = 0.0;
			int count_filled = 0, count_blank = 0;

			for (int u = 0; u < seg.getWidth(); u++)
				for (int v = 0; v < seg.getHeight(); v++)
				{
					imago::byte b = original_image.getByte(seg.getX() + u, seg.getY() + v);
					if (seg.getByte(u, v) == 0)
					{
						intensity_filled += b;
						count_filled++;
					}
					else
					{
						intensity_blank += b;
						count_blank++;
					}
					src_crop.getByte(u, v) = b;
				}

			if (count_filled > 0)
				intensity_filled /= count_filled;

			if (count_blank > 0)
				intensity_blank /= count_blank;

			// intensity_blank is > intensity_filled
			getLogExt().append("Intensity blank", intensity_blank);
			getLogExt().append("Intensity filled", intensity_filled);
			
			logEndpoints(seg, p, 5);
			getLogExt().append("Image", src_crop);

			double threshold = intensity_filled + (intensity_blank - intensity_filled) * 0.65; // MAGIC!!!

			Segment shifted;
			shifted.init(src_crop.getWidth(), src_crop.getHeight());
			for (int u = 0; u < src_crop.getWidth(); u++)
				for (int v = 0; v < src_crop.getHeight(); v++)
					shifted.getByte(u, v) = src_crop.getByte(u, v) < threshold ? 0 : 255;					

			getLogExt().append("Threshold shifted", shifted);

			ThinFilter2(shifted).apply();

			getLogExt().append("Thinned + Threshold shifted", shifted);

			Points2i shifted_pts = getAllFilled(shifted);

			if (!shifted_pts.empty())	
				for (Points2i::iterator i1 = p.begin(); i1 != p.end(); i1++)
					for (Points2i::iterator i2 = (i1 + 1); i2 != p.end(); i2++)
					{
						Vec2i start = getNearest(*i1, shifted_pts);
						Vec2i end = getNearest(*i2, shifted_pts);
						Points2i path = getPath(shifted, start, end);					
						for (Points2i::iterator pp = path.begin(); pp != path.end(); pp++)
						{
							if (seg.getByte(pp->x, pp->y) != 0)
							{
								seg.getByte(pp->x, pp->y) = 0;
								result = true;
							}
						}
					}
		}
		
		return result;
	}

	/// returns true if changes made
	bool SegmentTools::makeSegmentConnected(Segment& seg, const Points2i& to_connect, double d1, double d2)
	{
		bool changed = false;

		// try to fill broken pixels inside
		for (int x = 0; x < seg.getWidth(); x++)
			for (int y = 0; y < seg.getHeight(); y++)
			{
				if (seg.getByte(x, y) != 0 && getInRange(seg, Vec2i(x,y), 1).size() >= 6)
				{
					seg.getByte(x, y) = 0;
					changed = true;
				}
			}
	
		// try to fill broken pixels inside
		for (int x = 0; x < seg.getWidth(); x++)
			for (int y = 0; y < seg.getHeight(); y++)
			{
				if (seg.getByte(x, y) != 0 && getInRange(seg, Vec2i(x,y), 2).size() >= 19)
				{
					seg.getByte(x, y) = 0;
					changed = true;
				}
			}


		// looks like hardcore complexity code, but practically to_connect.size() is below 5
		for (Points2i::const_iterator it1 = to_connect.begin(); it1 != to_connect.end(); it1++)
			for (Points2i::const_iterator it2 = (it1 + 1); it2 != to_connect.end(); it2++)
			{
				if (Vec2i::distance(*it1, *it2) < d1)
				{
					Points2i p1 = getInRange(seg, *it1, d1);
					Points2i p2 = getInRange(seg, *it2, d1);
					for (Points2i::const_iterator pit1 = p1.begin(); pit1 != p1.end(); pit1++)
						for (Points2i::const_iterator pit2 = p2.begin(); pit2 != p2.end(); pit2++)
							if (Vec2i::distance(*pit1, *pit2) < d2)
							{
								ImageDrawUtils::putLineSegment(seg, *pit1, *pit2, 0);
								changed = true;
							}
				}
			}

		return changed;
	}
}

