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

#include <vector>
#include <deque>

#include "boost/graph/iteration_macros.hpp"
#include "boost/foreach.hpp"

#include "comdef.h"
#include "current_session.h"
#include "image.h"
#include "image_utils.h"
#include "image_draw_utils.h"
#include "segment.h"
#include "stat_utils.h"
#include "molecule.h"
#include "skeleton.h"
#include "vec2d.h"
#include "wedge_bond_extractor.h"

using namespace imago;

WedgeBondExtractor::WedgeBondExtractor( SegmentDeque &segs, Image &img ) : _segs(segs), _img(img)
{
}

bool WedgeBondExtractor::_pointsCompare( const SegCenter &c, const SegCenter &d )
{
   bool res;

   Vec2d a = c.center, b = d.center;

   if (a.x > b.x)  
      res = true;
   if (a.x < b.x) 
      res = false;
   if (abs(a.x - b.x) <= 3)
   {
      if (a.y > b.y)
         res = true;
      if (a.y < b.y)
         res = false;
      if (abs(a.y - b.y) <= 3)
         res = false;
   }

   return res;
}

void WedgeBondExtractor::_fitSingleDownBorders( Vec2d &p1, Vec2d &p2, Vec2d &v1, Vec2d &v2 )
{
   _intersectionContext ic;

   ic.img = &_img;

   ic.white_found = false;
   ic.intersection_point.x = -1;
   ic.intersection_point.y = -1;
   ImageDrawUtils::putLineSegment(p1, v1, 255, &ic, _intersectionFinderPlotCallBack);

   if (ic.intersection_point.x != -1 && ic.intersection_point.y != -1)
      p1 = ic.intersection_point;

   ic.white_found = false;
   ic.intersection_point.x = -1;
   ic.intersection_point.y = -1;
   ImageDrawUtils::putLineSegment(p2, v2, 255, &ic, _intersectionFinderPlotCallBack);

   if (ic.intersection_point.x != -1 && ic.intersection_point.y != -1)
      p2 = ic.intersection_point;
}

void WedgeBondExtractor::singleDownFetch( Skeleton &g )
{
   int sdb_count = 0;
   double eps = 3.3, angle;

   std::vector<SingleDownBond> sd_bonds;
   std::vector<SegCenter> segs_info;
   std::vector<Segment *> to_delete_segs;

   for (SegmentDeque::iterator it = _segs.begin(); it != _segs.end(); ++it)
   {
      if (ImageUtils::testSlashLine(**it, &angle, eps))
      {
         Vec2d a = (*it)->getCenter();
         segs_info.push_back(SegCenter(it, a, angle));
      }
   }

   if (segs_info.empty())
      return;

   for (int i = 0; i != (int)segs_info.size(); i++)
   {
      segs_info[i].seginfo_index = i;
   }

   int f = 0;

   //TODO: maybe better a LOT
   for (int i = 0; i != (int)segs_info.size(); i++)
      for (int j = i + 1; j != (int)segs_info.size(); j++)
      {
         if (segs_info[i].used && segs_info[j].used && abs(segs_info[i].angle - segs_info[j].angle) < 0.1)
         {
            f++;
            DoubleVector distances;
            Vec2d p1 = segs_info[i].center, p2 = segs_info[j].center;   

            std::vector<SegCenter> cur_points;

            cur_points.push_back(segs_info[i]);
            cur_points.push_back(segs_info[j]);
            
            for (int k = 0; k != (int)segs_info.size(); k++)
            {
               Vec2d p3;

               if (k != i && k != j && segs_info[k].used)
               {
                  p3 = segs_info[k].center;

                  if (absolute(p1.x - p2.x) <= 2)
                  {
                     if (absolute(p1.x - p3.x) <= 2 || absolute(p3.x - p2.x) <= 2)
                     {
                        cur_points.push_back(segs_info[k]);
                        continue;
                     }
                  }

                  if (absolute(p1.y - p2.y) <= 2)
                  {
                     if (absolute(p1.y - p3.y) <= 2 || absolute(p3.y - p2.y) <= 2)
                     {
                        cur_points.push_back(segs_info[k]);
                        continue;
                     }
                  }

                  int ch1 = (p1.x - p3.x) * (p2.y - p1.y), 
                      ch2 = (p1.x - p2.x) * (p3.y - p1.y);

                  if (absolute(ch1 - ch2) <= 45)
                     cur_points.push_back(segs_info[k]);
               }
            }

            std::sort(cur_points.begin(), cur_points.end(), _pointsCompare);

            //Minimum segments count in single-down bond is 3, right?
            if ((int)cur_points.size() >= 3)
            {
               std::vector<IntPair> same_dist_pairs;
               DoubleVector distances(cur_points.size() - 1);

               for (int k = 0; k != (int)cur_points.size() - 1; k++)
                  distances[k] = Vec2d::distance(cur_points[k + 1].center, cur_points[k].center);

               for (int k = 0; k != (int)distances.size();)
               {
                  int l = k + 1;
                  IntPair p;

                  for (; l != (int)distances.size(); l++)
                  {
                     //TODO: Check this with care and tender
                     if (abs(distances[l - 1] - distances[l]) > 10)
                        break;
                  }

                  p.first = k;
                  p.second = l;

                  same_dist_pairs.push_back(p);

                  k += l - k;
               }

               for (int k = 0; k != (int)same_dist_pairs.size(); k++)
               {
                  IntPair p = same_dist_pairs[k];

                  if (p.second - p.first > 1)
                  {
                     double ave_dist = 0;

                     for (int l = p.first; l < p.second; l++)
                     {
                        ave_dist += distances[l];
                     }

                     ave_dist /= p.second - p.first;

                     if (ave_dist > 40)
                        continue;

                     //TODO: check this again
                     if (segs_info[cur_points[p.first].seginfo_index].used == false ||
                         segs_info[cur_points[p.second].seginfo_index].used == false)
                         continue;

                     double length;

                     Vec2d p1 = cur_points[p.first].center, 
                        p2 = cur_points[p.second].center, orient;

                     length = Vec2d::distance(p1, p2);

                     orient.diff(p2, p1);
                     orient.normalize();

                     orient.scale(length);

                     Vec2d v1 = p1, v2 = p2;

                     v1.diff(v1, orient);
                     v2.sum(v2, orient);

                     _fitSingleDownBorders(p1, p2, v1, v2);
                     g.addBond(p2, p1, SINGLE_DOWN); 

                     sdb_count++;

                     for (int l = p.first; l <= p.second; l++)
                     {
                        //TODO: It is not nice deleting elements from deque. 
                        to_delete_segs.push_back(*cur_points[l].seg_iterator);
                        segs_info[cur_points[l].seginfo_index].used = false;
                     }
                  }
               }                             
            }
            cur_points.clear();
        }
      }

   //TODO: Not clever enough. Because of deque iterators invalidation after erase
   for (SegmentDeque::iterator it = _segs.begin(); it != _segs.end();)
   {
      std::vector<Segment *>::iterator res = std::find(to_delete_segs.begin(), to_delete_segs.end(), *it);

      if (res != to_delete_segs.end())
      {
         delete *it;
         it = _segs.erase(it);
      }
      else
         ++it;
   }

   g.recalcAvgBondLength();
   LPRINT(0, "Single-down bonds found: %d", sdb_count);
}

int WedgeBondExtractor::_radiusFinder( const Vec2d &v )
{
   _CircleContext cc;
   cc.img = &_img;
   cc.done = 0;
   int r = 1;

   while (!cc.done)
   {
      r++;
      ImageDrawUtils::putCircle(v.x, v.y, r, 0, &cc, _radiusFinderPlotCallback);
   }

   return r + 1;
}

bool WedgeBondExtractor::_radiusFinderPlotCallback( int x, int y, int color, void *userdata )
{
   _CircleContext *cc = (_CircleContext*) userdata;
   int w = cc->img->getWidth(), h = cc->img->getHeight();

   if (x >= 0 && y >= 0 && x < w && y < h)
   {
      if (cc->img->getByte(x, y) != 0) //Not black
         cc->done = 1;
   }
   else
      cc->done = 1;

   return true;
}

bool WedgeBondExtractor::_intersectionFinderPlotCallBack( int x, int y, int color, void *userdata )
{
   _intersectionContext *ic = (_intersectionContext *)userdata;
   int w = ic->img->getWidth(), h = ic->img->getHeight();

   if (x >= 0 && y >= 0 && x < w && y < h)
   {
      if (ic->img->getByte(x, y) == 255)
         ic->white_found = true;

      if (ic->img->getByte(x, y) == 0)
      {
         if (ic->white_found)
         {
            if (ic->intersection_point.x == -1 && ic->intersection_point.y == -1)
            {
               ic->intersection_point.x = x;
               ic->intersection_point.y = y;
            }
         }
      }
   }
   
   return true;
}

void WedgeBondExtractor::fixStereoCenters( Molecule &mol )
{
   Skeleton::SkeletonGraph &graph = mol.getSkeleton();
   const Molecule::ChemMapping &labels = mol.getMappedLabels();
   std::vector<Skeleton::Edge> to_reverse_bonds;

   BGL_FORALL_EDGES(b, graph, Skeleton::SkeletonGraph)
   {
      Bond b_bond = boost::get(boost::edge_type, graph, b);
      BondType type = b_bond.type;

      if (type == SINGLE_DOWN || type == SINGLE_UP)
      {
         bool begin_stereo = false, end_stereo = false;         
         Skeleton::Vertex v1 = boost::source(b, graph), 
            v2 = boost::target(b, graph);

         if (_checkStereoCenter(v1, mol))
            begin_stereo = true;

         if (_checkStereoCenter(v2, mol))
            end_stereo = true;

         if (!begin_stereo)
         {
            if (!begin_stereo && !end_stereo)
               mol.setBondType(b, SINGLE);

            if (end_stereo && !begin_stereo)
               to_reverse_bonds.push_back(b);
         }         
      }
   }

   BOOST_FOREACH( Skeleton::Edge e, to_reverse_bonds )
   {
      mol.reverseEdge(e);
   }
}

bool WedgeBondExtractor::_checkStereoCenter( Skeleton::Vertex &v, 
   Molecule &mol )
{
   _Configuration conf;
   const Skeleton::SkeletonGraph &graph = mol.getSkeleton();
   const Molecule::ChemMapping &labels = mol.getMappedLabels();

   Molecule::ChemMapping::const_iterator elem = labels.find(v);

   if (elem == labels.end())
   {
      conf.label_first = 'C';
      conf.label_second = 0;
      conf.charge = 0;
   }
   else
   {
      conf.label_first = elem->second->satom.atoms[0].label_first;
      conf.label_second = elem->second->satom.atoms[0].label_second;
      conf.charge = elem->second->satom.atoms[0].charge;
   }

   conf.degree = boost::in_degree(v, graph);
   conf.n_double_bonds = 0;

   std::pair<Skeleton::EdgeIterator, Skeleton::EdgeIterator> p;

   p = boost::out_edges(v, graph);

   for (Skeleton::EdgeIterator it = p.first; it != p.second; ++it)
   {
      BondType type = boost::get(boost::edge_type, graph, *it).type;

      if (type == DOUBLE)
         conf.n_double_bonds++;
   }

   static const _Configuration allowed_stereocenters [] = 
   {
      {'C', 0, 0, 3, 0 },
      {'C', 0, 0, 4, 0 },
      {'S', 'i', 0, 3, 0 },
      {'S', 'i', 0, 4, 0 },
      {'N', 0, 1, 3, 0 },
      {'N', 0, 1, 4, 0 },
      {'N', 0, 0, 3, 0 },
      {'N', 0, 0, 4, 2 },
      {'S', 0, 1, 3, 0 },
      {'S', 0, 0, 3, 1 },
      {'P', 0, 0, 3, 0 },
      {'P', 0, 1, 4, 0 },
      {'P', 0, 0, 4, 1 },
   };

   int arr_size = sizeof(allowed_stereocenters) / sizeof(allowed_stereocenters[0]);

   for (int i = 0; i < arr_size; i++)
   {
      if (allowed_stereocenters[i].label_first == conf.label_first && 
         allowed_stereocenters[i].label_second == conf.label_second && 
         allowed_stereocenters[i].charge == conf.charge &&
         allowed_stereocenters[i].degree == conf.degree && 
         allowed_stereocenters[i].n_double_bonds == conf.n_double_bonds)
      {
         return true;
      }
   }
   
   return false;
}

void WedgeBondExtractor::singleUpFetch( Skeleton &g )
{   
   int count = 0;

   Skeleton::SkeletonGraph &graph = g.getGraph();
   RecognitionSettings &rs = getSettings();

   if (g.getEdgesCount() >= 1)
   {
      Image img;
      img.copy(_img);
      _bond_length = rs["AvgBondLength"];
      
      //printf("A:%d %d\n", img.getWidth(), img.getHeight()); fflush(stdout);
      /*
      for (int i = g.vertexHead(); i != g.vertexEnd(); i = g.vertexNext(i))
      {
         Vec2d &v = g.getVertex(i).pos;
         img.getByte(v.x, v.y) = 255;
      }*/

      //TODO: Watch out. v.x & v.y can be larger than picture size

      _bfs_state.resize(_img.getWidth() * _img.getHeight());
      //_thicknesses.resize(g.getVerticesCount());
      IntVector iqm_thick;

      BGL_FORALL_VERTICES(v, graph, Skeleton::SkeletonGraph) 
      {
         Vec2d v_vec2d = g.getVertexPos(v);

         int r = _radiusFinder(v_vec2d);
         _thicknesses.insert(std::make_pair(v, r));
         iqm_thick.push_back(r);
      }

      std::sort(iqm_thick.begin(), iqm_thick.end());
      _mean_thickness = StatUtils::interMean(iqm_thick.begin(), iqm_thick.end());

      BGL_FORALL_EDGES(b, graph, Skeleton::SkeletonGraph)
      {
         if (_isSingleUp(g, b))
         {
            count++;
            g.setBondType(b, SINGLE_UP);
         }
      }

      _thicknesses.clear();
      _bfs_state.clear();
   }

//   if (false)
//      g.drawGraph(_img.getWidth(), _img.getHeight(), "output/graph_su.png");

   LPRINT(0, "Single-up bonds: %d", count);
}

bool WedgeBondExtractor::_isSingleUp( Skeleton &g, Skeleton::Edge &e1 )
{
   Bond bond = g.getBondInfo(e1);
   double thick_ratio_eps = 1.6;

   if (bond.type != SINGLE)
      return false;

   int r;

   if (_thicknesses[g.getBondBegin(e1)] >= _thicknesses[g.getBondEnd(e1)])
      ;//g.reverseEdge(e1);

   r = _thicknesses[g.getBondEnd(e1)];
   if (r / _mean_thickness < thick_ratio_eps)
      return false;

   if (_thicknesses[g.getBondBegin(e1)] / _mean_thickness > thick_ratio_eps)
   {
      //This bond is just so thick
   }

   Vec2d bb = g.getVertexPos(g.getBondBegin(e1));
   Vec2d ee = g.getVertexPos(g.getBondEnd(e1));

   if (Vec2d::distance(bb, ee) < _bond_length * 0.2)
      return false;
   
   Vec2d b(bb), e(ee);
   b.interpolate(ee, bb, 0.07);
   e.interpolate(bb, ee, 0.07);
   b.x = (int) b.x;
   b.y = (int) b.y;
   e.x = (int) e.x;
   e.y = (int) e.y;

   int w = _img.getWidth();
   int h = _img.getHeight();

   double dist2line0, dist2line1, dist2line2;
   double min_d11, min_d12, min_d21, min_d22;
   min_d11 = min_d12 = min_d21 = min_d22 = 1e16;

   double a1, a2, b1, b2;
   Vec2d pa1, pa2, pb1, pb2;
   a1 = a2 = b1 = b2 = 0;

   double A0, B0, C0; //line through b & e
   double A1, B1, C1; //line orthog (A,B,C) through b
   double A2, B2, C2; //line orthog (A,B,C) through e
   double t;
   
   A0 = b.y - e.y;
   B0 = e.x - b.x;
   t = sqrt(A0 * A0 + B0 * B0);
   A0 /= t; B0 /= t;
   C0 = b.x * e.y - e.x * b.y;
   C0 /= t;

   A1 = -B0; B1 = A0;
   C1 = -A1 * b.x - B1 * b.y;

   A2 = -B0; B2 = A0;
   C2 = -A2 * e.x - B2 * e.y;

   Points visited;
   std::deque<Vec2d> queue;
   bool border;

   queue.push_back(b);
   while (!queue.empty())
   {
      Vec2d cur = queue.front();

      queue.pop_front();

      border = false;
      visited.push_back(cur);

      double dp = Vec2d::distance(cur, e);
      dp = sqrt(dp * dp + 1) + 0.21;
      for (int i = cur.x - 1; i <= cur.x + 1; i++)
      {
         for (int j = cur.y - 1; j <= cur.y + 1; j++)
         {
            if (i == cur.x && j == cur.y)
               continue;

            if (i < 0 || j < 0 || i >= w || j >= h)
               continue;

            if (_img.getByte(i, j) == 255)
               border = true;

            if (_img.getByte(i, j) != 255 && !_bfs_state[j * w + i])
            {
               Vec2d v(i, j);
               double dist = Vec2d::distance(v, e);
               if (dist <= dp)
               {
                  queue.push_back(v);
                  _bfs_state[j * w + i] = 1;
               }
            }
         }
      }

      if (border)
      {
         dist2line0 = A0 * cur.x + B0 * cur.y + C0;
         dist2line1 = abs(A1 * cur.x + B1 * cur.y + C1);
         dist2line2 = abs(A2 * cur.x + B2 * cur.y + C2);

         if (dist2line0 >= 0)
         {
            if (dist2line1 < min_d11)
            {
               min_d11 = dist2line1;
               a1 = dist2line0;
               pa1.copy(cur);
            }

            if (dist2line2 < min_d21)
            {
               min_d21 = dist2line2;
               a2 = dist2line0;
               pa2.copy(cur);
            }
         }
         else
         {
            if (dist2line1 < min_d12)
            {
               min_d12 = dist2line1;
               b1 = -dist2line0;
               pb1.copy(cur);
            }

            if (dist2line2 < min_d22)
            {
               min_d22 = dist2line2;
               b2 = -dist2line0;
               pb2.copy(cur);
            }
         }
      }
   }

   ////printf("%lf   %lf   %lf   %lf\n", a1, a2, b1, b2);

   Vec2d p1(pa1);
   Vec2d p2(pa2);
   Vec2d p3(pb2);
   Vec2d p4(pb1);


   double S1 = abs(p1.x * p2.y - p2.x * p1.y +
                   p2.x * p3.y - p3.x * p2.y +
                   p3.x * p4.y - p4.x * p3.y +
                   p4.x * p1.y - p1.x * p4.y) * 0.5;

   double S2 = visited.size() / 1.6;

   for (int i = 0; i != visited.size(); i++)
   {
      _bfs_state[visited[i].y * w + visited[i].x] = 0;
   }

   double square_ratio = S2 / S1;

   a1 += b1; a2 += b2;
   double thick_ratio = std::max(a1, a2) / std::min(a1, a2);
   double angle = 0;
   {
      Vec2d n1, n2;
      n1.diff(pa1, pa2);
      n2.diff(pb1, pb2);
      try
      {
         angle = Vec2d::angle(n1, n2);
      }
      catch (Exception &e)
      {
         if (getSettings()["DebugSession"])
            LPRINT(0, "Skipped exception: %s", e.what());
      }
   }

   if (thick_ratio < thick_ratio_eps ||
       square_ratio < 0.6 ||
       angle < 0.06)
      return false;

   return true;
}

WedgeBondExtractor::~WedgeBondExtractor()
{
}
