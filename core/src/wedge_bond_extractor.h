/****************************************************************************
* Copyright (C) from 2009 to Present EPAM Systems.
*
* This file is part of Imago toolkit.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***************************************************************************/

#pragma once
#ifndef _wedge_bond_extractor_h
#define _wedge_bond_extractor_h

#include "stl_fwd.h"

namespace imago
{
   class Skeleton;
   class Molecule;
   class Image;
   struct Bond;

   class WedgeBondExtractor
   {
   public:

      struct SingleDownBond
      {
         Vec2d b, e;
         bool orient; // true if b->e
      };

      struct SegCenter
      {
         SegCenter()
         {
         }

         SegCenter( SegmentDeque::iterator new_seg_iterator, const Vec2d &new_center, double new_angle ) :
            seg_iterator(new_seg_iterator),
            center(new_center), angle(new_angle) 
         {
            used = true;
         }

         size_t seginfo_index;
         SegmentDeque::iterator seg_iterator;
         bool used;
         Vec2d center;
         double angle;
      };

      WedgeBondExtractor( SegmentDeque &segs, Image &img );

      int singleDownFetch(const Settings& vars, Skeleton &g );
      void singleUpFetch(const Settings& vars, Skeleton &g );

      void fixStereoCenters( Molecule &mol ); 

      ~WedgeBondExtractor();

   private:

      SegmentDeque &_segs;
      Image &_img;

      struct _intersectionContext
      {
         Image *img;
         Vec2d intersection_point;
         bool white_found;
      };

      void _fitSingleDownBorders( Vec2d &p1, Vec2d &p2, const Vec2d &v1, const Vec2d &v2 );
      static bool _intersectionFinderPlotCallBack( int x, int y, int color, void *userdata );	  
      
      bool _isSingleUp(const Settings& vars, Skeleton &g, const Skeleton::Edge &e, BondType &return_type);
      int _radiusFinder( const Vec2d &v );
      static bool _radiusFinderPlotCallback( int x, int y, int color, void *userdata );
      static int _doubleCompare( const void *a, const void *b );

      void fetchArrows(const Settings& vars, Skeleton &g );

      struct _Configuration
      {
         char label_first;
         char label_second;
         int charge;
         int degree;
         int n_double_bonds;
      };      

      bool _checkStereoCenter( Skeleton::Vertex v, Molecule &mol );

      std::map<Skeleton::Vertex, int> _thicknesses;
      std::vector<Skeleton::Edge> _bonds_to_reverse;

      //std::vector<int> _thicknesses;
      double _mean_thickness;
      std::vector<byte> _bfs_state;
      double _bond_length;

      int getVertexValence(Skeleton::Vertex v, Skeleton &mol);
	  void CurateSingleUpBonds(Skeleton &graph);

      struct _CircleContext
      {
         Image *img;
         bool done;
      };
   };
}


#endif /* _wedge_bond_extractor_h */