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

#ifndef _segmentator_h
#define _segmentator_h

#include "stl_fwd.h"
#include <vector>

#include "segment.h"

namespace imago
{
   class Image;

   class Segmentator
   {
   public:
      
      template<typename Container>
      static void segmentate( const Image &img, Container &segments,
                              int windowSize = 3 )
      {
         int i, j;
         IntVector visited(img.getHeight() * img.getWidth(), 0);

         segments.clear();

         for (i = 0; i < img.getHeight(); i++)
         {
            for (j = 0; j < img.getWidth(); j++)
            {
               if (img.getByte(j, i) < 255)
               {
                  if (visited[(i * img.getWidth() + j)] != 0)
                     continue;

                  Segment *newImg = new Segment();
                  segments.push_back(newImg);
                  newImg->getX() = j;
                  newImg->getY() = i;
                  _walkSegment(img, visited, newImg, windowSize);
               }
            }
         }
      }

   private:
      static void _walkSegment( const Image &img, IntVector &visited,
                                Segment *segment, int windowSize );
   };
}


#endif /* _segmentator_h */