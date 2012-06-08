#ifndef contour_extractor_h_
#define contour_extractor_h_

#include <vector>

#include "stl_fwd.h"
#include "settings.h"

namespace imago
{
   class Image;

   class ContourExtractor
   {
   public:
      ContourExtractor();
      virtual ~ContourExtractor();

      void getRawContour( const Image &i, Points2i &contour );
      void getApproxContour(const Settings& vars,  const Image &i, Points2i &contour );

   private:
	   void _approximize(const Settings& vars,  Points2i &contour );
   };
}

#endif /* contour_extractor_h_ */
