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

#ifndef _fourier_descriptors_extractor_h
#define _fourier_descriptors_extractor_h

#include "vec2d.h"
#include "segment.h"
#include "stl_fwd.h"

namespace imago
{
   class Image;

   class FourierDescriptors
   {
   public:
      //TODO: change Segment to Contour
      static void calculate( const Segment *seg, int count,
                             std::vector<double> &descriptors );
      
      static void calculate( const Points &contour, int count,
                             std::vector<double> &descriptor );

   };
}


#endif /* _fourier_descriptors_extractor_h */



