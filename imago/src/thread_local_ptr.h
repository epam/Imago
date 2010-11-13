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

#ifndef _thread_local_ptr_h
#define _thread_local_ptr_h

#include "comdef.h"

#ifndef _WIN32
#include <pthread.h>
#endif

namespace imago
{
   struct TLS {
      #ifdef _WIN32
         typedef int KeyType;
      #else
         typedef pthread_key_t KeyType;
      #endif

      static void createSlot( KeyType &key );
      static void deleteSlot( KeyType &key );
      static void setData( KeyType &key, void *data );
      static void *getData( KeyType &key );
   };

   template <class T> class ThreadLocalPtr 
   {
   public:
      ThreadLocalPtr()
      {
         TLS::createSlot(_key);
      }

      T *get()
      {
         void *data = TLS::getData(_key);
         return static_cast<T*>(data);
      }

      void set( T *ptr )
      {
         TLS::setData(_key, ptr);
      }

      void reset( T *ptr = 0)
      {
         T *old_ptr = get();
         if (old_ptr != ptr)
         {
            if (old_ptr != 0)
               delete old_ptr;
            TLS::setData(_key, ptr);
         }
      }

      ~ThreadLocalPtr()
      {
         TLS::deleteSlot(_key);
      }

   private:
      //If an object of this class is static then race condition might happen
      //at construction time
      TLS::KeyType _key;
     
      ThreadLocalPtr( const ThreadLocalPtr & );
   };
}

#endif /* _thread_local_ptr_h */

