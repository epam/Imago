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
 * @file   comdef.h
 *
 * @brief  Common definitions
 */

#pragma once

#include <algorithm>
#include <string>

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#define qword unsigned _int64
#else
#define DLLEXPORT
#define qword unsigned long long
#endif /* _WIN32 */

namespace imago
{
    typedef unsigned char byte;
    typedef unsigned short word;
    typedef unsigned int dword;

    const double EPS = 1e-10;
    const double DIST_INF = 1e10;
    const unsigned int MAX_TEXT_LINE = 1024;

    const double PI = 3.14159265358979323846;
    const float TWO_PI_f = 6.2831853071794f;
    const double HALF_PI = 1.57079632679489661923;

    template <typename T>
    int round(const T& a)
    {
        if (a >= 0)
            return (int)(a + 0.5);
        else
            return (int)(a - 0.5);
    }

    template <typename T>
    T absolute(const T& a)
    {
        return a > 0 ? a : -a;
    }

    template <typename T>
    int sign(const T& x)
    {
        return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
    }

    template <typename T>
    T square(const T& a)
    {
        return a * a;
    }

    static inline std::string upper(const std::string& in)
    {
        std::string data = in;
        std::transform(data.begin(), data.end(), data.begin(), ::toupper);
        return data;
    }

    static inline std::string lower(const std::string& in)
    {
        std::string data = in;
        std::transform(data.begin(), data.end(), data.begin(), ::tolower);
        return data;
    }
}
