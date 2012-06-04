#ifndef _prefilter_h_
#define _prefilter_h_

#include <vector>
#include "settings.h"
#include "image.h"

namespace imago
{
   void prefilterStd(Settings& vars, Image &image );

   bool isCircle(const Settings& vars, Image &seg, bool asChar = false);
   double estimateLineThickness(Image &bwimg, int grid);
}
#endif /* _prefilter_h_ */
