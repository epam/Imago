/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
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

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include <cstdio>
#include <cstdarg>

#include <deque>

#include "log.h"
#include "output.h"

using namespace imago;

Log::Log()
{
   printer = stdout_printer;
   _start = _getTime();
}

void Log::mark()
{
   _marks.push_back(_getTime());
}

void Log::reset()
{
   _start = _getTime();
}

void Log::print( bool marked, const char *format, ... )
{
   qword time = _getTime();
   qword ds = time - _start;  
   char str[MAX_LINE];
   std::string final_string;
   ArrayOutput out(final_string);
   
   va_list va;
   va_start(va, format);
   vsnprintf(str, MAX_LINE, format, va);
   va_end(va);

   out.printf("[%lf]   %s", _toSeconds(ds), str);
   if (marked)
   {
      qword mark;
      if(_marks.size() > 0)
      {
         mark = _marks.back();
         _marks.pop_back();
         qword dt = time - mark;
         out.printf(" (%lf)", _toSeconds(dt));
      }
   }
   out.writeCR();
   final_string.push_back(0);
   if (printer != 0)
      printer(final_string.c_str());
}

qword Log::_getTime()
{
#ifdef _WIN32
   LARGE_INTEGER counter;

   if (!QueryPerformanceCounter(&counter))
      return 0;

   return (qword) (counter.QuadPart);
#else
   struct timeval t;
   struct timezone tz;

   gettimeofday(&t, &tz);
   return t.tv_usec + t.tv_sec * 1000000ULL;
#endif
}

double Log::_toSeconds( qword val )
{
#ifdef _WIN32
   LARGE_INTEGER freq;
   double quot;

   if (!QueryPerformanceFrequency(&freq))
      return 0;

   quot = (double)val / freq.QuadPart;

   return quot;
#else
   return ((double)val / 1000000.0);
#endif
}

Log::~Log()
{
}

void Log::setPrinter( PRINT_FUNCTION_PTR func )
{
  printer = func;
}

void Log::stdout_printer( const char *text )
{
   fputs(text, stdout);
}

