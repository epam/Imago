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
 * @file png_saver.h
 * 
 * @brief   Declares the png saver class 
 */
#ifndef _png_saver_h
#define _png_saver_h

#include "png.h"
#include "comdef.h"

namespace imago
{
   class Image;
   class Output;

   /**
    * @brief   Png picture format saving class
    */
   class PngSaver
   {
   public:

      PngSaver( Output &out );
      void saveImage( const Image &I );
      ~PngSaver();

   private:
      PngSaver();

      static void _writer( png_structp png_ptr, png_bytep bytes, png_size_t size );

      Output &_out;
   };
}


#endif /* _png_saver_h */