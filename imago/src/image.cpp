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
 * @file   image.cpp
 * 
 * @brief  Implementation of Image class
 */

#include <cmath>
#include <cstring>

#include "image.h"
#include "exception.h"
#include "segment.h"

using namespace imago;

/** 
 * Default constructor
 */
Image::Image()
{
   _data = 0;
   _width = _height = 0;
}

/** 
 * Creates white image with given width & height
 * 
 * @param width
 * @param height
 */
Image::Image( int width, int height )
{
   _data = 0;
   init(width, height);
   memset(_data, -1, sizeof(byte) * _width * _height);
}

/** 
 * Destructor
 */
Image::~Image()
{
   clear();
}

/** 
 * @brief Clears image (frees memory)
 */
void Image::clear()
{
   if (_data)
   {
      delete[] _data;
   }

   _data = 0;
   _width = _height = 0;        
}

/** 
 * @brief Getter for width
 *
 * @return const reference to _width
 */
const int &Image::getWidth() const
{
   return _width;
}

/** 
 * @brief Getter for height
 * 
 * @return const reference to _height
 */
const int &Image::getHeight() const
{
   return _height;
}

/** 
 * @brief Getter to (i,j) byte of image
 * 
 * @param i 
 * @param j 
 * 
 * @return reference to needed byte
 */
byte &Image::getByte( int i, int j )
{
   int ind = _width * j + i;
   if (ind < 0 || ind >= _width * _height)
      throw OutOfBoundsException("Image::getByte(%d, %d)", i, j);
   return _data[ind];
}

/** 
 * @brief Constant getter to (i,j) byte of image
 * 
 * @param i 
 * @param j 
 * 
 * @return constant reference
 */
const byte &Image::getByte( int i, int j ) const
{
   int ind = _width * j + i;
   if (ind < 0 || ind >= _width * _height)
     throw OutOfBoundsException("Image::getByte(%d, %d)", i, j);
   return _data[ind];
}

/** 
 * @brief Copies image from @a other
 * 
 * @param other 
 */
void Image::copy( const Image &other )
{
   clear();
   init(other._width, other._height);
   memcpy(_data, other._data, sizeof(byte) * _width * _height);
}

/** 
 * @brief Creates empty (white) image with the same width & height as @a other has
 * 
 * @param other 
 */
void Image::emptyCopy( const Image &other )
{
   clear();
   init(other._width, other._height);
   memset(_data, -1, sizeof(byte) * _width * _height);
}

void Image::invert()
{
   int n = _height * _width;

   for (int i = 0; i < n; i++)
   {
      _data[i] = 255 - _data[i];
   }
}

/** 
 * @brief Crops image
 */
void Image::crop()
{
   int l, r, b, t;
   int i, j;

   byte *data = _data;
   int w = _width;
   int h = _height;
   
   t = l = r = b = -1;

   for (i = 0; i < w * h && t == -1; i++)
      if (data[i] != 255)
         t = i / w;

   for (i = h * w - 1; i >= 0 && b == -1; i--)
      if (data[i] != 255)
         b = i / w;

   for (i = 0; i < w && l == -1; i++)
      for (j = 0; j < h && l == -1; j++)
         if(data[j * w + i] != 255)
            l = i;

   for (i = w - 1; i >= 0 && r == -1; i--)
      for (j = 0; j < h && r == -1; j++)
         if(data[j * w + i] != 255)
            r = i;


   
   if (t + b + l + r == -4)
   {
      delete[] _data;
      _data = 0;
      _width = _height = 0;
      return;
   }

   _data = 0;
   init(r - l + 1, b - t + 1);

   for (i = t; i <= b; i++)
   {
      for (j = l; j <= r; j++)
      {
         getByte(j - l, i - t) = data[i * w + j];
      }
   }

   delete[] data;
}

/** 
 * @brief Splits image vertically into two parts.
 *
 * @param x where to split
 * @param left left part
 * @param right right part
 */
void Image::splitVert( int x, Image &left, Image &right ) const
{
   left.clear();
   right.clear();

   left.init(x, _height);
   right.init(_width - x, _height);

   for (int j = 0; j < _height; j++)
   {
      for (int i = 0; i < _width; i++)
      {
         if (i < x)
            left.getByte(i, j) = getByte(i, j);
         else
            right.getByte(i - x, j) = getByte(i, j);
      }
   }
}

/** 
 * @brief Extracts part, which is set by 2 points, of image
 * 
 * @param x1 x coordinate of upper left corner
 * @param y1 y coordinate of upper left corner
 * @param x2 x coordinate of lower right corner
 * @param y2 x coordinate of lower right corner
 * @param res output image
 */
void Image::extract( int x1, int y1, int x2, int y2, Image &res )
{
   throw Exception("Unimplemented method");
}

/** 
 * @brief Sets @a _width & @a _height and allocates memory
 * 
 * @param width 
 * @param height 
 */
void Image::init( int width, int height )
{
   if (_data)
      throw LogicException("Initialization of uncleared image");
   
   _width = width;
   _height = height;

   _data = new byte[_width * _height];
}

/**
 * @brief   Query if this object is initialized.
 * 
 * @return  @c true if initialized, @c false if not 
 */
bool Image::isInit() const
{
   return _data == 0 ? false : true;
}

void Image::fillWhite()
{
   if (_data == 0)
      throw LogicException("uninitialized image");

   memset(_data, -1, sizeof(byte) * _height * _width);
}

/**
 * @brief   Calculates image density 
 * 
 * @return  image density 
 */
double Image::density() const
{
   int n = _width * _height;
   double density = 0;

   for (int i = 0; i < n; i++)
      if (_data[i] == 0)
         density += 1;

   density /= (double)n;

   return density;
}

#include "allheaders.h"

void *Image::_toPIX()
{
   PIX *pix;
   pix = pixCreateNoInit(_width, _height, 8);

   l_uint32 *pixData = pixGetData(pix), *pixLine;
   l_uint32 wpl = pixGetWpl(pix);
   byte *imageLine;

   for (int y = 0; y < _height; y++)
   {
      pixLine = pixData + y * wpl;
      imageLine = _data + y * _width;
      for (int x = 0; x < _width; x++)
      {
         SET_DATA_BYTE(pixLine, x, _data[y * _width + x]);
      }
   }

   return pix;
}

void Image::_fromPIX( void *p )
{
   PIX *pix = (PIX*)p;
   l_uint32 *pixData = pixGetData(pix), *pixLine;
   l_uint32 w = pixGetWidth(pix), h = pixGetHeight(pix), wpl = pixGetWpl(pix);
   byte *imageLine;

   clear();
   init(w, h);

   for (int y = 0; y < _height; y++)
   {
      pixLine = pixData + y * wpl;
      imageLine = _data + y * _width;
      for (int x = 0; x < _width; x++)
      {
         imageLine[x] = GET_DATA_BYTE(pixLine, x);
      }
   }
}

void Image::rotate( float angle )
{
   PIX *pix, *pixRot;

   pix = (PIX*)_toPIX();
   //pixWrite("lol1.bmp", pix, IFF_BMP);

   pixRot = pixRotate(pix, angle, L_ROTATE_SAMPLING, L_BRING_IN_BLACK, _width, _height);
   //pixWrite("lol2.bmp", pixRot, IFF_BMP);

   _fromPIX(pixRot);

   pixDestroy(&pix);
   pixDestroy(&pixRot);
}

void Image::rotate90( bool cw)
{
   PIX *pix, *pixRot;

   pix = (PIX*)_toPIX();

   pixRot = pixRotate90(pix, (cw ? 1:-1));

   _fromPIX(pixRot);

   pixDestroy(&pix);
   pixDestroy(&pixRot);
}

void Image::rotate180()
{
   PIX *pix;

   pix = (PIX*)_toPIX();

   pixRotate180(pix, pix);

   _fromPIX(pix);

   pixDestroy(&pix);
}
