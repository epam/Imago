#include <cstdio>

#include "jpeglib.h"

#include "image.h"
#include "jpg_loader.h"

using namespace imago;

JpgLoader::JpgLoader( const char *FileName ) : _fileName(FileName)
{
}

bool JpgLoader::loadImage( Image &img )
{
   FILE* f = fopen(_fileName, "rb");

   if (f == 0)
      return false;

   struct jpeg_decompress_struct   cinfo;
   struct jpeg_error_mgr           jerr;

   try
   {
      cinfo.err = jpeg_std_error(&jerr);
      jpeg_create_decompress(&cinfo);
      jpeg_stdio_src(&cinfo, f);
      jpeg_read_header(&cinfo, 1);
      jpeg_save_markers(&cinfo, JPEG_APP0 + 1, 0xFFFF);

      // Step 4: set parameters for decompression
      {
   //                int scale = 2;
   //                cinfo.output_width = cinfo.image_width  / scale;
   //                cinfo.output_height= cinfo.image_height / scale;
   //                jpeg_calc_output_dimensions(&cinfo);
      }
      cinfo.out_color_space = JCS_GRAYSCALE;

      jpeg_start_decompress(&cinfo);

      img.init(cinfo.output_width, cinfo.output_height);
      
      JSAMPROW data = new JSAMPLE[cinfo.output_width * cinfo.num_components];
      
      for (size_t y = 0; cinfo.output_scanline < cinfo.output_height; y++)
      {
         JDIMENSION num_scanlines;
         num_scanlines = jpeg_read_scanlines(&cinfo, &data, 1);
         for(size_t x = 0; x < img.getWidth(); x++)
         {
            byte px;
            unsigned r, g, b;

            if(JCS_GRAYSCALE == cinfo.out_color_space)
            {
               px = (byte)data[x];
            }
            else if(JCS_RGB == cinfo.out_color_space) //3 == cinfo.output_components && 8 == cinfo.data_precision) // RGB
            {
               r = 299 * data[x * 3];
               g = 587 * data[x * 3 + 1];
               b = 114 * data[x * 3 + 2];
               px = (byte)(( r + g + b)/1000);
            }
            else // error: unsuppported image type
            {
               jpeg_finish_decompress(&cinfo);
               jpeg_destroy_decompress(&cinfo);
               delete[] data;
               fclose(f);
               return false;
            }

            img.getByte(x, y) = px;
         }

      }

      jpeg_finish_decompress(&cinfo);
      jpeg_destroy_decompress(&cinfo);
      delete[] data;

      fclose(f);
   }
   catch ( std::exception & )
   {
      jpeg_destroy_decompress(&cinfo);
      fclose(f);
      return false;
   }
   return true;
}

JpgLoader::~JpgLoader()
{
}