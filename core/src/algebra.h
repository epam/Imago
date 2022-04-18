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
#ifndef _math_h
#define _math_h

#include "vec2d.h"
#include <utility>
#include "settings.h"

namespace imago
{
   class Rectangle;
   
   struct Line
   {
      double A, B, C;
   };

   class Algebra
   {
   public:
      /**
       * @brief Distance from point to segment
       *
       * @param v point
       * @param b begin point of segment
       * @param e end point of segment
       *
       * @return
       */
      static double distance2segment( const Vec2d &v, const Vec2d &b, const Vec2d &e );

      static double distance2rect( const Vec2d &p, int x, int y, int width, int height );

      static double distance2rect( const Vec2d &p, const Rectangle &r );

      static Line points2line( const Vec2d &b, const Vec2d &e );

      static Vec2d linesIntersection(const Settings& vars, const Vec2d &p11, const Vec2d &p12, const Vec2d &p21, const Vec2d &p22 );

      static Vec2d linesIntersection(const Settings& vars, const Line &l1, const Line &l2 );
      
      static double slope( const Vec2d &b, const Vec2d &e );

      static double pointProjectionCoef( const Vec2d &orig, const Vec2d &to_begin , const Vec2d &to_end );
      
      static std::pair<Vec2d, Vec2d> segmentProjection( const Vec2d &orig_begin , const Vec2d &orig_end, const Vec2d &to_begin , const Vec2d &to_end );

      static bool segmentsParallel( const Vec2d &b1, const Vec2d &e1, const Vec2d &b2, const Vec2d &e2, double eps, double *dist = 0 );

      static bool rangesSeparable (double range1_bound1, double range1_bound2,  double range2_bound1, double range2_bound2);

	  static bool SegmentsOnSameLine(const Settings& vars, Vec2d &b1, Vec2d &e1, Vec2d &b2, Vec2d &e2);
   };
}
#endif /* _math_h */
