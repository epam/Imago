#include "Image.h"

namespace gga
{
    static inline void putClipPoint(int x, int y, Points &points)
    {
        points.push_back(Point((x < 0)?0:x, (y < 0)?0:y));
    }

    static inline void setEdges (int xc, int yc, int x, int y, size_t mask, Points &points)
    {
        if(mask&1)
            putClipPoint(xc+x, yc+y, points);
        if(mask&2)
            putClipPoint(xc+y, yc+x, points);
        if(mask&4)
            putClipPoint(xc+y, yc-x, points);
        if(mask&8)
            putClipPoint(xc+x, yc-y, points);
        if(mask&16)
            putClipPoint(xc-x, yc-y, points);
        if(mask&32)
            putClipPoint(xc-y, yc-x, points);
        if(mask&64)
            putClipPoint(xc-y, yc+x, points);
        if(mask&128)
            putClipPoint(xc-x, yc+y, points);
    }

    void Image::drawLine(size_t xo, size_t yo, size_t xend, size_t yend, const LineDefinition& line)
    {
        //Bresenham's line draw algorithm
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
        incr2 = dx<<1;                // second constant of scalar recalculation
                                    // use when s >= 0
        setEdgeCircle(xo,yo,xend,yend, dx, dy, swap, line.Width/2, &svx, &svy, points);
        putClipPoint((int)xo+svx, (int)yo-svy, points);
        putClipPoint((int)xo-svx, (int)yo+svy, points);
            
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

            putClipPoint((int)xo+svx,(int)yo-svy, points); // current point of vector
            putClipPoint((int)xo-svx,(int)yo+svy, points); // current point of vector
        }

        std::sort(points.begin(), points.end());
        Points::const_iterator first = points.begin();

        for (Points::const_iterator it = points.begin(); it != points.end(); it++)
        {
            Coord fx = (first->X < Width)?first->X:Width-1;
            Coord fy = (first->Y < Height)?first->Y:Height-1;
            Coord cx = (it->X < Width)?it->X:Width-1;
            Coord cy = (it->Y < Height)?it->Y:Height-1;

            if((it+1) == points.end())
            {
                memset(&Data[fx + fy* Width], line.Color.Value, cx - fx + 1);
                break;
            }
            if(fy != (it+1)->Y)
            {
                memset(&Data[fx + fy * Width], line.Color.Value, cx - fx + 1);
                first = it+1;
            }
        }
    }  

    void Image::setEdgeCircle(size_t xo, size_t yo, size_t xe, size_t ye, size_t dx, size_t dy, size_t swap, size_t radius, int *sx, int *sy, Points &points)
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

} //namespace

    /*
        void drawHairline(size_t xo, size_t yo, size_t xend, size_t yend, const LineDefinition& line = LineDefinition(INK,1))
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
*/

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
