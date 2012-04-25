#pragma once

#include "image.h"
#include "segment.h"
#include "stl_fwd.h"
#include "rectangle.h"
#include "image_interface.h"
#include <vector>

namespace imago
{	
	class RecognitionRecord
	{
		public:
		double getProbability() const { return _probability; }

		private:
		double _probability;
	};

	class CircleRecognitionRecord : public RecognitionRecord
	{
		public:
	};

	class SegmentRecognitionRecord : public RecognitionRecord
	{
		public:
	};

	class CharacterRecognitionRecord : public RecognitionRecord
	{
		public:
	};

	class RecognitionTree
	{
		public:
		RecognitionTree(const Image& image) : raw(image)
		{
		}

		private:		
		const Image& raw;
	};
}
