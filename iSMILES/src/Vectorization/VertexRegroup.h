#pragma once
#include <vector>
#include "Line.h"

namespace gga
{
    class VertexRegroup
    {
        Polylines Result;

    public:
        VertexRegroup(const Polylines src);
        
        /* Primary target: to reduce continuations of polylines/segments count.
         * converts "A---C D----B" to "A-------B"
         * converts "A----^----B"  to "A-------B" */
        const Polylines& getResult() const { return Result; }
    
    private:
        void removeDuplicates();

        void concatenateLines();

        void reduceFractures();
        void reduceFractures(Polyline& line);
    };
}
