#ifndef _shape_context_h_
#define _shape_context_h_

#include "features_compare_method.h"
#include "vec2d.h"
#include "stl_fwd.h"

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
      int _rBins, _thetaBins, _count;

      typedef std::vector<int> Context;
      struct PointWithContext
      {
         Vec2i p;
         Context context;
      };
      typedef std::vector<PointWithContext> ShapeContext;

      void _extractContourPoints( Points2i &sample ) const;
      void _calcShapeContext( const Vec2i &point,
                              ShapeContext &contexts ) const;

      double _contextDistance( const Context &a, const Context &b ) const;
      double _distance( const ShapeContext &a, const ShapeContext &b,
                        const std::vector<int> *mapping = 0) const;
      void _calcBestMapping( const ShapeContext &a,
                             const ShapeContext &b,
                             std::vector<int> &mapping ) const;

      //Spline

      //Copy of the Image?

      //Three distances

      ShapeContext _sc;

      inline int _ii2i( int a, int b );
      inline void _i2ii( int a, int b );
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
