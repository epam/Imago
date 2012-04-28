#pragma once

#include "vec2d.h"
#include "stl_fwd.h"
#include "rectangle.h"

namespace imago
{
	class PixelIterableInterface
	{
	public:
		// produces the next object point calculated by internal object state
		// returns false if no more points there are (the last reached)
		virtual bool itNext(Vec2i& point) = 0;
		// resets the internal object state; so itNext will return the first point
		virtual void itReset() = 0;
		
		// returns area. generic, not best performance
		virtual int getArea()
		{			
			int area = 0;
			itReset();
			for (Vec2i p; itNext(p); area++);
			return area;
		}
	};

	class RectShapedBounding : public PixelIterableInterface
	{
	public:
		RectShapedBounding(const RectShapedBounding& src);
		RectShapedBounding(const Points2i& pts);

		virtual bool itNext(Vec2i& point);
		virtual void itReset();

		inline const Rectangle& getBounding() const { return bound; }

	private:
		Rectangle bound;
		int cur_x, cur_y;
	};

	class CustomShapedBounding : public PixelIterableInterface
	{
	public:
		CustomShapedBounding(const CustomShapedBounding& src);
		CustomShapedBounding(const Points2i& pts);

		virtual bool itNext(Vec2i& point);
		virtual void itReset();

	private:
		typedef std::vector<std::pair</*start y*/int, /*end y*/int> > Slice;
		typedef std::vector<std::pair</*x*/int, /*y's*/Slice> > SliceList;
		SliceList slices;
		size_t cur_slice, cur_range;
		int cur_yval;
	};
}

