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
#import "prefilter.h"

#import "Recognizer.h"

#undef LMARK 
#undef LPRINT 
#undef TIME 

#define LMARK imago::getLog().mark();
#define LPRINT imago::getLog().print
#define TIME(a, msg) do { LMARK; a; LPRINT(1, msg); } while(0);

@implementation Recognizer

@synthesize image;

- (NSString *)recognize
{
   NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
   std::string molfileStr;
   
   NSString *fontPath = [[NSBundle mainBundle] pathForResource:@"TEST4" ofType:@"font"];

   NSLog(@"Loading image...\n");

   NSData *rawImage = UIImageJPEGRepresentation(self.image, 1.0f);
   //NSString *outPath = [[NSBundle mainBundle] pathForResource:@"photo11" ofType:@"jpg"];
   //NSData *rawImage = [NSData dataWithContentsOfFile:outPath];
   
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
      imago::prefilterFile(jpgImage, img);

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
      [pool drain];
      return nil;
   }
   
   [pool drain];
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
