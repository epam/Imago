#pragma once
#include "Line.h"

namespace gga
{
    class SegmentParams
    {
        const Polylines& Source;
        size_t AverageLineLength;
        int Rotation;

    public:
        SegmentParams(const Polylines& src);
        
        static int getAngle(const Line& line); // -180..180
        
        size_t getAverageLineLength() const { return AverageLineLength; }
        
        /* rotate image to returned Grad amount to make vertical/horizontal lines real vertical/horizontal */
        int getRotationAngle() const { return Rotation; }
        
    private:
        void calcLength();
        void calcAngle();
    };
}