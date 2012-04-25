#include "adaptive_filter.h"
#include <queue>
#include "log_ext.h"
#include "thin_filter2.h"
#include "generic_histogram.h"
#include "weak_segmentator.h"
#include "prefilter.h"
#include "prefilter_cv.h"

namespace imago
{
	/* Affects: recognition quality (LO), recognition time(LO)
	   Depends on: jpeg artifacts / camera noise / etc(LO)
	   */
	const int    INTERPOLATION_LEVEL = 2;      // (2*n+1)^2 kernel for mean filter will be used

	/* Affects: recognition quality(LO), recognition time(HI)
		*/
	const int    MAX_CROPS = 1;                
	const int    MAX_REFINE_ITERS = 2;

	// ---------------------------------------------------------------------------------

	void AdaptiveFilter::interpolateImage(const AdaptiveFilter& src, int radius) 
	{
		logEnterFunction();

		this->diffIterations = src.diffIterations;
		this->diffStepRange = src.diffStepRange;

		double int2 = (2*radius+1)*(2*radius+1);

		for (int y = 0; y < src.height(); y++)
			for (int x = 0; x < src.width(); x++)
			{				
				int sx = x, sy = y;

				// deal with corners
				if (sx < radius) sx = radius;
				if (sy < radius) sy = radius;
				if (sx >= src.width() - radius - 1) sx = src.width() - radius - 1;
				if (sy >= src.height() - radius - 1) sy = src.height() - radius - 1;

				double temp = 0.0;
				for (int dx = -radius; dx <= radius; dx++)
				{
					for (int dy = -radius; dy <= radius; dy++)
					{
						temp += src.at(sx + dx, sy + dy).intensity;
					}
				}

				at(x,y).intensity = (GrayscaleData)(temp / int2);
			}
	}

	unsigned char AdaptiveFilter::getMaximalIntensityDiff(int sx, int sy)
	{		
		if (at(sx,sy).diffCache == BLANK)
		{
			// restart:

			int cx = sx, cy = sy;

			for (int i = 0; i < diffIterations; i++)
			{			
				int ncx = cx, ncy = cy;
				for (int dx = -diffStepRange; dx <= diffStepRange; dx++)
					for (int dy = -diffStepRange; dy <= diffStepRange; dy++)
						if ((dx != 0 || dy != 0) && inRange(cx+dx, cy+dy))
							if (at(cx+dx,cy+dy).intensity > at(ncx,ncy).intensity)
							{
								ncx = cx+dx; ncy = cy+dy;
							}
				if (cx == ncx && cy == ncy)
					break;
				cx = ncx; cy = ncy;
			}

			/*if (iterations > 0 && at(cx,cy).intensity > 250) // glare // TODO: !!!
			{
				iterations /= 2;
				goto restart;				
			}*/
			
			unsigned char d = absolute(at(cx,cy).intensity - at(sx,sy).intensity);
			
			// small fixup to avoid recalculation if diff too big
			if (d == BLANK) d--;

			at(sx,sy).diffCache = d;
		}

		return at(sx,sy).diffCache;
	}

	unsigned char AdaptiveFilter::getIntensityBound(double inkTresh, const Rectangle& crop, WeakSegmentator* ws)
	{
		logEnterFunction();

		Histogram<256> distHist;
		for (int y = crop.y1(); y < crop.y2(); y++)
			for (int x = crop.x1(); x < crop.x2(); x++)
				if (ws == NULL || !ws->alreadyExplored(x - crop.x1(), y - crop.y1()))
					distHist.addData(getMaximalIntensityDiff(x, y));
		getLogExt().appendText("Accessed all pixels data");
		unsigned char result = distHist.getValueMoreThan(inkTresh);		
		getLogExt().append("Intensity diff bound", (int)result);
		return result;
	}

	void AdaptiveFilter::normalizedOuput(Image& img, const Rectangle& crop, WeakSegmentator* ws)
	{
		logEnterFunction();

		int minv = 255, maxv = 0;
		double average = 0.0;
		for (int y = 0; y < crop.height; y++)
			for (int x = 0; x < crop.width; x++)
			{
				if (ws == NULL || ws->readyForOutput(x,y))
				{
					GrayscaleData c = at(crop.x+x,crop.y+y).intensity;
					if (c < minv) minv = c;
					if (c > maxv) maxv = c;
					average += c;
				}
			}

		getLogExt().append("Minimal intensity matches diff", minv);
		getLogExt().append("Maximal intensity matches diff", maxv);
		getLogExt().append("Ink percentage", average / (img.getWidth() * img.getHeight()));

		if (minv == maxv && minv == 0)
		{
			// B/W images, fixup
			maxv = BLANK;
		}

		if (minv < maxv)
		{
			img.clear();
			img.init(crop.width, crop.height);

			double factor = double(BLANK) / double(maxv - minv);
			getLogExt().append("Normalization factor", factor);

			for (int y = 0; y < img.getHeight(); y++)
			{
				for (int x = 0; x < img.getWidth(); x++)
				{							
					if (ws == NULL || ws->readyForOutput(x,y))
					{
						GrayscaleData c = at(crop.x + x, crop.y + y).intensity;
						img.getByte(x, y) = (byte)(factor * (c - minv));
					}
					else
					{
						img.getByte(x, y) = BLANK;
					}
				}
			}
		}
	}


	class ImageAdapter : public ImageInterface
	{
	public:
		ImageAdapter(AdaptiveFilter& _af, Rectangle& _crop, int _diff_bound)
			: af(_af), crop(_crop), diff_bound(_diff_bound) { }		
		
		virtual bool isFilled(int x, int y) const		
		{
			return af.getMaximalIntensityDiff(crop.x + x, crop.y + y) >= diff_bound;
		}

		virtual unsigned char getIntensity(int x, int y) const
		{
			return af.at(crop.x + x, crop.y + y).intensity;
		}

		virtual int width() const
		{
			return crop.width;
		}

		virtual int height() const
		{
			return crop.height;
		}

		int getBound() const 
		{
			return diff_bound;
		}

		void updateBound(int v)
		{
			diff_bound = v;
		}

	private:
		AdaptiveFilter& af;
		Rectangle& crop;
		int diff_bound;
	};

	void AdaptiveFilter::process(Image& raw)
	{
		logEnterFunction();

		Image bitmask;
		bitmask.copy(raw);
		prefilterCV(bitmask);

		getLogExt().appendImage("raw", raw);		
		getLogExt().appendImage("binarized", bitmask);

		double inkPercentage = 0.0;
		// update ink percentage
		for (int x = 0; x < bitmask.getWidth(); x++)
			for (int y = 0; y < bitmask.getHeight(); y++)
				if (bitmask.getByte(x, y) == 0)
					inkPercentage += 1.0;
		inkPercentage /= bitmask.getWidth() * bitmask.getHeight() * 2;
		inkPercentage *= 1.2;
		
		// update line thickness
		double lineThickness = estimateLineThickness(bitmask);

		if (lineThickness <= 1.0) lineThickness = 1.0;
		if (lineThickness >= 10.0) lineThickness = 10.0;
		if (inkPercentage > 0.15) inkPercentage = 0.15;
		if (inkPercentage < 0.001) inkPercentage = 0.001;

		getLogExt().append("Line thickness", lineThickness);
		getLogExt().append("Ink percentage", inkPercentage);
		
		AdaptiveFilter af(raw.getWidth(), raw.getHeight());
		af.filterImage(raw, true, inkPercentage, (int)lineThickness);
		getLogExt().appendImage("filtered", raw);
	}

	void AdaptiveFilter::filterImage(Image& output, bool allowCrop, 
		                             double probablyInkPercentage, 
									 int lineThickness)
	{	
		logEnterFunction();	

		diffStepRange = 1; // one step pixels count
		diffIterations = lineThickness; // max steps count

		while (diffIterations > 4)
		{
			diffStepRange++;
			diffIterations = lineThickness / diffStepRange;
		}

		int diffFullPath  = diffStepRange * diffIterations;
		int winSize = 2 * lineThickness;

		double inkTresh = 1.0 - probablyInkPercentage;
		double refineTresh = inkTresh; // fixed, cause it's meaning is relative

		getLogExt().append("diffIterations", diffIterations);
		getLogExt().append("diffStepRange", diffStepRange);
		getLogExt().append("winSize", winSize);
		getLogExt().append("inkTresh", inkTresh);
		getLogExt().append("refineTresh", refineTresh);

		PrefilterParams p;
		p.logSteps = false;
		p.binarizeImage = false;
		p.strongThresh = true;

		//prefilterKernel(output, output, p);

		for (int h = 0; h < output.getHeight() && h < height(); h++)
			for (int w = 0; w < output.getWidth() && w < width(); w++)
				at(w,h).intensity = output.getByte(w,h);

		Rectangle crop(0, 0, this->width(), this->height());
		AdaptiveFilter interpolated(this->width(), this->height());
		interpolated.interpolateImage(*this, INTERPOLATION_LEVEL);

		// maximal crops allowed loop
		for (int crop_attempt = 0; crop_attempt <= MAX_CROPS; crop_attempt++)
		{
			int bound = interpolated.getIntensityBound(inkTresh, crop);
			ImageAdapter img(*this, crop, bound);
			WeakSegmentator ws(img.width(), img.height());

			int addedPixels = ws.appendData(img, diffIterations);

			if (!allowCrop || crop_attempt == MAX_CROPS || !ws.needCrop(crop, winSize))
			{
				getLogExt().appendText("Enter refinements loop");

				// refine loop
				for (int refine_iter = 1; refine_iter <= MAX_REFINE_ITERS; refine_iter++)
				{
					ws.updateRefineMap(diffFullPath);

					int new_bound = interpolated.getIntensityBound(refineTresh, crop, &ws);

					if (new_bound >= bound)
					{						
						getLogExt().append("Warning: Bound not changed", new_bound);
						break;
					}

					bound = new_bound;

					if (new_bound <= 0)
					{
						getLogExt().append("New intensity bound is too low, quit loop", new_bound);
						break;
					}

					img.updateBound(new_bound);					

					int added_n = ws.appendData(img, diffIterations);
					if (added_n < lineThickness)
					{
						getLogExt().append("Crossed useful refinements boundary on iteration", refine_iter);
						break;
					}
				}

				normalizedOuput(output, crop, &ws);
				break;
			}
		}

		for (int y = 0; y < output.getHeight(); y++)
			for (int x = 0; x < output.getWidth(); x++)
				output.getByte(x, y) = (output.getByte(x, y) < 255) ? 0 : 255;

		SegmentTools::fixBrokenPixels(output);
	}
}