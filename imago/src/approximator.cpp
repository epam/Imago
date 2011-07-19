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
#include <utility>
#include <opencv/cv.h>


#include "image.h"
#include "approximator.h"
#include "algebra.h"
#include "image_utils.h"
#include "image_draw_utils.h"

using namespace imago;

void SimpleApproximator::apply( double eps, const Points2d &input,Points2d &output ) const
{
   IntVector sample;
   std::vector<_Line> lines;
   std::vector<double> lengths;
   double ratio, mult;
   output.clear();

   _prepare(input, sample);

   lines.resize(sample.size() - 1);
   lengths.resize(sample.size() - 1);
   for (int i = 0; i < (int)sample.size() - 1; i++)
   {
      _calc_line(input, sample[i], sample[i + 1], lines[i]);
      lengths[i] = Vec2d::distance(input[sample[i]], input[sample[i + 1]]);
   }

   output.push_back(input[0]);
   for (int i = 0; i < (int)lines.size() - 1; i++)
   {
      _Line &l1 = lines[i];
      _Line &l2 = lines[i + 1];

      /*
      ratio = lengths[i] / lengths[i + 1];
      if (ratio < 0.3 || ratio > 3.3)
         mult = 0.6;
      else if (ratio < 0.7 || ratio > 10.0 / 7)
         mult = 0.485;
      else
         mult = 0.27;
      */

      //changed in "handwriting"
      if (absolute<double>(l1.a * l2.b - l2.a * l1.b) < eps) //"Constants" //0.65
      {
         l2.a = (l1.a + l2.a) / 2;
         l2.b = (l1.b + l2.b) / 2;
         l2.c = (l1.c + l2.c) / 2;
         //lengths[i + 1] += lengths[i];
         continue;
      }
      Vec2d v;
      v.x = (l1.b * l2.c - l2.b * l1.c) / (l1.a * l2.b - l2.a * l1.b);
      v.y = (l1.c * l2.a - l2.c * l1.a) / (l1.a * l2.b - l2.a * l1.b);
      output.push_back(v);
   }
   output.push_back(input.back());
}

void SimpleApproximator::_prepare( const Points2d &poly, IntVector &sample ) const
{
   double epsilons[2] = {1.13, 0.8}; //"Constants" //1.33, 1.2
   double dist = 0;
   sample.push_back(0);

   for (int l = 0; l < 1; l++)
   {
      int i = 0;
      double epsilon = epsilons[l];

      while (i < (int)poly.size() - 2)
      {
         int j, k;
         j = i + 1;
         bool flag = 1;
         while (j < (int)poly.size() - 1 && flag)
         {
            j++;
            dist = 0;
            for (k = i + 1; k < j; k++)
            {
               if (Algebra::distance2segment(poly[k], poly[i], poly[j]) > epsilon)
               {
                  flag = false;
                  break;
               }
            }
         }
         if (j != (int)poly.size() - 1)
            sample.push_back(j - 1);
         else
            sample.push_back(j);

         i = j + 1;
      }
   }
}

void SimpleApproximator::_calc_line( const Points2d &input, int begin, int end, _Line &res ) const
{
   double Sx = 0, Sy = 0, Sx2 = 0, Sxy = 0;
   
   for (int i = begin; i < end; i++)
   {
      const Vec2d &v = input[i];
      Sx += v.x;
      Sy += v.y;
      Sx2 += v.x * v.x;
      Sxy += v.x * v.y;
   }
   int n = end - begin;
   double dev = Sx2 - 2 * (Sx / n) * Sx + Sx * Sx / n;
   dev = dev / (n - 1);
   //TODO: consider vert lines carefully
   if (dev < 1.0) //"Constants"
   {
      res.a = 1;
      res.b = 0;
      res.c = -Sx / n;
   }
   else
   {
      res.a = (n * Sxy - Sx * Sy) / (n * Sx2 - Sx * Sx);
      res.b = -1;
      res.c = (Sy * Sx2 - Sx * Sxy) / (n * Sx2 - Sx * Sx);
   }
}

void CvApproximator::apply( double eps, const Points2d &input, Points2d &output ) const
{
   std::vector<cv::Point> vcurve;
   for (int i = 0; i < (int)input.size(); i++)
      vcurve.push_back(cv::Point(input[i].x, input[i].y));

   bool closed = (vcurve[0] == vcurve[vcurve.size() - 1]);
   cv::Mat curve(vcurve);
   std::vector<cv::Point> approxCurve;
   cv::approxPolyDP(curve, approxCurve, eps, closed);

   output.clear();
   for (int i = 0; i < (int)approxCurve.size(); i++)
      output.push_back(Vec2d(approxCurve[i].x, approxCurve[i].y));
   if (closed)
      output.push_back(Vec2d(output[0]));
}

void DPApproximator::_apply_int( double eps, const Points2d &input, Points2d &output ) const
{
   using namespace std;
   deque<pair<int, int> > stack;
   int l, r;
   int i;

   output.clear();
   stack.push_back(make_pair(0, input.size() - 1));
   
   while (stack.size() > 0)
   {
      boost::tie(l, r) = stack.back();
      stack.pop_back();

      const Vec2d &lp = input[l], &rp = input[r];
      int max_ind = -1, max_dist = eps;
      for (i = l + 1; i < r; ++i)
      {
         double d = Algebra::distance2segment(input[i], lp, rp);
         if (d > max_dist)
         {
            max_dist = d;
            max_ind = i;
         }
      }

      if (max_ind != -1)
      {
         stack.push_back(make_pair(max_ind, r));
         stack.push_back(make_pair(l, max_ind));
      }
      else
      {
         output.push_back(input[l]);
      }  
   }
   output.push_back(input.back());
}

void DPApproximator::apply( double eps, const Points2d &input, Points2d &output ) const
{
   if (input.front() == input.back())
   {
      //closed contour!
      //split input in halfes and 
   }
   else
   {
      _apply_int(eps, input, output);
   }
}
