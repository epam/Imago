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
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/iteration_macros.hpp"
#include "boost/foreach.hpp"

#include "comdef.h"
#include "algebra.h"
#include "current_session.h"
#include "recognition_settings.h"
#include "skeleton.h"
#include "double_bond_maker.h"
#include "triple_bond_maker.h"
#include "multiple_bond_checker.h"
#include "image_draw_utils.h"
#include "image_utils.h"

using namespace imago;

Skeleton::Skeleton()
{
   _multiBondErr = 0.3;//0.175;
}

void Skeleton::setInitialAvgBondLength( double avg_length )
{
   // DP: NOT USING WHAT IS SET HERE
   RecognitionSettings &rs = getSettings();

   _avg_bond_length = avg_length;

   double mult = 0.1;

   //TODO: Stupid temporary fix. We should think about it carefully.
   if (_avg_bond_length < 20)
      mult = 0.3;
   else if (_avg_bond_length < 85)
      mult = 0.175;
   else if (_avg_bond_length < 100)
      mult = 0.15; //TODO: handwriting
   else
      mult = 0.3; //TODO: handwriting

   rs.set("AddVertexEps", mult * _avg_bond_length);
   _addVertexEps = rs["AddVertexEps"];
}

void Skeleton::recalcAvgBondLength()
{
   int bonds_num = num_edges(_g);

   if (bonds_num == 0)
      return;

   _avg_bond_length = 0;
   _min_bond_length = 1000;

   BGL_FORALL_EDGES(e, _g, SkeletonGraph)
   {
      double len = (boost::get(boost::edge_type, _g, e)).length;
      _avg_bond_length += len;
      if (_min_bond_length > len)
         _min_bond_length = len;
   }

   _avg_bond_length /= bonds_num;
   
   /*
   double mult;
   //TODO: Desparate copy-paste from above
   if (_avg_bond_length < 20)
      mult = 0.3;
   else if (_avg_bond_length < 85)
      mult = 0.27;
   else if (_avg_bond_length < 100)
      mult = 0.23; //TODO: handwriting
   else
      mult = 0.3; //TODO: handwriting

   RecognitionSettings &rs = getSettings();
   rs.set("AddVertexEps", mult * _avg_bond_length);
   _addVertexEps = rs["AddVertexEps"];*/
}

Skeleton::Edge Skeleton::addBond( Vertex &v1, Vertex &v2, BondType type )
{
   //TODO: Check if edge was not added
   std::pair<Edge, bool> p;

   p = boost::edge(v1, v2, _g);
   if (p.second)
   {
      //Graph already has edge
      if (getSettings()["DebugSession"])
         LPRINT(0, "WARNING: Already has edge (%x, %x)", v1, v2);
      return p.first;
   }

   p = boost::add_edge(v1, v2, _g);

   Vec2d begin = boost::get(boost::vertex_pos, _g, v1),
         end = boost::get(boost::vertex_pos, _g, v2);

   if (!p.second)
   {
      throw LogicException("Can`t add bond (%lf, %lf) (%lf, %lf)", begin.x,
         begin.y, end.x, end.y);
   }

   Edge e = p.first;

   int dx = end.x - begin.x,
       dy = end.y - begin.y;
   double k = 0;

   if (dx == 0)
      k = PI_2;
   else
   {
      double angle = atan((double) dy / dx);
      k = angle;
   }

   Bond b(Vec2d::distance(begin, end), k, type);

   boost::put(boost::edge_type, _g, e, b);

   return e;
}

Skeleton::Edge Skeleton::addBond( const Vec2d &begin, const Vec2d &end,
                                  BondType type )
{
   Vertex v1 = addVertex(begin), v2 = addVertex(end);

   return addBond(v1, v2, type);
}

void Skeleton::removeBond( Vertex &v1, Vertex &v2 )
{
   boost::remove_edge(v1, v2, _g);
}

void Skeleton::removeBond( Edge &e )
{
   boost::remove_edge(e, _g);
}

Skeleton::Vertex Skeleton::addVertex( const Vec2d &pos )
{
   Vertex v = boost::add_vertex(_g);

   boost::put(boost::vertex_pos, _g, v, pos);

   return v;
}

Vec2d Skeleton::getVertexPos( const Vertex &v1 ) const
{
   return boost::get(boost::vertex_pos, _g, v1);
}

int Skeleton::getVerticesCount() const
{
   return boost::num_vertices(_g);
}

int Skeleton::getEdgesCount() const
{
   return boost::num_edges(_g);
}

Bond Skeleton::getBondInfo( const Edge &e ) const
{
   return boost::get(boost::edge_type, _g, e);
}

Skeleton::Vertex Skeleton::getBondBegin( const Skeleton::Edge &e ) const
{
   return boost::source(e, _g);
}

Skeleton::Vertex Skeleton::getBondEnd( const Skeleton::Edge &e ) const
{
   return boost::target(e, _g);
}

void Skeleton::_repairBroken()
{
   double coef;
   recalcAvgBondLength();

   //TODO: Tuning here?
   double toSmallErr;
   if (_avg_bond_length > 115)
      toSmallErr = 0.06;
   else if (_avg_bond_length > 85)
      toSmallErr = 0.13;
   else
      toSmallErr = 0.153;

   std::deque<Vertex> toRemove;

   BGL_FORALL_VERTICES(v, _g, SkeletonGraph)
   {
      if (boost::degree(v, _g) != 2)
         continue;
      
      boost::graph_traits<SkeletonGraph>::adjacency_iterator
         vi = boost::adjacent_vertices(v, _g).first;
      Vertex x, y;
      x = *vi;
      y = *(++vi);
      Edge e1, e2;
      Bond e1b, e2b;
      e1 = boost::edge(x, v, _g).first;
      e2 = boost::edge(v, y, _g).first;
      e1b = getBondInfo(e1);
      e2b = getBondInfo(e2);

      //changed in "handwriting" to 0.37
      if (e1b.length < toSmallErr * _avg_bond_length &&
          e2b.length < toSmallErr * _avg_bond_length)
         continue;

      coef = 1.0;
      if (e1b.length < 3 * toSmallErr * _avg_bond_length ||
          e2b.length < 3 * toSmallErr * _avg_bond_length)
         coef = 2.7;

      Vec2d x_pos, y_pos, v_pos;
      x_pos = boost::get(boost::vertex_pos, _g, x);
      y_pos = boost::get(boost::vertex_pos, _g, y);
      v_pos = boost::get(boost::vertex_pos, _g, v);
      Vec2d v1, v2;
      v1.diff(x_pos, v_pos);
      v2.diff(y_pos, v_pos);

      bool found = false;
      try
      {
         double angle = Vec2d::angle(v1, v2);
         if (angle > PI - coef * 0.2) // _parLinesEps)
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

         boost::remove_edge(e, _g);
         _reconnectBonds(v, to);
         toRemove.push_back(v);
      }
   }

   BOOST_FOREACH(Vertex v, toRemove)
      boost::remove_vertex(v, _g);
}

bool Skeleton::_isEqualDirection( const Edge &first, const Edge &second ) const
{
   Bond f = boost::get(boost::edge_type, _g, first),
        s = boost::get(boost::edge_type, _g, second);

   return (fabs(f.k - s.k) < _parLinesEps);
}

bool Skeleton::_isEqualDirection( const Vertex &b1,const Vertex &e1,const Vertex &b2,const Vertex &e2)  const
{
#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))
   Vec2d begin1 = boost::get(boost::vertex_pos, _g, b1),
         end1 = boost::get(boost::vertex_pos, _g, e1);

   Vec2d begin2 = boost::get(boost::vertex_pos, _g, b2),
         end2 = boost::get(boost::vertex_pos, _g, e2);
   
   int dx1 = end1.x - begin1.x,
       dy1 = end1.y - begin1.y;
   double k1 = 0;

   if (dx1 == 0)
      k1 = PI_2;
   else
   {
      double angle1 = atan((double) dy1 / dx1);
      k1 = angle1;
   }

   int dx2 = end2.x - begin2.x,
   dy2 = end2.y - begin2.y;
   double k2 = 0;

   if (dx2 == 0)
      k2 = PI_2;
   else
   {
      double angle2 = atan((double) dy2 / dx2);
      k2 = angle2;
   }

   return((fabs(k1 - k2) < _parLinesEps) && (sign(dx1) == sign(dx2)));
}


bool Skeleton::_isParallel( const Edge &first, const Edge &second ) const
{
   Bond f = boost::get(boost::edge_type, _g, first),
        s = boost::get(boost::edge_type, _g, second);

   return (fabs(f.k - s.k) < _parLinesEps ||
                    fabs(fabs(f.k - s.k) - PI) < _parLinesEps);
}

bool Skeleton::_dissolveShortEdges (double coeff, const bool has2nb)
{
   std::vector<Edge> toProcess;
   boost::graph_traits<SkeletonGraph>::edge_iterator ei, ei_e;
   boost::tie(ei, ei_e) = boost::edges(_g);

   for (; ei != ei_e; ++ei)
   {
      const Edge &edge = *ei;
      const Vertex &beg = boost::source(edge, _g);
      const Vertex &end = boost::target(edge, _g);

      double edge_len = boost::get(boost::edge_type, _g, edge).length;
      double max_edge_beg = 0, max_edge_end = 0;
	  bool  pb_e = false, pb_b = false;


      // find the longest edge going from the beginning of our edge
      {
		 bool state_conected_b = false;
         std::deque<Vertex> neighbors_b;
         boost::graph_traits<SkeletonGraph>::adjacency_iterator b_b, e_b;
         boost::tie(b_b, e_b) = boost::adjacent_vertices(beg, _g);
         neighbors_b.assign(b_b, e_b);

		 if(neighbors_b.size() > 1)
			 for (int i = 0; i < (int)neighbors_b.size(); i++)
			 {
				 if(neighbors_b[i] != end)
				 {
					 Edge ee = boost::edge(neighbors_b[i], beg, _g).first; // order is significant for taking edge with eqval direction
					 double len = boost::get(boost::edge_type, _g, ee).length;
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
         boost::graph_traits<SkeletonGraph>::adjacency_iterator b_e, e_e;
         boost::tie(b_e, e_e) = boost::adjacent_vertices(end, _g);
         neighbors_e.assign(b_e, e_e);
		 if(neighbors_e.size() > 1)
			 for (int i = 0; i < (int)neighbors_e.size(); i++)
			 {
				 if(neighbors_e[i] != beg)
				 {
					 Edge ee = boost::edge(neighbors_e[i], end, _g).first; // order is significant for taking edge with eqval direction
					 double len = boost::get(boost::edge_type, _g, ee).length;

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
				  LPRINT(0, "dissolving edge len: %.2lf, max_edge_beg: %.2lf, max_edge_end: %.2lf",
					  edge_len, max_edge_beg, max_edge_end);
				  // dissolve the edge
				  if (max_edge_end < max_edge_beg)
				  {          
					  _reconnectBonds(end, beg);
					  boost::remove_vertex(end, _g);
				  }
				  else
				  {
					  _reconnectBonds(beg, end);
					  boost::remove_vertex(beg, _g);
				  }
				  return true;
			  }
			  else
			  {
				  /*
				  if ((edge_len < max_edge_beg * (coeff) ||
				  edge_len < max_edge_end * (coeff)) &&
				  edge_len < _avg_bond_length * coeff)
				  {
					  LPRINT(0, "dissolving edge len: %.2lf, max_edge_beg: %.2lf, max_edge_end: %.2lf",
						  edge_len, max_edge_beg, max_edge_end);
					  // dissolve the edge
					  if (max_edge_end < max_edge_beg)
					  {          
						  _reconnectBonds(end, beg);
						  boost::remove_vertex(end, _g);
					  }
					  else
					  {
						  _reconnectBonds(beg, end);
						  boost::remove_vertex(beg, _g);
					  }
					  return true;

				  }
				  */

				  if(( max_edge_end < _avg_bond_length * coeff) &&
				  (edge_len*(coeff) > max_edge_end) && max_edge_end != 0.0)
				  {
					  bool ret = false;
					   if(neighbors_e.size() > 1 && !state_conected_e)
						   for (int i = 0; i < (int)neighbors_e.size(); i++)
						   {
							   if(neighbors_e[i] != beg)
							   {
								   _reconnectBonds(neighbors_e[i], end);
								   boost::remove_vertex(neighbors_e[i], _g);
								   setBondType(*ei, SINGLE_UP);
								   ret = true;
							   }
						   }
					  return ret;
				  }

				  if(( max_edge_beg < _avg_bond_length * coeff) &&
				  (edge_len*(coeff) > max_edge_beg) && max_edge_beg != 0.0)
				  {

					  bool ret = false;
					   if(neighbors_b.size() > 1 && !state_conected_b)
						   for (int i = 0; i < (int)neighbors_b.size(); i++)
						   {
							   if(neighbors_b[i] != end)
							   {
								   _reconnectBonds(neighbors_b[i], beg);
								   boost::remove_vertex(neighbors_b[i], _g);
								   setBondType(*ei, SINGLE_UP);
								   ret = true;
							   }
						   }
					  return ret;
				  }
			  }
			  if(edge_len < _avg_bond_length * (coeff))
			  {
				  BondType type = getBondType(edge);
				  if(pb_e && !state_conected_b && type == SINGLE)
				  {
					  _reconnectBonds(beg, end);
					  boost::remove_vertex(beg, _g);
					  return true;
					  
				  }
				  if(pb_b && !state_conected_e && type == SINGLE)
				  {
					  _reconnectBonds(end, beg);
					  boost::remove_vertex(end, _g);
					  return true;
				  }
			  }
		  }
		  else
		  {
 			  if (edge_len < max_edge_beg * coeff ||
				  edge_len < max_edge_end * coeff)
			  {
				 LPRINT(0, "dissolving edge len: %.2lf, max_edge_beg: %.2lf, max_edge_end: %.2lf",
						edge_len, max_edge_beg, max_edge_end);
				 // dissolve the edge
				 if (max_edge_end < max_edge_beg)
				 {
					_reconnectBonds(end, beg);
					boost::remove_vertex(end, _g);
				 }
				 else
				 {
					_reconnectBonds(beg, end);
					boost::remove_vertex(beg, _g);
				 }
				 return true;
			  }
		  }
	  }

   }
   return false;
}

bool Skeleton::_dissolveIntermediateVertices ()
{
   std::set<Vertex> vertices;
   boost::graph_traits<SkeletonGraph>::vertex_iterator vi, vi_end;
   boost::tie(vi, vi_end) = boost::vertices(_g);

   Vertex to_dissolve;
   double min_err = 10000;
   
   for (; vi != vi_end; ++vi)
   {
      const Vertex &vertex = *vi;

      std::deque<Vertex> neighbors;
      boost::graph_traits<SkeletonGraph>::adjacency_iterator b, e;
      boost::tie(b, e) = boost::adjacent_vertices(vertex, _g);
      neighbors.assign(b, e);

      if (neighbors.size() != 2)
         continue;

      //TODO: Need something more accurate
/*
      // DP: will learn how to use STL iterators another day
      int k;
      Vec2d vpos = boost::get(boost::vertex_pos, _g, vertex);
      for (k = 0; k < _vertices_big_degree.size(); k++)
      {
         if (Vec2d::distance(_vertices_big_degree[k], vpos) < 0.0001)
            break;
      }

      if (k != _vertices_big_degree.size())
         continue;
*/
      const Edge &edge1 = boost::edge(vertex, neighbors[0], _g).first;
      const Edge &edge2 = boost::edge(vertex, neighbors[1], _g).first;

      const Vertex &beg1 = boost::source(edge1, _g);
      const Vertex &beg2 = boost::source(edge2, _g);
      const Vertex &end1 = boost::target(edge1, _g);
      const Vertex &end2 = boost::target(edge2, _g);
      
      Vec2d dir1, dir2;

      if (beg1 == beg2 || end1 == end2)
      {
         dir1.diff(boost::get(boost::vertex_pos, _g, end1),
                   boost::get(boost::vertex_pos, _g, beg1));
         dir2.diff(boost::get(boost::vertex_pos, _g, end2),
                   boost::get(boost::vertex_pos, _g, beg2));
      }
      else if (beg1 == end2 || beg2 == end1)
      {
         dir1.diff(boost::get(boost::vertex_pos, _g, end1),
                   boost::get(boost::vertex_pos, _g, beg1));
         dir2.diff(boost::get(boost::vertex_pos, _g, beg2),
                   boost::get(boost::vertex_pos, _g, end2));
      }
      else
      {
         throw Exception("internal error: edges not adjacent");
      }

      double d = Vec2d::dot(dir1, dir2);
      double n1 = dir1.norm();
      double n2 = dir2.norm();
      double maxn = std::max(n1, n2);
      
      if (n1 * n2 > 0.00001)
         d /= n1 * n2;
      
      double ang = acos(d);

      if (ang < PI * 3 / 4)
         continue;

      double err = n1 * n2 * sin(ang) / (maxn * maxn);

      //if (d < -0.92)
      if (err < min_err)
      {
         min_err = err;
         to_dissolve = vertex;
      }
   }
   
   if (min_err < 0.17) //0.28 //0.22
   {
      LPRINT(0, "dissolving vertex, err = %.2lf", min_err);
      std::deque<Vertex> neighbors;
      boost::graph_traits<SkeletonGraph>::adjacency_iterator b, e;
      boost::tie(b, e) = boost::adjacent_vertices(to_dissolve, _g);
      neighbors.assign(b, e);
      addBond(neighbors[0], neighbors[1], SINGLE);
      boost::clear_vertex(to_dissolve, _g); 
      boost::remove_vertex(to_dissolve, _g);
      return true;
   }

   return false;
}

void Skeleton::_findMultiple()
{
   DoubleBondMaker _makeDouble(*this);
   TripleBondMaker _makeTriple(*this);
   MultipleBondChecker _checker(*this);
   
   std::vector<Edge> toProcess;
   boost::property_map<SkeletonGraph, boost::edge_type_t>::type types =
      boost::get(boost::edge_type, _g);
   boost::graph_traits<SkeletonGraph>::edge_iterator ei, ei_e;
   boost::tie(ei, ei_e) = boost::edges(_g);
   for (; ei != ei_e; ++ei)
      if (boost::get(types, *ei).type == SINGLE)
         toProcess.push_back(*ei);

   std::map<Edge, bool> used;
   do
   {
      std::vector<std::pair<Edge, Edge> > doubleBonds;
      std::vector<boost::tuple<Edge, Edge, Edge> > tripleBonds;

      int end = toProcess.size();
      for (int ii = 0; ii < end; ii++)
      {
         Edge i = toProcess[ii];
         if (used[i])
            continue;

         BGL_FORALL_EDGES(j, _g, SkeletonGraph)
         {
            if (i == j || boost::get(types, j).type != SINGLE ||
                used[j])
               continue;

            if (!_checker.checkDouble(i, j))
               continue;

            {
               std::pair<double, Edge*> arr[3];
               arr[0].first = boost::get(boost::edge_type, _g, i).length;
               arr[0].second = &i;
               arr[1].first = boost::get(boost::edge_type, _g, j).length;
               arr[1].second = &j;

               if (arr[1].first > arr[0].first)
                  std::swap(arr[0], arr[1]);

               bool is_triple = false;

               BGL_FORALL_EDGES(k, _g, SkeletonGraph)
               {
                  if (k == i || k == j ||
                      boost::get(types, k).type != SINGLE ||
                      used[k])
                     continue;
                  
                  if (!_checker.checkTriple(k))
                     continue;
                  
                  //Check degrees!
                  arr[2].first = boost::get(boost::edge_type, _g, k).length;
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
                  tripleBonds.push_back(boost::make_tuple(*arr[0].second,
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
      for (int i = 0; i < (int)tripleBonds.size(); ++i)
      {
         TripleBondMaker::Result ret = _makeTriple(tripleBonds[i]);

         int add = boost::get<0>(ret);
         if (add == 0)
            continue;
         
         used[boost::get<0>(tripleBonds[i])] = false;
         used[boost::get<1>(tripleBonds[i])] = false;
         used[boost::get<2>(tripleBonds[i])] = false;

         if (add == 1)
         {
            toProcess.push_back(boost::get<1>(ret));
         }
         else if (add == 2)
         {
            toProcess.push_back(boost::get<1>(ret));
            toProcess.push_back(boost::get<2>(ret));
         }
         
      }
      
      std::sort(doubleBonds.begin(), doubleBonds.end(),
                DoubleBondComparator<SkeletonGraph>(getGraph()));
      
      // if (getSettings()["DebugSession"])
      // {
      //    Image img(getSettings()["imgWidth"], getSettings()["imgHeight"]);
      //    img.fillWhite();
      //    for (int i = 0; i < (int)doubleBonds.size(); ++i)
      //    {
      //       Edge f = doubleBonds[i].first, s = doubleBonds[i].second;
      //       Vertex fb, fe, sb, se;
      //       fb = boost::source(f, _g), fe = boost::target(f, _g);
      //       sb = boost::source(s, _g), se = boost::target(s, _g);
      //       ImageDrawUtils::putLineSegment(img, boost::get(boost::vertex_pos, _g, fb), boost::get(boost::vertex_pos, _g, fe), 0);
      //       ImageDrawUtils::putLineSegment(img, boost::get(boost::vertex_pos, _g, sb), boost::get(boost::vertex_pos, _g, se), 0);
      //       ImageUtils::saveImageToFile(img, "output/gdb.png");
      //    }
      //    ImageUtils::saveImageToFile(img, "output/gdb.png");
      // }
      
      for (int i = 0; i < (int)doubleBonds.size(); ++i)
      {
         DoubleBondMaker::Result ret = _makeDouble(doubleBonds[i]);
         
         int add = boost::get<0>(ret);
         if (add == 0)
            continue;

         used[doubleBonds[i].first] = false;
         used[doubleBonds[i].second] = false;
         if (add == 1)
         {
            toProcess.push_back(boost::get<1>(ret));
         }
         else if (add == 2)
         {
            toProcess.push_back(boost::get<1>(ret));
            toProcess.push_back(boost::get<2>(ret));
         } 
      }

      types = boost::get(boost::edge_type, _g);
   } while (false);
   //} while (toProcess.size() != 0);
}

void Skeleton::_reconnectBonds( Vertex from, Vertex to )
{
   std::deque<Vertex> neighbours;
   boost::graph_traits<SkeletonGraph>::adjacency_iterator b, e;
   boost::tie(b, e) = boost::adjacent_vertices(from, _g);
   neighbours.assign(b, e);

   for (int i = 0; i < (int)neighbours.size(); i++)
   {
      Vertex v = neighbours[i];
      Edge e = boost::edge(from, v, _g).first;
      BondType t = get(boost::edge_type, _g, e).type;
      boost::remove_edge(e, _g);

      if (v == to)
         continue;
      
      addBond(v, to, t);
   }
}

bool Skeleton::_checkMidBonds( Vertex from, Vertex to )
{
   std::deque<Vertex> neighbours;
   boost::graph_traits<SkeletonGraph>::adjacency_iterator b, e;
   boost::tie(b, e) = boost::adjacent_vertices(from, _g);
   neighbours.assign(b, e);
   bool ret = false;

   for (int i = 0; i < (int)neighbours.size(); i++)
   {
      Vertex v = neighbours[i];
      Edge e = boost::edge(from, v, _g).first;

      if (v == to)
         continue;
      
      ret = true;
   }
   return ret;
}

void Skeleton::_reconnectBondsRWT( Vertex from, Vertex to, BondType new_t)
{
   std::deque<Vertex> neighbours;
   boost::graph_traits<SkeletonGraph>::adjacency_iterator b, e;
   boost::tie(b, e) = boost::adjacent_vertices(from, _g);
   neighbours.assign(b, e);

   for (int i = 0; i < (int)neighbours.size(); i++)
   {
      Vertex v = neighbours[i];
      Edge e = boost::edge(from, v, _g).first;
      boost::remove_edge(e, _g);

      if (v == to)
         continue;
      
      addBond(v, to, new_t);
   }
}

double Skeleton::_avgEdgeLendth (const Vertex &v, int &nnei)
{
   std::deque<Vertex> neighbors;
   boost::graph_traits<SkeletonGraph>::adjacency_iterator b, e;
   boost::tie(b, e) = boost::adjacent_vertices(v, _g);
   neighbors.assign(b, e);

   nnei = neighbors.size();

   if (neighbors.size() < 1)
      return 0;

   double avg = 0;

   for (int i = 0; i < (int)neighbors.size(); i++)
   {
      Edge e = boost::edge(v, neighbors[i], _g).first;
      avg += boost::get(boost::edge_type, _g, e).length;
   }
   return avg / neighbors.size();
}

void Skeleton::_joinVertices(double eps)
{
   std::deque<std::deque<Vertex> > nearVertices;
   std::deque<int> join_ind;
   boost::property_map<SkeletonGraph, boost::vertex_pos_t>::type pos =
           boost::get(boost::vertex_pos, _g);

   //recalcAvgBondSize?
   //double _addEps = getSettings().get("AddVertexEps");
   //double _addEps = _min_bond_length * 0.7;
#ifdef DEBUG
   LPRINT(0, "joining vertices, eps = %lf", eps);
#endif /* DEBUG */

   BGL_FORALL_VERTICES(v, _g, SkeletonGraph)
   {
      Vec2d v_pos = pos[v];
      int v_nnei;
      double v_avg_edge_len = _avgEdgeLendth(v, v_nnei);

      for (int i = 0; i < (int)nearVertices.size(); i++)
      {
         for (int j = 0; j < (int)nearVertices[i].size(); j++)
         {
            const Vertex &nei = nearVertices[i][j];
            int nei_nnei;
            double nei_avg_edge_len = _avgEdgeLendth(nei, nei_nnei);
            double thresh = eps * (nei_nnei * nei_avg_edge_len + v_nnei * v_avg_edge_len) /
               (v_nnei + nei_nnei);

            if (v_nnei + nei_nnei > 0 &&
                Vec2d::distance(v_pos, pos[nei]) < thresh)
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
         int first = join_ind[0];
         nearVertices[first].push_back(v);

         for (int i = (int)join_ind.size() - 1; i >= 1; i--)
         {
            int ii = join_ind[i];
            nearVertices[first].insert(nearVertices[first].end(),
                                       nearVertices[ii].begin(),
                                       nearVertices[ii].end());
            nearVertices.erase(nearVertices.begin() + ii);
         }
      }
      join_ind.clear();
   }

   for (int i = 0; i < (int)nearVertices.size(); i++)
   {
      int s = (int)nearVertices[i].size();
      if (s == 1)
         continue;
      
      Vec2d newPos;
      for (int j = 0; j < s; j++)
         newPos.add(pos[nearVertices[i][j]]);
      newPos.scale(1.0 / s);

      Vertex newVertex = addVertex(newPos);

      for (int j = 0; j < s; j++)
      {
         _reconnectBonds(nearVertices[i][j], newVertex);
         boost::remove_vertex(nearVertices[i][j], _g);
      }
   }
}

void Skeleton::modifyGraph()
{
   RecognitionSettings &rs = getSettings();

   //CSSETDOUBLE("AddVertexEps", 0.225 * _avg_bond_size);

   _parLinesEps = getSettings()["ParLinesEps"];

   recalcAvgBondLength();

   if (getSettings()["DebugSession"])
   {
      Image img(getSettings()["imgWidth"], getSettings()["imgHeight"]);
      img.fillWhite();
      ImageDrawUtils::putGraph(img, _g);
      ImageUtils::saveImageToFile(img, "output/ggg0.png");
    
   }

   _joinVertices(0.1);

   recalcAvgBondLength();

   _vertices_big_degree.clear();
   
   BGL_FORALL_VERTICES(v, _g, SkeletonGraph)
   {
      if (boost::degree(v, _g) > 2)
      {
         Vec2d pos = boost::get(boost::vertex_pos, _g, v);
         _vertices_big_degree.push_back(pos);
      }
   }

   if (getSettings()["DebugSession"])
    {
       Image img(getSettings()["imgWidth"], getSettings()["imgHeight"]);
       img.fillWhite();
       ImageDrawUtils::putGraph(img, _g);
       ImageUtils::saveImageToFile(img, "output/ggg1.png");
    
    }

   while (_dissolveShortEdges(0.1))
      ;

   if (getSettings()["DebugSession"])
    {
       Image img(getSettings()["imgWidth"], getSettings()["imgHeight"]);
       img.fillWhite();
       ImageDrawUtils::putGraph(img, _g);
       ImageUtils::saveImageToFile(img, "output/ggg2.png");
    
    }

   while (_dissolveIntermediateVertices())
      ;
   //_repairBroken();

   recalcAvgBondLength();

   if (getSettings()["DebugSession"])
    {
       Image img(getSettings()["imgWidth"], getSettings()["imgHeight"]);
       img.fillWhite();
       ImageDrawUtils::putGraph(img, _g);
       ImageUtils::saveImageToFile(img, "output/ggg3.png");
    
    }

    //_repairBroken(); // DP: disabled
   
    recalcAvgBondLength();

    _findMultiple();
    //while (_dissolveIntermediateVertices())
    //   ;
    
    if (getSettings()["DebugSession"])
    {
       Image img(getSettings()["imgWidth"], getSettings()["imgHeight"]);
       img.fillWhite();
       ImageDrawUtils::putGraph(img, _g);
       ImageUtils::saveImageToFile(img, "output/ggg4.png");
    }

    recalcAvgBondLength();
   
    //_joinVertices(0.1);
    while (_dissolveShortEdges(0.2))
      ;

    if (getSettings()["DebugSession"])
    {
       Image img(getSettings()["imgWidth"], getSettings()["imgHeight"]);
       img.fillWhite();
       ImageDrawUtils::putGraph(img, _g);
       ImageUtils::saveImageToFile(img, "output/ggg5.png");
    }

    recalcAvgBondLength();

    _joinVertices(0.33); //0.3!!!
    _joinVertices(0.2); // TODO: see IMG_0022

    //Shrinking short bonds (dots)
    std::vector<Edge> edgesToRemove;
    BGL_FORALL_EDGES(edge, _g, SkeletonGraph)
    {
       const Vertex &beg = boost::source(edge, _g);
       const Vertex &end = boost::target(edge, _g);
       Vec2d beg_pos = boost::get(boost::vertex_pos, _g, beg);
       const Vec2d &end_pos = boost::get(boost::vertex_pos, _g, end);
       if (boost::degree(beg, _g) == 1 && boost::degree(end, _g) == 1 &&
           boost::get(boost::edge_type, _g, edge).length < 0.13 * _avg_bond_length)
       {
          beg_pos.add(end_pos);
          beg_pos.scale(0.5);
          addVertex(beg_pos);
          edgesToRemove.push_back(edge);
       }
    }
    BOOST_FOREACH(Edge e, edgesToRemove)
    {
       Vertex beg = boost::source(e, _g);
       Vertex end = boost::target(e, _g);
       boost::remove_edge(e, _g);
       boost::remove_vertex(beg, _g);
       boost::remove_vertex(end, _g);
    }


    if (getSettings()["DebugSession"])
    {
       Image img(getSettings()["imgWidth"], getSettings()["imgHeight"]);
       img.fillWhite();
       ImageDrawUtils::putGraph(img, _g);
       ImageUtils::saveImageToFile(img, "output/ggg6.png");
    }

   
   //if (rs["DebugSession"])
   //drawGraph(2000, 1000, "output/ggg2.png");

   rs.set("AvgBondLength", _avg_bond_length);
   while (_dissolveShortEdges(0.45, true));

   if (getSettings()["DebugSession"])
    {
       Image img(getSettings()["imgWidth"], getSettings()["imgHeight"]);
       img.fillWhite();
       ImageDrawUtils::putGraph(img, _g);
       ImageUtils::saveImageToFile(img, "output/ggg7.png");
   }

}

void Skeleton::setBondType( Edge &e, BondType t )
{
   Bond b = boost::get(boost::edge_type, _g, e);

   b.type = t;

   boost::put(boost::edge_type, _g, e, b);
}

BondType Skeleton::getBondType( const Edge &e ) const
{
   return boost::get(boost::edge_type, _g, e).type;
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
}

