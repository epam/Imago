#include "Vectorize.h"

namespace gga
{
	Vectorize::Vectorize(const Image& image) 
				: SourceImage(image), 
				  CurrentImageSplit(image.getWidth(), image.getHeight())
	{
		// line-by-line scan to extract contours of objects
		Point p(0,0);
		for (p.Y = 0; p.Y < SourceImage.getHeight(); p.Y++)
		{
			for (p.X = 0; p.X < SourceImage.getWidth(); p.X++)
			{
				if (SourceImage.isFilled(p))
				{
					if (CurrentImageSplit.getAssignedSegment(p) == NULL)
					{
						Contour* c = new Contour();
						// that pixel is unprocessed yet, so extract the contour starting from it
						c->buildFromImagePart(SourceImage, CurrentImageSplit, p);
						// add new contour
						OuterContours.push_back(c);
					}
					// fixup 'X' scanrow to pass the previously processed contours
					// (null-pointer exception here means that something went totally wrong)
					p = CurrentImageSplit.getAssignedSegment(p)->findRightCorner(p);
				}
			} // for x
		} //for y
	}
	
	Vectorize::~Vectorize()
	{
		for (size_t u = 0; u < getContoursCount(); u++)
			delete OuterContours[u];
	}
	
	size_t Vectorize::getContoursCount() const
	{
		return OuterContours.size();
	}
	
	const Contour& Vectorize::getContour(size_t index) const
	{
		return *OuterContours.at(index);
	}
	
	const ImageMap& Vectorize::getImageSplit() const
	{
		return CurrentImageSplit;
	}
}
