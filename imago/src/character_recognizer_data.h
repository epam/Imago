#pragma once

#include <vector>
#include "symbol_features.h"

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

   protected:
	   bool _loaded;
	   int _count;
	   std::vector<SymbolClass> _classes;
	   std::vector<int> _mapping;	   
   };
}