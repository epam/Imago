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

#ifndef _segment_h
#define _segment_h

#include "vec2d.h"
#include "image.h"
#include "symbol_features.h"

namespace imago
{
   class Rectangle;

   class Segment : public Image
   {
   public:
      Segment();

      void copy( const Segment &s, bool copy_all = true );	  

      int getX() const;
      int getY() const;
      int &getX();
      int &getY();
      Rectangle getRectangle() const;
      Vec2i getCenter() const;

      void splitVert( int x, Segment &left, Segment &right ) const;
      void crop();
      void rotate90();

      double getRatio() const;
      double getDensity() const;
      double getRatio();
      double getDensity();

      SymbolFeatures &getFeatures() const;
      SymbolFeatures &getFeatures();
      void initFeatures( int descriptorsCount ) const;

      ~Segment();

   private:
      int _x, _y;
      double _ratio;
      double _density;
      mutable SymbolFeatures _features;
   };
}

#endif /* _segment_h */
