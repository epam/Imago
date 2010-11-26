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

int main( int argc, char *argv[] )
{
   if (argc > 1)
      testDrawGraph(argv[1]);

   return 0;
}