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
#ifndef _skeleton_h
#define _skeleton_h

#include <deque>
#include "beast.h"
#include <tuple>

#include "comdef.h"
#include "vec2d.h"
#include "settings.h"

namespace imago
{          
   enum BondType
   {
      BT_SINGLE = 1,
      BT_DOUBLE,
      BT_TRIPLE,
      BT_AROMATIC,
      BT_SINGLE_UP,
      BT_SINGLE_DOWN,
      BT_ARROW,
      BT_WEDGE,
      BT_SINGLE_UP_C, // single up bonds that need to be checked
      BT_UNKNOWN
   };

   struct Bond
   {
      double length, k;
      BondType type;

      Bond() {};

      Bond( double _length, double _k, BondType _type ) : length(_length),
         k(_k), type(_type) {};
   };

   class Skeleton
   {
   public: 
      struct VertexData {
         //size_t index;
         //Segment* segment;
         Vec2d position;
      };

      struct EdgeData {
         Bond bond;
      };

      class SkeletonGraph : public beast::Graph<VertexData, EdgeData>
      {
      public:
         typedef beast::Graph<VertexData, EdgeData> base_type;

         SkeletonGraph()
         {}
         const Vec2d &getVertexPosition(vertex_descriptor v) const { return _vertex_indices[v.id]->data.position; }
         void setVertexPosition(vertex_descriptor v, const Vec2d &val) { _vertex_indices[v.id]->data.position = val; }
         Bond getEdgeBond(edge_descriptor e) const { return _edge_indices[e.id]->data.bond; }
         void setEdgeBond(edge_descriptor e, Bond &val) { _edge_indices[e.id]->data.bond = val; }
      };

      typedef SkeletonGraph::base_type::vertex_descriptor Vertex;
      typedef SkeletonGraph::base_type::edge_descriptor Edge;

      Skeleton();

      Vertex addVertex(const Vec2d &pos);

      Edge addBond(Vertex v1, Vertex v2, BondType type = BT_SINGLE, bool throw_if_error = false);
      Edge addBond(const Vec2d &begin, const Vec2d &end, BondType type = BT_SINGLE, bool throw_if_error = false);

      void removeBond(Vertex v1, Vertex v2);
      void removeBond(const Edge &e);

      Vertex getBondBegin(const Edge &e) const;
      Vertex getBondEnd(const Edge &e) const;

      int getVerticesCount() const;
      int getEdgesCount() const;
      const Vec2d &getVertexPos(Vertex v1) const;
      BondType getBondType(const Edge &e) const;
      Bond getBondInfo(const Edge &e) const;
      void setBondType(const Edge &e, BondType t);

      void reverseEdge(const Edge &e);

      void setInitialAvgBondLength(Settings& vars, double avg_length );
      void recalcAvgBondLength();
      double bondLength() const { return _avg_bond_length; } 
      
      void modifyGraph(Settings& vars);

      void clear();

      operator SkeletonGraph() { return _g; }
      SkeletonGraph &getGraph() { return _g; }
      ~Skeleton();

      int getWarningsCount() const { return _warnings; }
      int getDissolvingsCount() const { return _dissolvings; }
	  
      void calcShortBondsPenalty(const Settings& vars);
      void calcCloseVerticiesPenalty(const Settings& vars);

   protected:

      SkeletonGraph _g;
      int _warnings, _dissolvings;
      
   private:
      friend class DoubleBondMaker;
      friend class TripleBondMaker;
      friend class MultipleBondChecker;
      
      void _reconnectBonds(Vertex from, Vertex to);
      bool _checkMidBonds(Vertex from, Vertex to);
      void _reconnectBondsRWT(Vertex from, Vertex to, BondType new_t);
      void _repairBroken(const Settings& vars);
      void _findMultiple(const Settings& vars);

   public:
      void _joinVertices(double eps);
      bool _dissolveShortEdges (double coeff, const bool has2nb = false);
      void deleteBadTriangles( double eps );

   private:
      bool _dissolveIntermediateVertices (const Settings& vars);
      double _avgEdgeLendth(Vertex v, int &nnei);
      typedef std::tuple<bool, Edge, Edge> MakersReturn;
      //MakersReturn _makeDouble( std::pair<Edge, Edge> edges );
      //MakersReturn _makeTriple( std::tuple<Edge, Edge, Edge> edges );
      bool _isParallel(const Edge &first, const Edge &second) const;
      bool _isEqualDirection(const Edge &first, const Edge &second) const;
      bool _isEqualDirection(Vertex b1, Vertex e1, Vertex b2, Vertex e2)  const;
      bool _isSegmentIntersectedByEdge(const Settings& vars, const Vec2d &b, const Vec2d &e, const std::deque<Edge> &edges) const;
      void _processInlineDoubleBond(const Settings& vars);

      void _connectBridgedBonds(const Settings& vars);
	  
      double _avg_bond_length;
      double _parLinesEps;
      double _addVertexEps;
      double _min_bond_length;
      double _min_bond_h2nb_length;
      std::vector<Vec2d> _vertices_big_degree;

      Skeleton( const Skeleton &g );
   };
}


#endif /* _skeleton_h_ */
