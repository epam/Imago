#pragma once
#include "../Image/Triangle.h"
#include "Line.h"
#include "ImageMap.h"

namespace gga
{
    class TriangleRecognize
    {
        bool Good;
        Triangle Result;
      
    public:
        TriangleRecognize(const Polyline& line, const ImageMap& imgMap);
        
        bool isGood() const { return Good; }
        const Triangle& getTriangle() const { return Result; }
    };
}

