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

#include "segment_tools.h"
#include "log_ext.h"
#include "image.h"
#include "image_draw_utils.h"
#include "thin_filter2.h"
#include <queue>
#include <float.h>

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

	double SegmentTools::getRealDistance(const Segment& seg1, const Segment& seg2, DistanceType type)
	{
		Points2i p1 = getAllFilled(seg1);
		Points2i p2 = getAllFilled(seg2);
		double result = DBL_MAX;
		for (size_t u1 = 0; u1 < p1.size(); u1++)
			for (size_t u2 = 0; u2 < p2.size(); u2++)
			{
				int x1 = p1[u1].x + seg1.getX();
				int y1 = p1[u1].y + seg1.getY();
				int x2 = p2[u2].x + seg2.getX();
				int y2 = p2[u2].y + seg2.getY();
				double d = DBL_MAX;

				if (type == dtDeltaX)
				{
					d = absolute(x1 - x2);
				}
				else if (type == dtDeltaY)
				{
					d = absolute(y1 - y2);
				}
				else if (type == dtEuclidian)
				{
					d = Vec2i::distance(Vec2i(x1,y1), Vec2i(x2,y2));
				}

				if (d < result)
					result = d;
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

	Points2i SegmentTools::getInRange(const Image& seg, Vec2i pos, int range)
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

	void SegmentTools::WaveMap::fillByStartPoint(const Vec2i& start, int max_length, bool outer_mode)
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

			if (cur_v.x >= 0 && cur_v.y >= 0 && cur_v.x < getWidth() && cur_v.y < getHeight() // range
				&& (getByte(cur_v.x, cur_v.y) == 0 || outer_mode) // fill
				&& (wavemap[idx] > cur_d || wavemap[idx] == 0)) // not filled with better value
			{
				wavemap[idx] = cur_d;

				if (max_length > 0 && cur_d > max_length)
				{
					// ignore
				}
				else
				{
					int new_d = cur_d;
					if (outer_mode)
					{
						if (getByte(cur_v.x, cur_v.y) != 0)
							new_d++; // penalty 1 if not filled
					}
					else
						new_d++; // penalty 1 anyway


					#define lookup(dx,dy) v.push(std::make_pair(Vec2i(cur_v.x + (dx), cur_v.y + (dy)), new_d));
					lookup(1,0); lookup(-1,0); lookup(0,1);  lookup(0,-1);
					lookup(1,1); lookup(-1,1); lookup(1,-1); lookup(-1,-1);				
					#undef lookup
				}
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
}

