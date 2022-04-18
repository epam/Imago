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

/**
 * @file   probability_separator.h
 *
 * @brief  Probabilistic estimate of segments
 */

#pragma once

#include "complex_contour.h"
#include "segment.h"
#include "settings.h"

namespace imago
{
    class ProbabilitySeparator
    {
    public:
        static void CalculateProbabilities(const Settings& vars, Image& seg, double& char_probability, double& bond_probability, double char_apriory = 0.5,
                                           double bond_apriory = 0.5);

    private:
        static int getAngleDirection(ComplexNumber vec);
    };
}
