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
#ifndef _recognition_context_h
#define _recognition_context_h

#include <string>

#include "comdef.h"
#include "chemical_structure_recognizer.h"
#include "image.h"
#include "molecule.h"
#include "settings.h"
#include "virtual_fs.h"
#include "session_manager.h"

namespace imago
{
   struct RecognitionContext
   {
      ChemicalStructureRecognizer csr;
      Image img_tmp;
	  Image img_src;
      Molecule mol;
      std::string molfile;
      std::string out_buf;
      std::string error_buf;
	  std::string configs_list;
      Settings vars;
      VirtualFS vfs;
      void *session_specific_data;
      
      RecognitionContext () 
      {
         session_specific_data = 0;
         error_buf = "No error";
      }
   };

   RecognitionContext *getContextForSession(qword sessionId);
   inline RecognitionContext *getCurrentContext()
   {
      return getContextForSession(SessionManager::getInstance().getSID());
   }

   void setContextForSession(qword sessionId, RecognitionContext *context);
   void deleteRecognitionContext(qword sessionId, RecognitionContext *context);
};


#endif /* _imago_session_h */