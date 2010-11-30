#include "ContourSplit.h"
#include "../Parameters.h"
#include <algorithm>

namespace gga
{
    ContourSplit::ContourSplit(const Contour& contour)
    {   
        std::vector<size_t> idx, idx_0, idx_90;
        
        const int DIST_DELTA_MIN = getGlobalParams().getLineWidth() / 2;
        const int DIST_DELTA_MAX = getGlobalParams().getLineWidth() * 3;
        
        const std::vector<size_t> idx_0_src = contour.getWayChanges();
        
        // reduce points count
        idx_0.push_back(idx_0_src[0]);
        for (int i = 1; i < idx_0_src.size(); i++)
        {
            int max = DIST_DELTA_MIN;
            
            for (int k = 0; k < idx_0.size(); k++)
            {
                if (contour[idx_0[k]].distance(contour[idx_0_src[i]]) < max)
                {
                    max = contour[idx_0[k]].distance(contour[idx_0_src[i]]);
                }
             }
            
            if (max == DIST_DELTA_MIN)
                idx_0.push_back(idx_0_src[i]);
        }
        
        // reconstruct rotated contour
        Bounds b(contour);
        Image img;
        img.setSize(b.getRight() + 4, b.getBottom() + 4, IT_BW);
        img.clear();
        for (Points::const_iterator it = contour.begin(); it != contour.end(); it++)
        {
            img.setPixel(it->X, it->Y, INK);                                
        }
        
        ImageMap map(img.getWidth(), img.getHeight());
        Contour rotated(img, map, contour[0], true);
        const std::vector<size_t> idx_90_src = rotated.getWayChanges();            
        
        // reduce points count
        idx_90.push_back(idx_90_src[0]);            
        for (int i = 1; i < idx_90_src.size(); i++)
        {
            int max = DIST_DELTA_MIN;
            
            for (int k = 0; k < idx_90.size(); k++)
            {
                if (contour[idx_90[k]].distance(contour[idx_90_src[i]]) < max)
                {
                    max = contour[idx_90[k]].distance(contour[idx_90_src[i]]);
                }
             }
            
            if (max == DIST_DELTA_MIN)
                idx_90.push_back(idx_90_src[i]);
        }
        
        // select only intersection indexes   
        for (std::vector<size_t>::const_iterator it_90 = idx_90.begin(); it_90 != idx_90.end(); it_90++)
        {
            bool found = false;
            for (std::vector<size_t>::const_iterator it_0 = idx_0.begin(); !found && it_0 != idx_0.end(); it_0++)
            {
                if (contour[*it_0].distance(rotated[*it_90]) < DIST_DELTA_MAX)
                    found = true;
            }
            if (found)
                idx.push_back(*it_90);
        }
        
        // split contour by junction points or line endpoints
        std::vector<size_t>::const_iterator it = idx.begin();
        Points temp;                
        for (size_t u = 0; u < rotated.size(); u++)
        {
            if (it != idx.end() && u == *it)
            {
                it++;
                if (!temp.empty())
                    Result.push_back(temp);
                temp.clear();
            }
            temp.push_back(rotated[u]);
        }        
        if (!temp.empty())
            Result.push_back(temp);        
    }
}