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
 * @file   vec2d.h
 * 
 * @brief  2d double vector
 */
#ifndef _vec2d_h
#define _vec2d_h

#include "comdef.h"

namespace imago
{
   /**
    * @brief Vector class
    */
   class Vec2d
   {
   public:
      //TODO: private or not to private
      double x;
      double y;

      /**
       * Default constructor
       */
      Vec2d();

      /**
       * Construct with given coordinates
       *
       * @param _x
       * @param _y
       */
      Vec2d( double _x, double _y );

      /**
       * Copy-constructor
       *
       * @param v
       */
      Vec2d( const Vec2d &v );

      /**
       * @brief Sets coordinates to (_x, _y)
       *
       * @param _x
       * @param _y
       */
      void set( double _x, double _y );

      /**
       * @brief Copies coordinates from vector @a v
       *
       * @param v
       */
      void copy( const Vec2d &v );

      /**
       * @brief Sets coordinates to (0, 0)
       *
       */
      void zero();

      /**
       * @brief Adds vector @a v
       *
       * @param v
       */
      void add( const Vec2d &v );

      /**
       * @brief Sets coordinates to sum of @a a and @a b
       *
       * @param a
       * @param b
       */
      void sum( const Vec2d &a, const Vec2d &b );

      /**
       * @brief Substracts vector @a v
       *
       * @param v
       */
      void sub( const Vec2d &v );

      /**
       * @brief Sets coordinates to difference of vectors @a a and @a b
       *
       * @param a
       * @param b
       */
      void diff( const Vec2d &a, const Vec2d &b );

      void interpolate( const Vec2d &b, const Vec2d &e, const double lambda );

      void middle( const Vec2d &b, const Vec2d &e );

      bool operator== ( const Vec2d &other ) const;

      /**
       * @brief Scales vector
       *
       * @param s scale factor
       */
      void scale( double s );

      /**
       * @brief this = v * s;
       *
       * @param v vector
       * @param s scale factor
       */
      void scaled( const Vec2d &v, double s );

      /**
       * @brief Length of vector
       *
       * @return length
       */
      double norm() const;

      void normalize();

      void rotate( double angle );

      /**
       * @brief Dot product of two vectors
       *
       * @param a first vector
       * @param b second vector
       *
       * @return dot product
       */
      static double dot( const Vec2d &a, const Vec2d &b );

      /**
       * @brief Angle between two vectors
       *
       * @param a first vector
       * @param b second vector
       *
       * @return Cosine of angle
       */
      static double angle( const Vec2d &a, const Vec2d &b );

      /**
       * @brief Distance between point v1 and v2
       *
       * @param a first vector
       * @param b second vector
       *
       * @return distance
       */
      static double distance( const Vec2d &a, const Vec2d &b );
   };
}


#endif /* _vec2d_h */
