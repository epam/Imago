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
#ifndef _session_manager_h
#define _session_manager_h

#include <set>
#include <deque>
#include <mutex>

#include "comdef.h"

namespace imago
{
   class SessionManager
   {
   public:
      static SessionManager &getInstance();

      qword getSID();
      void setSID( qword id );

      qword allocSID();
      void releaseSID( qword id );
   private:
      qword _freeSID;
      
      typedef std::deque<qword> IdContainer;
      IdContainer _availableSIDs;
      typedef std::set<qword> IdSet;
      IdSet _activeSessions;

      static SessionManager _instance;
      static std::mutex _mutex;
      typedef std::lock_guard<std::mutex> lock_guard;

      SessionManager();
      SessionManager( const SessionManager& );
      ~SessionManager();
   };
}

#endif /* _session_manager_h */

