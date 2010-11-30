#include "SegmentParams.h"
#include "../Parameters.h"
#include "../Histogram.h"
#include <math.h>
#ifdef DEBUG
#include <stdio.h> // printf "log"
#endif

// NO MAGIC CONSTANTS/PARAMETERS HERE

namespace gga
{
    int SegmentParams::getAngle(const Line& line)
    {
        int Y = line.getEnd().Y - line.getBegin().Y;
        int X = line.getEnd().X - line.getBegin().X;

        int result = 0;
        if (Y == 0)
            result = (X > 0) ? 90 : -90;
        else
            result = atan((double)X / (double)Y) / (2*3.14159) * 360.0;

        return result;
    }
    
    void SegmentParams::calcLength(const Polylines& Source)
    {
        double sumLength = 0.0;
        size_t count = 0;
                
        for (Polylines::const_iterator it = Source.begin(); it != Source.end(); it++)
        {
            for (size_t p = 1; p < it->size(); p++)
            {
                Line line = Line(it->at(p-1), it->at(p));
                double length = line.getBegin().distance(line.getEnd());
                sumLength += length;
                count++;
            }
        }
        if (count > 0)
        {            
            AverageLineLength = sumLength / count;            
        }        
    }
    
    void SegmentParams::calcAngle(const Polylines& Source)
    {
        for (size_t maxAngleDelta = 5; maxAngleDelta < 45; maxAngleDelta+=5)
        {
            #ifdef DEBUG
                if (maxAngleDelta > 5)
                    printf("---> Increased maxAngleDelta to %i*\n", maxAngleDelta);
            #endif            
            
            double verticalAngle = 0.0, horizontalAngle = 0.0;
            size_t verticalCount = 0, horizontalCount = 0;
            
            for (Polylines::const_iterator it = Source.begin(); it != Source.end(); it++)
            {
                for (size_t p = 1; p < it->size(); p++)
                {
                    Line line = Line(it->at(p-1), it->at(p));
                    int angle = (getAngle(line) + 180) % 180; // 0..179
                    if (angle < maxAngleDelta || angle > 180 - maxAngleDelta)
                    {
                        horizontalAngle += (angle < 90) ? angle : (angle - 180);
                        horizontalCount++;
                    }
                    else if (angle > 90 - maxAngleDelta && angle < 90 + maxAngleDelta)
                    {
                        verticalAngle += (angle - 90);
                        verticalCount++;
                    }
                }
            }
            
            if (verticalCount > 0 || horizontalCount > 0)
            {
                if (verticalCount > horizontalCount)
                {
                    Rotation = verticalAngle / verticalCount;
                }
                else
                {
                    Rotation = horizontalAngle / horizontalCount;
                }
                break; // for maxAngleDelta                
            }            
        }        
    }
    
    SegmentParams::SegmentParams(const Polylines& src)
    : AverageLineLength(0), Rotation(0)
    {   
        calcLength(src);
        calcAngle(src);
    }
}