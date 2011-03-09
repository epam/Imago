#ifndef _fourier_features_h
#define _fourier_features_h

#include <vector>

#include "ocr.h"

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
      void read( /*Input*/ FILE *fi );

   protected:
      typedef std::vector<double> Descriptors;
      virtual double _distance( const Descriptors &a,
                                const Descriptors &b ) const;

   private:
      int _count;

      Descriptors _outer;
      bool _has_inner;
      std::vector<Descriptors> _inner;
   };
}

#endif /* _fourier_features_h */
