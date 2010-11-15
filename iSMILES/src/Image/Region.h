#pragma once
#include <vector>
#include "Point.h"

namespace gga
{
	struct Region : public Points
    {
        inline Region(size_t allocate=127) { reserve(allocate); }
        inline bool isInside(const Point& p)
        {
            return false;
        }
    };
}

