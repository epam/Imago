#pragma once
#include "../Image/Triangle.h"
#include "Line.h"
#include "Contour.h"
#include "ImageMap.h"

namespace gga
{
    class TriangleRecognition
    {
        bool Good;
        bool Filled;
        double Deviation;
        Triangle Result;
      
    public:
        TriangleRecognition(const Polyline& line, const ImageMap& img_map);
        
        bool isGood() const { return Good; }
        bool isFilled() const { return Filled; }
        const Triangle& getTriangle() const { return Result; }
    };
}

