/****************************************************************************
 * Copyright (C) 2010-2011 GGA Software Services LLC
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

#ifndef _jpg_loader_h
#define _jpg_loader_h

#include "comdef.h"

namespace imago
{
   class Image;
   class Scanner;
   
   class JpgLoader
   {
   public:

      JpgLoader();
      bool loadImage( Image &img, const char *file_name );
      bool loadImage( Image &img, const byte *begin, const byte *end );
      ~JpgLoader();
   };
}


#endif /* _jpg_loader_h */
