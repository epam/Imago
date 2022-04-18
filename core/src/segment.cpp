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

void Segment::splitVert(int x, Segment& left, Segment& right) const
{
    Image::splitVert(x, left, right);

    left._x = _x;
    right._x = _x + x;
    left._y = right._y = _y;
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
