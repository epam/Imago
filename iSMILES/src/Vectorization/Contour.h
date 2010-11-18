#pragma once
#include "../Image/Point.h"
#include "../Image/Region.h"
#include "../Image/Image.h"
#include "ImageMap.h"
#include "Line.h"

namespace gga
{	
	class Contour : public ISegment, public Region
	{		
        // references to the constructor params
        const Image& SourceImage;
        ImageMap& CurrentImageMap;
        const Contour* OuterContour;
        
	public:
		/* here we assume that image is coherent in any of 8 ways,
		 * so if the pixel will not have neighbor in any of 4 diagonal and 4 straight directions
		 * then it will be considered as separate image part */         
         
        // extract contour and mark all coherent points on image map
        Contour(const Image& img, ImageMap& map, const Point& start);
        
        // returns outer contour for that one or NULL
        const Contour* getOuterContour() const { return OuterContour; }
		
	private:        
        // private methods for contour pass implementation only
		void passDownLeft(Point& p, bool RotatedAxis = false);
		Point movePoint(const Point& src, int x, int y, bool RotatedAxis = false);
		Point commitPoint(const Point& p);
	};
}

