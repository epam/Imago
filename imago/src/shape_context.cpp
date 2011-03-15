#include "shape_context.h"
#include "output.h"
#include "image.h"
#include "opencv/highgui.h"

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
      _calcBestMapping(my_sc, o_sc, mapping);

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

   void ShapeContextFeatures::_extractContourPoints()
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
         _sample.assign(all.begin(), all.end());
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

         _sample.assign(all_shuffled.begin(), all_shuffled.begin() + _count);

         _meanR = 0;
         Points2i::const_iterator b = _sample.begin(), e = _sample.end();
         for (Points2i::const_iterator it = b; it != e; ++it)
         {
            for (Points2i::const_iterator it2 = b; it2 != e; ++it2)
            {
               if (it2 == it)
                  continue;

               _meanR += Vec2i::distance(*it, *it2);
            }
         }
         _meanR /= _sample.size() * (_sample.size() - 1);

#ifdef DEBUG
         for (int i = 0; i < (int)_sample.size(); ++i)
         {
            res.at<byte>(_sample[i].y, _sample[i].x) = 0;
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
      Points2i::iterator pit;
      sc.resize(sample.points.size());
      ShapeContext::iterator sit;
      for (pit = sample.points.begin(), sit = sc.begin(); pit != sample.points.end(); ++pit, ++sit)
      {
         sit->p = *pit;
         _calcPointContext(sit->p, sit->context);
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
         assert(sum > 0);
         d += diff * diff / sum;
      }
      d /= 2;

      return d;
   }
}
