#pragma once

#include <map>
#include "image_interface.h"
#include "basic_2d_storage.h"
#include "rectangle.h"
#include "stl_fwd.h"

namespace imago
{
	/* Affects: recognition of rectangle-cropped images; sticky notes, etc (HI)
	Depends on: line thickness(HI,BOUND) */
	static const double AREA_THRESHOLD_FACTOR = 0.30; // %, minimal rectangle coverage of image
	static const int    RECTANGULAR_WINDOWSIZE = 12;   // maximal rectangle side width
	static const double RECTANGULAR_THRESHOLD = 0.95; // %, for rectange testing

	class WeakSegmentator : public Basic2dStorage<int>
	{
	public:
		WeakSegmentator(const ImageInterface &img);
		~WeakSegmentator();
		int appendData(const ImageInterface &img, int lookup_range);
		void performPixelOptimizations();
		void eraseNoise(int threshold);
		bool needCrop(Rectangle& crop);

		static int GetAverageIntensity(const ImageInterface &img, const Points2i& pts);

		inline bool isContiniousConnected(int x, int y1, int y2);

		Points2i GetInside(const Points2i& pts, int lookup_range);

		void fillInside(const ImageInterface &img, int lookup_range);
	
		void getBoundingBox(Rectangle& bound) const;

	protected:
		void getRectBounds(const Points2i& p, Rectangle& bounds, bool reinit = true) const;		
		int getRectangularArea(int id);
		bool hasRectangularStructure(int id, int window_size, double threshold, Rectangle& bound);

		std::map<int, Points2i> SegmentPoints;
		int id, added_pixels;
		int start_id;

	private:
		void fill(const ImageInterface &img, int id, int sx, int sy, int lookup_range);
		static bool get2centers(int* data, int size, double &c1, double& c2);
	};
}
