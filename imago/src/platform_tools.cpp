#include "platform_tools.h"

#ifdef _WIN32 // ------------------- Windows -------------------
#include <direct.h>
#include <Windows.h>

int platform::MKDIR(const std::string& directory)
{
	return _mkdir(directory.c_str());
}

unsigned int platform::TICKS()
{
	LARGE_INTEGER lFreq, lStart;
	QueryPerformanceFrequency(&lFreq);
	QueryPerformanceCounter(&lStart);
	double msecs = ((double)lStart.QuadPart / lFreq.QuadPart * 1000.0);
	return (int)msecs;
}

unsigned int platform::MEM_AVAIL()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
	GlobalMemoryStatusEx (&statex);
	return static_cast<size_t>(statex.ullAvailVirtual / 1024);
}

#else // ------------------- POSIX -------------------

#include <sys/stat.h>
#include <errno.h>

int platform::MKDIR(const std::string& directory)
{
	return mkdir(directory.c_str(), S_IRWXU|S_IRGRP|S_IXGRP);
}

unsigned int platform::TICKS()
{
	return 0; // TODO
}

unsigned int platform::MEM_AVAIL()
{
	return 0; // TODO
}

#endif