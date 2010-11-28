#pragma once
#include "../Image/Point.h"

namespace gga
{
    struct Range
    {
        Coord L, R;
        inline Coord mid() const { return (L+R)/2; }
    };
    
    typedef std::vector<Range> RangeArrayBase;
    
    class RangeArray : public RangeArrayBase
    {       
    private:
        Coord Left, Top;
        bool InvertedAxis;
                
    public:
        RangeArray(const RangeArray& src, int from, int to = -1);
        RangeArray(const Points& src);
        
        Point coordToPoint(Coord x, Coord y) const;
        Points toPoints() const;
    };
}
