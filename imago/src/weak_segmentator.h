/****************************************************************************
 * Copyright (C) 2009-2012 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#pragma once
#ifndef _weak_segmentator_h
#define _weak_segmentator_h

#include <map>
#include "image.h"
#include "color_channels.h"
#include "image_interface.h"
#include "basic_2d_storage.h"
#include "rectangle.h"
#include "stl_fwd.h"
#include "settings.h"

namespace imago
{
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
			ConnectMode = false;
		}

		// addend data from image (img.isFilled() called)
		int appendData(const ImageInterface &img, int lookup_range);
		
		// updates the map for refineIsAllowed( )
		void updateRefineMap(const Settings& vars, int max_len);
				
		// updates crop if required
		bool needCrop(const Settings& vars, Rectangle& crop, int winSize);		

		// required for AdaptiveFilter updateBound( )
		bool alreadyExplored(int x, int y) const;

		// returns true if point should be returned from filter
		inline bool readyForOutput(int x, int y) const
		{
			return at(x,y).id > 0;
		}

		// returns neighbors of p with intensity == INK
		static Points2i getNeighbors(const Image& img, const Vec2i& p, int range = 1);
		
		// decorner image by setting corner pixels to 'set_to'
		static void decorner(Image &img, GrayscaleData set_to);

		// returns endpoints
		static Points2i decorneredEndpoints(Image &img);

		typedef std::map<int, Points2i> SegMap;
		SegMap SegmentPoints;		

		bool ConnectMode;

	protected:		
		// returns all segment endpoints
		Points2i getEndpointsDecornered() const;

		// required for appendData (after first one)
		bool refineIsAllowed(int x, int y) const;
		
		// returns area of bounding box of segment with id
		int getRectangularArea(int id);

		// check segment with id has rectangular structure
		bool hasRectangularStructure(const Settings& vars, int id, Rectangle& bound, int winSize);
		
		int currentRefineGeneration;

	private:
		// returns filled pixels count
		void fill(const ImageInterface &img, int& id, int startx, int starty, int lookup_range);
		
		// returns shortest path between two pixels
		Points2i getShortestPath(const ImageInterface &img, const Vec2i& start, const Vec2i& end);

		// returns 2 probably condensation point for integer vector
		static bool get2centers(int* data, int size, double &c1, double& c2);		
	};
}

#endif //_weak_segmentator_h
