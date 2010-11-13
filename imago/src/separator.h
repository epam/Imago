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

#ifndef _separator_h
#define _separator_h

#include "stl_fwd.h"

namespace imago
{
   class Segment;
   class Image;

   class Separator
   {
   public:      

      Separator( SegmentDeque &segs, const Image &img );

      void firstSeparation( SegmentDeque &layer_symbols, 
         SegmentDeque &layer_graphics );

   private:

      SegmentDeque &_segs;
      const Image &_img;

      enum
      {
         SEP_BOND,
         SEP_SYMBOL,
         SEP_SPECIAL,
         SEP_SUSPICIOUS
      };
     
      int _estimateCapHeight();
      bool _testDoubleBondV( Segment &segment );
      bool _checkSequence( IntPair &checking, IntPair &symbols_graphics, 
         double &density );
      bool _isSuspiciousSymbol( Segment *segment, SegmentDeque &layer_symbols, 
         int cap_height );
      static bool _segmentsComparator( Segment *a, Segment *b );

      Separator( const Separator &S );
   };
}


#endif /* _separator_h */