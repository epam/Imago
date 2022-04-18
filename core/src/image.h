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
 * @file image.h
 *
 * @brief   Declares the Image class
 */

#pragma once

#include <opencv2/opencv.hpp>

#include "comdef.h"
#include "exception.h"

namespace imago
{
    class Image : public cv::Mat1b
    {
    public:
        Image()
        {
        }

        Image(int width, int height) : cv::Mat1b(height, width)
        {
        }

        Image(const Image& other)
        {
            copy(other);
        }

        virtual ~Image()
        {
        }

        inline void init(int width, int height)
        {
            *this = Image(width, height);
        }

        inline void clear()
        {
            cv::Mat1b::resize(0);
        }

        inline bool isInit() const
        {
            return rows > 0;
        }

        inline void fillWhite()
        {
            for (int y = 0; y < rows; y++)
                for (int x = 0; x < cols; x++)
                    getByte(x, y) = 255;
        }

        inline const int& getWidth() const
        {
            return cols;
        }

        inline const int& getHeight() const
        {
            return rows;
        }

        inline byte& getByte(int x, int y)
        {
            return (*this)(y, x);
        }

        inline const byte& getByte(int x, int y) const
        {
            return (*this)(y, x);
        }

        inline bool isFilled(int x, int y) const
        {
            return getByte(x, y) != 255;
        }

        inline void copy(const Image& other)
        {
            other.copyTo(*this);
        }

        inline void emptyCopy(const Image& other)
        {
            *this = Image(other.cols, other.rows);
            fillWhite();
        }

        inline void invertColor()
        {
            for (int y = 0; y < getHeight(); y++)
                for (int x = 0; x < getWidth(); x++)
                    getByte(x, y) = 255 - getByte(x, y);
        }

        void crop(int left = -1, int top = -1, int right = -1, int bottom = -1, int* shift_x = NULL, int* shift_y = NULL);

        inline void extractRect(int x1, int y1, int x2, int y2, Image& res) const
        {
            if (x1 < 0)
                x1 = 0;
            if (y1 < 0)
                y1 = 0;
            if (x2 >= getWidth())
                x2 = getWidth() - 1;
            if (y2 >= getHeight())
                y2 = getHeight() - 1;
            (*this)(cv::Rect(x1, y1, x2 - x1 + 1, y2 - y1 + 1)).copyTo(res);
        }

        inline void splitVert(int x, Image& left, Image& right) const
        {
            extractRect(0, 0, x, getHeight() - 1, left);
            extractRect(x + 1, 0, getWidth() - 1, getHeight() - 1, right);
        }

        inline double density() const
        {
            int density = 0;
            for (int y = 0; y < rows; y++)
                for (int x = 0; x < cols; x++)
                    if (getByte(x, y) == 0)
                        density++;
            return (double)density / (cols * rows);
        }

        inline int mean() const
        {
            return (int)(cv::mean(*this)[0]);
        }

        inline void rotate90()
        {
            cv::transpose(*this, *this);
        }
    };
}
