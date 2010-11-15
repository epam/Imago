#include <stdio.h>
#include <algorithm>
#include "Contour.h"

namespace gga
{
	Contour::Contour()
	{
		RotatedAxis = false;
	}
	
	Point Contour::findRightCorner(const Point& leftCorner) const
	{
		Point rightCorner = leftCorner;
		Contour::const_iterator it = std::upper_bound(begin(), end(), leftCorner);
		if (it != end())
		{
			while ((it+1) != end() && (it+1)->Y == leftCorner.Y)
				it++;
			rightCorner = *it;
		}
		return rightCorner;
	}
	
	Point Contour::movePoint(const Point& src, int x, int y)
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
	
	Point Contour::commitPoint(const Point& p, const Image& img, ImageMap& split)
	{
		if (split.getAssignedSegment(p) == NULL && img.isFilled(p))
		{
			split.assignSegment(p, this);
			push_back(p);
		}
		return p;
	}

	void Contour::passDownLeft(const Image& src, ImageMap& split, Point& p)
	{
		while (src.isInside(p))
		{
			commitPoint(p, src, split);

			// (1) step one point down
			p = movePoint(p, 0, 1);

			// (2) select one of neighbors which is filled, prefer left one...
			Point left = movePoint(p, -1, 0);
			if (src.isFilled(left))
			{
				p = commitPoint(left, src, split);
				// ...and shift left as many as possible
				while (src.isInside(p))
				{
					Point left = movePoint(p, -1, 0);
					if (!src.isFilled(left))
						break; // no more left neighbors
				
					p = commitPoint(left, src, split);
				
					Point up = movePoint(p, 0, -1);
					if (src.isFilled(up))
						return; // crossed inside area
				}	
			}
			else
			{
				// selection still unfilled...
				while (src.isInside(p) && src.getPixel(p).isBackground())
				{
					// ...shift right by connected points and test again
					Point right = movePoint(p, 1,0);
					Point rightUp = movePoint(right, 0,-1);
					if (!src.isFilled(rightUp))
						return; // no more bottom right neighbors
					commitPoint(rightUp, src, split);
					p = commitPoint(right, src, split);
				}
			}
		}
	}
	
	void Contour::buildFromImagePart(const Image& src, ImageMap& split, const Point& start)
	{
		Point p = start;
		for (int iter = 0; ; iter++)
		{
			size_t count = size();
			passDownLeft(src, split, p);
			if (size() > count)
			{
				// printf("[%i] Point (%i,%i), inverse: %i; added: %i\n",  iter++, p.X, p.Y, InvertedAxis, size() - count);
			}
			else
			{
				break;
			}
			RotatedAxis = !RotatedAxis;
		}
		
		std::sort(begin(), end());
	}		
}

