#include "TriangleRecognize.h"
#include "../Parameters.h"

// ALL MAGIC CONSTANTS MOVED TO PARAMETERS.H

namespace gga
{
    TriangleRecognize::TriangleRecognize(const Polyline& line, const ImageMap& img_map)
    : Good(false), Filled(false), Deviation(0.0)
    {
        // TODO: check that condition.
        if (line.size() == 4 && line[0].distance(line[3]) < GlobalParams.getMaxTriangleBreakDistance())
        {
            Result = Triangle(line[0], line[1], line[2]);
            if (Result.getSideLength(0) < Result.getSideLength(1) + Result.getSideLength(2) &&
                Result.getSideLength(1) < Result.getSideLength(2) + Result.getSideLength(0) &&
                Result.getSideLength(2) < Result.getSideLength(0) + Result.getSideLength(1))
                {            
                    for (size_t p = 0; p < 3; p++)
                    {
                        size_t v0 = p % 3;
                        size_t v1 = (p + 1) % 3;
                        size_t v2 = (p + 2) % 3;
                        double a = 1.5 * Result.getSideLength(v0) / (Result.getSideLength(v1) + Result.getSideLength(v2));
                        double b = (fabs(Result.getSideLength(v1) - Result.getSideLength(v2))) / (Result.getSideLength(v0) / 1.5);
                        if (a < 1.0 && b < 1.0)
                        {
                            Deviation = a * b;
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