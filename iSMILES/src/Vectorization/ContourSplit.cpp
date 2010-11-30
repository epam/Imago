#include "ContourSplit.h"
#include <algorithm>
#include "../Parameters.h"

namespace gga
{
    ContourSplit::ContourSplit(const Contour& contour)
    {   
        Points temp;
        const std::vector<size_t> idx = contour.getWayChanges();
        std::vector<size_t>::const_iterator it = idx.begin();
        for (size_t u = 0; u < contour.size(); u++)
        {
            if (it != idx.end() && u == *it)
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
}