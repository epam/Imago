#pragma once
#include <vector>
#include "../Image/Point.h"

namespace gga
{   
    class ISegment
    {
    public:
        // returns pointer to the outer segment that contains this segment or NULL
        virtual const ISegment* getOuterSegment() const = 0;
    };
    
    class ImageMap
    {
        size_t Width, Height;
        std::vector<const ISegment*> Data;

    public:
        ImageMap(size_t width, size_t height);
        
        // assign segment to specified point on image
        void assignSegment(const Point& p, const ISegment* segment);
        
        // returns pointer to assigned segment for point p, or NULL
        const ISegment* getAssignedSegment(const Point& p) const;
        
        // returns getAssignedSegment != NULL
        bool isAssigned(const Point& p) const;
        
        size_t getWidth() const { return Width; }
        
        size_t getHeight() const { return Height; }
    };
}

