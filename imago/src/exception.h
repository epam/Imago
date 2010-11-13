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
  * @file   exception.h
  * 
  * @brief  Declares Exception class
  */

#ifndef _exception_h
#define _exception_h

#include <cstdarg>
#include <cstdio>
#include <exception>

#include "comdef.h"

namespace std
{
   class bad_alloc;
   class overflow_error;
   class underflow_error;
   class range_error;
}

namespace imago
{
   /**
    * @brief Exception class
    */
   class Exception : public std::exception
   {
   public:
      /**
       * Constructor (works like printf)
       *
       * @param format format string
       */
      explicit Exception( const char *format, ...);

      Exception();

      /**
       * Constructor (like previous, but also adds location of throw)
       *
       * @param file set by macros __FILE__
       * @param line set by macros __LINE__
       * @param func set by macros __FUNCTION__ or __PRETTY_FUNCTION__
       * @param format format string
       */
      //Exception( const char *file, int line, const char *func, const char *format, ... );

      /**
       * Destructor
       */
      virtual ~Exception() throw();

      /**
       * @brief Returns exception's message
       *
       * @return Constant pointer to c-string
       */
      const char *what() const throw();
   protected:
      /// No default construction
      
      /// Message string
      char _message[MAX_LINE];
      const char *_exc_name;
      void _prepare( const char *format, va_list args );
   };
#define CREATE_EXCEPTION(name, base)                                      \
   class name##Exception: public base                                     \
   {                                                                      \
   public:                                                                \
      explicit name##Exception( const char *format, ...)                  \
      {                                                                   \
         _exc_name = #name;                                               \
         va_list args;                                                    \
         va_start(args, format);                                          \
         _prepare(format, args);                                          \
         va_end(args);                                                    \
      }                                                                   \
      name##Exception()                                                   \
      {                                                                   \
         _exc_name = #name;                                               \
         sprintf(_message, "%sException", _exc_name);                     \
      }                                                                   \
   };

#define CREATE_BASE_EXCEPTION(name) CREATE_EXCEPTION(name, Exception);
   CREATE_BASE_EXCEPTION(DivizionByZero);
   CREATE_BASE_EXCEPTION(OutOfMemory);
   CREATE_BASE_EXCEPTION(Overflow);
   CREATE_BASE_EXCEPTION(Underflow);
   CREATE_BASE_EXCEPTION(OutOfBounds);
   //typedef std::bad_alloc OutOfMemoryException;
   //typedef std::overflow_error OverflowException;
   //typedef std::underflow_error UnderflowException;
   //typedef std::range_error OutOfBoundsException;
   CREATE_BASE_EXCEPTION(Logic);
   CREATE_EXCEPTION(InvalidName, LogicException);
   CREATE_EXCEPTION(InappropriateType, LogicException);
   
   CREATE_BASE_EXCEPTION(IO);
   CREATE_EXCEPTION(FileNotFound, IOException);
   CREATE_BASE_EXCEPTION(NullPointer);
   
   CREATE_BASE_EXCEPTION(OCR);
   CREATE_EXCEPTION(NoContour, OCRException);
   CREATE_EXCEPTION(Unrecognized, OCRException);
   CREATE_EXCEPTION(Split, OCRException);
   CREATE_EXCEPTION(Label, OCRException);

   CREATE_BASE_EXCEPTION(NoResult);
}

#endif /* _exception_h */
