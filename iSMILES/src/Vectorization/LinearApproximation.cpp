#include <algorithm>
#include "LinearApproximation.h"
#include "../Parameters.h"
#include "../Histogram.h"
#ifdef DEBUG
#include <stdio.h> // printf "log"
#endif

// ALL MAGIC CONSTANTS MOVED TO PARAMETERS.H

#define sqr(w)      ((w)*(w))
#define sign(w)     (((w) < 0) ? -1.0 : ( ((w) > 0) ? 1.0 : 0.0))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#define max(a,b)    (((a) > (b)) ? (a) : (b))

namespace gga
{
    LinearApproximation::LinearApproximation(const RangeArray& ranges)
    : Good(false), StdDev(0.0), Ranges(ranges)
    {        
        /* calculate df(f) values histogram */
        Histogram<size_t, double> hist;
        for (size_t y = 0; y < Ranges.size(); y++)
        {
            RangeArray::const_iterator it = Ranges.begin() + y;
            RangeArray::const_iterator it2 = it;
            unsigned int step = GlobalParams.getLinearApproximationStep();
            for (size_t u = 0; it2 != Ranges.end() && u < step; u++)
                it2++;
                
            if (it2 == Ranges.end())
                break;
            
            double coef = (double)(it2->mid() - it->mid()) / (double)step;
            hist.add(y, coef);
        }
        
        if (hist.empty())
            return;

        /* initial values */
        double Coef = hist.average();
        double Shift = Ranges.begin()->mid();

        for (int iter = 1; iter <= 2; iter++)
        { 
            double d = 1.0;
            /* calculate and correct StdDev */
            do {
                double dev_minus = 0.0, dev_plus = 0.0;
                for (int p = -1; p <= 1; p++)
                {
                    double sqrL = 0.0, sqrR = 0.0;
                    double maxdL = 0.0, maxdR = 0.0;
                    int maxuL = 0, maxuR = 0;
                    bool first = true;
                    for (size_t u = 0; u < Ranges.size(); u++)
                    {
                        double X = (Coef+d*p)*u + Shift;
                        
                        double dL = fabs ( X - Ranges[u].L );
                        if (dL > maxdL)
                        {
                            maxdL = dL;
                            maxuL = u;
                        }
                        sqrL += sqr( dL );

                        double dR = fabs ( X - Ranges[u].R );
                        if (dR > maxdR)
                        {
                            maxdR = dR;
                            maxuR = u;
                        }                            
                        sqrR += sqr( dR );
                    }
                    double dev = (sqrt(sqrL) + sqrt(sqrR)) / (Ranges.size() * 2.0);
                    
                    if (p == -1) dev_minus = dev;
                    else if (p == 1) dev_plus = dev;
                    else /* p == 0 */ StdDev = dev;

                    #ifdef DEBUG
                        if (iter == 1 && p == 0 && fabs(d) <= 0.0001 * 2)
                        {
                            printf("L: %f (%i); %i..%i..%i  |  R: %f (%i); %i..%i..%i \n", 
                                maxdL, maxuL, Ranges[maxuL].L, (int)((Coef+d)*maxuL + Shift), Ranges[maxuL].R,
                                maxdR, maxuR, Ranges[maxuR].L, (int)((Coef+d)*maxuR + Shift), Ranges[maxuR].R);                            
                        }
                    #endif
                    
                }
                /* select which is better */
                if (dev_minus < StdDev || dev_plus < StdDev)
                {
                    if (dev_minus < dev_plus)
                        Coef -= d;
                    else
                        Coef += d;
                }
                d /= 2.0;
            } while (fabs(d) > 0.0001);
            
            if (iter == 1)
            { /* correct Shift value */
                double d = 0.0;        
                do {
                    double avgL = 0.0, avgR = 0.0;
                    for (size_t u = 0; u < Ranges.size(); u++)
                    {
                        avgL += (Coef*u + Shift) - Ranges[u].L;                
                        avgR += Ranges[u].R - (Coef*u + Shift);
                    }
                    d = (avgR - avgL) / (Ranges.size() * 2.0);
                    Shift += d; // adjust
                } while (fabs(d) > 0.001);
            }
        }
        
        #ifdef DEBUG
            static int figure_num = 0;
            static int recurse_level = 0;
            if (recurse_level == 0)
                printf("Figure %i\n", figure_num);            
            char prefix[128] = {0};
            for (size_t u = 0; u < recurse_level*3; u++)
            {
                prefix[u] = ' ';
                prefix[u+1] = 0;
            }                
            recurse_level++;
            printf("%sDev: %f, Coef: %f, Shift: %f\n", prefix, StdDev, Coef, Shift);
        #endif

        
        { /* construct default result line */ 
            int first = 0, last = Ranges.size()-1;
            while (Shift + Coef*first < 0)
                first++;
            while (Shift + Coef*last < 0 && last > first)
                last--;                
            ResultLine = Line(Ranges.coordToPoint(Shift + Coef*first, first), Ranges.coordToPoint(Shift + Coef*last, last));        
        }

        Histogram<size_t, double> hist_d2;
        { /* cluster analysis for df(f) */
            double delta = hist.range() / GlobalParams.getTargetGroupsCount() + 0.0001 /*eps*/;
            hist_d2 = hist.regroup(delta).onlyRepresentative();
        }

        #ifdef DEBUG
            printf("%sDiff count: %i, after regroup: %i\n", prefix, hist.groups(), hist_d2.groups());
        #endif

        /* use second representative group to perform recursive split */
        if (hist_d2.groups() >= 2)
        {
            typedef std::vector<size_t> indexes_t;
            indexes_t Indexes = hist_d2.startIndexes();
            sort(Indexes.begin(), Indexes.end());
            indexes_t::iterator it = Indexes.begin();
            for( ; it != Indexes.end(); it++)
                if (*it > GlobalParams.getMinimalLineLength())
                    break;

            if (it != Indexes.end())
            {
                int second_gr_idx = *it + 20; // TODO: !!!
                int total = Ranges.size();
                
                #ifdef DEBUG
                    printf("%sFirst group [%i..%i]:\n", prefix, 0, second_gr_idx-1);
                #endif
                
                RangeArray rng1(Ranges, 0, second_gr_idx);
                LinearApproximation lin1(rng1); // will be good
                
                #ifdef DEBUG
                    printf("%sSecond group [%i..%i]:\n", prefix, second_gr_idx, total);
                #endif
                
                RangeArray rng2(Ranges, second_gr_idx);
                LinearApproximation lin2(rng2); // have to be better than current
                
                // TODO: average is not better function for std.dev. comparison
                double dev = (lin1.StdDev*second_gr_idx + lin2.StdDev*(total-second_gr_idx))/total;
                
                #ifdef DEBUG
                    printf("%s%cDev after split [%f,%f]=%f vs base %f\n", prefix, (dev < StdDev) ? '+' : '-',
                           lin1.StdDev, lin2.StdDev, dev, StdDev);
                #endif
                
                if (dev < StdDev)
                {                    
                    StdDev = dev;
                    
                    Polyline out1 = lin1.getLine();
                    Polyline out2 = lin2.getLine();

                    double minv = min( min(out1.getEnd().distance(out2.getEnd()), out1.getEnd().distance(out2.getBegin())),
                                       min(out1.getBegin().distance(out2.getEnd()), out1.getBegin().distance(out2.getBegin())) 
                                     ) + 0.0001 /*eps*/;
                    
                    if (out1.getEnd().distance(out2.getEnd()) <= minv)
                    {
                        std::reverse(out2.begin(), out2.end());
                    }
                    else if (out1.getBegin().distance(out2.getBegin()) <= minv)
                    {
                        std::reverse(out1.begin(), out1.end());
                    }
                    
                    ResultLine.clear();
                    for (size_t v = 0; v < out1.size(); v++)
                        ResultLine.insertKnot(out1[v]);
                    
                    for (size_t v = 1; v < out2.size(); v++)
                        ResultLine.insertKnot(out2[v]);
                }
            }
        }
        Good = StdDev < 1.0;
                
        #ifdef DEBUG
            recurse_level--;
            if (recurse_level == 0)
                figure_num++;
        #endif
    }
}
