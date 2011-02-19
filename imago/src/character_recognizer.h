#ifndef _character_recognizer_h
#define _character_recognizer_h

#include <string>
#include <vector>

#include "symbol_features.h"

#include "segment.h"
#include "stl_fwd.h"

namespace imago
{
   bool isCircle (Image &seg);

   class Segment;
   class CharacterRecognizer
   {
   public:
      CharacterRecognizer( int k );
      CharacterRecognizer( int k, const std::string &filename );

      char recognize( const SymbolFeatures &features,
                      const std::string &candidates, double *err = 0) const;

      char recognize( const Segment &seg, const std::string &candidates,
                      double *err = 0) const;
      inline int getDescriptorsCount() const {return _count;}
      ~CharacterRecognizer();

      static const std::string upper, lower, digits;
      static double _compareFeatures( const SymbolFeatures &f1,
                                      const SymbolFeatures &f2 );
   private:
      bool _loaded;
      void _loadBuiltIn();
      void _loadFromFile( const std::string &filename );
      static double _compareDescriptors( const std::vector<double> &d1,
                                         const std::vector<double> &d2 );

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

   class HWCharacterRecognizer
   {
   public:
      SymbolFeatures features_h1;
      SymbolFeatures features_h2; 
      SymbolFeatures features_h3;
      SymbolFeatures features_n1;
      SymbolFeatures features_n2;
      SymbolFeatures features_n3;
      HWCharacterRecognizer ();

      int recognize (Segment &seg);
   protected:
      CharacterRecognizer _cr;
      void _readFile(const char *filename, SymbolFeatures &features);
};


}

#endif /* _character_recognizer_h */
