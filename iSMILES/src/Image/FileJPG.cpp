#include <stdio.h>
#include <stdexcept>
#include <setjmp.h>
extern "C"
{
    #define HAVE_PROTOTYPES
    #include "../../../libjpeg/jpeglib.h"
}
#include "FileJPG.h"

namespace gga
{
    FileJPG::FileJPG(void)
    {
    }

    FileJPG::~FileJPG(void)
    {
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

    bool FileJPG::save(const std::string& path, const Image& img)
    {
        FILE* f = fopen(path.c_str(), "wb");
        if(0==f)
            return false;
        struct jpeg_compress_struct cinfo;
//        struct jpeg_error_mgr       jerr;
        try
        {
            jpeg_set_defaults  (&cinfo);
            jpeg_set_colorspace(&cinfo, JCS_GRAYSCALE);
            jpeg_start_compress(&cinfo, 1);

//TBD:

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

}
