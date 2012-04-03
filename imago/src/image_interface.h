#pragma once

#include "stl_fwd.h"

namespace imago
{
	// most generic image interface
	class ImageInterface
	{
	public:
		// check intenisty (or something) value is passed some bounds
		virtual bool isFilled(int x, int y) const = 0;

		// get raw intensity value 0..255
		virtual unsigned char getIntensity(int x, int y) const = 0; 

		// get the image dimensions
		virtual int width() const = 0;
		virtual int height() const = 0;

		// get area average intensity [generic]
		int getAverageIntensity(const Points2i& pts) const
		{
			double result = 0.0;
			if (!pts.empty())
			{
				for (size_t u = 0; u < pts.size(); u++)
					result += getIntensity(pts[u].x, pts[u].y);
				result /= pts.size();
			}			
			return (int)(result);
		}
	};
}

