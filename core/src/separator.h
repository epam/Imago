/****************************************************************************
* Copyright (C) from 2009 to Present EPAM Systems.
*
* This file is part of Imago toolkit.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***************************************************************************/

#pragma once
#ifndef _separator_h
#define _separator_h

#include "stl_fwd.h"
#include <queue>
#include <vector>
#include "rectangle.h"
#include "algebra.h"
#include "settings.h"
#include "line_priority_queue.h"
#include "character_recognizer.h"

namespace imago
{
   class Segment;
   class Image;

   class Separator
   {
   public:      

	Separator( SegmentDeque &segs, const Image &img );

/// Struct for reporting classification results for a segment
	  struct ClassifierResults{
		  int HuMoments;
		  int Ratios;
		  int KNN;
		  int Probability;
		  int OverAll;
		  bool Processed;
		  int KNNRatios;

		  ClassifierResults(){
			  HuMoments = Ratios  = KNN = Probability = OverAll = KNNRatios = -1;
			  Processed = false;
		  }
	  };

	  void ClassifySegment(const Settings& vars, SegmentDeque &layer_symbols, CharacterRecognizer &rec, Segment* seg, ClassifierResults &cresults);

	  void Separate(Settings& vars, CharacterRecognizer &rec, SegmentDeque &layer_symbols, SegmentDeque &layer_graphics );

	  void SeparateStuckedSymbols(const Settings& vars, SegmentDeque &layer_symbols, SegmentDeque &layer_graphics, CharacterRecognizer &rec );

   private:

      SegmentDeque &_segs;
      const Image &_img;

      enum
      {
         SEP_BOND,
         SEP_SYMBOL,
         SEP_SPECIAL,
         SEP_SUSPICIOUS
      };
     
      int _estimateCapHeight(const Settings& vars, bool &restrictedHeight);

      bool _testDoubleBondV(const Settings& vars, Segment &segment );

	  int _getApproximationSegmentsCount (const Settings& vars, Segment *cur_seg );
      
	  bool _analyzeSpecialSegment(const Settings& vars, Segment *cur_seg);

      bool _checkSequence(const Settings& vars, IntPair &checking, IntPair &symbols_graphics, double &density );
      
	  static bool _segmentsComparator( Segment *a, Segment *b );
	  
	  bool _bIsTextContext(const Settings& vars, SegmentDeque &layer_symbols, Rectangle rec);
      
	  Separator( const Separator &S );
	  
	  int HuClassifier(const Settings& vars, Image &im);

	  int PredictGroup(const Settings& vars, Segment *seg, int mark, SegmentDeque &layer_symbols);

	  int ClusterLines(const Settings& vars,Points2d& inputLines, IntVector& outClasses);
   };
}


#endif /* _separator_h */
