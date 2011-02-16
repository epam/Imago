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

namespace imago
{
   void prefilterFile (const char *filename, Image &img);
   bool isCircle (Image &seg);
}


void _findCircles (Image &img)
{
   SegmentDeque segments;
   int i, j;
   int count = 0;
   
   Segmentator::segmentate(img, segments, 3, 0);
   
   for (SegmentDeque::iterator it = segments.begin(); it != segments.end(); ++it, ++count)
   {
      Segment &seg = **it;
      ThinFilter2 tf(seg);
      
      tf.apply();
      
      
      printf("segment #%d: ", count);
      if (isCircle(seg))
         printf("  CIRCLE!\n");
      {
         FileOutput output("seg_%02d.png", count);
         PngSaver saver(output);
         saver.saveImage(seg);
      }
   }
}

int main(int argc, char **argv)
{
   Image img;
   try
   {
      qword sid = SessionManager::getInstance().allocSID();
      SessionManager::getInstance().setSID(sid);

      // all OK
      //prefilterFile("../../../data/from_caduff_2/IMG_0019.JPG", img);

      // one false negative at 0.25 threshold
      // prefilterFile("../../../data/from_caduff_2/IMG_0020.JPG", img);

      // one false negative at 0.25 threshold
      //prefilterFile("../../../data/from_caduff_2/IMG_0021.JPG", img);

      // all OK (no circles)
      //prefilterFile("../../../data/from_caduff_2/IMG_0022.JPG", img);
      //prefilterFile("../../../data/from_caduff_2/IMG_0023.JPG", img);
      //prefilterFile("../../../data/from_caduff_2/IMG_0024.JPG", img);

      // all OK
      //prefilterFile("../../../data/from_caduff_2/IMG_0025.JPG", img);
      
      // all OK (no circles; those touching bonds do not count)
      //prefilterFile("../../../data/from_caduff_2/IMG_0026.JPG", img);

      // all OK (one circle touching bond does not count)
      //prefilterFile("../../../data/from_caduff_2/IMG_0027.JPG", img);

      // 1 false negative at 0.25 threshold, 1 false positive (carbon)
      prefilterFile("../../../data/from_caduff_2/IMG_0028.JPG", img);
      
      // 1 false positive (carbon)
      // another false positive at 0.3 threshold
      //prefilterFile("../../../data/from_caduff_2/IMG_0030.JPG", img);

      // all OK
      //prefilterFile("../../../data/from_caduff_2/IMG_0047.JPG", img);

      // all OK
      //prefilterFile("../../../data/from_caduff_2/IMG_0051.JPG", img);

      
      _findCircles(img);
   }
   catch (Exception &e)
   {
      fprintf(stderr, "%s\n", e.what());
   }
   return 0;
}
