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

#include "cv.h"

#include "comdef.h"
#include "log_ext.h"
#include "image.h"
#include "image_utils.h"
#include "image_draw_utils.h"
#include "segment.h"
#include "stat_utils.h"
#include "molecule.h"
#include "skeleton.h"
#include "vec2d.h"
#include "wedge_bond_extractor.h"
#include "settings.h"

using namespace imago;

WedgeBondExtractor::WedgeBondExtractor( SegmentDeque &segs, Image &img ) : _segs(segs), _img(img)
{
}


struct PointsComparator : public std::binary_function<WedgeBondExtractor::SegCenter,WedgeBondExtractor::SegCenter,bool>
{
	int PointsCompareDist;

	PointsComparator(int dist)
	{
		PointsCompareDist = dist;
	}

	inline bool operator()(const WedgeBondExtractor::SegCenter& c, const WedgeBondExtractor::SegCenter& d)
	{
		Vec2d a = c.center, b = d.center;

		bool res;

		if (a.x > b.x)  
			res = true;
		if (a.x < b.x) 
			res = false;   

		if (fabs(a.x - b.x) <= PointsCompareDist)
		{
			if (a.y > b.y)
				res = true;
			if (a.y < b.y)
				res = false;
			if (fabs(a.y - b.y) <= PointsCompareDist)
				res = false;
		}

		return res;
	}
};


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

int WedgeBondExtractor::singleDownFetch(const Settings& vars, Skeleton &g )
{
   int sdb_count = 0;
   double eps = vars.wbe.SingleDownEps, angle;   

   std::vector<SingleDownBond> sd_bonds;
   std::vector<SegCenter> segs_info;
   std::vector<Segment *> to_delete_segs;

   for (SegmentDeque::iterator it = _segs.begin(); it != _segs.end(); ++it)
   {
      if (ImageUtils::testSlashLine(vars, **it, &angle, eps))
      {
         Vec2d a = (*it)->getCenter();
         segs_info.push_back(SegCenter(it, a, angle));
      }
   }

   if (segs_info.empty())
      return 0;

   for (size_t i = 0; i < segs_info.size(); i++)
   {
      segs_info[i].seginfo_index = i;
   }

   for (size_t i = 0; i < segs_info.size(); i++)
      for (size_t j = i + 1; j < segs_info.size(); j++)
      {
		  if (segs_info[i].used && segs_info[j].used && fabs(segs_info[i].angle - segs_info[j].angle) < vars.wbe.SomeTresh)
         {
            DoubleVector distances;
            Vec2d p1 = segs_info[i].center, p2 = segs_info[j].center;   

            std::vector<SegCenter> cur_points;

            cur_points.push_back(segs_info[i]);
            cur_points.push_back(segs_info[j]);
            
            for (size_t k = 0; k < segs_info.size(); k++)
            {
               Vec2d p3;

               if (k != i && k != j && segs_info[k].used)
               {
                  p3 = segs_info[k].center;

				  if (absolute(p1.x - p2.x) <= vars.wbe.SingleDownCompareDist)
                  {
                     if (absolute(p1.x - p3.x) <= vars.wbe.SingleDownCompareDist || absolute(p3.x - p2.x) <= vars.wbe.SingleDownCompareDist)
                     {
                        cur_points.push_back(segs_info[k]);
                        continue;
                     }
                  }

                  if (absolute(p1.y - p2.y) <= vars.wbe.SingleDownCompareDist)
                  {
                     if (absolute(p1.y - p3.y) <= vars.wbe.SingleDownCompareDist || absolute(p3.y - p2.y) <= vars.wbe.SingleDownCompareDist)
                     {
                        cur_points.push_back(segs_info[k]);
                        continue;
                     }
                  }

                  double ch1 = (p1.x - p3.x) * (p2.y - p1.y);
                  double ch2 = (p1.x - p2.x) * (p3.y - p1.y);

				  if (absolute(ch1 - ch2) <= vars.wbe.SingleDownAngleMax)
                     cur_points.push_back(segs_info[k]);
               }
            }

			std::sort(cur_points.begin(), cur_points.end(), PointsComparator(vars.wbe.PointsCompareDist));

            if ((int)cur_points.size() >= vars.wbe.MinimalSingleDownSegsCount)
            {
               std::vector<IntPair> same_dist_pairs;
               DoubleVector distances(cur_points.size() - 1);

               for (size_t k = 0; k < cur_points.size() - 1; k++)
                  distances[k] = Vec2d::distance(cur_points[k + 1].center, cur_points[k].center);

               for (size_t k = 0; k < distances.size();)
               {
                  int l = k + 1;
                  IntPair p;

                  for (; l != (int)distances.size(); l++)
                  {
					  if (fabs(distances[l - 1] - distances[l]) > vars.wbe.SingleDownDistancesMax)
                        break;
                  }

                  p.first = k;
                  p.second = l;

                  same_dist_pairs.push_back(p);

                  k += l - k;
               }

               for (size_t k = 0; k < same_dist_pairs.size(); k++)
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

					 if (ave_dist > vars.wbe.SingleDownLengthMax)
                        continue;

                     if (!segs_info[cur_points[p.first].seginfo_index].used ||
                         !segs_info[cur_points[p.second].seginfo_index].used)
                         continue;

                     Vec2d p1 = cur_points[p.first].center;
                     Vec2d p2 = cur_points[p.second].center; 
					 
                     double length = Vec2d::distance(p1, p2);

					 Vec2d orient;
                     orient.diff(p2, p1);
                     orient = orient.getNormalized();

                     orient.scale(length);

                     Vec2d v1 = p1, v2 = p2;

                     v1.diff(v1, orient);
                     v2.sum(v2, orient);

                     _fitSingleDownBorders(p1, p2, v1, v2);
                     g.addBond(p2, p1, SINGLE_DOWN); 

                     sdb_count++;

                     for (int l = p.first; l <= p.second; l++)
                     {
                        // mark elements to delete from deque 
                        to_delete_segs.push_back(*cur_points[l].seg_iterator);
                        segs_info[cur_points[l].seginfo_index].used = false;
                     }
                  }
               }                             
            }
            cur_points.clear();
        }
      }

   // delete elements from queue (note: iterators invalidation after erase)
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

   Skeleton::SkeletonGraph graph = g.getGraph();   
  
   return sdb_count;
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
      ImageDrawUtils::putCircle(round(v.x), round(v.y), r, 0, &cc, _radiusFinderPlotCallback);
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
	logEnterFunction();

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
	   conf.label_first = elem->second->satom.atoms[0].getLabelFirst();
	   conf.label_second = elem->second->satom.atoms[0].getLabelSecond();
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

void WedgeBondExtractor::singleUpFetch(const Settings& vars, Skeleton &g )
{   
	logEnterFunction();

   int count = 0;

   Skeleton::SkeletonGraph &graph = g.getGraph();
   
   if (g.getEdgesCount() >= 1)
   {
      Image img;
      img.copy(_img);
	  _bond_length = vars.dynamic.AvgBondLength;

      _bfs_state.resize(_img.getWidth() * _img.getHeight());
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
         if (_isSingleUp(vars, g, b))
         {
            count++;
            g.setBondType(b, SINGLE_UP);
         }
      }

      _thicknesses.clear();
      _bfs_state.clear();
   }

   getLogExt().append("Single-up bonds", count);
}

bool WedgeBondExtractor::_isSingleUp(const Settings& vars, Skeleton &g, Skeleton::Edge &e1 )
{
	logEnterFunction();
	
   Bond bond = g.getBondInfo(e1);

   if (bond.type != SINGLE)
      return false;

   Vec2d bb = g.getVertexPos(g.getBondBegin(e1));
   Vec2d ee = g.getVertexPos(g.getBondEnd(e1));


   double coef = vars.wbe.SingleUpDefCoeff;
   if (_bond_length < vars.wbe.SingleUpIncLengthTresh)
	   coef = vars.wbe.SingleUpIncCoeff;

   if (Vec2d::distance(bb, ee) < _bond_length * coef)
      return false;
   
   Vec2d b(bb), e(ee);
   b.interpolate(bb, ee, vars.wbe.SingleUpInterpolateEps);
   e.interpolate(ee, bb, vars.wbe.SingleUpInterpolateEps);
   b.x = round(b.x);
   b.y = round(b.y);
   e.x = round(e.x);
   e.y = round(e.y);
   Vec2d n;
   n.diff(e, b);
   n = n.getNormalized();
   int size = round(abs(n.x * (e.x - b.x)+ n.y * (e.y - b.y)));
   std::vector<int> profile(size);
   
   int w = _img.getWidth();
   int h = _img.getHeight();
   Image img(w, h);
   img.fillWhite();

   Points2d visited;
   std::deque<Vec2d> queue;

   queue.push_back(b);
   while (!queue.empty())
   {
      Vec2d cur = queue.front();

      queue.pop_front();

      visited.push_back(cur);

      double dp = Vec2d::distance(cur, e);
	  dp = sqrt(dp * dp + 1) + vars.wbe.SingleUpMagicAddition;
      for (int i = round(cur.x) - 1; i <= round(cur.x) + 1; i++)
      {
         for (int j = round(cur.y) - 1; j <= round(cur.y) + 1; j++)
         {
            if (i == round(cur.x) && j == round(cur.y))
               continue;

            if (i < 0 || j < 0 || i >= w || j >= h)
               continue;

            if (_img.getByte(i, j) != 255 && !_bfs_state[j * w + i])
            {
               Vec2d v(i, j);
               double dist = Vec2d::distance(v, e);
               if (dist <= dp)
               {
                  queue.push_back(v);
                  _bfs_state[j * w + i] = 1;
				  img.getByte(i, j) = 0;
				  int indx = round(n.x * (i - b.x) + n.y * (j - b.y));
				  if(indx > -1 && indx < profile.size())
					  profile[indx]++;
               }
            }
         }
      }

	  
   }
   getLogExt().appendVector("profile ", profile);
   getLogExt().appendImage("image profile", img);

   double y_mean = 0, x_mean = 0;
   int psize = profile.size() - 1;
   
   for(size_t i = 1; i < profile.size(); i++)
   {
	   
	   if( profile[i] == 0)
		   psize--;
	   else
	   {
		   x_mean += i;
		   y_mean += profile[i];
	   }
   }


   if( psize < profile.size() / 4 )
	   return false;

   y_mean /= psize;
   x_mean /= psize;

   double Sxx=0, Sxy=0;
   double max_val = 0;
   for(size_t i = 1; i < profile.size(); i++)
   {
	   if(profile[i] != 0 )
	   {
		   double xx = i - x_mean;
		   double xy = (profile[i] - y_mean) * (i - x_mean);
		   Sxx += xx * xx;
		   Sxy += xy;
		   if(max_val < profile[i])
			   max_val = profile[i];
	   }
   }

   double b_coeff = Sxy / Sxx;
   getLogExt().append("Slope coefficient", b_coeff);
   
   for (size_t i = 0; i < visited.size(); i++)
   {
	   int y = round(visited[i].y);
	   int x = round(visited[i].x);
	   if (y >= 0 && x >= 0 && y < _img.getHeight() && x < _img.getWidth())
		   _bfs_state[y * w + x] = 0;
   }

   if( abs(b_coeff) > vars.wbe.SingleUpSlopeThresh && max_val > vars.dynamic.LineThickness)
	   return true;
   else
	   if( y_mean / vars.dynamic.LineThickness > vars.wbe.SingleUpThickThresh)
		   return true;
	   
   return false;
}

WedgeBondExtractor::~WedgeBondExtractor()
{
}
