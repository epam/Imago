#ifndef _superatom_expansion_h
#define _superatom_expansion_h

#include <string>

namespace imago
{
	class Molecule;
	
	std::string expandSuperatoms(const Molecule &mol);
}

#endif