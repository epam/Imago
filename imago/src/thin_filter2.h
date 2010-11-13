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
 * @file morphology_filter.h
 *
 * @brief   Declares the thinning filter class
 */
#ifndef _thin_filter2_h
#define _thin_filter2_h

#include "comdef.h"
#include "filter.h"

namespace imago
{
   class ThinFilter2 : public Filter
   {
   public:

      ThinFilter2( Image &I );
      void apply();
      ~ThinFilter2();
      
   private:
      ThinFilter2( const ThinFilter2& );
      byte get( int x, int y );
      void set( int x, int y, byte val );
   };
}


#endif /* _thin_filter2_h */