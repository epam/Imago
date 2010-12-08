#pragma once
#include "../Image/Point.h"

namespace gga
{
    class Line : public Points
    {
    public:
        Line();
        Line(const Point& begin, const Point& end);

        const Point& getBegin() const { return at(0); }
        const Point& getEnd()   const { return at(size()-1); }
        
        double getLength() const;
        double getAngle() const; // -180..180

        double getDistance(const Point& to) const;
        double getDistance(const Line& to) const;

        // DEBUG USE:
        int BaseContourId;
        std::string SplitId;
        std::string getId() const; // BaseContourId.SplitId
    };
    
    class Polyline : public Line
    {
    public:
        Polyline() : Line() { }
        Polyline(const Line& src) : Line(src) { }
    };
    
    typedef std::vector<Polyline> Polylines;
}
