#include <deque>
#include <algorithm>
#include <vector>
#include <list>

#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/biconnected_components.hpp"
#include "boost/foreach.hpp"

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

//#ifdef _DEBUG
      rs["DebugSession"] = true;
      rs["ParLinesEps"] = 0.45;
      rs["AddVertexEps"] = 0.6;
//#endif /* _DEBUG */

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
   
int main( void )
{
   //testRNG("../../../data/mol_images/image13.png");
   //testRecognize("../../../data/mol_images/from-iphone/filtered/iphone2.jpg.out.png"); 
   testRecognize("../../../data/release_examples/3.png"); 
   system("start marvinsketch result.mol");

   //vs: IMAGE1.PNG

   //aromatize 433
   //stereo-up 324
   //stereo-down 215 250 258
   //separation 325 429 145(ego cut - one O)

   return 0;
}