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

#include <vector>

#ifndef _accum_field_h_
#define _accum_field_h_

template <typename ValueType, ValueType operation(const ValueType&, const ValueType&)>
class AccumLine
{
private:
    std::vector<ValueType> line;
    const ValueType neitral_element;

public:
    AccumLine()
    {
        line.clear();
    }
    AccumLine(ValueType ne_) : neitral_element(ne_)
    {
        line.clear();
    }

    ValueType& operator[](int x)
    {
        // if (x < 0) throw Exception("AccumLine: Negative index");
        while (line.size() <= x)
            line.push_back(neitral_element);
        return line[x];
    }

    void push_value(int x, ValueType& value)
    {
        (*this)[x] = operation((*this)[x], value);
    }
    int size()
    {
        return line.size();
    }
};

template <typename ValueType, ValueType operation(const ValueType&, const ValueType&)>
class AccumField
{
private:
    std::vector<AccumLine<ValueType, operation>> field;
    const ValueType neitral_element;

public:
    typedef AccumLine<ValueType, operation> local_line;

    AccumField()
    {
        field.clear();
    }
    AccumField(ValueType ne_) : neitral_element(ne_)
    {
        field.clear();
    }

    local_line& operator[](int x)
    {
        // if (x < 0) throw Exception("AccumField: Negative index");
        while (field.size() <= x)
            field.push_back(local_line(neitral_element));
        return field[x];
    }

    void push_value(int x, int y, ValueType& value)
    {
        ValueType& current_value = (*this)[x][y];
        current_value = operation(current_value, value);
    }

    bool is_proper_value(ValueType& x)
    {
        return x != neitral_element;
    }
    bool is_proper_value(int x, int y)
    {
        return x < field.size() && y < field[x].size() && is_proper_value(field[x][y]);
    }
    int size()
    {
        return field.size();
    }
};

#endif /* _math_h */
