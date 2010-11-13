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

#ifndef _session_manager_h
#define _session_manager_h

#include <map>
#include <deque>

#include "comdef.h"
#include "static_object.h"
#include "thread_local_ptr.h"
#include "lock.h"

namespace imago
{
   class ImagoSession;
   
   class SessionManager
   {
   public:
      static SessionManager &getInstance();

      qword getSID();
      void setSID( qword id );

      qword allocSID();
      void releaseSID( qword id );
   private:
      typedef std::map<qword, ImagoSession*> IdToPtrMap;
      //typedef std::map<ImagoSession*, qword> PtrToIdMap;
      typedef std::deque<qword> IdContainer;

      qword _freeSID;
      IdContainer _availableSIDs;

      IdToPtrMap _activeSessions;
      //PtrToIdMap ptr_to_id;


      static ThreadLocalPtr<qword> _curSID;
      static SessionManager _instance;
      static Lock _lock;

      SessionManager();
      SessionManager( const SessionManager& );
      ~SessionManager();
   };
}

#endif /* _session_manager_h */

