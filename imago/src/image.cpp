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

/** 
 * @brief Constant getter to (i,j) byte of image
 * 
 * @param i 
 * @param j 
 * 
 * @return constant reference
 */

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
	if(x1 < 0 || x2 > _width || 
		y1 < 0 || y2 > _height)
		throw Exception("Coordinates out of bounds");
	res.clear();
	res.init(x2 - x1, y2 - y1);

	for(int i = x1; i < x2; i++)
		for(int j = y1; j < y2; j++)
		{
			res.getByte(i - x1, j - y1) = this->getByte(i, j);
		}
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

   _data = new byte[_width * _height](); // speed a little slower, but quite useful
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

int Image::mean() const
{
   double total = 0;
   double den = 1.0 / (_width * _height);
   for (int i = 0; i < _width * _height; i++)
      total += _data[i] * den;
   return (int)total;
}

void Image::rotate90( bool cw )
{
   std::auto_ptr<byte> temp_ptr(new byte[_width * _height]);
   byte *temp = temp_ptr.get();
   int a, b, c;
   if (cw)
      a = _height, b = -1, c = _height - 1;
   else
      a = -_height, b = 1, c = (_width - 1) * _height;

   for (int i = 0; i < _width * _height; i++)
   {
      int x = i % _width, y = i / _width;
      int npos = a * x + b * y + c;
      temp[npos] = _data[i];
   }
   delete[] _data;
   std::swap(_width, _height);
   _data = temp_ptr.release();
}

void Image::rotate180()
{
   std::reverse(_data, _data + _width * _height);
}
