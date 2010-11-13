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

#ifndef _rectangle_h
#define _rectangle_h

namespace imago
{
   class Vec2d;
   class Rectangle
   {
   public:

      Rectangle();
      Rectangle( int _x, int _y, int _width, int _height );
      Rectangle( const Vec2d &top_left, const Vec2d &bottom_right );
      Rectangle( const Vec2d &pos, int _width, int _height );
      
      double diagLength2() const;
      double diagLength() const;
      static double distance( const Rectangle &r1, const Rectangle &r2 );

      int x, y;
      int width, height;
   };
}


#endif /* _rectangle_h */

