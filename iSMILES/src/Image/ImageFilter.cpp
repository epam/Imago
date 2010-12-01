#include <math.h>
#include <algorithm>
#include "ImageFilter.h"

//#define TEST in compiler command line
#ifdef TEST
    #include <stdio.h>   //test log
    #include "FilePNG.h" //test log
    #include "../Timer.h"//test log

    static gga::FilePNG png;
    extern char filename[];
    static char file[64];
#endif

namespace gga
{
    // Gaussian blur matrix:  
    //                          
    //    1    2    1          
    //    2    4    2          
    //    1    2    1          
    //                          
    //////////////////////////////////////////////////  

    void ImageFilter::prepareImageForVectorization()
    {
        if(IT_BW == Image.getType())  // not photo image
            return;
        std::vector<size_t> histogram;

#ifdef TEST
sprintf (file,"out/test-%s.flt-00_original.png", filename);
png.save(file, Image);
Timer tm, ttotal;
double totalTime=0.;
#endif

// RESIZE LARGE IMAGE
    if(Image.getWidth()/Parameters.ImageSize > 1 || Image.getHeight()/Parameters.ImageSize > 1)     // iphone: 2592 (5Mpx) or 1296 
    {
        size_t n = (Image.getWidth() > Image.getHeight() ? Image.getWidth() : Image.getHeight()) / Parameters.ImageSize;
        if(n > 1)
            Image.resizeLinear(n);
            //Image.resizeMaxContrast(n)
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("Image.resizeLinear: %.4f sec. n=%d, W=%d, H=%d\n", tm.getElapsedTime(), n, Image.getWidth(), Image.getHeight());
sprintf (file,"out/test-%s.flt-01_resize-lin.png", filename);
png.save(file, Image);
tm.reset();
#endif
    }

// UNSHARP MASK 1 for very low contrast and unsharp images and camera shake effect
        if(0!=Parameters.UnsharpMaskAmount)
            unsharpMaskImage(&Image, Parameters.UnsharpMaskRadius, 1., Parameters.UnsharpMaskAmount, (int)Parameters.UnsharpMaskThreshold);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("unsharpMaskImage: %.4f sec. R=%f\n", tm.getElapsedTime(), Parameters.UnsharpMaskRadius);
sprintf (file,"out/test-%s.flt-03_unsharp-mask-1.png", filename);
png.save(file, Image);
tm.reset();
#endif

// BLUR - remove noise
        if(0 != Parameters.RadiusBlur1)
        {
            blurImage(&Image, Parameters.RadiusBlur1);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("blurImage: %.4f sec. R=%d, bg=%d\n", tm.getElapsedTime(), Parameters.RadiusBlur1, getBackgroundValue(Image));
sprintf (file,"out/test-%s.flt-05_blur-1.png", filename);
png.save(file, Image);
tm.reset();
#endif
        }

// STRETCH increase contrast
        if(0 != Parameters.StretchImage)
        {
            makeHistogram (Image, &histogram);
            size_t minColor = 0, maxColor = histogram.size()-1, maxN = histogram[histogram.size()-1];
            for(size_t i = 0; i < histogram.size(); i++)
            {
                if( i > 32 && histogram[i] >= maxN)
                {
                    maxColor = i;
                    maxN = histogram[i];
                }
                if( 0 == minColor && histogram[i] >= 100)   //first valuable dark color
                    minColor = i;
            }
//            maxColor -= 16;
            stretchImageHistogram(&Image, minColor, maxColor);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("stretchImageHistogram: %.4f sec. minColor=%d maxColor=%d\n", tm.getElapsedTime(), minColor, maxColor);
sprintf (file,"out/test-%s.flt-07_stretched-1.png", filename);
png.save(file, Image);
tm.reset();
#endif
        }

//-----------------------------------------------------  SELECT OBJECTS  ----------------------------------------------------
// BLUR AFTER STRETCH
        if(0 != Parameters.RadiusBlur2)
        {
            blurImage(&Image, Parameters.RadiusBlur2);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("blurImage: %.4f sec. R=%d\n", tm.getElapsedTime(), Parameters.RadiusBlur2);
sprintf (file,"out/test-%s.flt-08_blur-2.png", filename);
png.save(file, Image);
tm.reset();
#endif
        }
// CROP BORDER
        if(0 != Parameters.CropBorder)
        {
            Image.crop(Parameters.CropBorder, Parameters.CropBorder, Image.getWidth() - Parameters.CropBorder - 1, Image.getHeight() - Parameters.CropBorder -1);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("cropBorder: %.4f sec.\n", tm.getElapsedTime());
sprintf (file,"out/test-%s.flt-09_crop-borders.png", filename);
png.save(file, Image);
tm.reset();
#endif
        }

// UNSHARP MASK
        if(0!=Parameters.UnsharpMaskAmount2)
            unsharpMaskImage(&Image, Parameters.UnsharpMaskRadius2, 1., Parameters.UnsharpMaskAmount2, (int)Parameters.UnsharpMaskThreshold2);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("unsharpMaskImage: %.4f sec. R=%f bg=%d\n", tm.getElapsedTime(), Parameters.UnsharpMaskRadius2, getBackgroundValue(Image));
sprintf (file,"out/test-%s.flt-10_unsharp-mask.png", filename);
png.save(file, Image);
tm.reset();
#endif

//-----------------------------------------------------  IMPROVE PICTURE ----------------------------------------------------
/* // opt STRETCH 2 - no effect
        makeHistogram (Image, &histogram);
        size_t maxColor = histogram.size()-1, maxN = histogram[histogram.size()-1];
        size_t minColor = 0, minN = histogram[0];
        for(size_t i = 0; i < histogram.size(); i++)
        {
            if( i > 32 && histogram[i] >= maxN)
            {
                maxColor = i;
                maxN = histogram[i];
            }
            if(histogram[i] <= minN && i < maxColor)
            {
                minColor = i;
                minN = histogram[i];
            }
            else if(histogram[i] > 4*minN)
                minN = 0;   // stop find first minimum
        }
        stretchImageHistogram(&Image, (size_t(16) > minColor ? minColor : size_t(16)), maxColor);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("stretchImageHistogram: %.4f sec. minColor=%d (%d) maxColor=%d\n", tm.getElapsedTime(), (size_t(16) > minColor ? minColor : size_t(16)), minColor, maxColor);
sprintf (file,"out/test-%s.flt-30_stretched.png", filename);
png.save(file, Image);
tm.reset();
#endif


// BLUR 2 we can lost very small details here and connect neighbour objects
        if(0 != Parameters.RadiusBlur2)
            blurImage(&Image, Parameters.RadiusBlur2);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("blurImage: %.4f sec.\n", tm.getElapsedTime());
sprintf (file,"out/test-%s.flt-40_blur-2.png", filename);
png.save(file, Image);
tm.reset();
#endif



// UNSHARP MASK 2 we can lost very small details here
        if(0!=Parameters.UnsharpMaskAmount2)
            unsharpMaskImage(Image, Parameters.UnsharpMaskRadius, 1., Parameters.UnsharpMaskAmount2, (int)Parameters.UnsharpMaskThreshold2);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("unsharpMaskImage: %.4f sec.\n", tm.getElapsedTime());
sprintf (file,"out/test-%s.flt-48_unsharp-mask-2.png", filename);
png.save(file, Image);
tm.reset();
#endif
*/

//-----------------------------------------------------  BLACK WHITE  ----------------------------------------------------
//to BW
    {
        unsigned char bg = 32;//getBackgroundValue(Image);
        convertGrayscaleToBlackWhite(&Image, bg);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("convertGrayscaleToBlackWhite: %.4f sec. Background >= %d (%d)\n", tm.getElapsedTime(), (int)bg, getBackgroundValue(Image));
sprintf (file,"out/test-%s.flt-50_BW.png", filename);
png.save(file, Image);
tm.reset();
#endif
    }
//----------------------------------------------------- CLEAR PICTURE ----------------------------------------------------
        if(0 != Parameters.VignettingHoleDistance)
            clearCorners (&Image, Parameters.VignettingHoleDistance);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("clearCorners: %.4f sec.\n", tm.getElapsedTime());
sprintf (file,"out/test-%s.flt-60_cleared-cornes.png", filename);
png.save(file, Image);
tm.reset();
#endif
        if(0 != Parameters.SmallDirtSize)
            eraseSmallDirts (&Image, Parameters.SmallDirtSize);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("eraseSmallDirts: %.4f sec.\n", tm.getElapsedTime());
sprintf (file,"out/test-%s.flt-70_cleared-dirts.png", filename);
png.save(file, Image);
tm.reset();
#endif

        cropImageToPicture(&Image);
#ifdef TEST
totalTime += tm.getElapsedTime();
printf("cropImageToPicture: %.4f sec.\nTotalTime =  %.4f (with log %.4f) sec.\n", tm.getElapsedTime(), totalTime, ttotal.getElapsedTime());
sprintf (file,"out/test-%s.flt-99_croped.png", filename);
png.save(file, Image);
tm.reset();
#endif
    }

//==============================================================================

    Coord ImageFilter::computeLineWidthHistogram(std::vector<size_t>* histogram, size_t size)
    {
        size_t maxFrequentWidth = 0, maxFrequentWidthNumber = 0;
        if(-1==size)
            size = Image.getWidth()/10;

        histogram->resize(size);
        memset(&(*histogram)[0], 0, histogram->size());
        for (size_t y = 0; y < Image.getHeight(); y++)
            for(size_t x = 0; x < Image.getWidth() ; x++)
            if(!Image.getPixel(x, y).isBackground())
        {
            size_t w = 0;
            for(; x < Image.getWidth() && !Image.getPixel(x, y).isBackground(); x++)
                w++;
            if (w < histogram->size())
            {
                size_t n = ++(*histogram)[w];
                if (maxFrequentWidthNumber < n)
                {
                    maxFrequentWidthNumber = n;
                    maxFrequentWidth       = w;
                }
            }
        }
        return Coord(maxFrequentWidth);
    }

//==============================================================================

    static inline int round(float x) { return int(x > 0.f ? x + 0.5f : x - 0.5f);}
    
    static inline int max4(int x1, int x2, int x3, int x4)
    {
        int maxx = x1;
        if (maxx < x2)
            maxx = x2;
        if (maxx < x3)
            maxx = x3;
        if (maxx < x4)
            maxx = x4;
        return maxx;
    }

    static inline int min4(int x1, int x2, int x3, int x4)
    {
        int minx = x1;
        if (minx > x2)
            minx = x2;
        if (minx > x3)
            minx = x3;
        if (minx > x4)
            minx = x4;
        return minx;
    }

    void rotateImage90(const Image& img, unsigned int angle, Image* out) // 90, 180, 270
    {
#ifdef TEST
Timer tm;
#endif
        const int xc = img.getWidth()/2, yc = img.getHeight()/2;     // center of source image
        float sinAngle = sin(angle*(float)3.14159265359f/(float)180.f), cosAngle = cos(angle*(float)3.14159265359f/(float)180.f);
        {
            // compute new size
            int x1 = round(cosAngle * (0 - xc)              - sinAngle * (0 - yc));
            int x2 = round(cosAngle * (img.getWidth() - xc) - sinAngle * (0 - yc));
            int x3 = round(cosAngle * (img.getWidth() - xc) - sinAngle * (img.getHeight() - yc));
            int x4 = round(cosAngle * (0 - xc)              - sinAngle * (img.getHeight() - yc));

            int y1 = round(sinAngle * (0 - xc)              + cosAngle * (0 - yc));
            int y2 = round(sinAngle * (img.getWidth() - xc) + cosAngle * (0 - yc));
            int y3 = round(sinAngle * (img.getWidth() - xc) + cosAngle * (img.getHeight() - yc));
            int y4 = round(sinAngle * (0 - xc)              + cosAngle * (img.getHeight() - yc));

            out->setSize(size_t(max4(x1, x2, x3, x4) - min4(x1, x2, x3, x4)+1), size_t(max4(y1, y2, y3, y4) - min4(y1, y2, y3, y4)+1), img.getType());
            out->clear();
        }
        const size_t xc1 = out->getWidth()/2, yc1 = out->getHeight()/2; // center of output image

        // roteate pixels
        for (size_t y=0; y < img.getHeight(); y++)
         for(size_t x=0; x < img.getWidth (); x++)
        {
            int xsrc = (int)x - xc, ysrc = (int)y - yc;
            size_t x1, y1;
            x1 = (size_t) (xc1 + round(cosAngle * xsrc - sinAngle * ysrc));
            y1 = (size_t) (yc1 + round(sinAngle * xsrc + cosAngle * ysrc));
            out->setPixel(x1, y1, img.getPixel(x, y));
        }

        if(IT_BW == out->getType())//black white image
        {
            blurImage(out, 2);
            cropImageToPicture(out);
            unsharpMaskImage(out, 20.f, 0., 9.f, 0);    //50
            convertGrayscaleToBlackWhite(out, 210);
        }
#ifdef TEST
printf("rotateImage90: %.4f sec. a=%d degree.\n", tm.getElapsedTime(), angle);
tm.reset();
#endif
    }


    void rotateImage(const Image& img, float angle, Image* out)
    {
#ifdef TEST
Timer tm;
#endif
        const int xc = img.getWidth()/2, yc = img.getHeight()/2;     // center of source image
        float sinAngle = sin(angle*(float)3.14159265359f/(float)180.f), cosAngle = cos(angle*(float)3.14159265359f/(float)180.f);
        {
            // compute new size
            int x1 = round(cosAngle * (0 - xc)              - sinAngle * (0 - yc));
            int x2 = round(cosAngle * (img.getWidth() - xc) - sinAngle * (0 - yc));
            int x3 = round(cosAngle * (img.getWidth() - xc) - sinAngle * (img.getHeight() - yc));
            int x4 = round(cosAngle * (0 - xc)              - sinAngle * (img.getHeight() - yc));

            int y1 = round(sinAngle * (0 - xc)              + cosAngle * (0 - yc));
            int y2 = round(sinAngle * (img.getWidth() - xc) + cosAngle * (0 - yc));
            int y3 = round(sinAngle * (img.getWidth() - xc) + cosAngle * (img.getHeight() - yc));
            int y4 = round(sinAngle * (0 - xc)              + cosAngle * (img.getHeight() - yc));

            out->setSize(size_t(max4(x1, x2, x3, x4) - min4(x1, x2, x3, x4)+1), size_t(max4(y1, y2, y3, y4) - min4(y1, y2, y3, y4)+1), img.getType());
            out->clear();
        }
        const size_t xc1 = out->getWidth()/2, yc1 = out->getHeight()/2; // center of output image

        // roteate pixels
        for (size_t y=0; y < img.getHeight(); y++)
         for(size_t x=0; x < img.getWidth (); x++)
        {
            int xsrc = (int)x - xc, ysrc = (int)y - yc;
            size_t x1, y1;
            x1 = (size_t) (xc1 + round(cosAngle * xsrc - sinAngle * ysrc));
            y1 = (size_t) (yc1 + round(sinAngle * xsrc + cosAngle * ysrc));
            out->setPixel(x1, y1, img.getPixel(x, y));
        }

        if(IT_BW == out->getType())//black white image
        {
            blurImage(out, 2);
            cropImageToPicture(out);
            unsharpMaskImage(out, 20.f, 0., 9.f, 0);    //50
            convertGrayscaleToBlackWhite(out, 210);
        }
#ifdef TEST
printf("rotateImage: %.4f sec. a=%f degree.\n", tm.getElapsedTime(), angle);
tm.reset();
#endif
    }

    void eraseSmallDirts (Image* img, size_t radius)
    {
        for (size_t y = 0; y < img->getHeight(); y++)
         for(size_t x = 0; x < img->getWidth() ; x++)
         {
            if(!img->getPixel(x, y).isBackground())        // check outer border
             for(int r=1; r<=(int)radius; r++)
            {
                bool big = false;
                for(int i = -r; i <= r && !big; i++)
                {
                    if(!img->getPixel(x+i, y-r).isBackground()) // top border
                        big = true;
                    if(!img->getPixel(x+i, y+r).isBackground()) // bottom border
                        big = true;
                }
                for(int i = -r; i <= r && !big; i++)
                {
                    if(!img->getPixel(x-r, y+i).isBackground()) // left border
                        big = true;
                    if(!img->getPixel(x+r, y+i).isBackground()) // right border
                        big = true;
                }

                if(!big)
                {
                    for(int i = -r; i <= r && x + i < img->getWidth(); i++)
                    {
                        for(int j = -r; j <= r && y + j < img->getHeight(); j++)
                            img->setPixel(x+i, y+j, BACKGROUND);
                    }
                    x += r;
                    r = 2*radius;   //stop current pixel processing
                }
            }
        }
    }

//==============================================================================
/*
    void eraseSmallDirts1 (Image* img, size_t r)
    {
//        img.setPixel(2,2, Pixel(0));    //test

        if( r > 2)  // WRONG IMPLEMENTATION for r >= 2 !!!
            r = 2;
        for (size_t y = 0; y < img->getHeight(); y++)
         for(size_t x = 0; x < img->getWidth() ; x++)
         {
            if(!img->getPixel(x, y).isBackground())
            {
                size_t len = 1, hmax = 1, rmax = 1;

                for(size_t i = 1; i <= r && x + i < img->getWidth() && ! img->getPixel(x+i, y).isBackground(); i++)
                {
                    len++;
                    size_t h = 0;
                    for(size_t j = 0; j <= r && y + j < img->getHeight() && ! img->getPixel(x+i, y+j).isBackground(); j++)
                        h++;
                    for(size_t j = 1; j <= r && y - j >= 0 && ! img->getPixel(x+i, y-j).isBackground(); j++)
                        h++;
                    if(h > hmax)
                        hmax = h;
                }
                if(len < r)
                    for(size_t i = 1; i <= r && x - i >= 0 && ! img->getPixel(x-i, y).isBackground(); i++)   // NEVER !! already processed
                    {
                        len++;
                        size_t h = 0;
                        for(size_t j = 0; j <= r && y + j < img->getHeight() && ! img->getPixel(x-i, y+j).isBackground(); j++)
                            h++;
                        for(size_t j = 1; j <= r && y - j >= 0 && ! img->getPixel(x-i, y-j).isBackground(); j++)
                            h++;
                        if(h > hmax)
                            hmax = h;
                    }
                if(len < r && hmax < r) // find \ line
                {
                    len = 0;
                    bool stop = false;
                    for(size_t i = 1; !stop && i <= r && x + i < img->getWidth() && y + i < img->getHeight(); i++)
                    {
                        stop = true;
                        if(!img->getPixel(x+i, y+i).isBackground())
                        {
                            stop = false;
                            len++;
                        }
                        if(y>=i && !img->getPixel(x-i, y-i).isBackground())
                        {
                            stop = false;
                            len++;
                        }
                    }
                }
                if(len < r && hmax < r) // find / line
                {
                    len = 0;
                    bool stop = false;
                    for(size_t i = 1; !stop && i <= r && x + i < img->getWidth() && y + i < img->getHeight(); i++)
                    {
                        stop = true;
                        if(x>=i && !img->getPixel(x-i, y+i).isBackground())
                        {
                            stop = false;
                            len++;
                        }
                        if(y>=i && !img->getPixel(x+i, y-i).isBackground())
                        {
                            stop = false;
                            len++;
                        }
                    }
                }
                if(len < r && hmax < r) // find < line
                {
                    len = 0;
                    bool stop = false;
                    for(size_t i = 1; !stop && i <= r && x + i < img->getWidth() && y + i < img->getHeight(); i++)
                    {
                        stop = true;
                        if(!img->getPixel(x+i, y+i).isBackground())
                        {
                            stop = false;
                            len++;
                        }
                        if(y>=i && !img->getPixel(x+i, y-i).isBackground())
                        {
                            stop = false;
                            len++;
                        }
                    }
                }
                if(len < r && hmax < r) // find > line
                {
                    len = 0;
                    bool stop = false;
                    for(size_t i = 0; !stop && i <= r && x + i < img->getWidth() && y + i < img->getHeight(); i++)
                    {
                        stop = true;
                        if(x>=i && !img->getPixel(x-i, y+i).isBackground())
                        {
                            stop = false;
                            len++;
                        }
                        if(x>=i && y>=i && !img->getPixel(x-i, y-i).isBackground())
                        {
                            stop = false;
                            len++;
                        }
                    }
                }
                / *
                if(hmax <= r && len <= r)   // compute max distance by outer contour !!! WRONG IMPLEMENTATION for r > 2 !!!
                {
                    std::vector<bool> processed((r+1)*(r+1));
                    memset(&processed[0], false, processed.size());
                    int xi = x, yj = y;
                    while (rmax <= r && abs(xi - (int)x) <= (int)r &&  abs(yj - (int)y) <= (int)r &&  xi < (int)img.getWidth () && yj < (int)img.getHeight())
                    {
                       if(!processed[] && !img.getPixel(xi, yj+1).isBackground())
                        {
                            yj++;
                            if(xi >= 1 && !img.getPixel(xi-1, yj).isBackground())
                                xi--;
                        }
                        else if(yj >= 1 && !img.getPixel(xi, yj-1).isBackground())
                        {
                            yj--;
                            if(xi >= 1 && !img.getPixel(xi-1, yj).isBackground())
                                xi--;
                        }
                        else if(!img.getPixel(xi+1, yj).isBackground())
                        {
                            xi++;
                            if(yj >= 1 && !img.getPixel(xi, yj-1).isBackground())
                                yj--;
                        }
                        else if(xi >= 1 && !img.getPixel(xi-1, yj).isBackground())
                        {
                            xi--;
                            if(!img.getPixel(xi, yj+1).isBackground())
                                yj++;
                        }
                        else
                            break;
                        if (xi < 0)
                            xi = 0;
                        if (yj < 0)
                            yj = 0;

                        if(size_t(((int)x-xi)*((int)x-xi) + ((int)y-yj)*((int)y-yj)) > r*r)
                            rmax = 2*r;
                    }
                    rmax = size_t(((int)x-xi)*((int)x-xi) + ((int)y-yj)*((int)y-yj));
                }
                * /
                if(rmax <= r && hmax <= r && len <= r)
                {
                    for(size_t i = 0; i <= r && x < img->getWidth() && ! img->getPixel(x, y).isBackground(); i++, x++)
                    {
                        for(size_t j = 0; j <= r && y + j < img->getHeight() && ! img->getPixel(x, y+j).isBackground(); j++)
                            img->setPixel(x, y+j, BACKGROUND);
                    }
                }
                for(; x < img->getWidth() && ! img->getPixel(x, y).isBackground(); x++)   //skip big object
                {}
            }
        }
    }
*/

//==============================================================================
// UnsharpMask
//==============================================================================
/*
    typedef float real;
    static inline int   real2int    (real  x)   { return int  (x);}
    static inline real  int2real    (int   x)   { return real (x);}
    static inline float real2float  (real  x)   { return float(x);}
    static inline real  float2real  (float x)   { return real (x);}
    static inline int ROUND (real x) { return (int) (x + 0.5f);}
*/
/* // 64 bit
    typedef signed long long int real;
    static const int FPOINT_BITS = 24;          //20;
    static const int FPOINT_HALF = 0x7FFFFF;     //0x7FFFF;     // == 0.5
    static const float FPOINT_ONE  = 16777216.f;  //1048576.f;   // == 1.
*/
    typedef unsigned int real;
    static const int FPOINT_BITS = 20;          // mantissa (fractional part)
    static const int FPOINT_HALF = 0x7FFFF;     // == 0.5
    static const float FPOINT_ONE= 1048576.f;   // == 1.

    static inline int   real2int    (real  x)   { return int(x >> FPOINT_BITS);}
    static inline real  int2real    (int   x)   { return     x << FPOINT_BITS;}
    static inline float real2float  (real  x)   { return float(x) / FPOINT_ONE;}
    static inline real  float2real  (float x)   { return real(FPOINT_ONE * x);}
    static inline unsigned char DIVIDE (real x, real y) { return int(((x<<1)/y+1)>>1);}
    static inline unsigned char ROUND  (real x) { return real2int(x + FPOINT_HALF);}

//    static inline int   real2int    (real  x)   { return x / 200000;}
//    static inline real  int2real    (int   x)   { return x * 200000;}
//    static inline float real2float  (real  x)   { return (float)x / 200000.f;}
//    static inline real  float2real  (float x)   { return int(200000.f * x);}
//    static inline int ROUND (real x) { return real2int(x + 100000);}//FPOINT_HALF);} // x >= 0

    // Square:
    #define SQR(x) ((x) * (x))  //    static inline real SQR(real x) { return x*x;}

    static void blurLine (const real* ctable, const real* cmatrix, const int cmatrix_length,
                        const unsigned char* src, unsigned char* dest, const int len, const int bytes)
    {
        const real *cmatrix_p;
        const real *ctable_p;
        const unsigned char  *src_p;
        const unsigned char  *src_p1;
        const int     cmatrix_middle = cmatrix_length / 2;
        int           row;
        int           i, j;

        // This first block is the same as the optimized version. it is only used for very small pictures, so speed isn't a big concern.
        if (cmatrix_length > len)
        {
            for (row = 0; row < len; row++)
            {
                /* find the scale factor */
                real scale = 0;

                for (j = 0; j < len; j++)
                {
                    /* if the index is in bounds, add it to the scale counter */
                    if (j + cmatrix_middle - row >= 0 &&
                        j + cmatrix_middle - row < cmatrix_length)
                    scale += cmatrix[j];
                }

                src_p = src;

                for (i = 0; i < bytes; i++)
                {
                    real sum = 0;

                    src_p1 = src_p++;

                    for (j = 0; j < len; j++)
                    {
                        if (j + cmatrix_middle - row >= 0 &&
                            j + cmatrix_middle - row < cmatrix_length)
                        sum += *src_p1 * cmatrix[j];

                        src_p1 += bytes;
                    }

                    *dest++ = DIVIDE (sum , scale);
                }
            }
        }
        else
        {
            // for the edge condition, we only use available info and scale to one
            for (row = 0; row < cmatrix_middle; row++)
            {
                // find scale factor
                real scale = 0;

                for (j = cmatrix_middle - row; j < cmatrix_length; j++)
                    scale += cmatrix[j];

                src_p = src;

                for (i = 0; i < bytes; i++)
                {
                    real sum = 0;

                    src_p1 = src_p++;

                    for (j = cmatrix_middle - row; j < cmatrix_length; j++)
                    {
                        sum += *src_p1 * cmatrix[j];
                        src_p1 += bytes;
                    }

                    *dest++ = DIVIDE (sum , scale);
                }
            }

            // go through each pixel in each col
            for (; row < len - cmatrix_middle; row++)
            {
                src_p = src + (row - cmatrix_middle) * bytes;

                for (i = 0; i < bytes; i++)
                {
                    real sum = 0;

                    cmatrix_p = cmatrix;
                    src_p1 = src_p;
                    ctable_p = ctable;

                    for (j = 0; j < cmatrix_length; j++)
                    {
                        sum += cmatrix[j] * *src_p1;
                        src_p1 += bytes;
                        ctable_p += 256;
                    }

                    src_p++;
                    *dest++ = ROUND (sum);
                }
            }

            // for the edge condition, we only use available info and scale to one
            for (; row < len; row++)
            {
                // find scale factor
                real scale = 0;

                for (j = 0; j < len - row + cmatrix_middle; j++)
                scale += cmatrix[j];

                src_p = src + (row - cmatrix_middle) * bytes;

                for (i = 0; i < bytes; i++)
                {
                    real sum = 0;

                    src_p1 = src_p++;

                    for (j = 0; j < len - row + cmatrix_middle; j++)
                    {
                        sum += *src_p1 * cmatrix[j];
                        src_p1 += bytes;
                    }

                    *dest++ = DIVIDE (sum, scale);
                }
            }
        }
    }

    // generates a 1-D convolution matrix to be used for each pass of a two-pass gaussian blur.  Returns the length of the matrix.
    static int makeConvolveMatrix (float radius, real **cmatrix_p)
    {
      real  *cmatrix;
      float  std_dev;
      float  sum;
      int    matrix_length;
      int    i, j;

      /* we want to generate a matrix that goes out a certain radius
       * from the center, so we have to go out ceil(rad-0.5) pixels,
       * inlcuding the center pixel.  Of course, that's only in one direction,
       * so we have to go the same amount in the other direction, but not count
       * the center pixel again.  So we double the previous result and subtract
       * one.
       * The radius parameter that is passed to this function is used as
       * the standard deviation, and the radius of effect is the
       * standard deviation * 2.  It's a little confusing.
       */
      radius = fabs (radius) + 1.f;

      std_dev = radius;
      radius = std_dev * 2;

      // go out 'radius' in each direction
      matrix_length = (int)(2 * ceil(radius - 0.5f) + 1);
      if (matrix_length <= 0)
        matrix_length = 1;

      *cmatrix_p = new real[matrix_length];
      cmatrix = *cmatrix_p;

      /*  Now we fill the matrix by doing a numeric integration approximation
       * from -2*std_dev to 2*std_dev, sampling 50 points per pixel.
       * We do the bottom half, mirror it to the top half, then compute the
       * center point.  Otherwise asymmetric quantization errors will occur.
       *  The formula to integrate is e^-(x^2/2s^2).
       */

      // first we do the top (right) half of matrix
      for (i = matrix_length / 2 + 1; i < matrix_length; i++)
        {
          float base_x = i - (matrix_length / 2) - 0.5f;

          sum = 0.f;
          for (j = 1; j <= 50; j++)
            {
              float r = base_x + (real)0.02f * j;

              if (r <= radius)
                sum += exp(float (- SQR (r) / (2 * SQR (std_dev))));
            }

          cmatrix[i] = float2real(sum / 50);
        }

      // mirror the thing to the bottom half
      for (i = 0; i <= matrix_length / 2; i++)
        cmatrix[i] = cmatrix[matrix_length - 1 - i];

      // find center val -- calculate an odd number of quanta to make it symmetric,
      // even if the center point is weighted slightly higher than others.
      sum = 0.f;
      for (j = 0; j <= 50; j++)
        sum += exp(float (- SQR (- 0.5f + 0.02f * j) / (2 * SQR (std_dev))));

      cmatrix[matrix_length / 2] = float2real(sum / 51);

      // normalize the distribution by scaling the total sum to one
      sum = 0.f;
      for (i = 0; i < matrix_length; i++)
        sum += real2float(cmatrix[i]);

      for (i = 0; i < matrix_length; i++)
        cmatrix[i] = float2real(real2float(cmatrix[i]) / sum);

      return matrix_length;
    }

    // ----------------------- gen_lookup_table -----------------------
    // generates a lookup table for every possible product of 0-255 and
    //   each value in the convolution matrix.  The returned array is
    //   indexed first by matrix position, then by input multiplicand (?) value.
    static real* makeLookupTable (const real *cmatrix, int cmatrix_length)
    {
      real       *lookup_table   = new real [cmatrix_length * 256];
      real       *lookup_table_p = lookup_table;
      const real *cmatrix_p      = cmatrix;

      for (int i = 0; i < cmatrix_length; i++)
        {
          for (int j = 0; j < 256; j++)
            *(lookup_table_p++) = *cmatrix_p * j;

          cmatrix_p++;
        }

      return lookup_table;
    }

    // Perform an unsharp mask on the region, given a source region, dest.
    // region, width and height of the regions, and corner coordinates of
    // a subregion to act upon.  Everything outside the subregion is unaffected.

    static void unsharpRegion (const unsigned char* srcPR, unsigned char* destPR, int bytes,
                               float radius, float amount, int threshold, int x1, int x2, int y1, int y2)
    {
        int     width   = x2 - x1 + 1;
        int     height  = y2 - y1 + 1;
        real    *cmatrix = 0;
        int     cmatrix_length;
        real    *ctable  = 0;
        int     row, col;
 
        // generate convolution matrix and make sure it's smaller than each dimension
        cmatrix_length = makeConvolveMatrix (radius, &cmatrix);

        // generate lookup table
        ctable = makeLookupTable (cmatrix, cmatrix_length);

        //allocate buffers
        unsigned char  *src  = new unsigned char [width > height ? width : height];
        unsigned char  *dest = new unsigned char [width > height ? width : height];

        // blur the rows
        for (row = 0; row < height; row++)
        {
          memcpy(src, srcPR + x1 + (y1 + row) * width, width - x1);
          blurLine (ctable, cmatrix, cmatrix_length, src, dest, width, bytes);
          memcpy(destPR + x1 + (y1 + row) * width, dest , width - x1);
        }

        // blur the cols
        for (col = 0; col < width; col++)
        {
            for (row = 0; row < height; row++)
                src[row] = destPR[x1 + col + (y1 + row) * width];
            blurLine (ctable, cmatrix, cmatrix_length, src, dest, height, bytes);
            for (row = 0; row < height; row++)
                destPR[x1 + col + (y1 + row) * width] = dest[row];
        }

        //merge the source and destination (which currently contains the blurred version) images
        for (row = 0; row < height; row++)
        {
          const unsigned char *s = src;
          unsigned char       *d = dest;
          int          u, v;

          // get source row
          memcpy(src, srcPR + x1 + (y1 + row) * width, width - x1);
          // get dest row
          memcpy(dest, destPR + x1 + (y1 + row) * width, width - x1);

          // combine both
            for (u = 0; u < width; u++)
            {
                for (v = 0; v < bytes; v++)
                {
                    int value;
                    int diff = *s - *d;

                    // do tresholding
                    if (abs (2 * diff) < threshold)
                    diff = 0;

                    value = int(*s++ + amount * diff);
                    *d++ = value > 0 ? (value <= 255 ? value : 255) : 0;
                }
            }
            memcpy(destPR + x1 + (y1 + row) * width, dest , width - x1);
        }

      delete [] dest;
      delete [] src;
      delete [] ctable;
      delete [] cmatrix;
    }


    void unsharpMaskImage(Image* img, const float radius, const float sigma, const float amount,const int threshold)
    {
        int x1=0, y1=0, x2=img->getWidth()-1, y2=img->getHeight()-1;
        size_t size = img->getWidth()*img->getHeight();
        unsigned char* dest = new unsigned char[size];
        unsharpRegion ((const unsigned char*)img->getPixels(), dest, 1, radius, amount, threshold, x1, x2, y1, y2);
        memcpy(img->getPixels(), dest, size);
        delete [] dest;
    }


//==============================================================================
/*
<?php 

/ * 

New:  
- In version 2.1 (February 26 2007) Tom Bishop has done some important speed enhancements. 
- From version 2 (July 17 2006) the script uses the imageconvolution function in PHP  
version >= 5.1, which improves the performance considerably. 


Unsharp masking is a traditional darkroom technique that has proven very suitable for  
digital imaging. The principle of unsharp masking is to create a blurred copy of the image 
and compare it to the underlying original. The difference in colour values 
between the two images is greatest for the pixels near sharp edges. When this  
difference is subtracted from the original image, the edges will be 
accentuated.  

The Amount parameter simply says how much of the effect you want. 100 is 'normal'. 
Radius is the radius of the blurring circle of the mask. 'Threshold' is the least 
difference in colour values that is allowed between the original and the mask. In practice 
this means that low-contrast areas of the picture are left unrendered whereas edges 
are treated normally. This is good for pictures of e.g. skin or blue skies. 

Any suggenstions for improvement of the algorithm, expecially regarding the speed 
and the roundoff errors in the Gaussian blur process, are welcome. 

* / 

function UnsharpMask($img, $amount, $radius, $threshold)    {  

////////////////////////////////////////////////////////////////////////////////////////////////   
////   
////                  Unsharp Mask for PHP - version 2.1.1   
////   
////    Unsharp mask algorithm by Torstein H?nsi 2003-07.   
////             thoensi_at_netcom_dot_no.   
////               Please leave this notice.   
////   
///////////////////////////////////////////////////////////////////////////////////////////////   



    // $img is an image that is already created within php using  
    // imgcreatetruecolor. No url! $img must be a truecolor image.  

    // Attempt to calibrate the parameters to Photoshop:  
    if ($amount > 500)    $amount = 500;  
    $amount = $amount * 0.016;  
    if ($radius > 50)    $radius = 50;  
    $radius = $radius * 2;  
    if ($threshold > 255)    $threshold = 255;  
      
    $radius = abs(round($radius));     // Only integers make sense.  
    if ($radius == 0) {  
        return $img; imagedestroy($img); break;        }  
    $w = imagesx($img); $h = imagesy($img);  
    $imgCanvas = imagecreatetruecolor($w, $h);  
    $imgBlur = imagecreatetruecolor($w, $h);  
      

    // Gaussian blur matrix:  
    //                          
    //    1    2    1          
    //    2    4    2          
    //    1    2    1          
    //                          
    //////////////////////////////////////////////////  
          

    if (function_exists('imageconvolution')) { // PHP >= 5.1   
            $matrix = array(   
            array( 1, 2, 1 ),   
            array( 2, 4, 2 ),   
            array( 1, 2, 1 )   
        );   
        imagecopy ($imgBlur, $img, 0, 0, 0, 0, $w, $h);  
        imageconvolution($imgBlur, $matrix, 16, 0);   
    }   
    else {   

    // Move copies of the image around one pixel at the time and merge them with weight  
    // according to the matrix. The same matrix is simply repeated for higher radii.  
        for ($i = 0; $i < $radius; $i++)    {  
            imagecopy ($imgBlur, $img, 0, 0, 1, 0, $w - 1, $h); // left  
            imagecopymerge ($imgBlur, $img, 1, 0, 0, 0, $w, $h, 50); // right  
            imagecopymerge ($imgBlur, $img, 0, 0, 0, 0, $w, $h, 50); // center  
            imagecopy ($imgCanvas, $imgBlur, 0, 0, 0, 0, $w, $h);  

            imagecopymerge ($imgBlur, $imgCanvas, 0, 0, 0, 1, $w, $h - 1, 33.33333 ); // up  
            imagecopymerge ($imgBlur, $imgCanvas, 0, 1, 0, 0, $w, $h, 25); // down  
        }  
    }  

    if($threshold>0){  
        // Calculate the difference between the blurred pixels and the original  
        // and set the pixels  
        for ($x = 0; $x < $w-1; $x++)    { // each row 
            for ($y = 0; $y < $h; $y++)    { // each pixel  
                      
                $rgbOrig = ImageColorAt($img, $x, $y);  
                $rOrig = (($rgbOrig >> 16) & 0xFF);  
                $gOrig = (($rgbOrig >> 8) & 0xFF);  
                $bOrig = ($rgbOrig & 0xFF);  
                  
                $rgbBlur = ImageColorAt($imgBlur, $x, $y);  
                  
                $rBlur = (($rgbBlur >> 16) & 0xFF);  
                $gBlur = (($rgbBlur >> 8) & 0xFF);  
                $bBlur = ($rgbBlur & 0xFF);  
                  
                // When the masked pixels differ less from the original  
                // than the threshold specifies, they are set to their original value.  
                $rNew = (abs($rOrig - $rBlur) >= $threshold)   
                    ? max(0, min(255, ($amount * ($rOrig - $rBlur)) + $rOrig))   
                    : $rOrig;  
                $gNew = (abs($gOrig - $gBlur) >= $threshold)   
                    ? max(0, min(255, ($amount * ($gOrig - $gBlur)) + $gOrig))   
                    : $gOrig;  
                $bNew = (abs($bOrig - $bBlur) >= $threshold)   
                    ? max(0, min(255, ($amount * ($bOrig - $bBlur)) + $bOrig))   
                    : $bOrig;  
                  
                  
                              
                if (($rOrig != $rNew) || ($gOrig != $gNew) || ($bOrig != $bNew)) {  
                        $pixCol = ImageColorAllocate($img, $rNew, $gNew, $bNew);  
                        ImageSetPixel($img, $x, $y, $pixCol);  
                    }  
            }  
        }  
    }  
    else{  
        for ($x = 0; $x < $w; $x++)    { // each row  
            for ($y = 0; $y < $h; $y++)    { // each pixel  
                $rgbOrig = ImageColorAt($img, $x, $y);  
                $rOrig = (($rgbOrig >> 16) & 0xFF);  
                $gOrig = (($rgbOrig >> 8) & 0xFF);  
                $bOrig = ($rgbOrig & 0xFF);  
                  
                $rgbBlur = ImageColorAt($imgBlur, $x, $y);  
                  
                $rBlur = (($rgbBlur >> 16) & 0xFF);  
                $gBlur = (($rgbBlur >> 8) & 0xFF);  
                $bBlur = ($rgbBlur & 0xFF);  
                  
                $rNew = ($amount * ($rOrig - $rBlur)) + $rOrig;  
                    if($rNew>255){$rNew=255;}  
                    elseif($rNew<0){$rNew=0;}  
                $gNew = ($amount * ($gOrig - $gBlur)) + $gOrig;  
                    if($gNew>255){$gNew=255;}  
                    elseif($gNew<0){$gNew=0;}  
                $bNew = ($amount * ($bOrig - $bBlur)) + $bOrig;  
                    if($bNew>255){$bNew=255;}  
                    elseif($bNew<0){$bNew=0;}  
                $rgbNew = ($rNew << 16) + ($gNew <<8) + $bNew;  
                    ImageSetPixel($img, $x, $y, $rgbNew);  
            }  
        }  
    }  
    imagedestroy($imgCanvas);  
    imagedestroy($imgBlur);  
      
    return $img;  

} 
?> 

//==============================================================================
    MagickExport Image *UnsharpMaskImageChannel(const Image *image,
  const ChannelType channel,const double radius,const double sigma,
  const double amount,const double threshold,ExceptionInfo *exception)
{
#define SharpenImageTag  "Sharpen/Image"

  CacheView
    *image_view,
    *unsharp_view;

  Image
    *unsharp_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  MagickPixelPacket
    bias;

  MagickRealType
    quantum_threshold;

  ssize_t
    y;

  assert(image != (const Image *) NULL);
  assert(image->signature == MagickSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",image->filename);
  assert(exception != (ExceptionInfo *) NULL);
  unsharp_image=BlurImageChannel(image,channel,radius,sigma,exception);
  if (unsharp_image == (Image *) NULL)
    return((Image *) NULL);
  quantum_threshold=(MagickRealType) QuantumRange*threshold;
  
  //  Unsharp-mask image.
  
  status=MagickTrue;
  progress=0;
  GetMagickPixelPacket(image,&bias);
  image_view=AcquireCacheView(image);
  unsharp_view=AcquireCacheView(unsharp_image);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(dynamic,4) shared(progress,status)
#endif
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    MagickPixelPacket
      pixel;

    register const IndexPacket
      *restrict indexes;

    register const PixelPacket
      *restrict p;

    register IndexPacket
      *restrict unsharp_indexes;

    register PixelPacket
      *restrict q;

    register ssize_t
      x;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,image->columns,1,exception);
    q=GetCacheViewAuthenticPixels(unsharp_view,0,y,unsharp_image->columns,1,
      exception);
    if ((p == (const PixelPacket *) NULL) || (q == (PixelPacket *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    indexes=GetCacheViewVirtualIndexQueue(image_view);
    unsharp_indexes=GetCacheViewAuthenticIndexQueue(unsharp_view);
    pixel=bias;
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      if ((channel & RedChannel) != 0)
        {
          pixel.red=p->red-(MagickRealType) q->red;
          if (fabs(2.0*pixel.red) < quantum_threshold)
            pixel.red=(MagickRealType) GetRedPixelComponent(p);
          else
            pixel.red=(MagickRealType) p->red+(pixel.red*amount);
          SetRedPixelComponent(q,ClampRedPixelComponent(&pixel));
        }
      if ((channel & GreenChannel) != 0)
        {
          pixel.green=p->green-(MagickRealType) q->green;
          if (fabs(2.0*pixel.green) < quantum_threshold)
            pixel.green=(MagickRealType) GetGreenPixelComponent(p);
          else
            pixel.green=(MagickRealType) p->green+(pixel.green*amount);
          SetGreenPixelComponent(q,ClampGreenPixelComponent(&pixel));
        }
      if ((channel & BlueChannel) != 0)
        {
          pixel.blue=p->blue-(MagickRealType) q->blue;
          if (fabs(2.0*pixel.blue) < quantum_threshold)
            pixel.blue=(MagickRealType) GetBluePixelComponent(p);
          else
            pixel.blue=(MagickRealType) p->blue+(pixel.blue*amount);
          SetBluePixelComponent(q,ClampBluePixelComponent(&pixel));
        }
      if ((channel & OpacityChannel) != 0)
        {
          pixel.opacity=p->opacity-(MagickRealType) q->opacity;
          if (fabs(2.0*pixel.opacity) < quantum_threshold)
            pixel.opacity=(MagickRealType) GetOpacityPixelComponent(p);
          else
            pixel.opacity=p->opacity+(pixel.opacity*amount);
          SetOpacityPixelComponent(q,ClampOpacityPixelComponent(&pixel));
        }
      if (((channel & IndexChannel) != 0) &&
          (image->colorspace == CMYKColorspace))
        {
          pixel.index=unsharp_indexes[x]-(MagickRealType) indexes[x];
          if (fabs(2.0*pixel.index) < quantum_threshold)
            pixel.index=(MagickRealType) unsharp_indexes[x];
          else
            pixel.index=(MagickRealType) unsharp_indexes[x]+(pixel.index*
              amount);
          unsharp_indexes[x]=ClampToQuantum(pixel.index);
        }
      p++;
      q++;
    }
    if (SyncCacheViewAuthenticPixels(unsharp_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp critical (MagickCore_UnsharpMaskImageChannel)
#endif
        proceed=SetImageProgress(image,SharpenImageTag,progress++,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  unsharp_image->type=image->type;
  unsharp_view=DestroyCacheView(unsharp_view);
  image_view=DestroyCacheView(image_view);
  if (status == MagickFalse)
    unsharp_image=DestroyImage(unsharp_image);
  return(unsharp_image);
}
*/

}
