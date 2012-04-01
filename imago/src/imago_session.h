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

#ifndef _imago_session_h
#define _imago_session_h

#include "comdef.h"
#include "chemical_structure_recognizer.h"
#include "log.h"
#include "recognition_settings.h"
#include "molecule.h"

namespace imago
{
   class ImagoSession
   {
   public:
      ImagoSession() : _context(0) {}
      ~ImagoSession() {}

      ChemicalStructureRecognizer &recognizer() {return _csr;}
      RecognitionSettings &settings() {return _rs;}
      Log &log() {return _log;}
      Molecule &mol() {return _mol;}

      void *&context() {return _context;}

      const ChemicalStructureRecognizer &recognizer() const {return _csr;}
      const RecognitionSettings &settings() const {return _rs;}
      const Log &log() const {return _log;}
      const Molecule &mol() const {return _mol;}

   private:
      ImagoSession(const ImagoSession& orig);
      
      ChemicalStructureRecognizer _csr;
      Molecule _mol;
      RecognitionSettings _rs;
      Log _log;

      void *_context;
   };


};


#endif /* _imago_session_h */