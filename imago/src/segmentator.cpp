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

#include <deque>
#include <vector>

#include "comdef.h"
#include "image.h"
#include "segmentator.h"
#include "segment.h"

using namespace imago;

void Segmentator::_walkSegment( const Image &img, BitArray &visited,
                                Segment *segment, int windowSize, unsigned char validColor )
{
   IntDeque q;
   IntDeque segment_elements;  
   //lists above will represent queues
   
   int width = img.getWidth(), height = img.getHeight();
   int x_max, x_min;
   int y_max, y_min;
   int cur;
   int tmp;
   int half = windowSize >> 1;

   int x, y;

   x_max = x_min = segment->getX();
   y_max = y_min = segment->getY();
   cur = segment->getY() * width + segment->getX();
   q.push_back(cur);
   segment_elements.push_back(cur);

   while (!q.empty())
   {
      tmp = q.front();

      q.pop_front();

      y = tmp / width;
      x = tmp % width;

      for (int i = y - half; i <= y + half; i++)
      {
         for (int j = x - half; j <= x + half; j++)
         {
            if (j == x && i == y)
               continue;
            if (i >= 0 && i < height && j >= 0 && j < width)
            {
               int ind = (i * width) + j;

               if (visited.at(j, i))
                  continue;

               if (img.getByte(j, i) == validColor)
               {
                  q.push_back(ind);

                  x_max = std::max(x_max, j);
                  x_min = std::min(x_min, j);

                  y_max = std::max(y_max, i);
                  y_min = std::min(y_min, i);

                  segment_elements.push_back(ind);

                  visited.at(j, i) = 1;
               }
            }
         }
      }
   }

   segment->init(x_max - x_min + 1, y_max - y_min + 1);
   segment->getX() = x_min;
   segment->getY() = y_min;
   segment->fillWhite();

   while (!segment_elements.empty())
   {
      tmp = segment_elements.front();
      segment_elements.pop_front();

      y = tmp / width;
      x = tmp % width;
      byte b = img.getByte(x, y);
      y -= y_min;
      x -= x_min;      
      if (validColor == 255) // compare with white
         b = 0;
      segment->getByte(x, y) = b;
   }
}
