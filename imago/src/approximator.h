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

#ifndef _approximator_h
#define	_approximator_h

#include "stl_fwd.h"

namespace imago
{
   class Vec2d;

   class Approximator
   {
   public:
       static void apply( const Points &input, Points &output );
   private:
       struct _Line
       {
           double a, b, c;
       };
       static void _calc_line( const Points &input, int begin, int end, _Line &res );
       static void _prepare( const Points &poly, IntVector &sample );
   };
}
#endif /* _approximator_h */
