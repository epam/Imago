#include <opencv/highgui.h>
#include "boost/foreach.hpp"
#include "boost/scoped_ptr.hpp"

#include "munkres.h"
#include "tpsinterpolate.h"

#include "shape_context.h"
#include "output.h"
#include "image.h"
#include "contour_extractor.h"
#include "segmentator.h"

#include "image_utils.h"

#ifdef DEBUG
#include "image_draw_utils.h"
#endif

namespace imago
{

   ShapeContextFeatures::ShapeContextFeatures( int count, int rBins, int thetaBins ):
         _count(count), _binsR(rBins), _binsT(thetaBins)
   {
   }

   ShapeContextFeatures::~ShapeContextFeatures()
   {

   }

   void ShapeContextFeatures::extract( const Image &img )
   {
      _img.create(img.getHeight(), img.getWidth(), CV_8U);

      for (int k = 0; k < img.getHeight(); k++)
      {
         for (int l = 0; l < img.getWidth(); l++)
         {
            byte v = img.getByte(l, k);
            _img.at<byte>(k, l) = v;
            if (v != 255)
               _image_sample.points.push_back(Vec2i(l, k));
         }
      }

      _calcSampleMean(_image_sample);
      _extractContourPoints();
   }

   double ShapeContextFeatures::compare( const IFeatures *other ) const
   {
      const ShapeContextFeatures *fothers =
            static_cast<const ShapeContextFeatures*>(other);

      if (this->_count != fothers->_count)
         throw LogicException("Cannot compare ShapeContext "
                              "with different sample size");
      if (this->_binsR != fothers->_binsR || this->_binsT != fothers->_binsT)
         throw LogicException("Cannot compare Contexts with different size!"
                              " Not implemented!");

      ShapeContext my_sc, o_sc;
      _calcShapeContext(my_sc);
      fothers->_calcShapeContext(o_sc);

      assert(my_sc.size() == o_sc.size());
      std::vector<int> mapping;

      DPRINTF("Mapping\n");
      _calcBestMapping(my_sc, o_sc, mapping);
      DPRINTF("Mapping done\n");

#ifdef DEBUG
      {
         Image img(__max(_img.cols, fothers->_img.cols),
                   __max(_img.rows, fothers->_img.rows));

         img.fillWhite();
         for (int i = 0; i < mapping.size(); ++i)
         {
            const Vec2i &a = _sample.points[i], &b = fothers->_sample.points[mapping[i]];
            ImageDrawUtils::putCircle(img, a.x, a.y, 2, 0);
            ImageDrawUtils::putCircle(img, b.x, b.y, 7, 50);
            ImageDrawUtils::putLineSegment(img, a, b, 128);
         }

         ImageUtils::saveImageToFile(img, "mapping.png");
      }
#endif

      std::vector<boost::array<double, 2> > positions(mapping.size());
      std::vector<boost::array<double, 2> > values(mapping.size());

      for (int i = 0; i < _sample.points.size(); ++i)
      {
         positions[i][0] = _sample.points[i].x;
         positions[i][1] = _sample.points[i].y;
         values[i][0] = fothers->_sample.points[mapping[i]].x;
         values[i][1] = fothers->_sample.points[mapping[i]].y;
      }

      boost::scoped_ptr<tps::ThinPlateSpline<2, 2> > tps;
      try
      {
         tps.reset(new tps::ThinPlateSpline<2, 2>(positions, values));
      }
      catch(boost::numeric::ublas::singular &e)
      {
         puts("Cannot calculate TPS. Singular matrix.");
         fflush(stdout);
         return -1.0f;
      }

#if 1//def DEBUG
      {
         Image img(__max(_img.cols, fothers->_img.cols),
                   __max(_img.rows, fothers->_img.rows));
         img.fillWhite();

         for (int i = 0; i < _img.rows; ++i)
         {
            for (int j = 0; j < _img.cols; ++j)
            {
               if (_img.at<byte>(i, j) == 255)
                  continue;

               boost::array<double, 2> pos;
               pos[0] = j, pos[1] = i;
               pos = tps->interpolate(pos);
               Vec2i t(pos[0], pos[1]);
               if (t.x < 0 || t.x >= img.getWidth() ||
                   t.y < 0 || t.y >= img.getHeight())
                  continue;

               img.getByte(t.x, t.y) = _img.at<byte>(i, j);
            }
         }

         ImageUtils::saveImageToFile(img, "spline2.png");
      }
#endif

      //Comparing images
      double dist = 0;
      Points2i::const_iterator pit;
      Context f1_con, f2_con;
      int s = _image_sample.points.size();
      for (pit = _image_sample.points.begin(); pit != _image_sample.points.end(); ++pit)
      {
         _calcPointContext(*pit, f1_con, IMAGE);

         boost::array<double, 2> pos;
         pos[0] = pit->x, pos[1] = pit->y;
         pos = tps->interpolate(pos);
         Vec2i t(pos[0], pos[1]);
         if (t.x < 0 || t.x >= fothers->_img.cols ||
             t.y < 0 || t.y >= fothers->_img.rows)
         {
            s--;
            continue;
         }

         fothers->_calcPointContext(t, f2_con, IMAGE);
         dist += _contextDistance(f1_con, f2_con);

         //if (fothers->_img.at<byte>(t.y, t.x) != 255)
         //   dist += 1;
      }
      //dist = 2 * dist / _image_sample.points.size() / fothers->_image_sample.points.size();
      if (s <= 0)
         dist = 0;
      else
         dist /= s;

      return dist;
   }

   void ShapeContextFeatures::read( /*Input*/ FILE *fi )
   {
      throw LogicException("Not implemented");
   }

   void ShapeContextFeatures::write( Output &o ) const
   {
      throw LogicException("Not implemented");
   }

   void ShapeContextFeatures::_calcSampleMean( Sample &sample ) const
   {
      sample.meanR = 0;
      Points2i::const_iterator b = sample.points.begin(),
            e = sample.points.end();
      for (Points2i::const_iterator it = b; it != e; ++it)
      {
         for (Points2i::const_iterator it2 = it; it2 != e; ++it2)
         {
            sample.meanR += 2 * Vec2i::distance(*it, *it2);
         }
      }
      sample.meanR /= sample.points.size() * sample.points.size();
   }


   void ShapeContextFeatures::_extractContourPoints()
   {
      Image img(_img.cols, _img.rows);
      for (int i = 0; i < _img.rows; ++i)
      {
         for (int j = 0; j < _img.cols; ++j)
         {
            img.getByte(j, i) = _img.at<byte>(i, j);
         }
      }

      Points2i contourA;
      ContourExtractor CE;
      CE.getRawContour(img, contourA);

      Points2i contour;
      for (int i = 0; i < (int)contourA.size() - 1 ; ++i)
      {
         int dx = contourA[i + 1].x - contourA[i].x;
         int dy = contourA[i + 1].y - contourA[i].y;
         if (dx == 0 && dy > 0)
            contour.push_back(Vec2i(contourA[i].x - 1, contourA[i].y));
         else if (dx == 0 && dy < 0)
            contour.push_back(contourA[i + 1]);
         else if (dy == 0 && dx > 0)
            contour.push_back(contourA[i]);
         else if (dy == 0 && dx < 0)
            contour.push_back(Vec2i(contourA[i].x - 1, contourA[i].y - 1));
      }

      //Inner contours processing
      {
         SegmentDeque segments;
         Segmentator::segmentate(img, segments, 3, 255); //all white parts

         int x, y, sw, sh;
         int _width = img.getWidth(), _height = img.getHeight();
         int total = 0;
         int i = 0;
         BOOST_FOREACH(Segment * &seg, segments)
         {
            x = seg->getX(), y = seg->getY();
            sw = seg->getWidth(), sh = seg->getHeight();

            if (x == 0 || y == 0 || x + sw == _width || y + sh == _height)
            {
               delete seg;
               continue;
            }

            CE.getRawContour(*seg, contourA);
            for (int i = 0; i < (int)contourA.size() - 1; ++i)
            {
               int dx = contourA[i + 1].x - contourA[i].x;
               int dy = contourA[i + 1].y - contourA[i].y;
               if (dx == 0 && dy > 0)
                  contour.push_back(contourA[i]);
               else if (dx == 0 && dy < 0)
                  contour.push_back(Vec2i(contourA[i].x - 1, contourA[i].y - 1));
               else if (dy == 0 && dx > 0)
                  contour.push_back(Vec2i(contourA[i].x, contourA[i].y - 1));
               else if (dy == 0 && dx < 0)
                  contour.push_back(contourA[i + 1]);
               contour.back().add(Vec2i(x, y));
            }
            delete seg;
         }
      }

      double h = 1.0 * (contour.size() - 1) / (_count - 1);
      for (int j = 0; j < _count; j++)
         _sample.points.push_back(contour[(int)(h * j)]);

#ifdef DEBUG
      for (int i = 0; i < (int)_sample.points.size(); ++i)
      {
         ImageDrawUtils::putCircle(img, _sample.points[i].x, _sample.points[i].y, 3, 128);
      }
      ImageUtils::saveImageToFile(img, "sample.png");
#endif

      _calcSampleMean(_sample);
   }
   /*
   void ShapeContextFeatures::_extractContourPoints( Sample &sample ) const
   {
      cv::Mat res;
      cv::Canny(_img, res, 1.0, 3.0, 3);

      Points2i all;

      for (int i = 0; i < res.rows; ++i)
      {
         for (int j = 0; j < res.cols; ++j)
         {
            if (res.at<byte>(i, j) == 255)
               all.push_back(Vec2i(j, i));
         }
      }

      int total = (int)all.size();

      if (total == 0)
         throw LogicException("Cannot extract contour points!");
      else if (total < _count)
         sample.points.assign(all.begin(), all.end());
      else
      {
         Points2i all_shuffled = all;
         for (int i = 0; i < 3; i++)
         {
            for (int j = total - 1; j >= 0; --j)
            {
               int r = (j == 0) ? 0 : (rand() % j);
               std::swap(all_shuffled[r], all_shuffled[j]);
            }
         }

         sample.points.assign(all_shuffled.begin(), all_shuffled.begin() + _count);

         sample.meanR = 0;
         Points2i::const_iterator b = sample.points.begin(), e = sample.points.end();
         for (Points2i::const_iterator it = b; it != e; ++it)
         {
            for (Points2i::const_iterator it2 = b; it2 != e; ++it2)
            {
               if (it2 == it)
                  continue;

               sample.meanR += Vec2i::distance(*it, *it2);
            }
         }
         sample.meanR /= sample.points.size() * (sample.points.size() - 1);

#ifdef DEBUG
         for (int i = 0; i < (int)sample.points.size(); ++i)
         {
            res.at<byte>(sample.points[i].y, sample.points[i].x) = 0;
         }
         cv::imwrite("edges.png", res);
#endif
      }
   }
   */

   inline int ShapeContextFeatures::_ii2i( int r, int t ) const
   {
      return t * _binsR + r;
   }

   inline std::pair<int, int> ShapeContextFeatures::_i2ii( int i ) const
   {
      int r = i % _binsR;
      int t = i / _binsR;
      return std::make_pair(r, t);
   }

   void ShapeContextFeatures::_calcShapeContext( ShapeContext &sc ) const
   {
      Points2i::const_iterator pit;
      sc.resize(_sample.points.size());
      ShapeContext::iterator sit;
      for (pit = _sample.points.begin(), sit = sc.begin(); pit != _sample.points.end(); ++pit, ++sit)
      {
         sit->p = *pit;
         _calcPointContext(sit->p, sit->context);
      }
   }

   void ShapeContextFeatures::_calcPointContext( const Vec2i &point, Context &context, CONTEXT_TYPE type ) const
   {
      const Sample *sample = 0;
      switch(type)
      {
         case SAMPLE:
            sample = &_sample;
            break;
         case IMAGE:
            sample = &_image_sample;
            break;
      }
      assert(sample != 0);
      context.resize(_binsR * _binsT, 0);

      double minR = 1e16, maxR = 0;

      for (Points2i::const_iterator it = sample->points.begin(); it != sample->points.end(); ++it)
      {
         if (*it == point)
            continue;

         double d = Vec2i::distance(point, *it);
         if (d < minR)
            minR = d;
         if (d > maxR)
            maxR = d;
      }

      maxR += 1;
      double leftR = log(minR / sample->meanR), rightR = log(maxR / sample->meanR);

      double stepR = (rightR - leftR) / (_binsR - 1);
      double stepT = (2 * PI - 0) / (_binsT - 1);

      //DPRINTF("R: %lf %lf\nSteps:%lf %lf\n***\n", leftR, rightR, stepR, stepT);

      const Vec2i UP(0, 1);
      for (Points2i::const_iterator it = sample->points.begin(); it != sample->points.end(); ++it)
      {
         if (*it == point)
            continue;

         Vec2i v;
         v.diff(*it, point);
         double logRscaled = log(v.norm() / sample->meanR);
         double t = Vec2i::angle(v, UP);

         if (v.x < 0)
            t += PI;

//         int binR = 0;
//         for (binR = 0; binR < _binsR - 1; ++binR)
//            if (leftR + binR * stepR <= logRscaled && logRscaled < leftR + (binR + 1) * stepR)
//               break;

         int binR = (int)floor((logRscaled - leftR) / stepR);
         int binT = (int)floor(t / stepT);

         assert(binR >= 0 && binR < _binsR);
         assert(binT >= 0 && binT < _binsT);

         //DPRINTF("   %lf %lf %lf", leftR, logRscaled, rightR);
         //DPRINTF("   Bins: %d %d\n", binR, binT);

         context[_ii2i(binR, binT)]++;
      }

      //Histogram normalization
      double sum = 0;
      for (int i = 0; i < context.size(); i++)
         sum += context[i];

      for (int i = 0; i < context.size(); i++)
         context[i] /= sum;
   }

   double ShapeContextFeatures::_contextDistance( const Context &a, const Context &b ) const
   {
      if (a.size() != b.size()) //TODO: Need to check equality of _binsR and _binsT!
         throw LogicException("Cannot compare Contexts with different size!");

      double d = 0;
      for (int i = 0; i < a.size(); ++i)
      {
         double diff = a[i] - b[i];
         double sum = a[i] + b[i];

         if (sum < 1e-6)
            continue;

         d += diff * diff / sum;
      }
      d /= 2;

      return d;
   }

   void ShapeContextFeatures::_calcBestMapping( const ShapeContext &a, const ShapeContext &b, std::vector<int> &mapping ) const
   {
      assert(a.size() == b.size());
      munkres::Matrix<double> m(a.size(), a.size());
      for (int i = 0; i < (int)a.size(); ++i)
      {
         for (int j = 0; j < (int)a.size(); ++j)
         {
            m(i, j) = _contextDistance(a[i].context, b[j].context);
         }
      }

      munkres::Munkres solver;
      solver.solve(m);

      mapping.assign(a.size(), -1);
      for (int i = 0; i < a.size(); ++i)
      {
         for (int j = 0; mapping[i] == -1 && j < a.size(); ++j)
            if (m(i, j) == 0)
               mapping[i] = j;

         if (mapping[i] == -1)
            throw LogicException("Cannot calculate best mapping!");
      }
   }
}
