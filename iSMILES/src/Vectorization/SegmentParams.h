#pragma once
#include "Line.h"

namespace gga
{
    class SegmentParams
    {
        size_t AverageLineLength;
        int Rotation;

    public:
        SegmentParams(const Polylines& src);
        
        /* average line segment length in pixels */
        size_t getAverageLineLength() const { return AverageLineLength; }
        
        /* rotate image to returned degree amount to make vertical/horizontal lines real vertical/horizontal */
        int getRotationAngle() const { return Rotation; }
        
    private:
        void calcLength(const Polylines& Source);
        void calcAngle(const Polylines& Source);
    };
}