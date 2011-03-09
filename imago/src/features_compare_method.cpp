#include <cstdio>

#include "features_compare_method.h"
#include "exception.h"

namespace imago
{
   FeaturesCompareMethod::~FeaturesCompareMethod()
   {
      std::vector<SymbolClass>::iterator it_c;
      std::deque<IFeatures*>::iterator it_f;
      for (it_c = _classes.begin(); it_c != _classes.end(); ++it_c)
         for (it_f = it_c->second.begin(); it_f != it_c->second.end(); ++it_f)
            delete *it_f;
   }

   void FeaturesCompareMethod::train( const TrainSet &ts )
   {
      TrainSet::const_iterator it;
      for (it = ts.begin(); it != ts.end(); ++it)
      {
         SymbolClass *cls = 0;
         if (_mapping[it->second] == -1)
         {
            _classes.push_back(std::vector<SymbolClass>::value_type());
            _mapping[it->second] = _classes.size() - 1;
            cls = &_classes.back();
         }
         else
            cls = &_classes[_mapping[it->second]];

         cls->second.push_back(_extract(*it->first));
      }
   }

   void FeaturesCompareMethod::save( Output &o ) const
   {
      _writeHeader(o);
   }

   void FeaturesCompareMethod::load( const std::string &filename )
   {
      FILE *fi = fopen(filename.c_str(), "r");
      if (!fi)
         throw IOException("Cannot open file %s", filename.c_str());

      _readHeader(fi);
   }

   void FeaturesCompareMethod::_getSuspects( const Image *img, int count,
                                             std::deque<Suspect> &s ) const
   {

   }
}
