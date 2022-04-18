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

#pragma once
#ifndef _segmentator_h
#define _segmentator_h

#include "stl_fwd.h"
#include <vector>

#include "segment.h"
#include "separator.h"
#include "basic_2d_storage.h"

namespace imago
{
   class Image;

   class Segmentator
   {
   public:

	   typedef Basic2dStorage<unsigned char> BitArray;
      
      template<typename Container>
      static void segmentate( const Image &img, Container &segments, int windowSize = 3, byte validColor = 0 )
      {
         int i, j;

         BitArray visited(img.getWidth(), img.getHeight());

         segments.clear();

         for (i = 0; i < img.getHeight(); i++)
         {
            for (j = 0; j < img.getWidth(); j++)
            {
               if (img.getByte(j, i) == validColor)
               {
                  if (visited.at(j, i))
                     continue;

                  Segment *newImg = new Segment();
                  segments.push_back(newImg);
                  newImg->getX() = j;
                  newImg->getY() = i;
                  _walkSegment(img, visited, newImg, windowSize, validColor);
               }
            }
         }
      }

   private:
      static void _walkSegment( const Image &img, BitArray &visited,
                                Segment *segment, int windowSize, byte validColor );
   };
}


#endif /* _segmentator_h */
