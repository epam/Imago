#include <stdio.h>
#include <stdexcept>
#include "../../../libpng/png.h"
#include "FilePNG.h"

namespace gga
{
    FilePNG::FilePNG(void)
    {
    }

    FilePNG::~FilePNG(void)
    {
    }

    static void loadData(png_structp png_def, png_bytep data, png_size_t size )
    {
        FILE* f = (FILE*) png_get_progressive_ptr(png_def);
        if(fread(data, 1, size, f) != (size_t)size)
            throw std::runtime_error("File read error");
    }

    static void saveData(png_structp png_def, png_bytep data, png_size_t size )
    {
        FILE* f = (FILE*) png_get_progressive_ptr(png_def);
        if(fwrite(data, 1, size, f) != (size_t)size)
            throw std::runtime_error("File write error");
    }

    bool FilePNG::load(const std::string& path, Image* img)
    {
        png_structp png;
        png_infop   info, end_info;
   
        png = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)0, (png_error_ptr)0, (png_error_ptr)0);

        if (png == 0)
            return false;

        info = png_create_info_struct(png);

        if (info == 0)
        {
            png_destroy_read_struct(&png, (png_infopp)0, (png_infopp)0);
            return false;
        }

        end_info = png_create_info_struct(png);
   
        if (!end_info)
        {
            png_destroy_read_struct(&png, &info, (png_infopp)0);
            return false;
        }

        if (setjmp(png_jmpbuf(png)))
        {
            png_destroy_read_struct(&png, &info, &end_info);
            return false;
        }

        FILE* f = fopen(path.c_str(), "rb");
        if(0==f)
        {
            png_destroy_read_struct(&png, &info, &end_info);
            return false;
        }

        try
        {
            png_set_read_fn(png, f, loadData);

            png_byte bit_depth = png_get_bit_depth(png, info);
            png_byte color_type = png_get_color_type(png, info);
   
            if (color_type == PNG_COLOR_TYPE_PALETTE)
                png_set_palette_to_rgb(png);

            if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
                png_set_expand_gray_1_2_4_to_8(png);

            if (png_get_valid(png, info, PNG_INFO_tRNS))
                png_set_tRNS_to_alpha(png);

            png_read_png(png, info, PNG_TRANSFORM_IDENTITY, 0);
            fclose(f);
        }
        catch(std::exception& )
        {
            fclose(f);
            png_destroy_read_struct(&png, &info, &end_info);
            return false;
        }

        img->setSize(info->width, info->height, (1==info->pixel_depth ? IT_BW : IT_GRAYSCALE));         // black white / grayscale
        png_byte ** data = png_get_rows(png, info); // load whole file

        for (size_t y = 0; y < info->height; y++)
         for(size_t x = 0; x < info->width ; x++)
        {
            Pixel    px;
            unsigned r, g, b, a;

            if (info->pixel_depth == 1)         // black white
            {
                px = Pixel( ((data[y][x / 8]) & (1 << (7 - x % 8))) != 0 ? BACKGROUND : INK);
            }
            else if (info->pixel_depth == 8)    // gray scale
            {
                px = Pixel(data[y][x]);
            }
            else if (info->pixel_depth == 24)   // RGB
            {
                r = 299 * data[y][x * 3];
                g = 587 * data[y][x * 3 + 1];
                b = 114 * data[y][x * 3 + 2];
                px = Pixel((unsigned char)(( r + g + b)/1000));
            }
            else if (info->pixel_depth == 32)   // RGB + Alpha
            {
                r = 299 * data[y][x * 4];
                g = 587 * data[y][x * 4 + 1];
                b = 114 * data[y][x * 4 + 2];
                a =(1000* data[y][x * 4 + 3]) / 255;
                px = Pixel((unsigned char)((r + g + b) * a)/1000);
            }
            else // error: unsuppported image type
            {
                png_destroy_read_struct(&png, &info, &end_info);
                return false;
            }
            img->setPixel(x, y, px);
        }

        png_destroy_read_struct(&png, &info, &end_info);
        return true;
    }

    bool FilePNG::save(const std::string& path, const Image& img)
    {
        png_struct *png;
        png_info *info;
   
        png = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)0, (png_error_ptr)0, (png_error_ptr)0);

        if (!png)
            return false;
        info = png_create_info_struct(png);
        if (!info)
        {
            png_destroy_write_struct(&png, (png_infopp)0);
            return false;
        }

        if (setjmp(png_jmpbuf(png)))
        {
            png_destroy_write_struct(&png, &info);
            return false;
        }  

        FILE* f = fopen(path.c_str(), "wb");
        if(0==f)
        {
            png_destroy_write_struct(&png, &info);
            return false;
        }

        png_byte **data;
        data = new png_byte* [img.getHeight()];

        for (size_t y = 0; y < img.getHeight(); y++)
            data[y] = (png_byte*)(img.getPixels() + y * img.getWidth());

        try
        {
            png_set_write_fn(png, f, saveData, 0);

            png_set_IHDR(png, info, img.getWidth(), img.getHeight(), 8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
            png_write_info(png, info);

            png_write_image(png, data);
            png_write_end  (png, info);
        }
        catch(std::exception& )
        {
            fclose(f);
            delete[] data;
            png_destroy_write_struct(&png, &info);
            return false;
        }

        fclose(f);
        png_destroy_write_struct(&png, &info);
        delete[] data;
        return true;
    }

}
