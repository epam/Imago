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

#ifndef _lock_h
#define _lock_h

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#else
#include <pthread.h>
#endif

#include "comdef.h"

namespace imago
{
   class Lock
   {
   public:
      Lock();
      ~Lock();

      void lock();
      void unlock();

   #ifdef _WIN32
      typedef CRITICAL_SECTION LockType;
   #else
      typedef pthread_mutex_t LockType;
   #endif

   private:
      Lock(const Lock &);

      LockType os_lock;
   };

   class AutoLock
   {
   public:
      explicit AutoLock(Lock &_l) : l(_l)
      {
         l.lock();
      }

      ~AutoLock()
      {
         l.unlock();
      }
   private:
      AutoLock(const AutoLock &);
      Lock &l;
   };
}
#endif /* _lock_h */

