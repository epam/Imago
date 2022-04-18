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
#ifndef _image_draw_utils_h
#define _image_draw_utils_h

#include "comdef.h"
#include "vec2d.h"

namespace imago
{
    class Image;
    
    class ImageDrawUtils
    {
    public:
        static void putLine( Image &img, double thetha, double r, double eps, byte color );

        static void putLineSegment( const Vec2i &p1, const Vec2i &p2, int color, void *userdata, bool (*plot)( int x, int y, int color, void *userdata ) );
        static void putLineSegment( Image &img, const Vec2i &p1, const Vec2i &p2, byte color );
        
        static void putCircle( Image &img, int cx, int cy, int r, byte color );
        static void putCircle( int cx, int cy, int r, byte color, void *userdata, bool (*plot)( int x, int y, int color, void *userdata ) );

        template <class EuclideanGraph>
        static void putGraph( Image &img, const EuclideanGraph &cg )
        {
           EuclideanGraph &g = const_cast<EuclideanGraph&>(cg);
           for (typename EuclideanGraph::vertex_iterator begin = g.vertexBegin(), end = g.vertexEnd();
                begin != end;
                ++begin)
           {
              typename EuclideanGraph::vertex_descriptor v = *begin;
              const Vec2d &pos = g.getVertexPosition(v);
              ImageDrawUtils::putCircle(img, round(pos.x), round(pos.y), 4, 100);
           }
           for (auto begin = g.edgeBegin(), end = g.edgeEnd(); begin != end; ++begin)
           {
              typename EuclideanGraph::edge_descriptor e = *begin;
              const Vec2d &b_pos = g.getVertexPosition(e.m_source);
              const Vec2d &e_pos = g.getVertexPosition(e.m_target);
              ImageDrawUtils::putLineSegment(img, b_pos, e_pos, 100);
           }
        }

    private:
        static void _plot8points( int cx, int cy, int x, int y, byte color, void *userdata, bool (*plot)( int x, int y, int color, void *userdata ) );
        static void _plot4points( int cx, int cy, int x, int y, byte color, void *userdata, bool (*plot)( int x, int y, int color, void *userdata ) );

        static bool _imagePlot( int x, int y, int color, void *userdata );
    };
};


#endif /* _image_draw_utils_h */

