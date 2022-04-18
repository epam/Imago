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

#include "pixel_boundings.h"

#include <climits>

#include "settings.h"

namespace imago
{
    RectShapedBounding::RectShapedBounding(const RectShapedBounding& src)
    {
        bound = src.bound;
    }

    RectShapedBounding::RectShapedBounding(const Points2i& pts)
    {
        int min_x = INT_MAX, min_y = INT_MAX, max_x = 0, max_y = 0;
        for (Points2i::const_iterator it = pts.begin(); it != pts.end(); ++it)
        {
            min_x = std::min(min_x, it->x);
            min_y = std::min(min_y, it->y);
            max_x = std::max(max_x, it->x);
            max_y = std::max(max_y, it->y);
        }
        bound = Rectangle(min_x, min_y, max_x, max_y, 0);
    }
}
