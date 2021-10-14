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
#ifndef _rectangle_h
#define _rectangle_h

#include "vec2d.h"

namespace imago
{
   class Rectangle
   {
   public:

      Rectangle();
      Rectangle( int _x, int _y, int _width, int _height );
      Rectangle( const Vec2i &top_left, const Vec2i &bottom_right );
      Rectangle( const Vec2i &pos, int _width, int _height );
      
      double diagLength2() const;
      double diagLength() const;
      static double distance( const Rectangle &r1, const Rectangle &r2 );

      int x, y;
      int width, height;

	  int x1() const { return x; }
	  int x2() const { return x + width; }
	  int y1() const { return y; }
	  int y2() const { return y + height; }

	  void adjustBorder(int border)
	  {
		  x += border;
		  y += border;
		  width -= 2*border;
		  height -= 2*border;
	  }

	  Rectangle( int x1, int y1, int x2, int y2, int border )
	  {
		  x = x1;
		  y = y1;
		  width  = x2 - x1;
		  height = y2 - y1;
		  adjustBorder(border);
	  }
   };
}


#endif /* _rectangle_h */

