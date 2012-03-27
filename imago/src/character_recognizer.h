#ifndef _character_recognizer_h
#define _character_recognizer_h

#include <string>
#include <vector>
#include <map>

#include "character_recognizer_data.h"
#include "symbol_features.h"

#include "segment.h"
#include "stl_fwd.h"
#include "recognition_distance.h"
#include "segment_tools.h"

namespace imago
{
   bool isCircle (Image &seg);

   class Segment;

   bool isPossibleCharacter(const Segment& seg, bool loose_cmp = false);
	
   class CharacterRecognizer: CharacterRecognizerData
   {
   public:
      CharacterRecognizer( int k );
      CharacterRecognizer( int k, const std::string &filename );

      RecognitionDistance recognize( const SymbolFeatures &features,
                                     const std::string &candidates, bool wide_range = false ) const;

      RecognitionDistance recognize_all( const Segment &seg, const std::string &candidates = all ) const;

	  char recognize( const Segment &seg, const std::string &candidates,
                      double *distance = 0 ) const;

      inline int getDescriptorsCount() const {return _count;}
      ~CharacterRecognizer();

      static const std::string upper, lower, digits, all;

      static double _compareFeatures( const SymbolFeatures &f1,
                                      const SymbolFeatures &f2 );
   private:
      void _loadData( std::istream &in );
      static double _compareDescriptors( const std::vector<double> &d1,
                                         const std::vector<double> &d2 );      
      int _k;
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
