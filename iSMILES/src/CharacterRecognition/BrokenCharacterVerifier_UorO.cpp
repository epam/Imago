#include <math.h>
#include <algorithm>
#include "BrokenCharacterVerifier.h"

namespace gga
{
    bool isUorO(const Points& contour, size_t maxBreak, char* result)
    {

        size_t   N = maxBreak;
        unsigned centerX = 0, centerY = 0;
        Points   points; // begin, end;
        std::vector<float> a(contour.size());

        for(size_t i=0; i < contour.size(); i++)
        {
            centerX += contour[i].X;
            centerY += contour[i].Y;
        }
        centerX /= contour.size();
        centerY /= contour.size();

        for(size_t i=0; i < contour.size(); i++)
            a[i] = atan2(float(contour[i].Y - centerY), float(contour[i].X - centerX));   // = / - pi

        std::sort(a.begin(), a.end());
        float maxdA = 0.f;
        for(size_t i=1; i < a.size(); i++)
        {
            float da = fabs(a[i]-a[i-1]);
            if(da<3.14f && da > maxdA)
                maxdA = a[i];
        }
        
        if(maxdA > 30*(float)3.14159265359f/(float)180.f)
            *result = 'U';
        else
            *result = 'O';
        return true;
    }

}
