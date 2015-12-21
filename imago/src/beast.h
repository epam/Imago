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

#include <list>
#include <vector>
#include<stddef.h>

namespace beast
{
   template<class vertex_data_type, class edge_data_type>
   class Graph
   {
   public:
      typedef struct SVectorDescriptor
      {
         size_t id;
         SVectorDescriptor() : id(-1) {}
         SVectorDescriptor(size_t n) : id(n) {}
         bool operator == (const SVectorDescriptor& other) const { return id == other.id; }
         bool operator != (const SVectorDescriptor& other) const { return !(*this == other); }
         bool operator < (const SVectorDescriptor& other) const { return id < other.id; }
      } vertex_descriptor;
      typedef struct SEdgeDescriptor
      {
         size_t id;
         SVectorDescriptor m_source;
         SVectorDescriptor m_target;
         SEdgeDescriptor() : id(-1), m_source(-1), m_target(-1) {}
         SEdgeDescriptor(size_t id, SVectorDescriptor u, SVectorDescriptor v) : id(id), m_source(u), m_target(v) {}
         bool operator == (const SEdgeDescriptor& other) const { return id == other.id; }
         bool operator < (const SEdgeDescriptor& other) const { return id < other.id; }
      } edge_descriptor;
   protected:

      struct _Vertex
      {
         _Vertex(size_t id) : desc(id) {}
         vertex_descriptor desc;
         std::list<std::pair<size_t, size_t>> neighbors;
         vertex_data_type data;
      };

      struct _Edge
      {
         _Edge(edge_descriptor desc, vertex_descriptor u, vertex_descriptor v) : desc(desc), source(u), target(v) {}
         edge_descriptor desc;
         vertex_descriptor source;
         vertex_descriptor target;
         edge_data_type data;
      };

      std::list<_Vertex> _vertices;
      std::list<_Edge> _edges;
      std::vector<typename std::list<_Vertex>::iterator> _vertex_indices;
      std::vector<typename std::list<_Edge>::iterator> _edge_indices;
   public:

      class vertex_iterator: public std::iterator< std::forward_iterator_tag, vertex_descriptor >
      {
      public:
         vertex_iterator() {}
         vertex_iterator(typename std::list<_Vertex>::iterator &iter) : m_iter(iter) {}
         vertex_iterator(const typename std::list<_Vertex>::iterator &iter) : m_iter(iter) {}
         vertex_iterator(const vertex_iterator &other) : m_iter(other.m_iter) {}
         vertex_iterator& operator = (const vertex_iterator &other) { m_iter = other.m_iter; return *this; }
         bool operator == (const vertex_iterator &other) const { return m_iter == other.m_iter; }
         bool operator != (const vertex_iterator &other) const { return !(*this == other); }
         vertex_descriptor operator * () const { return m_iter->desc; }
         vertex_iterator& operator ++ () { return ++m_iter, *this; }
      private:
         typename std::list<_Vertex>::iterator m_iter;
      };
      friend class vertex_iterator;

      class edge_iterator: public std::iterator< std::forward_iterator_tag, edge_descriptor >
      {
      public:
         edge_iterator() {}
         edge_iterator(typename std::list<_Edge>::iterator &iter) : m_iter(iter) {}
         edge_iterator(const typename std::list<_Edge>::iterator &iter) : m_iter(iter) {}
         edge_iterator(const edge_iterator &other) : m_iter(other.m_iter) {}
         edge_iterator& operator = (const edge_iterator &other) { m_iter = other.m_iter; return *this; }
         bool operator == (const edge_iterator &other) const { return m_iter == other.m_iter; }
         bool operator != (const edge_iterator &other) const { return !(*this == other); }
         edge_descriptor operator * () const { return m_iter->desc; }
         edge_iterator& operator ++ () { return ++m_iter, *this; }
         vertex_descriptor get_source() { return m_iter->source; }
         vertex_descriptor get_target() { return m_iter->target; }
      private:
         typename std::list<_Edge>::iterator m_iter;
      };
      friend class edge_iterator;

      class adjacency_iterator: public std::iterator< std::forward_iterator_tag, vertex_descriptor >
      {
      public:
         adjacency_iterator() {}
         adjacency_iterator(typename std::list<std::pair<size_t, size_t>>::iterator &iter) : m_iter(iter) {}
         adjacency_iterator(const typename std::list<std::pair<size_t, size_t>>::iterator &iter) : m_iter(iter) {}

         bool operator == (const adjacency_iterator &other) const { return m_iter == other.m_iter; }
         bool operator != (const adjacency_iterator &other) const { return !(*this == other); }
         vertex_descriptor operator * () const { return vertex_descriptor(m_iter->first); }
         adjacency_iterator& operator ++ () { return ++m_iter, *this; }
      private:
         typename std::list<std::pair<size_t, size_t>>::iterator m_iter;
      };

      class out_edge_iterator
      {
      public:
         out_edge_iterator() {}
         out_edge_iterator(typename std::list<std::pair<size_t, size_t>>::iterator &iter, const std::vector<typename std::list<_Edge>::iterator> *edge_indices)
            : m_iter(iter), m_edge_indices(edge_indices) {}
         out_edge_iterator(const typename std::list<std::pair<size_t, size_t>>::iterator &iter, const std::vector<typename std::list<_Edge>::iterator> *edge_indices)
            : m_iter(iter), m_edge_indices(edge_indices) {}
         bool operator == (const out_edge_iterator& other) const { return m_iter == other.m_iter; }
         bool operator != (const out_edge_iterator &other) const { return !(*this == other); }
         edge_descriptor operator * () const { return (*m_edge_indices)[m_iter->second]->desc; }
         out_edge_iterator& operator ++ () { return ++m_iter, *this; }
      private:
         typename std::list<std::pair<size_t, size_t>>::iterator m_iter;
         const std::vector<typename std::list<_Edge>::iterator> *m_edge_indices;
      };






      Graph()
      {
      }

      void clear()
      {
         _vertices.clear();
         _edges.clear();
         _vertex_indices.clear();
         _edge_indices.clear();
      }

      size_t vertexCount() const
      {
         return _vertices.size();
      }
      vertex_iterator vertexBegin()
      {
         return vertex_iterator(_vertices.begin());
      }
      vertex_iterator vertexEnd()
      {
         return vertex_iterator(_vertices.end());
      }
      vertex_descriptor addVertex()
      {
         size_t id = _vertex_indices.size();
         auto iter = _vertices.insert(_vertices.end(), _Vertex(id));
         _vertex_indices.push_back(iter);
         return vertex_descriptor(id);
      }
      void removeVertex(vertex_descriptor desc)
      {
         auto u_iter = _vertex_indices[desc.id];
         for (auto u_nei_pair : u_iter->neighbors)
         {
            // remove edges
            auto edge_iter = _edge_indices[u_nei_pair.second];
            auto v_iter = _vertex_indices[u_nei_pair.first];
            for (auto v_nei_iter = v_iter->neighbors.begin(); v_nei_iter != v_iter->neighbors.end(); ++v_nei_iter)
            {
               if (v_nei_iter->second == u_nei_pair.second)
               {
                  v_iter->neighbors.erase(v_nei_iter);
                  break;
               }
            }
            _edge_indices[u_nei_pair.second] = _edges.end();
            _edges.erase(edge_iter);
         }
         _vertex_indices[desc.id] = _vertices.end();
         _vertices.erase(u_iter);
      }
//      void clearVertex(vertex_descriptor desc);
//      void clearVertex(vertex_iterator iter);
      size_t getDegree(vertex_descriptor desc) const
      {
         return _vertex_indices[desc.id]->neighbors.size();
      }

      size_t edgeCount() const
      {
         return _edges.size();
      }
      edge_iterator edgeBegin()
      {
         return edge_iterator(_edges.begin());
      }
      edge_iterator edgeEnd()
      {
         return edge_iterator(_edges.end());
      }
      std::pair<edge_descriptor, bool> getEdge(vertex_descriptor u, vertex_descriptor v)
      {
         for (auto iter : _edges)
         {
            if ((iter.source == u.id && iter.target == v.id) || (iter.source == v.id && iter.target == u.id))
               return std::make_pair(edge_descriptor(iter.desc), true);
         }
         return std::make_pair(edge_descriptor(), false);
      }
      std::pair<edge_descriptor, bool> addEdge(vertex_descriptor u, vertex_descriptor v)
      {
         auto result = getEdge(u, v);
         if (!result.second)
         {
            size_t id = _edge_indices.size();
            auto iter = _edges.insert(_edges.end(), _Edge(edge_descriptor(id, u, v), u, v));
            _edge_indices.push_back(iter);
            _vertex_indices[u.id]->neighbors.push_back(std::make_pair(v.id, id));
            _vertex_indices[v.id]->neighbors.push_back(std::make_pair(u.id, id));
            result.first = _edges.back().desc;//edge_descriptor(id, u, v);
            result.second = true;
         }
         return result;
      }
      void removeEdge(edge_descriptor desc)
      {
         auto iter = _edge_indices[desc.id];
         // remove links in vertices
         for (auto iter = _vertex_indices[desc.m_source.id]->neighbors.begin(),
                   end = _vertex_indices[desc.m_source.id]->neighbors.end(); iter != end; ++iter)
            if (iter->second == desc.id)
            {
               _vertex_indices[desc.m_source.id]->neighbors.erase(iter);
               break;
            }
         for (auto iter = _vertex_indices[desc.m_target.id]->neighbors.begin(),
            end = _vertex_indices[desc.m_target.id]->neighbors.end(); iter != end; ++iter)
            if (iter->second == desc.id)
            {
               _vertex_indices[desc.m_target.id]->neighbors.erase(iter);
               break;
            }
         _edges.erase(iter);
         _edge_indices[desc.id] = _edges.end();
      }
      void removeEdge(edge_iterator iter)
      {
         //if iter != end
         removeEdge(*iter);
      }
      void removeEdge(vertex_descriptor u, vertex_descriptor v)
      {
         auto result = getEdge(u, v);
         if (result.second)
         {
            removeEdge(result.first);
         }
      }

      adjacency_iterator adjacencyBegin(vertex_descriptor v) const
      {
         return adjacency_iterator(_vertex_indices[v.id]->neighbors.begin());
      }
      adjacency_iterator adjacencyEnd(vertex_descriptor v) const
      {
         return adjacency_iterator(_vertex_indices[v.id]->neighbors.end());
      }

      out_edge_iterator outEdgeBegin(vertex_descriptor v) const
      {
         return out_edge_iterator(_vertex_indices[v.id]->neighbors.begin(), &_edge_indices);
      }
      out_edge_iterator outEdgeEnd(vertex_descriptor v) const
      {
         return out_edge_iterator(_vertex_indices[v.id]->neighbors.end(), &_edge_indices);
      }
   private:
   };
}