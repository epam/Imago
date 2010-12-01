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
#include "../iSMILES/src/Image/FileJPG.h"
#include "../iSMILES/src/Image/FilePNG.h"

#undef LMARK 
#undef LPRINT 
#undef TIME 

#define LMARK imago::getLog().mark();
#define LPRINT imago::getLog().print
#define TIME(a, msg) do { LMARK; a; LPRINT(1, msg); } while(0);

void convert( gga::Image &a, imago::Image &b )
{
   b.init(a.getWidth(), a.getHeight());
   b.fillWhite();

   for (int i = 0; i < b.getWidth(); i++)
      for (int j = 0; j < b.getHeight(); j++)
      {
         b.getByte(i, j) = a.getPixel(i, j).Value;
      }
}

void recognize(const char *Filename, const char *output)
{
   try
   {
      qword id = imago::SessionManager::getInstance().allocSID();
      imago::SessionManager::getInstance().setSID(id);
      imago::RecognitionSettings &rs = imago::getSettings();
      rs.set("DebugSession", false);

      imago::Image img;

      //Load JPG image in iSMILES image structure
      gga::Image original_img;
      gga::FileJPG().load(Filename, &original_img);

      original_img.resizeLinear(3);
      
      //Process image using iSMILES
      gga::ImageFilter flt(original_img);
      
      flt.Parameters.ImageSize = 10000;
      
      TIME(flt.prepareImageForVectorization(), "iSMILES processing");

      //gga::FilePNG().save(output, original_img);

      //Back to imago Image type
      convert(original_img, img);

      if (rs["DebugSession"])
      {
         imago::ImageUtils::saveImageToFile(img, "output/process_result.png");
      }

      //Recognize molecule
      imago::Molecule mol;
      const char *fontfile = "TEST3.font"; //TODO: Set correct path
      imago::ChemicalStructureRecognizer().image2mol(img, mol);

      //Save result
      //imago::FileOutput fo("result.mol");
      imago::StandardOutput fo;
      imago::MolfileSaver ma(fo);
      TIME(ma.saveMolecule(mol), "Saving molecule");

      imago::SessionManager::getInstance().releaseSID(id);
   }
   catch( imago::Exception &e )
   {
      puts(e.what());
   }
}

/*
int main ( int argc, char *argv[] )
{
   if (argc > 1)
      recognize(argv[1]);

   return 0;
}
*/
