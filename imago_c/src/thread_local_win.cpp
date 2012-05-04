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

#include <windows.h>

#include "thread_local_ptr.h"
#include "exception.h"

using namespace imago;

void TLS::createSlot( KeyType &key )
{
   if ((key = TlsAlloc()) == TLS_OUT_OF_INDEXES)
	   throw ImagoException("Cannot create TLS key");
}

void TLS::setData( KeyType &key, void *data )
{
   if (!TlsSetValue(key, data))
      throw ImagoException("Cannot set data to TLS");
}

void *TLS::getData( KeyType &key )
{
   return TlsGetValue(key);
}

void TLS::deleteSlot( KeyType &key )
{
   if (!TlsFree(key))
      throw ImagoException("Cannot delete TLS key");
}
