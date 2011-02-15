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
      virtual int findFromSymbols( const SegmentDeque &symbols );
   private:
      boost::tuple<int, char, double> _processSymbol( const Segment &seg );
      void _rotateContourTo( const Vec2d &p, Points &contour );
      const CharacterRecognizer &_cr;
   };
}

#endif /* orientation_finder_h */
