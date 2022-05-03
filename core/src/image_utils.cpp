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

#include "image_utils.h"

#include <algorithm>
#include <cmath>
#include <cstdarg>
#include <string>

#include <opencv2/opencv.hpp>

#include "accum_field.h"
#include "failsafe_png.h"
#include "image.h"
#include "image_draw_utils.h"
#include "log_ext.h"
#include "output.h"
#include "scanner.h"
#include "segment.h"
#include "stat_utils.h"
#include "thin_filter2.h"
#include "vec2d.h"

using namespace std;

namespace imago
{
    bool ImageUtils::testSmall(Segment& img, double bond_len)
    {
        int h = img.getHeight(), w = img.getWidth();
        int threshold = bond_len / 3;
        return h * h + w * w < threshold * threshold;
    }

    bool ImageUtils::testSlashLine(const Settings& vars, Segment& img, double* angle, double eps)
    {
        logEnterFunction();

        double density, thetha, r;

        getLogExt().appendSegment("segment", img);

        Image tmp;

        tmp.copy(img);
        ThinFilter2(tmp).apply();

        thetha = HALF_PI + atan2((double)img.getHeight(), (double)img.getWidth());
        r = 0;
        density = tmp.density();
        ImageDrawUtils::putLine(tmp, thetha, r, eps, 255);
        density = tmp.density() / density;

        if (density < vars.utils.SlashLineDensity)
        {
            if (angle != 0)
                *angle = thetha;
            return true;
        }

        tmp.copy(img);
        ThinFilter2(tmp).apply();

        thetha = -thetha;
        r = cos(thetha) * img.getWidth();
        density = tmp.density();
        ImageDrawUtils::putLine(tmp, thetha, r, eps, 255);
        density = tmp.density() / density;

        if (density < vars.utils.SlashLineDensity)
        {
            if (angle != 0)
                *angle = thetha;
            return true;
        }

        if (angle != 0)
            *angle = thetha;

        return false;
    }

    void ImageUtils::putSegment(Image& img, const Segment& seg, bool careful)
    {
        int i, j, img_cols = img.getWidth(), seg_x = seg.getX(), seg_y = seg.getY(), seg_rows = seg.getHeight(), seg_cols = seg.getWidth(),
                  img_size = img.getWidth() * img.getHeight();

        for (j = 0; j < seg_rows; j++)
            for (i = 0; i < seg_cols; i++)
            {
                int y = j + seg_y;
                int x = i + seg_x;
                // int address = (j + seg_y) * img_cols + (i + seg_x);

                // if (address < img_size)
                if (y >= 0 && y < img.getHeight() && x >= 0 && x < img.getWidth())
                {
                    if (careful)
                    {
                        if (img.getByte(x, y) == 255)
                            img.getByte(x, y) = seg.getByte(i, j);
                    }
                    else
                    {
                        img.getByte(x, y) = seg.getByte(i, j);
                    }
                }
            }
    }

    void ImageUtils::cutSegment(Image& img, const Segment& seg, bool forceCut, byte val)
    {
        int i, j, img_cols = img.getWidth(), seg_x = seg.getX(), seg_y = seg.getY(), seg_rows = seg.getHeight(), seg_cols = seg.getWidth();

        for (j = 0; j < seg_rows; j++)
            for (i = 0; i < seg_cols; i++)
            {
                int y = j + seg_y;
                int x = i + seg_x;
                // int address = (j + seg_y) * img_cols + (i + seg_x);

                if (y >= 0 && y < img.getHeight() && x >= 0 && x < img.getWidth())
                {
                    if (seg.getByte(i, j) == 0)
                        if (img.getByte(x, y) == 0 || forceCut)
                            img.getByte(x, y) = val;
                }
            }
    }

    void ImageUtils::cutSegmentExtra(Image& img, const Segment& seg, byte val)
    {
        int i, j, img_cols = img.getWidth(), seg_x = seg.getX(), seg_y = seg.getY(), seg_rows = seg.getHeight(), seg_cols = seg.getWidth();

        for (j = 0; j < seg_rows; j++)
            for (i = 0; i < seg_cols; i++)
            {
                int y = j + seg_y;
                int x = i + seg_x;
                // int address = (j + seg_y) * img_cols + (i + seg_x);

                if (y >= 2 && y < img.getHeight() - 2 && x >= 2 && x < img.getWidth() - 2)
                {
                    if (seg.getByte(i, j) == 0)
                    {
                        for (int k = -2; k < 3; k++)
                            for (int l = -2; l < 3; l++)
                                img.getByte(x + l, y + k) = val;
                    }
                }
            }
    }

    void ImageUtils::copyImageToMat(const Image& img, cv::Mat& mat)
    {
        img.copyTo(mat);

        /*
        int w = img.getWidth();
        int h = img.getHeight();

        mat.create(h, w, CV_8U);
        int i, j;

        for (i = 0; i < w; i++)
        for (j = 0; j < h; j++)
        mat.at<unsigned char>(j, i) = img.getByte(i, j);*/
    }

    void ImageUtils::copyMatToImage(const cv::Mat& mat, Image& img)
    {
        mat.copyTo(img);

        /*
        int w = mat.cols;
        int h = mat.rows;

        img.init(w, h);
        int i, j;

        for (i = 0; i < w; i++)
        for (j = 0; j < h; j++)
        img.getByte(i, j) = mat.at<unsigned char>(j, i);*/
    }

    void ImageUtils::loadImageFromBuffer(const vector<byte>& buffer, Image& img)
    {
        cv::Mat mat = cv::imdecode(cv::Mat(buffer), 0);
        if (mat.empty())
            throw ImagoException("Image data is invalid");
        copyMatToImage(mat, img);
    }

    void ImageUtils::loadImageFromFile(Image& img, const char* format, ...)
    {
        logEnterFunction();

        char str[MAX_TEXT_LINE];
        va_list args;

        va_start(args, format);
        vsnprintf(str, sizeof(str), format, args);
        va_end(args);

        const char* FileName = str;
        img.clear();

        string fname(FileName);

        if (fname.length() < 5)
            throw ImagoException("Unknown file format " + fname);

        FILE* f = fopen(fname.c_str(), "r");
        if (f == 0)
            throw FileNotFoundException(fname.c_str());
        fclose(f);

        cv::Mat mat = cv::imread(fname, -1 /*BGRA*/);

        if (mat.empty())
        {
            getLogExt().appendText("CV returned empty mat");
            if (failsafePngLoadFile(fname, img))
            {
                getLogExt().appendText("... but failsafePngLoad helps");
            }
            else
            {
                throw ImagoException("Image file is invalid");
            }
        }
        else
        {
            if (mat.type() == CV_8UC4)
            {
                getLogExt().append("Image type", "CV_8UC4 / BGRA");
                for (int row = 0; row < mat.rows; row++)
                    for (int col = 0; col < mat.cols; col++)
                    {
                        cv::Vec4b& v = mat.at<cv::Vec4b>(row, col);
                        if (v[3] == 0) // transparent
                        {
                            v[0] = v[1] = v[2] = 255; // to white
                        }
                    }
                cv::cvtColor(mat, mat, cv::COLOR_BGRA2GRAY);
            }
            else if (mat.type() == CV_8UC3)
            {
                getLogExt().append("Image type", "CV_8UC3 / BGR");
                cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);
            }
            else if (mat.type() == CV_8UC1)
            {
                getLogExt().append("Image type", "CV_8UC1 / GRAY");
            }
            else
            {
                getLogExt().appendText("Unknown image type, attempt to reload as grayscale");
                mat = cv::imread(fname, 0 /*Grayscale*/);
            }
            copyMatToImage(mat, img);
        }
    }

    void ImageUtils::saveImageToFile(const Image& img, const char* format, ...)
    {
        char str[MAX_TEXT_LINE];
        va_list args;

        va_start(args, format);
        vsnprintf(str, sizeof(str), format, args);
        va_end(args);

        string fname(str);
        cv::Mat mat;
        copyImageToMat(img, mat);
        cv::imwrite(fname, mat);
    }

    void ImageUtils::saveImageToBuffer(const Image& img, const string& ext, vector<byte>& buffer)
    {
        cv::Mat mat;
        copyImageToMat(img, mat);
        cv::imencode(ext, mat, buffer);
    }

    struct _AngRadius
    {
        float ang;
        float radius;
    };

    static int _cmp_ang(const void* p1, const void* p2)
    {
        const _AngRadius& f1 = *(const _AngRadius*)p1;
        const _AngRadius& f2 = *(const _AngRadius*)p2;

        if (f1.ang < f2.ang)
            return -1;
        return 1;
    }

    bool ImageUtils::isThinCircle(const Settings& vars, Image& seg, double& radius, bool asChar)
    {
        logEnterFunction();

        int w = seg.getWidth();
        int h = seg.getHeight();
        int i, j;
        float centerx = 0, centery = 0;
        int npoints = 0;

        for (j = 0; j < h; j++)
        {
            for (i = 0; i < w; i++)
            {
                if (seg.getByte(i, j) == 0)
                {
                    centerx += i;
                    centery += j;
                    npoints++;
                }
            }
        }

        if (npoints == 0)
            throw ImagoException("Empty fragment");

        centerx /= npoints;
        centery /= npoints;

        _AngRadius* points = new _AngRadius[npoints + 1];
        int k = 0;
        float avg_radius = 0;

        for (i = 0; i < w; i++)
            for (j = 0; j < h; j++)
            {
                if (seg.getByte(i, j) == 0)
                {
                    float radius = sqrt((i - centerx) * (i - centerx) + (j - centery) * (j - centery));
                    points[k].radius = radius;
                    avg_radius += radius;
                    float cosine = (i - centerx) / radius;
                    float sine = (centery - j) / radius;
                    float ang = (float)atan2(sine, cosine);
                    if (ang < 0)
                        ang += TWO_PI_f;
                    points[k].ang = ang;
                    k++;
                }
            }

        qsort(points, npoints, sizeof(_AngRadius), _cmp_ang);

        points[npoints].ang = points[0].ang + TWO_PI_f;
        points[npoints].radius = points[0].radius;

        for (i = 0; i < npoints; i++)
        {
            float gap = points[i + 1].ang - points[i].ang;
            float r1 = fabs(points[i].radius);
            float r2 = fabs(points[i + 1].radius);
            float gapr = 1.f;

            if (r1 > r2 && r2 > EPS)
                gapr = r1 / r2;
            else if (r2 < r1 && r1 > EPS)
                gapr = r2 / r1;

            double c = asChar ? vars.routines.Circle_AsCharFactor : 1.0;

            if (gapr > vars.routines.Circle_GapRadiusMax * c)
            {
                getLogExt().append("Radius gap", gapr);
                delete[] points;
                return false;
            }

            if (gap > vars.routines.Circle_GapAngleMax * c && gap < 2 * PI - vars.routines.Circle_GapAngleMax * c)
            {
                getLogExt().append("C-like gap", gap);
                delete[] points;
                return false;
            }
        }

        avg_radius /= npoints;

        if (avg_radius < vars.routines.Circle_MinRadius)
        {
            getLogExt().append("Degenerated circle", avg_radius);
            delete[] points;
            return false;
        }

        float disp = 0;

        for (i = 0; i < npoints; i++)
            disp += (points[i].radius - avg_radius) * (points[i].radius - avg_radius);

        disp /= npoints;
        float ratio = sqrt(disp) / avg_radius;

#ifdef DEBUG
        printf("avgr %.3f dev %.3f ratio %.3f\n", avg_radius, sqrt(disp), ratio);
#endif

        getLogExt().append("avg_radius", avg_radius);
        radius = avg_radius;
        getLogExt().append("Ratio", ratio);

        delete[] points;
        if (ratio > vars.routines.Circle_MaxDeviation)
            return false; // not a circle
        return true;
    }

    double ImageUtils::estimateLineThickness(Image& bwimg, int grid)
    {
        int w = bwimg.getWidth();
        int h = bwimg.getHeight();
        int d = grid;

        IntVector lthick;

        if (w < d)
            d = max<int>(w >> 1, 1);

        {
            int startseg = -1;
            for (int i = 0; i < w; i += d)
            {
                for (int j = 0; j < h; j++)
                {
                    byte val = bwimg.getByte(i, j);
                    if (val == 0 && (startseg == -1))
                        startseg = j;
                    if ((val > 0 || j == (h - 1)) && startseg != -1)
                    {
                        lthick.push_back(j - startseg);
                        startseg = -1;
                    }
                }
            }
        }

        if (h > d)
            d = grid;
        else
            d = max<int>(h >> 1, 1);

        {
            int startseg = -1;
            for (int j = 0; j < h; j += d)
            {
                for (int i = 0; i < w; i++)
                {
                    byte val = bwimg.getByte(i, j);
                    if (val == 0 && (startseg == -1))
                        startseg = i;
                    if ((val > 0 || i == (w - 1)) && startseg != -1)
                    {
                        lthick.push_back(i - startseg);
                        startseg = -1;
                    }
                }
            }
        }
        sort(lthick.begin(), lthick.end());
        double thickness = 0;
        if (lthick.size() > 0)
            thickness = StatUtils::interMean(lthick.begin(), lthick.end());

        return thickness * 0.85;
    }

    // unsuccessful function, please dont use
    void ImageUtils::analizeImage(Image& img, double& predicted_len, double& predicted_count)
    {
        int h = img.getHeight(), w = img.getWidth();
        getLogExt().append("Hight = ", h);
        getLogExt().append("Width = ", w);
        int cnt1 = 0;
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
                if (img.isFilled(x, y) && (y == 0 || !img.isFilled(x, y - 1)))
                    cnt1++;
        }
        int cnt2 = 0;
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
                if (img.isFilled(x, y) && (x == 0 || !img.isFilled(x - 1, y)))
                    cnt2++;
        }
        int cnt = cnt1 + cnt2;
        getLogExt().append("Average by columns: ", cnt1 * 1. / w);
        getLogExt().append("Average by rows: ", cnt2 * 1. / h);
        if (cnt == 0)
        {
            predicted_count = predicted_len = 0;
            return;
        }
        double nl = cnt / ((sqrt(3.) + 3.) / 6.);
        double sq = 1. * h * w;
        getLogExt().append("Cnt = ", cnt);
        getLogExt().append("nl = ", nl);
        predicted_len = sqrt(pow(sq, 3) / pow(nl, 4));
        predicted_count = nl / predicted_len;
    }

    double ImageUtils::preestimateBondLen(Image& img)
    {
        int h = img.getHeight(), w = img.getWidth();

        int R = min(h, w);
        int L = 5;
        double answ = 0;
        // printf("h = %d, w = %d\n", h, w);
        vector<IntPair> vertex_set;
        while (R - L > 1)
        {
            vertex_set.clear();
            int M = (L + R) / 2;
            printf("%d ", M);
            int radius = M / 10;
            for (int x = 0; x < w; x++)
                for (int y = 0; y < h; y++)
                {
                    if (_hasRadius(img, x, y, M))
                    {
                        // printf("Radius (YES)\n");
                        bool flag = true;
                        for (auto p : vertex_set)
                            if (abs(x - p.first) + abs(y - p.second) < radius)
                                flag = false;
                        if (flag)
                            vertex_set.emplace_back(x, y);
                    }
                    else
                    { // printf("Radius (NO)\n");
                    }
                }

            int cnt = vertex_set.size();
            printf("%d\n", cnt);
            double frec = 5;
            if (cnt * M * M * frec > h * w)
                L = M; // there is enough atoms for this size of picture: cnt > (h/M) * (w/M) / frec
            else
                R = M;
            answ = max(answ, 1. * L);
        }

        return answ;
    }

    int ImageUtils::_maxRadius(Image& img, int cx, int cy)
    {
        // printf("Max radius %d %d\n", cx, cy);
        int L = 0;
        int R = min(img.getHeight(), img.getWidth());

        while (R - L > 1)
        {
            int M = (L + R) / 2;
            if (_hasRadius(img, cx, cy, M))
                L = M;
            else
                R = M;
        }
        // if (L > 0) printf("Radius (%d, %d) is %d\n", cx, cy, L);
        return L;
    }

    bool ImageUtils::_hasRadius(Image& img, int cx, int cy, double r)
    {
        // printf("Radius? %d %d\n", cx, cy);
        if (!img.isFilled(cx, cy))
            return false;
        int x, y;
        double r2;
        for (x = (int)r, y = 0, r2 = x * x - r * r; x > 0;)
        { // r2 is always iquals to (x * x + y *y - r * r)
            for (int dx = -x; dx <= x; dx += 2 * x + (x == 0))
                for (int dy = -y; dy <= y; dy += 2 * y + (y == 0))
                    if (img.in(cx + dx, cy + dy) && img.isFilled(cx + dx, cy + dy) && _isThereSegment(img, cx, cy, cx + dx, cy + dy))
                        return true;

            int rdx = r2 - 2 * x + 1;
            int rdy = r2 + 2 * y + 1;
            if (abs(rdx) < abs(rdy))
            {
                x--;
                r2 -= 2 * x - 1;
            }
            else
            {
                y++;
                r2 += 2 * y + 1;
            }
        }
        return false;
    }

    bool ImageUtils::_isThereSegment(Image& img, int x1, int y1, int x2, int y2)
    {
        // printf("Is segment %d %d %d %d\n", x1, y1, x2, y2);
        if (!img.in(x1, y1) || !img.in(x2, y2))
            return false;
        /*if (abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1) return true;
        if (!img.isFilled((x1 + x2) >> 1, (y1 + y2) >> 1)) return false;
        return _isSegment(img, x1, y1, (x1 + x2) >> 1, (y1 + y2) >> 1) && _isSegment(img, (x1 + x2) >> 1, (y1 + y2) >> 1, x2, y2);*/

        int w = abs(x1 - x2);
        int h = abs(y1 - y2);
        int len = w * h;
        int dx = sign(x2 - x1);
        int dy = sign(y2 - y1);

        int diff = 0;

        for (int x = x1, y = y1; x != x2 || y != y2;)
        {
            if (!img.isFilled(x, y))
                return false;
            if (diff == 0)
            {
                x += dx;
                y += dy;
                diff += w - h;
            }
            else if (diff < 0)
            {
                y += dy;
                diff += w;
            }
            else
            {
                x += dx;
                diff -= h;
            }
        }
        if (!img.isFilled(x2, y2))
            return false;
        return true;
    }

    Vec2i ImageUtils::_farestSegmentEnd(Image& img, Vec2i center, double thickness, bool& on_line, double& linearity, double& centrality)
    {
        // printf("thickness: %.5f", thickness);
        int cx = center.x, cy = center.y;
        Fraction MAX_VALUE(1 << 15);
        Fraction MIN_VALUE(1, 1 << 15);
        Interval VOID_INTERVAL(MAX_VALUE, MIN_VALUE);

        int max_dist_sqr = 0;
        Vec2i max_vec(center);

        vector<Vec2i> farest_in_quadrant;
        vector<int> cnt;
        for (int dx = -1; dx <= 1; dx += 2)
            for (int dy = -1; dy <= 1; dy += 2)
            {

                int max_dist_sqr_quad = 0;
                Vec2i max_vec_quad(center);

                AccumField<Interval, Interval::unite> tan_interval(VOID_INTERVAL);

                tan_interval[0][0] = Interval(MIN_VALUE, MAX_VALUE);

                bool have_proper_value = true;
                for (int x = 0; have_proper_value; x++)
                {
                    have_proper_value = false;

                    for (int y = 0; y < tan_interval[x].size(); y++)
                    {

                        if (img.isPixel(cx + x * dx, cy + y * dy))
                        {
                            if (tan_interval[x][y].is_void())
                            {
                                tan_interval[x][y] = VOID_INTERVAL;
                            }
                            else
                            {
                                have_proper_value = true;

                                // TODO FIX performance issues (copies)
                                Fraction fr11(2 * y + 1, 2 * x + 1);
                                Fraction fr12(2 * y + 1, max(2 * x - 1, 0));
                                Interval it1(fr11, fr12);

                                Fraction fr21(max(2 * y - 1, 0), 2 * x + 1);
                                Fraction fr22(2 * y + 1, 2 * x + 1);
                                Interval it2(fr21, fr22);

                                Interval iv1 = Interval::intersec(tan_interval[x][y], it1);
                                Interval iv2 = Interval::intersec(tan_interval[x][y], it2);

                                tan_interval.push_value(x, y + 1, iv1);
                                tan_interval.push_value(x + 1, y, iv2);
                            }
                        }
                        else
                            tan_interval[x][y] = VOID_INTERVAL;
                    }
                }

                int cc = 0;
                for (int x = 0; x < tan_interval.size(); x++)
                    for (int y = 0; y < tan_interval[x].size(); y++)
                        if (img.isInternal(cx + dx * x, cy + y * dy, thickness * 0.4) && !tan_interval[x][y].is_void())
                        {
                            if (x * x + y * y > max_dist_sqr_quad)
                            {
                                max_dist_sqr_quad = x * x + y * y;
                                max_vec_quad = Vec2i(cx + x * dx, cy + y * dy);
                            }
                            cc++;
                        }

                cnt.push_back(cc);
                farest_in_quadrant.push_back(max_vec_quad);
                if (max_dist_sqr_quad > max_dist_sqr)
                {
                    max_dist_sqr = max_dist_sqr_quad;
                    max_vec = max_vec_quad;
                }
                // printf("%d\n", tan_interval.size());
            }

        vector<double> lens;
        for (auto p : farest_in_quadrant)
            lens.push_back(Vec2i::distance(p, center));
        int index1, index2;
        if (lens[0] + lens[3] > lens[1] + lens[2])
            index1 = 0, index2 = 3;
        else
            index1 = 1, index2 = 2;

        on_line = lens[index1] > thickness && lens[index2] > thickness &&
                  lens[index1] + lens[index2] <= Vec2i::distance(farest_in_quadrant[index1], farest_in_quadrant[index2]) + thickness;

        double dist = Vec2i::distance(farest_in_quadrant[index1], farest_in_quadrant[index2]);
        linearity = 1. * lens[index1] * lens[index2] / (lens[index1] + lens[index2] - dist + 1) / (lens[index1] + lens[index2] - dist + 1);
        centrality = 1.;
        for (auto p : farest_in_quadrant)
        {
            double dist = Vec2i::distance(center, p);
            centrality += dist * dist * dist;
        }
        return max_vec;
    }

    void ImageUtils::_fillStopSegmentField(Image& img, Vec2i center, double thickness, vector<Vec2i>& field)
    {
        // printf("thickness: %.5f", thickness);
        int cx = center.x, cy = center.y;
        Fraction MAX_VALUE(1 << 15);
        Fraction MIN_VALUE(1, 1 << 15);
        Interval VOID_INTERVAL(MAX_VALUE, MIN_VALUE);

        field.clear();
        // vector<int> cnt;
        for (int dx = -1; dx <= 1; dx += 2)
            for (int dy = -1; dy <= 1; dy += 2)
            {

                int max_dist_sqr_quad = 0;
                Vec2i max_vec_quad(center);

                AccumField<Interval, Interval::unite> tan_interval(VOID_INTERVAL);

                tan_interval[0][0] = Interval(MIN_VALUE, MAX_VALUE);

                bool have_proper_value = true;
                for (int x = 0; have_proper_value; x++)
                {
                    have_proper_value = false;

                    for (int y = 0; y < tan_interval[x].size(); y++)
                    {

                        if (img.isPixel(cx + x * dx, cy + y * dy))
                        {
                            if (tan_interval[x][y].is_void())
                            {
                                tan_interval[x][y] = VOID_INTERVAL;
                            }
                            else
                            {
                                have_proper_value = true;
                                // TODO FIX performance issues (copies)
                                Fraction fr11(2 * y + 1, 2 * x + 1);
                                Fraction fr12(2 * y + 1, max(2 * x - 1, 0));
                                Interval iv1 = Interval::intersec(tan_interval[x][y], Interval(fr11, fr12));

                                Fraction fr21(max(2 * y - 1, 0), 2 * x + 1);
                                Fraction fr22(2 * y + 1, 2 * x + 1);
                                Interval iv2 = Interval::intersec(tan_interval[x][y], Interval(fr21, fr22));

                                tan_interval.push_value(x, y + 1, iv1);
                                tan_interval.push_value(x + 1, y, iv2);
                            }
                        }
                        else
                            tan_interval[x][y] = VOID_INTERVAL;
                    }
                }

                for (int x = 0; x < tan_interval.size(); x++)
                    for (int y = 0; y < tan_interval[x].size(); y++)
                        if (img.isInternal(cx + dx * x, cy + y * dy, thickness * 0.4) && !tan_interval[x][y].is_void())
                        {
                            if (x * x + y * y > max_dist_sqr_quad)
                            {
                                max_dist_sqr_quad = x * x + y * y;
                                max_vec_quad = Vec2i(cx + x * dx, cy + y * dy);
                            }
                        }

                field.push_back(max_vec_quad);
            }
        // printf("%d", field.size());
    }

    bool ImageUtils::_isSegment(Segment& img, double accepThick = 5)
    {
        int h = img.getHeight();
        int w = img.getWidth();

        vector<int> left_pic(h, w + 1);
        vector<int> right_pic(h, -1);

        for (int x = 0; x < w; x++)
            for (int y = 0; y < h; y++)
                if (img.isFilled(x, y))
                {
                    right_pic[y] = x;
                    if (left_pic[y] > w)
                        left_pic[y] = x;
                }

        int left_y = -1, right_y = -1;
        double max_dist = -1;
        for (int y1 = 0; y1 < h; y1++)
            for (int y2 = 0; y2 < h; y2++)
            {
                double dist = Vec2d::distance(Vec2d(left_pic[y1], y1), Vec2d(right_pic[y2], y2));
                if (dist > max_dist)
                {
                    max_dist = dist;
                    left_y = y1;
                    right_y = y2;
                }
            }

        Vec2d orient;
        orient.diff(Vec2d(right_pic[right_y], right_y), Vec2d(left_pic[left_y], left_y));
        double segment_len = orient.norm();
        if (segment_len < accepThick)
            return true;
        orient = orient.getNormalized();
        double min_cross = 0, max_cross = 0;
        for (int y = 0; y < h; y++)
        {
            double current_cross = Vec2d::cross(orient, Vec2d(left_pic[y] - left_pic[left_y], y - left_y));
            min_cross = min(min_cross, current_cross);
            max_cross = max(max_cross, current_cross);
            current_cross = Vec2d::cross(orient, Vec2d(right_pic[y] - left_pic[left_y], y - left_y));
            min_cross = min(min_cross, current_cross);
            max_cross = max(max_cross, current_cross);
        }

        return max_cross - min_cross <= sqrt(accepThick * segment_len / 3);
    }

    void ImageUtils::calulateLinearity(Image& img, vector<vector<double>>& linearity, vector<vector<double>>& centrality)
    {
        int h = img.getHeight(), w = img.getWidth();
        // printf("Starting search (%d x %d)\n", w, h);

        Image log_image(w, h);
        log_image.fillWhite();

        linearity = vector<vector<double>>(w, vector<double>(h, 0.));
        centrality = vector<vector<double>>(w, vector<double>(h, 0.));

        double thickness = estimateLineThickness(img, 1);

        for (int x = 0; x < w; x++)
        {
            if (x % 100 == 0)
                printf("%d...\n", x);
            for (int y = 0; y < h; y++)
                if (img.isFilled(x, y))
                {
                    bool flag;
                    double lin;
                    double cen;
                    _farestSegmentEnd(img, Vec2i(x, y), thickness, flag, lin, cen);
                    linearity[x][y] = lin;
                    centrality[x][y] = cen;
                }
        }
    }

    void ImageUtils::extractGraphics(Image& img, SegmentDeque& _segs, SegmentDeque& _grapics, SegmentDeque& _symbols, SegmentDeque& _lines, double bad_bond_len)
    {
        int h = img.getHeight(), w = img.getWidth();
        // printf("Starting search (%d x %d)\n", w, h);

        double thickness = estimateLineThickness(img, 1);
        double avail_line_thickness = 3 * thickness;
        vector<vector<double>> linearity;
        img.calculateLinearity(linearity);

        vector<bool> to_delete(_segs.size(), false);
        for (int i = 0; i < _segs.size(); i++)
        {
            Segment* s = _segs[i];
            int y = -1, x = -1;
            if ((y = ImageUtils::getSplitY(linearity, *s)) >= 0 || (x = ImageUtils::getSplitX(linearity, *s)) >= 0)
            {
                Segment* s1 = new Segment();
                Segment* s2 = new Segment();
                if (y >= 0)
                    s->splitHor(y, *s1, *s2);
                else
                    s->splitVert(x, *s1, *s2);
                s1->crop();
                s2->crop();
                to_delete[i] = true;
                _segs.push_back(s1);
                _segs.push_back(s2);
                to_delete.push_back(false);
                to_delete.push_back(false);
            }
        }

        SegmentDeque new_seg;
        for (int i = 0; i < _segs.size(); i++)
            if (to_delete[i])
            {
                delete _segs[i];
            }
            else
            {
                new_seg.push_back(_segs[i]);
            }
        _segs.clear();
        for (auto seg : new_seg)
            _segs.push_back(seg);

        vector<double> values;
        vector<pair<double, Segment*>> value_and_segment;
        for (auto seg : _segs)
        {
            double sum = 0;
            int cnt = 0;
            for (int x = 0; x < seg->cols; x++)
                for (int y = 0; y < seg->rows; y++)
                    if (seg->isFilled(x, y))
                    {
                        cnt++;
                        sum += linearity[seg->getX() + x][seg->getY() + y];
                    }

            if (!ImageUtils::_isSegment(*seg, avail_line_thickness) && getSegmentLinearity(linearity, *seg) > 0)
            {
                values.push_back(getSegmentLinearity(linearity, *seg));
                value_and_segment.emplace_back(values.back(), seg);
            }
        }
        double fictive_symbol = 50, fictive_graphics = 3000;
        if (bad_bond_len > 0)
        {
            fictive_graphics = pow(bad_bond_len, 4) / (8 * thickness * thickness);
            fictive_symbol = sqrt(fictive_graphics);
        }
        values.push_back(fictive_symbol);
        values.push_back(fictive_graphics);
        getLogExt().append("Thickness: ", estimateLineThickness(img, 1));
        getLogExt().append("Fictive symbol linearity: ", fictive_symbol);
        getLogExt().append("Fictive graphics linearity: ", fictive_graphics);

        sort(value_and_segment.begin(), value_and_segment.end());
        for (auto v : value_and_segment)
        {
            getLogExt().append<double>("linearity = ", v.first);
            getLogExt().appendImage("", *v.second);
        }
        vector<double> copy_values = values;

        values.clear();
        for (auto v : copy_values)
            if (v >= fictive_symbol / 2 && v <= fictive_graphics * 2)
                values.push_back(v);

        sort(values.begin(), values.end());
        int next = 0;
        int start = 0, finish = values.size() - 1;
        for (int i = 0; i < values.size() && next < values.size(); i++)
        {
            while (next < values.size() && values[next] < values[i] * 10)
                next++;
            if (next < values.size() && next - i < finish - start)
            {
                start = i;
                finish = next;
            }
        }
        // printf("start = %d, finish = %d\n", start, finish);
        int moment = start;
        for (int i = start; i < finish; i++)
            if (values[i + 1] / values[i] > values[moment + 1] / values[moment])
                moment = i;

        double splitValue = (values[moment] + values[moment + 1]) / 2;

        // printf("split value = %.5f\n", splitValue);
        int index = 0;
        _grapics.clear();
        _symbols.clear();
        _lines.clear();
        for (auto seg : _segs)
        {
            if (getSegmentLinearity(linearity, *seg) > 0)
            {
                if (ImageUtils::_isSegment(*seg, avail_line_thickness))
                    _lines.push_back(seg);
                else if (copy_values[index++] > splitValue)
                    _grapics.push_back(seg);
                else
                    _symbols.push_back(seg);
            }
        }

        vector<Vec2i> pics;
        vector<IntPair> edges;
        img._findGraph(_grapics, pics, edges);

        printf("Atoms: %d\n", pics.size());

        // writing to log
        Image graphics_image(w, h);
        Image symbols_image(w, h);
        Image lines_image(w, h);
        graphics_image.fillWhite();
        symbols_image.fillWhite();
        lines_image.fillWhite();
        for (auto seg : _grapics)
        {
            // seg->smoothing(2);
            ImageUtils::putSegment(graphics_image, *seg);
        }
        for (auto seg : _symbols)
            ImageUtils::putSegment(symbols_image, *seg);
        index = 0;
        for (auto pic : pics)
            // if (!is_intermed[index++])
            ImageDrawUtils::putCircle(graphics_image, pic.x, pic.y, 5, 0);
        for (auto seg : _lines)
            ImageUtils::putSegment(lines_image, *seg);
        getLogExt().appendImage("Graphics: ", graphics_image);
        getLogExt().appendImage("Symbols: ", symbols_image);
        getLogExt().appendImage("Lines: ", lines_image);
    }

    double ImageUtils::getSegmentLinearity(vector<std::vector<double>>& linearity, Segment& seg)
    {
        double sum = 0;
        int cnt = 0;
        for (int x = 0; x < seg.cols; x++)
            for (int y = 0; y < seg.rows; y++)
                if (seg.isFilled(x, y))
                {
                    cnt++;
                    sum += linearity[seg.getX() + x][seg.getY() + y];
                }

        /*int h = seg.getHeight(), w = seg.getWidth();
        vector<double> mid(h, 0);
        vector<double> pcnt(h, 0);
        for (int y = 0; y < h; y++) {
            double sum = 0;
            for (int x = 0; x < w; x++) if (seg.isFilled(x, y)) {
                sum += linearity[seg.getX() + x][seg.getY() + y];
                pcnt[y]++;
            }
            if (pcnt[y]) mid[y] = sum / pcnt[y]; else mid[y] = 0;
        }
        //getLogExt().appendVector("!!", mid);

        int best_y = 0;
        double best_ratio = 0;
        vector<double> ratios;
        for (int y = 10; y + 10 < h; y++) {
            double sum1 = 0, sum2 = 0;
            int cnt1 = 0, cnt2 = 0;
            for (int yy = 0; yy < h; yy++)
                if (yy <= y) {
                    sum1 += mid[yy] * pcnt[yy];
                    cnt1 += pcnt[yy];
                }
                else {
                    sum2 += mid[yy] * pcnt[yy];
                    cnt2 += pcnt[yy];
                }
            double ratio = (sum1 / cnt1) / (sum2/cnt2);
            ratio = max(ratio, 1. / ratio);
            ratio = ratio * min(cnt1, cnt2) / h / pcnt[y];
            ratios.push_back(ratio);
            if (ratio > best_ratio) {
                best_y = y;
                best_ratio = ratio;
            }
        }
        //getLogExt().appendVector("Ratios: ", ratios);

        Image log_image(seg);
        ImageDrawUtils::putLineSegment(log_image, Vec2i(0, best_y), Vec2i(w - 1, best_y), 0);

        getLogExt().append("Best ratio: ", best_ratio);
        getLogExt().append("Best y: ", best_y);
        getLogExt().appendImage("Separated segment: ", log_image);
        */
        double density = 1. * cnt / seg.rows / seg.cols;
        return sum / cnt / density / density;
    }

    int ImageUtils::getSplitCoord(vector<double>& mid, vector<int>& pcnt)
    {
        // int h = seg.getHeight(), w = seg.getWidth();

        int best_y = 0;
        double best_ratio = 0;
        vector<double> ratios;
        for (int y = 10; y + 10 < mid.size(); y++)
        {
            double sum1 = 0, sum2 = 0;
            int cnt1 = 0, cnt2 = 0;
            for (int yy = 0; yy < mid.size(); yy++)
                if (yy <= y)
                {
                    sum1 += mid[yy] * pcnt[yy];
                    cnt1 += pcnt[yy];
                }
                else
                {
                    sum2 += mid[yy] * pcnt[yy];
                    cnt2 += pcnt[yy];
                }
            double ratio = (sum1 / cnt1) / (sum2 / cnt2);
            ratio = max(ratio, 1. / ratio);
            ratio = ratio * min(cnt1, cnt2) / mid.size() / pcnt[y];
            ratios.push_back(ratio);
            if (ratio > best_ratio)
            {
                best_y = y;
                best_ratio = ratio;
            }
        }

        //        if (best_ratio > 3) return best_y;
        if (best_ratio > 5)
            return best_y;
        else
            return -1;
    }

    int ImageUtils::getSplitY(vector<std::vector<double>>& linearity, Segment& seg)
    {
        int h = seg.getHeight(), w = seg.getWidth();
        vector<double> mid(h, 0);
        vector<int> pcnt(h, 0);
        for (int y = 0; y < h; y++)
        {
            double sum = 0;
            for (int x = 0; x < w; x++)
                if (seg.isFilled(x, y))
                {
                    sum += linearity[seg.getX() + x][seg.getY() + y];
                    pcnt[y]++;
                }
            if (pcnt[y])
                mid[y] = sum / pcnt[y];
            else
                mid[y] = 0;
        }
        // getLogExt().appendVector("!!", mid);
        return getSplitCoord(mid, pcnt);
    }

    int ImageUtils::getSplitX(vector<std::vector<double>>& linearity, Segment& seg)
    {
        int h = seg.getHeight(), w = seg.getWidth();
        vector<double> mid(w, 0);
        vector<int> pcnt(w, 0);
        for (int x = 0; x < w; x++)
        {
            double sum = 0;
            for (int y = 0; y < h; y++)
                if (seg.isFilled(x, y))
                {
                    sum += linearity[seg.getX() + x][seg.getY() + y];
                    pcnt[x]++;
                }
            if (pcnt[x])
                mid[x] = sum / pcnt[x];
            else
                mid[x] = 0;
        }
        // getLogExt().appendVector("!!", mid);
        return getSplitCoord(mid, pcnt);
    }

    void ImageUtils::removeSegmentsFromDeque(SegmentDeque& from_delete, SegmentDeque& what_delete)
    {
        int w = 0, h = 0;
        for (auto seg : from_delete)
        {
            w = max(w, seg->getX() + seg->getWidth());
            h = max(h, seg->getY() + seg->getHeight());
        }
        for (auto seg : what_delete)
        {
            w = max(w, seg->getX() + seg->getWidth());
            h = max(h, seg->getY() + seg->getHeight());
        }
        int radius = 2;
        vector<vector<bool>> is_occup(w + 2 * radius, vector<bool>(h + 2 * radius, false));

        for (auto seg : what_delete)
        {
            int base_x = seg->getX(), base_y = seg->getY();
            for (int x = 0; x < seg->getWidth(); x++)
                for (int y = 0; y < seg->getHeight(); y++)
                    if (seg->isFilled(x, y))
                        for (int dx = -radius; dx <= radius; dx++)
                            for (int dy = -radius; dy <= radius; dy++)
                                is_occup[base_x + x + radius][base_y + y + radius] = true;
        }

        vector<bool> to_delete;
        for (const auto seg : from_delete)
        {
            int cnt = 0;
            int base_x = seg->getX(), base_y = seg->getY();
            for (int x = 0; x < seg->getWidth(); x++)
                for (int y = 0; y < seg->getHeight(); y++)
                    if (seg->isFilled(x, y) && is_occup[base_x + x + radius][base_y + y + radius])
                        cnt++;

            to_delete.push_back(cnt * 3 >= seg->getSquare());
        }
        SegmentDeque to_save;
        int index = 0;
        for (auto seg : from_delete)
            if (!to_delete[index++])
                to_save.push_back(seg);
        from_delete.clear();
        for (auto seg : to_save)
            from_delete.push_back(seg);
    }

    bool ImageUtils::isVertexOnEdge(Vec2i a, Vec2i b, Vec2i p, double thickness)
    {
        double A = a.y - b.y;
        double B = b.x - a.x;
        double C = a.x * b.y - a.y * b.x;
        double norm = sqrt(A * A + B * B);
        A /= norm;
        B /= norm;
        C /= norm;

        if (abs(A * p.x + B * p.y + C) >= thickness)
            return false;

        double h1 = A * a.y - B * a.x;
        double h2 = A * b.y - B * b.x;
        double h3 = A * p.y - B * p.x;

        if ((h1 - h3) * (h2 - h3) >= 0)
            return false;

        double distab = Vec2i::distance(a, b);
        double distap = Vec2i::distance(a, p);
        double distbp = Vec2i::distance(b, p);

        return distap < distab && distbp < distab;
    }
}
