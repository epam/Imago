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
#include "binarizer.h"
#include "molecule.h"
#include "fourier_descriptors.h"
#include "log_ext.h"
#include "output.h"
#include "prefilter.h"
#include "weak_segmentator.h"
#include "constants.h"

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
	logEnterFunction();

   int x, y, i, j;

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
         {
            for (i = y - 1; i <= y + 1; i++)
            {
               for (j = x - 1; j <= x + 1; j++)
               {
                  if (i >= 0 && i < img.getHeight() && j >= 0 && j < img.getWidth())
                     if (img.getByte(j, i) == 0)
                        img.getByte(j, i) = 255;
               }
            }
            
         }
      }
   }

   getLogExt().appendImage("Decornered image", img);
}

void GraphicsDetector::_extractPolygon(const Settings& vars, const Segment &seg, Points2d &poly ) const
{
	logEnterFunction();

	getLogExt().appendSegment("Segment", seg);

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

   getLogExt().append("eps" , _approx_eps);

   if (_approximator)
      _approximator->apply(vars, _approx_eps, contour, poly);

	if (getLogExt().loggingEnabled())
	{		
		Segment temp;
		temp.copy(seg, false);		
		for (size_t u = 0; u < poly.size(); u++)
			ImageDrawUtils::putCircle(temp, round(poly[u].x), round(poly[u].y), 5, 0);
		getLogExt().appendImage("Segment with polypoints", temp);
	}

   for (size_t i = 0; i < poly.size(); i++)
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

void GraphicsDetector::extractRingsCenters(const Settings& vars, SegmentDeque &segments, Points2d &ring_centers ) const
{
	logEnterFunction();

   for (SegmentDeque::iterator it = segments.begin(); it != segments.end();)
   {      
	   if (absolute((*it)->getRatio() - vars.graph.RatioSub) < vars.graph.RatioTresh)
      {
         Segment tmp;

         tmp.copy(**it);
         ThinFilter2(tmp).apply();

		 getLogExt().appendSegment("Ring?", tmp);
         
         if (isCircle(vars, tmp))
         {
            bool valid = true;
            double r = ((*it)->getWidth() + (*it)->getHeight()) / 4;
            Vec2d center = tmp.getCenter();
            BOOST_FOREACH(Segment *s, segments)
            {
               double d = Vec2d::distance(center, s->getCenter());
			   getLogExt().append("R", r);
			   getLogExt().append("D", d);
               if (d < r)
               {
                  valid = false;
                  break;
               }
            }
			getLogExt().append("valid", (int)valid);

            if (!valid)
            {
               ++it;
               continue;
            }

            ring_centers.push_back(tmp.getCenter());
            delete *it;
            it = segments.erase(it);
            continue;
         }
      }
      ++it;
   }

}


void GraphicsDetector::analyzeUnmappedLabels( std::deque<Label> &unmapped_labels, 
                                              Points2d &ring_centers )
{
	logEnterFunction();

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

void GraphicsDetector::detect(const Settings& vars, const Image &img, Points2d &lsegments ) const
{
	logEnterFunction();

   SegmentDeque segs;
   Points2d poly;
   Image tmp;
   tmp.copy(img);
   
   ThinFilter2 tf2(tmp);
   tf2.apply();
     
   if (vars.general.IsHandwritten)
   {
	   // less accurate, but more stable
	   _decorner(tmp);   
   }
   else
   {
	   // more precise, but depends on pixels artefacts
	   WeakSegmentator::decorner(tmp, 255);
   }

   Segmentator::segmentate(tmp, segs);

   BOOST_FOREACH( Segment *s, segs )
   {
      poly.clear();
      _extractPolygon(vars, *s, poly);

	  for (size_t i = 1; i < poly.size(); i++)
      {
         lsegments.push_back(poly[i - 1]);
         lsegments.push_back(poly[i]);
      }
      delete s;
   }
   segs.clear();
}
