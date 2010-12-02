#include <stdio.h>
#include <stdexcept>
#include <setjmp.h>
extern "C"
{
    #define HAVE_PROTOTYPES
    #include "jpeglib.h"
}
#include "ImageFilter.h"
#include "FileJPG.h"

namespace gga
{
static const int JPEG_MAX_SCAN_BLOCK_HEIGHT = 16;

static const unsigned char* getApp1Marker(const unsigned char* jpegBuff, size_t size, size_t* len)
{
    for(size_t i = 0; i < size-16; i++, jpegBuff++)
     if(0xFF==*jpegBuff && 0xE1==*(jpegBuff+1) && 'E'==*(jpegBuff+4) && 0==memcmp(jpegBuff+4, "Exif\0\0", 6))    // APP1 MARKER with EXIF Found
    {
        *len = (unsigned short) *(jpegBuff+3) + (*(jpegBuff+2)<<8);    // big endian
        return jpegBuff;
    }
     return 0;
}


static unsigned short getOrientation (const unsigned char* app1, size_t size)
{
    if(0 != app1 && size > 16)
        for(size_t i = 4+6; i < size-4; i++, app1++)
         if(0x01==*app1 && 0x12==*(app1+1))    // ORIENTATION TAG ID=0x112 Type=short
        {
            return (unsigned short) *(app1+3) + (*(app1+2)<<8);    // big endian;
        }
    return -1;
}

static void jpeg_exif_rotate (Image* img, unsigned short orientation)
{
    int angle = 0;
    switch(orientation)
    {
        case 1: // standard orientation, do nothing
            break;
        case 2: // flipped right-left
            break;
        case 3: // rotated 180
                angle = 180;
            break;

        case 4: // flipped top-bottom
            break;
        case 5: // flipped diagonally around '\'
            break;
        case 6: // 90 CW
                angle = 90;
            break;
        case 7: // flipped diagonally around '/'
            break;
        case 8: // 90 CCW
                angle = 270;
            break;
        case -1:    //not found
        default:    // shouldn't happen
            break;
    }
        
    if(0 != angle)
    {
        const Image src(*img);
        rotateImage(src, (float)angle, img);
    }
}

//=============================================================================

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
		
      //TODO: What is it? Compile error?.. Why?
      //jpeg_mem_dest(&cjpeg, dest_image, image_size);  // data written to mem

		jpeg_start_compress (&cjpeg, TRUE);

		row_ptr[0] = input_image;
    
		for (y = 0; y < height; y++) {
			jpeg_write_scanlines(&cjpeg, row_ptr, 1);
			row_ptr[0] += width;
		}
    
		jpeg_finish_compress(&cjpeg);
		jpeg_destroy_compress(&cjpeg);

		return true;
	}


    FileJPG::FileJPG(void)
    {
    }

    FileJPG::~FileJPG(void)
    {
    }
    
    bool FileJPG::load(const std::vector<unsigned char>& buff, Image* img)
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
        if (setjmp(jper.jmpbuf)) {
            jpeg_destroy_decompress(&jpx.cinfo);
            return false;
        }
        
        /*create decompress struct*/
        jpeg_create_decompress(&jpx.cinfo);
        
        /*prepare IO*/
        jpx.src.init_source = stub;
        jpx.src.fill_input_buffer = fill_input_buffer;
        jpx.src.skip_input_data = skip_input_data;
        jpx.src.resync_to_restart = jpeg_resync_to_restart;
        jpx.src.term_source = stub;
        jpx.skip = 0;
        jpx.src.next_input_byte = (const JOCTET *)(&(buff[0]));
        jpx.src.bytes_in_buffer = buff.size();
        jpx.cinfo.src = (struct jpeg_source_mgr *) &jpx.src;
        
        /*read header*/
        do 
        {
            i = jpeg_read_header(&jpx.cinfo, TRUE);
        }
        while (i == JPEG_HEADER_TABLES_ONLY);

        /*we're supposed to have the full image in the buffer, wrong stream*/
        if (i == JPEG_SUSPENDED) {
            jpeg_destroy_decompress(&jpx.cinfo);
            return false;
        }
        
        width = jpx.cinfo.image_width;
        height = jpx.cinfo.image_height;
        stride = width * jpx.cinfo.num_components;

        switch (jpx.cinfo.num_components) {
        case 1:     pixel_format = JCS_GRAYSCALE;
            break;
        case 3:     pixel_format = JCS_RGB;
            break;
        default:    jpeg_destroy_decompress(&jpx.cinfo);
            return false;
        }
        
        img->setSize(width, height, IT_GRAYSCALE);
        /*decode*/
        jpx.cinfo.do_fancy_upsampling = FALSE;
        jpx.cinfo.do_block_smoothing = FALSE;
        if (!jpeg_start_decompress(&jpx.cinfo))
        {
            jpeg_destroy_decompress(&jpx.cinfo);
            return false;
        }
        if (jpx.cinfo.rec_outbuf_height>JPEG_MAX_SCAN_BLOCK_HEIGHT)
        {
            jpeg_destroy_decompress(&jpx.cinfo);
            return false;
        }
        
        JSAMPROW data = new JSAMPLE[jpx.cinfo.output_width * jpx.cinfo.num_components];
        for(size_t y = 0; jpx.cinfo.output_scanline < jpx.cinfo.output_height; y++)
        {
            JDIMENSION num_scanlines;
            num_scanlines = jpeg_read_scanlines(&jpx.cinfo, &data, 1);
            for(size_t x = 0; x < img->getWidth(); x++)
            {
                Pixel    px;
                unsigned r, g, b;

                if(JCS_GRAYSCALE == jpx.cinfo.out_color_space)
                {
                    px = Pixel(data[x]);
                }
                else if(JCS_RGB == jpx.cinfo.out_color_space) //3 == cinfo.output_components && 8 == cinfo.data_precision) // RGB
                {
                    r = 299 * data[x * 3];
                    g = 587 * data[x * 3 + 1];
                    b = 114 * data[x * 3 + 2];
                    px = Pixel((unsigned char)(( r + g + b)/1000));
                }
                else // error: unsuppported image type
                {
                    jpeg_finish_decompress(&jpx.cinfo);
                    jpeg_destroy_decompress(&jpx.cinfo);
                    delete[] data;
                    return false;
                }

                img->setPixel(x, y, px);
            }
        }
        jpeg_finish_decompress(&jpx.cinfo);
        jpeg_destroy_decompress(&jpx.cinfo);
        delete[] data;

        size_t len=0;
        const unsigned char*  app1 = getApp1Marker (&buff[0], buff.size(), &len);
        unsigned short orientation = getOrientation(app1, len);
        if(-1 != orientation)
            img->setOrientation(orientation);  //jpeg_exif_rotate (img, orientation);
        return true;
    }

    bool FileJPG::load(const std::string& path, Image* img)
    {
        FILE* f = fopen(path.c_str(), "rb");
        if(0==f)
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

            img->setSize(cinfo.output_width, cinfo.output_height, IT_GRAYSCALE);
            JSAMPROW data = new JSAMPLE[cinfo.output_width * cinfo.num_components];
            for(size_t y = 0; cinfo.output_scanline < cinfo.output_height; y++)
            {
                JDIMENSION num_scanlines;
                num_scanlines = jpeg_read_scanlines(&cinfo, &data, 1);
                for(size_t x = 0; x < img->getWidth(); x++)
                {
                    Pixel    px;
                    unsigned r, g, b;

                    if(JCS_GRAYSCALE == cinfo.out_color_space)
                    {
                        px = Pixel(data[x]);
                    }
                    else if(JCS_RGB == cinfo.out_color_space) //3 == cinfo.output_components && 8 == cinfo.data_precision) // RGB
                    {
                        r = 299 * data[x * 3];
                        g = 587 * data[x * 3 + 1];
                        b = 114 * data[x * 3 + 2];
                        px = Pixel((unsigned char)(( r + g + b)/1000));
                    }
                    else // error: unsuppported image type
                    {
                        jpeg_finish_decompress(&cinfo);
                        jpeg_destroy_decompress(&cinfo);
                        delete[] data;
                        fclose(f);
                        return false;
                    }

                    img->setPixel(x, y, px);
                }

            }

            jpeg_finish_decompress(&cinfo);
            jpeg_destroy_decompress(&cinfo);
            delete[] data;

            fseek(f, 0, SEEK_SET);
            std::vector<unsigned char> buff(32*1024);
            size_t size = fread(&buff[0], 1, buff.size(), f);
            size_t len=0;
            const unsigned char*  app1 = getApp1Marker (&buff[0], size, &len);
            unsigned short orientation = getOrientation(app1, len);
            if(-1 != orientation)
                img->setOrientation(orientation);  //jpeg_exif_rotate (img, orientation);
            fclose(f);
        }
        catch(std::exception& )
        {
            jpeg_destroy_decompress(&cinfo);
            fclose(f);
            return false;
        }
        return true;
    }

    bool FileJPG::save(const std::string& path, const Image& img, int quality)
    {
        FILE* f = fopen(path.c_str(), "wb");
        if(0==f)
            return false;
        struct jpeg_compress_struct cinfo;
        struct jpeg_error_mgr       jerr;
        cinfo.err = jpeg_std_error(&jerr);
        try
        {
            jpeg_create_compress(&cinfo);
            jpeg_stdio_dest     (&cinfo, f);
            cinfo.image_width  = img.getWidth ();
            cinfo.image_height = img.getHeight();
            cinfo.input_components = 1;
            cinfo.in_color_space = JCS_GRAYSCALE;
            jpeg_set_defaults(&cinfo);
            jpeg_set_quality (&cinfo, quality, 1);//FALSE);
            jpeg_start_compress(&cinfo, 1);

            JSAMPROW scanline = (JSAMPROW)img.getPixels();
            while(1==jpeg_write_scanlines(&cinfo, &scanline, 1))
                scanline += img.getWidth();

            jpeg_finish_compress (&cinfo);
            jpeg_destroy_compress(&cinfo);

            fclose(f);
        }
        catch(std::exception& )
        {
            fclose(f);
            jpeg_destroy_compress(&cinfo);
            return false;
        }
        return true;
    }
 
    bool FileJPG::save(std::vector<unsigned char>* out, const Image& img, int quality)
    {
        unsigned char *dest_image = 0;
        unsigned long  image_size = 0;

        put_jpeg_grey_memory(&dest_image, &image_size, (unsigned char *)img.getPixels(), img.getWidth(), img.getHeight(), quality);
        if(0==out || 0==image_size)
            return false;
        out->resize(image_size);
        memcpy(&out->front(), dest_image, image_size);
        free(dest_image);
        return true;
    }


}
