#ifndef _fourier_features_h
#define _fourier_features_h

#include <vector>

#include "classification.h"
#include "features_compare_method.h"

namespace imago
{
   class Image;
   class Output;

   class FourierFeatures: public IFeatures
   {
   public:
      FourierFeatures( int count );
      virtual ~FourierFeatures();

      void extract( const Image &img );
      double compare( const IFeatures *other ) const;

      void write( Output &o ) const;
      void read( Scanner &s );

   protected:
      typedef std::vector<double> Descriptors;
      virtual double _distance( const Descriptors &a,
                                const Descriptors &b ) const;

   private:
      int _count;

      Descriptors _outer;
      std::vector<Descriptors> _inner;
   };

   class FourierFeaturesCompareMethod: public FeaturesCompareMethod
   {
   public:
      FourierFeaturesCompareMethod( int count, int k ):
         FeaturesCompareMethod(k), _count(count)
      {};
      FourierFeaturesCompareMethod(): FeaturesCompareMethod()
      {};
      ~FourierFeaturesCompareMethod()
      {};

   private:
      int _count;

   protected:
      virtual IFeatures *_extract( const Image &img ) const;

      virtual void _readHeader( Scanner &s );
      virtual IFeatures* _readFeatures( Scanner &s ) const;
      virtual void _writeHeader( Output &o ) const;
   };
}

#endif /* _fourier_features_h */
