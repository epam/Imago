#pragma once
#include "Pixel.h"

namespace gga
{
    struct LineDefinition // drawing parameters
    {
        Pixel   Color;
        size_t  Width;
    public:
        inline LineDefinition(unsigned char color = INK, size_t width = 1) : Color(color), Width(width) {}
    };
}
