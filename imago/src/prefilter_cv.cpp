#include "prefilter_cv.h"
#include <opencv/cv.h>
#include "image.h"
#include "image_utils.h"
#include "pixel_boundings.h"
#include "segment_tools.h"
#include "weak_segmentator.h"
#include "log_ext.h"

namespace imago
{

	bool resampleImage(Image &image)
	{
		logEnterFunction();

		int w = image.getWidth();
		int h = image.getHeight();
		int m = std::max(w, h);
		int scale = 1;
		while (m / scale > MAX_IMAGE_DIMENSIONS) scale++;
		if (scale == 1)
		{
			getLogExt().appendText("resample is not required");
			return false;
		}
		else
		{
			getLogExt().append("Required resample by", scale);
			Image temp(w / scale, h / scale);
			for (int y = 0; y < temp.getHeight(); y++)
				for (int x = 0; x < temp.getWidth(); x++)			
				{
					int c = 0;
					for (int dy = 0; dy < scale; dy++)
						for (int dx = 0; dx < scale; dx++)
							c += image.getByte(x*scale+dx, y*scale+dy);
					temp.getByte(x, y) = c / scale / scale;
				}
			image.copy(temp);
			return true;
		}
	}

	bool isBinarized(Image &image)
	{
		logEnterFunction();

		const int MAX_NON_BW_PIXELS_PROPORTION = 10;

		int white_count = 0, black_count = 0, others_count = 0;
		for (int y = 0; y < image.getHeight(); y++)
			for (int x = 0; x < image.getWidth(); x++)
				if (image.getByte(x, y) == 0)
					black_count++;
				else if (image.getByte(x, y) == 255)
					white_count++;
				else 
					others_count++;

		getLogExt().append("white_count", white_count);
		getLogExt().append("black_count", black_count);
		getLogExt().append("others_count", others_count);

		if (MAX_NON_BW_PIXELS_PROPORTION * others_count < black_count + white_count)
		{	
			getLogExt().appendText("image is binarized");
			if (others_count > 0)
			{
				getLogExt().appendText("Fixup other colors");
				for (int y = 0; y < image.getHeight(); y++)
					for (int x = 0; x < image.getWidth(); x++)
						if (image.getByte(x, y) != 255)
							image.getByte(x, y) = 0;
			}
			return true;
		}
		else
		{
			getLogExt().appendText("image requires processing");
			return false;
		}
	}	

	void prefilterCV(Image& raw)
	{
		logEnterFunction();

		const int MIN_GOOD_PIXELS_COUNT = 10; // minimal pixels count for good segment
		const int MAX_BAD_TO_GOOD_RATIO = 6;  // used for classification of good/bad segments
		const int BORDER_PROPORTIONS = 40;    // border is 1/nth part of corresponding image dimension
		const int MAX_RECTANGLE_WIDTH = 12;   // pixels count for rectangular crop

		cv::Mat grayFrame;
		ImageUtils::copyImageToMat(raw, grayFrame);

		cv::Mat smoothed2x(grayFrame.rows, grayFrame.cols, CV_8U);
		cv::Mat reduced2x((grayFrame.rows+1)/2, (grayFrame.cols+1)/2, CV_8U);
		cv::pyrDown(grayFrame, reduced2x);
		cv::pyrUp(reduced2x, smoothed2x);

		#define binarize_impl(what, output, adaptiveThresholdBlockSize, adaptiveThresholdParameter) \
			cv::adaptiveThreshold((what), (output), 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, 0 /*CV_THRESH_BINARY*/, (adaptiveThresholdBlockSize) + (adaptiveThresholdBlockSize) % 2 + 1, (adaptiveThresholdParameter));
	
		cv::Mat strong, weak;
		binarize_impl(smoothed2x, strong, 4, 1.3);
		binarize_impl(smoothed2x,  weak,  8, 1.2);

		#undef binarize_impl
	
		getLogExt().appendMat("strong", strong);
		getLogExt().appendMat("weak",   weak);

		Image bin;
		ImageUtils::copyMatToImage(weak, bin);

		WeakSegmentator ws(raw.getWidth(), raw.getHeight());
		ws.appendData(ImgAdapter(raw,bin), 1);

		int borderX = raw.getWidth()  / BORDER_PROPORTIONS + 1;
		int borderY = raw.getHeight() / BORDER_PROPORTIONS + 1;

		Rectangle crop = Rectangle(0, 0, raw.getWidth(), raw.getHeight());
		bool need_crop = ws.needCrop(crop, MAX_RECTANGLE_WIDTH);

		Image output(crop.width, crop.height);
		output.fillWhite();

		for (WeakSegmentator::SegMap::const_iterator it = ws.SegmentPoints.begin(); it != ws.SegmentPoints.end(); it++)
		{
			const Points2i& p = it->second;
		
			int good = 0, bad = 0;
			for (size_t u = 0; u < p.size(); u++)
			{
				if (p[u].x > borderX && p[u].y > borderY
					&& p[u].x < raw.getWidth() - borderX && p[u].y < raw.getHeight() - borderY
					&& strong.at<unsigned char>(p[u].y, p[u].x) == 0)
					good++;
				else
					bad++;
			}

			if (MAX_BAD_TO_GOOD_RATIO * good > bad && good > MIN_GOOD_PIXELS_COUNT)
			{
				getLogExt().append("Segment id", it->first);
				getLogExt().append("Good points", good);
				getLogExt().append("Bad points", bad);
				getLogExt().appendText("");

				for (size_t u = 0; u < p.size(); u++)
				{
					int x = p[u].x - crop.x;
					int y = p[u].y - crop.y;
					if (x >= 0 && y >= 0 && x < output.getWidth() && y < output.getHeight())
					{
						output.getByte(x, y) = 0;
					}
				}
			}
		}

		getLogExt().appendImage("output", output);

		raw.copy(output);
	}

}

