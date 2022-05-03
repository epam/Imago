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

#include <deque>

#include "graph_extractor.h"
#include "graphics_detector.h"
#include "image_draw_utils.h"
#include "image_utils.h"
#include "log_ext.h"
#include "segment.h"
#include "skeleton.h"

using namespace imago;

void GraphExtractor::extract(Settings& vars, const GraphicsDetector& gd, const SegmentDeque& segments, Skeleton& graph)
{
    logEnterFunction();

    Image tmp;
    int w = 0, h = 0;

    // recreate image from segments
    for (Segment* s : segments)
    {
        if (s->getX() + s->getWidth() >= w)
            w = s->getX() + s->getWidth();
        if (s->getY() + s->getHeight() >= h)
            h = s->getY() + s->getHeight();
    }

    tmp.init(w + 10, h + 10);
    tmp.fillWhite();

    for (Segment* s : segments)
    {
        ImageUtils::putSegment(tmp, *s, true);
    }

    getLogExt().appendImage("Working image", tmp);

    extract(vars, gd, tmp, graph);
}

void GraphExtractor::extract(Settings& vars, const GraphicsDetector& gd, const Image& img, Skeleton& graph)
{
    logEnterFunction();

    double avg_size = 0;
    Points2d lsegments;

    gd.detect(vars, img, lsegments);

    if (!lsegments.empty())
    {
        for (size_t i = 0; i < lsegments.size() / 2; i++)
        {
            Vec2d& p1 = lsegments[2 * i];
            Vec2d& p2 = lsegments[2 * i + 1];

            double dist = Vec2d::distance(p1, p2);

            if (dist > 2.0)
                avg_size += dist;
        }

        avg_size /= (lsegments.size() / 2.0);

        graph.setInitialAvgBondLength(vars, avg_size);

        getLogExt().appendSkeleton(vars, "Graph before", (Skeleton::SkeletonGraph)graph);

        for (size_t i = 0; i < lsegments.size() / 2; i++)
        {
            Vec2d& p1 = lsegments[2 * i];
            Vec2d& p2 = lsegments[2 * i + 1];

            double dist = Vec2d::distance(p1, p2);

            if (dist > vars.graph.MinimalDistTresh)
                graph.addBond(p1, p2);
        }

        getLogExt().appendSkeleton(vars, "Source skeleton", (Skeleton::SkeletonGraph)graph);

        graph.modifyGraph(vars);

        getLogExt().appendSkeleton(vars, "Modified skeleton", (Skeleton::SkeletonGraph)graph);
    }
}
