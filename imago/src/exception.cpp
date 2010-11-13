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

/**
 * @file   exception.cpp
 *
 * @brief  Implementation of Exception class
 */

#include <cstdio>
#include <cstring>

#include "exception.h"

using namespace imago;

Exception::Exception( const char *format, ...)
{
   _exc_name = "";
   va_list args;
   va_start(args, format);
   _prepare(format, args);
   va_end(args);
}

void Exception::_prepare( const char* format, va_list args )
{
   char new_format[MAX_LINE];
   sprintf(new_format, "%sException: %s", _exc_name, format);
   vsnprintf(_message, MAX_LINE, new_format, args);
}

Exception::Exception()
{
   _exc_name = "";
   sprintf(_message, "Exception");
}

Exception::~Exception() throw()
{
}

const char *Exception::what() const throw()
{
   return _message;
}
