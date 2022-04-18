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

#include <iostream>

#include "session_manager.h"

using namespace imago;

std::mutex SessionManager::_mutex;
#if (_MSC_VER >= 1800)
__declspec(thread) qword _curSID;
#else
thread_local qword _curSID;
#endif
SessionManager SessionManager::_instance;


SessionManager::SessionManager()
{
   _freeSID = 0;
}

qword SessionManager::getSID()
{
   qword *pid = &_curSID;
   qword id;

   if (pid == 0)
   {
      id = allocSID();
      setSID(id);
   }
   else
      id = *pid;

   return id;
}

qword SessionManager::allocSID()
{
   lock_guard lock(_mutex);
   qword id;

   if (_availableSIDs.size() > 0)
   {
      id = _availableSIDs.front();
      _availableSIDs.pop_front();
   }
   else
   {
      while (_activeSessions.find(_freeSID) !=  _activeSessions.end())
         ++_freeSID;

      id = _freeSID;
      ++_freeSID;
   }

   _activeSessions.insert(id);
   return id;
}

void SessionManager::setSID( qword id )
{
   lock_guard lock(_mutex);

   if (_activeSessions.find(id) == _activeSessions.end())
   {
      //keep working or throw an exception?
      //throw WrongSessionIdException();
      _activeSessions.insert(id);
   }

   qword *pId = &_curSID;
   *pId = id;
}

void SessionManager::releaseSID( qword id )
{
   lock_guard lock(_mutex);

   IdSet::iterator curSessionIt = _activeSessions.find(id);
   if (curSessionIt == _activeSessions.end())
   {
      std::cerr << "Trying to release unallocated session " << id << "\n";
      return;
   }

   _activeSessions.erase(curSessionIt);
   _availableSIDs.push_back(id);
}

SessionManager &SessionManager::getInstance()
{
   return _instance;
}

SessionManager::~SessionManager()
{
   _activeSessions.clear();
   _availableSIDs.clear();
}

