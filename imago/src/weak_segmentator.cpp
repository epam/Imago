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

#include "weak_segmentator.h"
#include <queue>
#include <string.h>
#include "log_ext.h"
#include "pixel_boundings.h"
#include "color_channels.h"
#include "thin_filter2.h"
#include "segment_tools.h"

namespace imago
{	
	Points2i WeakSegmentator::getNeighbors(const Image& img, const Vec2i& p, int range)
	{
		Points2i neighb;
		for (int dy = -range; dy <= range; dy++)
			for (int dx = -range; dx <= range; dx++)
				if ((dx != 0 || dy != 0) && p.x+dx >= 0 && p.y+dy >= 0
					&& p.x+dx < img.getWidth() && p.y+dy < img.getHeight() )
					if (img.getByte(p.x+dx, p.y+dy) == INK)
						neighb.push_back(Vec2i(p.x+dx, p.y+dy));
		return neighb;
	}

	void WeakSegmentator::decorner(Image &img, GrayscaleData set_to)
	{
		logEnterFunction();

		for (int y = 0; y < img.getHeight(); y++)
		{
			for (int x = 0; x < img.getWidth(); x++)
			{
				if (img.getByte(x,y) != INK)
					continue;
				if (getNeighbors(img, Vec2i(x,y)).size() > 2)
					img.getByte(x,y) = set_to;
			}
		}

		getLogExt().appendImage("Decorner", img);
	}

	int WeakSegmentator::appendData(const ImageInterface &img, int lookup_range, bool reconnect)
	{
		logEnterFunction();
			
		int added_pixels = 0;

		for (int y = 0; y < height(); y++)
			for (int x = 0; x < width(); x++)
				if (at(x,y).id == 0 && img.isFilled(x,y))
				{
					int id = SegmentPoints.size()+1;
					fill(img, id, x, y, lookup_range, reconnect);			
					added_pixels += SegmentPoints[id].size();
				}

		getLogExt().append("Currently added pixels", added_pixels);
		getLogExt().append("Total segments count", SegmentPoints.size());

		return added_pixels;
	}

	bool WeakSegmentator::needCrop(const Settings& vars, Rectangle& crop, int winSize)
	{
		logEnterFunction();

		int area_pixels = round(width() * height() * vars.weak_seg.RectangularCropAreaTreshold);
		for (size_t id = 1; id <= SegmentPoints.size(); id++)
		{			
			Rectangle bounds;
			if (getRectangularArea(id) > area_pixels && hasRectangularStructure(vars, id, bounds, winSize))
			{
				getLogExt().append("Has rectangular structure, id", id);	
				bounds.adjustBorder(winSize*2);
				crop = bounds;
				return true;
			}
		}
		return false;
	}

	int WeakSegmentator::getRectangularArea(int id)
	{
		RectShapedBounding b(SegmentPoints[id]);		
		return b.getBounding().width * b.getBounding().height;
	}		

	bool WeakSegmentator::hasRectangularStructure(const Settings& vars, int id, Rectangle& bound, int winSize)
	{
		Points2i& p = SegmentPoints[id];
		
		std::vector<int> map_x;
		std::vector<int> map_y;

		for (Points2i::iterator it = p.begin(); it != p.end(); it++)
		{
			if (it->x >= map_x.size())
				map_x.resize(it->x + 1);
			map_x[it->x]++;

			if (it->y >= map_y.size())
				map_y.resize(it->y + 1);
			map_y[it->y]++;
		}

		double x1c, x2c, y1c, y2c;			
		if (get2centers(map_x, x1c, x2c) && get2centers(map_y, y1c, y2c))
		{
			// now update maps
			map_x.clear();
			map_y.clear();

			for (Points2i::iterator it = p.begin(); it != p.end(); it++)
			{
				if (it->y > y1c && it->y < y2c)
				{
					if (it->x >= map_x.size())
						map_x.resize(it->x + 1);
					map_x[it->x]++;
				}
				if (it->x > x1c && it->x < x2c)
				{
					if (it->y >= map_y.size())
						map_y.resize(it->y + 1);
					map_y[it->y]++;
				}
			}
			// and centers
			if (get2centers(map_x, x1c, x2c) && get2centers(map_y, y1c, y2c) &&
				fabs(x1c - x2c) > 2*winSize && fabs(y1c - y2c) > 2*winSize)
			{
				int good = 0, bad = 0;
				for (Points2i::iterator it = p.begin(); it != p.end(); it++)
					if ((fabs(it->x - x1c) < winSize || fabs(it->x - x2c) < winSize) ||
						(fabs(it->y - y1c) < winSize || fabs(it->y - y2c) < winSize))
						good++;
					else
						bad++;
				if ((double)good / (good+bad) > vars.weak_seg.RectangularCropFitTreshold)
				{
					bound = Rectangle((int)x1c, (int)y1c, (int)x2c, (int)y2c, 0);
					return true;
				}
			}
		}

		return false;
	}

	Points2i WeakSegmentator::getShortestPath(const ImageInterface &img, const Vec2i& start, const Vec2i& end)
	{
		// this function works OK but it's such a performance waste

		int id = at(start.x, start.y).id;
		const Points2i pts = SegmentPoints[id];
		Points2i pts_ext = pts;
		pts_ext.push_back(end);

		RectShapedBounding b(pts_ext);
		int _x = b.getBounding().x;
		int _y = b.getBounding().y;
		Image output(b.getBounding().width+1, b.getBounding().height+1);		
		output.fillWhite();
		for (size_t u = 0; u < pts.size(); u++) // draw points
			output.getByte(pts[u].x - _x, pts[u].y - _y) = 0;

		SegmentTools::WaveMap wave(output);
		//getLogExt().appendImage("wavemap for", output);
		wave.fillByStartPoint(Vec2i(start.x - _x, start.y - _y), 10, true);
		Points2i res = wave.getPath(Vec2i(end.x - _x, end.y - _y));
		Points2i result;
		for (size_t u = 0; u < res.size(); u++)
			result.push_back(Vec2i(res[u].x + _x, res[u].y + _y));
		return result;
	}

	void WeakSegmentator::fill(const ImageInterface &img, int& id, int sx, int sy, int lookup_range, bool reconnect)
	{
		std::queue<Vec2i> v;
		v.push(Vec2i(sx,sy));
		while (!v.empty())
		{
			Vec2i cur = v.front();
			v.pop(); // remove top

			if (at(cur.x,cur.y).id == 0)
			{
				at(cur.x,cur.y).id = id;
				SegmentPoints[id].push_back(cur);

				for (int dx = -lookup_range; dx <= lookup_range; dx++)
					for (int dy = -lookup_range; dy <= lookup_range; dy++)
					{						
						Vec2i t(cur.x + dx,cur.y + dy);
						if ((dx != 0 || dy != 0) && inRange(t.x, t.y))
						{
							if (at(t.x, t.y).id == 0)
							{					
								if (img.isFilled(t.x, t.y))
								{
									/*
									// performance waste
									if (ConnectMode && (abs(dx) >= lookup_range || abs(dy) >= lookup_range) )
									{
										if (SegmentPoints[id].size() < 120)
										{
											Points2i shortestPath = getShortestPath(img, cur, t);
											for (size_t u = 0; u < shortestPath.size(); u++)
											{
												v.push(shortestPath[u]);
											}
										}
									}*/	

									if (reconnect && (abs(dx) > 1 || abs(dy) > 1) )
									{
										v.push(Vec2i(cur.x + dx/2,cur.y + dy/2));
									}
									v.push(t);
								}
							}
							else if (at(t.x, t.y).id != id)
							{
								int merge_id = at(t.x, t.y).id;
								for (size_t u = 0; u < SegmentPoints[id].size(); u++)
								{
									Vec2i p = SegmentPoints[id][u];
									at(p.x, p.y).id = merge_id;
									SegmentPoints[merge_id].push_back(p);
								}
								SegmentPoints.erase(SegmentPoints.find(id));
								id = merge_id;
							}
						}
					}
			}
		} // while
	}

	bool WeakSegmentator::get2centers(const std::vector<int>& data, double &c1, double& c2) // c1 < c2
	{
		double mean = 0.0, count = 0.0;
		for (size_t u = 0; u < data.size(); u++)
		{
			mean += u * data[u];
			count += data[u];
		}			
			
		if (count < 1)
			return false;

		mean /= count;
		c1 = 0.0;
		c2 = 0.0;
		double count1 = 0.0;
		double count2 = 0.0;

		for (size_t u = 0; u < data.size(); u++)
		{
			if (u < mean)
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
