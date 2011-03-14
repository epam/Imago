#include <cstdio>
#include <deque>
#include <vector>
#include <list>
#include <stdio.h>
#include <opencv/cv.h>
#include "boost/smart_ptr.hpp"

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
#include "graphics_detector.h"
#include "shape_context.h"

#include "classification.h"
#include "fourier_features.h"

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
                                           "../../../data/fonts/png/budhand3.png",
                                           "../../../data/fonts/png/annifont.png"};
     int count = 25;
     std::vector<Font *> fonts(fonts_count);
     for (int i = 0; i < fonts_count; i++)
        fonts[i]= new Font(font_names[i], count);
     
     FileOutput fout("../../../data/fonts/TEST5.font");
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

      CharacterRecognizer cr(3, "../../../data/fonts/TEST4.font");

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

      /*ImageUtils::loadImageFromFile(img, "/home/winkie/flamingo_test/rotate/rotate1.png");
      CharacterRecognizer cr(3);
      
      SegmentDeque segs;
      Segmentator::segmentate(img, segs);

      OrientationFinder of(cr);
      int rot = of.findFromSymbols(segs);

      printf("Orientation %d\n", rot);
      */
      const char *f = filename ? filename :
         "../../../data/from_caduff_2/IMG_0043.JPG";
         //"../../../ireco/first-delivery-images/photo09.jpg";
      prefilterFile(f, img);

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
void _ImageToMat(const Image &img, cv::Mat mat)
{
   int w = img.getWidth(), h = img.getHeight();
   cv::Mat res(h, w, CV_8U);
   for (int k = 0; k < h; k++)
   {
      for (int l = 0; l < w; l++)
      {
         res.at<byte>(k, l) = img.getByte(l, k);
      }
   }
   mat = res;
}

void _getHuMoments(const Image &img, double hu[7])
{
   int w = img.getWidth(), h = img.getHeight();
   cv::Mat mat(h, w, CV_8U);
   for (int k = 0; k < h; k++)
   {
      for (int l = 0; l < w; l++)
      {
         mat.at<byte > (k, l) = img.getByte(l, k);
      }
   }
   cv::Moments moments = cv::moments(mat, true);
   cv::HuMoments(moments, hu);
}

void makeCVFont( )
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
     
     FileOutput fout("../../../data/fonts/1.cvfont");
     fout.printf("%d %d\n", fonts_count, 62);

     for (int i = 0; i < fonts_count; i++)
     {
        Image img;
        ImageUtils::loadImageFromFile(img, font_names[i]);
        SegmentDeque segs;
        Segmentator::segmentate(img, segs);

        printf("%s: %d segments\n", font_names[i], segs.size());
        SegmentDeque::iterator it = segs.begin();
        for (int j = 0; j < (int)segs.size() - 2; j++)
        {
           if (j == 34 || j == 35)
              ++it;
           
           Image *img = *it;
           ++it;
           
           char sym;
           if (j < 26)
              sym = 'A' + j;
           else if (j < 52)
              sym = 'a' + (j - 26);
           else if (j < 62)
              sym = '0' + (j - 52);
           
           double hu[7];
           _getHuMoments(*img, hu);
           
           fout.printf("%c ", sym);
           for (int k = 0; k < 7; k++)
              fout.printf("%lf ", hu[k]);
           fout.writeCR();
        }
     }
  }
  catch(Exception &e)
  {
     puts(e.what());
  }
}

void testCvOCR( const char *_filename = 0)
{
   FILE *f = fopen("../../../data/fonts/1.cvfont", "r");
   int font_count, sym_count;
   fscanf(f, "%d %d\n", &font_count, &sym_count);
   std::vector<std::pair<char, std::vector<double> > > hus;
   hus.resize(font_count * sym_count);
   for (int i = 0; i < font_count * sym_count; i++)
   {
      fscanf(f, "%c ", &hus[i].first);
      hus[i].second.resize(7);
      for (int j = 0; j < 7; j++)
         fscanf(f, "%lf ", &hus[i].second[j]);
   }
   fclose(f);
   
   const char *filename = _filename ? _filename:
      "../../../data/fonts/png/desyrel.png";
      //"../../../../flamingo_test/sym/n/IMG_0054.JPG.out.png";

   qword sid = SessionManager::getInstance().allocSID();
   SessionManager::getInstance().setSID(sid);

   Image img;
   ImageUtils::loadImageFromFile(img, filename);
   SegmentDeque segs;
   Segmentator::segmentate(img, segs);

   Image &imgN = *segs[4];

   ThinFilter2 tf(imgN);
   tf.apply();
/*
   CvApproximator cvApprox;
   GraphicsDetector gd(&cvApprox, 11.0);
   Points poly;
   gd.detect(imgN, poly);
   Image lol;
   lol.emptyCopy(imgN);
   lol.fillWhite();
   for (int i = 0; i < poly.size(); i += 2)
   {
      ImageDrawUtils::putLineSegment(lol, poly[i], poly[i + 1], 0);
   }
   ImageUtils::saveImageToFile(lol, "lol.png");
   printf("LINES COUNT = %d\n", poly.size());
   */
   imgN.invert();
   Image lol;
   lol.emptyCopy(imgN);
   lol.fillWhite();

   cv::Mat mat;
   _ImageToMat(imgN, mat);
   std::vector<cv::Vec4i> lines;

   printf("%d\n", mat.channels());
   cv::HoughLinesP(mat, lines, 1, CV_PI / 180, 13, 30, 100);
   printf("LINES COUNT = %d\n", lines.size());
   for (int i = 0; i < lines.size(); i += 2)
   {
      cv::Vec4i &v = lines[i];
      ImageDrawUtils::putLineSegment(lol, Vec2d(v[0], v[1]), Vec2d(v[2], v[3]), 0);
   }
   ImageUtils::saveImageToFile(lol, "lol.png");
}

void createTrainSet(std::vector<std::string> fonts, IOCRClassification::TrainSet &ts)
{
   for (int i = 0; i < (int)fonts.size(); i++)
   {
      Image img;
      ImageUtils::loadImageFromFile(img, fonts[i].c_str());
      SegmentDeque segs;
      Segmentator::segmentate(img, segs);

      printf("%s: %d segments\n", fonts[i].c_str(), segs.size());
      SegmentDeque::iterator it = segs.begin();
      for (int j = 0; j < (int)segs.size() - 2; j++)
      {
         if (j == 34 || j == 35)
            ++it;

         Image *img = *it;
         ++it;

         char sym;
         if (j < 26)
            sym = 'A' + j;
         else if (j < 52)
            sym = 'a' + (j - 26);
         else if (j < 62)
            sym = '0' + (j - 52);

         ts.push_back(std::make_pair(img, sym));
      }
   }
}

void testClassifier()
{
   IOCRClassification *classificator = new FourierFeaturesCompareMethod(25, 3);
   std::vector<std::string> fonts;
   IOCRClassification::TrainSet ts;
   fonts.push_back("../../../data/fonts/png/serif.png");
   //"../../../data/fonts/png/MarkerSD_it.png",
   //"../../../data/fonts/png/Writing_Stuff.png",
   fonts.push_back("../../../data/fonts/png/MarkerSD.png");
   fonts.push_back("../../../data/fonts/png/desyrel.png");
   fonts.push_back("../../../data/fonts/png/budhand.png");
   fonts.push_back("../../../data/fonts/png/annifont.png");
   createTrainSet(fonts, ts);

   //classificator->train(ts);
   //FileOutput fout("fdc.dump");
   //classificator->save(fout);
   classificator->load("fdc.dump");

   bool b; char c; double err;
   Image img;

   ImageUtils::loadImageFromFile(img, "letter_n.png");

   b = classificator->getBest(img, c, &err);

   printf("%d %c %lf\n", (int)b, c, err);

   for (int i = 0; i < (int)ts.size(); i++)
      delete ts[i].first;
}



void testShapeContext( const char *filename )
{
   qword sid = SessionManager::getInstance().allocSID();
   SessionManager::getInstance().setSID(sid);

   boost::shared_ptr<IFeatures> f(new ShapeContextFeatures(50, 10, 10));
   Image img;
   ImageUtils::loadImageFromFile(img, "../../../../flamingo_test/As.png");

   TIME(f->extract(img), "Extract");

   SessionManager::getInstance().releaseSID(sid);
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
#ifdef DEBUG
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

   //testRotation(argv[1]);
   //makeCVFont();

   //testClassifier();
   testShapeContext(argv[1]);

   //testCvOCR(argv[1]);
   
   return 0;
}
