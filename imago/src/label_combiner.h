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

#ifndef _label_combiner_h
#define _label_combiner_h

#include <deque>
#include "stl_fwd.h"
#include "superatom.h"
#include "rectangle.h"

namespace imago
{
   class Segment;
   class Font;

   struct Label
   {
      std::vector<Segment*> symbols;
      Rectangle rect;
      int line_y;

      //int cap_letters_count;

      int multi_line_y;
      int multi_begin;

      Superatom satom;
      Label()
      {
         line_y = 0; //cap_letters_count = 0;
         multi_line_y = multi_begin = -1;
      }
   };

   class LabelCombiner
   {
   public:
      LabelCombiner( SegmentDeque &symbols_layer, SegmentDeque &other_layer,
                     int cap_height, const Font &fnt );
      ~LabelCombiner();
      void extractLabels( std::deque<Label> &labels );
      void setParameters( double capHeightError, double maxSymRatio,
                          double minSymRatio );
   private:
      SegmentDeque &_symbols_layer;
      const Font &_fnt;
      int _cap_height;
      int _space;

      std::deque<Label> _labels;
      void _fetchSymbols( SegmentDeque &layer );
      void _locateLabels();
      void _fillLabelInfo( Label &l );
      static bool _segmentsComparator( const Segment* const &a,
                                       const Segment* const &b );

      static bool _segmentsCompareX( const Segment* const &a,
                                     const Segment* const &b );
      //DEBUG vars
      int _imgHeight, _imgWidth;
      //
      //"Constants"
      double _cap_height_error;
      double _maxSymRatio, _minSymRatio;
   };
}
#endif /* _label_combiner_h */

