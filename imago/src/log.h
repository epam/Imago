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

#ifndef _log_h
#define _log_h

#include <deque>

#include "comdef.h"

namespace imago
{
   class Log
   {
      typedef void (*PRINT_FUNCTION_PTR)( const char *text );
   public:
      Log();
      ~Log();

      void reset();
      void mark();
      void print( bool marked, const char *format, ... );
      void setPrinter( PRINT_FUNCTION_PTR func );

      static void stdout_printer( const char *text );
   private:
      typedef std::deque<qword> MarksContainer;
      MarksContainer _marks;
      PRINT_FUNCTION_PTR printer;
      
      qword _mark;
      qword _start;
      qword _getTime();
      double _toSeconds(qword val);
   };
}

#endif /* _log_h */

