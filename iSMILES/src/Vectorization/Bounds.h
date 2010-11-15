#pragma once
#include "../Image/Point.h"
#include "../Image/Image.h"

namespace gga
{
	class Bounds
	{
		Coord Left, Right, Top, Bottom;
	public:
		Bounds(Coord left, Coord right, Coord top, Coord bottom);
		Bounds(const Points& points);
		
		inline Coord getLeft()   const { return Left; }
		inline Coord getRight()  const { return Right; }
		inline Coord getTop()    const { return Top; }
		inline Coord getBottom() const { return Bottom; }
		
		inline Coord getWidth()  const { return Right - Left + 1; }
		inline Coord getHeight() const { return Bottom - Top + 1; }
		inline unsigned int getArea()   const { return getWidth()*getHeight(); }
		
		bool isInside(const Image& image)  const;
		bool isInside(const Bounds& outer) const;
	};
}

