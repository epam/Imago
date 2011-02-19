#ifndef orientation_finder_h
#define orientation_finder_h

#include "boost/tuple/tuple.hpp"
#include <deque>

#include "segment.h"
#include "stl_fwd.h"
#include "character_recognizer.h"

namespace imago
{
   class OrientationFinder
   {
   public:
      OrientationFinder( const CharacterRecognizer &cr );
      virtual ~OrientationFinder();
      int findFromSymbols( const SegmentDeque &symbols );
      int findFromImage( const Image &img );
   private:
      boost::tuple<int, char, double> _processSymbol( const Segment &seg );
      void _rotateContourTo( const Vec2d &p, Points &contour );
      const CharacterRecognizer &_cr;
      HWCharacterRecognizer _hwcr;
   };
}

#endif /* orientation_finder_h */
