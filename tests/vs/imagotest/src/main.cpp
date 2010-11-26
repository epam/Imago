#include <cstdio>
#include <deque>
#include <vector>
#include <list>

#include "skeleton.h"
#include "molecule.h"
#include "vec2d.h"
#include "algebra.h"
#include "image.h"
#include "png_loader.h"
#include "png_saver.h"
#include "fourier_descriptors_extractor.h"
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
#include "graphics_detector.h"

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

   FourierDescriptorsExtractor fde(&img1);

   try
   {
      fde.getDescriptors(desc, 10);
      for(int i = 0; i < 10; i++)
      {
         printf("%lf %lf\n", desc[i * 2], desc[i * 2 + 1]);
      }


      puts("");
      fde.resetImage(&img2);
      fde.getDescriptors(desc, 10);
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
      filename = "../../../data/release_examples/4.png";
      //filename = "/home/vsmolov/flamingo_test/US07314705-20080101-C00010.png";
      //filename = "../../../../../flamingo_test/t.png";
      //filename = "~/flamingo_test/800.png";
      //filename = "../../../data/mol_images/from_articles/75.png";
      qword sid = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(sid);
      ChemicalStructureRecognizer &csr = gSession.get()->recognizer();
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
         //FourierDescriptorsExtractor::_getContour(**it, contour);
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

void makeFont( const char *name )
{
  try
  {
     char buf[1024] = {0};
     int count = 25;
     sprintf(buf, "../../../data/fonts/png/%s.png", name);
     Font fnt(buf, count);
     sprintf(buf, "../../../data/fonts/%s.font", name);
     FileOutput fout(buf);
     fout.printf("%d\n", count);

     for (int i = 0; i < (int)fnt._symbols.size(); i++)
     {
        Font::FontItem &fi = fnt._symbols[i];
        fout.printf("%c %d\n", fi.sym, fi.features.inner_contours_count);
        for (int i = 0; i < (int)fi.features.descriptors.size(); i++)
           fout.printf("%.15lf ", fi.features.descriptors[i]);
        fout.writeCR();
        for (int i = 0; i < fi.features.inner_contours_count; i++)
        {
           for (int j = 0; j < (int)fi.features.inner_descriptors[i].size(); j++)
           {
              fout.printf("%.15lf ", fi.features.inner_descriptors[i][j]);
           }
           fout.writeCR();
        }
     }
  }
  catch(Exception &e)
  {
     puts(e.what());
  }
}

void testVectorization( const char *name )
{
   try
   {
      const char *filename;
      filename = name?name:"../../../../flamingo_test/sep/1.png";
      qword sid = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(sid);

      getSettings()["DebugSession"] = true;
      
      Image img;
      ImageUtils::loadImageFromFile(img, filename);
      LPRINT(0, "Start");

      Points lsegments;
      LMARK;
      GraphicsDetector gd;
      gd.detect(img, lsegments);
      LPRINT(1, "Vectorization");
      
      Image img2;
      img2.emptyCopy(img);
      img2.fillWhite();
      double avg_size = 0;
      for (int i = 0; i < (int)lsegments.size() / 2; i++)
      {
         const Vec2d &p1 = lsegments[2 * i];
         const Vec2d &p2 = lsegments[2 * i + 1];

         ImageDrawUtils::putLineSegment(img2, p1, p2, 0);
         avg_size += Vec2d::distance(p1, p2);
      }

      avg_size /= (lsegments.size() / 2);
      
      LMARK;
      Skeleton graph;
      graph.setInitialAvgBondLength(avg_size);

      for (int i = 0; i < (int)lsegments.size() / 2; i++)
      {
         const Vec2d &p1 = lsegments[2 * i];
         const Vec2d &p2 = lsegments[2 * i + 1];
         
         graph.addBond(p1, p2);
      }

      TIME(graph.modifyGraph(), "ololo");
      
      LPRINT(1, "Other");

      
      ImageUtils::saveImageToFile(img2, "output/vect.png");
      img2.fillWhite();
      ImageDrawUtils::putGraph(img2, graph.getGraph());
      ImageUtils::saveImageToFile(img2, "output/vect2.png");
   }
   catch (Exception &e)
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
   int num = 144; //103; //267; //27; //249; //197; //29; //181; //301; //27; //150; //101; //209; //301; //326; //334; //336; //250;//349; //145;//226;//339; //262;
   //num = readCL(argc, argv);

   //testContour();
   //testRecognizer(num);
   //testOCR(argv[1]);
   //makeFont(argv[1]);
   testVectorization(argv[1]);
   return 0;
}
