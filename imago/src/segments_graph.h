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
#if 0
      typedef boost::property<boost::vertex_pos_t, Vec2d, 
         boost::property<boost::vertex_seg_ptr_t, Segment*> > 
         SegmentsGraphVertexProperties;

      typedef boost::adjacency_list<boost::vecS, boost::vecS,
         boost::undirectedS, SegmentsGraphVertexProperties, 
         boost::property<boost::edge_weight_t, double> > SegmentsGraph;

      typedef boost::property_map<SegmentsGraph, boost::vertex_pos_t>
         VertexPosMap;
      typedef boost::property_map<SegmentsGraph, boost::vertex_seg_ptr_t>
         VertexSegMap;

      typedef boost::graph_traits<SegmentsGraph>::vertex_descriptor Vertex;

      Vertex add_segment( Segment *seg, SegmentsGraph &g );

      template <typename InputIterator>
      inline void add_segment_range( InputIterator begin, InputIterator end,
                                                          SegmentsGraph &g )
      {
         std::for_each(begin, end, std::bind(&add_segment, std::placeholders::_1, boost::ref(g)));
      }
#else
      typedef boost::property<boost::vertex_pos_t, Vec2d,
            boost::property<boost::vertex_seg_ptr_t, Segment*, boost::property<boost::vertex_index_t, size_t>> >
            SegmentsGraphVertexProperties;
      typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, SegmentsGraphVertexProperties, boost::property<boost::edge_weight_t, double>> boost_adjacency_list_type;

      class SegmentsGraph : public beast::Graph<boost_adjacency_list_type>
      {
      public:
         SegmentsGraph():
            img_ptrs(boost::get(boost::vertex_seg_ptr, _boost_adjacency_list_implementation)),
            positions(boost::get(boost::vertex_pos, _boost_adjacency_list_implementation)),
            indices(boost::get(boost::vertex_index, _boost_adjacency_list_implementation)),
            weights(boost::get(boost::edge_weight, _boost_adjacency_list_implementation))
         {}
         Segment* getVertexSegmentByInd(size_t ind) { return boost::get(img_ptrs, boost::vertex(ind, _boost_adjacency_list_implementation)); }
         Segment* getVertexSegment(vertex_descriptor v) { return boost::get(img_ptrs, v); }
         Vec2d getVertexPosition(vertex_descriptor v) { return boost::get(positions, v); }
         size_t getVertexIndex(vertex_descriptor v) const { return boost::get(indices, v); }
         void setVertexSegment(vertex_descriptor v, Segment* val) { boost::get(img_ptrs, v) = val; }
         void setVertexPosition(vertex_descriptor v, Vec2d val) { boost::get(positions, v) = val; }
         void setWeight(edge_descriptor e, double val) { boost::get(weights, e) = val; }
      private:
         boost::property_map<boost_adjacency_list_type, boost::vertex_seg_ptr_t>::type img_ptrs;
         boost::property_map<boost_adjacency_list_type, boost::vertex_pos_t>::type positions;
         boost::property_map<boost_adjacency_list_type, boost::vertex_index_t>::type indices;
         boost::property_map<boost_adjacency_list_type, boost::edge_weight_t>::type weights;
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
#endif
   }
}


#endif /* _segments_graph_h_ */