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

#pragma once
#ifndef _rng_builder_h
#define _rng_builder_h

#include "stl_fwd.h"
#include "comdef.h"

namespace imago
{
   class RNGBuilder
   {
   public:
      template <class EuclideanGraph>
      static void build( EuclideanGraph &g )
      {
         int n = (int)g.vertexCount();

         std::vector<typename EuclideanGraph::vertex_descriptor> ind2vert(n);
         DoubleVector distances(n * n, 0);

         int i = 0;
         for(typename EuclideanGraph::vertex_iterator begin = g.vertexBegin(), end = g.vertexEnd(); begin != end; begin = end, ++i)
            for(typename EuclideanGraph::vertex_descriptor v;
               begin != end ? (v = *begin, true) : false;
               ++begin)
                  ind2vert[i] = v;

         for (int i = 0; i < n; i++)
         {
            for (int j = 0; j < n; j++)
            {
               distances[i + j * n] = Vec2d::distance(g.getVertexPosition(ind2vert[i]),
                                                      g.getVertexPosition(ind2vert[j]));
            }
         }

         for (int i = 0; i < n; i++)
         {
            for (int j = 0; j < n; j++)
            {
               if (i != j)
               {
                  bool add_edge = true;
                  double d = distances[i + j * n];

                  for (int k = 0; k < n; k++)
                  {
                     if (k != i && k != j)
                     {
                        if (d > std::max(distances[i + k * n],
                                         distances[k + j * n]))
                        {
                           add_edge = false;
                           break;
                        }
                     }
                  }

                  if (add_edge)
                  {
                     std::pair<typename EuclideanGraph::edge_descriptor, bool> added = g.addEdge(ind2vert[i], ind2vert[j]);

                     if (!added.second)
					 {
						 getLogExt().appendText("Warning: <RNG::build> edge is not added");
					 }

                     g.setWeight(added.first, distances[i + j * n]);
                  }
               }
            }
         }
      }
   };
}


#endif /* _rng_builder_h_ */