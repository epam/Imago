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

#include <deque>
#include <tuple>

#include "beast.h"
#include "comdef.h"
#include "settings.h"
#include "stl_fwd.h"
#include "vec2d.h"

namespace imago
{
    enum BondType
    {
        BT_SINGLE = 1,
        BT_DOUBLE,
        BT_TRIPLE,
        BT_AROMATIC,
        BT_SINGLE_UP,
        BT_SINGLE_DOWN,
        BT_ARROW,
        BT_WEDGE,
        BT_SINGLE_UP_C, // single up bonds that need to be checked
        BT_UNKNOWN
    };

    struct Bond
    {
        double length, k;
        BondType type;

        Bond(){};

        Bond(double _length, double _k, BondType _type) : length(_length), k(_k), type(_type){};
    };

    class Skeleton
    {
    public:
        struct VertexData
        {
            // size_t index;
            // Segment* segment;
            Vec2d position;
        };

        struct EdgeData
        {
            Bond bond;
        };

        class SkeletonGraph : public beast::Graph<VertexData, EdgeData>
        {
        public:
            typedef beast::Graph<VertexData, EdgeData> base_type;

            SkeletonGraph()
            {
            }
            Vec2d getVertexPosition(vertex_descriptor v) const
            {
                return _vertex_indices[v.id]->data.position;
            }
            void setVertexPosition(vertex_descriptor v, const Vec2d& val)
            {
                _vertex_indices[v.id]->data.position = val;
            }
            Bond getEdgeBond(edge_descriptor e) const
            {
                return _edge_indices[e.id]->data.bond;
            }
            void setEdgeBond(edge_descriptor e, Bond& val)
            {
                _edge_indices[e.id]->data.bond = val;
            }
        };

        typedef SkeletonGraph::base_type::vertex_descriptor Vertex;
        typedef SkeletonGraph::base_type::edge_descriptor Edge;

        Skeleton();

        Vertex addVertex(const Vec2d& pos);

        Edge addBond(Vertex& v1, Vertex& v2, BondType type = BT_SINGLE, bool throw_if_error = false);
        Edge addBond(const Vec2d& begin, const Vec2d& end, BondType type = BT_SINGLE, bool throw_if_error = false);

        void removeBond(Vertex& v1, Vertex& v2);
        void removeBond(Edge& e);

        Vertex getBondBegin(const Edge& e) const;
        Vertex getBondEnd(const Edge& e) const;

        int getVerticesCount() const;
        int getEdgesCount() const;
        Vec2d getVertexPos(const Vertex& v1) const;
        BondType getBondType(const Edge& e) const;
        Bond getBondInfo(const Edge& e) const;
        void setBondType(Edge e, BondType t);

        void reverseEdge(const Edge& e);

        void setInitialAvgBondLength(Settings& vars, double avg_length);
        void recalcAvgBondLength();
        double bondLength()
        {
            return _avg_bond_length;
        }

        void modifyGraph(Settings& vars);

        void clear();

        operator SkeletonGraph()
        {
            return _g;
        }
        SkeletonGraph& getGraph()
        {
            return _g;
        }
        ~Skeleton();

        int getWarningsCount() const
        {
            return _warnings;
        }
        int getDissolvingsCount() const
        {
            return _dissolvings;
        }

        void calcShortBondsPenalty(const Settings& vars);
        void calcCloseVerticiesPenalty(const Settings& vars);

    protected:
        SkeletonGraph _g;
        int _warnings, _dissolvings;

    private:
        friend class DoubleBondMaker;
        friend class TripleBondMaker;
        friend class MultipleBondChecker;

        void _reconnectBonds(Vertex from, Vertex to);
        bool _checkMidBonds(Vertex from, Vertex to);
        void _reconnectBondsRWT(Vertex from, Vertex to, BondType new_t);
        void _repairBroken(const Settings& vars);
        void _findMultiple(const Settings& vars);

    public:
        void _joinVertices(double eps, bool parallel_check = false);
        bool _dissolveShortEdges(const Settings& vars, double coeff, const bool has2nb, SegmentDeque& layer_symbols);
        bool _dissolveIntermediateVertices(const Settings& vars);
        void deleteBadTriangles(double eps);

    private:
        double _avgEdgeLendth(const Vertex& v, int& nnei);
        typedef std::tuple<bool, Edge, Edge> MakersReturn;
        // MakersReturn _makeDouble( std::pair<Edge, Edge> edges );
        MakersReturn _makeTriple(std::tuple<Edge, Edge, Edge> edges);
        bool _isParallel(const Edge& first, const Edge& second) const;
        bool _isEqualDirection(const Edge& first, const Edge& second) const;
        bool _isEqualDirection(const Vertex& b1, const Vertex& e1, const Vertex& b2, const Vertex& e2) const;
        bool _isSegmentIntersectedByEdge(const Settings& vars, Vec2d& b, Vec2d& e, std::deque<Edge> edges);
        void _processInlineDoubleBond(const Settings& vars);
        bool _checkParallelEdges(const Vertex& v1, const Vertex& v2);

        void _connectBridgedBonds(const Settings& vars);

        double _avg_bond_length, _parLinesEps, _addVertexEps, _min_bond_length, _min_bond_h2nb_length;
        std::vector<Vec2d> _vertices_big_degree;

        Skeleton(const Skeleton& g);
    };
}
