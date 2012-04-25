#include "prefilter_cv.h"
#include <opencv/cv.h>
#include "image.h"
#include "image_utils.h"
#include "image_interface.h"
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

		if (10 * others_count < black_count + white_count)
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

	// required for prefilterCV implementation
	class ImgAdapter :  public ImageInterface
	{
	public:
		ImgAdapter(const Image& _raw, const Image& _bin) : raw(_raw), bin(_bin)
		{
		}

		virtual bool isFilled(int x, int y) const
		{
			return bin.getByte(x,y) == 0;
		}		
	
		virtual unsigned char getIntensity(int x, int y) const
		{
			return raw.getByte(x,y);
		}

		virtual int width() const 
		{
			return std::min(raw.getWidth(), bin.getWidth());
		}
	
		virtual int height() const
		{
			return std::min(raw.getHeight(), bin.getHeight());
		}
	private:
		const Image& raw;
		const Image& bin;
	};

	bool prefilterCV(Image& raw)
	{
		logEnterFunction();

		cv::Mat grayFrame;
		ImageUtils::copyImageToMat(raw, grayFrame);

		cv::Mat smoothed2x(grayFrame.rows, grayFrame.cols, CV_8U);
		cv::Mat reduced2x((grayFrame.rows+1)/2, (grayFrame.cols+1)/2, CV_8U);
		cv::pyrDown(grayFrame, reduced2x);
		cv::pyrUp(reduced2x, smoothed2x);

		#define binarize(what, output, adaptiveThresholdBlockSize, adaptiveThresholdParameter) \
			cv::adaptiveThreshold((what), (output), 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, 0 /*CV_THRESH_BINARY*/, (adaptiveThresholdBlockSize) + (adaptiveThresholdBlockSize) % 2 + 1, (adaptiveThresholdParameter));
	
		cv::Mat strong, weak;
		binarize(smoothed2x, strong, 4, 1.3);
		binarize(smoothed2x,  weak,  8, 1.2);
	
		getLogExt().appendMat("strong", strong);
		getLogExt().appendMat("weak",   weak);

		Image bin;
		ImageUtils::copyMatToImage(weak, bin);

		WeakSegmentator ws(raw.getWidth(), raw.getHeight());
		ws.appendData(ImgAdapter(raw,bin), 1);

		int borderX = raw.getWidth()  / 40 + 1;
		int borderY = raw.getHeight() / 40 + 1;

		Rectangle crop = Rectangle(0, 0, raw.getWidth(), raw.getHeight());
		bool need_crop = ws.needCrop(crop, 12);

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

			if (6*good > bad && good > 10)
			{
				//printf("Segment %u: %u / %u\n", it->first, good, bad);
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

		bool result = true;

		{
			int filled = 0, blank = 0;
			for (int x = 0; x < output.getWidth(); x++)
				for (int y = 0; y < output.getHeight(); y++)
				{
					if (output.getByte(x,y) == 0)
						filled++;
					else
						blank++;
				}

			// in percents
			double ratio = 100.0 * (double)filled / ((double)blank + 0.001);		

			getLogExt().append("B/W ratio", ratio);

			if (ratio < 0.1 || ratio > 7.5)
			{
				getLogExt().appendText("B/W ratio fails, pass image to other filters");
		 		result = false;
			}
		}

		if (result)
		{
			raw.copy(output);
		}

		return result;
	}

}

