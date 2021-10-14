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
#ifndef _segment_h
#define _segment_h

#include "vec2d.h"
#include "image.h"

namespace imago
{
   class Rectangle;

   class Segment : public Image
   {
   public:
      Segment();

	  Segment( int width, int height, int x, int y ) : Image(width, height)
	  {
		  _x = x; _y = y;
	  }

	  Segment( const Segment &other)
	  {
		  copy(other);
	  }

	  virtual ~Segment();

      void copy( const Segment &s, bool copy_all = true );	  
	  void copy( const Image &i) { Image::copy(i); }

      int getX() const;
      int getY() const;
      
	  int &getX();
      int &getY();

      Rectangle getRectangle() const;
      Vec2i getCenter() const;

      void splitVert( int x, Segment &left, Segment &right ) const;
      void crop();
      void rotate90();

	  double getRatio();
      double getDensity();

      double getRatio() const;
      double getDensity() const;
  
   private:
      int _x, _y;
      double _ratio;
      double _density;
   };
}

#endif /* _segment_h */
