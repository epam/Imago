/****************************************************************************
* Copyright (C) from 2009 to Present EPAM Systems.
*
* This file is part of Imago toolkit.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
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
         for (typename EuclideanGraph::vertex_iterator begin = g.vertexBegin(), end = g.vertexEnd();
            begin != end;
            ++begin)
         {
            typename EuclideanGraph::vertex_descriptor v = *begin;
            ind2vert[i] = v;
            g.setVertexIndex(v, i++);
         }

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