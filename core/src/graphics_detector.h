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

#include "label_combiner.h"
#include "settings.h"
#include "stl_fwd.h"
#include "vec2d.h"

namespace imago
{
    struct LineSegment
    {
        Vec2d b;
        Vec2d e;
    };

    class Segment;
    class Image;
    class Molecule;
    class BaseApproximator;

    class GraphicsDetector
    {
    public:
        GraphicsDetector();
        GraphicsDetector(const BaseApproximator* approximator, double eps);
        void extractRingsCenters(const Settings& vars, SegmentDeque& segments, Points2d& ring_centers) const;
        void analyzeUnmappedLabels(std::deque<Label>& unmapped_labels, Points2d& ring_centers);
        void detect(const Settings& vars, const Image& img, Points2d& lsegments) const;
        ~GraphicsDetector();

    private:
        const BaseApproximator* _approximator;
        double _approx_eps;
        void _decorner(Image& img) const;
        void _extractPolygon(const Settings& vars, const Segment& seg, Points2d& poly) const;
        int _countBorderBlackPoints(const Image& img) const;
        GraphicsDetector(const GraphicsDetector&);
    };
}
