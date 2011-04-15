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

#include <cstdlib>
#include <cmath>

#include "bitarray.h"
#include "exception.h"

using namespace imago;

BitArray::BitArray()
{
   _storage = 0;
   _nbits = 0;
}

BitArray::BitArray( int size )
{
   _nbits = (size + 7) / 8 * 8;
   _storage = new byte[_nbits / 8];
   memset(_storage, 0, _nbits / 8);
}

bool BitArray::getBit( int i )
{
   if (_storage == 0)
      throw Exception("BitArray: not allocated");

   return ((((byte *)_storage)[i / 8] & (byte)(1 << (i % 8))) == 0) ? false : true;
}

void BitArray::setBit( int i, int val )
{
   if (_storage == 0)
      throw Exception("BitArray: not allocated");

   if (val)
      ((byte *)_storage)[i / 8] |= (1 << (i % 8));
   else
      ((byte *)_storage)[i / 8] &= ~(1 << (i % 8));
}

int BitArray::size()
{
   return _nbits;
}

BitArray::~BitArray()
{
   if (_storage != 0)
   {
      delete[] _storage;
      _storage = 0;
   }
}