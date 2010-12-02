#pragma once
#include "Point.h"

namespace gga
{
    struct Rectangle
    {
        Point   LeftTop, RightBottom;
    public:     
        inline Rectangle(const Point& lt = Point(0,0), const Point& rb = Point(0,0)) : LeftTop(lt), RightBottom(rb) {}
        inline Rectangle(Coord xlt, Coord ylt, Coord xrb, Coord yrb) : LeftTop(xlt, ylt), RightBottom(xrb, yrb) {}
        inline Coord getWidth ()const  { return RightBottom.X - LeftTop.X;}
        inline Coord getHeight()const  { return RightBottom.Y - LeftTop.Y;}
        inline bool isInside (const Point& xy) const { return !(xy < LeftTop) && (xy == RightBottom || xy < RightBottom);}
    };
}
