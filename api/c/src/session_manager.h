/****************************************************************************
* Copyright (C) from 2009 to Present EPAM Systems.
*
* This file is part of Imago toolkit.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
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

