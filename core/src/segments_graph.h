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

#include "comdef.h"
#include "segment.h"
#include "vec2d.h"
#include "beast.h"

namespace imago
{
    namespace segments_graph
    {
        struct VertexData
        {
            size_t index;
            Segment* segment;
            Vec2d position;
        };

        struct EdgeData
        {
            double weight;
        };

        class SegmentsGraph : public beast::Graph<VertexData, EdgeData>
        {
        public:
            SegmentsGraph()
            {
            }
            Segment* getVertexSegment(vertex_descriptor v) const
            {
                return _vertex_indices[v.id]->data.segment;
            }
            const Vec2d& getVertexPosition(vertex_descriptor v) const
            {
                return _vertex_indices[v.id]->data.position;
            }
            size_t getVertexIndex(vertex_descriptor v) const
            {
                return _vertex_indices[v.id]->data.index;
            }
            void setVertexSegment(vertex_descriptor v, Segment* val)
            {
                _vertex_indices[v.id]->data.segment = val;
            }
            void setVertexPosition(vertex_descriptor v, const Vec2d& val)
            {
                _vertex_indices[v.id]->data.position = val;
            }
            void setVertexIndex(vertex_descriptor v, size_t val)
            {
                _vertex_indices[v.id]->data.index = val;
            }
            void setWeight(edge_descriptor e, double val)
            {
                _edge_indices[e.id]->data.weight = val;
            }

        private:
        };

        void add_segment(Segment* seg, SegmentsGraph& g);

        template <typename InputIterator>
        inline void add_segment_range(InputIterator begin, InputIterator end, SegmentsGraph& g)
        {
            for (auto iter = begin; iter != end; ++iter)
            {
                add_segment(*iter, g);
            }
        }
    }
}
