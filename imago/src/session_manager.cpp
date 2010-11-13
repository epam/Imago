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

#include <iostream>

#include "session_manager.h"
#include "segment.h"
#include "imago_session.h"

using namespace imago;

SessionManager SessionManager::_instance;
Lock SessionManager::_lock;
ThreadLocalPtr<qword> SessionManager::_curSID;

namespace imago
{
   ThreadLocalPtr<ImagoSession> gSession;
}

SessionManager::SessionManager()
{
   _freeSID = 0;
   _activeSessions.clear();
}

qword SessionManager::getSID()
{
   qword *pid = _curSID.get();
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
   AutoLock locker(_lock);
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

   _activeSessions.insert(std::make_pair(id, (ImagoSession*)0));
   return id;
}

void SessionManager::setSID( qword id )
{
   AutoLock locker(_lock);

   if (_activeSessions.find(id) == _activeSessions.end())
   {
      //keep working or throw an exception?
      //throw WrongSessionIdException();
      _activeSessions.insert(std::make_pair(id, (ImagoSession*)0));
   }

   qword *pId = _curSID.get();
   if (pId == 0)
   {
      _curSID.reset(new qword(id));
      pId = _curSID.get();
   }
   else
      *pId = id;
   
   IdToPtrMap::iterator curSessionIt = _activeSessions.find(id);

   if (curSessionIt->second == 0)
      curSessionIt->second = new ImagoSession();
   
   gSession.set(curSessionIt->second);
}

void SessionManager::releaseSID( qword id )
{
   AutoLock locker(_lock);

   //for (IdToPtrMap::iterator it = _activeSessions.begin(); it != _activeSessions.end(); ++it)
   //   std::cout << it->first << " <-> " << it->second << std::endl;

   IdToPtrMap::iterator curSessionIt = _activeSessions.find(id);
   if (curSessionIt == _activeSessions.end())
   {
      std::cerr << "Trying to release unallocated session " << id << "\n";
      return;
   }

   //std::cout << "deleting " << curSessionIt->second << "\n";
   delete curSessionIt->second;
   _activeSessions.erase(curSessionIt);
   gSession.set(0);
   _availableSIDs.push_back(id);
}

SessionManager &SessionManager::getInstance()
{
   return _instance;
}

SessionManager::~SessionManager()
{
   for (IdToPtrMap::iterator it = _activeSessions.begin();
         it != _activeSessions.end(); ++it)
   {
      //std::cout << it->first << " <-> " << (int)it->second << std::endl;
      delete it->second;
   }

   _activeSessions.clear();
   _availableSIDs.clear();
   _curSID.reset(0);
}

