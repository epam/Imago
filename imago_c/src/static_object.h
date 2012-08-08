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

#pragma once
#ifndef _static_object_h
#define _static_object_h

#include "lock.h"
    
namespace imago
{
   extern Lock _static_obj_construction_lock;

   template <typename T>
   class StaticObject
   {
   public:
      ~StaticObject()
      {
         if (_was_created)
         {
            _obj->~T();
            _obj = 0;
            _was_created = false;
         }
      }
      
      T * ptr ()
      {
         return _ptr();
      }
      T & ref ()
      {
         return *_ptr();
      }
      T * operator -> ()
      {
         return ptr();
      }

   private:
      void _ensureInitialized ()
      {
         if (!_was_created)
         {
            AutoLock locker(_static_obj_construction_lock);

            if (!_was_created)
            {
               _obj = new ((void *)_obj_data) T;
               _was_created = true;
            }
         }
      }
      
      T * _ptr ()
      {
         _ensureInitialized();
         return _obj;
      }
      
      T *_obj;
      char _obj_data[sizeof(T)];
      volatile bool _was_created; // Zero for static objects
   };
}


#endif /* _static_object_h */
