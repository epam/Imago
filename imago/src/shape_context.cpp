#include <opencv/highgui.h>

#include "munkres.h"
#include "tpsinterpolate.h"
#include "affine_transform.h"

#include "shape_context.h"
#include "output.h"
#include "image.h"

#ifdef DEBUG
#include "image_draw_utils.h"
#include "image_utils.h"
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
            _img.at<byte>(k, l) = img.getByte(l, k);
         }
      }
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

      //TODO: Move it to "extract"?
      Sample my_sample, o_sample;
      _extractContourPoints(my_sample);
      fothers->_extractContourPoints(o_sample);

      ShapeContext my_sc, o_sc;
      _calcShapeContext(my_sample, my_sc);
      fothers->_calcShapeContext(o_sample, o_sc);

      assert(my_sc.size() == o_sc.size());
      std::vector<int> mapping;
#ifdef DEBUG
      puts("Mapping");
#endif
      _calcBestMapping(my_sc, o_sc, mapping);
#ifdef DEBUG
      puts("Mapping done");
#endif


#ifdef DEBUG
      {
         Image img(__max(_img.cols, fothers->_img.cols),
                   __max(_img.rows, fothers->_img.rows));

         img.fillWhite();
         for (int i = 0; i < mapping.size(); ++i)
         {
            Vec2i &a = my_sample.points[i], &b = o_sample.points[mapping[i]];
            ImageDrawUtils::putCircle(img, a.x, a.y, 2, 0);
            ImageDrawUtils::putCircle(img, b.x, b.y, 7, 50);
            ImageDrawUtils::putLineSegment(img, a, b, 128);
         }

         ImageUtils::saveImageToFile(img, "mapping.png");
      }
#endif
/*
      std::vector<boost::array<double, 2> > positions(mapping.size());
      //std::vector<boost::array<double, 1> > values_x(mapping.size());
      //std::vector<boost::array<double, 1> > values_y(mapping.size());
      std::vector<boost::array<double, 2> > values(mapping.size());

      for (int i = 0; i < my_sample.points.size(); ++i)
      {
         positions[i][0] = my_sample.points[i].x;
         positions[i][1] = my_sample.points[i].y;
         values[i][0] = o_sample.points[i].x;
         values[i][1] = o_sample.points[i].y;
      }

      tps::ThinPlateSpline<2, 2> tpsX(positions, values);
      //tps::ThinPlateSpline<2, 1> tpsY(positions, values_y);
*/

      affine::AffineTransform at(my_sample.points, o_sample.points, mapping);

#ifdef DEBUG
      {
         Image img(__max(_img.cols, fothers->_img.cols),
                   __max(_img.rows, fothers->_img.rows));

         img.fillWhite();
         Sample sss;
         _extractContourPoints(sss);
         for (int i = 0; i < my_sample.points.size(); ++i)
         {
            Vec2i &a = sss.points[i];
            //boost::array<double, 2> pos;
            //pos[0] = a.x, pos[1] = a.y;
            //pos = tpsX.interpolate(pos);
            Vec2i b = at.interpolate(a); //(pos[0], pos[1]);
            ImageDrawUtils::putCircle(img, a.x, a.y, 2, 0);
            ImageDrawUtils::putCircle(img, b.x, b.y, 7, 50);
            ImageDrawUtils::putLineSegment(img, a, b, 128);
         }

         ImageUtils::saveImageToFile(img, "spline.png");
      }
#endif

      return 0;
   }

   void ShapeContextFeatures::read( /*Input*/ FILE *fi )
   {
      throw LogicException("Not implemented");
   }

   void ShapeContextFeatures::write( Output &o ) const
   {
      throw LogicException("Not implemented");
   }

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

   void ShapeContextFeatures::_calcShapeContext( const Sample &sample, ShapeContext &sc ) const
   {
      Points2i::const_iterator pit;
      sc.resize(sample.points.size());
      ShapeContext::iterator sit;
      for (pit = sample.points.begin(), sit = sc.begin(); pit != sample.points.end(); ++pit, ++sit)
      {
         sit->p = *pit;
         _calcPointContext(sample, sit->p, sit->context);
      }
   }

   void ShapeContextFeatures::_calcPointContext( const Sample &sample, const Vec2i &point, Context &context ) const
   {
      context.resize(_binsR * _binsT, 0);

      double minR = 1e16, maxR = 0;

      for (Points2i::const_iterator it = sample.points.begin(); it != sample.points.end(); ++it)
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
      double leftR = log(minR / sample.meanR), rightR = log(maxR / sample.meanR);

      double stepR = (rightR - leftR) / (_binsR - 1);
      double stepT = (2 * PI - 0) / (_binsT - 1);

#ifdef DEBUG
      printf("R: %lf %lf\nSteps:%lf %lf\n***\n", leftR, rightR, stepR, stepT);
#endif

      const Vec2i UP(0, 1);
      for (Points2i::const_iterator it = sample.points.begin(); it != sample.points.end(); ++it)
      {
         if (*it == point)
            continue;

         Vec2i v;
         v.diff(*it, point);
         double logRscaled = log(v.norm() / sample.meanR);
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

#ifdef DEBUG
         //printf("   %lf %lf %lf", leftR, logRscaled, rightR);
         printf("   Bins: %d %d\n", binR, binT);
#endif
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
         //assert(sum > 0);
         if (sum < 1e-6)
         {
#ifdef DEBUG
            //printf("\t***SKIPPING ZERO IN DISTANCE***\n", sum);
#endif
            continue;
         }
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
