#include "prefilter_cv.h"
#include <opencv2/opencv.hpp>
#include "image.h"
#include "image_utils.h"
#include "pixel_boundings.h"
#include "segment_tools.h"
#include "weak_segmentator.h"
#include "adaptive_filter.h"
#include "prefilter.h"
#include "chemical_structure_recognizer.h"
#include "log_ext.h"

namespace imago
{
	void imago::prefilterEntrypoint(Settings& vars, Image& raw)
	{
		vars.general.ImageWidth = vars.general.OriginalImageWidth = raw.getWidth();
		vars.general.ImageHeight = vars.general.OriginalImageHeight = raw.getHeight();

		prefilter_cv::resampleImage(raw);

		vars.general.IsHandwritten = true;

		if (prefilter_cv::isBinarized(vars, raw))
		{
			vars.general.IsHandwritten = false;			
			vars.general.DefaultFilterType = ftPass;
		}

		if (vars.general.DefaultFilterType == ftAdaptive)
		{
			AdaptiveFilter::process(vars, raw);
		}			
		else if (vars.general.DefaultFilterType == ftCV)
		{
			prefilter_cv::prefilterCV(vars, raw);
		}			
		else if (vars.general.DefaultFilterType == ftStd)
		{
			prefilterStd(vars, raw);
		}
		else
		{
			// ftPass, do nothing
		}

		vars.updateCluster();
	}

	namespace prefilter_cv
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

				// this code allows to crop image in rectangular border
				// useful only for 1 image from Image2Structure set
				// but works quite fast.
				{
					WeakSegmentator ws(image.getWidth(), image.getHeight());
					ws.appendData(ImgAdapter(image,image), 1);

					Rectangle viewport;
					if (ws.needCrop(vars, viewport, vars.prefilterCV.MaxRectangleCropLineWidthAlreadyBinarized))
					{
						image.crop(viewport.x1(), viewport.y1(), viewport.x2(), viewport.y2());
					}
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
			static const int CV_THRESH_BINARY = 0;

			logEnterFunction();

			cv::Mat grayFrame;
			ImageUtils::copyImageToMat(raw, grayFrame);
		
			cv::Mat reduced2x((grayFrame.rows+1)/2, (grayFrame.cols+1)/2, CV_8U);
			cv::pyrDown(grayFrame, reduced2x);

			cv::Mat smoothed2x(grayFrame.rows, grayFrame.cols, CV_8U);
			cv::pyrUp(reduced2x, smoothed2x);		

			cv::Mat strong;
			cv::adaptiveThreshold(smoothed2x, strong, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, (vars.prefilterCV.StrongBinarizeSize) + (vars.prefilterCV.StrongBinarizeSize) % 2 + 1, vars.prefilterCV.StrongBinarizeTresh);
			getLogExt().appendMat("strong", strong);

			cv::Mat weak;
			cv::adaptiveThreshold(smoothed2x, weak,   255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, (vars.prefilterCV.WeakBinarizeSize)   + (vars.prefilterCV.WeakBinarizeSize) % 2 + 1,   vars.prefilterCV.WeakBinarizeTresh);	
			getLogExt().appendMat("weak",   weak);

			Image* output = NULL;
			Rectangle viewport;
			int tresholdPassSum = 0, tresholdPassCount = 0;

			int borderX = raw.getWidth()  / vars.prefilterCV.BorderPartProportion + 1;
			int borderY = raw.getHeight() / vars.prefilterCV.BorderPartProportion + 1;

			{
				Image bin;
				ImageUtils::copyMatToImage(weak, bin);

				WeakSegmentator ws(raw.getWidth(), raw.getHeight());
				ws.appendData(ImgAdapter(raw,bin), 1);

				viewport = Rectangle(0, 0, raw.getWidth(), raw.getHeight());
				ws.needCrop(vars, viewport, vars.prefilterCV.MaxRectangleCropLineWidth);

				output = new Image(viewport.width, viewport.height);
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
						if (getLogExt().loggingEnabled())
						{
							std::map<std::string, int> temp;
							temp["Segment id"] = it->first;
							temp["Good points"] = good;
							temp["Bad points"] = bad;
							getLogExt().appendMap("Append segment", temp);
						}

						for (size_t u = 0; u < p.size(); u++)
						{
							int x = p[u].x - viewport.x;
							int y = p[u].y - viewport.y;
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

				if (tresholdPassCount > 0 && vars.prefilterCV.UseTresholdPixelsAddition)
				{
					// second pass; now against the source image

					double average_fill_output = 0.0;
					for (int x = 0; x < output->getWidth(); x++)
						for (int y = 0; y < output->getHeight(); y++)
							if (output->getByte(x,y) == 0)
								average_fill_output += 1;
					average_fill_output /= (output->getWidth()*output->getHeight());

					// now fill inside areas
					double tr = (double)tresholdPassSum / tresholdPassCount;
					byte estimatedTreshold = round(tr + vars.prefilterCV.AdditionPercentage * tr);
					getLogExt().append("estimatedTreshold", (int)estimatedTreshold);

					Image* tresh = new Image(raw.getWidth(), raw.getHeight());
					for (int y = 0; y < raw.getHeight(); y++)
						for (int x = 0; x < raw.getWidth(); x++)							
							tresh->getByte(x, y) = (raw.getByte(x, y) < estimatedTreshold) ? 0 : 255;

					WeakSegmentator ws(raw.getWidth(), raw.getHeight());
					ws.appendData(ImgAdapter(raw,*tresh), 2);
					
					tresh->fillWhite();

					for (WeakSegmentator::SegMap::const_iterator it = ws.SegmentPoints.begin(); it != ws.SegmentPoints.end(); it++)
					{
						const Points2i& p = it->second;
		
						int good = 0, bad = 0;
						for (size_t u = 0; u < p.size(); u++)
						{
							if (p[u].x > borderX && p[u].y > borderY
								&& p[u].x < raw.getWidth() - borderX && p[u].y < raw.getHeight() - borderY
								&& output->getByte(p[u].x, p[u].y) == 0)
								good++;
							else
								bad++;
						}

						if (vars.prefilterCV.MaxBadToGoodRatio2 * good > bad && good > vars.prefilterCV.MinGoodPixelsCount2)
						{							
							for (size_t u = 0; u < p.size(); u++)
							{
								int x = p[u].x - viewport.x;
								int y = p[u].y - viewport.y;
								if (x >= 0 && y >= 0 && x < output->getWidth() && y < output->getHeight())
								{
									tresh->getByte(x, y) = 0;
								}
							}
						}
					}

					getLogExt().appendImage("segments get by average treshold", *tresh);

					double average_fill_tresh = 0.0;
					for (int x = 0; x < tresh->getWidth(); x++)
						for (int y = 0; y < tresh->getHeight(); y++)
							if (tresh->getByte(x,y) == 0)
								average_fill_tresh += 1;
					average_fill_tresh /= (tresh->getWidth() * tresh->getHeight());
					
					getLogExt().append("average fill output", average_fill_output);
					getLogExt().append("average fill tresh", average_fill_tresh);

					double ratio = average_fill_tresh / average_fill_output;
					getLogExt().append("ratio", ratio);

					if (ratio < vars.prefilterCV.MaxFillRatio)
					{			
						// add tresh to output
						for (int y = 0; y < viewport.height; y++)
							for (int x = 0; x < viewport.width; x++)
								if (tresh->getByte(viewport.x + x, viewport.y + y) == 0)
									output->getByte(x,y) = 0;
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
	} // end namespace

}

