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
#include <deque>
#include <vector>

#include "boost/foreach.hpp"

#include "graphics_detector.h"
#include "image.h"
#include "segment.h"
#include "segmentator.h"
#include "approximator.h"
#include "thin_filter2.h"
#include "image_utils.h"
#include "image_draw_utils.h"
#include "convolver.h"
#include "binarizer.h"
#include "molecule.h"
#include "fourier_descriptors.h"
#include "recognition_settings.h"
#include "font.h"
#include "current_session.h"
#include "output.h"

using namespace imago;

GraphicsDetector::GraphicsDetector() : _approximator(0), _approx_eps(0.0)
{
}

GraphicsDetector::GraphicsDetector( const BaseApproximator *approximator, double eps ) :
      _approximator(approximator), _approx_eps(eps)
{
}


GraphicsDetector::~GraphicsDetector()
{
}

void GraphicsDetector::_decorner( Image &img ) const
{
   int x, y, i, j;
   RecognitionSettings &rs = getSettings();

   for (y = 0; y < img.getHeight(); y++)
   {
      for (x = 0; x < img.getWidth(); x++)
      {
         if (img.getByte(x, y) != 0)
            continue;

         int c = 0;
         for (i = y - 1; i <= y + 1; i++)
         {
            for (j = x - 1; j <= x + 1; j++)
            {
               if (i >= 0 && i < img.getHeight() && j >= 0 && j < img.getWidth())
                  if (img.getByte(j, i) == 0)
                     c++;
            }
         }
         if (c >= 4)
            img.getByte(x, y) = 255;
      }
   }

   if (rs["DebugSession"])
      ImageUtils::saveImageToFile(img, "output/decornered.png");
}

void GraphicsDetector::_extractPolygon( const Segment &seg, Points2d &poly ) const
{
   int begin = -1;
   bool closed = true;
   int i, j, x, y, c;
   int cur, prev, next;
   int h = seg.getHeight(), w = seg.getWidth();
   Points2d contour;

   if (w * h == 1)
      return;
   
   for (c = 0, y = 0; y < h && c != 2; y++)
   {
      for (x = 0; x < w; x++)
      {
         if (seg.getByte(x, y) != 0)
            continue;

         if (begin == -1)
            begin = x + y * w;

         c = 0;
         for (i = y - 1; i <= y + 1; i++)
         {
            for (j = x - 1; j <= x + 1; j++)
            {
               if (i >= 0 && i < h && j >= 0 && j < w)
                  if (seg.getByte(j, i) == 0)
                     c++;
            }
         }
         if (c == 2)
         {
            begin = x + y * w;
            closed = false;
         }
      }
   }
   
   cur = begin;
   prev = -1;
   while (true)
   {
      x = cur % w;
      y = cur / w;
      contour.push_back(Vec2d(x, y));

      next = -1;
      for (i = y - 1; i <= y + 1; i++)
      {
         for (j = x - 1; j <= x + 1; j++)
         {
            if (i >= 0 && i < h && j >= 0 && j < w)
            {
               if ((i == y && j == x) || (j + i * w) == prev)
                  continue;

               if (seg.getByte(j, i) == 0)
                  next = j + i * w;
            }
         }
      }

      if (closed && next == begin)
         break;
      if (!closed && next == -1)
         break;
      prev = cur;
      cur = next;
   }
   if (closed)
   {
      Vec2d tmp;

      tmp.copy(contour[0]);
      contour.push_back(tmp); //WATCH
   }

   if (_approximator)
      _approximator->apply(_approx_eps, contour, poly);

   for (i = 0; i < (int)poly.size(); i++)
   {
      Vec2d v(seg.getX(), seg.getY());
      poly[i].add(v);
   }
}

int GraphicsDetector::_countBorderBlackPoints( const Image &img ) const
{
   int count = 0;

   for (int i = 0; i < img.getWidth(); i++)
   {
      if (img.getByte(i, 0) == 0)
         count++;

      if (img.getByte(i, img.getHeight() - 1) == 0)
         count++;
   }

   for (int j = 0; j < img.getHeight(); j++)
   {
      if (img.getByte(0, j) == 0)
         count++;

      if (img.getByte(img.getWidth() - 1, j) == 0)
         count++;
   }

   return count;
}

struct _AngRadius
{
   float ang;
   float radius;
};

static int _cmp_ang (const void *p1, const void *p2)
{
   const _AngRadius &f1 = *(const _AngRadius *)p1;
   const _AngRadius &f2 = *(const _AngRadius *)p2;

   if (f1.ang < f2.ang)
      return -1;
   return 1;
}

bool isCircle (Image &seg)
{
   int w = seg.getWidth();
   int h = seg.getHeight();
   int i, j;
   float centerx = 0, centery = 0;
   int npoints = 0;

   for (j = 0; j < h; j++)
   {
      for (i = 0; i < w; i++)
      {
         if (seg.getByte(i, j) == 0)
         {
            centerx += i;
            centery += j;
            npoints++;
         }
      }
   }

   if (npoints == 0)
      throw Exception("empty fragment?");

   centerx /= npoints;
   centery /= npoints;

   _AngRadius *points = new _AngRadius[npoints + 1];
   int k = 0;
   float avg_radius = 0;

   for (i = 0; i < w; i++)
      for (j = 0; j < h; j++)
      {
         if (seg.getByte(i, j) == 0)
         {
            float radius = sqrt((i - centerx) * (i - centerx) +
                                (j - centery) * (j - centery));
            points[k].radius = radius;
            avg_radius += radius;
            float cosine = (i - centerx) / radius;
            float sine = (centery - j) / radius;
            float ang = (float)atan2(sine, cosine);
            if (ang < 0)
               ang += 2 * PI;
            points[k].ang = ang;
            k++;
         }
      }

   qsort(points, npoints, sizeof(_AngRadius), _cmp_ang);
   
   points[npoints].ang = points[0].ang + 2 * PI;
   points[npoints].radius = points[0].radius;

   for (i = 0; i < npoints; i++)
   {
      float gap = points[i + 1].ang - points[i].ang;
      float r1 = fabs(points[i].radius);
      float r2 = fabs(points[i + 1].radius);
      float gapr = 1.f;

      if (r1 > r2 && r2 > 0.00001)
         gapr = r1 / r2;
      else if (r2 < r1 && r1 > 0.00001)
         gapr = r2 / r1;

      if (gap < 0.1 && gapr > 2)
      {
         #ifdef DEBUG
         printf("large radios gap: %3f -> %3f at %3f\n", r1, r2, points[i].ang);
         #endif
         delete[] points;
         return false;
      }

      if (gap > 1.0)
      {
         #ifdef DEBUG
         printf("large gap: %3f at %3f\n", gap, points[i].ang);
         #endif
         delete[] points;
         return false;
      }
      if (gap > PI / 8 && (points[i].ang < PI / 8 || points[i].ang > 7 * PI / 4))
      {
         #ifdef DEBUG
         printf("C-like gap: %3f at %3f\n", gap, points[i].ang);
         #endif
         delete[] points;
         return false;
      }
   }

   avg_radius /= npoints;

   if (avg_radius < 0.0001)
   {
      #ifdef DEBUG
      printf("degenerate\n");
      #endif
      delete[] points;
      return false;
   }

   float disp = 0;

   for (i = 0; i < npoints; i++)
      disp += (points[i].radius - avg_radius) * (points[i].radius - avg_radius);

   disp /= npoints;
   float ratio = sqrt(disp) / avg_radius;

   #ifdef DEBUG
   printf("avgr %.3f dev %.3f ratio %.3f\n",
          avg_radius, sqrt(disp), ratio);
   #endif

   delete[] points;
   if (ratio > 0.3)
      return false; // not a circle
   return true;
}

void GraphicsDetector::extractRingsCenters( SegmentDeque &segments, Points2d &ring_centers ) const
{
 /*  int circle_count;
   Segment circle;
   std::vector<double> circle_descriptors;
   
   circle.init(100, 100);
   circle.fillWhite();

   ImageDrawUtils::putCircle(circle, 50, 50, 40, 0);
   circle.crop();
   
   FourierDescriptors::calculate(&circle, 10, circle_descriptors);
   circle_count = _countBorderBlackPoints(circle);

   Image img;

   img.init(1000, 1000);
   img.fillWhite();

   std::vector<double> tmp_descriptors;*/

   for (SegmentDeque::iterator it = segments.begin(); it != segments.end();)
   {      
      if (absolute((*it)->getRatio() - 1.0) < 0.4)
      {
         Segment tmp;

         tmp.copy(**it);
         ThinFilter2(tmp).apply();

         if (getSettings()["DebugSession"])
            ImageUtils::saveImageToFile(tmp, "output/tmp_ring.png");
         
         if (isCircle(tmp))
         {
            ring_centers.push_back(tmp.getCenter());
            delete *it;
            it = segments.erase(it);
            continue;
         }
      }
         /*
         Segment tmp;

         tmp.copy(**it);
         Convolver gauss(tmp);
         gauss.initGauss();
         gauss.apply();
         Binarizer b(tmp, (int)getSettings()["BinarizationLvl"]);
         b.apply();
         ThinFilter2(tmp).apply();
         tmp.crop();         
         
         try 
         {
            FourierDescriptors::calculate(&tmp, 5, tmp_descriptors);
         }
         catch (Exception &e)
         {
            continue; //If it is impossible to get contour - no ring detected
         }

         double diff = 0;

         for (int i = 0; i < (int)tmp_descriptors.size(); i++)
         {
            double a = tmp_descriptors[i],
                   b = circle_descriptors[i], weight;

            if ((i % 2))
               weight = 0.5;  
            else
               weight = 1.5;
            diff += weight * (a - b) * (a - b);
         }

         diff = sqrt(diff);

         if (diff > 0.08 && diff < 0.41)
         {
            int cur_count = _countBorderBlackPoints(**it);

            if (absolute(cur_count - circle_count) < 40)
            {
               ring_centers.push_back(tmp.getCenter());
               delete *it;
               it = segments.erase(it);
               continue;
            }
         }*/
      //}
      ++it;
   }
}


void GraphicsDetector::analyzeUnmappedLabels( std::deque<Label> &unmapped_labels, 
                                              Points2d &ring_centers )
{
   BOOST_FOREACH( Label &l, unmapped_labels )
   {
      //TODO: More convenient criteria here
      //      like 'No O inside convex polygon'
      if (l.satom.atoms[0].label_first == 'O')
      {
         ring_centers.push_back(l.symbols[0]->getCenter());
      }
   }
}

void GraphicsDetector::detect( const Image &img, Points2d &lsegments ) const
{
   SegmentDeque segs;
   Points2d poly;
   Image tmp;
   tmp.copy(img);

   ThinFilter2 tf2(tmp);
   TIME(tf2.apply(), "Thinning");
   _decorner(tmp);

   Segmentator::segmentate(tmp, segs);

   BOOST_FOREACH( Segment *s, segs )
   {
      poly.clear();
      _extractPolygon(*s, poly);

      for (int i = 0; i < (int)poly.size() - 1; i++)
      {
         lsegments.push_back(poly[i]);
         lsegments.push_back(poly[i + 1]);
      }
      delete s;
   }
   segs.clear();
}
