#include "Draw.h"
#include "../src/Parameters.h"

namespace gga
{
    namespace Draw
    {
        Image PointsToImage(const Points& src)
        {
            Image result;
            Bounds b(src);
            result.setSize(b.getWidth(), b.getHeight(), IT_BW);
            for (size_t x = 0; x < result.getWidth(); x++)
                for (size_t y = 0; y < result.getHeight(); y++)
                    result.setPixel(x,y, BACKGROUND);
            for (Points::const_iterator it = src.begin(); it != src.end(); it++)
                result.setPixel(it->X-b.getLeft(), it->Y-b.getTop(), INK);
            return result;
        }
        
        Image RangeArrayToImage(const RangeArray& src)
        {
            return PointsToImage(src.toPoints());
        }

        Image LineToImage(const LinearApproximation& src)
        {
            if (!src.isGood())
                return RangeArrayToImage(src.getRange());
                
            Points pts = src.getRange().toPoints();
            Polyline line = src.getLine();
            for (size_t u = 0; u < line.size(); u++) // add line points to range points
                pts.push_back(line[u]);
            
            Bounds b(pts);
            Image result;
            result.setSize(b.getWidth(), b.getHeight(), IT_BW);
            
            LineDefinition def = LineDefinition(127, GlobalParams.getLineWidth());
            for (size_t u = 0; u < line.size() - 1; u++)
            {
                result.drawLine(line[u].X - b.getLeft(), line[u].Y - b.getTop(), line[u+1].X - b.getLeft(), line[u+1].Y - b.getTop(), def);
            }

            result.drawImage(0, 0, PointsToImage(pts), false);

            return result;
        }
    }
}

