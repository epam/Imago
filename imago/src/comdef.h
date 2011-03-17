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

/**
 * @file   comdef.h
 * 
 * @brief  Common definitions
 */

#ifndef _comdef_h
#define _comdef_h

#define DO_LOG

#ifndef NDEBUG
#define DEBUG
#define DPRINTF printf
#define DFPRINTF fprintf
#else
#undef DEBUG
#define DPRINTF(...)
#define DFPRINTF(...)
#endif

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
   const int MAX_LINE = 1024;
   
   const double PI = 3.14159265358979323846;
   const double PI_2 = 1.57079632679489661923;
   const double PI_4 = 0.78539816339744830962;

   template <typename T> T absolute( const T &a )
   {
      return a > 0 ? a : -a;
   }
}

#include "boost/graph/properties.hpp"
namespace boost
{
   enum vertex_seg_ptr_t { vertex_seg_ptr };
   enum vertex_pos_t { vertex_pos };
   enum edge_type_t { edge_type };
   BOOST_INSTALL_PROPERTY(vertex, seg_ptr);
   BOOST_INSTALL_PROPERTY(vertex, pos);
   BOOST_INSTALL_PROPERTY(edge, type);
}

#define __max(a, b) (((a) < (b)) ? (b) : (a))
#define __min(a, b) (((a) < (b)) ? (a) : (b))

#endif /* _comdef_h */
