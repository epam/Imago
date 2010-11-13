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

#ifndef _chemical_structure_recognizer_h
#define _chemical_structure_recognizer_h

#include "boost/shared_ptr.hpp"

#include "image.h" 
#include "stl_fwd.h"

namespace imago
{
   class Molecule;
   class Font;
   class Segment;
   
   class ChemicalStructureRecognizer
   {
   public:

      ChemicalStructureRecognizer();

      void setImage( Image &img );
      void recognize( Molecule &mol ); 
      void image2mol( Image &img, Molecule &mol );

      ~ChemicalStructureRecognizer();

   private:
      boost::shared_ptr<Font> _fnt;
      Image _origImage;
      
      void _processFilter();
      void _selectFont( const SegmentDeque &layer );

      ChemicalStructureRecognizer( const ChemicalStructureRecognizer &csr );
   };
}


#endif /* _chemical_structure_recognizer_h */