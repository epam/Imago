#include "image.h"
#include <string>

namespace imago
{
	bool failsafePngLoadBuffer(const unsigned char* buffer, size_t buf_size, Image& img);
	bool failsafePngLoadFile(const std::string& fname, Image& img);
}

