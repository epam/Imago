#include "ImageMap.h"

namespace gga
{
	ImageMap::ImageMap(size_t width, size_t height) : Width(width)
	{
		const size_t items = width*height;
		Data.resize(items);
		for (size_t u = 0; u < items; u++)
		{
			Data[u] = NULL;
		}
	}
	
	void ImageMap::assignSegment(const Point& p, const ISegment* segment)
	{
		Data[p.Y*Width + p.X] = segment;
	}
	
	const ISegment* ImageMap::getAssignedSegment(const Point& p) const
	{
		return Data[p.Y*Width + p.X];
	}
}
