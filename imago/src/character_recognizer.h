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
#include "symbol_features.h"
#include "segment.h"
#include "stl_fwd.h"
#include "recognition_distance.h"
#include "segment_tools.h"
#include "settings.h"

namespace imago
{
   class Segment;   
	
   class CharacterRecognizer
   {
   public:
	  bool isPossibleCharacter(const Settings& vars, const Segment& seg, 
		                       bool loose_cmp = false, char* result = NULL);  

      RecognitionDistance recognize(const Settings& vars, const Segment &seg, 
									const std::string &candidates = all) const;

	  virtual ~CharacterRecognizer() { };

      static const std::string upper; 
	  static const std::string lower;
	  static const std::string digits;
	  static const std::string charges;
	  static const std::string all;
	  static const std::string brackets;
	  static const std::string like_bonds;

   private:
	   static qword getSegmentHash(const Segment &seg, const std::string& candidates);
   };

}

#endif /* _character_recognizer_h */
