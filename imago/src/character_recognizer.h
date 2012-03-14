#ifndef _character_recognizer_h
#define _character_recognizer_h

#include <string>
#include <vector>
#include <map>

#include "symbol_features.h"

#include "segment.h"
#include "stl_fwd.h"

namespace imago
{
   bool isCircle (Image &seg);

   class Segment;

	class RecognitionProbability : public std::map<char, double>
	  {
	  public:
		  /// returns best matched symbol & its distance
		  char getBest(double* dist = NULL) const;
		  /// returns the difference between best symbols recognized
		  double getQuality() const;
	  };

   class CharacterRecognizer
   {
   public:	  
      CharacterRecognizer( int k );
      CharacterRecognizer( int k, const std::string &filename );

      RecognitionProbability recognize( const SymbolFeatures &features,
                      const std::string &candidates) const;

      char recognize( const Segment &seg, const std::string &candidates,
                      double *distance = 0) const;

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
      SymbolFeatures features_h4;
      SymbolFeatures features_h5;
      SymbolFeatures features_h6;
      SymbolFeatures features_h7;
      SymbolFeatures features_h8;
      SymbolFeatures features_h9;
      SymbolFeatures features_h10;
      SymbolFeatures features_h11;
            
      SymbolFeatures features_n1;
      SymbolFeatures features_n2;
      SymbolFeatures features_n3;
      SymbolFeatures features_n4;
      SymbolFeatures features_n5;
      SymbolFeatures features_n6;
      HWCharacterRecognizer ( const CharacterRecognizer &cr );

      int recognize (Segment &seg);
   protected:
      const CharacterRecognizer &_cr;
      void _readFile(const char *filename, SymbolFeatures &features);
};


}

#endif /* _character_recognizer_h */
