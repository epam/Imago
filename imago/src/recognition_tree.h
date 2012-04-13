#pragma once

#include "image.h"
#include "segment.h"
#include "stl_fwd.h"
#include "rectangle.h"
#include <vector>

namespace imago
{	
	typedef Rectangle Crop;
	typedef std::vector<Crop> CropList;

	class ImageTreatmentAdapter
	{
	public:
		// treat pixel intensity level as ink tolerance
		virtual byte treat(const Image& img, int x, int y) const = 0;
		// translate the treat() result to binary
		virtual bool ink(const Image& img, int x, int y) const = 0;
		// usually: source_image --treat--> temp_image --ink--> pixels_list
	};

	class DefaultImageTreat : public ImageTreatmentAdapter // suitable for binarized images
	{
	public:
		virtual byte treat(const Image& img, int x, int y) const;
		virtual bool ink(const Image& img, int x, int y) const;
	};

	class AutoconnectionImageTreat : public ImageTreatmentAdapter
	{
	public:
		AutoconnectionImageTreat(int range);
		virtual byte treat(const Image& img, int x, int y) const;
		virtual bool ink(const Image& img, int x, int y) const;
	private:
		int _range;
	};

	class RasterObject
	{
	public:
		RasterObject(const Image& img, const CropList& segments);
		RasterObject(const Image& img, Crop crop);
		RasterObject(const Image& img);

		bool isBinarized() const;

		enum SegmentQueryType
		{
			sqSource,
			sqTreatAdapterUse,
			sqThinned
		};

		void asSegment(const ImageTreatmentAdapter& a, Segment& result, SegmentQueryType q = sqTreatAdapterUse) const;

		enum PointsQuertyType
		{
			pqAll,
			pqThinned,
			pqContour,
			pqEnds
		};

		void getPoints(const ImageTreatmentAdapter& a, Points2i& result, PointsQuertyType q = pqAll) const;

		double getAverageLineThickness(const ImageTreatmentAdapter& a) const;
	
		// utils:
		static void getNeighbors(const ImageTreatmentAdapter& a, Points2i& result, const Image& img, Vec2i pos, int range = 1);

	protected:		

		const Image& _img; // image hard link
		
		CropList _crops; // adjustable crops array
		Crop _bounding;

		void updateBounding();

	private:
		// cached data here
	};

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
		RecognitionTree(const Image& img) : _img(img), _root(img)
		{
		}

		const RasterObject& getRoot() const
		{
			return _root;
		}

		RasterObject& getRoot()
		{
			return _root;
		}

	private:
		RasterObject _root;
		const Image& _img;
	};

}