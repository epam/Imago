#pragma once
#include <string>
#include "Image.h"

namespace gga
{
    class FilePNG
    {
    public:
        FilePNG();
        ~FilePNG();
        bool load(const std::string& path, Image* img);
        bool save(const std::string& path, const Image& img);
    };
}

