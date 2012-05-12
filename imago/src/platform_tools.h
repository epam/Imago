#pragma once

#include <string>

namespace platform
{
	int MKDIR(const std::string& directory);
	unsigned int TICKS();
	unsigned int MEM_AVAIL();
}

