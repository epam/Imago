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
#ifndef _std_fwd_h
#define _std_fwd_h

#include "comdef.h"
#include "vec2d.h"


#include <deque>
#include <list>
#include <vector>
#include <utility>

// namespace std
// {
//    template<typename E> class allocator;
//    template<typename E, typename A> class vector;
//    template<typename E, typename A> class list;
//    template<typename E, typename A> class deque;
//    template<typename T1, typename T2> struct pair;
// }

namespace imago
{
   class Segment;

typedef std::list<int, std::allocator<int> > IntList;
typedef std::vector<int, std::allocator<int> > IntVector;
typedef std::vector<char, std::allocator<char> > CharVector;
typedef std::deque<int, std::allocator<int> > IntDeque;
typedef std::vector<double, std::allocator<double> > DoubleVector;
typedef std::list<Segment *, std::allocator<Segment *> > SegmentList;
typedef std::deque<Segment *, std::allocator<Segment *> > SegmentDeque;
typedef std::vector<Vec2d, std::allocator<Vec2d> > Points2d;
typedef std::vector<Vec2i, std::allocator<Vec2i> > Points2i;
typedef std::pair<int, int> IntPair;

// #define FWD_DECL(Container, Type, Name) typedef std::Container<Type, std::allocator<Type> > Name
//    FWD_DECL(list, int, IntList);
//    FWD_DECL(vector, int, IntVector);
//    FWD_DECL(vector, char, CharVector);
//    FWD_DECL(deque, int, IntDeque);
//    FWD_DECL(vector, double, DoubleVector);
//    FWD_DECL(list, Segment *, SegmentList);
//    FWD_DECL(deque, Segment *, SegmentDeque);
//    FWD_DECL(vector, Vec2d, Points2d);
//    FWD_DECL(vector, Vec2i, Points2i);
}


#endif /* _std_fwd_h_ */
