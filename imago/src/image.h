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
 * @file image.h
 * 
 * @brief   Declares the Image class
 */
#ifndef _image_h
#define _image_h

#include "comdef.h"

namespace imago
{
   class Segment;

   /**
    * @brief   Picture representation type
    */
   class Image
   {
   public:

      //Constructors & destructor
      Image();
      Image( int width, int height );
      ~Image();

      //init\de-init
      void init( int width, int height );
      void clear();
      bool isInit() const;
      void fillWhite();

      //Get functions
      const int &getWidth() const;
      const int &getHeight() const;
      byte &getByte( int i, int j );
      const byte &getByte( int i, int j ) const;
      inline const byte &operator[]( int i ) const {return _data[i];}
      inline byte &operator[]( int i ) {return _data[i];}
      inline byte const * const getData() const {return _data;}
      inline byte *getData() { return _data; }

      //Copy
      void copy( const Image &other );
      void emptyCopy( const Image &other );

      //Helpful functions
      void invert();
      void crop();
      void splitVert( int x, Image &left, Image &right ) const;
      void extract( int x1, int y1, int x2, int y2, Image &res );
      double density() const;

      void rotate( float angle );
      void rotate90( bool cw = true );
      void rotate180();

   protected:
      int _width, _height;
      void *_toPIX();
      void _fromPIX( void *p );

   private:
      Image( const Image & );
      byte *_data;
      
   };
}


#endif /* _image_h */
