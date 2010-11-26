#include "SegmentParams.h"
#include "../Parameters.h"
#include "../Histogram.h"
#include <math.h>
#ifdef DEBUG
#include <stdio.h> // printf "log"
#endif

namespace gga
{
    int SegmentParams::getAngle(const Line& line)
    {
        double Y = line.getEnd().Y - line.getBegin().Y;
        double X = line.getEnd().X - line.getBegin().X;

        double result = 0.0;
        if (fabs(Y) < 0.0001)
            result = (X > 0.0) ? 90.0 : -90.0;
        else
            result = atan(X/Y) / (2*M_PI) * 360.0;
                
        #ifdef DEBUG
            printf("Angle for (%i,%i)-(%i,%i) is %f\n",
                line.getBegin().X, line.getBegin().Y, line.getEnd().X, line.getEnd().Y, result);
        #endif        
        
        return result;
    }
    
    SegmentParams::SegmentParams(const Polylines& src)
    : AverageLineLength(0), Rotation(0)
    {   
        // step 1. calc average length
        double sumLength = 0.0;
        size_t count = 0;
                
        for (Polylines::const_iterator it = src.begin(); it != src.end(); it++)
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
        
        // step 2. calc rotation angle        
        for (size_t maxAngleDelta = 5; maxAngleDelta < 45; maxAngleDelta+=5)
        {
            #ifdef DEBUG
                if (maxAngleDelta > 5)
                    printf("---> Increased maxAngleDelta to %i*\n", maxAngleDelta);
            #endif            
            
            double verticalAngle = 0.0, horizontalAngle = 0.0;
            size_t verticalCount = 0, horizontalCount = 0;
            
            for (Polylines::const_iterator it = src.begin(); it != src.end(); it++)
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
}