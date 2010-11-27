#include "log.h"
#include "exception.h"
#include "image.h"
#include "image_utils.h"
#include "molfile_saver.h"
#include "session_manager.h"
#include "recognition_settings.h"
#include "current_session.h"
#include "molecule.h"
#include "chemical_structure_recognizer.h"
#include "output.h"

#include "../iSMILES/src/Image/Image.h"
#include "../iSMILES/src/Image/ImageFilter.h"
#include "../iSMILES/src/Image/Point.h"

#undef LMARK 
#undef LPRINT 
#undef TIME 

#define LMARK imago::getLog().mark();
#define LPRINT imago::getLog().print
#define TIME(a, msg) do { LMARK; a; LPRINT(1, msg); } while(0);

void processImage( imago::Image &img )
{
   gga::Image img1;
   
   img1.setSize(img.getWidth(), img.getHeight());

   for (int i = 0; i < img.getWidth(); i++)
      for (int j = 0; j < img.getHeight(); j++)
      {
         img1.setPixel(i, j, gga::Pixel(img.getByte(i, j)));
      }

   gga::ImageFilter flt(img1); 
   flt.prepareImageForVectorization();

   for (int i = 0; i < img.getWidth(); i++)
      for (int j = 0; j < img.getHeight(); j++)
      {
         img.getByte(i, j) = img1.getPixel(i, j).Value;
      }
}

void recognize( char *Filename )
{
   try
   {
      qword id = imago::SessionManager::getInstance().allocSID();
      imago::SessionManager::getInstance().setSID(id);
      imago::RecognitionSettings &rs = imago::getSettings();
      rs.set("DebugSession", false);

      imago::Image img;
      imago::ImageUtils::loadImageFromFile(img, Filename);
      TIME(processImage(img), "iSMILES processing");

      if (rs["DebugSession"])
      {
         imago::ImageUtils::saveImageToFile(img, "output/process_result.png");
      }

      imago::Molecule mol;

      imago::ChemicalStructureRecognizer().image2mol(img, mol);

      imago::FileOutput fo("result.mol");
      imago::MolfileSaver ma(fo);
      TIME(ma.saveMolecule(mol), "Saving molecule");

      imago::SessionManager::getInstance().releaseSID(id);
   }
   catch( imago::Exception &e )
   {
      puts(e.what());
   }
}

int main( int argc, char *argv[] )
{
   if (argc > 1)
      recognize(argv[1]);

   return 0;
}
