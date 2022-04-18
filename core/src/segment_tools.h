/****************************************************************************
 * Copyright (C) from 2009 to Present EPAM Systems.
 *
 * This file is part of Imago toolkit.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ***************************************************************************/

#pragma once

#include "segment.h"
#include "stl_fwd.h"

namespace imago
{
    namespace SegmentTools
    {
        // return all filled points from segment
        Points2i getAllFilled(const Segment& seg);

        // return count of filled points
        int getFilledCount(const Segment& seg);

        // returns distance between two sets
        enum DistanceType
        {
            dtEuclidian,
            dtDeltaX,
            dtDeltaY
        };
        double getRealDistance(const Segment& seg1, const Segment& seg2, DistanceType type = dtEuclidian);

        // returns real segment height (delta between top and bottom filled pixels)
        int getRealHeight(const Segment& seg);

        // returns percentage of pixels with y > line_y
        double getPercentageUnderLine(const Segment& seg, int line_y);

        // returns all filled pixels in range of [range x range] from pos
        Points2i getInRange(const Image& seg, Vec2i pos, int range);

        // returns all endpoints
        Points2i getEndpoints(const Segment& seg);

        // return nearest pixel of pts from start point
        Vec2i getNearest(const Vec2i& start, const Points2i& pts);
    };
}
