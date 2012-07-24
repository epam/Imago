#pragma once

#include <string>
#include <vector>

namespace imago
{
    static const unsigned char MAX_ATOM_ELEMENT_NUMBER = 109;

    class AtomSymbolMap
    {
		// indexed by string like "Ag" interpretted as unsigned short, the first symbol must be in UPPER case
        unsigned char SymbolMap[0xFFFF];

		// inserts element into 'Elements' and into 'SymbolMap'
		void insert(const std::string& element);

	public:
		std::vector<std::string> Elements;

    public:
        AtomSymbolMap();
        		
		// fast lookup for specified element in table
		bool lookup(const std::string& str) const;
    };

    extern AtomSymbolMap AtomMap;   
}
