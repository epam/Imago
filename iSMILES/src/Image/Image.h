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

   private:
        inline void setEdges (size_t xc, size_t yc, size_t x, size_t y, size_t mask, const Pixel pixel)
        {
            if(mask&1)
                setPixel(xc+x, yc+y, pixel);
            if(mask&2)
                setPixel(xc+y, yc+x, pixel);
            if(mask&4)
                setPixel(xc+y, yc-x, pixel);
            if(mask&8)
                setPixel(xc+x, yc-y, pixel);
            if(mask&16)
                setPixel(xc-x, yc-y, pixel);
            if(mask&32)
                setPixel(xc-y, yc-x, pixel);
            if(mask&64)
                setPixel(xc-y, yc+x, pixel);
            if(mask&128)
                setPixel(xc-x, yc+y, pixel);
        }
        inline void setEdges (size_t xc, size_t yc, size_t x, size_t y, size_t mask, Points &points)
        {
            if(mask&1)
                points.push_back(Point(xc+x, yc+y));
            if(mask&2)
                points.push_back(Point(xc+y, yc+x));
            if(mask&4)
                points.push_back(Point(xc+y, yc-x));
            if(mask&8)
                points.push_back(Point(xc+x, yc-y));
            if(mask&16)
                points.push_back(Point(xc-x, yc-y));
            if(mask&32)
                points.push_back(Point(xc-y, yc-x));
            if(mask&64)
                points.push_back(Point(xc-y, yc+x));
            if(mask&128)
                points.push_back(Point(xc-x, yc+y));
        }

        inline void setEdgeCircle(size_t xo, size_t yo, size_t xe, size_t ye, size_t dx, size_t dy, size_t swap, size_t radius, int *sx, int *sy, const Pixel pixel)
        {
        //Bresenham's circule draw algorithm
            int  x = 0,  y = radius,  d = 3 - (radius<<1);
            int mask = 255;
            int ddx = xe - xo;
            *sx = 0; 
            *sy = 0;

            if (ddx < 0)
                ddx=-1;
            else 
                ddx=1;

            while (x < y)
            {
                int rrr  = x * dx;
                int rrr2 = y * dy;
                if(swap)
                {
                    if(rrr>=rrr2)
                    {
                        mask = 255-1-2-128-64;
                        if(!rrr)
                        {
                            *sx = y; 
                            *sy = ddx*x; 
                        }
                    }
                    else
                    {
                      mask = 255-128-1-2-4;
                      if(ddx<0)
                          mask = 255-2-4-8-16;
                      *sx = ddx*y; 
                      *sy = x; 
                    }
                }
                else
                {
                    if(rrr>=rrr2)
                    {
                        mask = 255-1-2-4-8;
                        if(!rrr)
                            {
                                *sx = ddx*x; 
                                *sy = y; 
                            }
                    }
                    else
                    {
                      mask = 255-1-2-4-128;
                      if(ddx<0)
                          mask = 255-2-4-8-16;
                      *sx = ddx*x; 
                      *sy = y; 
                    }
                }

                if (ddx < 0)
                    mask=~ mask;

                setEdges (xo, yo, x, y, mask, pixel);
                setEdges (xe, ye, x, y, ~mask, pixel);
                
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
            {
                setEdges (xo, yo, x, y, mask, pixel);
                setEdges (xe, ye, x, y, ~mask, pixel);
            } 
        } 

        inline void setEdgeCircle(size_t xo, size_t yo, size_t xe, size_t ye, size_t dx, size_t dy, size_t swap, size_t radius, int *sx, int *sy, Points &points)
        {
        //Bresenham's circule draw algorithm
            int  x = 0,  y = radius,  d = 3 - (radius<<1);
            int mask = 255;
            int ddx = xe - xo;
            *sx = 0; 
            *sy = 0;

            if (ddx < 0)
                ddx=-1;
            else 
                ddx=1;

            while (x < y)
            {
                int rrr  = x * dx;
                int rrr2 = y * dy;

                if(swap)
                {
                    if(rrr>=rrr2)
                    {
                        mask = 255-1-2-128-64;
                        if(!rrr)
                        {
                            *sx = y; 
                            *sy = ddx*x; 
                        }
                    }
                    else
                    {
                      mask = 255-128-1-2-4;
                      if(ddx<0)
                          mask = 255-2-4-8-16;
                      *sx = ddx*y; 
                      *sy = x; 
                    }
                }
                else
                {
                    if(rrr>=rrr2)
                    {
                        mask = 255-1-2-4-8;
                        if(!rrr)
                            {
                                *sx = ddx*x; 
                                *sy = y; 
                            }
                    }
                    else
                    {
                      mask = 255-1-2-4-128;
                      if(ddx<0)
                          mask = 255-2-4-8-16;
                      *sx = ddx*x; 
                      *sy = y; 
                    }
                }

                if (ddx < 0)
                    mask=~ mask;

                setEdges (xo, yo, x, y, mask, points);
                setEdges (xe, ye, x, y, ~mask, points);
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
            {
                setEdges (xo, yo, x, y, mask, points);
                setEdges (xe, ye, x, y, ~mask, points);
            } 
        } 

    public:
        inline void drawSardelka(size_t xo, size_t yo, size_t xend, size_t yend, const LineDefinition& line = LineDefinition(INK,1))
        {
        //Bresenham's line draw algorithm
            int  dx, dy, s, sx, sy, kl, swap, incr1, incr2, svx, svy;

               sy = 1;
               if ((dy = yend-yo) < 0)
               {
                   int xt = xo;
                   int yt = yo;
                   xo = xend;
                   yo = yend;
                   xend = xt;
                   yend = yt;
                   dy = -dy;
               }
               else if (dy == 0) 
                   --sy;
            // calculation dx and steps
               sx = 0;
               if ((dx = xend-xo) < 0)
               {
                    dx = -dx;
                    --sx;
               }
               else if (dx>0)
                   ++sx;

            // calculate the slope
               swap = 0;
               if ((kl = dx) < (s = dy))
               {
                  dx = s;
                  dy = kl;
                  kl = s;
                  ++swap;
               }

               s = (incr1 = dy<<1) - dx;
                                    // incr1 - constant of scalar recalculation
                                    // if current s < 0  and
                                    // s - initial difference
               incr2 = dx<<1;       // second constant of scalar recalculation
                                    // use when s >= 0
               setEdgeCircle(xo,yo,xend,yend, dx, dy, swap, line.Width/2, &svx, &svy, line.Color);
               setPixel (xo+svx,yo-svy,line.Color); // current point of vector
               setPixel (xo-svx,yo+svy,line.Color); // current point of vector
               while (--kl >= 0)
               {
                  if (s >= 0)
                  {
                     if (swap)
                         xo+= sx;
                     else
                         yo+= sy;
                     s-= incr2;
                  }
                  if (swap)
                      yo += sy;
                  else
                      xo+= sx;
                  s += incr1;
                  setPixel (xo+svx,yo-svy,line.Color); // current point of vector
                  setPixel (xo-svx,yo+svy,line.Color); // current point of vector
               }
        }  

        inline void drawLine(size_t xo, size_t yo, size_t xend, size_t yend, const LineDefinition& line = LineDefinition(INK,1))
        {
        //Bresenham's line draw algorithm
        //    if(line.Width < 2)
        //    { // fast draw
        //        drawHairline( xo, yo, xend, yend, line);
        //        return;
        //    }
            int  dx, dy, s, sx, sy, kl, swap, incr1, incr2, svx, svy;
            Points points;

               sy = 1;
               if ((dy = yend-yo) < 0)
               {
                   int xt = xo;
                   int yt = yo;
                   xo = xend;
                   yo = yend;
                   xend = xt;
                   yend = yt;
                   dy = -dy;
               }
               else if (dy == 0) 
                   --sy;
            // calculation dx and steps
               sx = 0;
               if ((dx = xend-xo) < 0)
               {
                    dx = -dx;
                    --sx;
               }
               else if (dx>0)
                   ++sx;

            // calculate the slope
               swap = 0;
               if ((kl = dx) < (s = dy))
               {
                  dx = s;
                  dy = kl;
                  kl = s;
                  ++swap;
               }

               s = (incr1 = dy<<1) - dx;
                                    // incr1 - constant of scalar recalculation
                                    // if current s < 0  and
                                    // s - initial difference
               incr2 = dx<<1;       // second constant of scalar recalculation
                                    // use when s >= 0
               setEdgeCircle(xo,yo,xend,yend, dx, dy, swap, line.Width/2, &svx, &svy, points);
               points.push_back(Point(xo+svx, yo-svy));
               points.push_back(Point(xo-svx, yo+svy));
    
               while (--kl >= 0)
               {
                  if (s >= 0)
                  {
                     if (swap)
                         xo+= sx;
                     else
                         yo+= sy;
                     s-= incr2;
                  }
                  if (swap)
                      yo += sy;
                  else
                      xo+= sx;
                  s += incr1;

                  points.push_back(Point(xo+svx,yo-svy)); // current point of vector
                  points.push_back(Point(xo-svx,yo+svy)); // current point of vector
               }

               std::sort(points.begin(), points.end());
               Points::const_iterator first = points.begin();
               for (Points::const_iterator it = points.begin(); it != points.end(); it++)
               {
                   if(it->X + it->Y * Width < Height * Width)
                   {
                       if((it+1) == points.end())
                       {
                           memset(&Data[first->X + first->Y * Width], line.Color.Value, (it->X - first->X)+1);
                           break;
                       }

                       if(first->Y != (it+1)->Y)
                       {
                           memset(&Data[first->X + first->Y * Width], line.Color.Value, (it->X - first->X)+1);
                           first = it+1;
                       }
                   }
               }
        }  

        inline void drawHairline(size_t xo, size_t yo, size_t xend, size_t yend, const LineDefinition& line = LineDefinition(INK,1))
        {
        //Bresenham's line draw algorithm
            int  dx, dy, s, sx, sy, kl, swap, incr1, incr2;

            // calculation dx and steps
               sx = 0;
               if ((dx = xend-xo) < 0)
               {
                    dx = -dx;
                    --sx;
               }
               else if (dx>0)
                   ++sx;
               sy = 0;
               if ((dy = yend-yo) < 0)
               {
                   dy = -dy;
                   --sy;
               }
               else if (dy>0) 
                   ++sy;

            // calculate the slope
               swap = 0;
               if ((kl = dx) < (s = dy))
               {
                  dx = s;
                  dy = kl;
                  kl = s;
                  ++swap;
               }

               s = (incr1 = dy<<1) - dx;
                                    // incr1 - constant of scalar recalculation
                                    // if current s < 0  and
                                    // s - initial difference
               incr2 = dx<<1;       // second constant of scalar recalculation
                                    // use when s >= 0
               setPixel (xo,yo,line.Color); // current point of vector
               while (--kl >= 0)
               {
                  if (s >= 0)
                  {
                     if (swap)
                         xo+= sx;
                     else
                         yo+= sy;
                     s-= incr2;
                  }
                  if (swap)
                      yo += sy;
                  else
                      xo+= sx;
                  s += incr1;
                  setPixel (xo,yo,line.Color); // current point of vector
               }
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
    
    public:
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

/* wrong algorithm

        inline void drawLine(size_t xo, size_t yo, size_t xend, size_t yend, const LineDefinition& line = LineDefinition(INK,1))
        {
            if(xo > xend)
            {
                size_t tmp = xo;
                xo = xend;
                xend = tmp;
                tmp = yo;
                yo = yend;
                yend = tmp;
            }

            if(yo == yend)
            {
                for (size_t x = xo; x <= xend; x++)
                 for(size_t y = yo; y < yo + line.Width; y++)
                    setPixel(x, y, line.Color);
            }
            else
            {
                size_t yPrev = yo;
                for(size_t xL = xo; xL <= xend; xL++)
                {
                    int dy = (xend==xo) ? int(yend) - yo : int( ((int(yend - yo) * ((int(xL - xo)<<8) / int(xend - xo)) ) + 0x7F)>>8 );
//                    int dy = (xend==xo) ? int(yend) - yo : int(( (int(yend) - int(yo)) * ( double((int(x) - int(xo))) / double(int(xend) - int(xo)) )) + 0.5);
                    for(size_t x = xL; x < xL + line.Width; x++)
                    {
                        if(yo <= yend)
                            for(size_t y = yPrev; y < yo + dy; y++)
                                setPixel(x, y, line.Color);
                        else
                            for(size_t y = yPrev; y > size_t(int(yo) + dy); y--)
                                setPixel(x, y, line.Color);
                        setPixel(x, yo+dy, line.Color);
                    }
                    yPrev = size_t(int(yo) + dy);
                }
            }
        }
*/

/* slow and floatting-point:

        inline void drawCircle(size_t xo, size_t yo, size_t radius, const LineDefinition& line = LineDefinition(INK,1))
        {
            size_t y[2] = { (yo + radius), (yo - radius) };
            for(size_t r = 1; r <= radius; r++)
            {
                size_t dy = (size_t)( 0.5 + sqrt(double(radius*radius - r*r)) );
                drawLine(xo - (r-1), y[0], xo - r, yo + dy, line); //setPixel(xo - r, yo + dy, color);
                drawLine(xo - (r-1), y[1], xo - r, yo - dy, line); //setPixel(xo - r, yo - dy, color);
                drawLine(xo + (r-1), y[0], xo + r, yo + dy, line); //setPixel(xo + r, yo + dy, color);
                drawLine(xo + (r-1), y[1], xo + r, yo - dy, line); //setPixel(xo + r, yo - dy, color);
                y[0] = yo + dy;
                y[1] = yo - dy;
            }
        }
*/
        inline void drawImage(size_t xo, size_t yo, const Image& img)
        {
            for (size_t y=yo; y <= yo + img.getHeight(); y++)
             for(size_t x=xo; x <= xo + img.getWidth (); x++)
                 setPixel(x, y, img.getPixel(x-xo, y-yo));
        }

        inline void fillRegion(const Region& reg)
        {
        }
    };
}
