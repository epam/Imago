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

#include <algorithm>
#include <vector>

#include "binarizer.h"
#include "image.h"
#include "stl_fwd.h"

using namespace imago;

void Binarizer::apply(Image &_img, int _t )
{
	if (_t > 255)
      _t = 255;
   if (_t < 0)
      _t = _getThreshold(_img);   

   int i, n;

   n = _img.getHeight() * _img.getWidth();

   for (i = 0; i < n; i++)
   {
      byte &b = _img[i];

      if (b < _t)
         b = 0;
      else if (b >= _t)
         b = 255;
   }
}

bool Binarizer::_comparePair( IntPair a, IntPair b )
{
   return a.second < b.second;
}

int Binarizer::_getThreshold(const Image &_img)
{
   std::vector<IntPair> histogram(256, std::make_pair(0, 0));

   for (int i = 0; i != histogram.size(); ++i)
   {
      histogram[i].first = i;
   }

   for (int i = 0; i < _img.getWidth() * _img.getHeight(); i++)
      histogram[_img[i]].second++;

   std::stable_sort(histogram.begin(), histogram.end(), _comparePair);

   return histogram[histogram.size() / 2].first;
}
