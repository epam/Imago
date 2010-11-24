#pragma once
#include "../src/Image/Image.h"
#include "../src/Vectorization/Vectorize.h"

namespace gga
{
    namespace Draw
    {
        Image PointsToImage(const Points& src);
        Image RangeArrayToImage(const RangeArray& src);
        Image LineToImage(const Polyline& src);
        Image LineAprxToImage(const LinearApproximation& src);
        Image TriangleToImage(const Triangle& src);
    }
}

