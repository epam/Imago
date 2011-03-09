#ifndef _fourier_desc_method_h
#define _fourier_desc_method_h

#include "ocr.h"

#include <vector>
#include <deque>

namespace imago
{
   class FeaturesCompareMethod: public IRecognitionMethod
   {
   public:
      FeaturesCompareMethod( int k_neighbours ) : _k(k_neighbours),
                                                  _mapping(256, -1)
      {};
      virtual ~FeaturesCompareMethod();

      void train( const TrainSet &ts );

      void save( Output &o ) const;
      void load( /*Input*/ const std::string &filename );

   protected:
      virtual IFeatures *_extract( const Image &img ) const = 0;
      virtual double _compare( const IFeatures *a, const IFeatures *b ) = 0;

      virtual void _readHeader( /*Input*/ FILE *fi ) {};
      virtual void _writeHeader( Output &o ) const {};

   private:
      int _k;
      void _getSuspects( const Image *img, int count,
                         std::deque<Suspect> &s ) const;

      typedef std::pair<char, std::deque<IFeatures*> > SymbolClass;
      std::vector<SymbolClass> _classes;
      std::vector<int> _mapping;
   };
}

#endif /* _fourier_desc_method_h */
