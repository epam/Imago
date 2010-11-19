#include "Vectorize.h"

namespace gga
{
	Vectorize::Vectorize(const Image& image) 
				: SourceImage(image), 
				  CurrentImageMap(image.getWidth(), image.getHeight())
	{
		// line-by-line scan to extract contours of objects
		Point p(0,0);
		for (p.Y = 0; p.Y < SourceImage.getHeight(); p.Y++)
		{
			for (p.X = 0; p.X < SourceImage.getWidth(); p.X++)
			{
				if (SourceImage.isFilled(p) && !CurrentImageMap.isAssigned(p))
                {
                    // that pixel is unprocessed yet, so extract the contour starting from it
                    Contour* c = new Contour(SourceImage, CurrentImageMap, p);
                    // add new contour
                    Contours.push_back(c);
                }
			} // for x
		} //for y
	}
	
	Vectorize::~Vectorize()
	{
		for (size_t u = 0; u < getContoursCount(); u++)
			delete Contours[u];
	}
	
	size_t Vectorize::getContoursCount() const
	{
		return Contours.size();
	}
	
	const Contour& Vectorize::getContour(size_t index) const
	{
		return *Contours.at(index);
	}
	
	const ImageMap& Vectorize::getImageMap() const
	{
		return CurrentImageMap;
	}
}
