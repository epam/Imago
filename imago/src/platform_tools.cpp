/****************************************************************************
 * Copyright (C) 2009-2012 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

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
	__int64 ticks = (__int64)msecs;
	return (unsigned int)ticks;
}

unsigned int platform::MEM_AVAIL()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
	GlobalMemoryStatusEx (&statex);
	return static_cast<size_t>(statex.ullAvailVirtual / 1024);
}

std::string platform::getLineEndings()
{
	return "\r\n";
}

#else // ------------------- POSIX -------------------

#include <sys/stat.h>
//#include <errno.h>

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

std::string platform::getLineEndings()
{
	return "\n";
}

#endif