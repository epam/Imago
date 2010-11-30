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
        
        double getSideLength(size_t side = 0) const
        {
            size_t v1 = side % 3, v2 = (side + 1) % 3;
            return Vertex[v1].distance(Vertex[v2]);
        }
	};
    
    typedef std::vector<Triangle> Triangles;
}
