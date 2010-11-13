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

         SegCenter( SegmentDeque::iterator new_seg_iterator, Vec2d new_center, double new_angle ) :  
            seg_iterator(new_seg_iterator),
            center(new_center), angle(new_angle) 
         {
            used = true;
         }

         int seginfo_index;
         SegmentDeque::iterator seg_iterator;
         bool used;
         Vec2d center;
         double angle;
      };

      WedgeBondExtractor( SegmentDeque &segs, Image &img );

      void singleDownFetch( Skeleton &g );
      void singleUpFetch( Skeleton &g );

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

      void _fitSingleDownBorders( Vec2d &p1, Vec2d &p2, Vec2d &v1, Vec2d &v2 );
      static bool _intersectionFinderPlotCallBack( int x, int y, int color, void *userdata );

      static bool _pointsCompare( const SegCenter &a, const SegCenter &b );

      bool _isSingleUp( Skeleton &g, Skeleton::Edge &e );
      int _radiusFinder( const Vec2d &v );
      static bool _radiusFinderPlotCallback( int x, int y, int color, void *userdata );
      static int _doubleCompare( const void *a, const void *b );

      struct _Configuration
      {
         char label_first;
         char label_second;
         int charge;
         int degree;
         int n_double_bonds;
      };      

      bool _checkStereoCenter( Skeleton::Vertex &v, Molecule &mol );

      std::map<Skeleton::Vertex, int> _thicknesses;

      //std::vector<int> _thicknesses;
      double _mean_thickness;
      std::vector<byte> _bfs_state;
      double _bond_length;

      struct _CircleContext
      {
         Image *img;
         bool done;
      };
   };
}


#endif /* _wedge_bond_extractor_h */