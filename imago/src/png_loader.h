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

/**
 * @file png_loader.h
 * 
 * @brief   Declares the png loader class
 */
#ifndef _png_loader_h
#define _png_loader_h

#include "png.h"
#include "comdef.h"

namespace imago
{
   class Image;
   class Scanner;

   /**
    * @brief   Png picture format loading class
    */
   class PngLoader
   {
   public:

      PngLoader( Scanner &scan );
      void loadImage( Image &I );
      ~PngLoader();

   private:
      PngLoader();

      static void _reader( png_structp png_ptr, png_bytep bytes, png_size_t size );

      Scanner &_scan;
   };
}


#endif /* _png_loader_h */