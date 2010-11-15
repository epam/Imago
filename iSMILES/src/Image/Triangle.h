#pragma once
#include "Point.h"

namespace gga
{
	struct Triangle
	{
        Point   Vertex[3];
    public:		
        inline Triangle(const Point& v1 = Point(0,0), const Point& v2 = Point(0,0), const Point& v3 = Point(0,0)) { Vertex[0] = v1; Vertex[1] = v2; Vertex[2] = v3;}
//        inline Coord getWidth ()const  { return RightBottom.X - LeftTop.X;}
//        inline Coord getHeight()const  { return RightBottom.Y - LeftTop.Y;}
//		inline bool isInside (const Point& xy) const { return !(xy < LeftTop) && (xy == RightBottom || xy < RightBottom);}
	};
}
