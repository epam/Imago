#include "pixel_boundings.h"
#include "settings.h"

namespace imago
{
	RectShapedBounding::RectShapedBounding(const RectShapedBounding& src)
	{
		bound = src.bound;
		itReset();
	}

	RectShapedBounding::RectShapedBounding(const Points2i& pts)
	{
		int min_x = MaxImageDimensions, min_y = MaxImageDimensions, max_x = 0, max_y = 0;
		for (Points2i::const_iterator it = pts.begin(); it != pts.end(); it++)
		{
			min_x = std::min(min_x, it->x);
			min_y = std::min(min_y, it->y);
			max_x = std::max(max_x, it->x);
			max_y = std::max(max_y, it->y);
		}
		bound = Rectangle(min_x, min_y, max_x, max_y, 0);
		itReset();
	}

	void RectShapedBounding::itReset()
	{
		cur_x = 0;
		cur_y = 0;
	}

	bool RectShapedBounding::itNext(Vec2i& point)
	{
		if (cur_x < bound.x1())
		{
			cur_x = bound.x1();
		}

		while (cur_x <= bound.x2())
		{			
			if (cur_y < bound.y1())
			{
				cur_y = bound.y1();
			}
			else if (cur_y > bound.y2())
			{
				cur_y = bound.y1();
				cur_x++;
			}
			else
			{
				point.x = cur_x;
				point.y = cur_y;
				return true;
			}
		}
		return false;
	}

	CustomShapedBounding::CustomShapedBounding(const CustomShapedBounding& src)
	{
		slices = src.slices;
		itReset();
	}

	CustomShapedBounding::CustomShapedBounding(const Points2i& pts) // now simple min-max boundary init
	{
		int map_x_y1[MaxImageDimensions];
		int map_x_y2[MaxImageDimensions];
		for (int u = 0; u < MaxImageDimensions; u++)
		{
			// pre-fill
			map_x_y1[u] = MaxImageDimensions;
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

		int min_idx = -1, max_idx = -1;
		for (int u = 0; u < MaxImageDimensions; u++)
		{
			if (map_x_y1[u] != MaxImageDimensions)
			{
				if (min_idx == -1)
					min_idx = u;
				max_idx = u;
			}
		}

		for (int u = min_idx; u <= max_idx; u++)
		{
			Slice p;
			p.push_back(std::make_pair(map_x_y1[u], map_x_y2[u]));
			slices.push_back(std::make_pair(u, p));
		}

		itReset();
	}

	bool CustomShapedBounding::itNext(Vec2i& point)
	{
		while (cur_slice < slices.size())
		{
			if (cur_range >= slices[cur_slice].second.size())
			{
				cur_slice++;
				cur_range = 0;
				cur_yval = 0;
			}
			else
			{				
				if (cur_yval < slices[cur_slice].second[cur_range].first)
				{
					// fixup cur_y set to 0
					cur_yval = slices[cur_slice].second[cur_range].first;
				}
				else if (cur_yval > slices[cur_slice].second[cur_range].second)
				{
					cur_range++;						
				}
				else
				{
					point.x = slices[cur_slice].first;
					point.y = cur_yval;
					cur_yval++;
					return true;
				}
			}
		}
		return false;
	}

	void CustomShapedBounding::itReset()
	{
		cur_slice = 0;
		cur_range = 0;
		cur_yval = 0;
	}
}