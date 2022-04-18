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

#include <vector>

#include "settings.h"

namespace cv
{
    class Mat;
}

namespace imago
{
    class Image;
    class Segment;

    class ImageUtils
    {
    public:
        static void copyImageToMat(const Image& img, cv::Mat& mat);
        static void copyMatToImage(const cv::Mat& mat, Image& img);

        static void loadImageFromFile(Image& img, const char* FileName, ...);
        static void saveImageToFile(const Image& img, const char* FileName, ...);

        static void loadImageFromBuffer(const std::vector<byte>& buffer, Image& img);
        static void saveImageToBuffer(const Image& img, const std::string& format, std::vector<byte>& buffer);

        static void putSegment(Image& img, const Segment& seg, bool careful = true);
        static void cutSegment(Image& img, const Segment& seg, bool forceCut = false, byte val = 255);

        static bool testSlashLine(const Settings& vars, Segment& img, double* angle, double eps);
        static bool isThinCircle(const Settings& vars, Image& seg, double& radius, bool asChar = false);
        static double estimateLineThickness(Image& bwimg, int grid);
    };
}
