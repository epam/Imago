#include "recognition_tree.h"
#include "thin_filter2.h"
#include "log_ext.h"
#include "algebra.h"
#include "prefilter.h"
#include "adaptive_filter.h"

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

		//getLogExt().appendSegment("Treat segment", out);

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

	class BitmaskTreat : public ImageTreatmentAdapter
	{
	public:
		BitmaskTreat(const Image& mask) : bitmask(mask) { }

		virtual byte treat(const Image& img, int x, int y) const
		{
			return (bitmask.getByte(x, y) != 255) ? img.getByte(x, y) : 255;
		}
		virtual bool ink(const Image& img, int x, int y) const
		{
			return bitmask.getByte(x, y) != 255 && img.getByte(x, y) != 255;
		}
	private:
		const Image& bitmask;
	};

	void RecognitionTree::segmentate()
	{
		logEnterFunction();
		
		bitmask.copy(raw);
		if (isAlreadyBinarized(bitmask))
			return;

		PrefilterParams p;
		p.logSteps = false;
		p.strongThresh = true;
		prefilterKernel(raw, bitmask, p);

		getLogExt().appendImage("raw", raw);		
		getLogExt().appendImage("binarized", bitmask);

		double inkPercentage = 0.0;
		// update ink percentage
		for (int x = 0; x < bitmask.getWidth(); x++)
			for (int y = 0; y < bitmask.getHeight(); y++)
				if (bitmask.getByte(x, y) == 0)
					inkPercentage += 1.0;
		inkPercentage /= bitmask.getWidth() * bitmask.getHeight() * 2;
		inkPercentage *= 1.1;
		
		// update line thickness
		lineThickness = estimateLineThickness(bitmask);

		if (lineThickness <= 1.0) lineThickness = 1.0;
		if (lineThickness >= 10.0) lineThickness = 10.0;
		if (inkPercentage > 0.15) inkPercentage = 0.15;
		if (inkPercentage < 0.001) inkPercentage = 0.001;

		getLogExt().append("Line thickness", lineThickness);
		getLogExt().append("Ink percentage", inkPercentage);

		Image bitmask2;
		bitmask2.copy(raw);
		AdaptiveFilter af(bitmask2.getWidth(), bitmask2.getHeight());
		af.filterImage(bitmask2, false, inkPercentage, lineThickness);
		getLogExt().appendImage("filtered", bitmask2);

		for (int x = 0; x < bitmask.getWidth(); x++)
			for (int y = 0; y < bitmask.getHeight(); y++)
				if (bitmask2.getByte(x, y) == 0)
					bitmask.getByte(x, y) = 0;

		getLogExt().appendImage("merged", bitmask);
		
		/*int factor = lineThickness / 2.0;
		if (factor >= 1)
		{
			Image resampled2(raw.getWidth() / factor, raw.getHeight() / factor),
				  resampled1(resampled2.getWidth(), resampled2.getHeight());
			resampled1.fillWhite();
			for (int x = 0; x < resampled2.getWidth(); x++)
				for (int y = 0; y < resampled2.getHeight(); y++)
				{
					int i = 0, c = 0;
					for (int dx = 0; dx < factor && x*factor+dx < raw.getWidth(); dx++)
						for (int dy = 0; dy < factor && y*factor+dy < raw.getHeight(); dy++)
						{
							i += raw.getByte(x*factor+dx, y*factor+dy);
							c++;
							if (bitmask.getByte(x*factor+dx, y*factor+dy) == 0)
								resampled1.getByte(x,y) = 0;
						}
					resampled2.getByte(x, y) = i / c;
				}
		
			getLogExt().appendImage("resampled2", resampled2);

			AdaptiveFilter af(resampled2.getWidth(), resampled2.getHeight());
			af.filterImage(resampled2, false);

			Image bitmask2(bitmask.getWidth(), bitmask.getHeight());
			bitmask2.fillWhite();
			for (int x = 1; x < resampled2.getWidth() - 1; x++)
				for (int y = 1; y < resampled2.getHeight() - 1; y++)
				{
						for (int dx = 0; dx < factor; dx++)
							for (int dy = 0; dy < factor; dy++)
								bitmask2.getByte(x*factor+dx, y*factor+dy) = resampled2.getByte(x, y);
				}

			getLogExt().appendImage("bitmask2", bitmask2);

			BitmaskTreat bt(bitmask);
		
			Segment thin;
			Points2i epts;
			root.asSegment(bt, thin, RasterObject::sqThinned);
			root.getPoints(bt, epts, RasterObject::pqEnds);

			for (size_t v = 0; v < epts.size(); v++)
			{			
				Points2i p;
				Vec2i current = epts[v], old = current;
				for (int i = 0; i < 2*lineThickness; i++)
				{
					Points2i temp;
					RasterObject::getNeighbors(DefaultImageTreat(), temp, thin, current);
					for (size_t u = 0; u < temp.size(); u++)
					{
						if (! (temp[u] == current || temp[u] == old) )
						{
							current = temp[u];
							p.push_back(current);
						}
					}
				}
			
				double average_dx = 0.0, average_dy = 0.0;
				for (size_t u = 0; u < p.size(); u++)
				{
					double kx = epts[v].x - p[u].x;
					double ky = epts[v].y - p[u].y;
					double norm = sqrt(kx*kx + ky*ky);
					if (norm < 1.0) continue;
					average_dx += (kx / norm) / p.size();
					average_dy += (ky / norm) / p.size();
				}
				if (fabs(average_dx) > 0.1 || fabs(average_dy) > 0.1)
				{
					double norm = sqrt(average_dx*average_dx + average_dy*average_dy);
					average_dx /= norm;
					average_dy /= norm;
					double px = epts[v].x, py = epts[v].y;
					for (int i = 0; i < 20; i++)
					{
						px += average_dx;
						py += average_dy;
						if (bitmask2.getByte(px, py) == 0)
						{
							for (int dx = -factor; dx <= factor; dx++)
								for (int dy = -factor; dy <= factor; dy++)
									if (sqrt((double)(dx*dx+dy*dy)) < lineThickness / 3.0)
										bitmask.getByte(px+dx, py+dy) = 0;
						}
						else
							break;
					}
				}				
			}

			getLogExt().appendImage("Bitmask updated", bitmask);
		}*/
	}
}