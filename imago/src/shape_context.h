#ifndef _shape_context_h_
#define _shape_context_h_

#include "features_compare_method.h"
#include "vec2d.h"
#include "stl_fwd.h"
#include <opencv/cv.h>


namespace imago
{
   class Image;

   class ShapeContextFeatures: public IFeatures
   {
   public:
      ShapeContextFeatures( int count, int rBins, int thetaBins );
      virtual ~ShapeContextFeatures();

      void extract( const Image &img );
      double compare( const IFeatures *other ) const;

      void write( Output &o ) const;
      void read( /*Input*/FILE *fi );
   private:
      cv::Mat _img;
      int _binsR, _binsT, _count;

      typedef std::vector<double> Context;
      struct PointWithContext
      {
         Vec2i p;
         Context context;
      };
      typedef std::vector<PointWithContext> ShapeContext;

      struct Sample
      {
         Point2i points;
         double meanR;
      };

      void _extractContourPoints( Sample &sample ) const;
      void _calcShapeContext( const Sample &sample, ShapeContext &sc ) const;
      void _calcPointContext( const Sample &sample, const Vec2i &point,
                              Context &context ) const;

      double _contextDistance( const Context &a, const Context &b ) const;

      void _calcBestMapping( const ShapeContext &a,
                             const ShapeContext &b,
                             std::vector<int> &mapping ) const;

      //Spline

      //Copy of the Image?

      //Three distances

      inline int _ii2i( int r, int t ) const;
      inline std::pair<int, int> _i2ii( int v ) const;
   };

   class ShapeContextCompareMethod: public FeaturesCompareMethod
   {
   public:
      ShapeContextCompareMethod():
         FeaturesCompareMethod(), _count(-1)
      {};
      ShapeContextCompareMethod( int count, int k ):
         FeaturesCompareMethod(k), _count(count)
      {}

   protected:
      int _count;
      virtual IFeatures *_extract( const Image &img ) const;

      virtual void _readHeader( /*Input*/FILE *fi );
      virtual IFeatures* _readFeatures( /*Input*/FILE *fi ) const;
      virtual void _writeHeader( Output &o ) const;
   };
}

#endif /* _shape_context_h_ */
