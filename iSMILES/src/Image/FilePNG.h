#pragma once
#include <string>
#include <vector>
#include "Image.h"

namespace gga
{
    class FilePNG
    {
    public:
        FilePNG();
        ~FilePNG();
        bool load(const std::string& path, Image* img);
        bool load(const std::vector<unsigned char>& buff, Image* img);
        bool save(const std::string& path, const Image& img);
        bool save(std::vector<unsigned char>* out, const Image& img);
    };
}

