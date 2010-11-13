/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#include <cmath>
#include <vector>
#include <deque>
#include <stack>

#include "exception.h"
#include "fourier_descriptors_extractor.h"
#include "image.h"
#include "binarizer.h"
#include "png_saver.h"
#include "output.h"
#include "image_utils.h"
#include "algebra.h"
//#include "approximator.h"

using namespace imago;

void FourierDescriptorsExtractor::getDescriptors( const Segment *seg, int count )
{
   std::vector<double> &_desc = seg->getFeatures().descriptors;
      
   std::vector<Vec2d> poly;

   //PngSaver(*seg).saveImage("output/poly2.png");

   _getBoundaryPolygon(*seg, poly);

   _desc.clear();

   double length = 0; //length of polygon
   double square;
   Vec2d p1, p2, p3;
   Vec2d v1, v2; 

   for (int i = 1; i < (int)poly.size(); i++)
   {
      length += Vec2d::distance(poly[i - 1], poly[i]);
   }

   for (int i = 1; i <= count; i++)
   {
      double lk, phi;
      double a = 0, b = 0;

      for (int k = 1; k < (int)poly.size(); k++)
      {
         lk = 0;
         for (int j = 1; j <= k; j++)
         {
            lk += Vec2d::distance(poly[j - 1], poly[j]);
         }

         p1 = poly[k - 1];
         p2 = poly[k];

         if (k == (int)poly.size() - 1)
            p3 = poly[0];
         else
            p3 = poly[k + 1];

         v1.diff(p3, p2);
         v2.diff(p2, p1);
           
         phi = Vec2d::angle(v1, v2);

         square = p1.x * p2.y - p2.x * p1.y +
                  p2.x * p3.y - p3.x * p2.y +
                  p3.x * p1.y - p1.x * p3.y;

         if (square < 0)
            phi = -phi;

         a += sin(2 * PI * i * lk / length) * phi;
         b += cos(2 * PI * i * lk / length) * phi;
      }

      a /= -PI * i;
      b /= PI * i;

      //r = sqrt(a * a + b * b);

      _desc.push_back(a);
      _desc.push_back(b);
   }
}

void FourierDescriptorsExtractor::_getContour( const Image &_img, IntDeque &cont )
{
   Image img;
   img.copy(_img);
   Binarizer(img, 190).apply();
   //ImageUtils::saveImageToFile(img, "output/gc.png");

   int w = img.getWidth(), h = img.getHeight();
   int k = (h + 1) * (w + 1);
   int begin = 0, x, y;
   byte ul, ur, dl, dr;
   int i;
   std::deque<int> prev(k, -1);

   double dist = 0;
   double min_dist = 1e16;
   for (i = 0; i < w * h; i++)
   { 
      if (img[i] != 255)
      {
         y = i / w;
         x = i % w;
         //begin = y * (w + 1) + x;

         dist = sqrt((double)x * x + y * y);
         if (min_dist - dist > EPS)
         {
            min_dist = dist;
            begin = i + i / w;
         }

         //begin = i + i / w;
         //break;
      }
   }

   std::stack<int> stack;
   int cur, p = 0;
   int t = 0, s = 0;
   int next[4] = {-1, -1, -1, -1};
   int delta;
   int first;
   first = begin + 1;
   y = first / (w + 1);
   x = first % (w + 1);
   
   if (begin >= w + 2 && img[first - 1 - y] != 255 &&
       img[first - w - 1 - (y - 1)] != 255 &&
       img[first - y] != 0 && img[first - w - 1 - 1 - (y - 1)] != 0)
   {
      first -= w + 1;
   }

   cur = first;
   stack.push(cur);
   int iterations = 0;
   while (true)
   {
      iterations++;
      if (iterations > k)
         throw NoContourException("infinite loop");

      if (stack.size() == 0)
         throw NoContourException();

      cur = stack.top();
      stack.pop();

      prev[cur] = p;
      delta = cur - p;

      if (cur == begin)
         break;

      y = cur / (w + 1);
      x = cur % (w + 1);

      if (y > 0 && y < h && x > 0 && x < w)
      {
         if (img[cur - y] != 255 && img[cur - w - 1 - 1 - (y - 1)] != 255 &&
             img[cur - 1 - y] != 0 && img[cur - w - 1 - (y - 1)] != 0)
         {
            if (delta == w + 1 || delta == w)
               t = cur + 1;
            else if (delta == -1) // || delta == w + 2
               t = cur - w - 1;
            else if (delta == -(w + 1) || delta == -w)
               t = cur - 1;
            else if (delta == 1) // || delta == -(w + 2)
               t = cur + w + 1;

            prev[cur] = -1;
            stack.push(t);
            continue;
         }

         if (img[cur - 1 - y] != 255 && img[cur - w - 1 - (y - 1)] != 255 &&
             img[cur - y] != 0 && img[cur - w - 1 - 1 - (y - 1)] != 0)
         {
            if (delta == w + 1) // || delta == w
               t = cur - 1;
            else if (delta == -1 || delta == -(w + 2))
               t = cur + w + 1;
            else if (delta == -(w + 1)) // || delta == -w
               t = cur + 1;
            else if (delta == 1 || delta == w + 2)
               t = cur - (w + 1);

            prev[cur] = -1;
            stack.push(t);
            continue;
         }
      }

      
      if (delta == 1 || delta == (w + 2))
         s = 4;
      else if (delta == (w + 1) || delta == w || delta == 2 * (w + 1))
         s = 3;
      else if (delta == -1 || delta ==  -(w + 2))
         s = 2;
      else if (delta == -(w + 1) || delta == -w || delta == -2 * (w + 1))
         s = 1;


      //Where can we go from there
      ul = (x - 1 >= 0 && y - 1 >= 0)?img.getByte(x - 1, y - 1):255;
      ur = (x < w && y - 1 >= 0)?img.getByte(x, y - 1):255;
      dl = (x - 1 >= 0 && y < h)?img.getByte(x - 1, y):255;
      dr = (x < w && y < h)?img.getByte(x, y):255;

      if (y - 1 >= 0 && (ul - ur) != 0)
      {
         next[(s + 0) % 4] = cur - w - 1;
      }
      if (x + 1 < w + 1 && (ur - dr) != 0)
      {
         next[(s + 1) % 4] = cur + 1;
      }
      if (y + 1 < h + 1 && (dr - dl) != 0)
      {
         next[(s + 2) % 4] = cur + w + 1;
      }
      if (x - 1 >= 0 && (dl - ul) != 0)
      {
         next[(s + 3) % 4] = cur - 1;
      } 

      for (i = 3; i >= 0; i--)
      {
         if (next[i] != -1)
         {
            if (prev[next[i]] == -1)
               stack.push(next[i]);
            next[i] = -1;
         }
      } 

      p = cur;
   }

   cont.clear();
   cur = prev[begin];
   do
   {
      cont.push_back(cur);
      cur = prev[cur];
   } while (cur != first);
   cont.push_back(begin);
}

void FourierDescriptorsExtractor::_getBoundaryPolygon( const Image &_img,
                                                       std::vector<Vec2d> &poly )
{
   IntDeque cont;

   _getContour(_img, cont);
   
   for (int i = cont.size() - 1; i >= 0; i--)
   { 
      int &p = cont[i];
      Vec2d v;
      v.y = p / (_img.getWidth() + 1);
      v.x = p % (_img.getWidth() + 1);
      poly.push_back(v);
   }

   //return;
   
   poly.push_back(Vec2d(poly[0])); //Vec2d(poly[0])
   _approximatePolygon(poly);
   //Array<Vec2d> approximated;
   //Approximator::apply(poly, approximated);

   //poly.copy(approximated);
   //_drawPolygon(_img, poly);
}

void FourierDescriptorsExtractor::_approximatePolygon( std::vector<Vec2d> &poly )
{
   double epsilons[2] = {1.047, 0.8}; //"Constants" ?
   for (int l = 0; l < 2; l++)
   {
      int i = 1;
      double epsilon = epsilons[l];

      while (i < (int)poly.size() - 2)
      {
         int j, k;
         j = i + 1;
         bool flag = 1;
         while (j < (int)poly.size() - 1 && flag)
         {
            j++;
            for (k = i + 1; k < j; k++)
            {
               if (Algebra::distance2segment(poly[k], poly[i], poly[j]) > epsilon)
               {
                  flag = false;
                  break;
               }
            }
         }
         j--;

         for (k = i + 1; k < j; k++)
            poly.erase(poly.begin() + (i + 1));

         i++;
      }
   }

   poly.pop_back();
}

void FourierDescriptorsExtractor::_drawPolygon( const Image &_img,
                                                std::vector<Vec2d>& poly )
{
   int w, h;
   w = _img.getWidth() + 1;
   h = _img.getHeight() + 1;
   Image tmp(w, h);
   tmp.fillWhite();
   
   for (int i = 0; i < (int)poly.size(); i++)
   {
      tmp.getByte(poly[i].x, poly[i].y) = 0;
   }
   /*FileOutput fout("poly.png"); DEBUG output
   PngSaver(tmp).saveImage(fout);
   fout.flush();*/ //DEBUG output
}
