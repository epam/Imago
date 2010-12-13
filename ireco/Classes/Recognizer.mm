//
//  Recognizer.mm
//  ireco
//
//  Created by Boris Karulin on 07.12.10.
//  Copyright 2010 Scite. All rights reserved.
//

#import "log.h"
#import "exception.h"
#import "image.h"
#import "image_utils.h"
#import "molfile_saver.h"
#import "session_manager.h"
#import "recognition_settings.h"
#import "current_session.h"
#import "molecule.h"
#import "chemical_structure_recognizer.h"
#import "output.h"

#import "Image/Image.h"
#import "Image/ImageFilter.h"
#import "Image/Point.h"
#import "Image/FileJPG.h"
//#import "FilePNG.h"

#import "Recognizer.h"

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

@implementation Recognizer

@synthesize image;

- (NSString *)recognize
{
   std::string molfileStr;
   
   NSString *fontPath = [[NSBundle mainBundle] pathForResource:@"TEST4" ofType:@"font"];

   NSLog(@"Loading image...\n");

   NSData *rawImage = UIImageJPEGRepresentation(self.image, 1.0f);
   std::vector<unsigned char> jpgImage((unsigned char *)[rawImage bytes], (unsigned char *)[rawImage bytes] + [rawImage length]);
   
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
      gga::FileJPG().load(jpgImage, &original_img);
      
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
      
      //gga::FilePNG().save(output, original_img);
      
      //Back to imago Image type
      convert(original_img, img);
      
      /*
      if (rs["DebugSession"])
      {
         imago::ImageUtils::saveImageToFile(img, "output/process_result.png");
      }
      */
      
      //Recognize molecule
      imago::Molecule mol;
      const char *fontfile = [fontPath cStringUsingEncoding:NSASCIIStringEncoding];
      imago::ChemicalStructureRecognizer(fontfile).image2mol(img, mol);
      
      //Save result
      //imago::FileOutput fo("result.mol");
      imago::ArrayOutput so(molfileStr);
      //imago::StandardOutput fo;
      imago::MolfileSaver ma(so);
      TIME(ma.saveMolecule(mol), "Saving molecule");
      
      imago::SessionManager::getInstance().releaseSID(id);
   }
   catch( imago::Exception &e )
   {
      puts(e.what());
      return nil;
   }
   
   return [NSString stringWithCString:molfileStr.c_str()];
}

+ (Recognizer *)recognizerWithImage:(UIImage *)image
{
   Recognizer *inst = [[self alloc] init];
   
   inst.image = image;
   [inst autorelease];
   return inst;
}

@end
