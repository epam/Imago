#include "TriangleRecognize.h"
#include "../Parameters.h"

namespace gga
{
    TriangleRecognize::TriangleRecognize(const Polyline& line, const ImageMap& img_map)
    : Good(false), Filled(false)
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
                        
                        // check it is sharp enogh
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
            // TODO: check Filled or not
        }
    }
};