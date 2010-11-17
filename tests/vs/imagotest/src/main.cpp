#include <cstdio>
#include <deque>
#include <vector>
#include <list>

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
//#include "graph.h"

using namespace imago;

struct TestStruct
{
   TestStruct()
   {
      puts("constructor");
   }

   ~TestStruct()
   {
      puts("destructor");
   }
   void f()
   {
      int asd = 0;
   }
   TestStruct &func()
   {
      return *this;
   }
};

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

void testVectors()
{
   Vec2d a, b, c;

   a.set(0, 0);
   b.set(2, 0);
   c.set(1, 1);

   printf("dist2seg = %lf\n", Algebra::distance2segment(c, a, b));

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

void testCrop()
{
   /*
   PngLoader in("data/4.png");
   Image img;
   in.loadImage(img);
   img.crop();
   PngSaver out(img);
   FileOutput fout("test/croped.png");
   out.saveImage(fout);
    */
}
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

/*void testHT()
{
   Image c, h, n;
   PngLoader("c.png").loadImage(c);
   PngLoader("h.png").loadImage(h);
   PngLoader("n.png").loadImage(n);

   Array<BlackPoint> pts_c;
   Array<BlackPoint> pts_h;
   Array<BlackPoint> pts_n;

   Array<LineParams> lp_c;
   Array<LineParams> lp_h;
   Array<LineParams> lp_n;

   HoughTransformer ht_c(c, pts_c, 30);
   ht_c.apply();
   ht_c.getLines(lp_c);

   HoughTransformer ht_h(h, pts_h, 30);
   ht_h.apply();
   ht_h.getLines(lp_h);

   HoughTransformer ht_n(n, pts_n, 30);
   ht_n.apply();
   ht_n.getLines(lp_n);

   //printf("%d %d %d\n", ht_c.lines(), ht_h.lines(), ht_n.lines());
   for (int i = 0; i < lp_n.size(); i++)
   {
      printf("%lf %lf | %lf %lf\n", lp_h[i].sin_thetha, lp_h[i].cos_thetha, lp_n[i].sin_thetha, lp_n[i].cos_thetha);
   }
}*/
/*
void test123()
{
   try
   {
      Segment n[3];

      PngLoader("n1.png").loadImage(n[0]);
      PngLoader("n2.png").loadImage(n[1]);
      PngLoader("n3.png").loadImage(n[2]);

      int c = 25;

      Font fnt("../../../data/fonts/arial.font", 0);

      Binarizer(n[0], 190).apply();
      Binarizer(n[1], 190).apply();
      Binarizer(n[2], 190).apply();

      FourierDescriptorsExtractor::getDescriptors(n[0], c);

      FourierDescriptorsExtractor::getDescriptors(n[1], c);

      FourierDescriptorsExtractor::getDescriptors(n[2], c);


      for (int i = 0; i < 2 * c; i++)
      {
         printf("%lf %lf %lf\n", n[0].getFeatures()->descriptors[i], n[1].getFeatures()->descriptors[i], n[2].getFeatures()->descriptors[i]); //, nd[i], nfd[i]);
      }

      printf("%c %c %c", fnt.findBest(n[0], 0, 26, 0), fnt.findBest(n[1], 0, 26, 0), fnt.findBest(n[2], 0, 26, 0));
   }
   catch (Exception &e)
   {
      puts(e.what());
   }
}
*/
//void makeFont()
//{
//   try
//   {
//      int count = 25;
//      Font fnt("../../../data/fonts/arial_bold.png", count);
//      FileOutput fout("../../../data/fonts/arial_bold.font");
//      fout.printf("%d\n", count);
//
//      for (int i = 0; i < fnt._symbols.size(); i++)
//      {
//         Font::FontItem &fi = fnt._symbols[i];
//         fout.printf("%c", fi.sym);
//         for (int i = 0; i < fi.features.descriptors.size(); i++)
//            fout.printf(" %.15lf", fi.features.descriptors[i]);
//         fout.writeCR();
//      }
//   }
//   catch(Exception &e)
//   {
//      puts(e.what());
//   }
//}

// void graphTest()
// {
//    std::list<int> asd;
//    for (int i = 0; i < 10; i++)
//       asd.push_back(i);

//    std::list<int>::iterator it1, it2;
//    it1 = asd.begin();
//    it2 = ++++++asd.begin();

//    const std::list<int> *ptr = &asd;
//    std::find(ptr->begin(), ptr->end(), 5);

//    asd.erase(it1);
//    it1 = asd.begin();
//    std::cout << *it1 << " " << *it2 << "\n";

//    Graph g;
//    for (int i = 0; i < 10; i++)
//    {
//       std::cout << g.addVertex().getIndex() << "\n";
//    }


//    g.addEdge(0, 1);
//    g.addEdge(1, 2);
//    g.addEdge(2, 3);
//    g.addEdge(3, 4);
//    g.addEdge(4, 5);
//    g.addEdge(5, 6);
//    g.addEdge(6, 7);
//    g.addEdge(7, 8);
//    g.addEdge(8, 9);
//    g.addEdge(9, 0);

//    for (Graph::edge_iterator b = g.edgeBegin(); b != g.edgeEnd(); ++b)
//    {
//       std::cout << b->first << " " << b->second << "\n";
//    }

//    std::vector<IntPair> edges;
//    edges.assign(g.edgeBegin(), g.edgeEnd());
//    std::vector<int> vertices;
//    g.deleteVertex(g.v2i(0));
//    g.deleteVertex(g.v2i(5));
//    vertices.assign(g.vertexBegin(), g.vertexEnd());
//    for (int i = 0; i < vertices.size(); i++)
//       std::cout << vertices[i] << "\n";

//    std::cout << "---\n";
//    const Graph &gg = g;
//    Graph::const_vertex_iterator v = gg.v2i(3);
//    for (Graph::const_adj_iterator it = gg.adjacentBegin(v), end = gg.adjacentEnd(v);
//         it != end; ++it)
//       std::cout << it->first << "\n";
   
//    int aaa = 0;
// }

static ThreadLocalPtr<int> asd;
static bool done = 0;

void *thread(void *thread_id)
{
   while(!done)
   {
      *asd.get() = rand();
      printf("THREAD: %d; ASD: %d\n", *((int*)thread_id), *asd.get());
      sleep(3);
   }

   pthread_exit(NULL);
}

void testThreads()
{
   const int thread_count = 20;
   pthread_t threads[thread_count];
   for (int i = 0; i < thread_count; i++)
      pthread_create(&threads[i], NULL, thread, new int(i));

   scanf("*");
   done = 1;
   pthread_exit(NULL);
}

#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>



class TestClass
{
public:
   TestClass()
   {
   }
   std::ostringstream& stream() { return o; };
   ~TestClass()
   {
      std::cout << o.str();
   }
   std::ostringstream o;
};

#define LOG123 TestClass().stream()

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
      //filename = "../../../tests/autotester/results/28.png";
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

void testOCR()
{
   try
   {
      const char *filename = "/home/vsmolov/flamingo_test/iphone2.jpg.out.png";
      qword sid = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(sid);
      Image img;
      ImageUtils::loadImageFromFile(img, filename);
      LPRINT(0, "Start");
      // Convolver gauss(img);
      // gauss.initGauss();
      // gauss.apply();

      Binarizer(img, getSettings()["BinarizationLvl"]).apply();
      Font fnt(Font::ARIAL);
      std::deque<Segment*> segs;
      Segmentator::segmentate(img, segs);

      for (std::deque<Segment*>::iterator it = segs.begin(),
              end = segs.end(); it != end; ++it)
      {
         double d;
         char c = fnt.findBest(*it, 0, 26, &d);
         printf("(%d, %d)   %c  %.5lf\n", (*it)->getX(), (*it)->getY(), c, d);
      }
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
   testOCR();

   return 0;
}
