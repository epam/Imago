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
 * @file png_saver.cpp
 * 
 * @brief   Implements the png saver Class. 
 */

#include <cstdio>

#include "exception.h"
#include "image.h"
#include "png_saver.h"
#include "output.h"

using namespace imago;


PngSaver::PngSaver( Output &out ) : _out(out)
{
}

/**
 * @brief   Saves an image. 
 * 
 * @exception ERROR Thrown when @c FileName is @c null, file opening failed, or some of png format processing functions failed 
 * 
 * @param   FileName If non-null, name of the file. 
 */
void PngSaver::saveImage( const Image &_img )
{
   int i, j;
   png_struct *png;
   png_info *info;
   png_byte **data;
   
   png = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)0, (png_error_ptr)0, (png_error_ptr)0);

   if (!png)
      throw Exception("Error creating png write struct");

   info = png_create_info_struct(png);
   if (!info)
   {
      png_destroy_write_struct(&png, (png_infopp)0);
      throw Exception("Error creating png info struct");
   }

   if (setjmp(png_jmpbuf(png)))
   {
      png_destroy_write_struct(&png, &info);
      throw Exception("Png error");
   }  

   int w = _img.getWidth(), h = _img.getHeight();

   png_set_write_fn(png, &_out, _writer, 0);

   png_set_IHDR(png, info, w, h, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

   png_write_info(png, info);

   data = new png_byte*[h];

   for (i = 0; i < h; i++)
   {
      data[i] = new png_byte[w * 3];
      for (j = 0; j < w; j++)
      {
         data[i][j * 3] = data[i][j * 3 + 1] = data[i][j * 3 + 2] = _img.getByte(j, i);
      }
   }

   png_write_image(png, data);

   png_write_end(png, info);

   png_destroy_write_struct(&png, &info);

   for (i = 0; i < h; i++)
      delete[] data[i];

   delete[] data;
}

void PngSaver::_writer( png_structp png_ptr, png_bytep bytes, png_size_t size )
{
   Output *out = (Output *)png_get_progressive_ptr(png_ptr);
   out->write(bytes, size);
}

/**
* Default destructor
*/
PngSaver::~PngSaver()
{
}