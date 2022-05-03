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

#include "label_combiner.h"

#include <algorithm>
#include <cfloat>
#include <vector>

#include "algebra.h"
#include "character_recognizer.h"
#include "image_draw_utils.h"
#include "image_utils.h"
#include "log_ext.h"
#include "output.h"
#include "rng_builder.h"
#include "segment_tools.h"
#include "segments_graph.h"

using namespace imago;

LabelCombiner::LabelCombiner(Settings& vars, SegmentDeque& symbols_layer, SegmentDeque& other_layer, const CharacterRecognizer& cr)
    : _symbols_layer(symbols_layer), _cr(cr), _graphic_layer(other_layer)

{
    if (vars.dynamic.CapitalHeight > 0.0)
    {
        _labels.clear();
        _locateLabels(vars);
        for (Label& l : _labels)
        {
            fillLabelInfo(vars, l, _cr);
        }
    }
}

void LabelCombiner::extractLabels(std::deque<Label>& labels)
{
    labels.assign(_labels.begin(), _labels.end());
}

using namespace segments_graph;

size_t Dfs(SegmentsGraph& g, SegmentsGraph::vertex_descriptor v, std::vector<int>& comps, size_t curr)
{
    size_t index = g.getVertexIndex(v);
    if (comps[index] != -1)
        return 0;
    comps[index] = (int)curr;
    for (auto adj_iter = g.adjacencyBegin(v), end = g.adjacencyEnd(v); adj_iter != end; ++adj_iter)
        Dfs(g, *adj_iter, comps, curr);
    return 1;
}

size_t connected_components(SegmentsGraph& g, std::vector<int>& comps)
{
    size_t cc = 0;
    for (auto& v : comps)
        v = -1;
    size_t curr = 0;
    for (auto iter = g.vertexBegin(), end = g.vertexEnd(); iter != end; ++iter)
    {
        cc += Dfs(g, *iter, comps, cc);
    }
    return cc;
}

void LabelCombiner::_locateLabels(const Settings& vars)
{
    logEnterFunction();

    using namespace segments_graph;

    SegmentsGraph seg_graph;
    add_segment_range(_symbols_layer.begin(), _symbols_layer.end(), seg_graph);

    RNGBuilder::build(seg_graph);

    SegmentsGraph::edge_iterator ei, ei_end, next;
    ei = seg_graph.edgeBegin();
    ei_end = seg_graph.edgeEnd();

    double distance_constraint = vars.dynamic.CapitalHeight * vars.lcomb.MaximalDistanceFactor;
    double distance_constraint_y = vars.dynamic.CapitalHeight * vars.lcomb.MaximalYDistanceFactor;

    for (next = ei; ei != ei_end; ei = next)
    {
        Segment* s_b = seg_graph.getVertexSegment(ei.get_source());
        Segment* s_e = seg_graph.getVertexSegment(ei.get_target());

        RecognitionDistance pr_b = _cr.recognize(vars, *s_b);
        RecognitionDistance pr_e = _cr.recognize(vars, *s_e);

        ++next;
        if (SegmentTools::getRealDistance(*s_b, *s_e, SegmentTools::dtEuclidian) < distance_constraint &&
            SegmentTools::getRealDistance(*s_b, *s_e, SegmentTools::dtDeltaY) < distance_constraint_y)
        {
            // Special check for "-" and "+" symbols
            if ((pr_b.getBest() == '-') || (pr_e.getBest() == '-') || (pr_b.getBest() == '+') || (pr_e.getBest() == '+'))
                continue;

            // Check diagonal case
            getLogExt().append("DeltaX", absolute(s_b->getX() - s_e->getX()));
            getLogExt().append("DeltaY", absolute(s_b->getY() - s_e->getY()));
            getLogExt().append("Y Overlap (1)", (s_b->getY() + SegmentTools::getRealHeight(*s_b) - s_e->getY()));
            getLogExt().append("Y Overlap (2)", (s_e->getY() + SegmentTools::getRealHeight(*s_e) - s_b->getY()));

            if (absolute(s_b->getX() - s_e->getX()) > vars.dynamic.CapitalHeight / 3 && absolute(s_b->getY() - s_e->getY()) > vars.dynamic.CapitalHeight)
            {
                seg_graph.removeEdge(*ei);
            }
            else if (((s_b->getY() < s_e->getY()) && ((s_b->getY() + SegmentTools::getRealHeight(*s_b) - s_e->getY()) < vars.dynamic.CapitalHeight * 0.1)) ||
                     ((s_b->getY() > s_e->getY()) && ((s_e->getY() + SegmentTools::getRealHeight(*s_e) - s_b->getY()) < vars.dynamic.CapitalHeight * 0.1)))
            {
                seg_graph.removeEdge(*ei);
            }
            else
                continue;
        }
        else
            seg_graph.removeEdge(*ei);
    }

    getLogExt().appendGraph(vars, "seg_graph", seg_graph);

    std::vector<int> _components(seg_graph.vertexCount());
    size_t cc = connected_components(seg_graph, _components);
    std::vector<std::vector<int>> components(cc);
    for (size_t i = 0; i < _components.size(); i++)
        components[_components[i]].push_back((int)i);

    size_t n = seg_graph.vertexCount();
    std::vector<typename SegmentsGraph::vertex_descriptor> ind2vert(n);
    size_t i = 0;
    for (auto begin = seg_graph.vertexBegin(), end = seg_graph.vertexEnd(); begin != end; begin = end)
        for (SegmentsGraph::vertex_descriptor v; begin != end ? (v = *begin, true) : false; ++begin, ++i)
            ind2vert[i] = v;
    for (size_t i = 0; i < ind2vert.size(); ++i)
        seg_graph.setVertexIndex(ind2vert[i], i);

    _labels.resize(cc);
    for (size_t i = 0; i < components.size(); i++)
    {
        getLogExt().append("Component", i);
        getLogExt().appendVector("Subcomponents", components[i]);
        _labels[i].symbols.resize(components[i].size());
        for (int j = 0; j < (int)components[i].size(); j++)
        {
            _labels[i].symbols[j] = seg_graph.getVertexSegment(ind2vert[components[i][j]]);
        }
    }
}

void LabelCombiner::fillLabelInfo(const Settings& vars, Label& l, const CharacterRecognizer& cr)
{
    logEnterFunction();

    int min_x = INT_MAX, min_y = INT_MAX, max_x = 0, max_y = 0;

    int capital_height = (int)vars.dynamic.CapitalHeight;

    if (l.symbols.size())
    {
        int sum = 0;
        int min_end = INT_MAX;
        int max_begin = 0;
        int max_end = 0;
        bool multiline = false;
        for (size_t u = 0; u < l.symbols.size(); u++)
        {
            int y_begin = l.symbols[u]->getY();
            int y_end = y_begin + l.symbols[u]->getHeight();
            int x_begin = l.symbols[u]->getX();
            int x_end = x_begin + l.symbols[u]->getWidth();

            sum += y_end;

            min_x = std::min(min_x, x_begin);
            min_y = std::min(min_y, y_begin);
            max_x = std::max(max_x, x_end);
            max_y = std::max(max_y, y_end);

            if ((y_begin > max_begin) && (l.symbols[u]->getHeight() > capital_height * 0.8))
                max_begin = y_begin;

            if ((y_begin >= min_end) && (l.symbols[u]->getHeight() > capital_height * 0.8))
                multiline = true;

            if ((y_end <= max_begin) && (l.symbols[u]->getHeight() > capital_height * 0.8))
                multiline = true;

            if ((l.symbols[u]->getHeight() > capital_height * 0.9) && (l.symbols[u]->getHeight() < capital_height * 1.1))
            {
                RecognitionDistance pr = cr.recognize(vars, *l.symbols[u]);
                char ch = pr.getBest();
                if ((ch == '%') || (ch == '^') || (ch == '$') || (ch == '='))
                {
                    getLogExt().append("Symb with subscript found %s , ignore it for baseline calc.", ch);
                    continue;
                }

                if (y_end > max_end)
                    max_end = y_end;
            }
        }
        if (multiline)
        {
            l.baseline_y = sum / (int)l.symbols.size();
        }
        else if (max_end > 0)
        {
            l.baseline_y = max_end;
        }
        else
        {
            l.baseline_y = -1;
        }
        l.multiline = multiline;
    }
    else
    {
        l.baseline_y = -1;
        l.multiline = false;
    }

    l.rect = Rectangle(min_x, min_y, max_x, max_y, 1);

    std::sort(l.symbols.begin(), l.symbols.end(), segmentsCompareX);
}

bool LabelCombiner::segmentsComparator(const Segment* const& a, const Segment* const& b)
{
    if (a->getY() < b->getY())
        return true;
    else if (a->getY() == b->getY())
    {
        if (a->getX() < b->getX())
            return true;
    }

    return false;
}

bool LabelCombiner::segmentsCompareX(const Segment* const& a, const Segment* const& b)
{
    if (a->getX() < b->getX())
        return true;

    return false;
}

LabelCombiner::~LabelCombiner()
{
}
