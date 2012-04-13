#include "recognition_tree.h"
#include "thin_filter2.h"
#include "log_ext.h"
#include "algebra.h"

namespace imago
{
	byte DefaultImageTreat::treat(const Image& img, int x, int y) const
	{
		return (img.getByte(x,y) != 255) ? 0 : 255;
	}

	bool DefaultImageTreat::ink(const Image& img, int x, int y) const
	{
		return img.getByte(x,y) != 255;
	}

	AutoconnectionImageTreat::AutoconnectionImageTreat(int range) : _range(1.2*range)
	{
	}

	byte AutoconnectionImageTreat::treat(const Image& img, int x, int y) const
	{
		if (img.getByte(x,y) != 255) return 0;
		
		Points2i pts;
		RasterObject::getNeighbors(*this, pts, img, Vec2i(x, y), 2*_range);
		
		// TODO: too slow!
		for (size_t u = 0; u < pts.size(); u++)
			for (size_t v = 0; v < pts.size(); v++)
				if (pts[u].x < x && pts[v].x > x && // on different sides
					abs(pts[u].y - y) < _range/2 && abs(pts[v].y - y) < _range/2 && // almost same y
					Vec2i::distance(pts[u],pts[v]) < _range && // not too distinct
					Algebra::SegmentsOnSameLine(Vec2d(pts[u].x, pts[u].y), Vec2d(x,y),
					                            Vec2d(pts[v].x, pts[v].y), Vec2d(x,y)))
					{
						return 0;
					}

		return 255;
	}

	bool AutoconnectionImageTreat::ink(const Image& img, int x, int y) const
	{
		return img.getByte(x,y) != 255;
	}

	RasterObject::RasterObject(const Image& img, const CropList& segments) : _img(img), _crops(segments)
	{
		updateBounding();
	}

	RasterObject::RasterObject(const Image& img, Crop crop) : _img(img)
	{
		_crops.push_back(crop);
		updateBounding();
	}

	RasterObject::RasterObject(const Image& img) : _img(img)
	{
		_crops.push_back(Rectangle(0,0,img.getWidth(),img.getHeight()));
		updateBounding();
	}

	void RasterObject::updateBounding()
	{
		int x1 = INT_MAX, y1 = INT_MAX, x2 = 0, y2 = 0;
		for (CropList::const_iterator it = _crops.begin(); it != _crops.end(); it++)
		{
			if (it->x1() < x1) x1 = it->x1();
			if (it->x2() > x2) x2 = it->x2();
			if (it->y1() < y1) y1 = it->y1();
			if (it->y2() > y2) y2 = it->y2();
		}
		_bounding = Crop(x1,y1,x2,y2,0);
	}

	void RasterObject::asSegment(const ImageTreatmentAdapter& a, Segment& out, SegmentQueryType q) const
	{
		out.clear();
		out.init(_bounding.width, _bounding.height);
		out.fillWhite();
		for (CropList::const_iterator it = _crops.begin(); it != _crops.end(); it++)
		{
			for (int y = it->y1(); y < it->y2(); y++)
			{
				for (int x = it->x1(); x < it->x2(); x++)
				{
					byte v = (q == sqSource) ? _img.getByte(x,y) : a.treat(_img, x, y);
					out.getByte(x-_bounding.x, y-_bounding.y) = v;
				}
			}
		}
		getLogExt().appendSegment("Treat segment", out);
		if (q == sqThinned)
		{
			ThinFilter2(out).apply();
		}
		out.getX() = _bounding.x;
		out.getY() = _bounding.y;
	}

	void RasterObject::getNeighbors(const ImageTreatmentAdapter& a, Points2i& result, const Image& seg, Vec2i pos, int range)
	{
		result.clear();
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
					&& a.ink(seg, pos.x + dx, pos.y + dy))
				{
					result.push_back(Vec2i(pos.x + dx, pos.y + dy));
				}
			}
		}				
	}

	void RasterObject::getPoints(const ImageTreatmentAdapter& a, Points2i& p, PointsQuertyType q) const
	{
		logEnterFunction();
		
		p.clear();
		Segment temp;
		asSegment(a, temp, (q == pqEnds || q == pqThinned) ? sqThinned : sqTreatAdapterUse );		

		for (int y = 0; y < temp.getHeight(); y++)
		{
			for (int x = 0; x < temp.getWidth(); x++)
			{
				byte v = temp.getByte(x, y);
				if (a.ink(temp, x, y))
				{
					if (q == pqThinned || q == pqAll)
					{
						p.push_back(Vec2i(x+_bounding.x, y+_bounding.y));
					}
					else if (q == pqEnds)
					{
						Points2i neighb;
						getNeighbors(a, neighb, temp, Vec2i(x,y), 1);
						if (neighb.size() == 1)
							p.push_back(Vec2i(x+_bounding.x, y+_bounding.y));
					}
				}
			}
		}
	}
}