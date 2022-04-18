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

#include <tuple>

#include "settings.h"
#include "skeleton.h"

namespace imago
{
    class DoubleBondMaker
    {
    private:
        typedef Skeleton::Vertex Vertex;
        typedef Skeleton::Edge Edge;
        typedef Skeleton::SkeletonGraph Graph;

    public:
        DoubleBondMaker(const Settings& settings, Skeleton& s);

        typedef std::tuple<int, Edge, Edge> Result;

        Result operator()(const std::pair<Edge, Edge>& edges);

        virtual ~DoubleBondMaker();

    private:
        Edge empty;
        Edge first, second;
        Bond bf, bs;
        Vertex fb, fe, sb, se;
        Vec2d fb_pos, fe_pos, sb_pos, se_pos;

        Result _validateVertices();

        DoubleBondMaker(const DoubleBondMaker&);

        Result _simple();

        Result _hard();

        void _disconnect(Vertex a, Vertex b, const Vertex* third);
        Skeleton& _s;
        Graph& _g;
        double _avgBondLength;

        const Settings& vars;
    };

    template <class Graph>
    class DoubleBondComparator
    {
    public:
        DoubleBondComparator(Graph& g) : _g(g)
        {
        }
        typedef typename Graph::edge_descriptor Edge;
        int operator()(const std::pair<Edge, Edge>& a, const std::pair<Edge, Edge>& b)
        {
            double average_len_a = 0.5 * (_g.getEdgeBond(a.first).length + _g.getEdgeBond(a.second).length);
            double average_len_b = 0.5 * (_g.getEdgeBond(b.first).length + _g.getEdgeBond(b.second).length);
            return average_len_a > average_len_b;
        }

    private:
        Graph& _g;
    };
}
