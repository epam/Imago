#ifndef _prefilter_h_
#define _prefilter_h_

#include <vector>
#include "constants.h"

namespace imago
{
   class Image;
   class CharacterRecognizer;

   struct PrefilterParams
   {
	   bool logSteps;
	   bool adaptiveThresh;
	   bool strongThresh;
	   bool reduceImage;
	   bool binarizeImage;
	   PrefilterParams()
	   {
		   logSteps = reduceImage = binarizeImage = true;
		   adaptiveThresh = strongThresh = false;
	   }
   };

   void prefilterKernel( const Image &raw, Image &image, const PrefilterParams& p = PrefilterParams());
   void prefilterImage( Image &image, const CharacterRecognizer &cr );

   bool   isCircle(Image &seg);
   double estimateLineThickness(Image &bwimg, int grid = -1);
}
#endif /* _prefilter_h_ */
