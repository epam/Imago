#ifndef _superatom_expansion_h
#define _superatom_expansion_h

#include <string>
#include "constants.h"

namespace imago
{
	class Molecule;
	
	std::string expandSuperatoms(const Settings& vars, const Molecule &mol);
}

#endif