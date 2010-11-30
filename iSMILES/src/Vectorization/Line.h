#pragma once
#include "../Image/Point.h"

namespace gga
{
    class Line : public Points
    {
    public:
        Point& getBegin() { return at(0); }
        Point& getEnd()   { return at(size()-1); }
        
        const Point& getBegin() const { return at(0); }
        const Point& getEnd()   const { return at(size()-1); }
        
        Line() { }
        Line(const Point& begin, const Point& end)
        {
            push_back(begin);
            push_back(end);
        }
    };
    
    class Polyline : public Line
    {
    public:
        Polyline() : Line() { }
        Polyline(const Line& src) : Line(src) { }
    };
    
    typedef std::vector<Polyline> Polylines;
}
