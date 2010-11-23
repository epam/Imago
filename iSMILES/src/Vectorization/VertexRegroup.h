#pragma once
#include <vector>
#include "Line.h"


namespace gga
{
    typedef std::vector<Polyline> Polylines;
    
    class VertexRegroup
    {
        Polylines Result;
    public:
        VertexRegroup(const Polylines src);
        
        const Polylines& getResult() const { return Result; }
    };
}

#pragma once
#include <vector>
#include "Line.h"


namespace gga
{
    typedef std::vector<Polyline> Polylines;
    
    class VertexRegroup
    {
        Polylines Result;
    public:
        VertexRegroup(const Polylines src);
        
        const Polylines& getResult() const { return Result; }
    };
}

