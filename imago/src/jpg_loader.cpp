#include <cstdio>

#include "jpeglib.h"

#include "image.h"
#include "jpg_loader.h"

using namespace imago;

JpgLoader::JpgLoader() 
{
}

bool JpgLoader::loadImage( Image &img, const char *file_name )
{
   FILE* f = fopen(file_name, "rb");

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
         for (size_t x = 0; x < img.getWidth(); x++)
         {
            byte px;
            unsigned r, g, b;

            if (JCS_GRAYSCALE == cinfo.out_color_space)
            {
               px = (byte)data[x];
            }
            else if (JCS_RGB == cinfo.out_color_space) //3 == cinfo.output_components && 8 == cinfo.data_precision) // RGB
            {
               r = 299 * data[x * 3];
               g = 587 * data[x * 3 + 1];
               b = 114 * data[x * 3 + 2];
               px = (byte)(( r + g + b)/1000);
            }
            else 
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

typedef struct
{
   struct jpeg_error_mgr pub;
   jmp_buf jmpbuf;
} JPGErr;
    
typedef struct
{
   /*io manager*/
   struct jpeg_source_mgr src;

   int skip;
   struct jpeg_decompress_struct cinfo;
} JPGCtx;
    
static void _fatal_error(j_common_ptr cinfo) 
{
   JPGErr *err = (JPGErr *) cinfo->err;
   longjmp(err->jmpbuf, 1);
}

static void stub(j_decompress_ptr cinfo) {}
static void _nonfatal_error(j_common_ptr cinfo) { }
static void _nonfatal_error2(j_common_ptr cinfo, int lev) {}
/*a JPEG is always carried in a complete, single MPEG4 AU so no refill*/
    
static boolean fill_input_buffer(j_decompress_ptr cinfo) { return 0; }
    
static void skip_input_data(j_decompress_ptr cinfo, long num_bytes)
{
   JPGCtx *jpx = (JPGCtx *) cinfo->src;
   if (num_bytes > (long) jpx->src.bytes_in_buffer)
   {
      jpx->skip = num_bytes - jpx->src.bytes_in_buffer;
      jpx->src.next_input_byte += jpx->src.bytes_in_buffer;
      jpx->src.bytes_in_buffer = 0;
   }
   else
   {
      jpx->src.bytes_in_buffer -= num_bytes;
      jpx->src.next_input_byte += num_bytes;
      jpx->skip = 0;
   }
}
    
static int put_jpeg_grey_memory(unsigned char **dest_image, unsigned long *image_size, 
   unsigned char *input_image, int width, int height, int quality)
{
   int y;
   JSAMPROW row_ptr[1];
   struct jpeg_compress_struct cjpeg;
   struct jpeg_error_mgr jerr;

   cjpeg.err = jpeg_std_error(&jerr);
   jpeg_create_compress(&cjpeg);
   cjpeg.image_width = width;
   cjpeg.image_height = height;
   cjpeg.input_components = 1; /* one colour component */
   cjpeg.in_color_space = JCS_GRAYSCALE;

   jpeg_set_defaults(&cjpeg);

   jpeg_set_quality(&cjpeg, quality, TRUE);
   cjpeg.dct_method = JDCT_FASTEST;
   jpeg_mem_dest(&cjpeg, dest_image, image_size);  // data written to mem

   jpeg_start_compress (&cjpeg, TRUE);

   row_ptr[0] = input_image;
    
   for (y = 0; y < height; y++) 
   {
      jpeg_write_scanlines(&cjpeg, row_ptr, 1);
      row_ptr[0] += width;
   }
    
   jpeg_finish_compress(&cjpeg);
   jpeg_destroy_compress(&cjpeg);

   return true;
}

bool JpgLoader::loadImage( Image &img, const char *begin, const char *end )
{
   unsigned int width, height, pixel_format;
   int i;
   int stride;
   JPGErr jper;
   JPGCtx jpx;
        
   jpx.cinfo.err = jpeg_std_error(&(jper.pub));
   jper.pub.error_exit = _fatal_error;
   jper.pub.output_message = _nonfatal_error;
   jper.pub.emit_message = _nonfatal_error2;
   
   if (setjmp(jper.jmpbuf))
   {
      jpeg_destroy_decompress(&jpx.cinfo);
      return false;
   }
        
   jpeg_create_decompress(&jpx.cinfo);
        
   jpx.src.init_source = stub;
   jpx.src.fill_input_buffer = fill_input_buffer;
   jpx.src.skip_input_data = skip_input_data;
   jpx.src.resync_to_restart = jpeg_resync_to_restart;
   jpx.src.term_source = stub;
   jpx.skip = 0;
   jpx.src.next_input_byte = (const JOCTET *)(begin);
   jpx.src.bytes_in_buffer = (end - begin) / sizeof(char);
   jpx.cinfo.src = (struct jpeg_source_mgr *) &jpx.src;
        
   do 
   {
      i = jpeg_read_header(&jpx.cinfo, TRUE);
   } while (i == JPEG_HEADER_TABLES_ONLY);

   if (i == JPEG_SUSPENDED) 
   {
      jpeg_destroy_decompress(&jpx.cinfo);
      return false;
   }
        
   width = jpx.cinfo.image_width;
   height = jpx.cinfo.image_height;
   stride = width * jpx.cinfo.num_components;

   switch (jpx.cinfo.num_components) 
   {
   case 1:     
      pixel_format = JCS_GRAYSCALE;
      break;
   case 3:     
      pixel_format = JCS_RGB;
      break;
   default:    
      jpeg_destroy_decompress(&jpx.cinfo);
      return false;
   }
        
   img.init(width, height);
   
   jpx.cinfo.do_fancy_upsampling = FALSE;
   jpx.cinfo.do_block_smoothing = FALSE;

   if (!jpeg_start_decompress(&jpx.cinfo))
   {
      jpeg_destroy_decompress(&jpx.cinfo);
      return false;
   }

   static const int JPEG_MAX_SCAN_BLOCK_HEIGHT = 16;

   if (jpx.cinfo.rec_outbuf_height > JPEG_MAX_SCAN_BLOCK_HEIGHT)
   {
      jpeg_destroy_decompress(&jpx.cinfo);
      return false;
   }
        
   JSAMPROW data = new JSAMPLE[jpx.cinfo.output_width * jpx.cinfo.num_components];

   for (size_t y = 0; jpx.cinfo.output_scanline < jpx.cinfo.output_height; y++)
   {
      JDIMENSION num_scanlines;
      num_scanlines = jpeg_read_scanlines(&jpx.cinfo, &data, 1);

      for (size_t x = 0; x < img.getWidth(); x++)
      {
         byte px;
         unsigned r, g, b;

         if (JCS_GRAYSCALE == jpx.cinfo.out_color_space)
         {
            px = data[x];
         }
         else if (JCS_RGB == jpx.cinfo.out_color_space) 
         {
            r = 299 * data[x * 3];
            g = 587 * data[x * 3 + 1];
            b = 114 * data[x * 3 + 2];
            px = (unsigned char)((r + g + b) / 1000);
         }
         else 
         {
            jpeg_finish_decompress(&jpx.cinfo);
            jpeg_destroy_decompress(&jpx.cinfo);
            delete[] data;
            return false;
         }

         img.getByte(x, y) = px;
      }
   }
   jpeg_finish_decompress(&jpx.cinfo);
   jpeg_destroy_decompress(&jpx.cinfo);
   delete[] data;

   return true;
}

JpgLoader::~JpgLoader()
{
}