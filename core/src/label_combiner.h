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

#include <deque>

#include "rectangle.h"
#include "segment.h"
#include "settings.h"
#include "stl_fwd.h"
#include "superatom.h"

namespace imago
{
    class Segment;
    class Font;
    class CharacterRecognizer;

    struct Label
    {
        std::vector<Segment*> symbols;
        Rectangle rect;
        int baseline_y;
        bool multiline;

        Superatom satom;

        Label()
        {
            baseline_y = 0;
            multiline = false;
        }

        int MaxSymbolWidth() const
        {
            int result = 0;
            std::vector<Segment*>::const_iterator it;
            for (it = symbols.begin(); it != symbols.end(); ++it)
                if ((*it)->getWidth() > result)
                    result = (*it)->getWidth();
            return result;
        }
    };

    class LabelCombiner
    {
    public:
        LabelCombiner(Settings& vars, SegmentDeque& symbols_layer, SegmentDeque& other_layer, const CharacterRecognizer& cr);
        ~LabelCombiner();

        void extractLabels(std::deque<Label>& labels);

        static void fillLabelInfo(const Settings& vars, Label& l, const CharacterRecognizer& cr);

        static bool segmentsComparator(const Segment* const& a, const Segment* const& b);

        static bool segmentsCompareX(const Segment* const& a, const Segment* const& b);

    private:
        SegmentDeque& _symbols_layer;
        SegmentDeque& _graphic_layer;
        const CharacterRecognizer& _cr;

        double _capHeightStandardDeviation;

        std::deque<Label> _labels;
        void _locateLabels(const Settings& vars);
    };
}
