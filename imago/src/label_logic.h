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
#ifndef _label_logic_h
#define	_label_logic_h

#include "superatom.h"
#include "character_recognizer.h"
#include "settings.h"

namespace imago
{
   struct Superatom;
   class Segment;
   class CharacterRecognizer;
   struct Label;

   class LabelLogic
   {
   public:
      LabelLogic( const CharacterRecognizer &cr );
      ~LabelLogic();
            
      void recognizeLabel(const Settings& vars, Label &label );

   protected:
	  void process_ext(const Settings& vars, Segment *seg, int line_y );

   private:	  
      const CharacterRecognizer &_cr;
      Superatom *_satom;
      Atom *_cur_atom;
      LabelLogic( LabelLogic & );

	  void _addAtom();
	  void setSuperatom( Superatom *satom );
      void _predict(const Settings& vars,  const Segment *seg, std::string &letters );      
	  void _postProcessLabel(Label& label);
	  bool _multiLetterSubst(char sym);
   };
}

#endif /* _label_logic_h */

