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

#include "periodic_table.h"

#include <memory.h>
#include <cstdint>

namespace imago
{
    AtomSymbolMap AtomMap;

    bool AtomSymbolMap::lookup(const std::string& str) const
    {
        char c_str[2] = {0};
        for (size_t c = 0; c < str.size() && c < 2; c++)
            c_str[c] = str[c];
        return SymbolMap[*(uint16_t*)c_str] != 0;
    }

    void AtomSymbolMap::insert(const std::string& element)
    {
        Elements.push_back(element);
        char c_str[2] = {0};
        for (size_t c = 0; c < element.size() && c < 2; c++)
            c_str[c] = element[c];
        SymbolMap[*(uint16_t*)(c_str)] = (unsigned char)Elements.size();
    }

    AtomSymbolMap::AtomSymbolMap()
    {
        memset(SymbolMap, 0, sizeof(SymbolMap));
        insert("H");
        insert("He");
        insert("Li");
        insert("Be");
        insert("B");
        insert("C");
        insert("N");
        insert("O");
        insert("F");
        insert("Ne");
        insert("Na");
        insert("Mg");
        insert("Al");
        insert("Si");
        insert("P");
        insert("S");
        insert("Cl");
        insert("Ar");
        insert("K");
        insert("Ca");
        insert("Sc");
        insert("Ti");
        insert("V");
        insert("Cr");
        insert("Mn");
        insert("Fe");
        insert("Co");
        insert("Ni");
        insert("Cu");
        insert("Zn");
        insert("Ga");
        insert("Ge");
        insert("As");
        insert("Se");
        insert("Br");
        insert("Kr");
        insert("Rb");
        insert("Sr");
        insert("Y");
        insert("Zr");
        insert("Nb");
        insert("Mo");
        insert("Tc");
        insert("Ru");
        insert("Rh");
        insert("Pd");
        insert("Ag");
        insert("Cd");
        insert("In");
        insert("Sn");
        insert("Sb");
        insert("Te");
        insert("I");
        insert("Xe");
        insert("Cs");
        insert("Ba");
        insert("La");
        // insert("Ce");
        insert("Pr");
        insert("Nd");
        insert("Pm");
        insert("Sm");
        insert("Eu");
        insert("Gd");
        insert("Tb");
        insert("Dy");
        insert("Ho");
        insert("Er");
        insert("Tm");
        insert("Yb");
        insert("Lu");
        insert("Hf");
        insert("Ta");
        insert("W");
        insert("Re");
        insert("Os");
        insert("Ir");
        insert("Pt");
        insert("Au");
        insert("Hg");
        insert("Tl");
        insert("Pb");
        insert("Bi");
        insert("Po");
        insert("At");
        insert("Rn");
        insert("Fr");
        insert("Ra");
        insert("Ac");
        insert("Th");
        insert("Pa");
        insert("U");
        insert("Np");
        insert("Pu");
        insert("Am");
        insert("Cm");
        insert("Bk");
        insert("Cf");
        insert("Es");
        insert("Fm");
        insert("Md");
        insert("No");
        insert("Lr");
        insert("Rf");
        insert("Df");
        insert("Sg");
        insert("Bh");
        insert("Hn");
        insert("Mt");
    }
}
