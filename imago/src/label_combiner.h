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
#ifndef _label_combiner_h
#define _label_combiner_h

#include <deque>
#include "stl_fwd.h"
#include "superatom.h"
#include "rectangle.h"
#include "segment.h"
#include "settings.h"

namespace imago
{
   class Segment;
   class Font;
   class CharacterRecognizer;

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

	  int MaxSymbolWidth()
	  {
		  int maxwidth = 0;
		  std::vector<Segment *>::iterator sit;
		  for(sit = symbols.begin();sit != symbols.end(); sit++)
			  if((*sit)->getWidth() > maxwidth)
				  maxwidth = (*sit)->getWidth();
		  return maxwidth;
	  }
   };

   class LabelCombiner
   {
   public:
      LabelCombiner(Settings& vars, SegmentDeque &symbols_layer, SegmentDeque &other_layer, const CharacterRecognizer &cr );
      ~LabelCombiner();
      
	  void extractLabels( std::deque<Label> &labels );

	  

   private:
      SegmentDeque &_symbols_layer;
	  SegmentDeque &_graphic_layer;
      const CharacterRecognizer &_cr;
	  double _capHeightStandardDeviation;

      std::deque<Label> _labels;
      void _locateLabels(const Settings& vars);
      void _fillLabelInfo(const Settings& vars, Label &l );
      static bool _segmentsComparator( const Segment* const &a,
                                       const Segment* const &b );

      static bool _segmentsCompareX( const Segment* const &a,
                                     const Segment* const &b );
      
   };
}
#endif /* _label_combiner_h */

