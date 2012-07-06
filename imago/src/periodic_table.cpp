#include <memory.h>
#include "periodic_table.h"

namespace imago
{
    unsigned char AtomSymbolMap::SymbolMap[0xFFFF]; 

    AtomSymbolMap AtomMap;

	bool AtomSymbolMap::lookup(const std::string& str) const
	{
		char c_str[4] = {0};
		strcpy_s(c_str, 3, str.c_str());
		return SymbolMap[*(unsigned short*)c_str] != 0;
	}

    AtomSymbolMap::AtomSymbolMap()
    {
        unsigned char n = 1;
        memset(SymbolMap, 0, sizeof(SymbolMap));
        SymbolMap[*(unsigned short*)"H" ] = n++;
        SymbolMap[*(unsigned short*)"He"] = n++;  //2
        SymbolMap[*(unsigned short*)"Li"] = n++;
        SymbolMap[*(unsigned short*)"Be"] = n++;
        SymbolMap[*(unsigned short*)"B" ] = n++;
        SymbolMap[*(unsigned short*)"C" ] = n++;
        SymbolMap[*(unsigned short*)"N" ] = n++;
        SymbolMap[*(unsigned short*)"O" ] = n++;
        SymbolMap[*(unsigned short*)"F" ] = n++;
        SymbolMap[*(unsigned short*)"Ne"] = n++;  //10
        SymbolMap[*(unsigned short*)"Na"] = n++;
        SymbolMap[*(unsigned short*)"Mg"] = n++;
        SymbolMap[*(unsigned short*)"Al"] = n++;
        SymbolMap[*(unsigned short*)"Si"] = n++;
        SymbolMap[*(unsigned short*)"P" ] = n++;
        SymbolMap[*(unsigned short*)"S" ] = n++;
        SymbolMap[*(unsigned short*)"Cl"] = n++;
        SymbolMap[*(unsigned short*)"Ar"] = n++;  //18
        SymbolMap[*(unsigned short*)"K" ] = n++;
        SymbolMap[*(unsigned short*)"Ca"] = n++;
        SymbolMap[*(unsigned short*)"Sc"] = n++;
        SymbolMap[*(unsigned short*)"Ti"] = n++;
        SymbolMap[*(unsigned short*)"V" ] = n++;
        SymbolMap[*(unsigned short*)"Cr"] = n++;
        SymbolMap[*(unsigned short*)"Mn"] = n++;
        SymbolMap[*(unsigned short*)"Fe"] = n++;
        SymbolMap[*(unsigned short*)"Co"] = n++;
        SymbolMap[*(unsigned short*)"Ni"] = n++;  //28
        SymbolMap[*(unsigned short*)"Cu"] = n++;
        SymbolMap[*(unsigned short*)"Zn"] = n++;
        SymbolMap[*(unsigned short*)"Ga"] = n++;
        SymbolMap[*(unsigned short*)"Ge"] = n++;
        SymbolMap[*(unsigned short*)"As"] = n++;
        SymbolMap[*(unsigned short*)"Se"] = n++;
        SymbolMap[*(unsigned short*)"Br"] = n++;
        SymbolMap[*(unsigned short*)"Kr"] = n++;  //36
        SymbolMap[*(unsigned short*)"Rb"] = n++;
        SymbolMap[*(unsigned short*)"Sr"] = n++;
        SymbolMap[*(unsigned short*)"Y" ] = n++;
        SymbolMap[*(unsigned short*)"Zr"] = n++;
        SymbolMap[*(unsigned short*)"Nb"] = n++;
        SymbolMap[*(unsigned short*)"Mo"] = n++;
        SymbolMap[*(unsigned short*)"Tc"] = n++;
        SymbolMap[*(unsigned short*)"Ru"] = n++;
        SymbolMap[*(unsigned short*)"Rh"] = n++;
        SymbolMap[*(unsigned short*)"Pd"] = n++;  //46
        SymbolMap[*(unsigned short*)"Ag"] = n++;
        SymbolMap[*(unsigned short*)"Cd"] = n++;
        SymbolMap[*(unsigned short*)"In"] = n++;
        SymbolMap[*(unsigned short*)"Sn"] = n++;
        SymbolMap[*(unsigned short*)"Sb"] = n++;
        SymbolMap[*(unsigned short*)"Te"] = n++;
        SymbolMap[*(unsigned short*)"I" ] = n++;
        SymbolMap[*(unsigned short*)"Xe"] = n++;  //54
        SymbolMap[*(unsigned short*)"Cs"] = n++;
        SymbolMap[*(unsigned short*)"Ba"] = n++;

        SymbolMap[*(unsigned short*)"La"] = n++;  //57
        SymbolMap[*(unsigned short*)"Ce"] = n++;
        SymbolMap[*(unsigned short*)"Pr"] = n++;
        SymbolMap[*(unsigned short*)"Nd"] = n++;
        SymbolMap[*(unsigned short*)"Pm"] = n++;
        SymbolMap[*(unsigned short*)"Sm"] = n++;
        SymbolMap[*(unsigned short*)"Eu"] = n++;
        SymbolMap[*(unsigned short*)"Gd"] = n++;
        SymbolMap[*(unsigned short*)"Tb"] = n++;
        SymbolMap[*(unsigned short*)"Dy"] = n++;
        SymbolMap[*(unsigned short*)"Ho"] = n++;
        SymbolMap[*(unsigned short*)"Er"] = n++;
        SymbolMap[*(unsigned short*)"Tm"] = n++;
        SymbolMap[*(unsigned short*)"Yb"] = n++;
        SymbolMap[*(unsigned short*)"Lu"] = n++;  //71

        SymbolMap[*(unsigned short*)"Hf"] = n++;
        SymbolMap[*(unsigned short*)"Ta"] = n++;
        SymbolMap[*(unsigned short*)"W" ] = n++;
        SymbolMap[*(unsigned short*)"Re"] = n++;
        SymbolMap[*(unsigned short*)"Os"] = n++;
        SymbolMap[*(unsigned short*)"Ir"] = n++;
        SymbolMap[*(unsigned short*)"Pt"] = n++;  //78
        SymbolMap[*(unsigned short*)"Au"] = n++;
        SymbolMap[*(unsigned short*)"Hg"] = n++;
        SymbolMap[*(unsigned short*)"Tl"] = n++;
        SymbolMap[*(unsigned short*)"Pb"] = n++;
        SymbolMap[*(unsigned short*)"Bi"] = n++;
        SymbolMap[*(unsigned short*)"Po"] = n++;
        SymbolMap[*(unsigned short*)"At"] = n++;
        SymbolMap[*(unsigned short*)"Rn"] = n++;  //86
        SymbolMap[*(unsigned short*)"Fr"] = n++;
        SymbolMap[*(unsigned short*)"Ra"] = n++;

        SymbolMap[*(unsigned short*)"Ac"] = n++;  //89
        SymbolMap[*(unsigned short*)"Th"] = n++;
        SymbolMap[*(unsigned short*)"Pa"] = n++;
        SymbolMap[*(unsigned short*)"U" ] = n++;
        SymbolMap[*(unsigned short*)"Np"] = n++;
        SymbolMap[*(unsigned short*)"Pu"] = n++;
        SymbolMap[*(unsigned short*)"Am"] = n++;
        SymbolMap[*(unsigned short*)"Cm"] = n++;
        SymbolMap[*(unsigned short*)"Bk"] = n++;
        SymbolMap[*(unsigned short*)"Cf"] = n++;
        SymbolMap[*(unsigned short*)"Es"] = n++;
        SymbolMap[*(unsigned short*)"Fm"] = n++;
        SymbolMap[*(unsigned short*)"Md"] = n++;
        SymbolMap[*(unsigned short*)"No"] = n++;
        SymbolMap[*(unsigned short*)"Lr"] = n++;  //103

        SymbolMap[*(unsigned short*)"Rf"] = n++;
        SymbolMap[*(unsigned short*)"Db"] = n++;
        SymbolMap[*(unsigned short*)"Sg"] = n++;
        SymbolMap[*(unsigned short*)"Bh"] = n++;
        SymbolMap[*(unsigned short*)"Hn"] = n++;
        SymbolMap[*(unsigned short*)"Mt"] = n;    //109

#ifdef DEBUG
        if(MAX_ATOM_ELEMENT_NUMBER !=n)
            throw -1;
#endif
    }
}

