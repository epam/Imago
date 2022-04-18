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

#include "settings.h"
#include "stl_fwd.h"
#include "vec2d.h"

namespace imago
{
    class BaseApproximator
    {
    public:
        virtual void apply(const Settings& vars, double eps, const Points2d& input, Points2d& output) const = 0;
        virtual ~BaseApproximator() = default;
    };

    class CvApproximator : public BaseApproximator
    {
    public:
        void apply(const Settings& vars, double eps, const Points2d& input, Points2d& output) const;
    };

    class DPApproximator : public BaseApproximator
    {
        void _apply_int(double eps, const Points2d& input, Points2d& output) const;

    public:
        void apply(const Settings& vars, double eps, const Points2d& input, Points2d& output) const;
    };
}
