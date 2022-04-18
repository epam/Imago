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
    class TripleBondMaker
    {
    private:
        typedef Skeleton::Vertex Vertex;
        typedef Skeleton::Edge Edge;
        typedef Skeleton::SkeletonGraph Graph;

    public:
        TripleBondMaker(const Settings& settings, Skeleton& s);

        typedef std::tuple<int, Edge, Edge> Result;

        Result operator()(const std::tuple<Edge, Edge, Edge>& edges);

        virtual ~TripleBondMaker();

    private:
        TripleBondMaker(const TripleBondMaker&);

        Edge first, second, third;
        Edge empty;
        Vertex fb, fe, sb, se, tb, te;

        Result _validateVertices();

        Skeleton& _s;
        Graph& _g;
        double _avgBondLength;

        const Settings& vars;
    };
}
