#include "VertexRegroup.h"
#include <stdlib.h>
#include "../Logger.h"
#include "../Parameters.h"

namespace gga
{
    #define pr(x) (void*)(&(*x))
    
    void VertexRegroup::reduceFractures()
    {
        for (Polylines::iterator it = Result.begin(); it != Result.end(); it++)
        {
            for (size_t u = 1; u < it->size()-1; u++)
            {
                // 180* addition to avoid negative angles
                int a1v = 180 + Line(it->at(u-1),it->at(u)).getAngle();
                int a2v = 180 + Line(it->at(u),it->at(u+1)).getAngle();
                if (abs(a1v-a2v) < getGlobalParams().getMaxFractureAngle())
                {
                    it->erase(it->begin() + u);
                    LOG << "Removed fracture for angles " << a1v << " and " << a2v << " in line " << pr(it);                    
                    break;
                }
            }
        }
    }
    
    void VertexRegroup::concatenateLines()
    {
        bool doneSomething;
        do
        {
            doneSomething = false;
            for (Polylines::iterator first = Result.begin(); !doneSomething && first != Result.end(); )
            {
                for (Polylines::iterator second = Result.begin(); second != Result.end(); second++)
                {
                    if (first == second)
                        continue;
                        
                    // compare positions of first line end to second line begin
                    if ( second->getBegin().distance(first->getEnd()) < getGlobalParams().getMaxLineBreakDistance() )
                    {
                        for (size_t u = 1; u < second->size(); u++)
                            first->push_back(second->at(u));
                        LOG << "Joined (end-to-begin) lines " << pr(first) << " and " << pr(second);
						Result.erase(second);
                        doneSomething = true;
                        break;
                    }
                    else if ( second->getEnd().distance(first->getEnd()) < getGlobalParams().getMaxLineBreakDistance() )
                    {
                        for (int u = second->size()-2; u >= 0; u--)
                            first->push_back(second->at(u));
                        LOG << "Joined (end-to-end) lines " << pr(first) << " and " << pr(second);
                        Result.erase(second);
                        doneSomething = true;
                        break;
                    }
                }
				if (!doneSomething)
					first++;
            }                
        } while (doneSomething);
    }
    
    
    double DistanceFromLine(double cx, double cy, double ax, double ay, double bx, double by)
    {
        double r_numerator = (cx-ax)*(bx-ax) + (cy-ay)*(by-ay);
        double r_denomenator = (bx-ax)*(bx-ax) + (by-ay)*(by-ay);
        double r = r_numerator / r_denomenator;
        double px = ax + r*(bx-ax);
        double py = ay + r*(by-ay);
        double s = ((ay-cy)*(bx-ax)-(ax-cx)*(by-ay) ) / r_denomenator;

        double distanceLine = fabs(s)*sqrt(r_denomenator);
        double distanceSegment = distanceLine;
        
        double xx = px;
        double yy = py;

        if ( (r < 0) || (r > 1) )
        {

            double dist1 = (cx-ax)*(cx-ax) + (cy-ay)*(cy-ay);
            double dist2 = (cx-bx)*(cx-bx) + (cy-by)*(cy-by);
            if (dist1 < dist2)
            {
                xx = ax;
                yy = ay;
                distanceSegment = sqrt(dist1);
            }
            else
            {
                xx = bx;
                yy = by;
                distanceSegment = sqrt(dist2);
            }
        }

        return distanceSegment;
    }

    int VertexRegroup::pointToLineDistance(const Point& p, const Line& l)
    {
        return (int)DistanceFromLine(p.X, p.Y, l.getBegin().X, l.getBegin().Y, l.getEnd().X, l.getEnd().Y);
    }
    
    int VertexRegroup::lineDistance(const Line& longer, const Line& shorter)
    {
        int dB = pointToLineDistance(shorter.getBegin(), longer);
        int dE = pointToLineDistance(shorter.getEnd(), longer);
        return (dB + dE) / 2;
    }
    
    void VertexRegroup::removeDuplicates()
    {
        std::vector<Line> p;
        for (Polylines::iterator it = Result.begin(); it != Result.end(); it++)
        {
            for (size_t u = 0; u < it->size()-1; u++)
            {
                Line line(it->at(u),it->at(u+1));
                p.push_back(line);
            }
        }
        
        bool doneSomething;
        do
        {
            doneSomething = false;        
            for (std::vector<Line>::iterator first = p.begin(); !doneSomething && first != p.end(); )
            {
                for (std::vector<Line>::iterator second = p.begin(); second != p.end(); second++)
                {
                    if (first == second)
                        continue;

                    int l1 = (int)first->getLength();
                    int l2 = (int)second->getLength();
                    if (l2 > l1)
                        continue;

                    int a1v = (180 + first->getAngle()) % 180;
                    int a2v = (180 + second->getAngle()) % 180;
                    int a = abs(a1v - a2v);
                    
                    unsigned int d = lineDistance(*first, *second);

                    if (a < getGlobalParams().getMaxFractureAngle() && 
                        d < getGlobalParams().getLineWidth() * 2 ) // TODO: check and name this.
                    {
                        LOG << "Removed duplicate (" << l2 << "), keep " << l1 << " pixels";
                        p.erase(second);
                        doneSomething = true;
                        break;
                    }
                }
				if (!doneSomething)
					first++;
            }
        } while (doneSomething);
        
        // copy remaining to result
        Result.clear();
        for (std::vector<Line>::iterator it = p.begin(); it != p.end(); it++)
            Result.push_back(*it);
    }
    
    VertexRegroup::VertexRegroup(const Polylines src)
    : Result(src)
    {   
        LOG << "---- removeDuplicates ----";
        removeDuplicates();
        
        LOG << "---- concatenateLines ----";        
        concatenateLines();                
        
        LOG << "---- reduceFractures ----";
        reduceFractures();        
    }
}
