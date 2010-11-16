#pragma once
#include <vector>
#include <math.h>

namespace gga
{
    typedef unsigned short Coord;

#pragma pack(push, 1)
    struct Point
    {
        Coord X, Y;
    public:        
        inline Point(Coord x = 0, Coord y = 0) : X(x), Y(y)    {}
        inline bool operator == (const Point& second) const { return Y==second.Y && X==second.X;}
        inline bool operator <  (const Point& second) const { return Y<second.Y || Y==second.Y && X<second.X;}
        inline double distance(const Point& second = Point(0,0)) const { return sqrt((double)((Y-second.Y)*(Y-second.Y)+(X-second.X)*(X-second.X))); }
    };
#pragma pack(pop)

    typedef std::vector<Point> Points;
}

