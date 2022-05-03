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

/**
 * @file   image.cpp
 *
 * @brief  Implementation of Image class
 */

#include "image.h"

#include <cmath>

#include "image_draw_utils.h"
#include "image_utils.h"
#include "log_ext.h"
#include "stat_utils.h"

using namespace imago;
using namespace std;

/**
 * @brief Crops image
 */
void Image::crop(int left, int top, int right, int bottom, int* shift_x, int* shift_y)
{
    int w = getWidth();
    int h = getHeight();

    if (left == -1 || right == -1 || top == -1 || bottom == -1)
    {
        for (left = 0; left < w; left++)
            for (int y = 0; y < h; y++)
                if (isFilled(left, y))
                {
                    goto left_done;
                }

    left_done:

        for (right = w - 1; right >= left; right--)
            for (int y = 0; y < h; y++)
                if (isFilled(right, y))
                {
                    goto right_done;
                }

    right_done:

        for (top = 0; top < h; top++)
            for (int x = 0; x < w; x++)
                if (isFilled(x, top))
                {
                    goto top_done;
                }

    top_done:

        for (bottom = h - 1; bottom >= top; bottom--)
            for (int x = 0; x < w; x++)
                if (isFilled(x, bottom))
                {
                    goto bottom_done;
                }

    bottom_done:;
    }

    if (left >= 0 && right >= 0 && top >= 0 && bottom >= 0)
    {
        if (shift_x)
            *shift_x = left;
        if (shift_y)
            *shift_y = top;
        extractRect(left, top, right, bottom, *this);
    }
}

bool Image::isInternal(int x, int y, double r)
{
    int d = (int)r;
    for (int dx = -d; dx <= d; dx++)
        for (int dy = -d; dy <= d; dy++)
            if (dx * dx + dy * dy <= r * r && in(x + dx, y + dy) && !isFilled(x + dx, y + dy))
                return false;
    return true;
}

void Image::initStopVectorField()
{
    // smoothing(-1);
    // smoothing(2);
    int w = getWidth(), h = getHeight();
    _stopVectorField = vector<vector<vector<Vec2i>>>(w, vector<vector<Vec2i>>(h, vector<Vec2i>(0)));
    double thickness = ImageUtils::estimateLineThickness(*this, 1);
    for (int x = 0; x < w; x++)
    {
        if (x % 100 == 0)
            printf("%d.. \n", x);
        for (int y = 0; y < h; y++)
            if (isFilled(x, y))
            {
                ImageUtils::_fillStopSegmentField(*this, Vec2i(x, y), thickness, _stopVectorField[x][y]);
                // printf(" ... %d\n", stopVectorField[x][y].size());
            }
    }
}

void Image::calculateLinearity(vector<vector<double>>& linearity)
{
    int w = getWidth(), h = getHeight();
    linearity = vector<vector<double>>(w, vector<double>(h, 0.));
    auto stopVectorField = getStopVectorField();
    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
            if (isFilled(x, y))
            {
                vector<double> lens;
                Vec2i center(x, y);
                for (auto p : stopVectorField[x][y])
                    lens.push_back(Vec2i::distance(p, center));
                int index1, index2;
                if (lens[0] + lens[3] > lens[1] + lens[2])
                    index1 = 0, index2 = 3;
                else
                    index1 = 1, index2 = 2;

                double dist = Vec2i::distance(stopVectorField[x][y][index1], stopVectorField[x][y][index2]);
                linearity[x][y] = 1. * lens[index1] * lens[index2] / (lens[index1] + lens[index2] - dist + 1) / (lens[index1] + lens[index2] - dist + 1);
            }
}

void Image::calculateCentrality(std::vector<std::vector<double>>& centrality)
{
    int w = getWidth(), h = getHeight();
    centrality = vector<vector<double>>(w, vector<double>(h, 0.));
    auto stopVectorField = getStopVectorField();
    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
            if (isFilled(x, y))
            {
                for (auto p : stopVectorField[x][y])
                {
                    double dist = Vec2i::distance(Vec2i(x, y), p);
                    centrality[x][y] += dist * dist * dist;
                }
            }
}

double Image::estimateBondLen(SegmentDeque& segments)
{
    double thickness = ImageUtils::estimateLineThickness(*this, 1);
    printf("Thickness = %.5f\n", thickness);
    vector<double> lens;
    int cnt = 0;
    auto stopVectorField = getStopVectorField();
    for (auto seg : segments)
    {
        for (int x = 0; x < seg->getWidth(); x++)
            for (int y = 0; y < seg->getHeight(); y++)
                if (seg->isFilled(x, y))
                {
                    Vec2i center(x + seg->getX(), y + seg->getY());
                    double dist = 0;
                    for (auto p : stopVectorField[center.x][center.y])
                    {
                        cnt++;
                        dist = max(dist, Vec2i::distance(center, p));
                    }

                    lens.push_back(dist);
                }
    }
    sort(lens.begin(), lens.end());
    double answ = StatUtils::interMean(lens.begin(), lens.end()) * 4 / 3;
    // printf("%.5f\n", answ);
    // printf("%d\n", cnt);

    return answ;
}

void Image::shiftBorder(int n)
{
    if (cols + 2 * n <= 0 || rows + 2 * n <= 0)
    {
        Image newimage(0, 0);
        copy(newimage);
        return;
    }

    Image newimage(cols + 2 * n, rows + 2 * n);
    newimage.fillWhite();
    if (n >= 0)
    {
        for (int x = 0; x < cols; x++)
            for (int y = 0; y < rows; y++)
                newimage.getByte(x + n, y + n) = getByte(x, y);
    }
    else
    {
        for (int x = -n; x - n < cols; x++)
            for (int y = -n; y - n < rows; y++)
                newimage.getByte(x + n, y + n) = getByte(x, y);
    }
    copy(newimage);
}

void Image::getInterior(int r)
{
    Image newimage(cols, rows);
    for (int x = 0; x < cols; x++)
        for (int y = 0; y < rows; y++)
            if (isInternal(x, y, r))
                newimage.getByte(x, y) = 0;
            else
                newimage.getByte(x, y) = 255;

    copy(newimage);
}

void Image::smoothing(int r)
{
    invertColor();
    getInterior(r);
    invertColor();
    getInterior(r);
}

int Image::getSquare()
{
    int cnt = 0;
    for (int x = 0; x < getWidth(); x++)
        for (int y = 0; y < getHeight(); y++)
            cnt += isFilled(x, y);

    return cnt;
}

int Image::getPerimeter()
{
    int cnt = 0;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    for (int x = 0; x < getWidth(); x++)
        for (int y = 0; y < getHeight(); y++)
            if (isFilled(x, y))
                for (int t = 0; t < 4; t++)
                    cnt += !isPixel(x + dx[t], y + dy[t]);

    return cnt;
}

int Image::getBadPixelsCount()
{
    int cnt = 0;
    for (int x = 0; x < getWidth(); x++)
        for (int y = 0; y < getHeight(); y++)
            if (isFilled(x, y))
                cnt += (!isPixel(x - 1, y) && !isPixel(x + 1, y)) || (!isPixel(x, y - 1) && !isPixel(x, y + 1));

    return cnt;
}

double Image::getRoughness()
{
    return (double)getPerimeter() / getSquare();
}

double Image::getRoughness2()
{
    double perimeter = getPerimeter();
    return sqrt(perimeter) * perimeter / getSquare();
}

double Image::getRoughness3()
{
    return 1.0 * getBadPixelsCount() / getSquare();
}

void Image::_findGraph(SegmentDeque& _segs, vector<Vec2i>& atoms, vector<pair<int, int>>& edge)
{
    int h = getHeight(), w = getWidth();
    // printf("Starting search (%d x %d)\n", w, h);

    double thickness = ImageUtils::estimateLineThickness(*this, 1);
    vector<vector<double>> centrality;
    calculateCentrality(centrality);

    // 0. Searching of centrality field
    const int size = 5;
    int core[size + 1][size + 1];
    int base = 3;
    for (int x = 0; x <= size; x++)
        for (int y = 0; y <= size; y++)
            core[x][y] = 1;
    for (int i = size; i > 0; i--)
        for (int x = 0; x < i; x++)
            for (int y = 0; y < i; y++)
                core[x][y] *= base;

    vector<vector<double>> convolution(w, vector<double>(h, 0));
    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
            for (int dx = -size; dx <= size; dx++)
                for (int dy = -size; dy <= size; dy++)
                    if (in(x + dx, y + dy))
                    {
                        convolution[x][y] += centrality[x + dx][y + dy] * core[abs(dx)][abs(dy)];
                    }

    // 1. Primary atoms search
    vector<vector<int>> segment_number(w, vector<int>(h, -1));
    int index = 0;
    for (auto seg : _segs)
    {
        for (int x = 0; x < seg->getWidth(); x++)
            for (int y = 0; y < seg->getHeight(); y++)
                if (seg->isFilled(x, y))
                    segment_number[seg->getX() + x][seg->getY() + y] = index;
        index++;
    }

    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
            if (segment_number[x][y] >= 0)
            {
                bool is_local_max = true;
                for (int dx = -size; dx <= size; dx++)
                    for (int dy = -size; dy <= size; dy++)
                        if (in(x + dx, y + dy) && segment_number[x + dx][y + dy] == segment_number[x][y])
                        {
                            is_local_max &= convolution[x][y] >= convolution[x + dx][y + dy];
                        }
                if (is_local_max)
                {
                    atoms.emplace_back(x, y);
                }
            }

    int atoms_count = atoms.size();
    auto stopVectorField = getStopVectorField();

    Image log_image(w, h);
    log_image.fillWhite();

    set<Vec2i> atoms_set;
    for (auto a : atoms)
        atoms_set.insert(a);
    map<Vec2i, int> atoms_number;
    for (int i = 0; i < atoms.size(); i++)
        atoms_number[atoms[i]] = i + 1;

    // 2. Diametral vertices adding
    edge.clear();
    for (int i = 0; i < atoms_count; i++)
    {
        auto vector = stopVectorField[atoms[i].x][atoms[i].y];
        int farest = 0;
        for (int j = 1; j < 4; j++)
            if (Vec2i::distance(atoms[i], vector[j]) > Vec2i::distance(atoms[i], vector[farest]))
                farest = j;

        if (atoms_set.count(vector[farest]))
        {
            edge.emplace_back(i, atoms_number[vector[farest]] - 1);
        }
        else
        {
            edge.emplace_back(i, atoms.size());
            atoms_set.insert(vector[farest]);
            atoms_number[vector[farest]] = atoms.size() + 1;
            atoms.push_back(vector[farest]);
        }
    }

    // 3. Edges searching
    for (int i = 0; i < atoms.size(); i++)
        for (int j = 0; j < i; j++)
            if (segment_number[atoms[i].x][atoms[i].y] == segment_number[atoms[j].x][atoms[j].y])
                if (ImageUtils::_isThereSegment(*this, atoms[i].x, atoms[i].y, atoms[j].x, atoms[j].y))
                    edge.emplace_back(i, j);

    for (auto a : atoms)
        ImageDrawUtils::putCircle(log_image, a.x, a.y, 5, 0);
    for (auto e : edge)
        ImageDrawUtils::putLineSegment(log_image, atoms[e.first], atoms[e.second], 0);

    getLogExt().appendImage("Molecule Graph:", log_image);

    // 4. Uniting close vertices
    vector<vector<int>> graph(atoms.size(), vector<int>(0));

    int max_dist = 5 * thickness;

    for (int i = 0; i < atoms.size(); i++)
    {
        // dijkstra algorithm
        set<pair<double, Vec2i>> dist_set;
        dist_set.emplace(1, atoms[i]);

        vector<Vec2i> pos(0);
        map<Vec2i, int> dist;

        while (!dist_set.empty())
        {
            auto d = *dist_set.begin();
            if (d.first > max_dist + 1)
                break;

            pos.push_back(d.second);
            dist[d.second] = d.first;
            dist_set.erase(d);

            for (int dx = -1; dx <= 1; dx++)
                for (int dy = -1; dy <= 1; dy++)
                    if (dx || dy)
                    {
                        double add = dx * dy ? sqrt(2) : 1;
                        Vec2i newvec(d.second);
                        newvec.add(Vec2i(dx, dy));
                        if (!isPixel(newvec.x, newvec.y))
                            continue;
                        if (dist[newvec] == 0 || dist[newvec] > d.first + add)
                        {
                            dist_set.erase(make_pair(dist[newvec], newvec));
                            dist[newvec] = d.first + add;
                            dist_set.emplace(dist[newvec], newvec);
                        }
                    }
        }

        for (auto p : pos)
            if (atoms_number[p] > 0)
                graph[i].push_back(atoms_number[p] - 1);
    }

    vector<Vec2d> grouped_atom;
    vector<int> group_size;
    vector<int> number_of_group(atoms.size(), -1);
    int group_count = 0;
    for (int i = 0; i < atoms.size(); i++)
        if (number_of_group[i] == -1)
        {
            group_size.push_back(0);
            grouped_atom.emplace_back();
            for (int j : graph[i])
            {
                number_of_group[j] = group_count;
                group_size.back()++;
                grouped_atom.back().add(atoms[j]);
            }
            grouped_atom.back().scale(1. / group_size.back());
            group_count++;
        }

    vector<vector<bool>> united_edge(group_count, vector<bool>(group_count, false));
    for (auto e : edge)
        united_edge[number_of_group[e.first]][number_of_group[e.second]] = true;
    for (int i = 0; i < group_count; i++)
        for (int j = 0; j < group_count; j++)
            united_edge[i][j] = united_edge[i][j] || united_edge[j][i];
    for (int i = 0; i < group_count; i++)
        united_edge[i][i] = false;

    Image log_image2(w, h);
    log_image2.fillWhite();

    for (auto a : grouped_atom)
        ImageDrawUtils::putCircle(log_image2, a.x, a.y, 5, 0);
    for (int i = 0; i < group_count; i++)
        for (int j = 0; j < group_count; j++)
            if (united_edge[i][j])
                ImageDrawUtils::putLineSegment(log_image2, grouped_atom[i], grouped_atom[j], 0);

    getLogExt().appendImage("Molecule Graph 2:", log_image2);

    // 5. Remove waste vertices of edges

    set<pair<double, pair<int, int>>> edge_with_length;
    for (int i = 0; i < group_count; i++)
        for (int j = 0; j < i; j++)
            if (united_edge[i][j])
                edge_with_length.emplace(Vec2i::distance(grouped_atom[i], grouped_atom[j]), make_pair(j, i));

    while (!edge_with_length.empty())
    {
        auto e = *edge_with_length.rbegin();
        int i = e.second.first, j = e.second.second;
        for (int k = 0; k < group_count; k++)
            if (k != i && k != j)
                if (ImageUtils::isVertexOnEdge(grouped_atom[i], grouped_atom[j], grouped_atom[k], thickness))
                {
                    edge_with_length.emplace(Vec2i::distance(grouped_atom[i], grouped_atom[k]), make_pair(min(i, k), max(i, k)));
                    edge_with_length.emplace(Vec2i::distance(grouped_atom[j], grouped_atom[k]), make_pair(min(j, k), max(j, k)));
                    united_edge[i][k] = united_edge[k][i] = true;
                    united_edge[j][k] = united_edge[k][j] = true;
                    united_edge[i][j] = united_edge[j][i] = false;
                    break;
                }
        edge_with_length.erase(e);
    }

    vector<bool> to_delete(atoms.size(), false);
    for (int iter = 0; iter < 2; iter++)
    {
        for (int i = 0; i < group_count; i++)
            if (!to_delete[i])
            {
                int cnt = 0;
                int first = -1;
                int second = -1;
                for (int j = 0; j < group_count; j++)
                    if (united_edge[i][j])
                    {
                        cnt++;
                        second = first;
                        first = j;
                    }
                if (cnt == 2)
                {
                    if (ImageUtils::isVertexOnEdge(grouped_atom[first], grouped_atom[second], grouped_atom[i], 2 * thickness))
                    {
                        united_edge[first][second] = united_edge[second][first] = true;
                        united_edge[first][i] = united_edge[i][first] = false;
                        united_edge[second][i] = united_edge[i][second] = false;
                        to_delete[i] = true;
                    }
                }
            }
    }

    Image log_image3(w, h);
    log_image3.fillWhite();

    for (int i = 0; i < grouped_atom.size(); i++)
        if (!to_delete[i])
            ImageDrawUtils::putCircle(log_image3, grouped_atom[i].x, grouped_atom[i].y, 5, 0);
    for (int i = 0; i < group_count; i++)
        if (!to_delete[i])
            for (int j = 0; j < group_count; j++)
                if (!to_delete[j] && united_edge[i][j])
                    ImageDrawUtils::putLineSegment(log_image3, grouped_atom[i], grouped_atom[j], 0);

    getLogExt().appendImage("Molecule Graph 3:", log_image3);

    atoms.clear();
    vector<int> atom_index(group_count, -1);
    int aind = 0;
    for (int i = 0; i < group_count; i++)
        if (!to_delete[i])
        {
            atoms.push_back(grouped_atom[i]);
            atom_index[i] = aind++;
        }
    // atoms.resize(aind);
    edge.clear();
    for (int i = 0; i < group_count; i++)
        if (!to_delete[i])
            for (int j = 0; j < i; j++)
                if (!to_delete[j] && united_edge[j][i])
                    edge.emplace_back(atom_index[j], atom_index[i]);
}

std::vector<std::vector<std::vector<Vec2i>>>& Image::getStopVectorField()
{
    if (!isStopVectorFieldCalulated)
    {
        initStopVectorField();
        isStopVectorFieldCalulated = true;
    }
    return _stopVectorField;
}
