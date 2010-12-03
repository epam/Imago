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

void recognize(const char *Filename, const char *output, const char *font_path)
{
   try
   {
      qword id = imago::SessionManager::getInstance().allocSID();
      imago::SessionManager::getInstance().setSID(id);
      imago::RecognitionSettings &rs = imago::getSettings();
      rs.set("DebugSession", false);

      imago::getLog().reset();

      LMARK;
      LPRINT(0 , "Let the recognition begin");

      imago::Image img;

      //Load JPG image in iSMILES image structure
      gga::Image original_img;
      gga::FileJPG().load(Filename, &original_img);

      TIME(original_img.resizeLinear(3), "iSMILES resize");
      
      printf("Orientation: %i\n", original_img.getOrientation());
      
      
      int angle = 0;
      switch(original_img.getOrientation())
      {
         case 1: // standard orientation, do nothing
         case 2: // flipped right-left
            break;
         case 3: // rotated 180
            angle = 180;
            break;
         case 4: // flipped top-bottom
         case 5: // flipped diagonally around '\'
            break;
         case 6: // 90 CW
            angle = 90;
            break;
         case 7: // flipped diagonally around '/'
            break;
         case 8: // 90 CCW
            angle = 270;
            break;
         case -1:    //not found
         default:    // shouldn't happen
            break;
      }
      
      if(angle != 0)
      {
         const gga::Image src(original_img);
         TIME(rotateImage(src, (float)angle, &original_img), "iSMILES rotate");
      }
      
      
      //Process image using iSMILES
      gga::ImageFilter flt(original_img);
      
      flt.Parameters.ImageSize = 10000;
      
      TIME(flt.prepareImageForVectorization(), "iSMILES image processing");

      gga::FilePNG().save(output, original_img);

      //Back to imago Image type
      convert(original_img, img);

      if (rs["DebugSession"])
      {
         imago::ImageUtils::saveImageToFile(img, "output/process_result.png");
      }

      //Recognize molecule
      imago::Molecule mol;
      const char *fontfile = font_path; //"TEST3.font"; //TODO: Set correct path
      imago::ChemicalStructureRecognizer(fontfile).image2mol(img, mol);

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
