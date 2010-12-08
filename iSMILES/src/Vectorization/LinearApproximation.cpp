#include "LinearApproximation.h"
#include <algorithm>
#include "../Logger.h"
#include "../Parameters.h"

#ifdef _WIN32
// workaround Visual Studio '#define min' problem
#undef min
#endif

namespace gga
{    
    const double LinearApproximation::eps = 0.0001;
    static size_t RecurseLevel = 0;
        
    Polyline LinearApproximation::constructDefaultResult(const double Coef, const double Shift)
    {
        int first = 0, last = Ranges.size()-1;
        while (Shift + Coef*first < 0)
            first++;
        while (Shift + Coef*last < 0 && last > first)
            last--;                
        int first_x = (int)(Shift + Coef*first);
        int last_x = (int)(Shift + Coef*last);
        return Line(Ranges.coordToPoint(first_x, first), Ranges.coordToPoint(last_x, last));
    }
    
    LinearApproximation::HistType LinearApproximation::calculateHistogram() const
    {
        HistType result;
        for (size_t y = 0; y < Ranges.size(); y++)
        {
            RangeArray::const_iterator it = Ranges.begin() + y;
            RangeArray::const_iterator it2 = it;
            unsigned int step = getGlobalParams().getLinearApproximationStep();
            for (size_t u = 0; it2 != Ranges.end() && u < step; u++)
                it2++;
                
            if (it2 == Ranges.end())
                break;
            
            double coef = (double)(it2->mid() - it->mid()) / (double)step;
            result.addValue(y, coef);
        }
        return result;
    }
    
    double LinearApproximation::optimizeCoef(double& Coef, const double Shift) const
    {
        double delta = 1.0;
        double dev[3];
        do {
            for (int p = -1; p <= 1; p++)
            {
                double sqrL = 0.0, sqrR = 0.0;
                for (size_t u = 0; u < Ranges.size(); u++)
                {
                    double X = (Coef + delta*p) * u + Shift;
                    double dL = X - Ranges[u].L;
                    double dR = X - Ranges[u].R;
                    sqrL += dL * dL;
                    sqrR += dR * dR;
                }
                dev[1+p] = (sqrt(sqrL) + sqrt(sqrR)) / (Ranges.size() * 2.0);
            }
            
            /* select one which is better */
            if (dev[0] < dev[1] || dev[2] < dev[1])
            {
                if (dev[0] < dev[2])
                    Coef -= delta;
                else
                    Coef += delta;
            }
            delta /= 2.0;
        } while (fabs(delta) > eps);        
        return dev[1];
    }
    
    double LinearApproximation::optimizeShift(const double Coef, double& Shift) const
    {
        double delta = 0.0;        
        do {
            double avgL = 0.0, avgR = 0.0;
            for (size_t u = 0; u < Ranges.size(); u++)
            {
                double X = Coef * u + Shift;
                avgL += X - Ranges[u].L;                
                avgR += Ranges[u].R - X;
            }
            delta = (avgR - avgL) / (Ranges.size() * 2.0);
            Shift += delta; // adjust
        } while (fabs(delta) >= 1.0); // 1.0 == one pixel in average, not magic.
        return delta;
    }
    
    Polyline LinearApproximation::concatenateLines(const Polyline& line1, const Polyline& line2)
    {
        Polyline result, out1 = line1, out2 = line2;
        
        double minv = std::min( std::min(out1.getEnd().distance(out2.getEnd()), out1.getEnd().distance(out2.getBegin())),
                                std::min(out1.getBegin().distance(out2.getEnd()), out1.getBegin().distance(out2.getBegin())) 
                         ) + eps;
        
        if (out1.getEnd().distance(out2.getEnd()) <= minv)
        {
            std::reverse(out2.begin(), out2.end());
        }
        else if (out1.getBegin().distance(out2.getBegin()) <= minv)
        {
            std::reverse(out1.begin(), out1.end());
        }
        
        for (size_t v = 0; v < out1.size(); v++)
            result.push_back(out1[v]);
        
        for (size_t v = 1; v < out2.size(); v++)
            result.push_back(out2[v]);
            
        return result;
    }
                 
    int LinearApproximation::calculateSplitStart(const HistType& hist) const
    {   
        int result = 0;
                
        for (size_t u = 0; u < hist.getGroupsCount() && result == 0; u++)
        {
            double value_temp;
            std::vector<size_t> indexes;
            hist.getGroup(u, value_temp, indexes);            
            size_t start = *(std::min_element(indexes.begin(), indexes.end()));
            if (start > getGlobalParams().getMinimalLineLength())                 
                result = start;
        }

        return result;        
    }
    
    void LinearApproximation::checkSplit(int start)
    {        
        int total = Ranges.size();
        
        LOG << getLogPrefix() << "First group [0.." << (start-1) << "]:";
        
        RangeArray rng1(Ranges, 0, start);
        LinearApproximation lin1(rng1); // will be good

        LOG << getLogPrefix() << "Second group [" << start << ".." << total << "]:";
        
        RangeArray rng2(Ranges, start);
        LinearApproximation lin2(rng2); // have to be better than current
        
        double NewDev = (lin1.StdDev * start * getGlobalParams().getSplitStdDevFactor() + lin2.StdDev * (total - start)) / total;
        
        LOG << getLogPrefix() << ((NewDev < StdDev) ? '+' : '-') << "Dev after split [" << lin1.StdDev << "," << lin2.StdDev
                << "]=" << NewDev << " vs base " << StdDev;
        
        if (NewDev < StdDev)
        {                    
            StdDev = NewDev;
            ResultLine = concatenateLines(lin1.getLine(), lin2.getLine());
        }
    }
    
    std::string LinearApproximation::getLogPrefix() const
    {
        std::string result;
        result.resize(RecurseLevel*3);
        for (size_t u = 0; u < result.size(); u++)
            result[u] = ' ';
        return result;
    }
    
    LinearApproximation::LinearApproximation(const RangeArray& ranges)
    : Good(false), StdDev(0.0), Ranges(ranges)
    {        
        HistType Hist_df = calculateHistogram();
        
        if (Hist_df.isEmpty())
        {
            LOG << "f' histogram is empty";
            return;
        }

        /* initial values */
        double Coef = Hist_df.getAverage();
        double Shift = Ranges.begin()->mid();
        
        /* optimize and calculate std.dev. */
        optimizeCoef(Coef, Shift);
        optimizeShift(Coef, Shift);
        StdDev = optimizeCoef(Coef, Shift);
        
        LOG << getLogPrefix() << "Dev: " << StdDev << ", Coef: " << Coef << ", Shift: " << Shift;
        
        ResultLine = constructDefaultResult(Coef, Shift);
        
        /* cluster analysis for df(f) */
        double delta = Hist_df.getRange() / getGlobalParams().getTargetGroupsCount() + eps;
        HistType hist_d2 = Hist_df.regroup(delta).getOnlyRepresentative();

        LOG << getLogPrefix() << "Diff count: " << Hist_df.getGroupsCount() << ", after regroup: " << hist_d2.getGroupsCount();
                
        int splitStart = calculateSplitStart(hist_d2);        
        if (splitStart > 0)
        {            
            RecurseLevel++;
            checkSplit(splitStart);
            RecurseLevel--;
        }
                
        Good = StdDev < getGlobalParams().getDeviationThreshold();
    }
}
