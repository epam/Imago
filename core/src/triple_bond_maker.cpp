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

#include "triple_bond_maker.h"

#include <set>

#include "algebra.h"
#include "settings.h"

using namespace imago;

TripleBondMaker::TripleBondMaker(const Settings& settings, Skeleton& s) : _s(s), _g(_s.getGraph()), vars(settings)
{
    _avgBondLength = _s.bondLength();
}

TripleBondMaker::~TripleBondMaker()
{
}

TripleBondMaker::Result TripleBondMaker::_validateVertices()
{
    std::set<Vertex> vertices;
    Graph::vertex_iterator vi, vi_end;
    vi = _g.vertexBegin();
    vi_end = _g.vertexEnd();
    vertices.insert(vi, vi_end);
    std::set<Vertex>::iterator it_end = vertices.end();
    bool firstValid, secondValid, thirdValid;
    firstValid = secondValid = thirdValid = true;
    if (vertices.find(fb) == it_end || vertices.find(fe) == it_end)
        firstValid = false;

    if (vertices.find(sb) == it_end || vertices.find(se) == it_end)
        secondValid = false;

    if (vertices.find(tb) == it_end || vertices.find(te) == it_end)
        thirdValid = false;

    if (firstValid && secondValid && thirdValid)
        return std::make_tuple(3, empty, empty);
    else if (firstValid && secondValid)
        return std::make_tuple(2, first, second);
    else if (firstValid && thirdValid)
        return std::make_tuple(2, first, third);
    else if (thirdValid && secondValid)
        return std::make_tuple(2, second, third);
    else if (firstValid)
        return std::make_tuple(1, first, empty);
    else if (secondValid)
        return std::make_tuple(1, second, empty);
    else if (thirdValid)
        return std::make_tuple(1, third, empty);
    else
        return std::make_tuple(0, empty, empty);
}

TripleBondMaker::Result TripleBondMaker::operator()(const std::tuple<Edge, Edge, Edge>& edges)
{
    std::set<Vertex> toRemove;
    std::tie(first, second, third) = edges;

    fb = first.m_source, fe = first.m_target;
    sb = second.m_source, se = second.m_target;
    tb = third.m_source, te = third.m_target;

    Result ret = _validateVertices();

    if (std::get<0>(ret) != 3)
        return ret;

    // Validating edges
    if (!_g.getEdge(fb, fe).second || !_g.getEdge(sb, se).second || !_g.getEdge(tb, te).second)
        return std::make_tuple(0, empty, empty);

    Vec2d fb_pos = _g.getVertexPosition(fb), fe_pos = _g.getVertexPosition(fe), sb_pos = _g.getVertexPosition(sb), se_pos = _g.getVertexPosition(se),
          tb_pos = _g.getVertexPosition(tb), te_pos = _g.getVertexPosition(te);

    if (Vec2d::distance(fb_pos, sb_pos) > Vec2d::distance(fb_pos, se_pos))
    {
        std::swap(sb, se);
        std::swap(sb_pos, se_pos);
    }
    if (Vec2d::distance(sb_pos, tb_pos) > Vec2d::distance(sb_pos, te_pos))
    {
        std::swap(tb, te);
        std::swap(tb_pos, te_pos);
    }

    Vec2d p1, p2;
    double l1, l2;

    std::tie(p1, p2) = Algebra::segmentProjection(sb_pos, se_pos, fb_pos, fe_pos);

    l1 = Vec2d::distance(fb_pos, p1);
    l2 = Vec2d::distance(p2, fe_pos);

    bool left = l1 > vars.mbond.TripleLeftLengthTresh * _avgBondLength;
    bool right = l2 > vars.mbond.TripleRightLengthTresh * _avgBondLength;

    _g.removeEdge(first);
    _g.removeEdge(second);
    _g.removeEdge(third);

    if (left || right)
    {
        toRemove.insert(sb);
        toRemove.insert(se);
        toRemove.insert(tb);
        toRemove.insert(te);
    }

    if (left && right)
    {
        Vertex v1 = _s.addVertex(p1), v2 = _s.addVertex(p2);

        Edge e1 = _s.addBond(fb, v1), e2 = _s.addBond(v1, v2, BT_TRIPLE), e3 = _s.addBond(v2, fe);

        ret = std::make_tuple(2, e1, e3);
    }
    else if (left)
    {
        Vertex v = _s.addVertex(p1);

        Edge e1 = _s.addBond(fb, v, BT_SINGLE), e2 = _s.addBond(v, fe, BT_TRIPLE);

        ret = std::make_tuple(1, e1, empty);
    }
    else if (right)
    {
        Vertex v = _s.addVertex(p2);

        Edge e1 = _s.addBond(fb, v, BT_TRIPLE), e2 = _s.addBond(v, fe, BT_SINGLE);
        ret = std::make_tuple(1, e2, empty);
    }
    else
    {
        p1.set((fb_pos.x + sb_pos.x + tb_pos.x) / 3, (fb_pos.y + sb_pos.y + tb_pos.y) / 3);
        p2.set((fe_pos.x + se_pos.x + te_pos.x) / 3, (fe_pos.y + se_pos.y + te_pos.y) / 3);

        Vertex v1 = _s.addVertex(p1), v2 = _s.addVertex(p2);
        Vertex *mbegin, *mend;
        double dist;

        if ((l1 = Vec2d::distance(p1, fb_pos)) < (l2 = Vec2d::distance(p1, sb_pos)))
            mbegin = &fb, mend = &fe, dist = l1;
        else
            mbegin = &sb, mend = &se, dist = l2;

        if (Vec2d::distance(p1, tb_pos) < dist)
            mbegin = &tb, mend = &te;

        _s._reconnectBonds(*mbegin, v1);
        _s._reconnectBonds(*mend, v2);

        toRemove.insert(fb);
        toRemove.insert(fe);
        toRemove.insert(sb);
        toRemove.insert(se);
        toRemove.insert(tb);
        toRemove.insert(te);

        Edge e = _s.addBond(v1, v2, BT_TRIPLE);

        ret = std::make_tuple(0, empty, empty);
    }

    for (Vertex v : toRemove)
        if (_g.getDegree(v) == 0)
            _g.removeVertex(v);

    return ret;
}
