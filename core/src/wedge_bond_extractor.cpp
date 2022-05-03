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

#include "wedge_bond_extractor.h"

#include <deque>
#include <vector>

#include "algebra.h"
#include "comdef.h"
#include "image.h"
#include "image_draw_utils.h"
#include "image_utils.h"
#include "log_ext.h"
#include "molecule.h"
#include "segment.h"
#include "settings.h"
#include "skeleton.h"
#include "stat_utils.h"
#include "vec2d.h"

using namespace imago;

void edge_summary(imago::Skeleton& g)
{
    if (getLogExt().loggingEnabled())
    {
        std::map<std::string, int> bondtypes;
        Skeleton::SkeletonGraph graph = g.getGraph();
        for (Skeleton::SkeletonGraph::edge_iterator begin = graph.edgeBegin(), end = graph.edgeEnd(); begin != end; begin = end)
            for (Skeleton::SkeletonGraph::edge_descriptor b; begin != end ? (b = *begin, true) : false; ++begin)
            {
                BondType bt = g.getBondType(b);
                std::string bts;
                switch (bt)
                {
                case BT_SINGLE:
                    bts = "SINGLE";
                    break;
                case BT_DOUBLE:
                    bts = "DOUBLE";
                    break;
                case BT_TRIPLE:
                    bts = "TRIPLE";
                    break;
                case BT_AROMATIC:
                    bts = "AROMATIC";
                    break;
                case BT_SINGLE_UP:
                    bts = "SINGLE_UP";
                    break;
                case BT_SINGLE_DOWN:
                    bts = "SINGLE_DOWN";
                    break;
                case BT_ARROW:
                    bts = "ARROW";
                    break;
                case BT_WEDGE:
                    bts = "WEDGE";
                    break;
                case BT_SINGLE_UP_C:
                    bts = "SINGLE_UP_C";
                    break;
                case BT_UNKNOWN:
                    bts = "UNKNOWN";
                    break;
                }
                bondtypes[bts]++;
            }
        getLogExt().appendMap("bond types", bondtypes);
    }
}

WedgeBondExtractor::WedgeBondExtractor(SegmentDeque& segs, Image& img) : _segs(segs), _img(img)
{
}

struct PointsComparator : public std::binary_function<WedgeBondExtractor::SegCenter, WedgeBondExtractor::SegCenter, bool>
{
    int PointsCompareDist;

    PointsComparator(int dist)
    {
        PointsCompareDist = dist;
    }

    inline bool operator()(const WedgeBondExtractor::SegCenter& c, const WedgeBondExtractor::SegCenter& d)
    {
        Vec2d a = c.center, b = d.center;

        bool res;

        if (a.x > b.x)
            res = true;
        if (a.x < b.x)
            res = false;

        if (fabs(a.x - b.x) <= PointsCompareDist)
        {
            if (a.y > b.y)
                res = true;
            if (a.y < b.y)
                res = false;
            if (fabs(a.y - b.y) <= PointsCompareDist)
                res = false;
        }

        return res;
    }
};

void WedgeBondExtractor::_fitSingleDownBorders(Vec2d& p1, Vec2d& p2, Vec2d& v1, Vec2d& v2)
{
    _intersectionContext ic;

    ic.img = &_img;

    ic.white_found = false;
    ic.intersection_point.x = -1;
    ic.intersection_point.y = -1;
    ImageDrawUtils::putLineSegment(p1, v1, 255, &ic, _intersectionFinderPlotCallBack);

    if (ic.intersection_point.x != -1 && ic.intersection_point.y != -1)
        p1 = ic.intersection_point;

    ic.white_found = false;
    ic.intersection_point.x = -1;
    ic.intersection_point.y = -1;
    ImageDrawUtils::putLineSegment(p2, v2, 255, &ic, _intersectionFinderPlotCallBack);

    if (ic.intersection_point.x != -1 && ic.intersection_point.y != -1)
        p2 = ic.intersection_point;
}

int WedgeBondExtractor::singleDownFetchOld(const Settings& vars, Skeleton& g, SegmentDeque& sdb_segs)
{
    int sdb_count = 0;
    double eps = vars.wbe.SingleDownEps, angle;

    std::vector<SegCenter> segs_info;
    std::vector<Segment*> to_delete_segs;

    for (SegmentDeque::iterator it = _segs.begin(); it != _segs.end(); ++it)
    {
        if (ImageUtils::testSlashLine(vars, **it, &angle, eps))
        {
            Vec2d a = (*it)->getCenter();
            segs_info.push_back(SegCenter(it, a, angle));
        }
    }

    if (segs_info.empty())
        return 0;

    for (size_t i = 0; i < segs_info.size(); i++)
    {
        segs_info[i].seginfo_index = i;
    }

    int w = _img.getWidth();
    int h = _img.getHeight();
    Image img(w, h);
    img.fillWhite();

    for (size_t i = 0; i < segs_info.size(); i++)
        for (size_t j = i + 1; j < segs_info.size(); j++)
        {
            if (segs_info[i].used && segs_info[j].used && fabs(segs_info[i].angle - segs_info[j].angle) < vars.wbe.SomeTresh)
            {
                Vec2d p1 = segs_info[i].center, p2 = segs_info[j].center;

                std::vector<SegCenter> cur_points;

                cur_points.push_back(segs_info[i]);
                cur_points.push_back(segs_info[j]);

                for (size_t k = 0; k < segs_info.size(); k++)
                {
                    Vec2d p3;

                    if (k != i && k != j && segs_info[k].used)
                    {
                        p3 = segs_info[k].center;

                        if (absolute(p1.x - p2.x) <= vars.wbe.SingleDownCompareDist)
                        {
                            if (absolute(p1.x - p3.x) <= vars.wbe.SingleDownCompareDist || absolute(p3.x - p2.x) <= vars.wbe.SingleDownCompareDist)
                            {
                                cur_points.push_back(segs_info[k]);
                                continue;
                            }
                        }

                        if (absolute(p1.y - p2.y) <= vars.wbe.SingleDownCompareDist)
                        {
                            if (absolute(p1.y - p3.y) <= vars.wbe.SingleDownCompareDist || absolute(p3.y - p2.y) <= vars.wbe.SingleDownCompareDist)
                            {
                                cur_points.push_back(segs_info[k]);
                                continue;
                            }
                        }

                        double ch1 = (p1.x - p3.x) * (p2.y - p1.y);
                        double ch2 = (p1.x - p2.x) * (p3.y - p1.y);

                        if (absolute(ch1 - ch2) <= vars.wbe.SingleDownAngleMax)
                            cur_points.push_back(segs_info[k]);
                    }
                }

                std::sort(cur_points.begin(), cur_points.end(), PointsComparator(vars.wbe.PointsCompareDist));

                if ((int)cur_points.size() >= vars.wbe.MinimalSingleDownSegsCount)
                {
                    std::vector<IntPair> same_dist_pairs;
                    DoubleVector distances(cur_points.size() - 1);

                    for (size_t k = 0; k < cur_points.size() - 1; k++)
                        distances[k] = Vec2d::distance(cur_points[k + 1].center, cur_points[k].center);

                    for (size_t k = 0; k < distances.size();)
                    {
                        size_t l = k + 1;
                        IntPair p;

                        for (; l != (int)distances.size(); l++)
                        {
                            if (fabs(distances[l - 1] - distances[l]) > vars.wbe.SingleDownDistancesMax)
                                break;
                        }

                        p.first = (int)k;
                        p.second = (int)l;

                        same_dist_pairs.push_back(p);

                        k += l - k;
                    }

                    for (size_t k = 0; k < same_dist_pairs.size(); k++)
                    {
                        IntPair p = same_dist_pairs[k];

                        if (p.second - p.first > 1)
                        {
                            double ave_dist = 0;

                            for (int l = p.first; l < p.second; l++)
                            {
                                ave_dist += distances[l];
                            }

                            ave_dist /= p.second - p.first;

                            if (ave_dist > vars.wbe.SingleDownLengthMax)
                                continue;

                            if (!segs_info[cur_points[p.first].seginfo_index].used || !segs_info[cur_points[p.second].seginfo_index].used)
                                continue;

                            Vec2d p1 = cur_points[p.first].center;
                            Vec2d p2 = cur_points[p.second].center;

                            getLogExt().append("Point 1 x", p1.x);
                            getLogExt().append("Point 1 y", p1.y);
                            getLogExt().append("Point 2 x", p2.x);
                            getLogExt().append("Point 2 y", p2.y);

                            double length = Vec2d::distance(p1, p2);

                            Vec2d orient;
                            orient.diff(p2, p1);
                            orient = orient.getNormalized();

                            orient.scale(length);

                            Vec2d v1 = p1, v2 = p2;

                            v1.diff(v1, orient);
                            v2.sum(v2, orient);

                            //                     _fitSingleDownBorders(p1, p2, v1, v2);
                            g.addBond(p2, p1, BT_SINGLE_DOWN);

                            getLogExt().append("Bond from x", p2.x);
                            getLogExt().append("Bond from y", p2.y);
                            getLogExt().append("Bond to x", p1.x);
                            getLogExt().append("Bond to y", p1.y);

                            sdb_count++;

                            img.fillWhite();

                            for (int l = p.first; l <= p.second; l++)
                            {
                                // mark elements to delete from deque
                                to_delete_segs.push_back(*cur_points[l].seg_iterator);
                                segs_info[cur_points[l].seginfo_index].used = false;

                                ImageUtils::putSegment(img, *(*cur_points[l].seg_iterator), true);
                            }
                            getLogExt().appendImage("Single Down Bond added", img);
                        }
                    }
                }
                cur_points.clear();
            }
        }

    // delete elements from queue (note: iterators invalidation after erase)
    for (SegmentDeque::iterator it = _segs.begin(); it != _segs.end();)
    {
        std::vector<Segment*>::iterator res = std::find(to_delete_segs.begin(), to_delete_segs.end(), *it);

        if (res != to_delete_segs.end())
        {
            Segment* s = new Segment(*(*it));
            sdb_segs.push_back(s);

            delete *it;
            it = _segs.erase(it);
        }
        else
            ++it;
    }

    g.recalcAvgBondLength();

    Skeleton::SkeletonGraph graph = g.getGraph();

    return sdb_count;
}

int WedgeBondExtractor::singleDownFetch(const Settings& vars, Skeleton& g, SegmentDeque& sdb_segs, double bond_len)
{

    std::vector<SegCenter> segs_info;
    std::vector<Segment*> to_delete_segs;

    int sdb_count = 0;

    bool use_bondlen = true;
    double calculated_bond_length = 0, thickness = 0;
    if (use_bondlen)
        calculated_bond_length = bond_len;
    else
        thickness = ImageUtils::estimateLineThickness(_img, 1);

    for (SegmentDeque::iterator it = _segs.begin(); it != _segs.end(); ++it)
    {
        if (ImageUtils::testSmall(**it, use_bondlen ? calculated_bond_length : 30 * thickness))
        {
            Vec2d a = (*it)->getCenter();
            segs_info.emplace_back(it, a, 0);
        }
    }

    /*std::vector<int> w(0), h(0);
    for (int i = 0; i < segs_info.size(); i++) {
        w.push_back((**segs_info[i].seg_iterator).cols);
        h.push_back((**segs_info[i].seg_iterator).rows);
    }
    getLogExt().appendVector("Highs:", h);
    getLogExt().appendVector("Widths:", w);*/

    std::vector<SegCenter> group;
    std::vector<bool> take(segs_info.size(), false);

    Image img1(_img.cols, _img.rows);
    img1.fillWhite();
    Image img2(_img.cols, _img.rows);
    img2.fillWhite();
    Image img3(_img.cols, _img.rows);
    img3.fillWhite();

    double max_dist = use_bondlen ? calculated_bond_length / 3 : thickness * 10;
    double max_dist_sqr = max_dist * max_dist;

    for (int i = 0; i < segs_info.size(); i++)
        if (!take[i])
        {

            group.clear();

            group.push_back(segs_info[i]);
            take[i] = true;
            for (int j = 0; j < group.size(); j++)
                for (int t = 0; t < segs_info.size(); t++)
                    if (!take[t] && Vec2d::distance(group[j].center, segs_info[t].center) < max_dist)
                    {
                        group.push_back(segs_info[t]);
                        take[t] = true;
                    }

            std::vector<bool> removed(group.size(), false);

            // printf("!!\n");
            // for (auto s : group) printf("(%.1f, %.1f) ", s.center.x, s.center.y);
            // printf("\n");
            while (true)
            {
                int max_line_start = -1;
                int max_line_end = -1;

                std::vector<int> on_line_current(0);
                std::vector<int> on_line(0);
                for (int start = 0; start < group.size(); start++)
                    if (!removed[start])
                        for (int end = start + 1; end < group.size(); end++)
                            if (!removed[end])
                            {
                                double dist = Vec2d::distance(group[start].center, group[end].center);
                                on_line_current.clear();

                                Vec2d orient;
                                orient.diff(group[end].center, group[start].center);
                                orient = orient.getNormalized();

                                for (int j = 0; j < group.size(); j++)
                                    if (!removed[j])
                                    {
                                        Segment& current_seg = **group[j].seg_iterator;
                                        bool has_pos = false;
                                        bool has_neg = false;
                                        Vec2d vec;
                                        vec.diff(Vec2d(current_seg.getX(), current_seg.getY()), group[start].center);
                                        double base_cross = Vec2d::cross(orient, vec);
                                        for (int x = 0; x < current_seg.getWidth(); x++)
                                            for (int y = 0; y < current_seg.getHeight(); y++)
                                                if (current_seg.isFilled(x, y))
                                                {
                                                    double cross = base_cross + Vec2d::cross(orient, Vec2d(x, y));
                                                    has_pos |= cross > 0;
                                                    has_neg |= cross < 0;
                                                }

                                        if (has_neg && has_pos)
                                            on_line_current.push_back(j);
                                    }

                                if (on_line.size() < on_line_current.size())
                                {
                                    max_line_start = start;
                                    max_line_end = end;
                                    on_line = on_line_current;
                                }
                            }

                if (max_line_start < 0)
                    break;
                // printf(" %d", on_line.size());
                if (on_line.size() > 2)
                {

                    bool actually_on_line = true;
                    int len = on_line.size();

                    for (int j = 0; j < len; j++)
                        ImageUtils::putSegment(img1, **group[on_line[j]].seg_iterator);

                    Vec2d orient;
                    orient.diff(group[max_line_end].center, group[max_line_start].center);
                    orient = orient.getNormalized();
                    std::vector<double> dist_to_start(len);
                    Vec2d vec;
                    for (int j = 0; j < len; j++)
                    {
                        vec.diff(group[on_line[j]].center, group[max_line_start].center);
                        dist_to_start[j] = Vec2d::dot(orient, vec);
                    }

                    // sorting segments
                    for (int a = 0; a < len; a++)
                        for (int b = 0; b < len - 1; b++)
                            if (dist_to_start[b] > dist_to_start[b + 1])
                            {
                                std::swap(dist_to_start[b], dist_to_start[b + 1]);
                                std::swap(on_line[b], on_line[b + 1]);
                            }

                    max_line_start = on_line[0];
                    max_line_end = on_line[len - 1];
                    orient.diff(group[max_line_end].center, group[max_line_start].center);
                    orient = orient.getNormalized();

                    /*Vec2i p1(group[max_line_end].center.x, group[max_line_end].center.y);
                    Vec2i p2(group[max_line_start].center.x, group[max_line_start].center.y);

                    ImageDrawUtils::putLineSegment(img1, p1, p2, 0);*/

                    std::vector<double> max_dot(len, -1e9);
                    std::vector<double> min_dot(len, 1e9);
                    std::vector<double> max_cross(len, -1e9);
                    std::vector<double> min_cross(len, 1e9);

                    for (int j = 0; j < len; j++)
                    {
                        Segment& current_seg = **group[on_line[j]].seg_iterator;
                        vec.diff(Vec2d(current_seg.getX(), current_seg.getY()), group[max_line_start].center);
                        double base_dot = Vec2d::dot(orient, vec);
                        double base_cross = Vec2d::cross(orient, vec);
                        std::vector<int> counts({current_seg.getWidth(), current_seg.getHeight(), current_seg.getHeight() * current_seg.getWidth()});
                        int cnt = 0;
                        for (int x = 0; x < current_seg.getWidth(); x++)
                            for (int y = 0; y < current_seg.getHeight(); y++)
                                if (current_seg.isFilled(x, y))
                                {
                                    cnt++;
                                    double dot = base_dot + Vec2d::dot(orient, Vec2d(x, y));
                                    max_dot[j] = std::max(max_dot[j], dot);
                                    min_dot[j] = std::min(min_dot[j], dot);
                                    double cross = base_cross + Vec2d::cross(orient, Vec2d(x, y));
                                    max_cross[j] = std::max(max_cross[j], cross);
                                    min_cross[j] = std::min(min_cross[j], cross);
                                }
                        counts.push_back(cnt);
                        getLogExt().appendVector("Counts", counts);
                    }

                    /*for (int j = 0; j < len; j++) {
                        Vec2d vec1 = orient;
                        Vec2d vec2 = orient;
                        vec1.scale(min_dot[j]);
                        vec2.scale(max_dot[j]);
                        Vec2d orient2 = orient;
                        orient2.rotate(PI / 2);
                        Vec2d add1 = orient2;
                        add1.scale(max_cross[j]);
                        Vec2d add2 = orient2;
                        add2.scale(min_cross[j]);

                        Vec2d A = vec1; A.add(add1); A.add(group[on_line[0]].center);
                        Vec2d B = vec2; B.add(add1); B.add(group[on_line[0]].center);
                        Vec2d C = vec2; C.add(add2); C.add(group[on_line[0]].center);
                        Vec2d D = vec1; D.add(add2); D.add(group[on_line[0]].center);

                        Vec2i p1(A.x, A.y);
                        Vec2i p2(B.x, B.y);
                        Vec2i p3(C.x, C.y);
                        Vec2i p4(D.x, D.y);

                        ImageDrawUtils::putLineSegment(img1, p1, p2, 128);
                        ImageDrawUtils::putLineSegment(img1, p2, p3, 128);
                        ImageDrawUtils::putLineSegment(img1, p3, p4, 128);
                        ImageDrawUtils::putLineSegment(img1, p4, p1, 128);
                    }*/

                    double dash_len = 0;
                    for (int j = 0; j < len; j++)
                        dash_len += (max_cross[j] - min_cross[j]) / std::max(max_dot[j] - min_dot[j], 1.);
                    dash_len /= len;

                    /*std::vector<double> lens(len);
                    for (int j = 0; j < len; j++) lens[j] = (max_cross[j] - min_cross[j]) / std::max(max_dot[j] - min_dot[j], 1.);
                    getLogExt().appendVector("Dash lengths: ", lens);*/

                    // getLogExt().appendVector(actually_on_line ? "Actually on line" : "Actually not on line", min_scal);
                    // getLogExt().appendVector(actually_on_line ? "Actually on line" : "Actually not on line", max_scal);

                    actually_on_line &= dash_len > 1.5;

                    for (int j = 0; j < len - 1; j++)
                        actually_on_line &= max_dot[j] < min_dot[j + 1];

                    if (actually_on_line)
                    {
                        for (int j = 0; j < len; j++)
                        {
                            ImageUtils::putSegment(img3, **group[on_line[j]].seg_iterator);
                            to_delete_segs.push_back(*group[on_line[j]].seg_iterator);
                        }
                    }

                    if (actually_on_line)
                    {
                        Vec2d p1 = group[on_line[0]].center;
                        Vec2d p2 = group[on_line[len - 1]].center;

                        Vec2d orient;
                        orient.diff(p2, p1);
                        orient.scale(1.0 / (len - 1));
                        p2.add(orient);
                        p1.diff(p1, orient);

                        double orientation = 0;
                        for (int j = 0; j < len; j++)
                            orientation += (-(len - 1) * .5 + j) * (max_cross[j] - min_cross[j]);

                        if (orientation > 0)
                            g.addBond(p1, p2, BT_SINGLE_DOWN);
                        else
                            g.addBond(p2, p1, BT_SINGLE_DOWN);

                        sdb_count += actually_on_line;
                    }
                    // TODO

                    for (int index : on_line)
                        removed[index] = true;
                }
                else
                {
                    break;
                }
            }
            // printf("??\n");
        }

    // Image img(_img.getWidth(), _img.getHeight());
    // img.fillWhite();
    // for (auto s : segs_info) ImageUtils::putSegment(img, **s.seg_iterator);
    getLogExt().appendImage("All small bits:", img1);
    // getLogExt().appendImage("All small bits:", img2);
    getLogExt().appendImage("All small bits:", img3);

    if (segs_info.empty())
        return 0;

    for (SegmentDeque::iterator it = _segs.begin(); it != _segs.end();)
    {
        std::vector<Segment*>::iterator res = std::find(to_delete_segs.begin(), to_delete_segs.end(), *it);

        if (res != to_delete_segs.end())
        {
            Segment* s = new Segment(*(*it));
            sdb_segs.push_back(s);

            delete *it;
            it = _segs.erase(it);
        }
        else
            ++it;
    }

    return sdb_count;
}

int WedgeBondExtractor::_radiusFinder(const Vec2d& v)
{
    _CircleContext cc;
    cc.img = &_img;
    cc.done = 0;
    int r = 1;

    while (!cc.done)
    {
        r++;
        ImageDrawUtils::putCircle(round(v.x), round(v.y), r, 0, &cc, _radiusFinderPlotCallback);
    }

    return r + 1;
}

bool WedgeBondExtractor::_radiusFinderPlotCallback(int x, int y, int color, void* userdata)
{
    _CircleContext* cc = (_CircleContext*)userdata;
    int w = cc->img->getWidth(), h = cc->img->getHeight();

    if (x >= 0 && y >= 0 && x < w && y < h)
    {
        if (cc->img->getByte(x, y) != 0) // Not black
            cc->done = 1;
    }
    else
        cc->done = 1;

    return true;
}

bool WedgeBondExtractor::_intersectionFinderPlotCallBack(int x, int y, int color, void* userdata)
{
    _intersectionContext* ic = (_intersectionContext*)userdata;
    int w = ic->img->getWidth(), h = ic->img->getHeight();

    if (x >= 0 && y >= 0 && x < w && y < h)
    {
        if (ic->img->getByte(x, y) == 255)
            ic->white_found = true;

        if (ic->img->getByte(x, y) == 0)
        {
            if (ic->white_found)
            {
                if (ic->intersection_point.x == -1 && ic->intersection_point.y == -1)
                {
                    ic->intersection_point.x = x;
                    ic->intersection_point.y = y;
                }
            }
        }
    }

    return true;
}

void WedgeBondExtractor::fixStereoCenters(Molecule& mol)
{
    logEnterFunction();

    Skeleton::SkeletonGraph& graph = mol.getSkeleton();
    const Molecule::ChemMapping& labels = mol.getMappedLabels();
    std::vector<Skeleton::Edge> to_reverse_bonds;
    for (Skeleton::SkeletonGraph::edge_iterator begin = graph.edgeBegin(), end = graph.edgeEnd(); begin != end; begin = end)
        for (Skeleton::SkeletonGraph::edge_descriptor b; begin != end ? (b = *begin, true) : false; ++begin)
        {
            Bond b_bond = graph.getEdgeBond(b);
            BondType type = b_bond.type;

            if (type == BT_SINGLE_DOWN || type == BT_SINGLE_UP_C)
            {
                bool begin_stereo = false, end_stereo = false;
                Skeleton::Vertex v1 = b.m_source, v2 = b.m_target;

                if (_checkStereoCenter(v1, mol))
                    begin_stereo = true;

                if (_checkStereoCenter(v2, mol))
                    end_stereo = true;

                if (!begin_stereo)
                {
                    if (!end_stereo)
                    {
                        mol.setBondType(b, BT_SINGLE);
                        getLogExt().appendText("Reset stereo bond!");
                    }
                    else
                    {
                        to_reverse_bonds.push_back(b);
                        getLogExt().appendText("Revert stereo bond!");
                    }
                }
                else if (type == BT_SINGLE_UP_C)
                    mol.setBondType(b, BT_SINGLE_UP);
            }
        }

    for (Skeleton::Edge e : to_reverse_bonds)
    {
        Bond b_bond = graph.getEdgeBond(e);
        BondType type = b_bond.type;

        if (type == BT_SINGLE_UP_C)
            mol.setBondType(e, BT_SINGLE_UP);

        mol.reverseEdge(e);
    }

    edge_summary(mol);
}

bool WedgeBondExtractor::_checkStereoCenter(Skeleton::Vertex& v, Molecule& mol)
{
    _Configuration conf;
    const Skeleton::SkeletonGraph& graph = mol.getSkeleton();
    const Molecule::ChemMapping& labels = mol.getMappedLabels();

    Molecule::ChemMapping::const_iterator elem = labels.find(v);

    if (elem == labels.end())
    {
        conf.label_first = 'C';
        conf.label_second = 0;
        conf.charge = 0;
    }
    else
    {
        conf.label_first = elem->second->satom.atoms[0].getLabelFirst();
        conf.label_second = elem->second->satom.atoms[0].getLabelSecond();
        conf.charge = elem->second->satom.atoms[0].charge;
    }

    conf.degree = (int)graph.getDegree(v);
    conf.n_double_bonds = 0;

    Skeleton::SkeletonGraph::out_edge_iterator begin, end;

    begin = graph.outEdgeBegin(v);
    end = graph.outEdgeEnd(v);

    for (Skeleton::SkeletonGraph::out_edge_iterator it = begin; it != end; ++it)
    {
        BondType type = graph.getEdgeBond(*it).type;

        if (type == BT_DOUBLE)
            conf.n_double_bonds++;
    }

    static const _Configuration allowed_stereocenters[] = {
        {'C', 0, 0, 3, 0}, {'C', 0, 0, 4, 0}, {'S', 'i', 0, 3, 0}, {'S', 'i', 0, 4, 0}, {'N', 0, 1, 3, 0}, {'N', 0, 1, 4, 0}, {'N', 0, 0, 3, 0},
        {'N', 0, 0, 4, 2}, {'S', 0, 1, 3, 0}, {'S', 0, 0, 3, 1},   {'P', 0, 0, 3, 0},   {'P', 0, 1, 4, 0}, {'P', 0, 0, 4, 1},
    };

    int arr_size = sizeof(allowed_stereocenters) / sizeof(allowed_stereocenters[0]);

    for (int i = 0; i < arr_size; i++)
    {
        if (allowed_stereocenters[i].label_first == conf.label_first && allowed_stereocenters[i].label_second == conf.label_second &&
            allowed_stereocenters[i].charge == conf.charge && allowed_stereocenters[i].degree == conf.degree &&
            allowed_stereocenters[i].n_double_bonds == conf.n_double_bonds)
        {
            return true;
        }
    }

    return false;
}

int WedgeBondExtractor::getVertexValence(Skeleton::Vertex& v, Skeleton& mol)
{
    std::deque<Skeleton::Vertex> neighbors;
    Skeleton::SkeletonGraph::adjacency_iterator b_e, e_e;
    b_e = mol.getGraph().adjacencyBegin(v);
    e_e = mol.getGraph().adjacencyEnd(v);
    neighbors.assign(b_e, e_e);

    int retVal = 0;

    for (size_t i = 0; i < neighbors.size(); i++)
    {
        Skeleton::Edge edge = mol.getGraph().getEdge(neighbors[i], v).first;
        BondType bType = mol.getBondType(edge);
        switch (bType)
        {
        case BT_DOUBLE:
            retVal += 2;
        case BT_TRIPLE:
            retVal += 3;
        default:
            retVal++;
        }
    }
    return retVal;
}

void WedgeBondExtractor::singleUpFetch(const Settings& vars, Skeleton& g)
{
    logEnterFunction();

    int count = 0;

    Skeleton::SkeletonGraph& graph = g.getGraph();

    if (g.getEdgesCount() >= 1)
    {
        Image img;
        img.copy(_img);
        _bond_length = vars.dynamic.AvgBondLength;

        _bfs_state.resize(_img.getWidth() * _img.getHeight());
        IntVector iqm_thick;

        for (Skeleton::SkeletonGraph::vertex_iterator begin = graph.vertexBegin(), end = graph.vertexEnd(); begin != end; begin = end)
            for (Skeleton::SkeletonGraph::vertex_descriptor v; begin != end ? (v = *begin, true) : false; ++begin)
            {
                Vec2d v_vec2d = g.getVertexPos(v);

                int r = _radiusFinder(v_vec2d);
                _thicknesses.insert(std::make_pair(v, r));
                iqm_thick.push_back(r);
            }

        std::sort(iqm_thick.begin(), iqm_thick.end());
        _mean_thickness = StatUtils::interMean(iqm_thick.begin(), iqm_thick.end());

        for (Skeleton::SkeletonGraph::edge_iterator begin = graph.edgeBegin(), end = graph.edgeEnd(); begin != end; begin = end)
            for (Skeleton::SkeletonGraph::edge_descriptor b; begin != end ? (b = *begin, true) : false; ++begin)
            {
                Skeleton::Vertex v1 = b.m_source, v2 = b.m_target;

                BondType bond_type = BT_SINGLE;

                if (_isSingleUp(vars, g, b, bond_type))
                {
                    if (bond_type == BT_WEDGE)
                    {
                        int b_val = getVertexValence(v1, g);
                        int e_val = getVertexValence(v2, g);
                        if (e_val == b_val)
                            continue;
                    }
                    count++;
                    g.setBondType(b, bond_type);
                }
            }

        _thicknesses.clear();
        _bfs_state.clear();
    }

    for (size_t i = 0; i < _bonds_to_reverse.size(); i++)
    {
        g.reverseEdge(_bonds_to_reverse[i]);
    }
    _bonds_to_reverse.clear();

    CurateSingleUpBonds(g);
    edge_summary(g);
    getLogExt().append("Single-up bonds", count);
}

bool WedgeBondExtractor::_isSingleUp(const Settings& vars, Skeleton& g, Skeleton::Edge& e1, BondType& return_type)
{
    logEnterFunction();

    Bond bond = g.getBondInfo(e1);

    if (bond.type != BT_SINGLE)
        return false;

    Vec2d bb = g.getVertexPos(g.getBondBegin(e1));
    Vec2d ee = g.getVertexPos(g.getBondEnd(e1));
    int r1 = _thicknesses[g.getBondBegin(e1)], r2 = _thicknesses[g.getBondEnd(e1)];
    int max_r = r1 > r2 ? r1 : r2;
    int min_r = r1 < r2 ? r1 : r2;

    double coef = vars.wbe.SingleUpDefCoeff;
    if (_bond_length < vars.wbe.SingleUpIncLengthTresh)
        coef = vars.wbe.SingleUpIncCoeff;

    if (Vec2d::distance(bb, ee) < _bond_length * coef)
        return false;
    double interpolation_factor = 0.1;

    Vec2d b(bb), e(ee);
    b.interpolate(bb, ee, interpolation_factor); // vars.wbe.SingleUpInterpolateEps);
    e.interpolate(ee, bb, interpolation_factor); // vars.wbe.SingleUpInterpolateEps);
    b.x = round(b.x);
    b.y = round(b.y);
    e.x = round(e.x);
    e.y = round(e.y);
    Vec2d n;
    n.diff(e, b);
    n = n.getNormalized();
    int size = round(abs(n.x * (e.x - b.x) + n.y * (e.y - b.y)));
    std::vector<int> profile(size);

    int w = _img.getWidth();
    int h = _img.getHeight();
    Image img(w, h);
    img.fillWhite();

    Points2d visited;
    std::deque<Vec2d> queue;

    queue.push_back(b);
    while (!queue.empty())
    {
        Vec2d cur = queue.front();

        queue.pop_front();

        visited.push_back(cur);

        double dp = Vec2d::distance(cur, e);
        dp = sqrt(dp * dp + 1) + vars.wbe.SingleUpMagicAddition;
        for (int i = round(cur.x) - 1; i <= round(cur.x) + 1; i++)
        {
            for (int j = round(cur.y) - 1; j <= round(cur.y) + 1; j++)
            {
                if (i == round(cur.x) && j == round(cur.y))
                    continue;

                if (i < 0 || j < 0 || i >= w || j >= h)
                    continue;

                if (_img.getByte(i, j) != 255 && !_bfs_state[j * w + i])
                {
                    Vec2d v(i, j);
                    double dist = Vec2d::distance(v, e);
                    if (dist <= dp)
                    {
                        queue.push_back(v);
                        _bfs_state[j * w + i] = 1;
                        img.getByte(i, j) = 0;
                        int indx = round(n.x * (i - b.x) + n.y * (j - b.y));
                        if (indx > -1 && indx < (int)profile.size())
                            profile[indx]++;
                    }
                }
            }
        }
    }
    getLogExt().appendVector("profile ", profile);
    getLogExt().appendImage("image profile", img);

    double y_mean = 0, x_mean = 0;
    size_t startProfile = round(vars.wbe.SingleUpInterpolateEps * profile.size());
    size_t endProfile = profile.size() - startProfile;

    size_t psize = endProfile - startProfile; //(profile.size() - 1);

    for (size_t i = startProfile; i < endProfile; i++)
    {

        if (profile[i] == 0)
            psize--;
        else
        {
            x_mean += i;
            y_mean += profile[i];
        }
    }

    if (psize < (int)profile.size() / 4)
        return false;

    y_mean /= psize;
    x_mean /= psize;

    double Sxx = 0, Sxy = 0;
    double max_val = 0;
    double Sydx = 0;
    int Scnt = 0;
    for (size_t i = startProfile; i < (startProfile + psize); i++)
    {
        if (profile[i] != 0)
        {
            double xx = i - x_mean;
            double xy = (profile[i] - y_mean) * (i - x_mean);
            Sxx += xx * xx;
            Sxy += xy;
            if (i != x_mean)
            {
                Sydx += (profile[i] - y_mean) / xx;
                Scnt++;
            }
            if (max_val < profile[i])
                max_val = profile[i];
        }
    }

    double b_coeff = Sxy / Sxx;
    double ratio = Sydx / Scnt;
    getLogExt().append("Slope coefficient", b_coeff);
    getLogExt().append("Y/X Ratio", ratio);

    for (size_t i = 0; i < visited.size(); i++)
    {
        int y = round(visited[i].y);
        int x = round(visited[i].x);
        if (y >= 0 && x >= 0 && y < _img.getHeight() && x < _img.getWidth())
            _bfs_state[y * w + x] = 0;
    }

    // if (abs(b_coeff) > vars.wbe.SingleUpSlopeThresh && (y_mean > vars.dynamic.LineThickness || max_r / min_r > 2))
    // printf("%.5f\n", abs(ratio));
    // printf("%.5f %.5f\n", abs(b_coeff), abs(ratio));
    // if (abs(ratio) > 0.3)
    if (abs(b_coeff) > vars.wbe.SingleUpSlopeThresh && (y_mean > vars.dynamic.LineThickness || max_r / min_r > 2))
    {
        return_type = BT_SINGLE_UP;
        if (b_coeff < 0)
            _bonds_to_reverse.push_back(e1); // g.reverseEdge(e1);
        return true;
    }
    else if (y_mean / vars.dynamic.LineThickness > vars.wbe.SingleUpThickThresh)
    {
        return_type = BT_WEDGE;
        return true;
    }
    return false;
}

void WedgeBondExtractor::CurateSingleUpBonds(Skeleton& graph)
{
    Skeleton::SkeletonGraph& g = graph.getGraph();
    for (Skeleton::SkeletonGraph::edge_iterator begin = g.edgeBegin(), end = g.edgeEnd(); begin != end; begin = end)
        for (Skeleton::SkeletonGraph::edge_descriptor e; begin != end ? (e = *begin, true) : false; ++begin)
        {
            BondType edge_type = graph.getBondType(e);
            if (edge_type == BT_SINGLE_UP)
            {
                Skeleton::Vertex b_v = graph.getBondBegin(e);
                Skeleton::Vertex e_v = graph.getBondEnd(e);
                int v1 = getVertexValence(b_v, graph), v2 = getVertexValence(e_v, graph);
                if (v1 == v2 && v1 == 1)
                    graph.setBondType(e, BT_SINGLE);
            }
            if (edge_type == BT_WEDGE)
            {
                Skeleton::Vertex b_v = graph.getBondBegin(e);
                Skeleton::Vertex e_v = graph.getBondEnd(e);
                bool has_single_begin = false, has_single_end = false;

                std::deque<Skeleton::Vertex> neighbors;
                Skeleton::SkeletonGraph::adjacency_iterator b_e, e_e;
                b_e = g.adjacencyBegin(b_v);
                e_e = g.adjacencyEnd(b_v);
                neighbors.assign(b_e, e_e);

                // check edges from beginning vertex
                for (size_t i = 0; i < neighbors.size(); i++)
                {
                    if (neighbors[i] != e_v)
                    {
                        Skeleton::Edge edge = g.getEdge(neighbors[i], b_v).first;
                        if (graph.getBondType(edge) == BT_SINGLE_UP)
                        {
                            has_single_begin = true;
                            break;
                        }
                    }
                }

                // check edges from ending vertex
                b_e = g.adjacencyBegin(e_v);
                e_e = g.adjacencyEnd(e_v);
                neighbors.assign(b_e, e_e);
                for (size_t i = 0; i < neighbors.size(); i++)
                {
                    if (neighbors[i] != b_v)
                    {
                        Skeleton::Edge edge = g.getEdge(neighbors[i], e_v).first;
                        if (graph.getBondType(edge) == BT_SINGLE_UP)
                        {
                            has_single_end = true;
                            break;
                        }
                    }
                }

                if (has_single_begin && has_single_end)
                    graph.setBondType(e, BT_SINGLE);
            }
        }

    for (Skeleton::SkeletonGraph::edge_iterator begin = g.edgeBegin(), end = g.edgeEnd(); begin != end; begin = end)
        for (Skeleton::SkeletonGraph::edge_descriptor e; begin != end ? (e = *begin, true) : false; ++begin)
        {
            BondType edge_type = graph.getBondType(e);
            if (edge_type == BT_WEDGE)
                graph.setBondType(e, BT_SINGLE_UP_C);
        }
}

void WedgeBondExtractor::fetchArrows(const Settings& vars, Skeleton& g)
{
    Skeleton::SkeletonGraph& graph = g.getGraph();
    for (Skeleton::SkeletonGraph::edge_iterator begin = graph.edgeBegin(), end = graph.edgeEnd(); begin != end; begin = end)
        for (Skeleton::SkeletonGraph::edge_descriptor e; begin != end ? (e = *begin, true) : false; ++begin)
        {
            BondType edge_type = g.getBondType(e);
            if (edge_type == BT_SINGLE_UP)
            {
                Skeleton::Vertex b = g.getBondBegin(e);
                Skeleton::Vertex e_v = g.getBondEnd(e);
                size_t b_deg = graph.getDegree(b);
                size_t e_deg = graph.getDegree(e_v);
                size_t min_deg = b_deg < e_deg ? b_deg : e_deg;
                size_t max_deg = b_deg > e_deg ? b_deg : e_deg;

                if (min_deg == 1 && max_deg == 2)
                {
                    Skeleton::Vertex v = b;
                    if (e_deg == 2)
                        v = e_v;
                    std::deque<Skeleton::Vertex> neighbors;
                    Skeleton::SkeletonGraph::adjacency_iterator b_e, e_e;
                    b_e = graph.adjacencyBegin(v);
                    e_e = graph.adjacencyEnd(v);
                    neighbors.assign(b_e, e_e);

                    for (size_t i = 0; i < neighbors.size(); i++)
                    {
                        if (neighbors[i] != b && neighbors[i] != e_v && graph.getDegree(neighbors[i]) == 1)
                        {
                            Skeleton::Edge edge = graph.getEdge(neighbors[i], v).first;

                            if (g.getBondType(edge) == BT_SINGLE)
                            {
                                Vec2d v1 = g.getVertexPos(neighbors[i]);
                                Vec2d v2 = g.getVertexPos(v);
                                Vec2d v3 = g.getVertexPos(v);
                                Vec2d v4 = g.getVertexPos(b_deg == 1 ? b : e_v);

                                if (Algebra::SegmentsOnSameLine(vars, v1, v2, v3, v4))
                                {
                                    // arrow found
                                    // TODO: handle properly
                                    g.removeBond(edge);
                                    g.removeBond(v, (b_deg == 1 ? b : e_v));
                                    g.addBond(neighbors[i], (b_deg == 1 ? b : e_v), BT_ARROW, true);
                                }
                            }
                        }
                    }
                }
            }
        }
}

WedgeBondExtractor::~WedgeBondExtractor()
{
}
