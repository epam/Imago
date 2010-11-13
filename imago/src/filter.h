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
 * @file filter.h
 * 
 * @brief   Declares the Filter class 
 */
#ifndef _filter_h
#define _filter_h

namespace imago
{
   class Image;

   /**
    * @brief   Abstract filter class
    */
   class Filter
   {
   public:

      Filter( Image &I );
      virtual void apply() = 0;
      virtual void apply( Image &res );
      ~Filter();

   protected:
      Image &_img;

   private:
      Filter();
      Filter( const Filter &F );
   };
}


#endif /* _filter_h */