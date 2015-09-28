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

#include "double_bond_maker.h"
#include "algebra.h"
#include "exception.h"

#include "image_draw_utils.h"
#include "image_utils.h"
#include "settings.h"

using namespace imago;

DoubleBondMaker::DoubleBondMaker( const Settings& settings, Skeleton &s ) : _s(s), _g(_s.getGraph()), vars(settings)
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
   
   std::tie(e, exists) = _g.getEdge(a, b);
   if (exists)
      _g.removeEdge(e);
   
   std::vector<Vertex> toDelete;

   for(Graph::adjacency_iterator begin = _g.adjacencyBegin(a), end = _g.adjacencyEnd(a);
       begin != end; begin = end)
      for(Graph::vertex_descriptor v;
          begin != end? (v = *begin, true) : false;
          ++begin)
   {
      if (third && v == *third)
         continue;
      
      for(Graph::adjacency_iterator begin = _g.adjacencyBegin(v), end = _g.adjacencyEnd(v);
          begin != end; begin = end)
         for(Graph::vertex_descriptor u;
             begin != end? (u = *begin, true) : false;
             ++begin)
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
      _g.removeEdge(_g.getEdge(a, *it).first);
      _g.removeEdge(_g.getEdge(*it, b).first);
      if (_g.getDegree(*it) == 0)
         _g.removeVertex(*it);
   }
}

DoubleBondMaker::Result DoubleBondMaker::_simple()
{
   size_t dfb = _g.getDegree(fb), dfe = _g.getDegree(fe),
       dsb = _g.getDegree(sb), dse = _g.getDegree(se);

   if ((dfb > 1 || dfe > 1) && dsb == 1 && dse == 1)
   {
      _g.removeEdge(second);
      _g.removeVertex(sb);
      _g.removeVertex(se);
      _s.setBondType(first, BT_DOUBLE);
   }
   else if ((dsb > 1 || dse > 1) && dfb == 1 && dfe == 1)
   {
      _g.removeEdge(first);
      _g.removeVertex(fb);
      _g.removeVertex(fe);
      _s.setBondType(second, BT_DOUBLE);
   }
   else
   {
      Vec2d p1, p2;
      p1.middle(fb_pos, sb_pos);
      p2.middle(fe_pos, se_pos);

      _g.removeEdge(first);
      _g.removeEdge(second);

      Vertex nb = _s.addVertex(p1),
             ne = _s.addVertex(p2);

      _s._reconnectBonds(fb, nb);
      _s._reconnectBonds(sb, nb);
      _s._reconnectBonds(fe, ne);
      _s._reconnectBonds(se, ne);
      std::set<Vertex> toRemove;

      if (_g.getDegree(fb) == 0)
         toRemove.insert(fb);
      if (_g.getDegree(sb) == 0)
         toRemove.insert(sb);
      if (_g.getDegree(fe) == 0)
         toRemove.insert(fe);
      if (_g.getDegree(se) == 0)
         toRemove.insert(se);

      for(Vertex v: toRemove)
      {
         _g.removeVertex(v);
      }

	  _s.addBond(nb, ne, BT_DOUBLE);
   }

   return std::make_tuple(0, empty, empty);
}

DoubleBondMaker::Result DoubleBondMaker::_hard()
{
   //Not really true
   if (_g.getDegree(sb) + _g.getDegree(se) != 2)
      return std::make_tuple(0, empty, empty);
   
   Vec2d p1, p2;
   std::tie(p1, p2) = Algebra::segmentProjection(sb_pos, se_pos, fb_pos, fe_pos);

   double l1 = Vec2d::distance(fb_pos, p1), l2 = Vec2d::distance(fe_pos, p2);

   _g.removeEdge(first);
   _g.removeEdge(second);
   if (fb != sb)
      _g.removeVertex(sb);
   if (fe != se)
      _g.removeVertex(se);

   bool left = l1 > vars.mbond.DoubleLeftLengthTresh * _avgBondLength;
   bool right = l2 > vars.mbond.DoubleRightLengthTresh * _avgBondLength;

   if (left && right)
   {
      Vertex v1 = _s.addVertex(p1), v2 = _s.addVertex(p2);
      Edge e1 = _s.addBond(fb, v1);
      _s.addBond(v1, v2, BT_DOUBLE);
      Edge e2 = _s.addBond(v2, fe);
      return std::make_tuple(2, e1, e2);
   }
   else if (left)
   {
      Vertex v = _s.addVertex(p1);
      Edge e1 = _s.addBond(fb, v);
      Edge e2 = _s.addBond(v, fe, BT_DOUBLE);
      return std::make_tuple(1, e1, empty);
   }
   else if (right)
   {
      Vertex v = _s.addVertex(p2);
      Edge e1 = _s.addBond(fb, v, BT_DOUBLE);
      Edge e2 = _s.addBond(v, fe);
      return std::make_tuple(1, e2, empty);
   }
   else
   {
      throw LogicException("DoubleBondMake::_hard");
   }
}

DoubleBondMaker::Result DoubleBondMaker::operator()( std::pair<Edge,Edge> edges )
{
   first = edges.first; second = edges.second;

   fb = first.m_source; fe = first.m_target;
   sb = second.m_source, se = second.m_target;

   Result ret;
   ret = _validateVertices();
   if (std::get<0>(ret) != 2) //Both edges should be valid
      return ret;
   
   if (!_g.getEdge(fb, fe).second ||
       !_g.getEdge(sb, se).second)
      return std::make_tuple(0, empty, empty);

   fb_pos = _g.getVertexPosition(fb);
   fe_pos = _g.getVertexPosition(fe);
   sb_pos = _g.getVertexPosition(sb);
   se_pos = _g.getVertexPosition(se);

   bf = _g.getEdgeBond(first);
   bs = _g.getEdgeBond(second);

   double dbb = Vec2d::distance(fb_pos, sb_pos) + Vec2d::distance(fe_pos, se_pos),
      dbe = Vec2d::distance(fb_pos, se_pos) + Vec2d::distance(fe_pos, sb_pos);
   
   if (dbe < dbb)
   {
      std::swap(sb, se);
      std::swap(sb_pos, se_pos);
   }

   if (_g.getDegree(fb) < _g.getDegree(fe) &&
       _g.getDegree(sb) < _g.getDegree(se))
   {
      std::swap(fb, fe);
      std::swap(fb_pos, fe_pos);
      std::swap(sb, se);
      std::swap(sb_pos, se_pos);
   }

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

   if (_avgBondLength > vars.mbond.Case1LengthTresh)
	   mult = vars.mbond.Case1Factor;
   else if (_avgBondLength > vars.mbond.Case2LengthTresh)
	   mult = vars.mbond.Case2Factor;
   else
	   mult = vars.mbond.Case3Factor;

   if (fl - sl < mult * _avgBondLength)
      return _simple();
   else
      return _hard();
}

DoubleBondMaker::Result DoubleBondMaker::_validateVertices()
{
   std::set<Vertex> vertices;
   Graph::vertex_iterator vi, vi_end;
   vi = _g.vertexBegin();
   vi_end = _g.vertexEnd();
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
      return std::make_tuple(2, first, second);
   else if (firstValid)
      return std::make_tuple(1, first, empty);
   else if (secondValid)
      return std::make_tuple(1, second, empty);
   else
      return std::make_tuple(0, empty, empty);
}
