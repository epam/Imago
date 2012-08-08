/****************************************************************************
 * Copyright (C) 2009-2012 GGA Software Services LLC
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
#ifndef _prefilter_h_
#define _prefilter_h_

#include <vector>
#include "settings.h"
#include "image.h"

namespace imago
{
   void prefilterStd(Settings& vars, Image &image );

   // NOTE: the input image must be thinned
   bool isCircle(const Settings& vars, Image &seg, double &radius, bool asChar = false);

   double estimateLineThickness(Image &bwimg, int grid);
}
#endif /* _prefilter_h_ */
