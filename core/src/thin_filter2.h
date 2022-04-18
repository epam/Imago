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

/**
 * @file thin_filter2.h
 *
 * @brief   Declares the thinning filter class
 */

#pragma once
#ifndef _thin_filter2_h
#define _thin_filter2_h

#include "comdef.h"
#include "image.h"

namespace imago
{
   class ThinFilter2
   {
   public:
      ThinFilter2( Image &I );
      void apply();
      ~ThinFilter2();
      
   private:
	  Image& _img;

      ThinFilter2( const ThinFilter2& );
      byte get( int x, int y );
      void set( int x, int y, byte val );
   };
}


#endif /* _thin_filter2_h */
