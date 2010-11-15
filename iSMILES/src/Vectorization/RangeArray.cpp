#include "RangeArray.h"
#include "Bounds.h"

namespace gga
{
	RangeArray::RangeArray(const Points& src)
	{
		Bounds b(src);

		Left = b.getLeft();
		Top = b.getTop();		

		size_t w, h;
		if (b.getHeight() >= b.getWidth())
		{
			h = b.getHeight();
			w = b.getWidth();
			InvertedAxis = false;
		}
		else
		{
			h = b.getWidth();
			w = b.getHeight();
			InvertedAxis = true;		
		}
		// now h > w.
		
		resize(h);
		// fill default values:
		for (size_t u = 0; u < size(); u++)
		{
			at(u).L = w;
			at(u).R = 0;
		}
		
		for (Points::const_iterator it = src.begin(); it != src.end(); it++)
		{
			Coord i_w = it->X - Left;
			Coord i_h = it->Y - Top;
			
			if (InvertedAxis)
			{
				Coord t = i_w;
				i_w = i_h;
				i_h = t;
			}
			// now max(i_h) > max(i_w).
			
			if (i_w < at(i_h).L)
				at(i_h).L = i_w;
			if (i_w > at(i_h).R)
				at(i_h).R = i_w;
		}
	}
    
    Point RangeArray::coordToPoint(Coord x, Coord y) const
    {
        if (InvertedAxis)
        {
            Coord t = x; x = y; y = t;
        }
        return Point(x + Left, y + Top);
    }
    
    Points RangeArray::toPoints() const
    {
        Points res;
        for (size_t y = 0; y < size(); y++)
        {        
            res.push_back(coordToPoint(at(y).L, y));
            res.push_back(coordToPoint(at(y).R, y));
        }
        return res;
    }
    
    RangeArray RangeArray::head(size_t splitPoint) const
    {
        Points p = toPoints(), start;
        for (size_t u = 0; u < 2*splitPoint && u < p.size(); u++)
            start.push_back(p[u]);
        return RangeArray(start);
    }
    
    RangeArray RangeArray::tail(size_t splitPoint) const
    {
        Points p = toPoints(), end;
        for (size_t u = 0; u < p.size(); u++)
            if (u >= 2*splitPoint)
                end.push_back(p[u]);
        return RangeArray(end);
    }
}
