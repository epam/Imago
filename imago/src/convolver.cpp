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

#include <cstring>

#include "convolver.h"
#include "image.h"
#include "exception.h"

using namespace imago;

Convolver::Convolver( Image &img ) : Filter(img), _kernel(0), _rows(0), _cols(0), _invBias(1.0)
{
}

void Convolver::_init( int rows, int cols, double invBias, const int *kernel )
{
   if (isInit())
      throw LogicException("invalid initialization");

   _rows = rows;
   _cols = cols;
   _invBias = invBias;
   _kernel = new int[_rows * _cols];
   memcpy(_kernel, kernel, sizeof(int) * _rows * _cols);
}

void imago::Convolver::initSharp()
{
   static const int sharp_kernel[3 * 3] = { -1, -1, -1, 
                                            -1, 11, -1, 
                                            -1, -1, -1 };

   _init(3, 3, 1.0 / 3, sharp_kernel);
}

void Convolver::initGauss()
{
   /* Gaussian blur filter mask with deviation = 1 */
   static const int gauss_kernel[5 * 5] = { 1,  4,  7,  4, 1, 
                                            4, 16, 26, 16, 4, 
                                            7, 26, 41, 26, 7, 
                                            4, 16, 26, 16, 4, 
                                            1,  4,  7,  4, 1 };
   _init(5, 5, 1.0 / 273, gauss_kernel); 
}

void Convolver::initBlur( int rx, int ry )
{
   int sx = 2 * rx + 1, sy = 2 * ry + 1;
   std::vector<int> kernel(sx * sy, 1);
   _init(sx, sy, 1.0 / (sx * sy), &kernel[0]);
}

void Convolver::initSobelX()
{
   /* Sobel discrete differential operator value (x value) */
   static const int sobel_kernel_x[3 * 3] = { 1, 0, -1, 2, 0, -2, 1, 0, -1 }; 
   _init(3, 3, 1, sobel_kernel_x); 
}

void Convolver::initSobelY()
{
   /* Sobel discrete differential operator value (y value) */
   static const int sobel_kernel_y[3 * 3] = { 1, 2, 1, 0, 0, 0, -1, -2, -1 };
   _init(3, 3, 1, sobel_kernel_y); 
}

void Convolver::deInit()
{
   if (!isInit())
      throw LogicException("invalid de-initialization");

   delete[] _kernel;

   _kernel = 0;
   _invBias = 1.0;
   _rows = _cols = 0;
}

bool Convolver::isInit()
{
   return _kernel == 0 ? false : true;
}

void Convolver::apply()
{
   if (!isInit())
      throw LogicException("no convolver initialization");

   int width = _img.getWidth(), height = _img.getHeight();

   int x_offset = _rows >> 1;
   int y_offset = _cols >> 1;

   for (int y = y_offset; y < height - y_offset; y++)
   {
      for (int x = x_offset; x < width - x_offset; x++)
      {
         double value = 0;

         for (int k = -y_offset; k <= y_offset; k++)
            for (int l = -x_offset; l <= x_offset; l++)
               value += _img.getByte(x + l, y + k)  * _kernel[(k + y_offset) * _cols + (l + x_offset)];

         value *= _invBias;

         if (value < 0)
            value = 0;
         else if (value > 255)
            value = 255;

         _img.getByte(x, y) = value;
      }
   }
}

Convolver::~Convolver()
{
   if (isInit())
      deInit();
}

