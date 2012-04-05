#include "adaptive_filter.h"
#include <queue>
#include "log_ext.h"
#include "generic_histogram.h"
#include "weak_segmentator.h"
#include "prefilter.h"
#include "thin_filter2.h"

namespace imago
{
	/* Affects: recognition quality (MED), recognition time(HI, cause of MAX_REFINE_ITERS)
	   Depends on: real image ink coverage ratio(MED)
	   */
	const double INK_THRESHOLD = 0.995;	       // 1-% for initial ink coverage
	
	/* Affects: recognition quality (LO), recognition time(LO)
	   Depends on: jpeg artifacts / camera noise / etc(LO)
	   */
	const int    INTERPOLATION_LEVEL = 2;      // (2*n+1)^2 kernel for mean filter will be used

	/* Affects: recognition quality (MED), recognition time(LO)
	   Depends on: line thickness(HI,BOUND)
	   */
	const int    DIFF_STEP_RANGE = 2;          // one step pixels count
	const int    DIFF_ITERATIONS = 4;          // max steps count
	const int    DIFF_FULL_PATH  = DIFF_ITERATIONS*DIFF_STEP_RANGE;

	/* Affects: recognition quality(LO)
	   Depends on: line thickness(LO,BOUND)
	   */
	const int    ERASE_NOISE_THRESHOLD = 32;   // pixels count, less that will be erased as noise	

	/* Affects: recognition quality(LO), recognition time(HI)
		*/
	const int    MAX_CROPS = 1;                // 1 is sufficient in most cases
	const int    MAX_REFINE_ITERS = 5;

	// ---------------------------------------------------------------------------------

	void AdaptiveFilter::interpolateImage(const AdaptiveFilter& src, int radius) 
	{
		logEnterFunction();

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

				at(x,y).intensity = temp / int2;
			}
	}

	unsigned char AdaptiveFilter::getMaximalIntensityDiff(int sx, int sy, int iterations)
	{		
		if (at(sx,sy).diffCache == BLANK)
		{
			// restart:

			int cx = sx, cy = sy;

			for (int i = 0; i < iterations; i++)
			{			
				int ncx = cx, ncy = cy;
				for (int dx = -DIFF_STEP_RANGE; dx <= DIFF_STEP_RANGE; dx++)
					for (int dy = -DIFF_STEP_RANGE; dy <= DIFF_STEP_RANGE; dy++)
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
			
			unsigned char d = abs(at(cx,cy).intensity - at(sx,sy).intensity);
			
			// small fixup to avoid recalculation if diff too big
			if (d == BLANK) d--;

			at(sx,sy).diffCache = d;
		}

		return at(sx,sy).diffCache;
	}

	unsigned char AdaptiveFilter::getIntensityBound(const Rectangle& crop, WeakSegmentator* ws)
	{
		logEnterFunction();

		Histogram<256> distHist;
		for (int y = crop.y1(); y < crop.y2(); y++)
			for (int x = crop.x1(); x < crop.x2(); x++)
				if (ws == NULL || !ws->alreadyExplored(x - crop.x1(), y - crop.y1()))
					distHist.addData(getMaximalIntensityDiff(x, y, DIFF_ITERATIONS));
		unsigned char result = distHist.getValueMoreThan(INK_THRESHOLD);		
		getLogExt().append("Intensity diff bound", (int)result);
		return result;
	}

	void AdaptiveFilter::normalizedOuput(Image& img, const Rectangle& crop, WeakSegmentator* ws)
	{
		logEnterFunction();

		int minv = 255, maxv = 0, average = 0;
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
		getLogExt().append("Average", average / (crop.width * crop.height));

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
						img.getByte(x, y) = factor * (c - minv);
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
			return af.getMaximalIntensityDiff(crop.x + x, crop.y + y, DIFF_ITERATIONS) >= diff_bound;
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

	void AdaptiveFilter::filterImage(Image& output)
	{	
		logEnterFunction();	

		doWiener(output);
		for (int h = 0; h < output.getHeight(); h++)
			for (int w = 0; w < output.getWidth(); w++)
				at(w,h).intensity = output.getByte(w,h);

		Rectangle crop(0, 0, this->width(), this->height());
		AdaptiveFilter interpolated(this->width(), this->height());
		interpolated.interpolateImage(*this, INTERPOLATION_LEVEL);

		if (FILTER_DUMP_IMAGES && getLogExt().loggingEnabled())
		{
			getLogExt().appendImage("Source image (in Image)", output);
			Image temp;
			normalizedOuput(temp, crop);
			getLogExt().appendImage("Source image (in AdaptiveFilter)", temp);
			interpolated.normalizedOuput(temp, crop);
			getLogExt().appendImage("Interpolated image", temp);
		}		

		double line_thickness = 1.0;
		
		// maximal crops allowed loop
		for (int crop_attempt = 0; crop_attempt <= MAX_CROPS; crop_attempt++)
		{
			int bound = interpolated.getIntensityBound(crop);
			ImageAdapter img(*this, crop, bound);
			WeakSegmentator ws(img.width(), img.height());

			int addedPixels = ws.appendData(img, DIFF_ITERATIONS);

			// update line thickness
			{
				Image temp;
				normalizedOuput(temp, crop, &ws);
				for (int y = 0; y < temp.getHeight(); y++)
					for (int x = 0; x < temp.getWidth(); x++)
						temp.getByte(x, y) = (temp.getByte(x, y) < 127) ? 0 : 255; // TODO, 127
				line_thickness = EstimateLineThickness(temp);
				getLogExt().append("Initial line thickness", line_thickness);
			}

			if (crop_attempt == MAX_CROPS || !ws.needCrop(crop))
			{
				getLogExt().appendText("Enter refinements loop");

				// refine loop
				for (int refine_iter = 1; refine_iter <= MAX_REFINE_ITERS; refine_iter++)
				{
					ws.updateRefineMap(DIFF_FULL_PATH);

					if (FILTER_DUMP_IMAGES && getLogExt().loggingEnabled())
					{
						Image temp;
						normalizedOuput(temp, crop, &ws);
						getLogExt().appendImage("Before refine", temp);
					}

					int new_bound = interpolated.getIntensityBound(crop, &ws);

					if (new_bound >= bound)
					{						
						//new_bound = bound - 1;						
						getLogExt().append("Warning: Bound not changed", new_bound);
					}

					bound = new_bound;

					if (new_bound <= 0)
					{
						getLogExt().append("New intensity bound is too low, quit loop", new_bound);
						break;
					}

					img.updateBound(new_bound);					

					int added_n = ws.appendData(img, DIFF_ITERATIONS);
					if (added_n < ERASE_NOISE_THRESHOLD)
					{
						getLogExt().append("Crossed useful refinements boundary on iteration", refine_iter);
						break;
					}
				}

				// ws.eraseNoise(ERASE_NOISE_THRESHOLD); // temporary. function is wrong

				ws.performPixelOptimizations();

				//ws.reconstructLines(line_thickness);

				normalizedOuput(output, crop, &ws);
				break;
			}
		}
			
		//if (FILTER_DUMP_IMAGES)
		//	getLogExt().appendImage("Refined image", output);

		// TODO: real very important part, affects anything! 140 is bad threshold!		
		for (int y = 0; y < output.getHeight(); y++)
			for (int x = 0; x < output.getWidth(); x++)
				output.getByte(x, y) = (output.getByte(x, y) < 140) ? 0 : 255;

		if (FILTER_DUMP_IMAGES)
			getLogExt().appendImage("Binarized image", output);


		// real hardcore goes here
		{
			ThinFilter2(output).apply();
			
			getLogExt().appendImage("Before final adjust", output);

			Image temp(output.getWidth(), output.getHeight());
			temp.fillWhite();

			double lt_dist = 0.5;
			int min_side = std::min(width(), height());

			getLogExt().append("Min side", min_side);

			if (min_side > 300) lt_dist = 1.0;
			if (min_side > 500) lt_dist = 2.0;
			if (min_side > 800) lt_dist = 3.0;
			if (min_side > 1200) lt_dist = 4.0;

			//while (line_thickness / 2.0 > lt_dist) lt_dist += 1.0;
			getLogExt().append("Reconstruct line thickness", lt_dist);

			for (int h = 0; h < output.getHeight(); h++)
				for (int w = 0; w < output.getWidth(); w++)
				{
					if (output.getByte(w,h) == BLANK)
						continue;

					Points2i nb = WeakSegmentator::getNeighbors(output, Vec2i(w,h), 2);
					// TODO: filter scratches
					if (nb.size() > 2)
					{
						// draw the line pattern (50% overhead here)
						for (int dx = -lt_dist; dx <= lt_dist; dx++)
							for (int dy = -lt_dist; dy <= lt_dist; dy++)
								if (sqrt((double)(dx*dx+dy*dy)) <= lt_dist)
									if (w + dx >= 0 && h + dy >= 0 && w + dx < output.getWidth() && h + dy < output.getHeight())
										temp.getByte(w + dx, h + dy) = INK;
					}
				}

			output.copy(temp);

			getLogExt().appendImage("After final adjust", output);
		}


		line_thickness = EstimateLineThickness(output);
		getSettings()["LineThickness"] = line_thickness;
		getLogExt().append("Line Thickness", line_thickness);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////

	bool FilterImageStub::isAdaptiveFilterEnabled()
	{
		int filter = getSettings()["AdaptiveFilter"];
		bool result = filter > 0;
		if (result)
		{
			getLogExt().appendText("Adaptive filter is enabled");
		}
		else
		{
			getLogExt().appendText("Adaptive filter is disabled");
		}
		return result;
	}
	
	bool FilterImageStub::isColorLoadingRequired()
	{
		int filter = getSettings()["AdaptiveFilter"];
		bool result = filter == 2;
		if (result)
		{
			getLogExt().appendText("Color loading is specified");
		}
		else
		{
			getLogExt().appendText("Grayscale loading is specified");
		}
		return result;
	}

	FilterImageStub::~FilterImageStub()
	{
		if (filterptr)
		{
			filterptr->filterImage(*imgptr);
			delete filterptr;
			filterptr = NULL;
		}
	}

	void FilterImageStub::initPixel(int x, int y, unsigned char intensity)
	{
		int scaled_x = x / scale;
		int scaled_y = y / scale;
		int sc2 = scale * scale;
		if (scaled_x < imgptr->getWidth() && scaled_y < imgptr->getHeight())
		{
			imgptr->getByte(scaled_x, scaled_y) += intensity / sc2;
			if (filterptr)
			{
				filterptr->at(scaled_x, scaled_y).intensity += intensity / sc2;
			}
		}
	}

	void FilterImageStub::initPixel(int x, int y, unsigned char R, unsigned char G, unsigned char B, unsigned char intensity)
	{
		int scaled_x = x / scale;
		int scaled_y = y / scale;
		int sc2 = scale * scale;
		
		if (intensity == 0) // need manual recalc
			intensity = (unsigned char)(((int)R * 299 + (int)G * 587 + (int)B * 114)/1000);

		if (scaled_x < imgptr->getWidth() && scaled_y < imgptr->getHeight())
		{
			imgptr->getByte(scaled_x, scaled_y) += intensity / sc2;
			if (filterptr)
			{
				filterptr->at(scaled_x, scaled_y).intensity += intensity / sc2;
				if (filterptr->rgb)
				{
					filterptr->rgb->at(scaled_x, scaled_y).RGB.R += R / sc2;
					filterptr->rgb->at(scaled_x, scaled_y).RGB.G += G / sc2;
					filterptr->rgb->at(scaled_x, scaled_y).RGB.B += B / sc2;
				}
			}
		}
	}

	FilterImageStub::FilterImageStub(Image* img, int source_width, int source_height) 
		: filterptr(NULL), scale(1)
	{
		logEnterFunction();

		imgptr = img;

		while (source_width / scale > MAX_IMAGE_DIMENSIONS) scale++;
		while (source_height / scale > MAX_IMAGE_DIMENSIONS) scale++;
		getLogExt().append("Selected scale", scale);

		img->clear();
		img->init(source_width / scale, source_height / scale);     	
		getLogExt().append("Image [scaled] width", img->getWidth());
		getLogExt().append("Image [scaled] height", img->getHeight());

		if (isAdaptiveFilterEnabled())
		{
			filterptr = new AdaptiveFilter(img->getWidth(), img->getHeight());
			if (isColorLoadingRequired())
			{
				filterptr->rgb = new AdaptiveFilter::RGBStorage(img->getWidth(), img->getHeight());
			}
		}
	}
}