#include "adaptive_filter.h"
#include <queue>
#include "log_ext.h"
#include "generic_histogram.h"
#include "weak_segmentator.h"
#include "prefilter.h"

namespace imago
{
	/* Affects: recognition quality (MED), recognition time(HI, cause of MAX_REFINE_ITERS)
	   Depends on: real image ink coverage ratio(MED)
	   */
	const double INK_THRESHOLD = 0.995;	       // 1-% for initial ink coverage
	
	/* Affects: recognition quality (LO), recognition time(LO)
	   Depends on: jpeg artifacts / camera noise / etc(LO)
	   */
	const int    INTERPOLATION_LEVEL = 3;      // (2*n+1)^2 kernel for mean filter will be used

	/* Affects: recognition quality (MED), recognition time(LO)
	   Depends on: line thickness(HI,BOUND)
	   */
	const int    DIFF_STEP_RANGE = 2;          // one step pixels count
	const int    DIFF_ITERATIONS = 4;          // max steps count
	// this should be greater than line thickness / 2
	const int    MAX_DELTA_PATH = DIFF_STEP_RANGE*DIFF_ITERATIONS;

	/* Affects: recognition quality(LO)
	   Depends on: line thickness(LO,BOUND)
	   */
	const int    ERASE_NOISE_THRESHOLD = 32;   // pixels count, less that will be erased as noise	

	/* Affects: recognition quality(LO), recognition time(HI)
		*/
	const int    MAX_CROPS = 1; // 1 is sufficient in most cases
	const int    MAX_REFINE_ITERS = 5;

	// ---------------------------------------------------------------------------------

	AdaptiveFilter::AdaptiveFilter(int w, int h) : Basic2dStorage<RGBData>(w, h), diff_cache(w, h, BLANK)
	{
	}

	AdaptiveFilter::AdaptiveFilter(const AdaptiveFilter& src, int interpolation) 
		: Basic2dStorage<RGBData>(src.width(), src.height()), 
		  diff_cache(src.width(), src.height(), BLANK)
	{
		logEnterFunction();

		for (int y = 0; y < src.height(); y++)
			for (int x = 0; x < src.width(); x++)
			{				
				int count = 0;
				double L[RGBData::CHANNELS_COUNT] = {0};
				for (int dx = -interpolation; dx <= interpolation; dx++)
					for (int dy = -interpolation; dy <= interpolation; dy++)
					if (inRange(x + dx, y + dy))
					{
						for (int i = 0; i < RGBData::CHANNELS_COUNT; i++)
							L[i] += src.at(x+dx,y+dy).L[i];
						count++;
					}
				for (int i = 0; i < RGBData::CHANNELS_COUNT; i++)
					at(x,y).L[i] = (double)L[i] / count;
			}
	}

	AdaptiveFilter::~AdaptiveFilter()
	{
	}

	int AdaptiveFilter::getMaximalIntensityDiff(int channel, int sx, int sy, int iterations)
	{		
		if (diff_cache.at(sx,sy) == BLANK)
		{
			restart:

			int cx = sx, cy = sy;

			for (int i = 0; i < iterations; i++)
			{			
				int ncx = cx, ncy = cy;
				for (int dx = -DIFF_STEP_RANGE; dx <= DIFF_STEP_RANGE; dx++)
					for (int dy = -DIFF_STEP_RANGE; dy <= DIFF_STEP_RANGE; dy++)
						if ((dx != 0 || dy != 0) && inRange(cx+dx, cy+dy))
							if (at(cx+dx,cy+dy).L[channel] > at(ncx,ncy).L[channel])
							{
								ncx = cx+dx; ncy = cy+dy;
							}
				if (cx == ncx && cy == ncy)
					break;
				cx = ncx; cy = ncy;
			}

			if (iterations > 0 && at(cx,cy).L[channel] > 250) // glare // TODO: !!!
			{
				iterations /= 2;
				goto restart;				
			}
			
			int d = abs(at(cx,cy).L[channel] - at(sx,sy).L[channel]);
			diff_cache.at(sx,sy) = d;
		}

		return diff_cache.at(sx,sy);
	}

	int AdaptiveFilter::getIntensityBound(const Rectangle& crop, WeakSegmentator* ws)
	{
		logEnterFunction();

		Histogram<256> distHist;
		for (int y = crop.y1(); y < crop.y2(); y++)
			for (int x = crop.x1(); x < crop.x2(); x++)
				if (ws == NULL || 0 == ws->at(x - crop.x1(), y - crop.y1()))
					distHist.addData(getMaximalIntensityDiff(INTENSITY_CHANNEL, x, y, DIFF_ITERATIONS));
		int result = distHist.getValueMoreThan(INK_THRESHOLD);
		getLogExt().append("Intensity diff bound", result);
		return result;
	}

	void AdaptiveFilter::normalizedOuput(Image& img, const WeakSegmentator& ws, const Rectangle& crop)
	{
		logEnterFunction();

		int minv = BLANK, maxv = INK;
		for (int y = 0; y < ws.height(); y++)
			for (int x = 0; x < ws.width(); x++)
			{
				if (ws.at(x, y) > 0)
				{
					unsigned char c = at(crop.x+x,crop.y+y).L[INTENSITY_CHANNEL];
					if (c < minv) minv = c;
					if (c > maxv) maxv = c;
				}
			}

		getLogExt().append("Minimal intensity matches diff", minv);
		getLogExt().append("Maximal intensity matches diff", maxv);

		if (minv < maxv)
		{
			img.clear();
			img.init(ws.width(), ws.height());

			double factor = double(BLANK) / double(maxv - minv);

			for (int y = 0; y < img.getHeight(); y++)
			{
				for (int x = 0; x < img.getWidth(); x++)
				{							
					if (ws.at(x, y) > 0)
					{
						unsigned char c = at(crop.x + x, crop.y + y).L[INTENSITY_CHANNEL];
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
		ImageAdapter(AdaptiveFilter& _rgb, Rectangle& _crop, int _diff_bound)
			: rgb(_rgb), crop(_crop), diff_bound(_diff_bound) { }		
		
		virtual bool isFilled(int x, int y) const		
		{
			return rgb.getMaximalIntensityDiff(INTENSITY_CHANNEL, crop.x + x, crop.y + y, DIFF_ITERATIONS) >= diff_bound;
		}

		virtual unsigned char getIntensity(int x, int y) const
		{
			return rgb.at(crop.x + x, crop.y + y).L[INTENSITY_CHANNEL];
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
		AdaptiveFilter& rgb;
		Rectangle& crop;
		int diff_bound;
	};

	void AdaptiveFilter::filterImage(Image& img)
	{	
		logEnterFunction();	

		getLogExt().appendImage("Source image", img);
		
		Rectangle crop(0, 0, this->width(), this->height());
		AdaptiveFilter interpolated(*this, INTERPOLATION_LEVEL);
		
		// maximal crops allowed loop
		for (int crop_attempt = 0; crop_attempt <= MAX_CROPS; crop_attempt++)
		{
			ImageAdapter img_a(*this, crop, interpolated.getIntensityBound(crop));
			WeakSegmentator ws(img_a);
			int added0 = ws.appendData(img_a, DIFF_ITERATIONS);
			int pixelAddBoundary = added0 / 25;

			if (crop_attempt == MAX_CROPS || !ws.needCrop(crop))
			{
				// refine loop
				for (int refine_iter = 1; refine_iter <= MAX_REFINE_ITERS; refine_iter++)
				{
					if (getLogExt().loggingEnabled())
					{
						Image temp;
						normalizedOuput(temp, ws, crop);
						getLogExt().appendImage("Working image", temp);
					}

					img_a.updateBound(interpolated.getIntensityBound(crop, &ws));
					int added_n = ws.appendData(img_a, DIFF_ITERATIONS);
					if (added_n < ERASE_NOISE_THRESHOLD || added_n < pixelAddBoundary)
					{
						getLogExt().append("Crossed useful refinements boundary on iteration", refine_iter);
						break;
					}
				}

				// ws.eraseNoise(ERASE_NOISE_THRESHOLD); // temporary. function is wrong

				ws.performPixelOptimizations();
				normalizedOuput(img, ws, crop);
				break;
			}
		}
			
		getLogExt().appendImage("Filtered image", img);

		for (int y = 0; y < img.getHeight(); y++)
			for (int x = 0; x < img.getWidth(); x++)
				img.getByte(x, y) = (img.getByte(x, y) != 255) ? 0 : 255;

		getLogExt().appendImage("Binarized image", img);

		double line_thickness = EstimateLineThickness(img);
		getSettings()["LineThickness"] = line_thickness;
		getLogExt().append("Line Thickness", line_thickness);
	}

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
				filterptr->at(scaled_x, scaled_y).L[INTENSITY_CHANNEL] += intensity / sc2;
		}
	}

	void FilterImageStub::initPixel(int x, int y, unsigned char R, unsigned char G, unsigned char B, unsigned char intensity)
	{
		int scaled_x = x / scale;
		int scaled_y = y / scale;
		int sc2 = scale * scale;
		if (intensity == 0)
			intensity = (unsigned char)(((int)R * 299 + (int)G * 587 + (int)B * 114)/1000);
		if (scaled_x < imgptr->getWidth() && scaled_y < imgptr->getHeight())
		{
			imgptr->getByte(scaled_x, scaled_y) += intensity / sc2;
			if (filterptr)
			{
				filterptr->at(scaled_x, scaled_y).L[INTENSITY_CHANNEL] += intensity / sc2;
				filterptr->at(scaled_x, scaled_y).L[R_CHANNEL] = R;
				filterptr->at(scaled_x, scaled_y).L[G_CHANNEL] = G;
				filterptr->at(scaled_x, scaled_y).L[B_CHANNEL] = B;
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
		}
	}
}