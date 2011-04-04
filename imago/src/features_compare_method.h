#ifndef _fourier_desc_method_h
#define _fourier_desc_method_h

#include "classification.h"

#include <vector>
#include <deque>

namespace imago
{
   class IFeatures
   {
   public:
      IFeatures()
      {};
      virtual ~IFeatures()
      {};

      virtual void extract( const Image &img ) = 0;
      virtual double compare( const IFeatures *other ) const = 0;

      virtual void write( Output &o ) const = 0;
      virtual void read( Scanner &s ) = 0;
   };

   class FeaturesCompareMethod: public IOCRClassification
   {
   public:
      FeaturesCompareMethod( int k_neighbours ) : _k(k_neighbours),
                                                  _mapping(256, -1)
      {};
      FeaturesCompareMethod() : _k(-1), _mapping(256, -1)
      {};
      virtual ~FeaturesCompareMethod();

      void train( const TrainSet &ts );

      void save( Output &o ) const;
      void load( Scanner &s );

   protected:
      virtual IFeatures *_extract( const Image &img ) const = 0;
      //virtual double _compare( const IFeatures *a, const IFeatures *b ) = 0;

      virtual void _readHeader( Scanner &s ) {};
      virtual IFeatures* _readFeatures( Scanner &s ) const = 0;
      virtual void _writeHeader( Output &o ) const {};

   private:
      int _k;
      void _getSuspectsFrom( const Image &img, const std::deque<char> &valid,
                             int count, std::deque<Suspect> &s ) const;
      void _getSuspects( const Image &img, int count,
                         std::deque<Suspect> &s ) const;

      typedef std::pair<char, std::deque<IFeatures*> > SymbolClass;
      std::vector<SymbolClass> _classes;
      std::vector<int> _mapping;
   };
}

#endif /* _fourier_desc_method_h */
