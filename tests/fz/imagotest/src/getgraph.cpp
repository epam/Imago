#include <string>

#include "current_session.h"
#include "image.h"
#include "session_manager.h"
#include "segmentator.h"
#include "graph_extractor.h"
#include "image_draw_utils.h"
#include "image_utils.h"
#include "binarizer.h"

using namespace imago;

void testGetGraph( const char *filename, const char *out_filename )
{
   try 
   {
      qword id = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(id);

      SegmentDeque segs;
      Image img;

      ImageUtils::loadImageFromFile(img, filename);
      Binarizer(img, 220).apply();

      getSettings()["DebugSession"] = false;

      Segmentator::segmentate(img, segs);

      Skeleton mol;

      TIME(GraphExtractor::extract(segs, mol), 
         "Extracting molecular graph");

      Image tmp;

      tmp.emptyCopy(img);
      ImageDrawUtils::putGraph(tmp, mol.getGraph());
      ImageUtils::saveImageToFile(tmp, out_filename);
      
      SessionManager::getInstance().releaseSID(id);
      
   }
   catch (Exception &e)
   {
   
   }
}
   
int main( int argc, char *argv[] )
{
   if (argc > 1)
      testGetGraph(argv[1], (std::string(argv[1]) + std::string("_imago.png")).c_str());

   return 0;
}