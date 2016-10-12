/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
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
