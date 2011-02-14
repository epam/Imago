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

/**
 * @file   vec2d.cpp
 * 
 * @brief  Implementation of vector
 */

#include <math.h>
#include <algorithm>

#include "vec2d.h"
#include "exception.h"

using namespace imago;

Vec2d::Vec2d()
{
   x = y = 0.0;
}

Vec2d::Vec2d( double _x, double _y )
{
   x = _x;
   y = _y;
}

Vec2d::Vec2d( const Vec2d &v )
{
   x = v.x;
   y = v.y;
}

void Vec2d::set( double _x, double _y )
{
   x = _x;
   y = _y;
}

void Vec2d::copy ( const Vec2d &v )
{
   x = v.x;
   y = v.y;
}

void Vec2d::zero()
{
   x = y = 0.0;
}

void Vec2d::add( const Vec2d &v )
{
   x += v.x;
   y += v.y;
}

void Vec2d::sum( const Vec2d &a, const Vec2d &b )
{
   x = a.x + b.x;
   y = a.y + b.y;
}

void Vec2d::sub( const Vec2d &v )
{
   x -= v.x;
   y -= v.y;
}

void Vec2d::diff( const Vec2d &a, const Vec2d &b )
{
   x = a.x - b.x;
   y = a.y - b.y;   
}

void Vec2d::interpolate( const Vec2d &b, const Vec2d &e, const double lambda )
{
   if (lambda < 0 || lambda > 1.0)
      throw LogicException("invalid lambda parameter");

   x = b.x * (1 - lambda) + e.x * lambda;
   y = b.y * (1 - lambda) + e.y * lambda;
}

void Vec2d::middle( const Vec2d &b, const Vec2d &e )
{
   interpolate(b, e, 0.5);
}

bool Vec2d::operator ==( const Vec2d &other ) const
{
   return fabs(x - other.x) < EPS && fabs(y - other.y) < EPS;
}

void Vec2d::scale( double s )
{
   x *= s;
   y *= s;
}

void Vec2d::scaled( const Vec2d &v, double s )
{
   x = v.x * s;
   y = v.y * s;
}

double Vec2d::norm() const
{
   return sqrt(x * x + y * y);
}

void Vec2d::normalize()
{
   double n = norm();

   x /= n;
   y /= n;
}

void Vec2d::rotate( double angle )
{
   double s = sin(angle);
   double c = cos(angle);
   double _x = x, _y = y;
   x = c * _x - s * _y;
   y = s * _x + c * _y;
}

double Vec2d::dot( const Vec2d &a, const Vec2d &b )
{
   return a.x * b.x + a.y * b.y;
}

double Vec2d::angle( const Vec2d &a, const Vec2d &b )
{
   double d = dot(a, b);
   double na = a.norm();
   double nb = b.norm();
   if (fabs(na * nb) < EPS)
      throw DivizionByZeroException();
   
   d = d / na / nb;

   if (absolute(d - 1) < 1e-10)
      return 0;
   
   return acos(d);
}

double Vec2d::distance( const Vec2d &a, const Vec2d &b )
{
   double dx, dy;
   dx = a.x - b.x;
   dy = a.y - b.y;

   return sqrt(dx * dx + dy * dy);
}
