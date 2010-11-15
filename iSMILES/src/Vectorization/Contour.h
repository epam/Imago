#pragma once
#include "../Image/Point.h"
#include "../Image/Region.h"
#include "../Image/Image.h"
#include "ImageMap.h"

namespace gga
{	
	class Contour : public ISegment, public Region
	{
	public:
		// ISegment overrides:
		Point findRightCorner(const Point& leftCorner) const;
		
	public:
		Contour();
		
		/* here we assume that image is coherent in any of 8 ways,
		 * so if the pixel will not have neighbor in any of 4 diagonal and 4 straight directions
		 * then it will be considered as separate image part */
		 
		// points will be sorted ascending by Y-axis
		void buildFromImagePart(const Image& src, ImageMap& split, const Point& start);
		
	private:
		bool RotatedAxis; // 180* rotated or not
		
		void passDownLeft(const Image& src, ImageMap& split, Point& p);

		Point movePoint(const Point& src, int x, int y);
		Point commitPoint(const Point& p, const Image& img, ImageMap& split);
	};
}

