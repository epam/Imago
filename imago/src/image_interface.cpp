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

#include "image_interface.h"

namespace imago
{

	double ImageInterface::getAverageIntensity(const Points2i& pts) const
	{
		double result = 0.0;
		if (!pts.empty())
		{
			for (size_t u = 0; u < pts.size(); u++)
				result += getIntensity(pts[u].x, pts[u].y);
			result /= pts.size();
		}			
		return result;
	}

	double ImageInterface::getAverageIntensity() const
	{
		double result = 0.0;
		for (int y = 0; y < height(); y++)
			for (int x = 0; x < width(); x++)
				result += getIntensity(x, y);
		result /= width() * height();
		return result;
	}

	double ImageInterface::getAverageFillrate(const Points2i& pts) const
	{
		if (pts.empty())
			return 0.0;

		int result = 0;
		for (size_t u = 0; u < pts.size(); u++)
			if (isFilled(pts[u].x, pts[u].y))
				result++;
		return (double)result / (double)(pts.size());
	}

	double ImageInterface::getAverageFillrate() const
	{
		int result = 0;
		for (int y = 0; y < height(); y++)
			for (int x = 0; x < width(); x++)
				if (isFilled(x, y))
					result++;		
		return (double)result / (double)(width()*height());
	}
}
