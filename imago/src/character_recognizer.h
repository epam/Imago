/****************************************************************************
 * Copyright (C) 2009-2012 GGA Software Services LLC
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
#ifndef _character_recognizer_h
#define _character_recognizer_h

#include <string>
#include <vector>
#include <map>
#include "character_recognizer_data.h"
#include "symbol_features.h"
#include "segment.h"
#include "stl_fwd.h"
#include "recognition_distance.h"
#include "segment_tools.h"
#include "settings.h"
#include "contour_template.h"

namespace imago
{
   class Segment;   
	
   class CharacterRecognizer: CharacterRecognizerData
   {
   public:
	  bool isPossibleCharacter(const Settings& vars, const Segment& seg, bool loose_cmp = false, char* result = NULL);  

      CharacterRecognizer( int classesCount );
      CharacterRecognizer( int classesCount, const std::string &filename );
      
      RecognitionDistance recognize(const Settings& vars, const Segment &seg, 
									const std::string &candidates = all,
									bool can_adjust = true) const;

      ~CharacterRecognizer();

      static const std::string upper; 
	  static const std::string lower;
	  static const std::string digits;
	  static const std::string charges;
	  static const std::string all;
	  static const std::string brackets;
	  static const std::string like_bonds;

   private:
	   RecognitionDistance _recognize(const Settings& vars, const SymbolFeatures &features,
									  const std::string &candidates, bool wide_range = false ) const;

       static double _compareFeatures(const Settings& vars,  const SymbolFeatures &f1,
		                              const SymbolFeatures &f2 );

	   static double _compareDescriptors(const Settings& vars,  const std::vector<double> &d1,
										 const std::vector<double> &d2 );      
	   bool IsParenthesis(const Settings& vars, ComplexContour &cc, bool &isLeft) const;
	   
	   int _classesCount;
   };

}

#endif /* _character_recognizer_h */
