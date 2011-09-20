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
#import "character_recognizer.h"
#import "superatom_expansion.h"

#import "Recognizer.h"

#undef LMARK 
#undef LPRINT 
#undef TIME 

#define LMARK imago::getLog().mark();
#define LPRINT imago::getLog().print
#define TIME(a, msg) do { LMARK; a; LPRINT(1, msg); } while(0);

@implementation Recognizer

- (NSString *)recognize: (UIImage *)image
{
   NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
   NSLog(@"Loading image...\n");
   NSData *rawImage = UIImageJPEGRepresentation(image, 1.0f);
   std::vector<unsigned char> jpgImage((unsigned char *)[rawImage bytes], (unsigned char *)[rawImage bytes] + [rawImage length]);

   [pool drain];

   try
   {
      imago::getLog().reset();
      
      LMARK;
      LPRINT(0 , "Let the recognition begin");
      
      imago::Image img;
      imago::prefilterFile(jpgImage, img, csr->getCharacterRecognizer());

      //Recognize molecule
      imago::Molecule mol;
      
      csr->image2mol(img, mol);
      
      //Save result
      std::string molfileStr;

      //imago::FileOutput fo("result.mol");
      //imago::ArrayOutput so(molfileStr);
      //imago::StandardOutput fo;
      //imago::MolfileSaver ma(so);
      //TIME(ma.saveMolecule(mol), "Saving molecule");

      molfileStr = imago::expandSuperatoms(mol);
      
      return [NSString stringWithCString:molfileStr.c_str() encoding:NSASCIIStringEncoding];
   }
   catch( imago::Exception &e )
   {
      puts(e.what());
      return nil;
   }
}

- (Recognizer *)init
{
   if (self = [super init])
   {
      sessionId = imago::SessionManager::getInstance().allocSID();
      imago::SessionManager::getInstance().setSID(sessionId);
      imago::RecognitionSettings &rs = imago::getSettings();
      rs.set("DebugSession", false);

      NSString *fontPath = [[NSBundle mainBundle] pathForResource:@"ff" ofType:@"font"];
      const char *fontfile = [fontPath cStringUsingEncoding:NSASCIIStringEncoding];
      
      csr = new imago::ChemicalStructureRecognizer(fontfile);
   }
   return self;
}

- (void)dealloc
{
   delete csr;
   imago::SessionManager::getInstance().releaseSID(sessionId);
   
   [super dealloc];
}

@end
