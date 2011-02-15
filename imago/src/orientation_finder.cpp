#include <cmath>
#include "boost/foreach.hpp"

#include "orientation_finder.h"
#include "vec2d.h"
#include "fourier_descriptors.h"
#include "contour_extractor.h"
#include "exception.h"
#include "segmentator.h"

namespace imago
{
   OrientationFinder::OrientationFinder( const CharacterRecognizer &cr ) : _cr(cr)
   {
   }

   OrientationFinder::~OrientationFinder()
   {
   }

   int OrientationFinder::findFromSymbols( const SegmentDeque &symbols )
   {
      int rotations[4] = {0};
      double dists[4] = {0.0};
      int r; char c, cup; double d;
      static const std::string bioriented = "BCDEHIKNPSUMWZbcdiklnpqsuz";
      std::vector<boost::tuple<int, char, double> > skipped;
      BOOST_FOREACH(Segment *s, symbols)
      {
         boost::tuple<int, char, double> tup = _processSymbol(*s);
         boost::tie(r, c, d) = tup;
         if (r == -1)
            continue;

         cup = toupper(c);
         if (cup == 'O' || cup == '0' || cup == 'X')
            continue;

         rotations[r]++;
         dists[r] += d;

         if (std::find(bioriented.begin(), bioriented.end(), c) != bioriented.end())
         {
            r = (r + 2) % 4;
            rotations[r]++;
            dists[r] += d;
         }
      }

      r = -1; d = 1e16;
      for (int i = 0; i < 4; i++)
         if (rotations[i] > 0 && dists[i] / rotations[i] < d)
            d = dists[i] / rotations[i], r = i;

      return r;
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
      //TODO:It's copied from Segment::initFeatures
      //Segment's inner parts
      features.inner_contours_count = 0;
      SegmentDeque segments;
      Segmentator::segmentate(seg, segments, 3, 255); //all white parts
      BOOST_FOREACH(Segment *in_seg, segments)
      {
         int in_x = in_seg->getX(), in_y = in_seg->getY(), in_w =
             in_seg->getWidth(), in_h = in_seg->getHeight();
         if (in_x == 0 || in_y == 0 || in_x + in_w == w || in_y + in_h == h)
            continue;

         features.inner_contours_count++;
      }
      features.inner_descriptors.resize(features.inner_contours_count);

      const std::string &candidates = CharacterRecognizer::upper +
                                      CharacterRecognizer::lower +
                                      "123456";

      //Not rotated
      approxContour = contour;
      contour_ext._approximize(approxContour);
      FourierDescriptors::calculate(approxContour, count, features.descriptors);
      c = _cr.recognize(features, candidates, &d);
      best_r = 0, best_c = c, best_d = d;

      //Rotated 90 cw
      _rotateContourTo(ur, contour);
      approxContour = contour;
      contour_ext._approximize(approxContour);
      FourierDescriptors::calculate(approxContour, count, features.descriptors);
      c = _cr.recognize(features, candidates, &d);
      if (d < best_d)
         best_r = 1, best_c = c, best_d = d;

      //Rotated 180
      _rotateContourTo(dr, contour);
      approxContour = contour;
      contour_ext._approximize(approxContour);
      FourierDescriptors::calculate(approxContour, count, features.descriptors);
      c = _cr.recognize(features, candidates, &d);
      if (d < best_d)
         best_r = 2, best_c = c, best_d = d;

      //Rotated 90 ccw (270)
      _rotateContourTo(dl, contour);
      approxContour = contour;
      contour_ext._approximize(approxContour);
      FourierDescriptors::calculate(approxContour, count, features.descriptors);
      c = _cr.recognize(features, candidates, &d);
      if (d < best_d)
         best_r = 3, best_c = c, best_d = d;

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
