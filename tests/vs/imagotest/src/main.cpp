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
#include "fourier_descriptors.h"
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
#include "graphics_detector.h"
#include "prefilter.h"
#include "superatom_expansion.h"

#include "classification.h"
#include "log_ext.h"
#include "adaptive_filter.h"

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
/*
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
*/
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

void _ImageToMat(const Image &img, cv::Mat mat)
{
   int w = img.getWidth(), h = img.getHeight();
   cv::Mat res(h, w, CV_8U);
   for (int k = 0; k < h; k++)
   {
      for (int l = 0; l < w; l++)
      {
         res.at<imago::byte>(k, l) = img.getByte(l, k);
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
         mat.at<imago::byte> (k, l) = img.getByte(l, k);
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
   for (size_t i = 0; i < lines.size(); i += 2)
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

void calcDescriptors(int argc, char **argv)
{
   if (argc != 3)
   {
      exit(-1);
   }
   const std::string imgpath(argv[1]);
   const int count = atoi(argv[2]);

   Image img;
   SegmentDeque segments;
   ImageUtils::loadImageFromFile(img, imgpath.c_str());

   Binarizer(img, 195).apply();
   Segmentator::segmentate(img, segments);
   Segment *seg;

   if (segments.size() >= 3)
   {
      printf("%s\n", imgpath.c_str());
      exit(-1);
   }
   assert(segments.size() < 3);

   if (segments.size() == 2)
   {
      Segment *head, *tail;
      head = segments.front();
      tail = segments.back();

      if (head->getHeight() * head->getWidth() > tail->getHeight() * tail->getWidth())
         seg = head;
      else
         seg = tail;
   }
   else
      seg = segments.front();

   seg->initFeatures(count);
   SymbolFeatures &features = seg->getFeatures();
   if (!features.recognizable)
      exit(-1);

   printf("%d\n", features.inner_contours_count);

   for (int i = 0; i < 2 * count; ++i)
   {
      printf("%lf ", features.descriptors[i]);
   }
   puts("");
   for (int j = 0; j < features.inner_contours_count; ++j)
   {
      for (int i = 0; i < 2 * count; ++i)
      {
         printf("%lf ", features.inner_descriptors[j][i]);
      }
      puts("");
   }
}

void testApproximator(char *filename)
{
   qword sid = SessionManager::getInstance().allocSID();
   SessionManager::getInstance().setSID(sid);

   double eps = 11;
   CvApproximator cv;
   DPApproximator dp;
   
   GraphicsDetector gdD(&dp, eps);
   GraphicsDetector gdC(&cv, eps);

   Image img, res;
   ImageUtils::loadImageFromFile(img, filename);
   
   Points2d lsegments;

   TIME(gdC.detect(img, lsegments), "CV");

   res.emptyCopy(img);
   res.fillWhite();
   for (Points2d::const_iterator it = lsegments.begin(), end = lsegments.end();
        it != end; ++it)
   {
      const Vec2d &b = *it;
      ++it;
      const Vec2d &e = *it;

      ImageDrawUtils::putLineSegment(res, b, e, 0);
      ImageDrawUtils::putCircle(res, b.x, b.y, 3, 128);
      ImageDrawUtils::putCircle(res, e.x, e.y, 3, 128);
   }

   ImageUtils::saveImageToFile(res, "cv.png");
   
   lsegments.clear();
   TIME(gdD.detect(img, lsegments), "DP");
   res.fillWhite();
   for (Points2d::const_iterator it = lsegments.begin(), end = lsegments.end();
        it != end; ++it)
   {
      const Vec2d &b = *it;
      ++it;
      const Vec2d &e = *it;

      ImageDrawUtils::putLineSegment(res, b, e, 0);
      ImageDrawUtils::putCircle(res, b.x, b.y, 3, 128);
      ImageDrawUtils::putCircle(res, e.x, e.y, 3, 128);
   }

   ImageUtils::saveImageToFile(res, "dp.png");
}

void testRecognition(const char *filename, int debugLog, int adaptiveFilter)
{
   try
   {
      qword sid = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(sid);
      
      Image img;

      VirtualFS vfs;

	  if (debugLog > 0)
	  {
		getSettings()["DebugSession"] = true;
		if (debugLog > 1)
			getLogExt().SetVirtualFS(vfs);
	  }

      ChemicalStructureRecognizer &csr = getRecognizer();

	  getSettings()["AdaptiveFilter"] = adaptiveFilter;

	  ImageUtils::loadImageFromFile(img, filename);
     	  
	  prefilterImage(img, csr.getCharacterRecognizer());
	  
      Molecule mol;
      csr.image2mol(img, mol);

      std::string molfile = expandSuperatoms(mol);

      FileOutput fout("molecule.mol");
      fout.writeString(molfile);

	  if (!vfs.empty())
	  {
		  FileOutput flogdump("log_vfs.txt");
		  std::vector<char> logdata;
		  vfs.getData(logdata);
		  flogdump.write(&logdata.at(0), logdata.size());
		  
		  // for testing only:
		  // VirtualFS v2;
		  // v2.setData(logdata);
		  // v2.storeOnDisk("log/");
	  }


      SessionManager::getInstance().releaseSID(sid);      
   }
   catch (std::exception &e)
   {
      puts(e.what());
   }
}

/*
//graphTest();
   
   //testArray();
   //testVectors();
   //testSegmentation();
   //testCrop();
   //testFD();
   //testFont();
   //testCombiner();
   //test123();

	//#ifdef DEBUG
	//   puts("DEBUG");
	//#endif
   
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

     //calcDescriptors(argc, argv);
   //makeCVFont();

   //testClassifier();
   //testShapeContext(argv[1]);

   //testCvOCR(argv[1]);

   //testApproximator(argv[1]);
   */

int main(int argc, char **argv)
{
   // parse command line
   std::vector<std::string> unparsedArgs;
   int debugLog = 0;
   //int adaptiveFilter = 1;
   int adaptiveFilter = 0;

   for (int i = 1; i < argc; i++)
   {
	   std::string s = argv[i];
	   if (s.empty()) continue;
	   if (s[0] == '-')
	   {
		   if (strcmp(s.c_str(), "-log") == 0)
			   debugLog = 1;
		   else if (strcmp(s.c_str(), "-vfslog") == 0)
			   debugLog = 2;
		   else if (strcmp(s.c_str(), "-rgb") == 0)
			   adaptiveFilter = 2;
		   else if (strcmp(s.c_str(), "-gs") == 0)
			   adaptiveFilter = 1;
		   else if (strcmp(s.c_str(), "-oldfilter") == 0)
			   adaptiveFilter = 0;
	   }
	   else
		   unparsedArgs.push_back(s);
   }

   if (!unparsedArgs.empty())
	   testRecognition(unparsedArgs[0].c_str(), debugLog, adaptiveFilter);

   return 0;
}
