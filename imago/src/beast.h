/****************************************************************************
 * Copyright (C) 2015 GGA Software Services LLC
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

#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/connected_components.hpp"


namespace beast
{
   template<class boost_adjacency_list_type>
   class Graph
   {
   protected:
      boost_adjacency_list_type _boost_adjacency_list_implementation;
   public:
      typedef typename boost_adjacency_list_type::vertex_iterator vertex_iterator;
      typedef typename boost_adjacency_list_type::edge_iterator edge_iterator;
      typedef typename boost_adjacency_list_type::adjacency_iterator adjacency_iterator;
      typedef typename boost_adjacency_list_type::out_edge_iterator out_edge_iterator;
      typedef typename boost_adjacency_list_type::vertex_descriptor vertex_descriptor;
      typedef typename boost_adjacency_list_type::edge_descriptor edge_descriptor;

      Graph()
      {
      }

      void clear() { _boost_adjacency_list_implementation.clear(); }

      size_t vertexCount() const { return boost::num_vertices(_boost_adjacency_list_implementation);  }
      vertex_iterator vertexBegin() { return _boost_adjacency_list_implementation.vertex_set().begin(); }
      vertex_iterator vertexEnd() { return _boost_adjacency_list_implementation.vertex_set().end(); }
      vertex_descriptor addVertex() { return boost::add_vertex(_boost_adjacency_list_implementation); }
      void removeVertex(vertex_descriptor desc) { boost::remove_vertex(desc, _boost_adjacency_list_implementation);  }
      void removeVertex(vertex_iterator iter) { boost::remove_vertex(*iter, _boost_adjacency_list_implementation);  }
      void clearVertex(vertex_descriptor desc) { boost::clear_vertex(desc, _boost_adjacency_list_implementation);  }
      void clearVertex(vertex_iterator iter) { boost::clear_vertex(*iter, _boost_adjacency_list_implementation);  }
      size_t getDegree(vertex_descriptor v) const { return boost::degree(v, _boost_adjacency_list_implementation); }

      size_t edgeCount() const { return boost::num_edges(_boost_adjacency_list_implementation);  }
      edge_iterator edgeBegin() { return edge_iterator(_boost_adjacency_list_implementation.m_edges.begin()); }
      edge_iterator edgeEnd() { return edge_iterator(_boost_adjacency_list_implementation.m_edges.end()); }
      std::pair<edge_descriptor, bool> getEdge(vertex_descriptor u, vertex_descriptor v) { return boost::edge(u, v, _boost_adjacency_list_implementation); }
      std::pair<edge_descriptor, bool> addEdge(vertex_descriptor u, vertex_descriptor v) { return boost::add_edge(u, v, _boost_adjacency_list_implementation); }
      void removeEdge(edge_descriptor desc) { boost::remove_edge(desc, _boost_adjacency_list_implementation);  }
      void removeEdge(edge_iterator iter) { boost::remove_edge(*iter, _boost_adjacency_list_implementation);  }
      void removeEdge(vertex_descriptor u, vertex_descriptor v) { boost::remove_edge(u, v, _boost_adjacency_list_implementation);  }

      adjacency_iterator adjacencyBegin(vertex_descriptor v) const { return boost::adjacent_vertices(v, _boost_adjacency_list_implementation).first; }
      adjacency_iterator adjacencyEnd(vertex_descriptor v) const { return boost::adjacent_vertices(v, _boost_adjacency_list_implementation).second; }
      
      out_edge_iterator outEdgeBegin(vertex_descriptor v) const { return boost::out_edges(v, _boost_adjacency_list_implementation).first; }
      out_edge_iterator outEdgeEnd(vertex_descriptor v) const { return boost::out_edges(v, _boost_adjacency_list_implementation).second; }

      size_t connected_components(std::vector<int> &comp)
      {
         size_t cc = boost::connected_components(_boost_adjacency_list_implementation, &comp[0]);
         return cc;
      }
   private:
   };
}