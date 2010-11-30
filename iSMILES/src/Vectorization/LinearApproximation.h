#pragma once
#include "Contour.h"
#include "RangeArray.h"
#include "Line.h"
#include "../Histogram.h"

namespace gga
{
    class LinearApproximation
    {
        bool Good;
        double StdDev;
        Polyline ResultLine;
        const RangeArray& Ranges;

        typedef Histogram<size_t, double> HistType;
        
    public:
        LinearApproximation(const RangeArray& ranges);
        
        bool isGood() const { return Good; }        
        const RangeArray& getRange() const { return Ranges; }                
        Polyline getLine() const { return ResultLine; }
        
    private:
        static const double eps;
        
        HistType calculateHistogram();
        double optimizeCoef(double& Coef, const double Shift);  // returns std.dev 
        double optimizeShift(const double Coef, double& Shift); // returns (R-L) disbalance
        Polyline constructDefaultResult(const double Coef, const double Shift);
                
        int calculateSplitStart(const HistType& hist); // returns 0 if no split applicable
        void checkSplit(int splitStart); // updates StdDev and ResultLine
        
        static Polyline concatenateLines(const Polyline& line1, const Polyline& line2);
    };
}

