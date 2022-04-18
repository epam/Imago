/****************************************************************************
* Copyright (C) from 2009 to Present EPAM Systems.
*
* This file is part of Imago toolkit.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***************************************************************************/

#pragma once
#ifndef _periodic_table_h
#define _periodic_table_h

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

#endif //_periodic_table_h
