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

#include <set>
#include "boost/foreach.hpp"
#include <cstdio>
#include "triple_bond_maker.h"
#include "algebra.h"

using namespace imago;

TripleBondMaker::TripleBondMaker( Skeleton &s ) : _s(s), _g(_s.getGraph())
{
   _avgBondLength = _s.bondLength();
}

TripleBondMaker::~TripleBondMaker()
{
}

TripleBondMaker::Result TripleBondMaker::operator ()(
                           boost::tuple<Edge,Edge,Edge> edges)
{
   std::set<Vertex> toRemove;
   Edge first, second, third;
   boost::tie(first, second, third) = edges;

   Vertex fbegin = boost::source(first, _g), fend = target(first, _g),
          sbegin = boost::source(second, _g), send = target(second, _g),
          tbegin = boost::source(third, _g), tend = target(third, _g);

   boost::property_map<Graph, boost::vertex_pos_t>::type
      positions = boost::get(boost::vertex_pos, _g);

   Vec2d fb_pos = positions[fbegin], fe_pos = positions[fend],
         sb_pos = positions[sbegin], se_pos = positions[send],
         tb_pos = positions[tbegin], te_pos = positions[tend];

   if (Vec2d::distance(fb_pos, sb_pos) > Vec2d::distance(fb_pos, se_pos))
   {
      std::swap(sbegin, send);
      std::swap(sb_pos, se_pos);
   }
   if (Vec2d::distance(sb_pos, tb_pos) > Vec2d::distance(sb_pos, te_pos))
   {
      std::swap(tbegin, tend);
      std::swap(tb_pos, te_pos);
   }

   Result ret;
   Vec2d p1, p2;
   double l1, l2;

   boost::tie(p1, p2) = Algebra::segmentProjection(sb_pos, se_pos,
                                                   fb_pos, fe_pos);

   l1 = Vec2d::distance(fb_pos, p1);
   l2 = Vec2d::distance(p2, fe_pos);

   bool left = l1 > 0.25 * _avgBondLength,
        right = l2 > 0.25 * _avgBondLength;
   
   boost::remove_edge(first, _g);
   boost::remove_edge(second, _g);
   boost::remove_edge(third, _g);

   if (left || right)
   {
      toRemove.insert(sbegin);
      toRemove.insert(send);
      toRemove.insert(tbegin);
      toRemove.insert(tend);
   }
      
   if (left && right)
   {
      Vertex v1 = _s.addVertex(p1), v2 = _s.addVertex(p2);

      Edge e1 = _s.addBond(fbegin, v1),
           e2 = _s.addBond(v1, v2, TRIPLE),
           e3 = _s.addBond(v2, fend);

      ret = boost::make_tuple(2, e1, e3);
   }
   else if (left)
   {
      Vertex v = _s.addVertex(p1);

      Edge e1 = _s.addBond(fbegin, v, SINGLE),
           e2 = _s.addBond(v, fend, TRIPLE);
      
      ret = boost::make_tuple(1, e1, Edge());
   }
   else if (right)
   {
      Vertex v = _s.addVertex(p2);
      
      Edge e1 = _s.addBond(fbegin, v, TRIPLE),
           e2 = _s.addBond(v, fend, SINGLE);
      ret = boost::make_tuple(1, e2, Edge());
   }
   else
   {
      p1.set((fb_pos.x + sb_pos.x + tb_pos.x) / 3,
             (fb_pos.y + sb_pos.y + tb_pos.y) / 3);
      p2.set((fe_pos.x + se_pos.x + te_pos.x) / 3,
             (fe_pos.y + se_pos.y + te_pos.y) / 3);
      
      Vertex v1 = _s.addVertex(p1), v2 = _s.addVertex(p2);
      Vertex *mbegin, *mend;
      double dist;

      if ( (l1 = Vec2d::distance(p1, fb_pos)) <
           (l2 = Vec2d::distance(p1, sb_pos)))
         mbegin = &fbegin, mend = &fend, dist = l1;
      else
         mbegin = &sbegin, mend = &send, dist = l2;

      if (Vec2d::distance(p1, tb_pos) < dist)
         mbegin = &tbegin, mend = &tend;

      _s._reconnectBonds(*mbegin, v1);
      _s._reconnectBonds(*mend, v2);

      toRemove.insert(fbegin);
      toRemove.insert(fend);
      toRemove.insert(sbegin);
      toRemove.insert(send);
      toRemove.insert(tbegin);
      toRemove.insert(tend);
      
      Edge e = _s.addBond(v1, v2, TRIPLE);

      ret = boost::make_tuple(0, Edge(), Edge());
   }

   BOOST_FOREACH(Vertex v, toRemove)
      if (boost::degree(v, _g) == 0)
         boost::remove_vertex(v, _g);
   
   return ret;
}
