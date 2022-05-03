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
#include "stl_fwd.h"

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
        static void cutSegmentExtra(Image& img, const Segment& seg, byte val = 255);
        static void removeSegmentsFromDeque(SegmentDeque& from_delete, SegmentDeque& what_delete);

        static bool testSlashLine(const Settings& vars, Segment& img, double* angle, double eps);
        static bool testSmall(Segment& img, double bond_len);
        static bool isThinCircle(const Settings& vars, Image& seg, double& radius, bool asChar = false);
        static double estimateLineThickness(Image& bwimg, int grid);
        static void analizeImage(Image& img, double& predicted_len, double& predicted_count);
        static double preestimateBondLen(Image& img);
        static bool _hasRadius(Image& img, int x, int y, double r);
        static bool _isThereSegment(Image& img, int x1, int y1, int x2, int y2);
        static int _maxRadius(Image& img, int cx, int cy);
        static Vec2i _farestSegmentEnd(Image& img, Vec2i center, double thickness, bool& on_line, double& linearity, double& centrality);
        static void _fillStopSegmentField(Image& img, Vec2i center, double thickness, std::vector<Vec2i>&);
        static bool _isSegment(Segment& img, double accepThick);
        static void calulateLinearity(Image& img, std::vector<std::vector<double>>& linearity, std::vector<std::vector<double>>& centrality);
        static void extractGraphics(Image& img, SegmentDeque& _segs, SegmentDeque& _grapics, SegmentDeque& _symbols, SegmentDeque& _lines,
                                    double bad_bond_len = -1);
        static double getSegmentLinearity(std::vector<std::vector<double>>& linearity, Segment& seg);
        static int getSplitY(std::vector<std::vector<double>>& linearity, Segment& seg);
        static int getSplitX(std::vector<std::vector<double>>& linearity, Segment& seg);
        static int getSplitCoord(std::vector<double>& mid, std::vector<int>& cnt);
        static bool isVertexOnEdge(Vec2i a, Vec2i b, Vec2i p, double thickness);
    };

    class Fraction
    {
    private:
        int x;
        int y; // 0 < x, y < 2^16
    public:
        static int gcd(int x, int y)
        {
            return x > y ? gcd(y, x) : x * y ? gcd(y % x, x) : x + y;
        }
        void reduce()
        {
            int a = gcd(x, y);
            x /= a;
            y /= a;
        }
        Fraction(int xx = 1, int yy = 1) : x(xx), y(yy)
        {
            reduce();
        }
        bool operator>(Fraction& f)
        {
            return x * f.y > f.x * y;
        }
        bool operator<(Fraction& f)
        {
            return f > *this;
        }
        bool operator==(Fraction& f)
        {
            return x == f.x && y == f.y;
        }
        bool operator<=(Fraction& f)
        {
            return !(*this > f);
        }
        bool operator>=(Fraction& f)
        {
            return !(*this < f);
        }
        static bool less(const Fraction& f1, const Fraction& f2)
        {
            return f1.x * f2.y < f1.y * f2.x;
        }

        static Fraction max(const Fraction& x, const Fraction& y)
        {
            return std::max(x, y, less);
        }
        static Fraction min(const Fraction& x, const Fraction& y)
        {
            return std::min(x, y, less);
        }
        void print()
        {
            printf("(%d / %d) ", x, y);
        }
        void println()
        {
            print();
            printf("\n");
        }
    };

    class Interval
    {
        Fraction start;
        Fraction finish;

    public:
        Interval(Fraction& s, Fraction& f) : start(s), finish(f){};
        static Interval unite(const Interval& s1, const Interval& s2)
        {
            Fraction s = Fraction::min(s1.start, s2.start);
            Fraction f = Fraction::max(s1.finish, s2.finish);
            return Interval(s, f);
        }
        static Interval intersec(const Interval& s1, const Interval& s2)
        {
            Fraction s = Fraction::max(s1.start, s2.start);
            Fraction f = Fraction::min(s1.finish, s2.finish);
            return Interval(s, f);
        }
        bool is_void()
        {
            return start > finish;
        }
    };
}
