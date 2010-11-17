#pragma once
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include "Pixel.h"
#include "Point.h"
#include "Region.h"
#include "LineDefinition.h"

namespace gga
{
    enum ImageType
    {
        IT_BW        = 1,
        IT_GRAYSCALE = 8,
    };

    class Image
    {
        size_t      Width;
        size_t      Height;
        ImageType   Type;
        std::vector<Pixel> Data;
    public:
         Image(){}
        ~Image(){}
        inline ImageType getType()const  { return Type  ;}
        inline size_t  getWidth ()const  { return Width ;}
        inline size_t  getHeight()const  { return Height;}
        inline const Pixel* getPixels()const { return &Data[0];}    //for write image on disk
        inline Pixel*       getPixels()  { return &Data[0];}        //for filter image (unsharp mask)
        inline void setSize (size_t width, size_t height, ImageType type)
        {
            Width  = width;
            Height = height;
            Type   = type;
            Data.resize(width * height);
        }
        inline void  setPixelFast(size_t x, size_t  y, const Pixel val)  { Data[x + y * Width] = val;}
        inline void  setPixel    (size_t x, size_t  y, const Pixel val)  { if(x < Width && y < Height) Data[x + y * Width] = val;}
        inline Pixel getPixel(size_t x, size_t  y) const     { return (x < Width && y < Height) ? Data[x + y * Width] : Pixel(BACKGROUND);}
        inline Pixel getPixel(const Point& p)     const      { return getPixel(p.X, p.Y);}
        inline bool isInside (const Point& p)     const      { return p.X < Width && p.Y < Height;}
        inline bool isFilled (const Point& p)     const      { return isInside(p) && !getPixel(p).isBackground(); }
        inline void crop(size_t xo, size_t yo, size_t xend, size_t yend)
        {
            const size_t cx = (xend - xo), cy = (yend - yo);
            for(size_t y=0; y <= cy; y++)
                memcpy(&Data[ 0 + y * cx], &Data[xo + (yo + y) * Width], cx);
            Width = cx;
            Height= cy;
            Data.resize(Width * Height);
        }

        // DRAWING Graphical primitives
        inline void clear()  { fill(Pixel(BACKGROUND));}
        inline void fill(Pixel px = Pixel(BACKGROUND))
        {
            memset(&Data[0], px.Value, Width*Height);
        }

        inline void drawImage(size_t xo, size_t yo, const Image& img)
        {
            for (size_t y=yo; y <= yo + img.getHeight(); y++)
             for(size_t x=xo; x <= xo + img.getWidth (); x++)
                 setPixel(x, y, img.getPixel(x-xo, y-yo));
        }

        inline void drawPoints(Points points, int xo = 0, int yo = 0, Pixel color = Pixel(INK))
        {
            for (size_t i = 0; i < points.size(); i++)
                setPixel(Coord(xo + points[i].X), Coord(yo + points[i].Y), color);
        }


        inline void drawPolygon(Points points, const LineDefinition& line = LineDefinition(INK,1))
        {
            for (size_t i = 1; i < points.size(); i++)
                drawLine(points[i-1].X, points[i-1].Y, points[i].X, points[i].Y, line);
        }

        void drawLine(size_t xo, size_t yo, size_t xend, size_t yend, const LineDefinition& line = LineDefinition(INK,1));

        inline void drawCircle(size_t xo, size_t yo, size_t radius, const LineDefinition& line = LineDefinition(INK,1))
        {
        //Bresenham's circule draw algorithm
            int  x = 0,  y = radius,  d = 3 - (radius<<1);
            while (x < y)
            {
                draw8CirculePixels (xo, yo, x, y, line);
                if (d < 0)
                    d = d + 4*x + 6;
                else
                {
                    d = d + 4*(x-y) + 10;
                    --y;
                }
                ++x;
            }
            if (x == y)
                draw8CirculePixels (xo, yo, x, y, line);
        } 

   private:
        inline void draw8CirculePixels (size_t xc, size_t yc, size_t x, size_t y, const LineDefinition& line = LineDefinition(INK,1))
        {
            setPixel(xc+x, yc+y, line.Color);
            setPixel(xc+y, yc+x, line.Color);
            setPixel(xc+y, yc-x, line.Color);
            setPixel(xc+x, yc-y, line.Color);
            setPixel(xc-x, yc-y, line.Color);
            setPixel(xc-y, yc-x, line.Color);
            setPixel(xc-y, yc+x, line.Color);
            setPixel(xc-x, yc+y, line.Color);
        }
    
        void setEdgeCircle(size_t xo, size_t yo, size_t xe, size_t ye, size_t dx, size_t dy, size_t swap, size_t radius, int *sx, int *sy, Points &points);
    };
}
