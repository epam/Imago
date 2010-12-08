#include "SegmentParams.h"
#include "../Logger.h"
#include "../Parameters.h"
#include "../Histogram.h"

namespace gga
{
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
            AverageLineLength = (size_t)(sumLength / count);
        }        
    }
    
    void SegmentParams::calcAngle(const Polylines& Source)
    {
        LOG << "---- calcAngle ----";
        
        for (int maxAngleDelta = 5; maxAngleDelta < 45; maxAngleDelta+=5)
        {
            LOG << "SegmentParams::calcAngle increased maxAngleDelta to " << maxAngleDelta;            
            
            double verticalAngle = 0.0, horizontalAngle = 0.0;
            size_t verticalCount = 0, horizontalCount = 0;
            
            for (Polylines::const_iterator it = Source.begin(); it != Source.end(); it++)
            {
                for (size_t p = 1; p < it->size(); p++)
                {
                    Line line(it->at(p-1), it->at(p));
                    int angle = ((int)line.getAngle() + 180) % 180; // 0..179
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
                    Rotation = (int)(verticalAngle / verticalCount);
                }
                else
                {
                    Rotation = (int)(horizontalAngle / horizontalCount);
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