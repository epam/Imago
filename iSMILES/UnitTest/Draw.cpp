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
        
        Image LineToImage(const Polyline& line)
        {
            Points pts;
            for (size_t u = 0; u < line.size(); u++) // add line points to range points
                pts.push_back(line[u]);
            
            Bounds b(pts);
            Image result;
            
            LineDefinition def = LineDefinition(127, GlobalParams.getLineWidth());
            
            result.setSize(b.getWidth() + def.Width * 2, b.getHeight() + def.Width * 2, IT_BW);
            
            
            for (size_t u = 0; u < line.size() - 1; u++)
            {
                result.drawLine(line[u].X - b.getLeft() + def.Width, 
                                line[u].Y - b.getTop() + def.Width, 
                                line[u+1].X - b.getLeft() + def.Width, 
                                line[u+1].Y - b.getTop() + def.Width, 
                                def);
            }
            
            return result;
        }

        Image LineAprxToImage(const LinearApproximation& src)
        {
            if (!src.isGood())
                return RangeArrayToImage(src.getRange());

            Image result = LineToImage(src.getLine());
            result.drawImage(0, 0, PointsToImage(src.getRange().toPoints()), false);

            return result;
        }
        
        Image TriangleToImage(const Triangle& src)
        {
            Polyline p;
            
            // produce somewhat like line-loop:
            p.push_back(src.Vertex[0]);
            p.push_back(src.Vertex[1]);
            p.push_back(src.Vertex[2]);
            p.push_back(src.Vertex[0]);
            
            return LineToImage(p);
        }
    }
}

