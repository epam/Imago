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
 * @file   image.cpp
 * 
 * @brief  Implementation of Image class
 */

#include <cmath>
#include <cstring>

#include "image.h"
#include "exception.h"
#include "segment.h"

using namespace imago;

/** 
 * @brief Crops image
 */
void Image::crop(int left, int top, int right, int bottom, int* shift_x, int* shift_y)
{
   int w = getWidth();
   int h = getHeight();
   
   if (left == -1 || right == -1 || top == -1 || bottom == -1)
   {
	   for (left = 0; left < w; left++)
		   for (int y = 0; y < h; y++)
			   if (isFilled(left, y))
			   {
				   goto left_done;
			   }

	   left_done:
	   
	   for (right = w-1; right >= left; right--)
		   for (int y = 0; y < h; y++)
			   if (isFilled(right, y))
			   {
				   goto right_done;
			   }

	   right_done:
	   
	   for (top = 0; top < h; top++)
		   for (int x = 0; x < w; x++)
			   if (isFilled(x, top))
			   {
				   goto top_done;
			   }

	   top_done:
	   
	   for (bottom = h-1; bottom >= top; bottom--)
		   for (int x = 0; x < w; x++)
			   if (isFilled(x, bottom))
			   {
				   goto bottom_done;
			   }

	   bottom_done: ;
   }

   if (left >= 0 && right >= 0 && top >= 0 && bottom >= 0)
   {
	   if (shift_x) *shift_x = left;
	   if (shift_y) *shift_y = top;
	   extractRect(left, top, right, bottom, *this);
   }
}

