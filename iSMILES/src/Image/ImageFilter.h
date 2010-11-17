#pragma once
#include <vector>
#include <algorithm>
#include "Image.h"

namespace gga
{
    static inline size_t makeHistogram  (const Image& img, std::vector<size_t>* histogram)
    {
        size_t maxh = 0;
        histogram->resize(256);
        memset(&(*histogram)[0], 0, 256);
        for (size_t y = 0; y < img.getHeight(); y++)
         for(size_t x = 0; x < img.getWidth() ; x++)
        {
            size_t v = ++(*histogram)[ img.getPixel(x, y).Value];
            if (maxh < v)
                maxh = v;
        }
        return maxh;
    }

    static inline void stretchImageHistogram(Image* img, size_t minColor, size_t maxColor)
    {
        size_t normalization = (255<<16)/(maxColor-minColor);
        for (size_t y = 0; y < img->getHeight(); y++)
         for(size_t x = 0; x < img->getWidth() ; x++)
        {
            size_t v = img->getPixel(x, y).Value;
            if(v < minColor)
                v = 0;
            else if(v > maxColor)
                v = 255;
            else
                v = (normalization*(v - minColor) + 0x7FFF)>>16;
            img->setPixel(x, y, Pixel(v));
        }
    }

    static inline void stretchImageHistogram(Image* img, size_t nmin)
    {
        std::vector<size_t> histogram;
        makeHistogram (*img, &histogram);
        size_t minColor, maxColor;
        for(minColor = 0; minColor < histogram.size() && histogram[minColor] < nmin; minColor++)
        {}
        for(maxColor= histogram.size()-1; maxColor > minColor && histogram[maxColor] < nmin; maxColor--)
        {}

        stretchImageHistogram(img, minColor, maxColor);
    }

    static inline void blurImage(Image* img, size_t r)
    {
        for (size_t y = 0; y < img->getHeight(); y++)
         for(size_t x = 0; x < img->getWidth() ; x++)
        {
            size_t px = 0;//img->getPixel(x, y).Value * (r+1)*(r+1);
            size_t weight = 0; //(r+1)*(r+1)
            size_t nx = r, ny = r;
            if( x+nx > img->getWidth())
                nx = img->getWidth() - x;
            if( y+ny > img->getHeight())
                ny = img->getHeight() - y;
            for (size_t iy = 0; iy < ny; iy++)
             for(size_t ix = 0; ix < nx; ix++) // average area
             {
                int dw = std::max(0, int((r+1)*(r+1) - ix*ix + iy*iy));
                if(0!=dw)
                    px += img->getPixel(x+ix, y+iy).Value * dw;
                weight += dw;
             }
            px /= weight;   // px /= nx * ny;
            img->setPixel(x, y, Pixel(px));
        }
    }

/* unsharpMaskImage()
%
%  A description of each parameter follows:
%
%    o image: the image.
%
%    o channel: the channel type.
%
%    o radius: the radius of the Gaussian, in pixels, not counting the center
%      pixel.
%
%    o sigma: the standard deviation of the Gaussian, in pixels.
%
%    o amount: the percentage of the difference between the original and the
%      blur image that is added back into the original.
%
%    o threshold: the threshold in pixels needed to apply the diffence amount.
%
%    o exception: return any errors or warnings in this structure.
%
*/
    void unsharpMaskImage(Image* img, const double radius, const double sigma, const double amount,const int threshold);

    static inline size_t getBackgroundValue(const Image& img)
    {
        std::vector<size_t> histogram;
        size_t maxh = makeHistogram (img, &histogram);
        for(size_t v = 2; v < histogram.size()-2; v++)
        {
            if(histogram[v-2] + histogram[v-1] + histogram[v] >= maxh/3)    // area of light background
            {
                for(v--; v > 0; v--)
                {
                    if(histogram[v] <= histogram[v+1]+12 || histogram[v] <= histogram[v+2]+12)
                        break;
//                    if(histogram[v] + histogram[v+1] + histogram[v+2] < maxh/64)    // exact begin of light background
//                        break;
                }
                return v;
            }
        }
        return 256/3;   //not found - return some middle value.
    }

    static inline void convertGrayscaleToBlackWhite (Image& img, const Pixel level)
    {
        for (size_t y = 0; y < img.getHeight(); y++)
         for(size_t x = 0; x < img.getWidth() ; x++)
        {
            Pixel px = img.getPixel(x, y);
            px.Value = (px.Value >= level.Value) ? BACKGROUND : INK;
            img.setPixel(x, y, px);
        }
    }

    static inline size_t clearSolidLine (Image& img, size_t xo, size_t xend, size_t y, size_t r)
    {
        size_t n = 0;
        if(xo <= xend)
        {
            for(size_t x = xo; x <= xend; x++)
            {
                bool clean;
                do
                {
                    clean = false;
                    for(size_t i = 0; i <= r && !clean && x+i <= xend; i++)
                        if(!img.getPixel(x+i, y).isBackground())
                            clean = true;
                    if(clean)
                    {
                        for(size_t i = 0; i <= r && x+i <= xend; i++)
                        {
                            n++;
                            img.setPixel(x+i, y, BACKGROUND);
                        }
                        x += r - 1;
                    }
                    else
                        return n;
                } while(clean);
            }
        }
        else    // reverse direction
        {
            for(size_t x = xo; x >= xend; x--)
            {
                bool clean;
                do
                {
                    clean = false;
                    for(size_t i = r+1; i > 0 && !clean && x-(i-1) >= xend; i--)
                        if(!img.getPixel(x-i-1, y).isBackground())
                            clean = true;
                    if(clean)
                    {
                        for(size_t i = r+1; i > 0 && x-(i-1) >= xend; i--)
                        {
                            n++;
                            img.setPixel(x-(i-1), y, BACKGROUND);
                        }
                        x -= r;
                    }
                    else
                        return n;
                } while(clean);
            }
        }
        return n;
    }

    static inline void clearCorners (Image& img, size_t r)
    {
        for (size_t y = 0; y < img.getHeight(); y++)    // left top corner
            if(0 == clearSolidLine (img, 0, img.getWidth()/4, y, r))
                break;
        for (size_t y = img.getHeight()-1; y > 0; y--)    // left bottom corner
            if(0 == clearSolidLine (img, 0, img.getWidth()/4, y, r))
                break;
        for (size_t y = 0; y < img.getHeight(); y++)    // right top corner
            if(0 == clearSolidLine (img, img.getWidth()/4, 0, y, r))
                break;
        for (size_t y = img.getHeight()-1; y > 0; y--)    // right bottom  corner
            if(0 == clearSolidLine (img, img.getWidth()/4, 0, y, r))
                break;
    }


    static inline void eraseSmallDirts (Image& img, size_t r)
    {
        for (size_t y = 0; y < img.getHeight(); y++)
         for(size_t x = 0; x < img.getWidth() ; x++)
         {
            if(!img.getPixel(x, y).isBackground())
            {
                size_t len = 0, hmax = 0, rmax=0;

                for(size_t i = 0; i <= r && x + i < img.getWidth() && ! img.getPixel(x+i, y).isBackground(); i++)
                {
                    len++;
                    size_t h = 0;
                    for(size_t j = 0; j <= r && y + j < img.getHeight() && ! img.getPixel(x+i, y+j).isBackground(); j++)
                        h++;
                    for(size_t j = 1; j <= r && y - j >= 0 && ! img.getPixel(x+i, y-j).isBackground(); j++)
                        h++;
                    if(h > hmax)
                        hmax = h;
                }
                for(size_t i = 1; i <= r && x - i >= 0 && ! img.getPixel(x-i, y).isBackground(); i++)
                {
                    len++;
                    size_t h = 0;
                    for(size_t j = 0; j <= r && y + j < img.getHeight() && ! img.getPixel(x-i, y+j).isBackground(); j++)
                        h++;
                    for(size_t j = 1; j <= r && y - j >= 0 && ! img.getPixel(x-i, y-j).isBackground(); j++)
                        h++;
                    if(h > hmax)
                        hmax = h;
                }
                // *
                if(hmax <= r && len <= r)   // compute max distance by outer contour
                {
                    int xi = x, yj = y;
                    while (rmax <= r && abs(xi - (int)x) <= (int)r &&  abs(yj - (int)y) <= (int)r &&  xi < (int)img.getWidth () && yj < (int)img.getHeight())
                    {
                       if(!img.getPixel(xi, yj+1).isBackground())
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
                        if (xi < 0)
                            xi = 0;
                        if (yj < 0)
                            yj = 0;

                        if(size_t(((int)x-xi)*((int)x-xi) + ((int)y-yj)*((int)y-yj)) > r*r)
                            rmax = 2*r;
                    }
                }
                // * /
                if(rmax <= r && hmax <= r && len <= r)
                {
                    for(size_t i = 0; i <= r && x < img.getWidth() && ! img.getPixel(x, y).isBackground(); i++, x++)
                    {
                        for(size_t j = 0; j <= r && y + j < img.getHeight() && ! img.getPixel(x, y+j).isBackground(); j++)
                            img.setPixel(x, y+j, BACKGROUND);
                    }
                }
                for(; x < img.getWidth() && ! img.getPixel(x, y).isBackground(); x++)   //skip big object
                {}
            }
        }
    }

    static inline void cropImageToPicture(Image& img)
    {
        size_t xend=0, yend=0;
        size_t xo=img.getWidth()-1, yo=img.getHeight()-1;

        for (size_t y = 0; y < img.getHeight(); y++)
        {
            bool includeLine = false;
            for(size_t x = 0; x < img.getWidth(); x++)
            {
                Pixel px = img.getPixel(x, y);
                if(!px.isBackground())
                {
                    includeLine = true;
                    if(x < xo)
                        xo = x;
                    if(x > xend)
                        xend = x;
                }
            }
            if(includeLine)
            {
                if(y < yo)
                    yo = y;
                if(y > yend)
                    yend = y;
            }
        }

        if (xo > xend)
        {
            size_t tmp = xo;
            xo = xend;
            xend = tmp;
        }
        if (yo > yend)
        {
            size_t tmp = yo;
            yo = yend;
            yend = tmp;
        }

        if (xo >= 4)
            xo -= 4;
        if (yo >= 4)
            yo -= 4;
        if (xend <= img.getWidth()-1 - 4)
            xend += 4;
        if (yend <= img.getHeight()-1 - 4)
            yend += 4;

        img.crop(xo, yo, xend, yend);
    }

    static inline void resampleImageBiCubic(Image& img, size_t cx, size_t cy)
    {

        //img.setSize(cx, cy, img.getType());
    }

    struct  ImageFilterParameters
    {
        double UnsharpMaskRadius;
        double UnsharpMaskAmount;
        double UnsharpMaskThreshold;
        double UnsharpMaskThreshold2;   //after stretch histogram
        size_t  CropBorder;
        size_t  RadiusBlur;
        size_t  VignettingHoleDistance;
        size_t  SmallDirtSize;
    public:
        inline ImageFilterParameters() : UnsharpMaskRadius(64), UnsharpMaskAmount(7), UnsharpMaskThreshold(3), UnsharpMaskThreshold2(130)
                                       , CropBorder(8), RadiusBlur(4), VignettingHoleDistance(31), SmallDirtSize(4) {}
    };

    class ImageFilter
    {
        gga::Image& Image;
        ImageFilterParameters  Parameters;
    public:

        inline ImageFilter(gga::Image& img) : Image(img)
        {
            // compute optimal default parameters based on image resiolution
            Parameters.UnsharpMaskRadius = std::min(120, int(std::min(Image.getWidth(), Image.getHeight())/4));
            Parameters.UnsharpMaskAmount = 7.;
            Parameters.UnsharpMaskThreshold = 72;
            Parameters.UnsharpMaskThreshold2= 130;
            Parameters.CropBorder   = 8;
            Parameters.RadiusBlur   = 5;
            Parameters.SmallDirtSize= 6;//2;   //4
            Parameters.VignettingHoleDistance = std::min(32, (int)Image.getWidth()/8);

        }

        void  prepareImageForVectorization();
        Coord computeLineWidthHistogram   (std::vector<size_t>* histogram, size_t size = -1);
    };

}
