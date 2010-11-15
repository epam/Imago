#pragma once
#include "Contour.h"
#include "RangeArray.h"
#include "Line.h"

namespace gga
{
	class LinearApproximation
	{		
		bool Good;		
		double StdDev;
        Polyline ResultLine;
		RangeArray Ranges;
		
	public:
        LinearApproximation(const RangeArray& ranges);
		
		bool isGood() const { return Good; }        
		const RangeArray& getRange() const { return Ranges; }                
        Polyline getLine() const { return ResultLine; };        
	};
}

