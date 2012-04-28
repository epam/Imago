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
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/iteration_macros.hpp"

#include "double_bond_maker.h"
#include "algebra.h"
#include "exception.h"

#include "image_draw_utils.h"
#include "current_session.h"
#include "image_utils.h"
#include "constants.h"

using namespace imago;

DoubleBondMaker::DoubleBondMaker( Skeleton &s ) : _s(s), _g(_s.getGraph())
{
   _avgBondLength = _s.bondLength();
}

DoubleBondMaker::~DoubleBondMaker()
{
}

void DoubleBondMaker::_disconnect( Vertex a, Vertex b, const Vertex *third )
{
   bool exists;
   Edge e;
   
   boost::tie(e, exists) = edge(a, b, _g);
   if (exists)
      boost::remove_edge(e, _g);
   
   std::vector<Vertex> toDelete;

   BGL_FORALL_ADJ(a, v, _g, Graph)
   {
      if (third && v == *third)
         continue;
      
      BGL_FORALL_ADJ(v, u, _g, Graph)
      {
         if (u == a)
            continue;

         if (u == b)
         {
            toDelete.push_back(v);
            break;
         }
      }
   }
   
   for (std::vector<Vertex>::iterator it = toDelete.begin();
        it != toDelete.end(); ++it)
   {
      boost::remove_edge(boost::edge(a, *it, _g).first, _g);
      boost::remove_edge(boost::edge(*it, b, _g).first, _g);
      if (boost::degree(*it, _g) == 0)
         boost::remove_vertex(*it, _g);
   }
}

DoubleBondMaker::Result DoubleBondMaker::_simple()
{
   // DP: commented that; needed a quick fix

   int dfb = boost::degree(fb, _g), dfe = boost::degree(fe, _g),
       dsb = boost::degree(sb, _g), dse = boost::degree(se, _g);

   if ((dfb > 1 || dfe > 1) && dsb == 1 && dse == 1)
   {
      boost::remove_edge(second, _g);
      boost::remove_vertex(sb, _g);
      boost::remove_vertex(se, _g);
      _s.setBondType(first, DOUBLE);
   }
   else if ((dsb > 1 || dse > 1) && dfb == 1 && dfe == 1)
   {
      boost::remove_edge(first, _g);
      boost::remove_vertex(fb, _g);
      boost::remove_vertex(fe, _g);
      _s.setBondType(second, DOUBLE);
   }
   else
   {
      Vec2d p1, p2;
      p1.middle(fb_pos, sb_pos);
      p2.middle(fe_pos, se_pos);

      boost::remove_edge(first, _g);
      boost::remove_edge(second, _g);

      Vertex nb = _s.addVertex(p1),
             ne = _s.addVertex(p2);

      _s._reconnectBonds(fb, nb);
      _s._reconnectBonds(sb, nb);
      _s._reconnectBonds(fe, ne);
      _s._reconnectBonds(se, ne);
      std::set<Vertex> toRemove;
      /*
   {
      double len_f = (boost::get(boost::edge_type, _g, first)).length;
      double len_s = (boost::get(boost::edge_type, _g, second)).length;
      

      // keep the larger one
      if (len_f > len_s)
      {
         _s._reconnectBonds(sb, fb);
         _s._reconnectBonds(se, fe);
         if (boost::degree(sb, _g) == 0)
            toRemove.insert(sb);
         if (boost::degree(se, _g) == 0)
            toRemove.insert(se);
         _s.setBondType(first, DOUBLE);
      }
      else
      {
         _s._reconnectBonds(fb, sb);
         _s._reconnectBonds(fe, se);
         if (boost::degree(fb, _g) == 0)
            toRemove.insert(fb);
         if (boost::degree(fe, _g) == 0)
            toRemove.insert(fe);
         _s.setBondType(second, DOUBLE);
      }
      */


      //TODO: Delete them now or later?
      //Some vars may point to the same vertex, so this will cause segfault
      
      if (boost::degree(fb, _g) == 0)
         toRemove.insert(fb);
      if (boost::degree(sb, _g) == 0)
         toRemove.insert(sb);
      if (boost::degree(fe, _g) == 0)
         toRemove.insert(fe);
      if (boost::degree(se, _g) == 0)
         toRemove.insert(se);


      BOOST_FOREACH(Vertex v, toRemove)
      {
         boost::remove_vertex(v, _g);
      }
      //DP: commented this too
      _s.addBond(nb, ne, DOUBLE);
   }

   return make_tuple(0, empty, empty);
}

DoubleBondMaker::Result DoubleBondMaker::_hard()
{
   //Not really true
   if (boost::degree(sb, _g) + boost::degree(se, _g) != 2)
      return boost::make_tuple(0, empty, empty);
   
   Vec2d p1, p2;
   boost::tie(p1, p2) = Algebra::segmentProjection(sb_pos, se_pos, fb_pos, fe_pos);

   double l1 = Vec2d::distance(fb_pos, p1), l2 = Vec2d::distance(fe_pos, p2);

   boost::remove_edge(first, _g);
   boost::remove_edge(second, _g);
   if (fb != sb)
      boost::remove_vertex(sb, _g);
   if (fe != se)
      boost::remove_vertex(se, _g);

   bool left = l1 > consts::DoubleBondMaker::LeftLengthTresh * _avgBondLength;
   bool right = l2 > consts::DoubleBondMaker::RightLengthTresh * _avgBondLength;

   if (left && right)
   {
      Vertex v1 = _s.addVertex(p1), v2 = _s.addVertex(p2);
      Edge e1 = _s.addBond(fb, v1);
      _s.addBond(v1, v2, DOUBLE);
      Edge e2 = _s.addBond(v2, fe);
      return boost::make_tuple(2, e1, e2);
   }
   else if (left)
   {
      Vertex v = _s.addVertex(p1);
      Edge e1 = _s.addBond(fb, v);
      Edge e2 = _s.addBond(v, fe, DOUBLE);
      return boost::make_tuple(1, e1, empty);
   }
   else if (right)
   {
      Vertex v = _s.addVertex(p2);
      Edge e1 = _s.addBond(fb, v, DOUBLE);
      Edge e2 = _s.addBond(v, fe);
      return boost::make_tuple(1, e2, empty);
   }
   else
   {
      throw LogicException("DoubleBondMake::_hard:%d", __LINE__);
   }
}

DoubleBondMaker::Result DoubleBondMaker::operator()( std::pair<Edge,Edge> edges )
{
   first = edges.first; second = edges.second;

   fb = source(first, _g); fe = target(first, _g);
   sb = source(second, _g), se = target(second, _g);

   Result ret;
   ret = _validateVertices();
   if (boost::get<0>(ret) != 2) //Both edges should be valid
      return ret;
   
   if (!boost::edge(fb, fe, _g).second ||
       !boost::edge(sb, se, _g).second)
      return boost::make_tuple(0, empty, empty);

   fb_pos = boost::get(boost::vertex_pos, _g, fb);
   fe_pos = boost::get(boost::vertex_pos, _g, fe);
   sb_pos = boost::get(boost::vertex_pos, _g, sb);
   se_pos = boost::get(boost::vertex_pos, _g, se);

   bf = boost::get(boost::edge_type, _g, first);
   bs = boost::get(boost::edge_type, _g, second);

   double dbb = Vec2d::distance(fb_pos, sb_pos) + Vec2d::distance(fe_pos, se_pos),
      dbe = Vec2d::distance(fb_pos, se_pos) + Vec2d::distance(fe_pos, sb_pos);
   
   if (dbe < dbb)
   {
      std::swap(sb, se);
      std::swap(sb_pos, se_pos);
   }

   if (boost::degree(fb, _g) < boost::degree(fe, _g) &&
       boost::degree(sb, _g) < boost::degree(se, _g))
   {
      std::swap(fb, fe);
      std::swap(fb_pos, fe_pos);
      std::swap(sb, se);
      std::swap(sb_pos, se_pos);
   }

//   if (fe == sb)
//      return boost::make_tuple(0, empty, empty);

   const Vertex *third = 0;
   if (fe == se)
      third = &fe;

   _disconnect(fb, sb, third);

   third = 0;
   if (fb == sb)
      third = &fb;
   _disconnect(fe, se, third);

   double fl = bf.length,
          sl = bs.length;
   double mult;

   if (_avgBondLength > consts::DoubleBondMaker::Case1LengthTresh)
	   mult = consts::DoubleBondMaker::Case1Factor;
   else if (_avgBondLength > consts::DoubleBondMaker::Case2LengthTresh)
	   mult = consts::DoubleBondMaker::Case2Factor;
   else
	   mult = consts::DoubleBondMaker::Case3Factor;

   //printf("SIMPLE OR HARD %lf %lf\n", fl - sl, mult * _avgBondLength);
   if (fl - sl < mult * _avgBondLength)
      return _simple();
   else
      return _hard();
}

DoubleBondMaker::Result DoubleBondMaker::_validateVertices()
{
   std::set<Vertex> vertices;
   boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
   boost::tie(vi, vi_end) = boost::vertices(_g);
   vertices.insert(vi, vi_end);
   std::set<Vertex>::iterator it_end = vertices.end();
   bool firstValid, secondValid;
   firstValid = secondValid = true;
   if (vertices.find(fb) == it_end ||
       vertices.find(fe) == it_end)
      firstValid = false;
   if (vertices.find(sb) == it_end ||
       vertices.find(se) == it_end)
      secondValid = false;

   if (firstValid && secondValid)
      return boost::make_tuple(2, first, second);
   else if (firstValid)
      return boost::make_tuple(1, first, empty);
   else if (secondValid)
      return boost::make_tuple(1, second, empty);
   else
      return boost::make_tuple(0, empty, empty);
}
