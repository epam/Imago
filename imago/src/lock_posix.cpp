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

#include <cstdio>
#include "lock.h"

using namespace imago;

Lock::Lock()
{
   pthread_mutex_init(&os_lock, NULL);
}

Lock::~Lock()
{
   pthread_mutex_destroy(&os_lock);
}

void Lock::lock()
{
   pthread_mutex_lock(&os_lock);
}

void Lock::unlock()
{
   pthread_mutex_unlock(&os_lock);
}

