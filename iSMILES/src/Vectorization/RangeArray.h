#pragma once
#include "../Image/Point.h"

namespace gga
{
    struct Range
    {
        Coord L, R;
        inline Coord mid() const { return (L+R)/2; }
    };
    
    class RangeArray : public std::vector<Range>
    {       
    private:
        Coord Left, Top;
        bool InvertedAxis;
                
    public:
        RangeArray(const Points& src);
        
        Point coordToPoint(Coord x, Coord y) const;
        Points toPoints() const;
        
        // TODO: those methods have bad performance and ugly implementation
        RangeArray head(size_t splitPoint) const;
        RangeArray tail(size_t splitPoint) const;
    };
}
