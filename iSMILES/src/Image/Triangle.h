#pragma once
#include "Point.h"

namespace gga
{
    struct Triangle
    {
        Point   Vertex[3];
        bool    Filled;

    public:     
        inline Triangle(const Point& v1 = Point(0,0), const Point& v2 = Point(0,0), const Point& v3 = Point(0,0))
        { 
            Vertex[0] = v1; 
            Vertex[1] = v2; 
            Vertex[2] = v3;
            Filled = false;
        }
        
        inline double getSideLength(size_t side = 0) const
        {
            size_t v1 = side % 3, v2 = (side + 1) % 3;
            return Vertex[v1].distance(Vertex[v2]);
        }
        
        inline double getArea() const
        {
            double a = Vertex[0].X - Vertex[2].X;
            double b = Vertex[0].Y - Vertex[2].Y;
            double c = Vertex[1].X - Vertex[2].X;
            double d = Vertex[1].Y - Vertex[2].Y;
            return 0.5 * fabs((a*d) - (b*c));
        }
        
        bool isInside(const Point& p) const
        {
            double areaOne = Triangle(p, Vertex[1], Vertex[2]).getArea();
            double areaTwo = Triangle(p, Vertex[0], Vertex[2]).getArea();
            double areaThr = Triangle(p, Vertex[0], Vertex[1]).getArea();
            return areaOne + areaTwo + areaThr <= getArea() + 0.0001 /*eps*/;
        }
    };
    
    typedef std::vector<Triangle> Triangles;
}
