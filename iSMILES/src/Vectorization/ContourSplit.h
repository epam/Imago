#pragma once
#include "ImageMap.h"
#include "Bounds.h"
#include "Contour.h"
#include "../Image/Image.h"

namespace gga
{
    // TODO: give meaningful name
    typedef std::vector<Points> PointsArray;
    
    class ContourSplit
    {
        PointsArray Result;

    public:
        ContourSplit(const Contour& contour);
        
        const PointsArray& getSplit() const { return Result; }        
        
    private:
        
    };
}

