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

#include <map>
#include <string>
#include <vector>

#include "comdef.h"

namespace imago
{
    class RecognitionDistance : public std::map<char, double>
    {
    protected:
        typedef std::pair<char, double> PrVecItem;
        typedef std::vector<PrVecItem> PrVec;

        void fillVector(PrVec& out) const;

        static bool sortCompareFunction(const PrVecItem& i1, const PrVecItem& i2)
        {
            return i1.second < i2.second;
        }

    public:
        /// returns best matched symbol and its distance
        char getBest(double* dist = NULL) const;

        /// returns the difference between two best symbols recognized
        double getQuality() const;

        /// returns best symbol and others differs no more than max_diff
        std::string getRangedBest(double max_diff = 0.5) const;

        /// selects best from both tables
        void mergeTables(const RecognitionDistance& second);

        /// multiply distance for specified sym_set by factor
        void adjust(double factor, const std::string& sym_set);
    };

    typedef std::map<qword, RecognitionDistance> RecognitionDistanceCacheType;
}
