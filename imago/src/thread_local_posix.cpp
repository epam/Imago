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

#include "thread_local_ptr.h"
#include "exception.h"

using namespace imago;

void TLS::createSlot( KeyType &key )
{
   if (pthread_key_create(&key, NULL))
      throw OutOfMemoryException("Cannot create TLS key");
}

void TLS::setData( KeyType &key, void *data )
{
   if (pthread_setspecific(key, data))
      throw OutOfMemoryException("Cannot set data to TLS");
}

void *TLS::getData( KeyType &key )
{
   return pthread_getspecific(key);
}

void TLS::deleteSlot( KeyType &key )
{
   if (pthread_key_delete(key))
      throw Exception("Cannot delete TLS key");
}