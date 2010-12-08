#pragma once
#include "../Image/Point.h"

namespace gga
{
    class Line : public Points
    {
    public:
        Line() { }        
        Line(const Point& begin, const Point& end);                

        const Point& getBegin() const { return at(0); }
        const Point& getEnd()   const { return at(size()-1); }
        
        double getLength() const;
        int getAngle() const;
    };
    
    class Polyline : public Line
    {
    public:
        Polyline() : Line() { }
        Polyline(const Line& src) : Line(src) { }
    };
    
    typedef std::vector<Polyline> Polylines;
}
