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

#include "segments_graph.h"

namespace imago
{
   namespace segments_graph
   {
      void add_segment( Segment *seg, SegmentsGraph &g )
      {
         Vec2d pos = seg->getCenter();

         SegmentsGraph::vertex_descriptor v = g.addVertex();
         g.setVertexPosition(v, pos);
         g.setVertexSegment(v, seg);
      }
   }
}