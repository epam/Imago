#include <deque>
#include <algorithm>
#include <vector>
#include <list>

#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/biconnected_components.hpp"
#include "boost/foreach.hpp"

#include "font.h"
#include "comdef.h"
#include "convolver.h"
#include "current_session.h"
#include "stl_fwd.h"
#include "binarizer.h"
#include "chemical_structure_recognizer.h"
#include "image.h"
#include "image_utils.h"
#include "image_draw_utils.h"
#include "molecule.h"
#include "molfile_saver.h"
#include "recognition_settings.h"
#include "rng_builder.h"
#include "segment.h"
#include "segmentator.h"
#include "separator.h"
#include "stl_fwd.h"
#include "session_manager.h"
#include "segments_graph.h"
#include "scanner.h"
#include "output.h"

using namespace imago;

void testRecognize( char *input )
{
   try   
   {
      qword id = SessionManager::getInstance().allocSID();
      
      SessionManager::getInstance().setSID(id);

      RecognitionSettings &rs = getSettings();

      rs["DebugSession"] = true;

      Image img;
      Molecule mol;

      ImageUtils::loadImageFromFile(img, input);

      gSession.get()->recognizer().image2mol(img, mol);

      FileOutput fo("result.mol");
      MolfileSaver ma(fo);

      ma.saveMolecule(mol);

      //printf("%lf", (double)rs["AvgBondLength"]);
      
      SessionManager::getInstance().releaseSID(id);
   }
   catch ( Exception &e )
   {
      puts(e.what());
   }
}

void testRNG( const char *input )
{
   try
   {
      qword id = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(id);
      RecognitionSettings &rs = getSettings();

//#ifdef _DEBUG
      rs.set("DebugSession", true);
//#endif /* _DEBUG */

      Image img;
      SegmentDeque segs;
      
      ImageUtils::loadImageFromFile(img, input);

      Binarizer(img, 220).apply();

      Segmentator::segmentate(img, segs);
      segments_graph::SegmentsGraph rng;

      BOOST_FOREACH(Segment *s, segs)
         segments_graph::add_segment(s, rng);

      TIME(RNGBuilder::build(rng), "rng building");

      typedef boost::graph_traits<segments_graph::SegmentsGraph>::edge_descriptor Edge;

      std::vector<Edge> spanning_tree;

      segments_graph::SegmentsGraph rng_mst;

      boost::kruskal_minimum_spanning_tree(rng, std::back_inserter(spanning_tree));

      boost::property_map<segments_graph::SegmentsGraph, boost::vertex_pos_t>::type
         positions_rng = boost::get(boost::vertex_pos, rng);

      boost::property_map<segments_graph::SegmentsGraph, boost::vertex_pos_t>::type
         positions_rngmst = boost::get(boost::vertex_pos, rng_mst);

      BOOST_FOREACH( Edge e, spanning_tree )
      {
         segments_graph::SegmentsGraph::vertex_descriptor v1 = boost::source(e, rng), 
            v2 = boost::source(e, rng);

         boost::add_edge(boost::source(e, rng), boost::target(e, rng), rng_mst);

         boost::put(boost::vertex_pos, rng_mst, v1, positions_rng[v1]);
         boost::put(boost::vertex_pos, rng_mst, v2, positions_rng[v2]);
      }

      ImageDrawUtils::putGraph(img, rng);
      ImageUtils::saveImageToFile(img, "output/rng.png"); 

      img.fillWhite();

      ImageDrawUtils::putGraph(img, rng_mst);
      ImageUtils::saveImageToFile(img, "output/rng_mst.png");

      SessionManager::getInstance().releaseSID(id);
   }
   catch ( Exception &e )
   {
      puts(e.what());
   }
}

void testAdaptiveBinarization( char *input )
{
   try
   {
      Image img;

      ImageUtils::loadImageFromFile(img, input);      

      ImageUtils::saveImageToFile(img, "output/origin.png");

      Binarizer(img).apply();

      ImageUtils::saveImageToFile(img, "output/binarized.png");
   }
   catch ( Exception &e )
   {      
      puts(e.what());
   }
}

void testDrawGraph( char *filename )
{
   try
   {
      qword id = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(id);

      Skeleton mol;
      std::string buf;

      FileScanner fs(filename);

      fs.readString(buf, true);

      int w = 0, h = 0;
      sscanf(buf.c_str(), "%i %i", &w, &h);

      fs.readString(buf, true);

      int count = 0;
      sscanf(buf.c_str(), "%i", &count);

      for (int i = 0; i < count; i++)
      {
         int x = 0, y = 0;
         Vec2d b, e;

         fs.readString(buf, true);
         sscanf(buf.c_str(), "%i %i", &x, &y);
         b.x = x, b.y = y;

         fs.readString(buf, true);
         sscanf(buf.c_str(), "%i %i", &x, &y);
         e.x = x, e.y = y;

         mol.addBond(b, e);
      }

      Image img;

      img.init(w, h);
      img.fillWhite();

      ImageDrawUtils::putGraph(img, mol.getGraph());
      ImageUtils::saveImageToFile(img, (std::string(filename) + std::string("_ismiles.png")).c_str());

      SessionManager::getInstance().releaseSID(id);
   }
   catch ( Exception &e )
   {
   }
}

void _processFilter( Image &_origImage)
{
   RecognitionSettings &rs = getSettings();

   const char *str = rs["Filter"];

   if (strcmp(str, "blur") == 0)
   {
      Convolver conv(_origImage);

      conv.initGauss();
      conv.apply();
   }
   if (strcmp(str, "sharp") == 0)
   {
      Convolver conv(_origImage);

      conv.initSharp();
      conv.apply();
   }

   //TODO: Check threshold
   Binarizer(_origImage, rs["BinarizationLvl"]).apply();
   //Binarizer(_origImage, 0).apply();
}

void _selectFont( const SegmentDeque &layer, boost::shared_ptr<Font> &_fnt )
{
   boost::shared_ptr<Font> serif(new Font(Font::SERIF));
   boost::shared_ptr<Font> arial(new Font(Font::ARIAL));

   double dist_a = 0, dist_s = 0;
   double tmp;

   for (SegmentDeque::const_iterator it = layer.begin();
      it != layer.end(); ++it)
   {
      double w = (*it)->getWidth();
      double h = (*it)->getHeight();

      if (w / h > 1.15) //"Constants"
         continue;

      serif->findBest(*it, 0, 26, &tmp); //"Constants"
      dist_s += tmp;

      arial->findBest(*it, 0, 26, &tmp); //"Constants"
      dist_a += tmp;
   }
   if (dist_a < dist_s)
   {
      _fnt = arial;
   }
   else
   {
      _fnt = serif;
   }
}


//void testHandWrittenRecogntion( char *Filename )
//{
//   try 
//   {
//      Image _origImage;
//      qword id = SessionManager::getInstance().allocSID();
//      SessionManager::getInstance().setSID(id);
//
//      ImageUtils::loadImageFromFile(_origImage, Filename);
//
//      boost::shared_ptr<Font> _fnt;
//
//      Molecule mol;
//
//      getLog().reset();
//      mol.clear();
//
//      SegmentDeque layer_symbols, layer_graphics, segments;
//      RecognitionSettings &rs = getSettings(); 
//
//#ifdef _DEBUG
//   rs["DebugSession"] = true;
//#else
//   rs["DebugSession"] = false;
//#endif
//
//
//      LMARK;
//      LPRINT(0 , "Let the recognition begin");
//
//      TIME(_processFilter(_origImage), "Image processing");
//
//      /*rs["SuperSegWndSize"] = 60;
//
//      //Super segmentation is evil
//      TIME(Segmentator::segmentate(_origImage, segments, rs["SuperSegWndSize"]),
//         "Super segmentation"); 
//
//      if (segments.empty())
//      {
//         LPRINT(0, "Image is empty");
//         return;
//      }
//
//      int max = 0;
//      Segment *ind = 0;
//
//      BOOST_FOREACH( Segment *s, segments )
//      {
//         if (s->getWidth() * s->getHeight() > max)
//         {
//            max = s->getWidth() * s->getHeight();
//            ind = s;
//         }
//      }
//
//      //Paranoia
//      if (ind == 0)
//      {
//         throw NullPointerException();
//      }*/
//
//      Image _img;
//      _img.copy(_origImage);
//
//      //TODO: Totally debug!!!
//      rs.set("imgHeight", _img.getHeight());
//      rs.set("imgWidth", _img.getWidth());
//      //
//
//      if (rs["DebugSession"])
//      {
//         ImageUtils::saveImageToFile(_img, "output/real_img.png");
//      }
//
//      //TODO: Other segments should be processed
//      BOOST_FOREACH( Segment *s, segments )
//         delete s;
//      segments.clear();
//
//      TIME(Segmentator::segmentate(_img, segments), "Normal segmentation");
//
//      //WedgeBondExtractor wbe(segments, _img); 
//      //TIME(wbe.singleDownFetch(mol), "Fetching single-down bonds");
//
//      Separator sep(segments, _img);
//      rs.set("SymHeightErr", 42);      
//      rs.set("MaxSymRatio", 1.4);      
//      TIME(sep.firstSeparation(layer_symbols, layer_graphics), 
//         "Symbols/Graphics elements separation");
//      LPRINT(0, "Symbols: %i, Graphics: %i", layer_symbols.size(), 
//         layer_graphics.size());
//
//      Image symbols, graphics;
//
//      symbols.emptyCopy(_img);
//      graphics.emptyCopy(_img);
//
//      BOOST_FOREACH( Segment *s, layer_symbols )
//         ImageUtils::putSegment(symbols, *s, true);
//
//      BOOST_FOREACH( Segment *s, layer_graphics )
//         ImageUtils::putSegment(graphics, *s, true);
//
//      ImageUtils::saveImageToFile(symbols, (std::string(Filename) + std::string("letters.png")).c_str());
//      ImageUtils::saveImageToFile(graphics, (std::string(Filename) + std::string("graphics.png")).c_str());
//
//      if (rs["DebugSession"])
//    
//      {
//         Image symbols, graphics;
//
//         symbols.emptyCopy(_img);
//         graphics.emptyCopy(_img);
//
//         BOOST_FOREACH( Segment *s, layer_symbols )
//            ImageUtils::putSegment(symbols, *s, true);
//
//         BOOST_FOREACH( Segment *s, layer_graphics )
//            ImageUtils::putSegment(graphics, *s, true);
//
//         ImageUtils::saveImageToFile(symbols, "output/letters.png");
//         ImageUtils::saveImageToFile(graphics, "output/graphics.png");
//      }
//
//      LMARK;
//      if (!layer_symbols.empty())
//      {
//         TIME(_selectFont(layer_symbols, _fnt), "Selecting font");
//
//         LabelCombiner lc(layer_symbols, layer_graphics,
//            rs["CapitalHeight"], *_fnt);
//         lc.extractLabels(mol.getLabels());
//
//         if (rs["DebugSession"])
//         {
//            Image symbols;
//            symbols.emptyCopy(_img);
//            BOOST_FOREACH( Segment *s, layer_symbols )
//               ImageUtils::putSegment(symbols, *s, true);
//            ImageUtils::saveImageToFile(symbols, "output/letters2.png");
//         }
//
//         LPRINT(1, "Found %d superatoms", mol.getLabels().size());
//      }
//      else
//      {
//         LPRINT(1, "No symbols found in image");
//      }
//      
//      /*
//
//      Points ringCenters;
//
//      TIME(GraphicsDetector().extractRingsCenters(layer_graphics, ringCenters), "Extracting aromatic rings");
//
//      LPRINT(0, "Found %i rings", ringCenters.size());
//
//      TIME(GraphExtractor::extract(layer_graphics, mol), 
//         "Extracting molecular graph");
//
//      TIME(wbe.singleUpFetch(mol), "Fetching single-up bonds");
//
//      if (!layer_symbols.empty())
//      {
//         LMARK;
//         LabelLogic ll(*_fnt, getSettings()["CapHeightErr"]);
//         BOOST_FOREACH(Label &l, mol.getLabels())
//            ll.recognizeLabel(l);
//
//         LPRINT(1, "Label recognizing");
//
//         mol.mapLabels();
//      }
//
//      mol.aromatize(ringCenters);
//
//      TIME(wbe.fixStereoCenters(mol), "Fixing stereo bonds directions");
//
//      LPRINT(0, "Compound recognized with #%i config", (int)rs["CfgNumber"] + 1);*/
//
//      BOOST_FOREACH( Segment *s, layer_symbols)
//         delete s;
//      BOOST_FOREACH( Segment *s, layer_graphics)
//         delete s;
//
//      LPRINT(1, "Recognition finished");
//
//
//
//      SessionManager::getInstance().releaseSID(id);
//   }
//   catch (Exception &e)
//   {
//      puts(e.what());
//   }
//}
   
int main( int argc, char *argv[] )
{
   //if (argc > 1)
     // testHandWrittenRecogntion(argv[1]);

   //testHandWrittenRecogntion("../../../data/mol_images/from-iphone/filtered/IMG_0065.jpg.out.png");
   //testHandWrittenRecogntion("../../../data/mol_images/from-iphone/filtered/iphone3.jpg.out.png");
   //testRNG("../../../data/mol_images/image13.png");
   //testRecognize("../../../data/mol_images/from-iphone/filtered/IMG_0057.jpg.out.png"); 
   testRecognize("../../../data/mol_images/temp/1.png"); 
   //C:\work\imago\data\mol_images\first-delivery-images
   //system("start marvinsketch result.mol");

   //vs: IMAGE1.PNG
     //aromatize 433
   //stereo-up 324
   //stereo-down 215 250 258
   //separation 325 429 145(ego cut - one O)

   return 0;
}