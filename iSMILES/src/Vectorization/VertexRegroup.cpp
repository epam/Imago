#include "VertexRegroup.h"
#include <stdlib.h>
#include "../Logger.h"
#include "../Parameters.h"

namespace gga
{
    void VertexRegroup::reduceFractures(Polyline& line)
    {
        bool doneSomething;
        do
        {
            doneSomething = false;
            for (size_t u = 1; u < line.size()-1; u++)
            {
                // 180* addition to avoid negative angles
                int a1v = 180 + (int)(Line(line[u-1],line[u]).getAngle());
                int a2v = 180 + (int)(Line(line[u],line[u+1]).getAngle());
                if (abs(a1v-a2v) < getGlobalParams().getMaxFractureAngle())
                {
                    line.erase(line.begin() + u);
                    LOG << "Removed fracture for angles " << a1v << " and " << a2v << " in line " << line.getId();
                    doneSomething = true;
                    break;
                }
            }
        } while (doneSomething);
    }

    void VertexRegroup::reduceFractures()
    {
        for (Polylines::iterator it = Result.begin(); it != Result.end(); it++)
        {
            reduceFractures(*it);
        }
    }
    
    void VertexRegroup::concatenateLines()
    {
        bool doneSomething;
        do
        {
            doneSomething = false;
            for (Polylines::iterator first = Result.begin(); first != Result.end(); first++)
            {
                for (Polylines::iterator second = Result.begin(); second != Result.end(); second++)
                {
                    if (first == second)
                        continue;
                        
                    if ( second->getBegin().distance(first->getEnd()) < getGlobalParams().getMaxLineBreakDistance() )
                    {
                        for (size_t u = 1; u < second->size(); u++)
                            first->push_back(second->at(u));
                        doneSomething = true;
                    }
                    else if ( second->getEnd().distance(first->getEnd()) < getGlobalParams().getMaxLineBreakDistance() )
                    {
                        for (int u = second->size()-2; u >= 0; u--)
                            first->push_back(second->at(u));
                        doneSomething = true;
                    }

                    if (doneSomething)
                    {
                        first->SplitId = first->SplitId + " - " + second->SplitId;
                        LOG << "Joined lines " << first->getId() << " by " << second->getId();
                        Result.erase(second);
                        break;
                    }
                }
                if (doneSomething)
                    break;
            }                
        } while (doneSomething);
    }

    void VertexRegroup::removeDuplicates()
    {
        std::vector<Line> p;
        for (Polylines::iterator it = Result.begin(); it != Result.end(); it++)
        {
            for (size_t u = 0; u < it->size()-1; u++)
            {
                Line line(it->at(u),it->at(u+1));
                line.BaseContourId = it->BaseContourId;
                std::stringstream ss;
                ss << p.size();
                line.SplitId = ss.str();
                p.push_back(line);
            }
        }
        
        bool doneSomething;
        do
        {
            doneSomething = false;        
            for (std::vector<Line>::iterator first = p.begin(); first != p.end(); first++)
            {
                for (std::vector<Line>::iterator second = p.begin(); second != p.end(); second++)
                {
                    if ( first == second || 
                        first->BaseContourId != second->BaseContourId || 
                        first->getLength() < second->getLength() )
                        continue;

                    int a1v = (180 + (int)first->getAngle()) % 180;
                    int a2v = (180 + (int)second->getAngle()) % 180;

                    if (abs(a1v - a2v) < getGlobalParams().getMaxFractureAngle() && 
                        first->getDistance(*second) < getGlobalParams().getMaxDuplicateDistance())
                    {
                        LOG << "Removed " << second->getId() << " duplicate of " << first->getId();
                        p.erase(second);
                        doneSomething = true;
                        break;
                    }
                }

                if (doneSomething)
                    break;
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
