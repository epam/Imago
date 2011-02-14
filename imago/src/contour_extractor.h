#ifndef contour_extractor_h_
#define contour_extractor_h_

#include <vector>

#include "stl_fwd.h"

namespace imago
{
   class Image;

   class ContourExtractor
   {
   public:
      ContourExtractor();
      virtual ~ContourExtractor();

      void getRawContour( const Image &i, Points &contour );
      void getApproxContour( const Image &i, Points &contour );

      //TODO: move it to private and eventually remove
      void _approximize( Points &contour );
   private:
   };
}

#endif /* contour_extractor_h_ */
