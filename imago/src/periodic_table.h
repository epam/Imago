#pragma once

#include <string>

namespace imago
{
    static const unsigned char MAX_ATOM_ELEMENT_NUMBER = 109;

    class AtomSymbolMap
    {
		// indexed by string like "Ag" interpretted as unsigned short, the first symbol must be in UPPER case
        static unsigned char SymbolMap[0xFFFF];

    public:
        AtomSymbolMap();
        
		inline unsigned char operator [] (unsigned short i) const
		{
			return SymbolMap[i];
		}
		
		bool lookup(const std::string& str) const;
    };

    extern AtomSymbolMap AtomMap;   
}
