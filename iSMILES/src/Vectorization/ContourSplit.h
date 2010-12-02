#pragma once
#include "ImageMap.h"
#include "Bounds.h"
#include "Contour.h"
#include "../Image/Image.h"

namespace gga
{    
    class ContourSplit
    {
    public:
        typedef std::vector<Points> Contours;
        typedef std::vector<size_t> Indexes;
    
    private:
        Contours Result;
        Bounds ContourBounds;

    public:
        ContourSplit(const Contour& contour);
        
        const Contours& getSplit() const { return Result; }        
        
    private:
        Indexes reduceIndexCount(const Indexes& indexes, const Contour& contour);
        Indexes intersectIndexes(const Indexes& idx_90, const Contour& rotated, const Indexes& idx_0, const Contour& contour);
        void createResultSplit(const Indexes& indexes, const Contour& contour);
    };
}

