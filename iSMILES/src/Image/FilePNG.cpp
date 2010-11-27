#include <stdio.h>
#include <stdexcept>
#include "png.h"
#include "FilePNG.h"

namespace gga
{
    FilePNG::FilePNG(void)
    {
    }

    FilePNG::~FilePNG(void)
    {
    }

    struct Reader
    {
        size_t Position;
        void*  Parameter;
        void (*ReadDataProc)(png_structp png_def, png_bytep data, png_size_t size);
    public:
        inline Reader(FILE* file, void (*proc)(png_structp png_def, png_bytep data, png_size_t size))
                    : Position(0), Parameter(file), ReadDataProc(proc) {}
        inline Reader(const std::vector<unsigned char>& buff, void (*proc)(png_structp png_def, png_bytep data, png_size_t size))
                    : Position(0), Parameter((void*)&buff), ReadDataProc(proc) {}
    };

    static void loadDataFromFile(png_structp png_def, png_bytep data, png_size_t size)
    {
        FILE* f = (FILE*) ((Reader*)png_get_progressive_ptr(png_def))->Parameter;
        if(fread(data, 1, size, f) != (size_t)size)
            throw std::runtime_error("File read error");
    }

    static void loadDataFromBuffer(png_structp png_def, png_bytep data, png_size_t size)
    {
        std::vector<unsigned char>* buf = (std::vector<unsigned char>*) ((Reader*) png_get_progressive_ptr(png_def))->Parameter;
        void* in = &(*buf)[((Reader*)(std::vector<unsigned char>*) png_get_progressive_ptr(png_def))->Position];
        ((Reader*)(std::vector<unsigned char>*) png_get_progressive_ptr(png_def))->Position += size;
        memcpy(data, in, size);
    }


    bool loadImage(const Reader& in, Image* img)
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

        try
        {
            png_set_read_fn(png, (void*)&in, in.ReadDataProc);

            png_byte bit_depth = png_get_bit_depth(png, info);
            png_byte color_type = png_get_color_type(png, info);
   
            if (color_type == PNG_COLOR_TYPE_PALETTE)
                png_set_palette_to_rgb(png);

            if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
                png_set_expand_gray_1_2_4_to_8(png);

            if (png_get_valid(png, info, PNG_INFO_tRNS))
                png_set_tRNS_to_alpha(png);

            png_read_png(png, info, PNG_TRANSFORM_IDENTITY, 0);
        }
        catch(std::exception& )
        {
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
            else if (PNG_COLOR_TYPE_GRAY == info->color_type)//info->pixel_depth == 8)    // gray scale
            {
                px = Pixel(data[y][x]);
            }
            else if (PNG_COLOR_TYPE_GRAY_ALPHA == info->color_type)
            {
                a = (1000 * data[y][x * 2 + 1]) / 255;
                px = Pixel((data[y][x * 2] * a)/1000);
            }
            else if (PNG_COLOR_TYPE_RGB == info->color_type)//info->pixel_depth == 24)   // RGB | Lab | ...
            {
                r = 299 * data[y][x * 3];
                g = 587 * data[y][x * 3 + 1];
                b = 114 * data[y][x * 3 + 2];
                px = Pixel((unsigned char)(( r + g + b)/1000));
            }
            else if (PNG_COLOR_TYPE_RGB_ALPHA == info->color_type)//info->pixel_depth == 32)   // RGB + Alpha | CMYK | YCCK
            {
                r = 299 * data[y][x * 4];
                g = 587 * data[y][x * 4 + 1];
                b = 114 * data[y][x * 4 + 2];
                a =(1000* data[y][x * 4 + 3]) / 255;
                px = Pixel((unsigned char)((r + g + b) * a)/1000);
            }
//            else if(PNG_COLOR_TYPE_PALETTE == info->color_type)
//            {}
            else    // error: unsuppported image type
            {
                png_destroy_read_struct(&png, &info, &end_info);
                return false;
            }
            img->setPixel(x, y, px);
        }

        png_destroy_read_struct(&png, &info, &end_info);
        return true;
    }

    bool FilePNG::load(const std::string& path, Image* img)
    {
        FILE* f = fopen(path.c_str(), "rb");
        if(0==f)
        {
            return false;
        }

        Reader in(f, loadDataFromFile);
        if(!loadImage(in, img))
        {
            fclose(f);
            img->setSize(0, 0);
            return false;
        }
        fclose(f);
        return true;
    }

    bool FilePNG::load(const std::vector<unsigned char>& buff, Image* img)
    {
        Reader in(buff, loadDataFromBuffer);
        if(!loadImage(in, img))
        {
            img->setSize(0, 0);
            return false;
        }
        return true;
    }

//=============================================================================================================

    struct Writer
    {
        void*  Parameter;
        void (*SaveDataProc)(png_structp png_def, png_bytep data, png_size_t size);
    public:
        inline Writer(FILE* file, void (*proc)(png_structp png_def, png_bytep data, png_size_t size))
                    : Parameter(file), SaveDataProc(proc) {}
        inline Writer(std::vector<unsigned char>* buff, void (*proc)(png_structp png_def, png_bytep data, png_size_t size))
                    : Parameter(buff), SaveDataProc(proc) {}
    };

    static void saveDataToFile(png_structp png_def, png_bytep data, png_size_t size )
    {
        FILE* f = (FILE*) ((Writer*)png_get_progressive_ptr(png_def))->Parameter;
        if(fwrite(data, 1, size, f) != (size_t)size)
            throw std::runtime_error("File write error");
    }

    static void saveDataToBuffer(png_structp png_def, png_bytep data, png_size_t size )
    {
        std::vector<unsigned char>* buf = (std::vector<unsigned char>*) ((Writer*)png_get_progressive_ptr(png_def))->Parameter;
        buf->resize(buf->size() + size);
        void* out = &(*buf)[buf->size() - size];
        memcpy(out, data, size);
    }

    static bool saveImage(const Writer& out, const Image& img)
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

        png_byte **data;
        data = new png_byte* [img.getHeight()];

        for (size_t y = 0; y < img.getHeight(); y++)
            data[y] = (png_byte*)(img.getPixels() + y * img.getWidth());

        try
        {
            png_set_write_fn(png, (void*)&out, out.SaveDataProc, 0);

            png_set_IHDR(png, info, img.getWidth(), img.getHeight(), 8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
            png_write_info(png, info);

            png_write_image(png, data);
            png_write_end  (png, info);
        }
        catch(std::exception& )
        {
            delete[] data;
            png_destroy_write_struct(&png, &info);
            return false;
        }

        png_destroy_write_struct(&png, &info);
        delete[] data;
        return true;
    }

    bool FilePNG::save(const std::string& path, const Image& img)
    {
        FILE* f = fopen(path.c_str(), "wb");
        if(0==f)
        {
            return false;
        }
        Writer out(f, saveDataToFile);
        if(!saveImage(out, img))
        {
            fclose(f);
            return false;
        }
        fclose(f);
        return true;
    }

    bool FilePNG::save(std::vector<unsigned char>* out, const Image& img)
    {
        if(0==out)
        {
            return false;
        }
        out->resize(0);
        out->reserve(24*1024);
        Writer wout(out, saveDataToBuffer);
        if(!saveImage(wout, img))
        {
            out->clear();
            return false;
        }
        return true;
    }
}
