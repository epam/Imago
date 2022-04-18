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

#include "character_recognizer.h"
#include "image.h"
#include "settings.h"
#include "stl_fwd.h"

namespace imago
{
    class Molecule;
    class Segment;
    class CharacterRecognizer;

    class ChemicalStructureRecognizer
    {
    public:
        ChemicalStructureRecognizer();

        void setImage(Image& img);
        void recognize(Settings& vars, Molecule& mol);
        void image2mol(Settings& vars, Image& img, Molecule& mol);
        void extractCharacters(Settings& vars, Image& img);
        const CharacterRecognizer& getCharacterRecognizer()
        {
            return _cr;
        };

        ~ChemicalStructureRecognizer();

    private:
        CharacterRecognizer _cr;
        Image _origImage;

        bool removeMoleculeCaptions(const Settings& vars, Image& img, SegmentDeque& layer_symbols, SegmentDeque& layer_graphics);
        void segmentate(const Settings& vars, Image& img, SegmentDeque& segments, bool connect_mode = false);
        void storeSegments(const Settings& vars, SegmentDeque& layer_symbols, SegmentDeque& layer_graphics);
        bool isReconnectSegmentsRequired(const Settings& vars, const Image& img, const SegmentDeque& segments);

        ChemicalStructureRecognizer(const ChemicalStructureRecognizer& csr);
    };
}
