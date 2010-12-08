#pragma once
#include "../src/Image/Image.h"
// quick way to include all necessary structures:
#include "../src/Vectorization/Vectorization.h"

namespace gga
{
    namespace Draw
    {
        Image PointsToImage(const Points& src, int border = 0);
        Image RangeArrayToImage(const RangeArray& src);
        Image LineToImage(const Polyline& src);
        void  LineToImage(const Polyline& src, Image& image);
        Image LineAprxToImage(const LinearApproximation& src);
        Image TriangleToImage(const Triangle& src);
    }
}

