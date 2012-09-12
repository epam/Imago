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
#ifndef _character_recognizer_data_h
#define _character_recognizer_data_h

#include <vector>
#include "symbol_features.h"
#include <istream>

namespace imago
{
   class CharacterRecognizerData
   {
   public:

		struct SymbolClass
		{
			char sym;
			std::vector<SymbolFeatures> shapes;
		};
      CharacterRecognizerData(): _loaded(false) {};

	  void LoadData( std::istream &in );

   protected:
	   bool _loaded;
	   int _count;
	   std::vector<SymbolClass> _classes;
	   std::vector<int> _mapping;	   
   };
}

#endif //_character_recognizer_data_h
