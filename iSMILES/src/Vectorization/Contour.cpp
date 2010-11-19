#include "Contour.h"
#include "Bounds.h"

namespace gga
{
	Contour::Contour(const Image& img, ImageMap& map, const Point& start)
    : SourceImage(img), CurrentImageMap(map), OuterContour(NULL)
	{
        bool doneSomething = true;
        
        // 1. construct contour
        Point p = start;        
		for (int iter = 0; doneSomething; iter++)
		{
			size_t count = size();
			passDownLeft(p, iter % 2 == 1);
            doneSomething = size() > count;
		}
        
        // 2. now fill all map points related to contour
        const Bounds b(*this);
        do
        {
            doneSomething = false;            
            for (p.X = b.getLeft(); p.X <= b.getRight(); p.X++)
            {
                for (p.Y = b.getTop(); p.Y < b.getBottom(); p.Y++)
                {
                    if (CurrentImageMap.getAssignedSegment(p) == this)
                    {
                        for (int dx = 0; dx <= 1; dx++)
                        {
                            for (int dy = -1; dy <= 1; dy++)
                            {
                                Point right = movePoint(p, dx, dy);
                                if (SourceImage.isFilled(right) && !CurrentImageMap.isAssigned(right))
                                {
                                    CurrentImageMap.assignSegment(right, this);
                                    doneSomething = true;
                                }
                            }                            
                        }
                    }
                }
            }
        } while (doneSomething);
        
        // 3. find outer contour
        {            
            const Coord start_y = at(0).Y;
            const Coord start_x = at(0).X;
            for (Coord x1 = start_x; x1 > 0 && OuterContour == NULL; x1--)
            {
                const ISegment* seg1 = CurrentImageMap.getAssignedSegment(Point(x1, start_y));
                if (seg1 != NULL && seg1 != this)
                {
                    for (Coord x2 = start_x + 1; x2 < SourceImage.getWidth(); x2++)
                    {
                        if (seg1 == CurrentImageMap.getAssignedSegment(Point(x2, start_y)))
                        {
                            OuterContour = static_cast<const Contour*>(seg1);
                            break;
                        }
                    }
                }                
            }
        }
	}
	

	Point Contour::movePoint(const Point& src, int x, int y, bool RotatedAxis)
	{
		Point p = src;
		if (RotatedAxis)
		{
			x = -x;
			y = -y;
		}
		p.X += x;
		p.Y += y;
		return p;
	}
	
	Point Contour::commitPoint(const Point& p)
	{
		if (!CurrentImageMap.isAssigned(p) && SourceImage.isFilled(p))
		{
			CurrentImageMap.assignSegment(p, this);
			push_back(p);
		}
		return p;
	}

	void Contour::passDownLeft(Point& p, bool RotatedAxis)
	{
		while (SourceImage.isInside(p))
		{
			commitPoint(p);

			// step one point down
			p = movePoint(p, 0,1, RotatedAxis);

			// select one of neighbors which is filled, prefer left one...
			Point left = movePoint(p, -1,0, RotatedAxis);
			if (SourceImage.isFilled(left))
			{
				p = commitPoint(left);
				// ...and shift left as many as possible
				while (SourceImage.isInside(p))
				{
					Point left = movePoint(p, -1,0, RotatedAxis);
					if (!SourceImage.isFilled(left))
						break; // no more left neighbors
				
					p = commitPoint(left);
				
					Point up = movePoint(p, 0,-1, RotatedAxis);
					if (SourceImage.isFilled(up))
						return; // crossed inside area
				}	
			}
			else
			{
				// selection still unfilled...
				while (SourceImage.isInside(p) && !SourceImage.isFilled(p))
				{
					// ...shift right by connected points and test again
					Point right = movePoint(p, 1,0, RotatedAxis);
					Point rightUp = movePoint(right, 0,-1, RotatedAxis);
					if (!SourceImage.isFilled(rightUp))
						return; // no more bottom right neighbors
					commitPoint(rightUp);
					p = commitPoint(right);
				}
			}
		}
	}
}


