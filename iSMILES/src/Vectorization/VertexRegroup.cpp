#include "VertexRegroup.h"

namespace gga
{
    VertexRegroup::VertexRegroup(const Polylines src)
    : Result(src)
    {
        bool doneSomething = false;
        do
        {
            for (Polylines::iterator first = Result.begin(); first != Result.end() && !doneSomething; first++)
            {
                for (Polylines::iterator second = Result.begin(); second != Result.end() && !doneSomething; second++)
                {
                    if (first != second)
                    {             
                        // TODO: compare angle & positions of first line begin/end to second line begin/end
                        if (false)
                        {
                            doneSomething = true;
                        }
                    }
                }   
            }                
        } while (doneSomething);
    }
}
