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

#ifndef _label_logic_h
#define	_label_logic_h

#include "superatom.h"
#include "character_recognizer.h"

namespace imago
{
   struct Superatom;
   class Segment;
   class CharacterRecognizer;
   struct Label;

   class LabelLogic
   {
   public:
      LabelLogic( const CharacterRecognizer &cr, double capHeightError );
      ~LabelLogic();

      void setSuperatom( Superatom *satom );
      void process( Segment *seg, int line_y );

      void recognizeLabel( Label &label );

   private:
      HWCharacterRecognizer _hwcr;
      int _cap_height;
      const CharacterRecognizer &_cr;
      double cap_height_error;
      Superatom *_satom;
      Atom *_cur_atom;
      bool flushed, was_super, was_charge, was_letter;
      LabelLogic( LabelLogic & );
      void _predict( const Segment *seg, std::string &letters );
      void _postProcess();
   };
}

#endif /* _label_logic_h */

