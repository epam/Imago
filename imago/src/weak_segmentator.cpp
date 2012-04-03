#include "weak_segmentator.h"
#include <queue>
#include "log_ext.h"
#include "pixel_boundings.h"

namespace imago
{
	int WeakSegmentator::GetAverageIntensity(const ImageInterface &img, const Points2i& pts)
	{
		if (pts.empty())
			return -1;

		double result = 0.0;
		for (size_t u = 0; u < pts.size(); u++)
			result += img.getIntensity(pts[u].x, pts[u].y);
			
		return (int)(result / pts.size());
	}


	bool WeakSegmentator::isContiniousConnected(int x, int y1, int y2)
	{
		bool ok = true;
		for (int y = y1; y < y2; y++)
			ok &= at(x, y) != 0;
		return ok;
	}

	Points2i WeakSegmentator::GetInside(const Points2i& pts, int lookup_range)
	{
		getLogExt().appendPoints("Points", pts);

		/*int map_x_y1[RGB_MAX_IMAGE_DIM];
		int map_x_y2[RGB_MAX_IMAGE_DIM];
		for (int u = 0; u < RGB_MAX_IMAGE_DIM; u++)
		{
			// pre-fill
			map_x_y1[u] = RGB_MAX_IMAGE_DIM;
			map_x_y2[u] = 0;
		}

		// extract min/max by scanlines
		for (size_t u = 0; u < pts.size(); u++)
		{
			if (pts[u].y < map_x_y1[pts[u].x])
				map_x_y1[pts[u].x] = pts[u].y;
			if (pts[u].y > map_x_y2[pts[u].x])
				map_x_y2[pts[u].x] = pts[u].y;
		}

		// now check area is connected

		// 1. find min/max indexes
		int min_idx = -1, max_idx = -1;
		for (int u = 0; u < RGB_MAX_IMAGE_DIM; u++)
		{
			if (map_x_y1[u] != RGB_MAX_IMAGE_DIM)
			{
				if (min_idx == -1)
					min_idx = u;
				max_idx = u;
			}
		}
		if (min_idx == -1)
			return Points2i(); // empty

		getLogExt().appendText("1 pass");

		// 2. now check indexes in [min_idx, max_idx] are filled continiously
		bool ok = true;
		for (int u = min_idx + 1; u <= max_idx; u++)
			ok &= map_x_y1[u] <= map_x_y2[u];
				    && abs(map_x_y1[u] - map_x_y1[u-1]) <= 2 * lookup_range // TODO! TEMP!
					&& abs(map_x_y2[u] - map_x_y2[u-1]) <= 2 * lookup_range; 
		if (!ok)
			return Points2i(); // empty

		getLogExt().appendText("2 pass");

		// 3. check that map_x_y1[min_idx] is connected to map_x_y2[min_idx]
		//           and map_x_y1[max_idx] is connected to map_x_y2[max_idx]
			
		// UPD: shift min_idx to meet criteria

		while (min_idx < max_idx)
		{
			if (isContiniousConnected(min_idx, map_x_y1[min_idx], map_x_y2[min_idx]))
				break;
			else
				min_idx++;
		}

		// UPD: shift max_idx to meet criteria

		while (min_idx < max_idx)
		{
			if (isContiniousConnected(max_idx, map_x_y1[max_idx], map_x_y2[max_idx]))
				break;
			else
				max_idx--;
		}

		if (min_idx >= max_idx)
			return Points2i(); // empty

		getLogExt().appendText("3 pass");

		// yeah, area is connected			
		for (int x = min_idx + 1; x < max_idx; x++)
			for (int y = map_x_y1[x] + 1; y < map_x_y2[x]; y++)
				if (at(x, y) == 0) // still blank
					result.push_back(Vec2i(x, y));*/

		Points2i result;

		CustomShapedBounding b(pts);

		getLogExt().appendText("init done");

		b.itReset();
		for (Vec2i p; b.itNext(p); )
			result.push_back(p);

		if (!result.empty())
			getLogExt().appendPoints("result", result);

		return result;
	}

	void WeakSegmentator::fillInside(const ImageInterface &img, int lookup_range)
	{
		// erase glares and noise
		std::vector<std::pair<int,int> > intensityLevels; // first - outside, second - inside
		for (int u = start_id; u < id; u++)
		{
			Points2i& points = SegmentPoints[u];
			Points2i& inside = GetInside(points, lookup_range);
			int i_outside = GetAverageIntensity(img, points);
			int i_inside = GetAverageIntensity(img, inside);
			//getLogExt().append("Inside intensity", i_inside);
			//getLogExt().append("Outside intensity", i_outside);
			intensityLevels.push_back(std::make_pair(i_outside, i_inside));
			// TEST! fill inside areas
			for (size_t v = 0; v < inside.size(); v++)
				at(inside[v].x, inside[v].y) = 1; // 'random' id
		}

		getLogExt().append("Added pixels", added_pixels);
		getLogExt().append("Segments count", SegmentPoints.size());
	}

	int WeakSegmentator::appendData(const ImageInterface &img, int lookup_range)
	{
		logEnterFunction();
			
		// TODO: calc useful pixels only
		added_pixels = 0;

		start_id = id;

		for (int y = 0; y < height(); y++)
			for (int x = 0; x < width(); x++)
				if (at(x,y) == 0 && img.isFilled(x,y))
					fill(img, id++, x, y, lookup_range);			

		return added_pixels;
	}

	WeakSegmentator::WeakSegmentator(const ImageInterface &img) 
		: Basic2dStorage<int>(img.width(), img.height(), 0), id(1)
	{	
	}

	WeakSegmentator::~WeakSegmentator()
	{			
	}

	void WeakSegmentator::performPixelOptimizations()
	{
		logEnterFunction();

		for (int y = 0; y < height(); y++)
			for (int x = 0; x < width(); x++)
			{
				int count = 0, id = 0;
				for (int dy = -1; dy <= 1; dy++)
					for (int dx = -1; dx <= 1; dx++)
						if ((dx != 0 || dy != 0) && inRange(x+dx, y+dy))
						{
							if (at(x+dx,y+dy) != 0)
							{
								id = at(x+dx,y+dy);
								count++;
							}
						}
				if (at(x,y) != 0 && count == 0) // erase lonely pixel
					at(x,y) = 0;
				else if (at(x,y) == 0 && count >= 7) // fill inside pixels group
					at(x,y) = id;
			}
	}

	void WeakSegmentator::eraseNoise(int threshold)
	{
		logEnterFunction();

		for (int y = 0; y < height(); y++)
			for (int x = 0; x < width(); x++)
			{
				int v = at(x, y);
				if (v > 0 && (int)SegmentPoints[v].size() < threshold)
				{
					SegmentPoints[v].clear();
					at(x,y) = 0;
				}
			}			
	}

	bool WeakSegmentator::needCrop(Rectangle& crop)
	{
		logEnterFunction();

		int area_threshold = width() * height() * AREA_THRESHOLD_FACTOR;
		for (size_t u = 0; u < SegmentPoints.size(); u++)
		{
			Rectangle bounds;
			if (getRectangularArea(u) > area_threshold 
				&& hasRectangularStructure(u, RECTANGULAR_WINDOWSIZE, RECTANGULAR_THRESHOLD, bounds))
			{
				getLogExt().append("Has rectangular structure, id", u);	
				bounds.adjustBorder(RECTANGULAR_WINDOWSIZE*2);
				crop = bounds;
				return true;
			}
		}
		return false;
	}

	void WeakSegmentator::getBoundingBox(Rectangle& bound) const
	{
		bound.x = bound.y = MAX_IMAGE_DIMENSIONS;
		bound.width = bound.height = 0;
		for (std::map<int, Points2i>::const_iterator it = SegmentPoints.begin(); it != SegmentPoints.end(); it++)
			getRectBounds(it->second, bound, false);
	}

	void WeakSegmentator::getRectBounds(const Points2i& p, Rectangle& bounds, bool reinit) const
	{
		int min_x = width(), max_x = 0, min_y = height(), max_y = 0;
		if (!reinit)
		{
			min_x = bounds.x1();
			min_y = bounds.y1();
			max_x = bounds.x2();
			max_y = bounds.y2();
		}
		for (Points2i::const_iterator it = p.begin(); it != p.end(); it++)
		{
			min_x = std::min(min_x, it->x);
			min_y = std::min(min_y, it->y);
			max_x = std::max(max_x, it->x);
			max_y = std::max(max_y, it->y);
		}
		bounds = Rectangle(min_x, min_y, max_x, max_y, 0);
	}
		
	int WeakSegmentator::getRectangularArea(int id)
	{
		Rectangle bounds;
		getRectBounds(SegmentPoints[id], bounds);
		return bounds.width * bounds.height;
	}		

	bool WeakSegmentator::hasRectangularStructure(int id, int window_size, double threshold, Rectangle& bound)
	{
		Points2i& p = SegmentPoints[id];
			
		int map_x[MAX_IMAGE_DIMENSIONS] = {0};
		int map_y[MAX_IMAGE_DIMENSIONS] = {0};
		for (Points2i::iterator it = p.begin(); it != p.end(); it++)
		{
			map_x[it->x]++;
			map_y[it->y]++;
		}

		double x1c, x2c, y1c, y2c;			
		if (get2centers(map_x, width(), x1c, x2c) && get2centers(map_y, height(), y1c, y2c))
		{
			// now update maps
			memset(map_x, 0, sizeof(map_x));
			memset(map_y, 0, sizeof(map_y));
			for (Points2i::iterator it = p.begin(); it != p.end(); it++)
			{
				if (it->y > y1c && it->y < y2c) map_x[it->x]++;
				if (it->x > x1c && it->x < x2c) map_y[it->y]++;
			}
			// and centers
			if (get2centers(map_x, width(), x1c, x2c) && get2centers(map_y, height(), y1c, y2c) &&
				fabs(x1c - x2c) > 2*window_size && fabs(y1c - y2c) > 2*window_size)
			{
				int good = 0, bad = 0;
				for (Points2i::iterator it = p.begin(); it != p.end(); it++)
					if ((fabs(it->x - x1c) < window_size || fabs(it->x - x2c) < window_size) ||
						(fabs(it->y - y1c) < window_size || fabs(it->y - y2c) < window_size))
						good++;
					else
						bad++;
				if ((double)good / (good+bad) > threshold)
				{
					bound = Rectangle(x1c, y1c, x2c, y2c, 0);
					return true;
				}
			}
		}

		return false;
	}

	void WeakSegmentator::fill(const ImageInterface &img, int id, int sx, int sy, int lookup_range)
	{
		typedef std::queue<Vec2i> WorkVector;
		WorkVector v;
		v.push(Vec2i(sx,sy));

		while (!v.empty())
		{
			Vec2i cur = v.front();
			v.pop();

			if (at(cur.x,cur.y) == 0)
			{
				at(cur.x,cur.y) = id;
				SegmentPoints[id].push_back(cur);
				added_pixels++;

				for (int dx = -lookup_range; dx <= lookup_range; dx++)
					for (int dy = -lookup_range; dy <= lookup_range; dy++)
					{
						Vec2i t(cur.x+dx,cur.y+dy);
						if ((dx != 0 || dy != 0) && inRange(t.x, t.y) 
							&& at(t.x, t.y) == 0 && img.isFilled(t.x, t.y))
						{
							// TODO: !!!fixup hack:
							// -- connectivity maker code
							/*if (at(cur.x + dx/2, cur.y + dy/2) == 0)
							{
								at(cur.x + dx/2, cur.y + dy/2) = id;
								added_pixels++;
							}
							*/
							// end hack
							v.push(t);
						}
					}
			}
		}
	}

	bool WeakSegmentator::get2centers(int* data, int size, double &c1, double& c2) // c1 < c2
	{
		double average = 0.0, count = 0.0;
		for (int u = 0; u < size; u++)
		{
			average += u * data[u];
			count += data[u];
		}			
			
		if (count < 1)
			return false;

		average /= count;
		c1 = 0.0;
		c2 = 0.0;
		double count1 = 0.0;
		double count2 = 0.0;

		for (int u = 0; u < size; u++)
		{
			if (u < average)
			{
				c1 += u * data[u];
				count1 += data[u];
			}
			else
			{
				c2 += u * data[u];
				count2 += data[u];
			}
		}

		if (count1 < 1 || count2 < 1)
			return false;

		c1 /= count1;
		c2 /= count2;
		return true;
	}
}
