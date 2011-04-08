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

#include <deque>

#include "boost/foreach.hpp"

#include "comdef.h"
#include "current_session.h"
#include "graph_extractor.h"
#include "graphics_detector.h"
#include "image_utils.h"
#include "image_draw_utils.h"
#include "recognition_settings.h"
#include "segment.h"
#include "skeleton.h"

using namespace imago;

void GraphExtractor::extract( const GraphicsDetector &gd, const SegmentDeque &segments, Skeleton &graph )
{
   Image tmp;
   int w = 0, h = 0;

   //TODO: New image here. Is this really necessary? 
   BOOST_FOREACH( Segment *s, segments )
   {
      if (s->getX() + s->getWidth() >= w)
         w = s->getX() + s->getWidth();
      if (s->getY() + s->getHeight() >= h)
         h = s->getY() + s->getHeight();
   }
   tmp.init(w + 10, h + 10);
   tmp.fillWhite();

   BOOST_FOREACH( Segment *s, segments )
   {
      ImageUtils::putSegment(tmp, *s, true);
   }

   RecognitionSettings &rs = getSettings();

   if (rs["DebugSession"])
   {
      ImageUtils::saveImageToFile(tmp, "output/tmp.png");
   }

   //TODO: We were thinking about refactoring it.
   extract(gd, tmp, graph);
}

void GraphExtractor::extract( const GraphicsDetector &gd, const Image &img, Skeleton &graph )
{
   double avg_size = 0;
   Points2d lsegments;

   gd.detect(img, lsegments);

   if (lsegments.empty())
      return;

   for (int i = 0; i < (int)lsegments.size() / 2; i++)
   {
      Vec2d &p1 = lsegments[2 * i];
      Vec2d &p2 = lsegments[2 * i + 1];

      double dist = Vec2d::distance(p1, p2);

      if (dist > 2.0)
         avg_size += dist;
   }

   avg_size /= (lsegments.size() / 2);

   graph.setInitialAvgBondLength(avg_size);

   for (int i = 0; i < (int)lsegments.size() / 2; i++)
   {
      Vec2d &p1 = lsegments[2 * i];
      Vec2d &p2 = lsegments[2 * i + 1];

      double dist = Vec2d::distance(p1, p2);

      if (dist > 2.0)
         graph.addBond(p1, p2);      
   }

   RecognitionSettings &rs = getSettings();

   if (rs["DebugSession"])
   {
      Image tmp;

      tmp.emptyCopy(img);
      ImageDrawUtils::putGraph(tmp, (Skeleton::SkeletonGraph)graph);
      ImageUtils::saveImageToFile(tmp, "output/graph_begin.png");
   }

   graph.modifyGraph();

   if (rs["DebugSession"])
   {
      Image tmp;

      tmp.emptyCopy(img);
      ImageDrawUtils::putGraph(tmp, (Skeleton::SkeletonGraph)graph);
      ImageUtils::saveImageToFile(tmp, "output/graph_mod.png");
   }
}
