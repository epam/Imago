#pragma once

#include <map>
#include "image.h"
#include "image_interface.h"
#include "basic_2d_storage.h"
#include "rectangle.h"
#include "stl_fwd.h"

namespace imago
{
	// DEBUG ONLY CONSTANT: add images to log or not (reduces process time)
	const bool FILTER_DUMP_IMAGES = true;

	#pragma pack (push, 1)
	struct SegmentPackedRecord
	{
		unsigned short int id;
		unsigned char refineGeneration;
		unsigned char Reserved;
		SegmentPackedRecord()
		{
			id = refineGeneration = Reserved = 0;
		}
	};
	#pragma pack (pop)

	class WeakSegmentator : public Basic2dStorage<SegmentPackedRecord>
	{
	public:		
		WeakSegmentator(int width, int height) : Basic2dStorage<SegmentPackedRecord>(width, height)
		{
			currentRefineGeneration = 0;
		}

		// addend data from image (img.isFilled() called)
		int appendData(const ImageInterface &img, int lookup_range);
		
		// updates the map for refineIsAllowed( )
		void updateRefineMap(int max_len);

		// remove alone pixels, fill broken pixels
		void performPixelOptimizations();
		
		// erase noise areas by density (pixels/area) threshold
		void eraseNoise(double threshold);

		// remove glares by its maximal are percent (area/img.area) threshold
		void removeGlares(double threshold);
		
		// updates crop if required
		bool needCrop(Rectangle& crop);		

		// required for AdaptiveFilter updateBound( )
		bool alreadyExplored(int x, int y) const;

		// redraw all image with specified line thinkness
		void reconstructLines(double thickness);

		// returns true if point should be returned from filter
		inline bool readyForOutput(int x, int y) const
		{
			return at(x,y).id > 0;
		}

	protected:		
		// returns all segment endpoints
		Points2i getEndpointsDecornered() const;

		// required for appendData (after first one)
		bool refineIsAllowed(int x, int y) const;
		
		// returns area of bounding box of segment with id
		int getRectangularArea(int id);

		// check segment with id has rectangular structure
		bool hasRectangularStructure(int id, Rectangle& bound);

		std::map<int, Points2i> SegmentPoints;
		int currentRefineGeneration;

	private:
		// returns filled pixels count
		void fill(const ImageInterface &img, int& id, int startx, int starty, int lookup_range);

		// returns 2 probably condensation point for integer vector
		static bool get2centers(int* data, int size, double &c1, double& c2);

		// returns neighbors of p with intensity == INK
		Points2i getNeighbors(const Image& img, const Vec2i& p, int range = 1) const;
	};
}
