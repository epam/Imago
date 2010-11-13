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

#ifndef _graphics_detector_h
#define _graphics_detector_h

#include "vec2d.h"
#include "stl_fwd.h"

namespace imago
{
   struct LineSegment
   {
      Vec2d b;
      Vec2d e;
   };
   
   class Segment;
   class Image;

   class GraphicsDetector
   {
   public:
      GraphicsDetector();
      void extractRingsCenters( SegmentDeque &segments, Points &ring_centers );
      void detect( const Image &img, Points &lsegments );
      ~GraphicsDetector();
   private:

      void _decorner( Image &img );
      void _extractPolygon( const Segment &seg, Points &poly );
      int _countBorderBlackPoints( const Image &img ) const;
      GraphicsDetector( const GraphicsDetector & );
   };
}
#endif /* _graphics_detector_h */

