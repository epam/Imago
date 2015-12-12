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

#include <cmath>
#include <set>

#include "comdef.h"
#include "algebra.h"
#include "log_ext.h"
#include "skeleton.h"
#include "double_bond_maker.h"
#include "triple_bond_maker.h"
#include "multiple_bond_checker.h"
#include "image_draw_utils.h"
#include "image_utils.h"
#include "settings.h"

using namespace imago;

Skeleton::Skeleton()
{	
}

void Skeleton::setInitialAvgBondLength(Settings& vars, double avg_length )
{
   _avg_bond_length = avg_length;
   double mult = vars.skeleton.BaseMult;

   // TODO: depends on hard-set constants (something more adaptive required here)

   if (_avg_bond_length < vars.skeleton.ShortBondLen)
	   mult = vars.skeleton.ShortMul;
   else if (_avg_bond_length < vars.skeleton.MediumBondLen)
	   mult = vars.skeleton.MediumMul;
   else if (_avg_bond_length < vars.skeleton.LongBondLen)
	   mult = vars.skeleton.LongMul;
   
   _addVertexEps = mult * _avg_bond_length;
}

void Skeleton::recalcAvgBondLength()
{
   size_t bonds_num = _g.edgeCount();

   if (bonds_num == 0)
      return;

   _avg_bond_length = 0;
   _min_bond_length = DIST_INF;

   for(SkeletonGraph::edge_iterator begin = _g.edgeBegin(), end = _g.edgeEnd();
       begin != end;
       begin = end)
      for(SkeletonGraph::edge_descriptor e;
          begin != end ? (e = *begin, true) : false;
          ++begin)
   {
      double len = _g.getEdgeBond(e).length;
      _avg_bond_length += len;
      if (_min_bond_length > len)
         _min_bond_length = len;
   }

   _avg_bond_length /= bonds_num;
}

Skeleton::Edge Skeleton::addBond( Vertex &v1, Vertex &v2, BondType type, bool throw_if_error )
{
   std::pair<Edge, bool> p;

   p = _g.getEdge(v1, v2);
   if (p.second)
   {
	   // Graph already has the edge
	   if (throw_if_error)
	   {
		   throw LogicException("Already has edge");
	   }
	   else
	   {
		   _warnings++;
		   std::ostringstream temp;
         temp << "WARNING: Already has edge (" << v1.id << ", " << v2.id << ")";
		   getLogExt().appendText(temp.str());
		   return p.first;
	   }
   }

   p = _g.addEdge(v1, v2);

   Vec2d begin = _g.getVertexPosition(v1),
         end = _g.getVertexPosition(v2);

   if (!p.second)
   {
	   std::ostringstream temp;
	   temp << "ERROR: Can't add bond (" << begin.x << ", " <<  begin.y << ") (" << end.x << ", " << end.y << ")";
	   getLogExt().appendText(temp.str());

      throw LogicException("Can't add bond");
   }

   Edge e = p.first;

   int dx = round(end.x - begin.x), dy = round(end.y - begin.y);
   double k = 0;

   if (dx == 0)
      k = HALF_PI;
   else
   {
      double angle = atan((double) dy / dx);
      k = angle;
   }

   Bond b(Vec2d::distance(begin, end), k, type);

   _g.setEdgeBond(e, b);

   return e;
}

Skeleton::Edge Skeleton::addBond( const Vec2d &begin, const Vec2d &end,
                                  BondType type, bool throw_if_error )
{
   Vertex v1 = addVertex(begin), v2 = addVertex(end);

   return addBond(v1, v2, type, throw_if_error);
}

void Skeleton::removeBond( Vertex &v1, Vertex &v2 )
{
   _g.removeEdge(v1, v2);
}

void Skeleton::removeBond( Edge &e )
{
   _g.removeEdge(e);
}

Skeleton::Vertex Skeleton::addVertex( const Vec2d &pos )
{
   Vertex v = _g.addVertex();

   _g.setVertexPosition(v, pos);

   return v;
}

Vec2d Skeleton::getVertexPos( const Vertex &v1 ) const
{
   return _g.getVertexPosition(v1);
}

int Skeleton::getVerticesCount() const
{
   return (int)_g.vertexCount();
}

int Skeleton::getEdgesCount() const
{
   return (int)_g.edgeCount();
}

Bond Skeleton::getBondInfo( const Edge &e ) const
{
   return _g.getEdgeBond(e);
}

Skeleton::Vertex Skeleton::getBondBegin( const Skeleton::Edge &e ) const
{
   return e.m_source;
}

Skeleton::Vertex Skeleton::getBondEnd( const Skeleton::Edge &e ) const
{
   return e.m_target;
}

void Skeleton::_repairBroken(const Settings& vars)
{
   double coef;
   recalcAvgBondLength();

   // TODO: depends on hard-set constants (something more adaptive required here)

   double toSmallErr;
   if (_avg_bond_length > vars.skeleton.LongBondLen)
	   toSmallErr = vars.skeleton.LongSmallErr;
   else if (_avg_bond_length > vars.skeleton.MediumBondLen)
	   toSmallErr = vars.skeleton.MediumSmallErr;
   else
	   toSmallErr = vars.skeleton.BaseSmallErr;

   std::deque<Vertex> toRemove;

   for(SkeletonGraph::vertex_iterator begin = _g.vertexBegin(), end = _g.vertexEnd();
       begin != end; begin = end)
      for (SkeletonGraph::vertex_descriptor v;
           begin != end ? (v = *begin, true):false;
           ++begin)
   {
      if (_g.getDegree(v) != 2)
         continue;
      
      SkeletonGraph::adjacency_iterator vi = _g.adjacencyBegin(v);
      Vertex x, y;
      x = *vi;
      y = *(++vi);
      Edge e1, e2;
      Bond e1b, e2b;
      e1 = _g.getEdge(x, v).first;
      e2 = _g.getEdge(v, y).first;
      e1b = getBondInfo(e1);
      e2b = getBondInfo(e2);

      if (e1b.length < toSmallErr * _avg_bond_length &&
          e2b.length < toSmallErr * _avg_bond_length)
         continue;

	  coef = vars.skeleton.BrokenRepairCoef1;
	  if (e1b.length < vars.skeleton.BrokenRepairFactor * toSmallErr * _avg_bond_length ||
          e2b.length < vars.skeleton.BrokenRepairFactor * toSmallErr * _avg_bond_length)
         coef = vars.skeleton.BrokenRepairCoef2;

      Vec2d x_pos, y_pos, v_pos;
      x_pos = _g.getVertexPosition(x);
      y_pos = _g.getVertexPosition(y);
      v_pos = _g.getVertexPosition(v);
      Vec2d v1, v2;
      v1.diff(x_pos, v_pos);
      v2.diff(y_pos, v_pos);

      bool found = false;
      try
      {
         double angle = Vec2d::angle(v1, v2);
		 if (angle > PI - coef * vars.skeleton.BrokenRepairAngleEps)
            found = true;
      }
      catch (DivizionByZeroException &)
      {}

      if (found)
      {
         Edge e;
         Vertex to;
         if (e1b.length < e2b.length)
            e = e1, to = x;
         else
            e = e2, to = y;

         _g.removeEdge(e);
         _reconnectBonds(v, to);
         toRemove.push_back(v);
      }
   }

   for(Vertex v: toRemove)
      _g.removeVertex(v);
}

bool Skeleton::_isEqualDirection( const Edge &first, const Edge &second ) const
{
   Bond f = _g.getEdgeBond(first),
        s = _g.getEdgeBond(second);

   return (fabs(f.k - s.k) < _parLinesEps);
}

bool Skeleton::_isEqualDirection( const Vertex &b1,const Vertex &e1,const Vertex &b2,const Vertex &e2)  const
{
   Vec2d begin1 = _g.getVertexPosition(b1),
         end1 = _g.getVertexPosition(e1);

   Vec2d begin2 = _g.getVertexPosition(b2),
         end2 = _g.getVertexPosition(e2);
   
   int dx1 = round(end1.x - begin1.x), dy1 = round(end1.y - begin1.y);
   double k1 = 0;

   if (dx1 == 0)
      k1 = HALF_PI;
   else
   {
      double angle1 = atan((double) dy1 / dx1);
      k1 = angle1;
   }

   int dx2 = round(end2.x - begin2.x), dy2 = round(end2.y - begin2.y);
   double k2 = 0;

   if (dx2 == 0)
      k2 = HALF_PI;
   else
   {
      double angle2 = atan((double) dy2 / dx2);
      k2 = angle2;
   }

   return((fabs(k1 - k2) < _parLinesEps) && (sign(dx1) == sign(dx2)));
}


bool Skeleton::_isParallel( const Edge &first, const Edge &second ) const
{
   Bond f = _g.getEdgeBond(first),
        s = _g.getEdgeBond(second);

   return (fabs(f.k - s.k) < _parLinesEps ||
                    fabs(fabs(f.k - s.k) - PI) < _parLinesEps);
}

void Skeleton::calcShortBondsPenalty(const Settings& vars)
{
	logEnterFunction();

	int probablyWarnings = 0;
	int minSize = (std::max)((int)vars.dynamic.CapitalHeight / 2, vars.main.MinGoodCharactersSize);
   for(SkeletonGraph::edge_iterator begin = _g.edgeBegin(), end = _g.edgeEnd();
       begin != end;
       begin = end)
      for(SkeletonGraph::edge_descriptor edge;
          begin != end ? (edge = *begin, true) : false;
          ++begin)
	{
		const Vertex &beg = edge.m_source;
		const Vertex &end = edge.m_target;

		double edge_len = _g.getEdgeBond(edge).length;

		if (edge_len < minSize / 2)
			probablyWarnings += 2;
		else if (edge_len < minSize)
			probablyWarnings += 1;
	}
	getLogExt().append("probablyWarnings", probablyWarnings);
	_warnings += probablyWarnings / 2;
	getLogExt().append("_warnings updated", _warnings);	
}

void Skeleton::calcCloseVerticiesPenalty(const Settings& vars)
{
	logEnterFunction();

	int probablyWarnings = 0;
   for(SkeletonGraph::vertex_iterator begin = _g.vertexBegin(), end = _g.vertexEnd();
       begin != end; begin = end)
      for (SkeletonGraph::vertex_descriptor one;
           begin != end ? (one = *begin, true):false;
           ++begin)
	{
      for(SkeletonGraph::vertex_iterator begin = _g.vertexBegin(), end = _g.vertexEnd();
          begin != end; begin = end)
         for (SkeletonGraph::vertex_descriptor two;
              begin != end ? (two = *begin, true):false;
              ++begin)
		{
			if (one == two)
				continue;

			double dist = Vec2d::distance(getVertexPos(one), getVertexPos(two));

			if (!_g.getEdge(one, two).second)
			{
				if (dist < vars.dynamic.CapitalHeight / 4)
					probablyWarnings += 2;
				else if (dist < vars.dynamic.CapitalHeight / 2)
					probablyWarnings += 1;
			}
		}		
	}
	getLogExt().append("probablyWarnings", probablyWarnings);
	_warnings += probablyWarnings / 2; // each counted twice
	getLogExt().append("_warnings updated", _warnings);	
}

bool Skeleton::_dissolveShortEdges (double coeff, const bool has2nb)
{

   for(SkeletonGraph::edge_iterator begin = _g.edgeBegin(), end = _g.edgeEnd();
       begin != end;
       begin = end)
      for(SkeletonGraph::edge_descriptor edge;
          begin != end ? (edge = *begin, true) : false;
          ++begin)
   {
      const Vertex &beg = edge.m_source;
      const Vertex &end = edge.m_target;

      double edge_len = _g.getEdgeBond(edge).length;
      double max_edge_beg = 0, max_edge_end = 0;
	  bool  pb_e = false, pb_b = false;


      // find the longest edge going from the beginning of our edge
      {
		 bool state_conected_b = false;
         std::deque<Vertex> neighbors_b;
         SkeletonGraph::adjacency_iterator b_b, e_b;
         b_b = _g.adjacencyBegin(beg);
         e_b = _g.adjacencyEnd(beg);
         neighbors_b.assign(b_b, e_b);

		 if(neighbors_b.size() > 1)
			 for (size_t i = 0; i < neighbors_b.size(); i++)
			 {
				 if(neighbors_b[i] != end)
				 {
					 Edge ee = _g.getEdge(neighbors_b[i], beg).first; // order is significant for taking edge with eqval direction
					 double len = _g.getEdgeBond(ee).length;
					 state_conected_b = state_conected_b | _checkMidBonds(neighbors_b[i], beg);

					 if (len > max_edge_beg)
						 max_edge_beg = len;
					 if(!pb_b)
						 pb_b = _isEqualDirection(end, beg, neighbors_b[i], beg);
				 }
			 }
      

      // find the longest edge going from the end of our edge
      
		 bool state_conected_e = false;
         std::deque<Vertex> neighbors_e;
         SkeletonGraph::adjacency_iterator b_e, e_e;
         b_e = _g.adjacencyBegin(end);
         e_e = _g.adjacencyEnd(end);
         neighbors_e.assign(b_e, e_e);
		 if(neighbors_e.size() > 1)
			 for (size_t i = 0; i < neighbors_e.size(); i++)
			 {				 
				 if(neighbors_e[i] != beg)
				 {
					 Edge ee = _g.getEdge(neighbors_e[i], end).first; // order is significant for taking edge with eqval direction
					 double len = _g.getEdgeBond(ee).length;

					 if (len > max_edge_end)
						 max_edge_end = len;
					 state_conected_e = state_conected_e | _checkMidBonds(neighbors_e[i], end);
					 if(!pb_e)
						 pb_e = _isEqualDirection(beg, end, neighbors_e[i], end);
				 }
			 }
      
		  if(has2nb)
		  {
			  if (edge_len < max_edge_beg * (coeff) &&
				  edge_len < max_edge_end * (coeff) &&
				  edge_len < _avg_bond_length * coeff)
			  {
				  _dissolvings++;

				  std::ostringstream temp;
				  temp << "dissolving edge len: " << edge_len << ", max_edge_beg: " << max_edge_beg << ", max_edge_end: " << max_edge_end;
				  getLogExt().appendText(temp.str());

				  // dissolve the edge
				  if (max_edge_end < max_edge_beg)
				  {          
					  _reconnectBonds(end, beg);
					  _g.removeVertex(end);
				  }
				  else
				  {
					  _reconnectBonds(beg, end);
					  _g.removeVertex(beg);
				  }
				  return true;
			  }
			  else
			  {				  
				  if(( max_edge_end < _avg_bond_length * coeff) &&
					  (edge_len*(coeff) > max_edge_end) && absolute(max_edge_end) > EPS)
				  {
					  bool ret = false;
					   if(neighbors_e.size() > 1 && !state_conected_e)
						   for (size_t i = 0; i < neighbors_e.size(); i++)
						   {
							   if(neighbors_e[i] != beg)
							   {
								   _reconnectBonds(neighbors_e[i], end);
								   _g.removeVertex(neighbors_e[i]);
								   ret = true;
							   }
						   }
					  if(ret)
						  return ret;
				  }

				  if(( max_edge_beg < _avg_bond_length * coeff) &&
				  (edge_len*(coeff) > max_edge_beg) && absolute(max_edge_beg) > EPS)
				  {

					  bool ret = false;
					   if(neighbors_b.size() > 1 && !state_conected_b)
						   for (size_t i = 0; i < neighbors_b.size(); i++)
						   {
							   if(neighbors_b[i] != end)
							   {
								   _reconnectBonds(neighbors_b[i], beg);
								   _g.removeVertex(neighbors_b[i]);
								   ret = true;
							   }
						   }
					  if(ret)
						  return ret;
				  }
			  }
			  if(edge_len < _avg_bond_length * (coeff))
			  {
				  BondType type = getBondType(edge);
				  if(pb_e && !state_conected_b && type == BT_SINGLE)
				  {
					  _reconnectBonds(beg, end);
					  _g.removeVertex(beg);
					  return true;
					  
				  }
				  if(pb_b && !state_conected_e && type == BT_SINGLE)
				  {
					  _reconnectBonds(end, beg);
					  _g.removeVertex(end);
					  return true;
				  }
			  }
		  }
		  else
		  {
 			  if (edge_len < max_edge_beg * coeff ||
				  edge_len < max_edge_end * coeff)
			  {
				  _dissolvings++;

				  std::ostringstream temp;
				  temp << "dissolving edge len: " << edge_len << ", max_edge_beg: " << max_edge_beg << ", max_edge_end: " << max_edge_end;
				  getLogExt().appendText(temp.str());
				  
				  // dissolve the edge
				 if (max_edge_end < max_edge_beg)
				 {
					_reconnectBonds(end, beg);
					_g.removeVertex(end);
				 }
				 else
				 {
					_reconnectBonds(beg, end);
					_g.removeVertex(beg);
				 }
				 return true;
			  }
		  }
	  }

   }
   return false;
}

bool Skeleton::_dissolveIntermediateVertices (const Settings& vars)
{
   SkeletonGraph::vertex_iterator vi, vi_end;
   vi = _g.vertexBegin();
   vi_end = _g.vertexEnd();

   Vertex to_dissolve;
   double min_err = 10000; // inf
   
   for (; vi != vi_end; ++vi)
   {
	   if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");

      const Vertex &vertex = *vi;

      std::deque<Vertex> neighbors;
      SkeletonGraph::adjacency_iterator b, e;
      b = _g.adjacencyBegin(vertex);
      e = _g.adjacencyEnd(vertex);
      neighbors.assign(b, e);

      if (neighbors.size() != 2)
         continue;

      //TODO: Need something more accurate

      const Edge &edge1 = _g.getEdge(vertex, neighbors[0]).first;
      const Edge &edge2 = _g.getEdge(vertex, neighbors[1]).first;

      const Vertex &beg1 = edge1.m_source;
      const Vertex &beg2 = edge2.m_source;
      const Vertex &end1 = edge1.m_target;
      const Vertex &end2 = edge2.m_target;
      
      Vec2d dir1, dir2;

      if (beg1 == beg2 || end1 == end2)
      {
         dir1.diff(_g.getVertexPosition(end1),
                   _g.getVertexPosition(beg1));
         dir2.diff(_g.getVertexPosition(end2),
                   _g.getVertexPosition(beg2));
      }
      else if (beg1 == end2 || beg2 == end1)
      {
         dir1.diff(_g.getVertexPosition(end1),
                   _g.getVertexPosition(beg1));
         dir2.diff(_g.getVertexPosition(beg2),
                   _g.getVertexPosition(end2));
      }
      else
      {
         throw ImagoException("Edges are not adjacent");
      }

      double d = Vec2d::dot(dir1, dir2);
      double n1 = dir1.norm();
      double n2 = dir2.norm();
      double maxn = std::max(n1, n2);
      
      if (n1 * n2 > EPS) 
         d /= n1 * n2;
      
      double ang = acos(d);

      if (ang < PI * 3 / 4)
         continue;

      double err = n1 * n2 * sin(ang) / (maxn * maxn);

      if (err < min_err)
      {
         min_err = err;
         to_dissolve = vertex;
      }
   }
   
   if (min_err < vars.skeleton.DissolveMinErr) 
   {
	   _dissolvings++;
      
	   getLogExt().append("dissolving vertex, err", min_err);

      std::deque<Vertex> neighbors;
      SkeletonGraph::adjacency_iterator b, e;
      b = _g.adjacencyBegin(to_dissolve);
      e = _g.adjacencyEnd(to_dissolve);
      neighbors.assign(b, e);
      addBond(neighbors[0], neighbors[1], BT_SINGLE);
// The clear function for vertex was needed by boost. Now clearing is implemented in removeVertex.
//      _g.clearVertex(to_dissolve);
		_g.removeVertex(to_dissolve);
      return true;
   }

   return false;
}

void Skeleton::_findMultiple(const Settings& vars)
{
   DoubleBondMaker  _makeDouble(vars, *this);
   TripleBondMaker  _makeTriple(vars, *this);
   MultipleBondChecker _checker(vars, *this);
   
   std::vector<Edge> toProcess;
   SkeletonGraph::edge_iterator ei, ei_e;
   ei = _g.edgeBegin();
   ei_e = _g.edgeEnd();
   for (; ei != ei_e; ++ei)
      if (_g.getEdgeBond(*ei).type == BT_SINGLE)
         toProcess.push_back(*ei);

   std::map<Edge, bool> used;
   do
   {
      std::vector<std::pair<Edge, Edge> > doubleBonds;
      std::vector<std::tuple<Edge, Edge, Edge> > tripleBonds;

      size_t end = toProcess.size();
      for (int ii = 0; ii < end; ii++)
      {
		  if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");

         Edge i = toProcess[ii];
         if (used[i])
            continue;

         for(SkeletonGraph::edge_iterator begin = _g.edgeBegin(), end = _g.edgeEnd();
             begin != end;
             begin = end)
            for(SkeletonGraph::edge_descriptor j;
                begin != end ? (j = *begin, true) : false;
                ++begin)
         {
            if (i == j || _g.getEdgeBond(j).type != BT_SINGLE ||
                used[j])
               continue;

            if (!_checker.checkDouble(vars, i, j))
               continue;

            {
               std::pair<double, Edge*> arr[3];
               arr[0].first = _g.getEdgeBond(i).length;
               arr[0].second = &i;
               arr[1].first = _g.getEdgeBond(j).length;
               arr[1].second = &j;

               if (arr[1].first > arr[0].first)
                  std::swap(arr[0], arr[1]);

               bool is_triple = false;

               for(SkeletonGraph::edge_iterator begin = _g.edgeBegin(), end = _g.edgeEnd();
                   begin != end;
                   begin = end)
                  for(SkeletonGraph::edge_descriptor k;
                      begin != end ? (k = *begin, true) : false;
                      ++begin)
               {
				   if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");

                  if (k == i || k == j ||
                      _g.getEdgeBond(k).type != BT_SINGLE ||
                      used[k])
                     continue;
                  
                  if (!_checker.checkTriple(vars, k))
                     continue;
                  
                  //Check degrees!
                  arr[2].first = _g.getEdgeBond(k).length;
                  arr[2].second = &k;

                  if (arr[2].first > arr[0].first)
                  {
                     std::swap(arr[2], arr[0]);
                     std::swap(arr[1], arr[2]);
                  } else if (arr[2].first > arr[1].first)
                     std::swap(arr[1], arr[2]);

                  is_triple = true;
                  break;
               }

               if (is_triple)
               {
                  used[i] = used[j] = used[*arr[2].second] = true;
                  tripleBonds.push_back(std::make_tuple(*arr[0].second,
                                                        *arr[1].second,
                                                        *arr[2].second));
               }
               else
               {
                  used[i] = used[j] = true;
                  doubleBonds.push_back(std::make_pair(*arr[0].second,
                                                       *arr[1].second));
               }
               break;
            }
         }
      }

      toProcess.erase(toProcess.begin(), toProcess.begin() + end);
      //Copy-paste
      for (size_t i = 0; i < tripleBonds.size(); ++i)
      {
         TripleBondMaker::Result ret = _makeTriple(tripleBonds[i]);

         int add = std::get<0>(ret);
         if (add == 0)
            continue;
         
         used[std::get<0>(tripleBonds[i])] = false;
         used[std::get<1>(tripleBonds[i])] = false;
         used[std::get<2>(tripleBonds[i])] = false;

         if (add == 1)
         {
            toProcess.push_back(std::get<1>(ret));
         }
         else if (add == 2)
         {
            toProcess.push_back(std::get<1>(ret));
            toProcess.push_back(std::get<2>(ret));
         }
         
      }
      
      std::sort(doubleBonds.begin(), doubleBonds.end(),
                DoubleBondComparator<SkeletonGraph>(getGraph()));
            
      for (int i = 0; i < (int)doubleBonds.size(); ++i)
      {
         DoubleBondMaker::Result ret = _makeDouble(doubleBonds[i]);
         
         int add = std::get<0>(ret);
         if (add == 0)
            continue;

         used[doubleBonds[i].first] = false;
         used[doubleBonds[i].second] = false;
         if (add == 1)
         {
            toProcess.push_back(std::get<1>(ret));
         }
         else if (add == 2)
         {
            toProcess.push_back(std::get<1>(ret));
            toProcess.push_back(std::get<2>(ret));
         } 
      }
   } while (false);
   _processInlineDoubleBond(vars);
}

void Skeleton::_processInlineDoubleBond(const Settings& vars)
{
	std::vector<Edge> toProcess, singles;
	std::vector<Edge>::iterator it, foundIt;

	double toSmallErr;
   if (_avg_bond_length > vars.skeleton.LongBondLen)
	   toSmallErr = vars.skeleton.LongSmallErr;
   else if (_avg_bond_length > vars.skeleton.MediumBondLen)
	   toSmallErr = vars.skeleton.MediumSmallErr;
   else
	   toSmallErr = vars.skeleton.BaseSmallErr;
   toSmallErr *= _avg_bond_length;

   for(SkeletonGraph::edge_iterator begin = _g.edgeBegin(), end = _g.edgeEnd();
       begin != end;
       begin = end)
      for(SkeletonGraph::edge_descriptor j;
          begin != end ? (j = *begin, true) : false;
          ++begin)
	{
		if(getBondType(j) == BT_SINGLE)
			singles.push_back(j);
		if(getBondType(j) == BT_DOUBLE)
			toProcess.push_back(j);
	}


	for(size_t i = 0;i < toProcess.size();i++)
	{
		bool foundInlineEdge = false;
		Vertex p1, p2, p3, p4;
		Vec2d p1b, p1e, p2b, p2e;

		for(it = singles.begin(); it != singles.end(); ++it)
		{
			if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");

			Vec2d midOfSingle;

			p1= getBondBegin(toProcess[i]);
			p2= getBondEnd(toProcess[i]);
			p3= getBondBegin((*it));
			p4= getBondEnd((*it));

			p1b = getVertexPos(p1);
			p1e = getVertexPos(p2);
			p2b = getVertexPos(p3);
			p2e = getVertexPos(p4);

			midOfSingle.middle(p2b, p2e);

			if(Algebra::SegmentsOnSameLine(vars, p1b, p1e, p2b, p2e) && 
				(Vec2d::distance(midOfSingle, p1b) + Vec2d::distance(midOfSingle, p1e)) < Vec2d::distance(p2b, p2e))
			{
				foundIt = it;
				foundInlineEdge = true;
				break;
			}
		}
		if(foundInlineEdge)
		{
			removeBond(*foundIt);
			singles.erase(foundIt);

			if(Vec2d::distance(p1b, p2b) < Vec2d::distance(p1e, p2b))
			{
				if(Vec2d::distance(p1b, p2b) > toSmallErr)
					addBond(p1, p3);
				
				if(Vec2d::distance(p1e, p2e) > toSmallErr)
					addBond(p2, p4);
				
			}
			else
			{
				if(Vec2d::distance(p1b, p2e) > toSmallErr)
					addBond(p1, p4);
				if(Vec2d::distance(p1e, p2b) > toSmallErr)
					addBond(p2, p3);
			}
			
			setBondType(toProcess[i], BT_TRIPLE);
		}


	}
}

void Skeleton::_reconnectBonds( Vertex from, Vertex to )
{
   std::deque<Vertex> neighbours;
   SkeletonGraph::adjacency_iterator b, e;
   b = _g.adjacencyBegin(from);
   e = _g.adjacencyEnd(from);
   neighbours.assign(b, e);

   for (size_t i = 0; i < neighbours.size(); i++)
   {
      Vertex v = neighbours[i];
      Edge e = _g.getEdge(from, v).first;
      BondType t = _g.getEdgeBond(e).type;
      _g.removeEdge(e);

      if (v == to)
         continue;
      
      addBond(v, to, t);
   }
}

bool Skeleton::_checkMidBonds( Vertex from, Vertex to )
{
   std::deque<Vertex> neighbours;
   SkeletonGraph::adjacency_iterator b, e;
   b = _g.adjacencyBegin(from);
   e = _g.adjacencyEnd(from);
   neighbours.assign(b, e);
   bool ret = false;

   for (size_t i = 0; i < neighbours.size(); i++)
   {
      Vertex v = neighbours[i];
      Edge e = _g.getEdge(from, v).first;

      if (v == to)
         continue;
      
      ret = true;
   }
   return ret;
}

void Skeleton::_reconnectBondsRWT( Vertex from, Vertex to, BondType new_t)
{
   std::deque<Vertex> neighbours;
   SkeletonGraph::adjacency_iterator b, e;
   b = _g.adjacencyBegin(from);
   e = _g.adjacencyEnd(from);
   neighbours.assign(b, e);

   for (size_t i = 0; i < neighbours.size(); i++)
   {
      Vertex v = neighbours[i];
      Edge e = _g.getEdge(from, v).first;
      _g.removeEdge(e);

      if (v == to)
         continue;
      
      addBond(v, to, new_t);
   }
}

double Skeleton::_avgEdgeLendth (const Vertex &v, int &nnei)
{
   std::deque<Vertex> neighbors;
   SkeletonGraph::adjacency_iterator b, e;
   b = _g.adjacencyBegin(v);
   e = _g.adjacencyEnd(v);
   neighbors.assign(b, e);

   nnei = (int)neighbors.size();

   if (neighbors.size() < 1)
      return 0;

   double avg = 0;

   for (size_t i = 0; i < neighbors.size(); i++)
   {
      Edge e = _g.getEdge(v, neighbors[i]).first;
      avg += _g.getEdgeBond(e).length;
   }
   return avg / neighbors.size();
}

void Skeleton::_joinVertices(double eps)
{
	logEnterFunction();
   std::deque<std::deque<Vertex> > nearVertices;
   std::deque<size_t> join_ind;

#ifdef DEBUG
   LPRINT(0, "joining vertices, eps = %lf", eps);
#endif /* DEBUG */

   for(SkeletonGraph::vertex_iterator begin = _g.vertexBegin(), end = _g.vertexEnd();
       begin != end; begin = end)
      for (SkeletonGraph::vertex_descriptor v;
           begin != end ? (v = *begin, true):false;
           ++begin)
   {
      Vec2d v_pos = _g.getVertexPosition(v);
      int v_nnei;
      double v_avg_edge_len = _avgEdgeLendth(v, v_nnei);

      for (size_t i = 0; i < nearVertices.size(); i++)
      {
         for (size_t j = 0; j < nearVertices[i].size(); j++)
         {
            const Vertex &nei = nearVertices[i][j];
            int nei_nnei;
            double nei_avg_edge_len = _avgEdgeLendth(nei, nei_nnei);
            double thresh = eps * (nei_nnei * nei_avg_edge_len + v_nnei * v_avg_edge_len) /
               (v_nnei + nei_nnei);

            if (v_nnei + nei_nnei > 0 &&
                Vec2d::distance(v_pos, _g.getVertexPosition(nei)) < thresh)
            {
               join_ind.push_back(i);
               break;
            }
         }
      }

      if (join_ind.size() == 0)
      {
         nearVertices.push_back(std::deque<Vertex>(1, v));
      }
      else
      {
         size_t first = join_ind[0];
         nearVertices[first].push_back(v);

         for (size_t i = join_ind.size() - 1; i >= 1; i--)
         {
            size_t ii = join_ind[i];
            nearVertices[first].insert(nearVertices[first].end(),
                                       nearVertices[ii].begin(),
                                       nearVertices[ii].end());
            nearVertices.erase(nearVertices.begin() + ii);
         }
      }
      join_ind.clear();
   }

   for (size_t i = 0; i < nearVertices.size(); i++)
   {
      size_t size = nearVertices[i].size();
      if (size == 1)
         continue;
      
      Vec2d newPos;
      for (size_t j = 0; j < size; j++)
         newPos.add(_g.getVertexPosition(nearVertices[i][j]));
      newPos.scale(1.0 / size);

      Vertex newVertex = addVertex(newPos);

      for (size_t j = 0; j < size; j++)
      {
         _reconnectBonds(nearVertices[i][j], newVertex);
         _g.removeVertex(nearVertices[i][j]);
      }
   }
}

bool Skeleton::_isSegmentIntersectedByEdge(const Settings& vars, Vec2d &b, Vec2d &e, std::deque<Edge> edges)
{
	std::deque<Edge>::iterator it;

	for(it=edges.begin();it != edges.end(); ++it)
	{
		Edge edge = *it;
		Vec2d p1 = getVertexPos(getBondBegin(edge));
		Vec2d p2 = getVertexPos(getBondEnd(edge));
		Vec2d intersection = Algebra::linesIntersection(vars, b, e, p1, p2);

		// TODO: check if intersection point is in segment p1, p2

		Vec2d diff1, diff2;
		diff1.diff(p1, intersection);
		diff2.diff(p2, intersection);
		double dotVal = Vec2d::dot(diff1, diff2);
		if( dotVal > 0)
			continue;
		
		double maxX = b.x > e.x ? b.x : e.x;
		double minX = b.x < e.x ? b.x : e.x;
		double maxY = b.y > e.y ? b.y : e.y;
		double minY = b.y < e.y ? b.y : e.y;

		if(intersection.x < maxX + 1 && intersection.x > minX-1 &&
			intersection.y < maxY + 1 && intersection.y > minY -1)
			return true;
	}
	return false;
}

void Skeleton::_connectBridgedBonds(const Settings& vars)
{
	logEnterFunction();

	std::vector<double> kFactor;
	std::vector<std::vector<Edge> > edge_groups_k;
	//group all parallel edges by similar factors
   for(SkeletonGraph::edge_iterator begin = _g.edgeBegin(), end = _g.edgeEnd();
       begin != end;
       begin = end)
      for(SkeletonGraph::edge_descriptor edge;
          begin != end ? (edge = *begin, true) : false;
          ++begin)
	{
		Bond f = _g.getEdgeBond(edge);
		Vec2d p1 = getVertexPos(getBondBegin(edge));
		Vec2d p2 = getVertexPos(getBondEnd(edge));
		double slope = Algebra::slope(p1, p2);
		if(f.type == BT_SINGLE)
		{
			bool found_kFactor = false;
			for(size_t i=0 ; i < kFactor.size() ; i++)
			{
				if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");

				if(fabs(slope - kFactor[i]) < vars.skeleton.SlopeFact1 ||
					fabs(fabs(slope - kFactor[i]) - PI)< vars.skeleton.SlopeFact2)
				{
					edge_groups_k[i].push_back(edge);
					found_kFactor = true;
					break;
				}
			}

			if(!found_kFactor)
			{
				edge_groups_k.push_back(std::vector<Edge>());
				edge_groups_k[edge_groups_k.size() - 1].push_back(edge);
				kFactor.push_back(slope);
			}
		}
	}
	getLogExt().append("Group size of edges which could bridge:", edge_groups_k.size());
	std::deque<std::pair<Edge, Edge> > edges_to_connect;

	//check edges to be connected
	for(size_t i=0;i<edge_groups_k.size();i++)
	{
		size_t gr_count = edge_groups_k[i].size();
		if( gr_count == 1)
			continue;
		std::deque<Edge> otherE;
		for(size_t k=0;k<edge_groups_k.size();k++)
		{
			if(k != i)
				otherE.insert(otherE.end(), edge_groups_k[k].begin(), edge_groups_k[k].end());
		}
		for(int k=0;k<gr_count;k++)
		{
			Vec2d p1 = getVertexPos(getBondBegin(edge_groups_k[i][k]));
			Vec2d p2 = getVertexPos(getBondEnd(edge_groups_k[i][k]));

			for(int l = k + 1;l<gr_count;l++)
			{
				if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");

				Vec2d sp1 = getVertexPos(getBondBegin(edge_groups_k[i][l]));
				Vec2d sp2 = getVertexPos(getBondEnd(edge_groups_k[i][l]));

				double d1 = Algebra::distance2segment(p1, sp1, sp2);
				double d2 = Algebra::distance2segment(p2, sp1, sp2);

				double min = d1 < d2 ? d1 : d2;

				double LineS = vars.dynamic.LineThickness;
				double blockS = LineS * vars.skeleton.ConnectBlockS;

				Vec2d nearP1, nearP2;
				if(d1 < d2)
					nearP1 = p1;
				else
					nearP1 = p2;

				double dd1 = Vec2d::distance<double>(nearP1, sp1);
				double dd2 = Vec2d::distance<double>(nearP1, sp2);
				
				if(dd1 < dd2)
					nearP2 = sp1;
				else
					nearP2 = sp2;

				if(min < blockS && min > vars.skeleton.ConnectFactor * LineS && 
					Algebra::SegmentsOnSameLine(vars, p1, p2, sp1, sp2) &&
					_isSegmentIntersectedByEdge(vars, nearP1, nearP2, otherE))
				{
					getLogExt().appendText("Candidate edges for bridge connections");
					getLogExt().append("Distance", min);
					edges_to_connect.push_back(std::pair<Edge, Edge>(edge_groups_k[i][l], edge_groups_k[i][k]));
				}
			}
		
		}
	}

	//connect edges
	std::deque<std::pair<Edge, Edge> >::iterator eit;
	std::vector<Vertex> verticies_to_remove;

	for(eit = edges_to_connect.begin(); eit != edges_to_connect.end(); ++eit)
	{
		Edge e1 = (*eit).first,
			e2 = (*eit).second;
		Vertex v1, v2, v3, v4;
		Vec2d p1 = getVertexPos(getBondBegin(e1));
		Vec2d p2 = getVertexPos(getBondEnd(e1));

		Vec2d sp1 = getVertexPos(getBondBegin(e2));
		Vec2d sp2 = getVertexPos(getBondEnd(e2));

		double d1 = Algebra::distance2segment(p1, sp1, sp2);
		double d2 = Algebra::distance2segment(p2, sp1, sp2);

		if(d1 < d2)
		{
			v1 = getBondBegin(e1);
			v3 = getBondEnd(e1);
			if(Vec2d::distance(p1, sp1) < Vec2d::distance(p1, sp2))
			{
				v2 = getBondBegin(e2);
				v4 = getBondEnd(e2);
			}
			else
			{
				v2 = getBondEnd(e2);
				v4 = getBondBegin(e2);
			}
		}
		else
		{
			v1 = getBondEnd(e1);
			v3 = getBondBegin(e1);
			if(Vec2d::distance(p2, sp1) < Vec2d::distance(p2, sp2))
			{
				v2 = getBondBegin(e2);
				v4 = getBondEnd(e2);
			}
			else
			{
				v2 = getBondEnd(e2);
				v4 = getBondBegin(e2);
			}
		}

		// ugly check for already removed verticies
		if (std::find(verticies_to_remove.begin(), verticies_to_remove.end(), v1) != verticies_to_remove.end() ||
			std::find(verticies_to_remove.begin(), verticies_to_remove.end(), v2) != verticies_to_remove.end() ||
			std::find(verticies_to_remove.begin(), verticies_to_remove.end(), v3) != verticies_to_remove.end() ||
			std::find(verticies_to_remove.begin(), verticies_to_remove.end(), v4) != verticies_to_remove.end())
			continue;

		if(_g.getDegree(v1) > 1 ||
			_g.getDegree(v2) > 1 )
		{
			continue;
		}

		addBond(v3, v4, BT_SINGLE);
		
		verticies_to_remove.push_back(v1);
		verticies_to_remove.push_back(v2);
	}

	for (size_t u = 0; u < verticies_to_remove.size(); u++)
	{
// The clear function for vertex was needed by boost. Now clearing is implemented in removeVertex.
//      _g.clearVertex(verticies_to_remove[u]); 
      _g.removeVertex(verticies_to_remove[u]);
   }
}

void Skeleton::modifyGraph(Settings& vars)
{
	logEnterFunction();

   //RecognitionSettings &rs = getSettings();

	_parLinesEps = vars.estimation.ParLinesEps;

   recalcAvgBondLength();

   if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");

   getLogExt().appendSkeleton(vars, "init", _g);

   _joinVertices(vars.skeleton.JoinVerticiesConst);

   if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");

   recalcAvgBondLength();

   _vertices_big_degree.clear();

   if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");
   
   for(SkeletonGraph::vertex_iterator begin = _g.vertexBegin(), end = _g.vertexEnd();
       begin != end; begin = end)
      for (SkeletonGraph::vertex_descriptor v;
           begin != end ? (v = *begin, true):false;
           ++begin)
   {
      if (_g.getDegree(v) > 2)
      {
         Vec2d pos = _g.getVertexPosition(v);
         _vertices_big_degree.push_back(pos);
      }
   }

   getLogExt().appendSkeleton(vars, "after join verticies", _g);

   while (_dissolveShortEdges(vars.skeleton.DissolveConst))
   {
	   if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");
   }

   getLogExt().appendSkeleton(vars, "after dissolve short edges", _g);

   while (_dissolveIntermediateVertices(vars))
   {
	   if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");
   }

   recalcAvgBondLength();

    getLogExt().appendSkeleton(vars, "after dissolve intermediate vertrices", _g);

    recalcAvgBondLength();

    _findMultiple(vars);

	if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");
    
	getLogExt().appendSkeleton(vars, "after find multiple", _g);

	_connectBridgedBonds(vars);

	if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");

	getLogExt().appendSkeleton(vars, "after connecting bridge bonds", _g);

    recalcAvgBondLength();
   
	while (_dissolveShortEdges(vars.skeleton.Dissolve2Const))
	{
		if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");
	}

	getLogExt().appendSkeleton(vars, "after dissolve edges 2", _g);

    recalcAvgBondLength();

	_joinVertices(vars.skeleton.Join2Const);
	_joinVertices(vars.skeleton.Join3Const);

    //Shrinking short bonds (dots)
    std::vector<Edge> edgesToRemove;
   for(SkeletonGraph::edge_iterator begin = _g.edgeBegin(), end = _g.edgeEnd();
       begin != end;
       begin = end)
      for(SkeletonGraph::edge_descriptor edge;
          begin != end ? (edge = *begin, true) : false;
          ++begin)
    {
       const Vertex &beg = edge.m_source;
       const Vertex &end = edge.m_target;
       Vec2d beg_pos = _g.getVertexPosition(beg);
       const Vec2d &end_pos = _g.getVertexPosition(end);
       if (_g.getDegree(beg) == 1 && _g.getDegree(end) == 1 &&
           _g.getEdgeBond(edge).length < vars.skeleton.ShrinkEps * _avg_bond_length)
       {
          beg_pos.add(end_pos);
          beg_pos.scale(0.5); // average
          addVertex(beg_pos);
          edgesToRemove.push_back(edge);
       }
    }
    for(Edge e: edgesToRemove)
    {
       Vertex beg = e.m_source;
       Vertex end = e.m_target;
       _g.removeEdge(e);
       _g.removeVertex(beg);
       _g.removeVertex(end);
    }


	getLogExt().appendSkeleton(vars, "after shrinking", _g);


   // ---------------------------------------------------------
	   // analyze graph for vertex mess
	Image temp(vars.general.ImageWidth, vars.general.ImageHeight);

	double distTresh = vars.dynamic.CapitalHeight;

	   if (distTresh > _avg_bond_length/vars.skeleton.DistTreshLimFactor)
		   distTresh = _avg_bond_length/vars.skeleton.DistTreshLimFactor;

	   std::vector<Skeleton::Edge> bad_edges;
      for(SkeletonGraph::edge_iterator begin = _g.edgeBegin(), end = _g.edgeEnd();
          begin != end;
          begin = end)
         for(SkeletonGraph::edge_descriptor e;
             begin != end ? (e = *begin, true) : false;
             ++begin)
	   {
		   const Skeleton::Vertex &beg = e.m_source;
		   const Skeleton::Vertex &end = e.m_target;
		   Vec2d pos_beg = _g.getVertexPosition(beg);
		   Vec2d pos_end = _g.getVertexPosition(end);
		   double d = Vec2d::distance(pos_beg, pos_end);
		   if (d < distTresh)
		   {
            for(SkeletonGraph::vertex_iterator range_begin = _g.vertexBegin(), range_end = _g.vertexEnd();
                range_begin != range_end; range_begin = range_end)
               for (SkeletonGraph::vertex_descriptor v;
                    range_begin != range_end ? (v = *range_begin, true):false;
                    ++range_begin)
			   {
				   if (vars.checkTimeLimit()) throw ImagoException("Timelimit exceeded");

				   if (v != beg && v != end)
				   {
					   Vec2d pos = _g.getVertexPosition(v);
					   if (Vec2i::distance(pos,pos_beg) < distTresh &&
						   Vec2i::distance(pos,pos_end) < distTresh)
					   {
						   if (getLogExt().loggingEnabled())
						   {
							   ImageDrawUtils::putCircle(temp, round(pos.x), round(pos.y), 2, 0);							   
							   ImageDrawUtils::putLineSegment(temp, pos_beg, pos_end, 0);
						   }
						   bad_edges.push_back(e);
						   break;
					   }
				   }
			   }			   
		   }
	   }

      for(Skeleton::Edge e: bad_edges)
		{
		   Skeleton::Vertex beg = e.m_source;
		   Skeleton::Vertex end = e.m_target;
		   _g.removeEdge(e);
		   if (_g.getDegree(beg) == 0)
			   _g.removeVertex(beg);
		   if (_g.getDegree(end) == 0)
			   _g.removeVertex(end);
		}

	   getLogExt().appendImage("Suspicious edges", temp);

	   // ---------------------------------------------------------


	   vars.dynamic.AvgBondLength = _avg_bond_length;
   
   for(SkeletonGraph::edge_iterator begin = _g.edgeBegin(), end = _g.edgeEnd();
       begin != end;
       begin = end)
      for(SkeletonGraph::edge_descriptor edge;
          begin != end ? (edge = *begin, true) : false;
          ++begin)
   {
      const Vertex &beg = edge.m_source;
      const Vertex &end = edge.m_target;
      Vec2d beg_pos = _g.getVertexPosition(beg);
      const Vec2d &end_pos = _g.getVertexPosition(end);
#ifdef DEBUG
      printf("(%lf, %lf) - (%lf, %lf) | %lf\n", beg_pos.x, beg_pos.y, end_pos.x, end_pos.y, _g.getEdgeBond(edge).length);
#endif
   }

}


void Skeleton::deleteBadTriangles( double eps )
{
   std::set<Edge> edges_to_delete;
   std::set<Vertex> vertices_to_delete;
   
   for(SkeletonGraph::edge_iterator begin = _g.edgeBegin(), end = _g.edgeEnd();
       begin != end;
       begin = end)
      for(SkeletonGraph::edge_descriptor edge;
          begin != end ? (edge = *begin, true) : false;
          ++begin)
   {
      if (edges_to_delete.find(edge) != edges_to_delete.end())
         continue;
      
      Vertex beg = edge.m_source;
      Vertex end = edge.m_target;

      SkeletonGraph::adjacency_iterator b1, e1, b2, e2;
      std::set<Vertex> intrsect, beg_neigh, end_neigh;
      b1 = _g.adjacencyBegin(beg);
      e1 = _g.adjacencyEnd(beg);
      b2 = _g.adjacencyBegin(end);
      e2 = _g.adjacencyEnd(end);
      beg_neigh.insert(b1, e1);
      end_neigh.insert(b2, e2);
      std::set_intersection(beg_neigh.begin(), beg_neigh.end(), end_neigh.begin(), end_neigh.end(), std::inserter(intrsect, intrsect.begin()));
      
      for(Vertex v: intrsect)
      {
         if (v == beg || v == end || vertices_to_delete.find(v) != vertices_to_delete.end())
            continue;
         
         double l_b, l_e, l_be;
         //add asserts
         l_b = _g.getEdgeBond(_g.getEdge(v, beg).first).length;
         l_e = _g.getEdgeBond(_g.getEdge(v, end).first).length;
         l_be = _g.getEdgeBond(edge).length;
         if (fabs(l_b - (l_e + l_be)) < eps) //v - b
         {
            if (_g.getDegree(end) == 2)
            {
               edges_to_delete.insert(edge);
               edges_to_delete.insert(_g.getEdge(v, end).first);
               vertices_to_delete.insert(end);
               setBondType(_g.getEdge(v, beg).first, BT_SINGLE_UP);
            }
            else
               edges_to_delete.insert(_g.getEdge(v, beg).first);
            //v - e
            //edge
         }
         else if (fabs(l_e - (l_b + l_be)) < eps) //v - e
         {
            //v - b
            //edge
            if (_g.getDegree(beg) == 2)
            {
               edges_to_delete.insert(edge);
               edges_to_delete.insert(_g.getEdge(v, beg).first);
               vertices_to_delete.insert(beg);
               setBondType(_g.getEdge(v, end).first, BT_SINGLE_UP);
            }
            else
               edges_to_delete.insert(_g.getEdge(v, end).first);
         }
         else if (fabs(l_be - (l_b + l_e)) < eps) //edge
         {
            //v - e
            //v - b
            if (_g.getDegree(v) == 2)
            {
               edges_to_delete.insert(_g.getEdge(v, end).first);
               edges_to_delete.insert(_g.getEdge(v, beg).first);
               vertices_to_delete.insert(v);
               setBondType(edge, BT_SINGLE_UP);               
            }
            else
               edges_to_delete.insert(edge);
         }
      }
   }

   for(Edge edge: edges_to_delete)
      _g.removeEdge(edge);
   for(Vertex v: vertices_to_delete)
      _g.removeVertex(v);
}

void Skeleton::setBondType( Edge e, BondType t )
{
   Bond b = _g.getEdgeBond(e);

   b.type = t;

   _g.setEdgeBond(e, b);
}

BondType Skeleton::getBondType( const Edge &e ) const
{
   return _g.getEdgeBond(e).type;
}

void Skeleton::reverseEdge( const Edge &e )
{
   BondType type = getBondType(e);
   Vertex v1 = getBondBegin(e), v2 = getBondEnd(e);

   removeBond(v1, v2);
   addBond(v2, v1, type);
}

Skeleton::~Skeleton()
{
}

void Skeleton::clear()
{
   _g.clear();
   _warnings = 0;
   _dissolvings = 0;
}

