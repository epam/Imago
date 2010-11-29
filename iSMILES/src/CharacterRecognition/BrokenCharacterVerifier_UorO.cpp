#include <math.h>
#include <algorithm>
#include "BrokenCharacterVerifier.h"

namespace gga
{
    bool isUorO(const Points& contour, size_t maxBreak, char* result)
    {

        unsigned centerX = 0, centerY = 0;
        std::vector<int> a(contour.size()); // angles from center to each point of countour

        for(size_t i=0; i < contour.size(); i++)
        {
            centerX += contour[i].X;
            centerY += contour[i].Y;
        }
        centerX /= contour.size();
        centerY /= contour.size();

        for(size_t i=0; i < contour.size(); i++)
            a[i] = int( atan2(float(contour[i].Y - centerY), float(contour[i].X - centerX)) * 3.14159265359f/180.f + 180.f ); // 0 - 360 degree

        std::sort(a.begin(), a.end());

        int maxdA = abs(a[a.size()-1] - a[0]);
        for(size_t i=1; i < a.size(); i++)
        {
            int da = abs(a[i]-a[i-1]);
            if (da > 180)
                da = 360 - da;
            if (maxdA < da)
                maxdA = da;
        }
        
        if(maxdA > 30)
            *result = 'U';  // or 'C'
        else
            *result = 'O';
        return true;
    }

}
