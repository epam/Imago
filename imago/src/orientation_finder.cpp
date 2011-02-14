#include <cmath>
#include "boost/foreach.hpp"

#include "orientation_finder.h"
#include "vec2d.h"
#include "fourier_descriptors.h"
#include "contour_extractor.h"
#include "exception.h"

namespace imago
{
   OrientationFinder::OrientationFinder( const CharacterRecognizer &cr ) : _letters(""), _cr(cr)
   {
   }

   OrientationFinder::~OrientationFinder()
   {
   }

   int OrientationFinder::findFromSymbols( const SegmentDeque &symbols )
   {
      BOOST_FOREACH(Segment *s, symbols)
      {
         int r; char c; double d;
         boost::tie(r, c, d) = _processSymbol(*s);
         if (r == -1)
            continue;
         printf("%d %c %lf\n", r, c, d);
      }
      return 123;
   }

   boost::tuple<int, char, double>
   OrientationFinder::_processSymbol( const Segment &seg )
   {
      int x, y;
      int w = seg.getWidth(), h = seg.getHeight();
      double d = 0, dist_ul, dist_ur, dist_dl, dist_dr;
      dist_ul = dist_ur = dist_dl = dist_dr = 1e16;
      Vec2d ul, ur, dl, dr;
      char c, best_c;
      double best_d;
      int best_r;

      SymbolFeatures features;
      int count = _cr.getDescriptorsCount();
      ContourExtractor contour_ext;
      Points approxContour, contour;

      try
      {
         contour_ext.getRawContour(seg, contour);
      }
      catch (NoContourException &e)
      {
         return boost::make_tuple(-1, -1, -1);
      }

      const byte *segData = seg.getData();
      for (int i = 0; i < w * h; i++)
      {
         if (segData[i] == 255) //white
            continue;

         x = i % w; y = i / w;

         d = sqrt((double)x * x + y * y);
         if (dist_ul - d > EPS)
         {
            dist_ul = d;
            ul.set(x, y);
         }

         d = sqrt((double)(w - 1 - x) * (w - 1 - x) + y * y);
         if (dist_ur - d > EPS)
         {
            dist_ur = d;
            ur.set(x + 1, y);
         }

         d = sqrt((double)x * x + (h - 1 - y) * (h - 1 - y));
         if (dist_dl - d > EPS)
         {
            dist_dl = d;
            dl.set(x, y + 1);
         }

         d = sqrt((double)(w - 1 - x) * (w - 1 - x) + (h - 1 - y) * (h - 1 - y));
         if (dist_dr - d > EPS)
         {
            dist_dr = d;
            dr.set(x + 1, y + 1);
         }

      }

      assert(std::find(contour.begin(), contour.end(), ul) != contour.end());
      assert(std::find(contour.begin(), contour.end(), ur) != contour.end());
      assert(std::find(contour.begin(), contour.end(), dl) != contour.end());
      assert(std::find(contour.begin(), contour.end(), dr) != contour.end());

      features.init = features.recognizable = 1;
      features.inner_contours_count = -1;
      const std::string &candidates = CharacterRecognizer::upper +
                                      CharacterRecognizer::lower +
                                      CharacterRecognizer::digits;

      //Not rotated
      approxContour = contour;
      contour_ext._approximize(approxContour);
      FourierDescriptors::calculate(approxContour, count, features.descriptors);
      c = _cr.recognize(features, candidates, &d);
      best_r = 0;
      best_c = c;
      best_d = d;

      //Rotated 90 cw
      _rotateContourTo(ur, contour);
      approxContour = contour;
      contour_ext._approximize(approxContour);
      FourierDescriptors::calculate(approxContour, count, features.descriptors);
      c = _cr.recognize(features, candidates, &d);
      if (d < best_d)
         best_r = 90, best_c = c, best_d = d;

      //Rotated 180
      _rotateContourTo(dr, contour);
      approxContour = contour;
      contour_ext._approximize(approxContour);
      FourierDescriptors::calculate(approxContour, count, features.descriptors);
      c = _cr.recognize(features, candidates, &d);
      if (d < best_d)
         best_r = 180, best_c = c, best_d = d;

      //Rotated 90 ccw (270)
      _rotateContourTo(dl, contour);
      approxContour = contour;
      contour_ext._approximize(approxContour);
      FourierDescriptors::calculate(approxContour, count, features.descriptors);
      c = _cr.recognize(features, candidates, &d);
      if (d < best_d)
         best_r = 270, best_c = c, best_d = d;

      return boost::make_tuple(best_r, best_c, best_d);
   }

   void OrientationFinder::_rotateContourTo( const Vec2d &p, Points &contour )
   {
      Points ncontour;
      Points::iterator it = find(contour.begin(), contour.end(), p);

      ncontour.insert(ncontour.begin(), it, contour.end());
      ncontour.insert(ncontour.end(), contour.begin() + 1, it + 1);

      contour.assign(ncontour.begin(), ncontour.end());
   }
}
