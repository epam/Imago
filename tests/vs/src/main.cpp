#include <iostream>

#include "comdef.h"
#include "chemical_structure_recognizer.h"
#include "image_utils.h"
#include "prefilter.h"
#include "superatom_expansion.h"
#include "output.h"
#include "molecule.h"

using namespace imago;

int main(int argc, char **argv)
{
   try
   {
      Image img;

      const char *f = (argc == 2)?argv[1]:"../../../tests/vs/TestImages/TS_3_iPad_2_1.JPG";
      
      ChemicalStructureRecognizer csr;

      ImageUtils::loadImageFromFile(img, f);
      
	  Settings vars;

      prefilterImage(vars, img, csr.getCharacterRecognizer());
      Molecule mol;

      csr.image2mol(vars, img, mol);

      std::string molfile = expandSuperatoms(vars, mol);

      FileOutput fout("molecule.mol");
      fout.writeString(molfile);      
   }
   catch (std::exception &e)
   {
      std::cout << e.what() << "\n";
   }
   
   return 0;
}