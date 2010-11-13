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
 * @file png_loader.cpp
 * 
 * @brief   Implements the png loader Class. 
 */

#include "exception.h"
#include "scanner.h"
#include "png.h"
#include "png_loader.h"
#include "image.h"

using namespace imago;

/**
 * @exception  ERROR Thrown when @c filename is @c null, or an error occured during file opening 
 * 
 * @param   FileName If non-null, name of the file. 
 */
PngLoader::PngLoader( Scanner &scan ) : _scan(scan)
{
	png_byte pngsig[8];
	int is_png = 0;

   _scan.read(8, pngsig);

   if (_scan.isEOF())
      throw LogicException("File is not in PNG format");;

	is_png = png_sig_cmp(pngsig, 0, 8);

   if (is_png != 0)
      throw LogicException("File is not in PNG format");

   _scan.seek(0, 0);
}

/**
 * @brief   Loads an image. 
 * 
 * @exception  ERROR Thrown when some of png processing function fails  
 * 
 * @param [out]  I - loaded image
 */
void PngLoader::loadImage( Image &I )
{
   int i, j;
   png_structp png;
   png_infop info, end_info;
   png_byte **data;
   png_byte r, g, b, a;
   r = g = b = a = 0;
   
   png = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)0, (png_error_ptr)0, (png_error_ptr)0);

   if (png == 0)
      throw Exception("Error creating png read struct");

   info = png_create_info_struct(png);

   if (info == 0)
   {
      png_destroy_read_struct(&png, (png_infopp)0, (png_infopp)0);
      throw Exception("Error creating png info struct");
   }

   end_info = png_create_info_struct(png);
   
   if (!end_info)
   {
      png_destroy_read_struct(&png, &info, (png_infopp)0);
      throw Exception("Error creating png info struct");
   }

   if (setjmp(png_jmpbuf(png)))
   {
      png_destroy_read_struct(&png, &info, &end_info);
      throw Exception("Png error");
   }

   png_set_read_fn(png, &_scan, _reader);

   png_byte bit_depth = png_get_bit_depth(png, info);
   png_byte color_type = png_get_color_type(png, info);
   
   if (color_type == PNG_COLOR_TYPE_PALETTE)
      png_set_palette_to_rgb(png);

   if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
      png_set_expand_gray_1_2_4_to_8(png);

   if (png_get_valid(png, info, PNG_INFO_tRNS))
      png_set_tRNS_to_alpha(png);

   /*
   png_color_16 my_background;
   my_background.red = my_background.green = my_background.blue = 255;
   png_color_16p image_background;

   
   if (png_get_bKGD(png, info, &image_background))
      png_set_background(png, image_background,
                         PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
   else
      png_set_background(png, &my_background,
                         PNG_BACKGROUND_GAMMA_SCREEN, 0, 1.0);
   */
   png_read_png(png, info, PNG_TRANSFORM_IDENTITY, 0);

   data = png_get_rows(png, info);

   I.init(info->width, info->height);

   int w = I.getWidth(), h = I.getHeight();

   for (i = 0; i < h; i++)
   { 
      for (j = 0; j < w; j++)
      {
         if (info->pixel_depth == 1)
         {
            byte pix = ((data[i][j / 8]) & (1 << (7 - j % 8))) > 0;
            r = g = b = (pix) ? 255 : 0;
            I.getByte(j, i) = (byte)(0.299f * r + 0.114f * b + 0.587f * g);
         }
         else if (info->pixel_depth == 8)
         {
            r = g = b = data[i][j];
            I.getByte(j, i) = (byte)(0.299f * r + 0.114f * b + 0.587f * g);
         }
         else if (info->pixel_depth == 24)
         {
            r = data[i][j * 3];
            g = data[i][j * 3 + 1];
            b = data[i][j * 3 + 2];
            I.getByte(j, i) = (byte)(0.299f * r + 0.114f * b + 0.587f * g);
         }
         else if (info->pixel_depth == 32)
         {
            r = data[i][j * 4];
            g = data[i][j * 4 + 1];
            b = data[i][j * 4 + 2];
            a = data[i][j * 4 + 3];
            float aa = a / 255.0f;
            I.getByte(j, i) = (byte)((0.299f * r + 0.114f * b + 0.587f * g) * aa
                                  + 255 * (1 - aa));
         }
      }
   }

   png_destroy_read_struct(&png, &info, &end_info);
}

void PngLoader::_reader( png_structp png_ptr, png_bytep bytes, png_size_t size )
{
   Scanner *scan = (Scanner *)png_get_progressive_ptr(png_ptr);
   scan->read(size, bytes);
}

/**
 * Default destructor
 */
PngLoader::~PngLoader()
{
}


