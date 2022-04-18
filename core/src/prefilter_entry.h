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

#include "image.h"
#include "settings.h"

namespace imago
{
    // selects first OK prefilter
    bool prefilterEntrypoint(Settings& vars, Image& output, const Image& src);

    // iterates trough next filters
    bool applyNextPrefilter(Settings& vars, Image& output, const Image& src, bool iterateNext = true);

    namespace PrefilterUtils
    {
        // returns true if image was modified
        bool resampleImage(const Settings& vars, Image& image);
    }
}
