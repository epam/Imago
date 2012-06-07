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
#include "settings.h"

namespace imago
{
   class Segment;   
	
   class CharacterRecognizer: CharacterRecognizerData
   {
   public:
	  bool isPossibleCharacter(const Settings& vars, const Segment& seg, bool loose_cmp = false, char* result = NULL);  

      CharacterRecognizer( int k );
      CharacterRecognizer( int k, const std::string &filename );

      RecognitionDistance recognize(const Settings& vars, const SymbolFeatures &features,
                                     const std::string &candidates, bool wide_range = false ) const;

      RecognitionDistance recognize_all(const Settings& vars, const Segment &seg, 
		                                 const std::string &candidates = all,
										 bool can_adjust = true) const;

	  char recognize(const Settings& vars, const Segment &seg, const std::string &candidates,
                      double *distance = 0 ) const;

      inline int getDescriptorsCount() const {return _count;}
      ~CharacterRecognizer();

      static const std::string upper; 
	  static const std::string lower;
	  static const std::string digits;
	  static const std::string charges;
	  static const std::string all;
	  static const std::string like_bonds;

      static double _compareFeatures(const Settings& vars,  const SymbolFeatures &f1,
                                      const SymbolFeatures &f2 );
   private:
      void _loadData( std::istream &in );
      static double _compareDescriptors(const Settings& vars,  const std::vector<double> &d1,
                                         const std::vector<double> &d2 );      
      int _k;
   };

}

#endif /* _character_recognizer_h */
