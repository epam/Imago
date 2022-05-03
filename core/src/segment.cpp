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

#include "segment.h"

#include <deque>
#include <vector>

#include "rectangle.h"
#include "vec2d.h"

using namespace imago;

Segment::Segment()
{
    _density = _ratio = -1;
    _x = _y = 0;
}

void Segment::copy(const Segment& s, bool copy_all)
{
    Image::copy(s);
    if (copy_all)
    {
        _x = s._x;
        _y = s._y;
    }
    else
    {
        _x = _y = 0;
    }
}

/**
 * @brief Getter for x
 *
 * @return const reference to _x
 */
int Segment::getX() const
{
    return _x;
}

/**
 * @brief Getter for y
 *
 * @return const reference to _y
 */
int Segment::getY() const
{
    return _y;
}

/**
 * @brief Getter for x
 *
 * @return const reference to _x
 */
int& Segment::getX()
{
    return _x;
}

/**
 * @brief Getter for y
 *
 * @return const reference to _y
 */
int& Segment::getY()
{
    return _y;
}

Rectangle Segment::getRectangle() const
{
    return Rectangle(_x, _y, getWidth(), getHeight());
}

double Segment::getRatio() const
{
    if (_ratio < 0)
        return (double)getWidth() / getHeight();

    return _ratio;
}

double Segment::getRatio()
{
    if (_ratio < 0)
    {
        _ratio = getWidth();
        _ratio /= getHeight();
    }

    return _ratio;
}

Vec2i Segment::getCenter() const
{
    return Vec2i(_x + getWidth() / 2, _y + getHeight() / 2);
}

double Segment::getDensity() const
{
    if (_density < 0)
        return density();

    return _density;
}

double Segment::getDensity()
{
    if (_density < 0)
        _density = density();

    return _density;
}

double Segment::getDiameter()
{
    int d = 0;
    std::vector<int> left(rows, cols);
    std::vector<int> right(rows, -1);
    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++)
            if (!getByte(x, y))
            {
                if (left[y] == cols)
                    left[y] = x;
                right[y] = x;
            }

    for (int y1 = 0; y1 < rows; y1++)
        if (left[y1] < cols)
            for (int y2 = 0; y2 < rows; y2++)
                if (right[y2] > -1)
                    d = std::max(d, (y2 - y1) * (y2 - y1) + (left[y1] - right[y2]) * (left[y1] - right[y2]));

    return sqrt(1. * d);
}

void Segment::splitVert(int x, Segment& left, Segment& right) const
{
    Image::splitVert(x, left, right);

    left._x = _x;
    right._x = _x + x;
    left._y = right._y = _y;
}

void Segment::splitHor(int y, Segment& up, Segment& down) const
{
    Image::splitHor(y, up, down);

    up._y = _y;
    down._y = _y + y;
    up._x = down._x = _x;
}

void Segment::crop()
{
    int l = 0, t = 0;

    Image::crop(-1, -1, -1, -1, &l, &t);

    _x += l;
    _y += t;
}

void Segment::rotate90()
{
    Image::rotate90();
    std::swap(_x, _y);
}

Segment::~Segment()
{
}
