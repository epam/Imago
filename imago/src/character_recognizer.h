#ifndef _character_recognizer_h
#define _character_recognizer_h

#include <string>
#include <vector>

#include "symbol_features.h"

namespace imago
{
   class Segment;
   class CharacterRecognizer
   {
   public:
      static std::string upper, lower, digits;
      CharacterRecognizer( int k );
      CharacterRecognizer( int k, const std::string &filename );

      char recognize( const SymbolFeatures &features,
                      const std::string &candidates, double *err = 0) const;

      char recognize( const Segment &seg, const std::string &candidates,
                      double *err = 0) const;
      ~CharacterRecognizer();

   private:
      bool _loaded;
      void _loadBuiltIn();
      void _loadFromFile( const std::string &filename );
      static double _compareDescriptors( const std::vector<double> &d1,
                                         const std::vector<double> &d2 );

      static double _compareFeatures( const SymbolFeatures &f1,
                                      const SymbolFeatures &f2 );
      struct SymbolClass
      {
         char sym;
         std::vector<SymbolFeatures> shapes;
      };

      int _k;
      int _count;
      std::vector<SymbolClass> _classes;
      std::vector<int> _mapping;
   };
}

#endif /* _character_recognizer_h */
