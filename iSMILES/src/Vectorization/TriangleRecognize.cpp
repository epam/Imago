#include "TriangleRecognize.h"
#include "../Logger.h"
#include "../Parameters.h"
#include "Bounds.h"
#include "Contour.h"

namespace gga
{
    TriangleRecognize::TriangleRecognize(const Polyline& line, const ImageMap& imgMap)
    : Good(false)
    {
        // check polyline can be triangle
        if (line.size() == 4 && line[0].distance(line[3]) < getGlobalParams().getMaxTriangleBreakDistance())
        {
            Result = Triangle(line[0], line[1], line[2]);
            
            // check is not degenerated
            if (Result.getSideLength(0) < Result.getSideLength(1) + Result.getSideLength(2) &&
                Result.getSideLength(1) < Result.getSideLength(2) + Result.getSideLength(0) &&
                Result.getSideLength(2) < Result.getSideLength(0) + Result.getSideLength(1))
                {            
                    for (size_t p = 0; p < 3; p++)
                    {
                        size_t v0 = p % 3;
                        size_t v1 = (p + 1) % 3;
                        size_t v2 = (p + 2) % 3;
                        
                        // check it is sharp enough
                        double r = getGlobalParams().getTriangleSideRatio();
                        if ( r * Result.getSideLength(v0) < Result.getSideLength(v1) &&
                             r * Result.getSideLength(v0) < Result.getSideLength(v2) &&
                             r * fabs(Result.getSideLength(v1) - Result.getSideLength(v2)) < Result.getSideLength(v0) )
                        {
                            Good = true;
                            break;
                        }                
                    }
                }
        }
        if (Good)
        {   
            // Check Filled or not
            size_t count = 0;
            Bounds bounds(line);
            Point p;            
            for (p.Y = bounds.getTop(); p.Y < bounds.getBottom(); p.Y++)
            {
                for (p.X = bounds.getLeft(); p.X < bounds.getRight(); p.X++)
                {
                    if (imgMap.isAssigned(p) && Result.isInside(p))
                    {
                        const Contour* contour = dynamic_cast<const Contour*>(imgMap.getAssignedSegment(p));
                        if (contour != NULL)
                        {
                            count += contour->size();
                            // ...and skip this object
                            Bounds bc(*contour);
                            p.Y = bc.getBottom();
                        }
                        else
                        {
                            count++;
                        }
                    }
                }                
            }
            int avgLen = (Result.getSideLength(0) + Result.getSideLength(1) + Result.getSideLength(2)) / 3;
            Result.Filled = count > avgLen;
            LOG << "Figure recognized as " << (Result.Filled ? "filled" : "blank") << " triangle";
        }
    }
};