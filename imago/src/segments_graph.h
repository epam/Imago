/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#pragma once
#ifndef _euclidean_graph_h
#define _euclidean_graph_h

#include "comdef.h"
#include "vec2d.h"
#include "segment.h"

#include "beast.h"

namespace imago
{
   namespace segments_graph
   {
      struct VertexData {
         size_t index;
         Segment* segment;
         Vec2d position;
      };

      struct EdgeData {
         double weight;
      };

      class SegmentsGraph : public beast::Graph<VertexData, EdgeData>
      {
      public:
         SegmentsGraph() {}
         Segment* getVertexSegment(vertex_descriptor v) { return _vertex_indices[v.id]->data.segment; }
         Vec2d getVertexPosition(vertex_descriptor v) { return _vertex_indices[v.id]->data.position; }
         size_t getVertexIndex(vertex_descriptor v) const { return _vertex_indices[v.id]->data.index; }
         void setVertexSegment(vertex_descriptor v, Segment* val) { _vertex_indices[v.id]->data.segment = val; }
         void setVertexPosition(vertex_descriptor v, Vec2d val) { _vertex_indices[v.id]->data.position = val; }
         void setVertexIndex(vertex_descriptor v, size_t val) { _vertex_indices[v.id]->data.index = val; }
         void setWeight(edge_descriptor e, double val) { _edge_indices[e.id]->data.weight = val; }
      private:
      };

      void add_segment( Segment *seg, SegmentsGraph &g );

      template <typename InputIterator>
      inline void add_segment_range( InputIterator begin, InputIterator end,
                                                          SegmentsGraph &g )
      {
         for(auto iter = begin; iter != end; ++iter)
         {
            add_segment( *iter, g);
         }
      }
   }
}

#endif /* _segments_graph_h_ */
