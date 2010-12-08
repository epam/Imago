#include "ContourSplit.h"
#include "../Parameters.h"
#include <algorithm>

namespace gga
{
    const int BORDER = 4;
    
    ContourSplit::Indexes ContourSplit::reduceIndexCount(const Indexes& indexes, const Contour& contour)
    {   
        const size_t DIST_DELTA_MIN = getGlobalParams().getLineWidth();
        Indexes result;
        
        if (!indexes.empty())
        {
            result.push_back(indexes[0]);
        }
        
        for (size_t i = 1; i < indexes.size(); i++)
        {
            size_t max = DIST_DELTA_MIN;
            
            for (size_t k = 0; k < result.size(); k++)
            {
                if (contour[result[k]].distance(contour[indexes[i]]) < max)
                {
                    max = (size_t)contour[result[k]].distance(contour[indexes[i]]);
                }
             }
            
            if (max == DIST_DELTA_MIN)
                result.push_back(indexes[i]);
        }
        
        return result;
    }
    
    ContourSplit::Indexes ContourSplit::intersectIndexes(const Indexes& idx_90, const Contour& rotated, const Indexes& idx_0, const Contour& contour)
    {
        const size_t DIST_DELTA_MAX = getGlobalParams().getMinimalLineLength();
        Indexes result;
        for (std::vector<size_t>::const_iterator it_90 = idx_90.begin(); it_90 != idx_90.end(); it_90++)
        {
            bool found = false;
            for (std::vector<size_t>::const_iterator it_0 = idx_0.begin(); !found && it_0 != idx_0.end(); it_0++)
            {
                if (contour[*it_0].distance(rotated[*it_90]) < DIST_DELTA_MAX)
                    found = true;
            }
            if (found)
                result.push_back(*it_90);
        }
        return result;
    }
    
    void ContourSplit::createResultSplit(const Indexes& indexes, const Contour& contour)
    {
        Result.clear();
        std::vector<size_t>::const_iterator it = indexes.begin();
        Points temp;                
        for (size_t u = 0; u < contour.size(); u++)
        {
            if (it != indexes.end() && u == *it)
            {
                it++;
                if (!temp.empty())
                    Result.push_back(temp);
                temp.clear();
            }
            temp.push_back(contour[u]);
        }        
        if (!temp.empty())
            Result.push_back(temp);   
    }
        
    ContourSplit::ContourSplit(const Contour& contour)
    : ContourBounds(contour)
    {   
        // reconstruct rotated contour
        const int dx = ContourBounds.getLeft() - BORDER;
        const int dy = ContourBounds.getTop() - BORDER;

        Image img;
        img.setSize(ContourBounds.getWidth() + 2 * BORDER, ContourBounds.getHeight() + 2 * BORDER, IT_BW);
        img.clear();
        for (Points::const_iterator it = contour.begin(); it != contour.end(); it++)
            img.setPixel(it->X - dx, it->Y - dy, INK);
            
        ImageMap map(img.getWidth(), img.getHeight());
        Point start(contour[0].X - dx, contour[0].Y - dy);
        Contour rotated(img, map, start, true, false);
        
        for (Points::iterator it = rotated.begin(); it != rotated.end(); it++)
            *it = Point(it->X + dx, it->Y + dy);
        
        // select only intersection indexes
        const Indexes idx_0 = reduceIndexCount(contour.getWayChanges(), contour);
        const Indexes idx_90 = reduceIndexCount(rotated.getWayChanges(), rotated);        
        const Indexes idx = intersectIndexes(idx_90, rotated, idx_0, contour);
        
        // split contour by junction points or line endpoints
        createResultSplit(idx, rotated);
    }
}