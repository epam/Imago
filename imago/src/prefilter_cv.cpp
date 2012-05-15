#include "prefilter_cv.h"
#include <opencv2/opencv.hpp>
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
		while (m / scale > MaxImageDimensions) scale++;
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

	bool isBinarized(const Settings& vars, Image &image)
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

		if (vars.prefilterCV.MaxNonBWPixelsProportion * others_count < black_count + white_count)
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

	void prefilterCV(const Settings& vars, Image& raw)
	{
		logEnterFunction();

		cv::Mat grayFrame;
		ImageUtils::copyImageToMat(raw, grayFrame);

		cv::Mat smoothed2x(grayFrame.rows, grayFrame.cols, CV_8U);
		cv::Mat reduced2x((grayFrame.rows+1)/2, (grayFrame.cols+1)/2, CV_8U);
		cv::pyrDown(grayFrame, reduced2x);
		cv::pyrUp(reduced2x, smoothed2x);

		#define binarize_impl(what, output, adaptiveThresholdBlockSize, adaptiveThresholdParameter) \
			cv::adaptiveThreshold((what), (output), 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, 0 /*CV_THRESH_BINARY*/, (adaptiveThresholdBlockSize) + (adaptiveThresholdBlockSize) % 2 + 1, (adaptiveThresholdParameter));
	
		cv::Mat strong, weak;
		binarize_impl(smoothed2x, strong, vars.prefilterCV.StrongBinarizeSize, vars.prefilterCV.StrongBinarizeTresh);
		binarize_impl(smoothed2x,  weak,  vars.prefilterCV.WeakBinarizeSize,   vars.prefilterCV.WeakBinarizeTresh);

		#undef binarize_impl
	
		getLogExt().appendMat("strong", strong);
		getLogExt().appendMat("weak",   weak);

		Image* output = NULL;
		Rectangle crop;
		int tresholdPassSum = 0, tresholdPassCount = 0;

		{
			Image bin;
			ImageUtils::copyMatToImage(weak, bin);

			WeakSegmentator ws(raw.getWidth(), raw.getHeight());
			ws.appendData(ImgAdapter(raw,bin), 1);

			int borderX = raw.getWidth()  / vars.prefilterCV.BorderPartProportion + 1;
			int borderY = raw.getHeight() / vars.prefilterCV.BorderPartProportion + 1;

			crop = Rectangle(0, 0, raw.getWidth(), raw.getHeight());
			ws.needCrop(vars, crop, vars.prefilterCV.MaxRectangleCropLineWidth);

			output = new Image(crop.width, crop.height);
			output->fillWhite();			

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

				if (vars.prefilterCV.MaxBadToGoodRatio * good > bad && good > vars.prefilterCV.MinGoodPixelsCount)
				{
					getLogExt().append("Segment id", it->first);
					getLogExt().append("Good points", good);
					getLogExt().append("Bad points", bad);
					getLogExt().appendText("");

					for (size_t u = 0; u < p.size(); u++)
					{
						int x = p[u].x - crop.x;
						int y = p[u].y - crop.y;
						if (x >= 0 && y >= 0 && x < output->getWidth() && y < output->getHeight())
						{
							tresholdPassSum += raw.getByte(x, y);
							tresholdPassCount++;
							output->getByte(x, y) = 0;
						}
					}
				}
			}
		}

		if (output)
		{
			getLogExt().appendImage("pre-output", *output);

			if (tresholdPassCount > 0)
			{
				// now fill inside areas
				byte estimatedTreshold = tresholdPassSum / tresholdPassCount;
				getLogExt().append("estimatedTreshold", (int)estimatedTreshold);

				Image* tresh = new Image(crop.width, crop.height);
				for (int y = 0; y < crop.height; y++)
					for (int x = 0; x < crop.width; x++)
						tresh->getByte(x, y) = (raw.getByte(x+crop.x, y+crop.y) < estimatedTreshold) ? 0 : 255;

				getLogExt().appendImage("get by average treshold", *tresh);

				
				// TODO: this is only temporary 
				// should check that tresh areas are inside output before merge pixels!

				if (true)
				{
					// add tresh to output
					for (int y = 0; y < crop.height; y++)
						for (int x = 0; x < crop.width; x++)
							if (tresh->getByte(x,y) == 0)
							{
								int neighbs = 0;
								for (int dx = -1; dx <= 1; dx++)
									for (int dy = -1; dy <= 1; dy++)
										if (x+dx >= 0 && y+dy >= 0 &&
											x+dx < crop.width && y+dy < crop.height)
										{
											if (output->getByte(x+dx,y+dy) == 0)
												neighbs++;
										}
								// this is not the same as correct 'inside' check!
								if (neighbs >= 3)
								{
									output->getByte(x,y) = 0;
								}
							}
				}

				delete tresh;
				tresh = NULL;
			}

			getLogExt().appendImage("output", *output);

			raw.copy(*output);

			delete output;
			output = NULL;
		}
	}

}

