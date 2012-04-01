#include <iostream>

#include "comdef.h"
#include "session_manager.h"
#include "current_session.h"
#include "chemical_structure_recognizer.h"
#include "image_utils.h"
#include "prefilter.h"
#include "superatom_expansion.h"
#include "output.h"


using namespace imago;

int main(int argc, char **argv)
{
   try
   {
      qword sid = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(sid);
      getSettings()["DebugSession"] = true;
      Image img;

      const char *f = (argc == 2)?argv[1]:"../../../tests/vs/TestImages/TS_3_iPad_2_1.JPG";

      //getSettings()["Filter"] = "blur"; //for 34!
      ChemicalStructureRecognizer &csr = getRecognizer();

      ImageUtils::loadImageFromFile(img, f);
      
      prefilterImage(img, csr.getCharacterRecognizer());
      Molecule &mol = gSession.get()->mol();

      csr.image2mol(img, mol);

      std::string molfile = expandSuperatoms(mol);

      FileOutput fout("molecule.mol");
      fout.writeString(molfile);

      SessionManager::getInstance().releaseSID(sid);
   }
   catch (std::exception &e)
   {
      std::cout << e.what() << "\n";
   }
   
   return 0;
}