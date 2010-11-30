#include "Parameters.h"

namespace gga
{

    static Parameters GlobalParams;

    Parameters& getGlobalParams()
    {
        return GlobalParams;
    }
}
