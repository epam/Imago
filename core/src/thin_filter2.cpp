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

#include <vector>

#include "thin_filter2.h"
#include "image.h"

using namespace imago;

ThinFilter2::ThinFilter2( Image &I ) : _img(I)
{
}

void ThinFilter2::apply()
{
   const static int masks[] = {0200, 0002, 0040, 0010};
   const static byte	del[512] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

   int xsize, ysize;
   int x, y;
   int i;
   int pc = 0;
   int count = 1;
   int p, q;
   int it = 0;
   
   std::vector<byte> qb;
   int m;

   xsize = _img.getWidth() + 20;
   ysize = _img.getHeight() + 20;

   _img.invertColor();

   qb.resize(xsize);
   qb[xsize - 1] = 0;

   while (count && it < 20)
   {
      pc++;
      count = 0;
      it++;
      
      for (i = 0; i < 4; i++)
      {
         m = masks[i];

         p = get(0, 0) != 0;
         for (x = 0; x < xsize - 1; x++)
            qb[x] = p = ((p << 1)&0006) | (get(x + 1, 0) != 0);

         for (y = 0; y < ysize - 1; y++)
         {
            q = qb[0];
            p = ((q << 3)&0110) | (get(0, y + 1) != 0);

            for (x = 0; x < xsize - 1; x++)
            {
               q = qb[x];
               p = ((p << 1) & 0666) | ((q << 3) & 0110) |
                  (get(x + 1, y + 1) != 0);
               qb[x] = p;
               if (((p & m) == 0) && del[p])
               {
                  count++;
                  set(x, y, 0);
               }
            }

            p = (p << 1)&0666;
            if ((p & m) == 0 && del[p])
            {
               count++;
               set(xsize - 1, y, 0);
            }
         }

         for (x = 0; x < xsize; x++)
         {
            q = qb[x];
            p = ((p << 1) & 0666) | ((q << 3) & 0110);
            if ((p & m) == 0 && del[p])
            {
               count++;
               set(x, ysize - 1, 0);
            }
         }
      }

      //printf("ThinImage: pass %d, %d pixels deleted\n", pc, count);
   }

   _img.invertColor();
}

inline byte ThinFilter2::get( int x, int y )
{
   x -= 10;
   y -= 10;
   if (x < 0 || y < 0 || x >= _img.getWidth() || y >= _img.getHeight())
      return 0;

   return _img.getByte(x,y);
}

inline void ThinFilter2::set( int x, int y, byte val )
{
   x -= 10;
   y -= 10;
   if (x < 0 || y < 0 || x >= _img.getWidth() || y >= _img.getHeight())
      return;

   _img.getByte(x,y) = val;
}

ThinFilter2::~ThinFilter2()
{
}
