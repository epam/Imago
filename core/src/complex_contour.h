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
 * @file   complex_number.h
 *
 * @brief  Complex numbers
 */

#pragma once

#include <sstream>
#include <vector>

#include "complex_number.h"
#include "graphics_detector.h"
#include "settings.h"
#include "stl_fwd.h"

namespace imago
{

    class ComplexContour
    {
    public:
        ComplexContour(void);
        ComplexContour(const std::vector<ComplexNumber>& conts) : _contours(conts)
        {
        }

        ComplexContour(const std::string& data)
        {
            std::stringstream s(data);
            double real, im;
            _contours.clear();

            while (!s.eof())
            {
                s >> real;
                s >> im;
                ComplexNumber c(real, im);
                _contours.push_back(c);
            }
        }

        ~ComplexContour(void);

        ComplexNumber& getContour(size_t shift);
        const ComplexNumber& getContour(size_t shift) const;

        double DiffR2(const ComplexContour& lc) const;

        double Norm() const;

        ComplexNumber Dot(const ComplexContour& c, size_t shift = 0) const;

        std::vector<ComplexNumber> InterCorrelation(const ComplexContour& c);

        std::vector<ComplexNumber> AutoCorrelation(bool normalize);

        ComplexNumber FindMaxNorm() const;

        void Scale(double scale);

        void Normalize();

        void NormalizeByPerimeter();

        double getNorm() const;

        double Distance(const ComplexContour& c);

        void Equalize(int n);

        static ComplexContour RetrieveContour(const Settings& vars, Image& seg, bool fine_detail = false);

        ComplexNumber NormDot(const ComplexContour& c) const
        {
            int count = (int)_contours.size();
            double norm1 = 0, norm2 = 0;
            ComplexNumber S;

            for (int i = 0; i < count; i++)
            {
                S += ComplexNumber::Dot(_contours[i], c.getContour(i));
                norm1 += _contours[i].getRadius2();
                norm2 += c.getContour(i).getRadius2();
            }

            double k = 1.0 / std::sqrt(norm1 * norm2);
            S *= k;
            return S;
        }

        size_t Size() const
        {
            return _contours.size();
        }

    private:
        void EqualizeUp(size_t n);
        void EqualizeDown(size_t n);
        std::vector<ComplexNumber> _contours;
    };
}
