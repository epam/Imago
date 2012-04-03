#pragma once

#include <map>
#include "image.h"
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
		// initialize width x height
		WeakSegmentator(const ImageInterface &img);

		~WeakSegmentator();
		
		// addend data from image (isFilled() called)
		int appendData(const ImageInterface &img, int lookup_range);
		
		// remove alone pixels, fill broken pixels
		void performPixelOptimizations();
		
		// erase noise areas by density threshold
		void eraseNoise(double threshold);

		// remove glares by its maximal are percent (area/img.area) threshold
		void removeGlares(double threshold);
		
		// updates crop if required
		bool needCrop(Rectangle& crop);		

		// updates the map for refineIsAllowed( )
		void updateRefineMap(const ImageInterface &img, int max_len);

		// required for appendData (after first one)
		bool refineIsAllowed(int x, int y) const;

		// required for AdaptiveFilter updateBound( )
		bool alreadyExplored(int x, int y) const;

	protected:		
		// returns all segment endpoints
		Points2i getEndpointsDecornered(const ImageInterface &img) const;
		
		// returns area of bounding box of segment with id
		int getRectangularArea(int id);

		// check segment with id has rectangular structure
		bool hasRectangularStructure(int id, int window_size, double threshold, Rectangle& bound);

		std::map<int, Points2i> SegmentPoints;
		Basic2dStorage<char> refineMap;
		int refineGeneration;

	private:
		// returns filled pixels count
		void fill(const ImageInterface &img, int id, int startx, int starty, int lookup_range);

		// returns 2 probably condensation point for integer vector
		static bool get2centers(int* data, int size, double &c1, double& c2);

		// returns neighbors of p with intensity == INK
		Points2i getNeighbors(const Image& img, const Vec2i& p, int range = 1) const;
	};
}
