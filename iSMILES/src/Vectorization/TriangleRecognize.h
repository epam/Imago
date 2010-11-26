#pragma once
#include "../Image/Triangle.h"
#include "Line.h"
#include "Contour.h"
#include "ImageMap.h"

namespace gga
{
    class TriangleRecognize
    {
        bool Good;
        bool Filled;
        double Deviation;
        Triangle Result;
      
    public:
        TriangleRecognize(const Polyline& line, const ImageMap& img_map);
        
        bool isGood() const { return Good; }
        bool isFilled() const { return Filled; }
        const Triangle& getTriangle() const { return Result; }
    };
}

