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
         getLogExt().append("Number of endpoints", pts.size()); 
			getLogExt().appendSegment("Segment with endpoints", endseg);
		}
	}

	Points2i SegmentTools::getEndpoints(const Segment& seg)
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

	SegmentTools::WaveMap::WaveMap(const Image& img)
	{
		copy(img);
		wavemap = new int[getWidth()*getHeight()]();
	}

	SegmentTools::WaveMap::~WaveMap()
	{
		if (wavemap)
		{
			delete []wavemap;
			wavemap = NULL;
		}
	}

	void SegmentTools::WaveMap::fillByStartPoint(const Vec2i& start)
	{
		typedef std::queue<std::pair<Vec2i, int> > WorkVector;
		WorkVector v;
		v.push(std::make_pair(start, 1));
		while (!v.empty())
		{
			Vec2i cur_v = v.front().first;
			int cur_d = v.front().second;
			v.pop();
			
			int idx = cur_v.x + cur_v.y * getWidth();

			if (cur_v.x >= 0 && cur_v.y >= 0
				&& cur_v.x < getWidth() && cur_v.y < getHeight()
				&& getByte(cur_v.x, cur_v.y) == 0
				&& (wavemap[idx] > cur_d || wavemap[idx] == 0))
			{
				wavemap[idx] = cur_d;

				#define lookup(dx,dy) v.push(std::make_pair(Vec2i(cur_v.x + (dx), cur_v.y + (dy)), cur_d+1));
				lookup(1,0); lookup(-1,0); lookup(0,1);  lookup(0,-1);
				lookup(1,1); lookup(-1,1); lookup(1,-1); lookup(-1,-1);				
				#undef lookup
			}
		}		
	}

	bool SegmentTools::WaveMap::isAccesssible(const Vec2i& finish)
	{
		return wavemap[finish.x + finish.y * getWidth()] != 0;
	}

	Points2i SegmentTools::WaveMap::getPath(const Vec2i& other)
	{
		Vec2i finish = other;

		Points2i result;

		size_t length_limit = getWidth()*getHeight();

		while (isAccesssible(finish))
		{
			int end = wavemap[finish.x + finish.y * getWidth()];

			if (end == 0 || end == 1 || result.size() > length_limit)
				break;

			result.push_back(finish);

			Points2i ways;
			#define lookup(dx,dy) ways.push_back(Vec2i(finish.x + (dx), finish.y + (dy)));
			lookup(1,0); lookup(-1,0); lookup(0,1);  lookup(0,-1);
			lookup(1,1); lookup(-1,1); lookup(1,-1); lookup(-1,-1);				
			#undef lookup

			int best_v = end;
			Vec2i best_w = finish;
			for (size_t u = 0; u < ways.size(); u++)
			{
				if (ways[u].x >= 0 && ways[u].x < getWidth() &&
					ways[u].y >= 0 && ways[u].y < getHeight())
				{
					int value = wavemap[ways[u].x + ways[u].y * getWidth()];
					if (value != 0 && value < best_v)
					{
						best_v = value;
						best_w = ways[u];
					}
				}
			}
			finish = best_w;
		}

		return result;
	}

	
	Vec2i SegmentTools::getNearest(const Vec2i& start, const Points2i& pts)
	{
		Vec2i result = pts[0];
		for (size_t u = 1; u < pts.size(); u++)
			if (Vec2i::distance(start, pts[u]) < Vec2i::distance(start, result))
				result = pts[u];
		return result;
	}

	bool SegmentTools::makeSegmentConnected(Segment& seg, const Image& original_image, double threshold_factor)
	{
		logEnterFunction();

		bool result = false;
		
		Points2i src_endpoints = getEndpoints(seg);
		logEndpoints(seg, src_endpoints);

		Image original_crop(seg.getWidth(), seg.getHeight());

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
				original_crop.getByte(u, v) = b;
			}

		if (count_filled == 0)
		{
			getLogExt().appendText("Nothing filled, exiting");
			return result;
		}

		if (count_filled > 0)
			intensity_filled /= count_filled;			

		if (count_blank > 0)
			intensity_blank /= count_blank;

		// intensity_blank is > intensity_filled
		getLogExt().append("Intensity blank", intensity_blank);
		getLogExt().append("Intensity filled", intensity_filled);
			
		getLogExt().appendImage("Source image crop", original_crop);

		double threshold = intensity_filled + (intensity_blank - intensity_filled) * threshold_factor;

		Segment threshold_shifted;
		threshold_shifted.init(original_crop.getWidth(), original_crop.getHeight());

		for (int u = 0; u < original_crop.getWidth(); u++)
		{
			for (int v = 0; v < original_crop.getHeight(); v++)
			{
				double average = 0.0;
				int count = 0;
					
				// process average filter here
				int range = 1;
				for (int dx = -range; dx <= range; dx++)
				{
					for (int dy = -range; dy <= range; dy++)
					{
						if (dx + u >= 0 && dx + u < original_crop.getWidth() &&
							dy + v >= 0 && dy + v < original_crop.getHeight())
						{
							average += original_crop.getByte(dx + u, dy + v);
							count++;
						}
					}
				}

				if (count) average /= count;

				threshold_shifted.getByte(u, v) = average < threshold ? 0 : 255;
			}
		}

		getLogExt().appendSegment("Threshold shifted and binarized", threshold_shifted);			

		WaveMap connected(threshold_shifted);
		if (src_endpoints.empty())
		{
			Points2i all = getAllFilled(seg);
			if (!all.empty())
				connected.fillByStartPoint(all[0]);
		}
		else
		{
			for (size_t u = 0; u < src_endpoints.size(); u++)
				connected.fillByStartPoint(src_endpoints[u]);
		}

		// now modify according endpoints accessed
		for (int u = 0; u < connected.getWidth(); u++)
			for (int v = 0; v < connected.getHeight(); v++)
				if (!connected.isAccesssible(Vec2i(u,v)))
					threshold_shifted.getByte(u, v) = 255; // make blank

		getLogExt().appendSegment("Modified connectivity by wavemap", threshold_shifted);

		/*// now remove too thin and probably wrong lines
		for (int u = 0; u < connected.getWidth(); u++)
			for (int v = 0; v < connected.getHeight(); v++)
				if (getInRange(threshold_shifted, Vec2i(u,v), 1).size() <= 3)
					threshold_shifted.getByte(u, v) = 255; // make blank

		// now try to fix broken pixels inside
		for (int u = 0; u < connected.getWidth(); u++)
			for (int v = 0; v < connected.getHeight(); v++)
				if (getInRange(threshold_shifted, Vec2i(u,v), 1).size() >= 7)
					threshold_shifted.getByte(u, v) = 0; // make filled

		for (int u = 0; u < connected.getWidth(); u++)
			for (int v = 0; v < connected.getHeight(); v++)
				if (getInRange(threshold_shifted, Vec2i(u,v), 2).size() >= 21)
					threshold_shifted.getByte(u, v) = 0; // make filled			

		getLogExt().appendSegment("Modified by pixel operations", threshold_shifted); */

		Points2i mod_endpoints = getEndpoints(threshold_shifted);			

		result = mod_endpoints.size() <= src_endpoints.size()
				    && getAllFilled(threshold_shifted).size() > getAllFilled(seg).size() / 2
					&& getAllFilled(threshold_shifted).size() < getAllFilled(seg).size() * 2;

		if (result)
		{
			seg.copy(threshold_shifted, false);
			getLogExt().appendSegment("Modified segment (result)", seg);
		}
		else
		{
			getLogExt().appendText("Connectivity became worser, ignoring");
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

