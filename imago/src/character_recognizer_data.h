#pragma once

#include <vector>
#include "symbol_features.h"

namespace imago
{
	class FontRecognizerData
	{
	public:
		void initializeArial();
		void initializeArialBold();
		void initializeSerif();

      struct FontItem
      {
         char sym;
         SymbolFeatures features;
      };

	  FontRecognizerData();

	protected:
		int _count;
		std::vector<FontItem> _symbols;
		std::vector<int> _mapping;      
	};

   class CharacterRecognizerData
   {
   public:
		void initializeHandwrittenFont();

		struct SymbolClass
		{
			char sym;
			std::vector<SymbolFeatures> shapes;
		};
		CharacterRecognizerData();

   protected:
	   bool _loaded;
	   int _count;
	   std::vector<SymbolClass> _classes;
	   std::vector<int> _mapping;	   
   };
}