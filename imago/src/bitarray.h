/****************************************************************************
 * Copyright (C) 2009-2011 GGA Software Services LLC
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

#ifndef _bitarray_h
#define _bitarray_h

#include "comdef.h"

namespace imago
{
   class BitArray
   {
   public:

      BitArray();
      BitArray( int size );

      bool getBit( int i );
      void setBit( int i, int val );
      int size();

      ~BitArray();
   
   private:

      BitArray( const BitArray & );

      byte *_storage;
      int _nbits;
   };
}


#endif /* __bitarray_h */