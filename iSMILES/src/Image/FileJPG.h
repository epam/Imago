#pragma once
#include <string>
#include "Image.h"

namespace gga
{
    class FileJPG
    {
    public:
        FileJPG();
        ~FileJPG();
        bool load(const std::string& path, Image* img);
        bool load(const std::vector<unsigned char>& buff, Image* img);
        bool save(const std::string& path, const Image& img, int quality = 100);
        bool save(std::vector<unsigned char>* out, const Image& img, int quality = 100);
    };
}

