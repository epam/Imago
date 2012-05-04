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

#ifndef _current_session_h
#define _current_session_h

#include "thread_local_ptr.h"
#include "imago_session.h"
#include "exception.h"

namespace imago
{
   extern ThreadLocalPtr<ImagoSession> gSession;

   inline Log &getLog()
   {
      ImagoSession *ptr = gSession.get();
      if (ptr == 0)
         throw LogicException("Using getLog() without started session");
      return ptr->log();
   }

   inline RecognitionSettings &getSettings()
   {
      ImagoSession *ptr = gSession.get();
      if (ptr == 0)
         throw LogicException("Using getSettings() without started session");
      return ptr->settings();
   }

   inline ChemicalStructureRecognizer &getRecognizer()
   {
      ImagoSession *ptr = gSession.get();
      if (ptr == 0)
         throw LogicException("Using getRecognizer() without started session");
      return ptr->recognizer();
   }
}


#endif /* _current_session_h */
