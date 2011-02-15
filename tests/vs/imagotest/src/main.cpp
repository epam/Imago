#include <cstdio>
#include <deque>
#include <vector>
#include <list>
#include <stdio.h>

#include "skeleton.h"
#include "molecule.h"
#include "vec2d.h"
#include "algebra.h"
#include "image.h"
#include "png_loader.h"
#include "png_saver.h"
#include "fourier_descriptors.h"
#include "font.h"
#include "superatom.h"
#include "label_combiner.h"
#include "chemical_structure_recognizer.h"
#include "segmentator.h"
#include "binarizer.h"
#include "log.h"
#include "output.h"
#include "thin_filter2.h"
#include "convolver.h"
#include "symbol_features.h"
#include "approximator.h"
#include "thread_local_ptr.h"
#include "image_draw_utils.h"
#include "scanner.h"
#include "image_utils.h"
#include "molfile_saver.h"
#include "session_manager.h"
#include "current_session.h"
#include "character_recognizer.h"
#include "orientation_finder.h"

using namespace imago;

int readCL( int argc, char **argv )
{
   if (argc < 2)
   {
      puts("Not enough cl parameters");
      exit(0);
   }
   int res;
   sscanf(argv[1], "%d", &res);
   return res;
}

//void testSegmentation()
//{
//   FileScanner fs("data/image162.png");
//   PngLoader in(fs);
//   Image img;
//
//   in.loadImage(img);
//   SegmentDeque segs;
//   Image seg;
//
//   try
//   {
//      Segmentator::segmentate(img, segs);
//
//      char str[20];
//      int i = 0;
//
//      deque_for_each(Segment*, segs, it)
//      {
//         Image &seg = **it;
//         FileOutput fout("test/seg_%d.png", i++);
//         PngSaver out(fout);
//         out.saveImage(seg);
//
//         delete *it;
//      }
//   }
//   catch (imago::Exception e)
//   {
//      puts(e.what());
//   }
//}

/*
void testFD()
{
   PngLoader in1("data/FDtest1.png");
   PngLoader in2("data/FDtest2.png");
   Image img1, img2;
   Array<double> desc;
   in1.loadImage(img1);
   in2.loadImage(img2);

   img1.crop();
   img2.crop();

   FourierDescriptors fde(&img1);

   try
   {
      fde.calculate(desc, 10);
      for(int i = 0; i < 10; i++)
      {
         printf("%lf %lf\n", desc[i * 2], desc[i * 2 + 1]);
      }


      puts("");
      fde.resetImage(&img2);
      fde.calculate(desc, 10);
      for(int i = 0; i < 10; i++)
      {
         printf("%lf %lf\n", desc[i * 2], desc[i * 2 + 1]);
      }
   }
   catch (imago::Exception e)
   {
   	puts(e.what());
      return;
   }
}
*/

void testFont()
{
   Font fnt("../../../imago/data/arial.png", 6);
}

/*
void testCombiner()
{
   try
   {
      Font fnt("../../../imago/data/arial.png", 6);
      List<Segment> segs;
      PngLoader in("data/touch7.png");
      Image img;
      in.loadImage(img);
//      img.binarizeManual(200);

      Segmentator::segmentate(img, segs);
      LabelCombiner sc(segs, fnt);
      List<Superatom> sups;
      sc.getLabels(sups);
      printf("%d superatoms\n", sups.size());
   }
   catch(Exception &e)
   {
      puts(e.what());
   }
}
*/

// static ThreadLocalPtr<int> asd;
// static bool done = 0;

// void *thread(void *thread_id)
// {
//    while(!done)
//    {
//       *asd.get() = rand();
//       printf("THREAD: %d; ASD: %d\n", *((int*)thread_id), *asd.get());
//       sleep(3);
//    }

//    pthread_exit(NULL);
// }

// void testThreads()
// {
//    const int thread_count = 20;
//    pthread_t threads[thread_count];
//    for (int i = 0; i < thread_count; i++)
//       pthread_create(&threads[i], NULL, thread, new int(i));

//    scanf("*");
//    done = 1;
//    pthread_exit(NULL);
// }


// #include <sstream>
// #include <iostream>
// #include <algorithm>
// #include <set>

// class TestClass
// {
// public:
//    TestClass()
//    {
//    }
//    std::ostringstream& stream() { return o; };
//    ~TestClass()
//    {
//       std::cout << o.str();
//    }
//    std::ostringstream o;
// };

// #define LOG123 TestClass().stream()

void testRecognizer(int num)
{
   try
   {
      const char *clide = "../../../data/mol_images/image";
      char *image_name = new char[strlen(clide) + 10];
      sprintf(image_name, "%s%d.png", clide, num);

      const char *filename = image_name;

      //filename = "../../../data/mol_images/triple.png";
      //filename = "data/70.png";
      //filename = "/media/usr/Zentsev/for_demo/firstly/1347f/5_noblur_200.png";
      //filename = "/media/usr/Zentsev/porphyrin-sample-v02ch07/6.png";
      //filename = "../../../tests/autotester/results2/43794.png";
      //filename = "../../../data/release_examples/4.png";
      //filename = "/home/vsmolov/flamingo_test/US07314705-20080101-C00010.png";
      //filename = "../../../../../flamingo_test/t.png";
      //filename = "~/flamingo_test/800.png";
      //filename = "../../../data/mol_images/from_articles/75.png";
      //filename = "/media/proj/OpenSource/flamingo-dev/first-delivery-images/photo04.png";
      filename = "../../../../flamingo_test/fdi/photo04.png";
      qword sid = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(sid);
      ChemicalStructureRecognizer CSR("../../../data/fonts/TEST4.font");
      ChemicalStructureRecognizer &csr = CSR; //gSession.get()->recognizer();
      RecognitionSettings &rs = getSettings();
      rs.set("DebugSession", true);
      Image img;
      Molecule mol;
      ImageUtils::loadImageFromFile(img, filename);
      csr.image2mol(img, mol);
      //csr.setImage(img);
      //csr.recognize(mol);

      FileOutput fout("molecule.mol");
      MolfileSaver saver(fout);
      saver.saveMolecule(mol);

      SessionManager::getInstance().releaseSID(sid);
      delete[] image_name;
   }
   catch (Exception &e)
   {
      puts(e.what());
   }
}

void testContour()
{
   try
   {
      const char *filename = "/home/vsmolov/flamingo_test/US07314705-20080101-C00010.png";
      qword sid = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(sid);
      Image img;
      ImageUtils::loadImageFromFile(img, filename);
      LPRINT(0, "Start");
      Convolver gauss(img);
      gauss.initGauss();
      gauss.apply();

      Binarizer(img, getSettings()["BinarizationLvl"]).apply();
      LMARK;
      std::deque<Segment*> segs;
      std::deque<int> contour;
      LMARK;
      Segmentator::segmentate(img, segs);
      LPRINT(1, "Segmentation");
      printf("%d segments\n", segs.size());
      LMARK;
      for (std::deque<Segment*>::iterator it = segs.begin(),
              end = segs.end(); it != end; ++it)
      {
         //Move FDE::_getContour from private to public if running this test
         //FourierDescriptors::_getContour(**it, contour);
         printf("Got contour. Size = %d\n", contour.size());
      }
      LPRINT(1, "Contours");
      LPRINT(1, "Stop");
   }
   catch (Exception &e)
   {
      puts(e.what());
   }   
}

void testOCR( const char *name )
{
   try
   {
      const char *filename;
      filename = name?name:"/home/vsmolov/flamingo_test/iphone2.jpg.out.png";
      //filename = "../../../data/fonts/png/MarkerSD_it.png";
      qword sid = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(sid);
      Image img;
      ImageUtils::loadImageFromFile(img, filename);
      LPRINT(0, "Start");
      // Convolver gauss(img);
      // gauss.initGauss();
      // gauss.apply();

      // Binarizer(img, getSettings()["BinarizationLvl"]).apply();
      Font fnt("../../../data/fonts/MarkerSD.font", 25);
      std::deque<Segment*> segs;
      Segmentator::segmentate(img, segs);

      int i = 0; //for font files
      for (std::deque<Segment*>::iterator it = segs.begin(),
              end = segs.end(); it != end; ++it, ++i)
      {
         double d;
         char c_s, c_b, c_d;
//         if (i < 26)
            c_s = fnt.findBest(*it, 0, 26, &d);
//         else if (i < 52 + 2)
            c_b = fnt.findBest(*it, 26, 52, &d);
//         else
            c_d = fnt.findBest(*it, 52, 62, &d);
         printf("i = %d  ", i);
         printf("(%d, %d)   %c %c %c  %.5lf  innerCcount = %d  h = %d\n",
                (*it)->getX(), (*it)->getY(), c_s, c_b, c_d, d,
                (*it)->getFeatures().inner_contours_count, (*it)->getHeight());
      }
   }
   catch (Exception &e)
   {
      puts(e.what());
   }
}

void makeFont( )
{
  try
  {
     const int fonts_count = 5;
     char font_names[fonts_count][1024] = {//"../../../data/fonts/png/arial2.png",
                                           "../../../data/fonts/png/serif.png",
                                           //"../../../data/fonts/png/MarkerSD_it.png",
                                           //"../../../data/fonts/png/Writing_Stuff.png",
                                           "../../../data/fonts/png/MarkerSD.png",
                                           "../../../data/fonts/png/desyrel.png",
                                           "../../../data/fonts/png/budhand.png",
                                           "../../../data/fonts/png/annifont.png"};
     int count = 25;
     std::vector<Font *> fonts(fonts_count);
     for (int i = 0; i < fonts_count; i++)
        fonts[i]= new Font(font_names[i], count);
     
     FileOutput fout("../../../data/fonts/TEST4.font");
     fout.printf("%d %d %d\n", count, fonts_count, 62);

     for (int i = 0; i < fonts_count; i++)
        printf("%d\n", fonts[i]->_symbols.size());


     for (int i = 0; i < 62; i++)
     {
        Font::FontItem *fi = &fonts[0]->_symbols[i];
        fout.printf("%c\n", fi->sym);
        for (int k = 0; k < fonts_count; k++)
        {
           fi = &fonts[k]->_symbols[i];
           fout.printf("%d\n", fi->features.inner_contours_count);
           for (int i = 0; i < (int)fi->features.descriptors.size(); i++)
              fout.printf("%.15lf ", fi->features.descriptors[i]);
           fout.writeCR();
           for (int i = 0; i < fi->features.inner_contours_count; i++)
           {
              for (int j = 0; j < (int)fi->features.inner_descriptors[i].size();
                   j++)
              {
                 fout.printf("%.15lf ", fi->features.inner_descriptors[i][j]);
              }
              fout.writeCR();
           }
        }
     }
  }
  catch(Exception &e)
  {
     puts(e.what());
  }
}

void testOCR2( const char *name )
{
   try
   {
      qword sid = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(sid);
      Image img;

      CharacterRecognizer cr(2, "../../../data/fonts/TEST4.font");

      const char *filename;
      filename = name?name:"../../../../flamingo_test/sym/n/IMG_0052.JPG.out.png";
      ImageUtils::loadImageFromFile(img, filename);
      LPRINT(0, "Start");
      // Convolver gauss(img);
      // gauss.initGauss();
      // gauss.apply();

      Binarizer(img, getSettings()["BinarizationLvl"]).apply();
      std::deque<Segment*> segs;
      Segmentator::segmentate(img, segs);

      int i = 0; //for font files
      for (std::deque<Segment*>::iterator it = segs.begin(),
              end = segs.end(); it != end; ++it, ++i)
      {
         double d;
         char c_s, c_b, c_d;
         c_s = cr.recognize(**it, CharacterRecognizer::upper, &d);
         c_b = cr.recognize(**it, CharacterRecognizer::lower, &d);
         c_d = cr.recognize(**it, CharacterRecognizer::digits, &d);
         printf("i = %d  ", i);
         printf("(%d, %d)   %c %c %c  %.5lf  innerCcount = %d  h = %d\n",
                (*it)->getX(), (*it)->getY(), c_s, c_b, c_d, d,
                (*it)->getFeatures().inner_contours_count, (*it)->getHeight());
      }
      
      // Binarizer(img, getSettings()["BinarizationLvl"]).apply();
      
   }
   catch (Exception &e)
   {
      puts(e.what());
   }
}

namespace imago
{
   void prefilterFile( const char *filename, Image &img );
}
void testRotation(const char *filename = 0)
{
   try
   {
      qword sid = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(sid);
      
      Image img;
      /*
      ImageUtils::loadImageFromFile(img, "/home/vsmolov/flamingo_test/rotate/rotate1.png");
      CharacterRecognizer cr(3);
      
      SegmentDeque segs;
      Segmentator::segmentate(img, segs);

      OrientationFinder of(cr);
      int rot = of.findFromSymbols(segs);

      printf("Orientation %d\n", rot);
      */
      const char *f = filename ? filename :
         "/home/vsmolov/flamingo_test/first-delivery-images/photo05.jpg";
      prefilterFile(f, img);

      img.rotate90();

      getSettings()["DebugSession"] = true;
      //getSettings()["Filter"] = "blur"; //for 34!
      ChemicalStructureRecognizer &csr = getRecognizer();
      Molecule mol;

      csr.image2mol(img, mol);
      //printf("Before: %d %d\n", img.getWidth(), img.getHeight());
      //img.rotate90(false);
      //printf("After: %d %d\n", img.getWidth(), img.getHeight());
      //ImageUtils::saveImageToFile(img, "rot.png");

      FileOutput fout("molecule.mol");
      MolfileSaver saver(fout);
      saver.saveMolecule(mol);

      SessionManager::getInstance().releaseSID(sid);

      
   }
   catch (std::exception &e)
   {
      puts(e.what());
   }
}

int main(int argc, char **argv)
{
   //graphTest();
   
   //testArray();
   //testVectors();
   //testSegmentation();
   //testCrop();
   //testFD();
   //testFont();
   //testCombiner();
   //test123();

   /*
   int x = 10;
   LOG123 << "123\n";
   LOG123 << "x = " << x << "\n";
   */
#ifndef NDEBUG
   puts("DEBUG");
#endif
   
   //testThreads();

   //138
   //144 strange double bond appears (second from top)
   //169 missed double bond
   //218 2 missed double bonds
   //238 bond dissapears
   //305 missed triple and double bonds
   //142
   int num = 103; //144; //103; //267; //27; //249; //197; //29; //181; //301; //27; //150; //101; //209; //301; //326; //334; //336; //250;//349; //145;//226;//339; //262;
   //num = readCL(argc, argv);

   //testContour();
   //testRecognizer(num);
   //testOCR(argv[1]);
   //makeFont();
   //testOCR2(argv[1]);

   testRotation(argv[1]);

   return 0;
}
