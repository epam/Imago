/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#ifndef _separator_h
#define _separator_h

#include "stl_fwd.h"
#include <queue>
#include <vector>
#include "rectangle.h"
#include "algebra.h"

namespace imago
{
   class Segment;
   class Image;

   class Separator
   {
   public:      

      Separator( SegmentDeque &segs, const Image &img );

      void firstSeparation( SegmentDeque &layer_symbols, 
         SegmentDeque &layer_graphics );

	  void SeparateStuckedSymbols(SegmentDeque &layer_symbols, SegmentDeque &layer_graphics );

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
     
      int _estimateCapHeight();
      bool _testDoubleBondV( Segment &segment );
	  int _getApproximationSegmentsCount ( Segment *cur_seg );
      
	  bool _analyzeSpecialSegment( Segment *cur_seg, SegmentDeque &layer_graphics, SegmentDeque &layer_symbols )
	  {
		  return _getApproximationSegmentsCount(cur_seg) <= 4 /* why?! */;
	  }

      bool _checkSequence( IntPair &checking, IntPair &symbols_graphics, 
         double &density );
      bool _isSuspiciousSymbol( Segment *segment, SegmentDeque &layer_symbols, 
         int cap_height );
      static bool _segmentsComparator( Segment *a, Segment *b );
	  bool _bIsTextContext(SegmentDeque &layer_symbols, Rectangle rec);
      Separator( const Separator &S );
	  int HuClassifier(double hu[7]);

	  struct SegmentIndx
	  {
		  std::pair<Vec2d, Vec2d> _lineSegment;
		  int _indx;
	  };
	  
	  class LineSegmentComparer
	  {
	  public:
		  LineSegmentComparer()
		  {
			  _rec = Rectangle(0, 0, 0, 0);
			  _sortByPolyLine = false;
		  }

		  void SetRectangle(Rectangle rec)
		  {
			  _rec = rec;
		  }

		  void SetPolyline(std::deque<Vec2d> polyline)
		  {
			  _polyline = polyline;
		  }
		  
		  LineSegmentComparer(Rectangle rec)
		  {
			  SetRectangle(rec);
		  }
		  
		  bool operator() (const SegmentIndx &lhs, const SegmentIndx &rhs) const
		  {
			  bool retVal;
			  if(_isSortByPolyLine())
				  retVal =  CompareByPolyline(lhs, rhs);
			  else
				  retVal = CompareByRectangle(lhs, rhs);

			  return retVal;
		  }
		  
		  bool _isSortByPolyLine() const
		  {
			  return _sortByPolyLine;
		  }
		  void setSortByPolyLine(bool enable)
		  {
			  _sortByPolyLine = enable;
		  }
	  private:
		  bool CompareByPolyline(const SegmentIndx &lhs, const SegmentIndx &rhs) const
		  {
			  double d1 = CompareSegmentByPoly(lhs);
			  double d2 = CompareSegmentByPoly(rhs);

			  if(d1 == imago::MAX_LINE && d2 == imago::MAX_LINE)
			  {
				  throw imago::Exception("Lines not set");
			  }

			  return d1 > d2;
		  }

		  bool CompareByRectangle(const SegmentIndx &lhs, const SegmentIndx &rhs) const
		  {
			  double d1 = Algebra::distance2rect(lhs._lineSegment.first, _rec);
			  double d2 = Algebra::distance2rect(lhs._lineSegment.second, _rec);

			  double d3 = Algebra::distance2rect(rhs._lineSegment.first, _rec);
			  double d4 = Algebra::distance2rect(rhs._lineSegment.second, _rec);

			  double min1 = d1 < d2 ? d1  : d2;
			  double min2 = d3 < d4 ? d3 : d4;

			  return min1 > min2;
		  }

		  double CompareSegmentByPoly(const SegmentIndx &si) const
		  {
			  double retVal = imago::MAX_LINE;
			  std::deque<std::pair<Vec2d, Vec2d>>::iterator it;

			  for(size_t i = 0; i < _polyline.size(); i+=2)
			  {
				  Vec2d p1 = _polyline[i];
				  Vec2d p2 = _polyline[i+1];

				  double d1 = Algebra::distance2segment(p1, si._lineSegment.first, si._lineSegment.second);
				  double d2 = Algebra::distance2segment(p2, si._lineSegment.first, si._lineSegment.second);

				  double min = d1 < d2 ? d1 : d2;
				  if(min < retVal)
					  retVal = min;
			  }

			  return retVal;
		  }
		  Rectangle _rec;
		  std::deque<Vec2d> _polyline;
		  bool _sortByPolyLine;
	  };

	  class PriorityQueue: public std::priority_queue<SegmentIndx, std::vector<SegmentIndx>, LineSegmentComparer>
	  {
	  public:
		  PriorityQueue(){

		  }
		  
		  void UpdateComparer(const Rectangle &rec)
		  {
			  SetRectangle(rec);
		  }

		  void UpdateComparer(const std::deque<Vec2d> polyLine)
		  {
			  SetPolyline(polyLine);
		  }

	  private:
		  
		  void SetRectangle(const Rectangle &rec)
		  {
			  std::vector<SegmentIndx> segs;
			  
			  
			  if(!this->empty())
			  {
				  do{
					  segs.push_back(this->top());
					  this->pop();
				  }while(!this->c.empty());
				    
				  _rec = rec;
				  
				  this->comp.SetRectangle(_rec);
				  this->comp.setSortByPolyLine(false);
				  
				  for(size_t i = 0;i<segs.size();i++)
				  {
					  this->push(segs[i]);
				  }
			  }
		  }

		  void SetPolyline(const std::deque<Vec2d> &polyline)
		  {
			  std::vector<SegmentIndx> segs;

			  if(!this->empty())
			  {
				  do{
					  segs.push_back(this->top());
					  this->pop();
				  }while(!this->c.empty());
				    
				  
				  this->comp.SetPolyline(polyline);
				  this->comp.setSortByPolyLine(true);
				  
				  for(size_t i = 0;i<segs.size();i++)
				  {
					  this->push(segs[i]);
				  }
			  }
		  }


		  Rectangle _rec;
	  };

   };
}


#endif /* _separator_h */