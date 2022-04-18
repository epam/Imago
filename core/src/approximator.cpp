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

#include "approximator.h"

#include <cmath>
#include <deque>
#include <utility>
#include <vector>

#include <opencv2/opencv.hpp>

#include "algebra.h"
#include "image.h"
#include "image_draw_utils.h"
#include "image_utils.h"

using namespace imago;

void CvApproximator::apply(const Settings& vars, double eps, const Points2d& input, Points2d& output) const
{
    std::vector<cv::Point> vcurve;
    for (size_t i = 0; i < input.size(); i++)
        vcurve.push_back(cv::Point(round(input[i].x), round(input[i].y)));

    bool closed = (vcurve[0] == vcurve[vcurve.size() - 1]);
    cv::Mat curve(vcurve);
    std::vector<cv::Point> approxCurve;
    cv::approxPolyDP(curve, approxCurve, eps, closed);

    output.clear();
    for (size_t i = 0; i < approxCurve.size(); i++)
        output.push_back(Vec2d(approxCurve[i].x, approxCurve[i].y));
    if (closed)
        output.push_back(Vec2d(output[0]));
}

void DPApproximator::_apply_int(double eps, const Points2d& input, Points2d& output) const
{
    using namespace std;
    deque<pair<int, int>> stack;
    int l, r;
    int i;

    output.clear();
    stack.push_back(make_pair(0, (int)input.size() - 1));

    while (stack.size() > 0)
    {
        std::tie(l, r) = stack.back();
        stack.pop_back();

        const Vec2d &lp = input[l], &rp = input[r];
        int max_ind = -1, max_dist = (int)eps;
        for (i = l + 1; i < r; ++i)
        {
            // Suppose, all points lay between left and right points.
            double d = Algebra::distance2segment(input[i], lp, rp);
            if (d > max_dist)
            {
                max_dist = (int)d;
                max_ind = i;
            }
        }

        if (max_ind != -1)
        {
            stack.push_back(make_pair(max_ind, r));
            stack.push_back(make_pair(l, max_ind));
        }
        else
        {
            output.push_back(input[l]);
        }
    }
    output.push_back(input.back());
}

void DPApproximator::apply(const Settings& vars, double eps, const Points2d& input, Points2d& output) const
{
    assert(input.size() > 1);
    output.clear();

    if (input.front() == input.back())
    {
        if (input.size() < 4)
        {
            output.push_back(input[0]);
            output.push_back(input[1]);
        }
        else
        {
            // Or find two farthest points on contour
            size_t half = input.size() / 2;
            Points2d ifirst(input.begin(), input.begin() + half), isecond(input.begin() + half, input.end());

            Points2d ofirst, osecond;
            _apply_int(eps, ifirst, ofirst);
            _apply_int(eps, isecond, osecond);

            bool joinFirst, joinLast;
            joinFirst = joinLast = false;

            if (Algebra::distance2segment(ofirst.front(), ofirst[1], osecond[osecond.size() - 2]) < eps)
            {
                // merging first segment from ofirst and last from osecond
                ofirst.erase(ofirst.begin());
                osecond[osecond.size() - 1] = ofirst.front();
            }

            if (ofirst.size() > 2 && osecond.size() > 2 && Algebra::distance2segment(ofirst.back(), ofirst[ofirst.size() - 2], osecond.front()) < eps)
            {
                // merging last segment from ofirst and first from osecond
                osecond.erase(osecond.begin());
                ofirst[ofirst.size() - 1] = osecond.front();
            }

            output.insert(output.begin(), ofirst.begin(), ofirst.end());
            output.insert(output.end(), osecond.begin() + 1, osecond.end());
        }
    }
    else
    {
        _apply_int(eps, input, output);
    }
}
