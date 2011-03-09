#include "boost/foreach.hpp"
#include <cmath>
#include <cfloat> //DBL_MAX

#include "comdef.h"
#include "fourier_features.h"
#include "segment.h"
#include "segmentator.h"
#include "fourier_descriptors.h"

namespace imago
{
   FourierFeatures::FourierFeatures( int count ) : _count(count),
         _has_inner(0)
   {

   }

   FourierFeatures::~FourierFeatures()
   {

   }

   double FourierFeatures::_distance( const Descriptors &a,
                                      const Descriptors &b ) const
   {
      int s = (int)std::min(a.size(), b.size());
      double c1, c2;
      double d = 0;
      for (int i = 0; i < s / 2; i++)
      {
         double d1 = a[2 * i] - b[2 * i];
         double d2 = a[2 * i + 1] - b[2 * i + 1];

         if (i < s / 4)
            c1 = 2.5, c2 = 3.5;
         else
            c1 = 0.9, c2 = 0.3;

         d += fabs(c1 * d1) + fabs(c2 * d2);
      }
      return d;
   }

   double FourierFeatures::compare( const IFeatures *other ) const
   {
      const FourierFeatures *fothers = static_cast<const FourierFeatures*>(other);

      double d = _distance(_outer, fothers->_outer);

      if (!_has_inner || !fothers->_has_inner)
         return sqrt(d);

      if (_inner.size() != fothers->_inner.size())
         return DBL_MAX;

      for (int i = 0; i < (int)_inner.size(); i++)
         if (_inner[i].size() != 0 && fothers->_inner[i].size() != 0)
            d += _distance(_inner[i], fothers->_inner[i]);

      return sqrt(d);
   }

   void FourierFeatures::extract( const Image &img )
   {
      FourierDescriptors::calculate(&img, _count, _outer);

      SegmentDeque segments;
      Segmentator::segmentate(img, segments, 3, 255); //all white parts

      int x, y, w, h;
      int _width = img.getWidth(), _height = img.getHeight();
      int total = 0;
      int i = 0;
      BOOST_FOREACH(Segment * &seg, segments)
      {
         x = seg->getX(), y = seg->getY();
         w = seg->getWidth(), h = seg->getHeight();

         if (x == 0 || y == 0 || x + w == _width || y + h == _height)
         {
            delete seg;
            seg = 0;
         }
         else
            total++;
      }

      _has_inner = (total > 0);
      _inner.resize(total);

      i = 0;
      BOOST_FOREACH(Segment * &seg, segments)
      {
         if (seg != 0)
            FourierDescriptors::calculate(seg, _count, _inner[i]);
      }
   }
}
