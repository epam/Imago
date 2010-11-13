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

#ifndef _recognition_settings_h
#define _recognition_settings_h

#include <map>
#include <string>

#include "comdef.h"

namespace imago
{     
   class RecognitionSettings
   {
   public:      

      //If used in formatted output, do not forget to explicitly convert type 
      struct Parameter
      {
      public:

         Parameter( int x ) : _x(x) {}
         Parameter( double y ) : _y(y) {}
         Parameter( const char *z ) : _z(z) {}
         Parameter( bool b ) : _b(b) {}

         operator int() { return _x; }
         operator double() { return _y; }
         operator const char*() { return _z; }
         operator bool() { return _b; }

      private:

         int _x;
         double _y;
         const char *_z;
         bool _b;
      };

      RecognitionSettings();

      Parameter get( const std::string &name );

      Parameter &operator[]( const std::string &name );

      template<typename T>
      void set( const std::string &name, T value )
      {
         NameToParMap::iterator it = _storage.find(name);

         if (it == _storage.end())
         {
            _storage.insert(std::make_pair(name, value));
            return;
         }  

         it->second = value;
      }

      void initConfig( int number );

      ~RecognitionSettings();      

      enum
      {
         CONF_COUNT = 5,
         COMMENT_SYM = '#'
      };
   private:      

      RecognitionSettings( const RecognitionSettings & );

      typedef std::map<const std::string, Parameter> NameToParMap;

      NameToParMap _storage;
   };
}


#endif /* _recognition_settings_h */