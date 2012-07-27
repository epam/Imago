#pragma once
#ifndef _recognition_distance_h
#define _recognition_distance_h

#include <vector>
#include <string>
#include <map>
#include "comdef.h"

namespace imago
{
	class RecognitionDistance : public std::map<char, double>
	  {
	  protected:
		  typedef std::pair<char, double> PrVecItem;
		  typedef std::vector<PrVecItem> PrVec;

		  void fillVector(PrVec &out) const;

		  static bool sortCompareFunction(const PrVecItem& i1, const PrVecItem& i2)
		  {
			  return i1.second < i2.second;
		  }

	  public:		  

		  /// returns best matched symbol and its distance
		  char getBest(double* dist = NULL) const;
		  
		  /// returns the difference between two best symbols recognized
		  double getQuality() const;

		  /// returns best symbol and others differs no more than max_diff
		  std::string getRangedBest(double max_diff = 0.5) const;
		  
		  /// selects best from both tables
		  void mergeTables(const RecognitionDistance& second);

		  /// multiply distance for specified sym_set by factor
		  void adjust(double factor, const std::string& sym_set);
	  };

	typedef std::map<qword, RecognitionDistance> RecognitionDistanceCacheType;
}

#endif // _recognition_distance_h
