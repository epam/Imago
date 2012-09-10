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

#pragma once
#ifndef contour_extractor_h_
#define contour_extractor_h_

#include <vector>

#include "stl_fwd.h"
#include "image.h"

namespace imago
{
   class Image;

   class ContourExtractor
   {
   public:
      ContourExtractor();
      virtual ~ContourExtractor();

      void getRawContour(const Image &i, Points2i &contour);
      void getApproxContour(const Image &i, Points2i &contour, double eps1, double eps2);

   private:
	   void _approximize(Points2i &contour, double eps1, double eps2);
   };
}

#endif /* contour_extractor_h_ */
