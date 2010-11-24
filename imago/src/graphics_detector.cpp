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
#include "fourier_descriptors_extractor.h"
#include "recognition_settings.h"
#include "font.h"
#include "current_session.h"
#include "output.h"

using namespace imago;

GraphicsDetector::GraphicsDetector()
{
}

GraphicsDetector::~GraphicsDetector()
{
}

void GraphicsDetector::_decorner( Image &img )
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

void GraphicsDetector::_extractPolygon( const Segment &seg, Points &poly )
{
   int begin = -1;
   bool closed = true;
   int i, j, x, y, c;
   int cur, prev, next;
   int h = seg.getHeight(), w = seg.getWidth();
   Points contour;

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

   Approximator::apply(contour, poly);

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

void GraphicsDetector::extractRingsCenters( SegmentDeque &segments, Points &ring_centers )
{
   int circle_count;
   Segment circle;
   std::vector<double> circle_descriptors;
   
   circle.init(100, 100);
   circle.fillWhite();

   ImageDrawUtils::putCircle(circle, 50, 50, 40, 0);
   circle.crop();
   
   FourierDescriptorsExtractor::getDescriptors(&circle, 10, circle_descriptors);
   circle_count = _countBorderBlackPoints(circle);

   Image img;

   img.init(1000, 1000);
   img.fillWhite();

   std::vector<double> tmp_descriptors;
   for (SegmentDeque::iterator it = segments.begin(); it != segments.end();)
   {      
      if (absolute((*it)->getRatio() - 1.0) < 0.2)
      {
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
            FourierDescriptorsExtractor::getDescriptors(&tmp, 5,
                                                        tmp_descriptors);
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

         if (diff > 0.08 && diff < 0.23)
         {
            int cur_count = _countBorderBlackPoints(**it);

            if (absolute(cur_count - circle_count) < 40)
            {
               ring_centers.push_back(tmp.getCenter());
               delete *it;
               it = segments.erase(it);
               continue;
            }
         }
      }
      ++it;
   }
}

void GraphicsDetector::detect( const Image &img, Points &lsegments )
{
   SegmentDeque segs;
   Points poly;
   Image tmp;
   tmp.copy(img);

   ThinFilter2 tf2(tmp);
   tf2.apply();
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

