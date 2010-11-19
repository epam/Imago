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
        
        Line(const Point& begin, const Point& end)
        {
            push_back(begin);
            push_back(end);
        }
        
        Line() { }
    };
    
    class Polyline : public Line
    {
    public:
        Polyline(const Line& src) : Line(src) { }
        Polyline() : Line() { }
        
        bool insertKnot(const Point& knot)
        {
            // TODO: check that knot doesn't produce self-intersecting line (not used yet)
            insert(end(), knot);
            return true;
        }
    };
}
