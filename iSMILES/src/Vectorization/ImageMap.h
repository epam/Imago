#pragma once
#include <vector>
#include "../Image/Point.h"

namespace gga
{	
	class ISegment
	{
	public:
		virtual Point findRightCorner(const Point& leftCorner) const = 0;
	};
	
	class ImageMap
	{
		size_t Width;
		std::vector<const ISegment*> Data;
	public:
		ImageMap(size_t width, size_t height);
		
		// assign segment to specified point on image
		void assignSegment(const Point& p, const ISegment* segment);
		
		// returns pointer to assigned segment for point p, or NULL
		const ISegment* getAssignedSegment(const Point& p) const;
	};
}

