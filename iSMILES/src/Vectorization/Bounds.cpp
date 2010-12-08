#include "Bounds.h"
#include "../Logger.h"

namespace gga
{
    Bounds::Bounds(Coord left, Coord right, Coord top, Coord bottom)
    {
        Left = left;
        Right = right;
        Top = top;
        Bottom = bottom;
    }
    
    Bounds::Bounds(const Points& points)
    {
        if (points.empty())
        {
            Left = Right = Top = Bottom = 0;
        }
        else
        {
            Left = Right = points.begin()->X;
            Top = Bottom = points.begin()->Y;
            for (Points::const_iterator it = points.begin(); it != points.end(); it++)
            {
                if (it->X < Left)
                    Left = it->X;
                if (it->X > Right)
                    Right = it->X;
                if (it->Y < Top)
                    Top = it->Y;
                if (it->Y > Bottom)
                    Bottom = it->Y;
            }
        }
        
        // LOG << "Generated bounds for " << points.size() << " points: [" << Left << ".." << Right << "] x [" << Top << ".." << Bottom << "]";
    }
    
    bool Bounds::isInside(const Image& image) const
    {
        return Left >= 0 && Top >= 0 && Left <= Right && Top <= Bottom
               && Right < image.getWidth() && Bottom < image.getHeight();
    }

    bool Bounds::isInside(const Bounds& outer) const
    {
        return Left >= 0 && Top >= 0 && Left <= Right && Top <= Bottom
               && Left  >= outer.getLeft()  && Top >= outer.getTop()
               && Right <= outer.getRight() && Bottom <= outer.getBottom();
    }
}

