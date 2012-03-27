#include "RGBInit.h"
#include "log_ext.h"
#include <queue>

namespace imago
{
	const int    INK = 0;                      // preferred intensity means filled
	const int    BLANK = 255;                  // intensity means blank
	const int    MAX_IMAGE_DIM = 4096;         // maximal resolution in pixels for longes side

	const int    COLOR_CHANNEL = 3;            // intensity channel		
	const double INK_THRESHOLD = 0.995;	       // % for initial ink coverage
	const int    INTERPOLATION_LEVEL = 3;      // (2*n+1)^2 kernel for mean filter will be used

	const int    DIFF_STEP_RANGE = 2;          // one step pixels count
	const int    DIFF_ITERATIONS = 4;          // max steps count

	const int    ERASE_NOISE_THRESHOLD = 32;   // pixels count, less that will be erased as noise

	const double AREA_THRESHOLD_FACTOR = 0.30; // %, minimal rectangle coverage of image
	const int    RECTANGULAR_WINDOWSIZE = 8;   // maximal rectangle side width
	const double RECTANGULAR_THRESHOLD = 0.95; // %, for rectange testing


	RGBData::RGBData(unsigned char r, unsigned char g, unsigned char b, unsigned char I)
	{
		L[0] = r;
		L[1] = g;
		L[2] = b;
		L[3] = I;
	}

	RGBStorage::RGBStorage(int w, int h) : Basic2dStorage<RGBData>(w, h), diff_cache(w, h, BLANK)
	{
	}

	RGBStorage::RGBStorage(const RGBStorage& src, int interpolation) 
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

	RGBStorage::~RGBStorage()
	{
	}

	int RGBStorage::getMaximalIntensityDiff(int channel, int sx, int sy, int iterations)
	{		
		if (diff_cache.at(sx,sy) == BLANK)
		{
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

			int d = abs(at(cx,cy).L[channel] - at(sx,sy).L[channel]);
			diff_cache.at(sx,sy) = d;
		}

		return diff_cache.at(sx,sy);
	}

	class ImageInterface
	{
	public:
		virtual bool isFilled(int x, int y) const = 0;
		virtual int width() const = 0;
		virtual int height() const = 0;
	};

	class WeakSegmentator : public Basic2dStorage<int>
	{
	public:
		WeakSegmentator(const ImageInterface &img, int lookup_range) 
			: Basic2dStorage<int>(img.width(), img.height(), 0)
		{	
			logEnterFunction();

			int id = 1;
			for (int y = 0; y < height(); y++)
				for (int x = 0; x < width(); x++)
					if (at(x,y) == 0 && img.isFilled(x,y))
						fill(img, id++, x, y, lookup_range);

			getLogExt().append("Segments count", SegmentPoints.size());			
		}

		~WeakSegmentator()
		{			
		}

		void performPixelOptimizations()
		{
			logEnterFunction();

			for (int y = 0; y < height(); y++)
				for (int x = 0; x < width(); x++)
				{
					int count = 0, id = 0;
					for (int dy = -1; dy <= 1; dy++)
						for (int dx = -1; dx <= 1; dx++)
							if ((dx != 0 || dy != 0) && inRange(x+dx, y+dy))
							{
								if (at(x+dx,y+dy) != 0)
								{
									id = at(x+dx,y+dy);
									count++;
								}
							}
					if (at(x,y) != 0 && count == 0) // erase lonely pixel
						at(x,y) = 0;
					else if (at(x,y) == 0 && count >= 7) // fill inside pixels group
						at(x,y) = id;
				}
		}

		void eraseNoise(int threshold)
		{
			logEnterFunction();

			for (int y = 0; y < height(); y++)
				for (int x = 0; x < width(); x++)
				{
					int v = at(x, y);
					if (v > 0 && (int)SegmentPoints[v].size() < threshold)
					{
						SegmentPoints[v].clear();
						at(x,y) = 0;
					}
				}			
		}

		bool needCrop(Rectangle& crop)
		{
			logEnterFunction();

			int area_threshold = width() * height() * AREA_THRESHOLD_FACTOR;
			for (size_t u = 0; u < SegmentPoints.size(); u++)
			{
				Rectangle bounds;
				if (getArea(u) > area_threshold 
					&& hasRectangularStructure(u, RECTANGULAR_WINDOWSIZE, RECTANGULAR_THRESHOLD, bounds))
				{
					getLogExt().append("Has rectangular structure, id", u);	
					bounds.adjustBorder(DIFF_ITERATIONS*2 + RECTANGULAR_WINDOWSIZE*2);
					crop = bounds;
					return true;
				}
			}
			return false;
		}

	protected:
		// only rectangular check
		int getArea(int id)
		{
			Points2i& p = SegmentPoints[id];
			int min_x = width(), max_x = 0, min_y = height(), max_y = 0;
			for (Points2i::iterator it = p.begin(); it != p.end(); it++)
			{
				min_x = std::min(min_x, it->x);
				min_y = std::min(min_y, it->y);
				max_x = std::max(max_x, it->x);
				max_y = std::max(max_y, it->y);
			}
			return (max_x - min_x) * (max_y - min_y);
		}

		void getAllBounds(Rectangle& bound)
		{
			int min_x = width(), max_x = 0, min_y = height(), max_y = 0;
			for (std::map<int, Points2i>::iterator it = SegmentPoints.begin(); it != SegmentPoints.end(); it++)
			{
				Points2i& p = it->second;			
				for (Points2i::iterator it = p.begin(); it != p.end(); it++)
				{
					min_x = std::min(min_x, it->x);
					min_y = std::min(min_y, it->y);
					max_x = std::max(max_x, it->x);
					max_y = std::max(max_y, it->y);
				}
			}
			bound = Rectangle(min_x, min_y, max_x, max_y, 0);
		}

		bool hasRectangularStructure(int id, int window_size, double threshold, Rectangle& bound)
		{
			Points2i& p = SegmentPoints[id];
			
			if (p.empty())
				return false;

			int map_x[MAX_IMAGE_DIM] = {0};
			int map_y[MAX_IMAGE_DIM] = {0};
			for (Points2i::iterator it = p.begin(); it != p.end(); it++)
			{
				map_x[it->x]++;
				map_y[it->y]++;
			}

			double x1c, x2c, y1c, y2c;
			bool result = get2centers(map_x, width(), x1c, x2c) && get2centers(map_y, height(), y1c, y2c);			
			
			if (result)
			{
				int map_x[MAX_IMAGE_DIM] = {0};
				int map_y[MAX_IMAGE_DIM] = {0};
				// now update maps
				for (Points2i::iterator it = p.begin(); it != p.end(); it++)
				{
					if (it->y > y1c && it->y < y2c) map_x[it->x]++;
					if (it->x > x1c && it->x < x2c) map_y[it->y]++;
				}
				// and centers
				result = get2centers(map_x, width(), x1c, x2c) && get2centers(map_y, height(), y1c, y2c);			
			}

			if (result)
			{
				if (fabs(x1c - x2c) < 2*window_size || fabs(y1c - y2c) < 2*window_size)
					result = false;
				else
				{
					int good = 0, bad = 0;
					for (Points2i::iterator it = p.begin(); it != p.end(); it++)
						if ((fabs(it->x - x1c) < window_size || fabs(it->x - x2c) < window_size) ||
							(fabs(it->y - y1c) < window_size || fabs(it->y - y2c) < window_size))
							good++;
						else
							bad++;
					result = (double)good / (good+bad) > threshold;
				}
			}

			if (result)
			{
				bound = Rectangle(x1c, y1c, x2c, y2c, 0);
			}

			/*if (result && getLogExt().loggingEnabled())
			{
				Image temp(width(), height());
				for (Points2i::iterator it = p.begin(); it != p.end(); it++)
					temp.getByte(it->x, it->y) = 0;
				ImageDrawUtils::putCircle(temp, x1c,y1c, window_size,0);
				ImageDrawUtils::putCircle(temp, x2c,y1c, window_size,0);
				ImageDrawUtils::putCircle(temp, x1c,y2c, window_size,0);
				ImageDrawUtils::putCircle(temp, x2c,y2c, window_size,0);
				getLogExt().appendImage("points", temp);
			}*/

			return result;
		}

		std::map<int, Points2i> SegmentPoints;

	private:
		void fill(const ImageInterface &img, int id, int sx, int sy, int lookup_range)
		{
			typedef std::queue<Vec2i> WorkVector;
			WorkVector v;
			v.push(Vec2i(sx,sy));

			while (!v.empty())
			{
				Vec2i cur = v.front();
				v.pop();

				if (at(cur.x,cur.y) == 0)
				{
					at(cur.x,cur.y) = id;
					SegmentPoints[id].push_back(cur);
					for (int dx = -lookup_range; dx <= lookup_range; dx++)
						for (int dy = -lookup_range; dy <= lookup_range; dy++)
						{
							Vec2i t(cur.x+dx,cur.y+dy);
							if ((dx != 0 || dy != 0) && inRange(t.x, t.y) 
								&& at(t.x, t.y) == 0 && img.isFilled(t.x, t.y))
							{
								// TODO: !!!fixup hack:
								// -- connectivity maker code
								if (at(cur.x + dx/2, cur.y + dy/2) == 0)
									at(cur.x + dx/2, cur.y + dy/2) = id;
								// end hack
								v.push(t);
							}
						}
				}
			}
		}

		static bool get2centers(int* data, int size, double &c1, double& c2) // c1 < c2
		{
			double average = 0.0, count = 0.0;
			for (int u = 0; u < size; u++)
			{
				average += u * data[u];
				count += data[u];
			}			
			
			if (count < 1)
				return false;

			average /= count;
			c1 = 0.0;
			c2 = 0.0;
			double count1 = 0.0;
			double count2 = 0.0;

			for (int u = 0; u < size; u++)
			{
				if (u < average)
				{
					c1 += u * data[u];
					count1 += data[u];
				}
				else
				{
					c2 += u * data[u];
					count2 += data[u];
				}
			}

			if (count1 < 1 || count2 < 1)
				return false;

			c1 /= count1;
			c2 /= count2;
			return true;
		}
	};

	int getIntensityBound(RGBStorage& data, const Rectangle& crop)
	{
		logEnterFunction();

		Hist<256> distHist;
		for (int y = crop.y1(); y < crop.y2(); y++)
			for (int x = crop.x1(); x < crop.x2(); x++)
				distHist.addData(data.getMaximalIntensityDiff(COLOR_CHANNEL, x, y, DIFF_ITERATIONS));
		int result = distHist.getValueMoreThan(INK_THRESHOLD);
		getLogExt().append("Intensity diff bound", result);
		return result;
	}

	void normalizeOuput(Image& img, const WeakSegmentator& ws, const RGBStorage& rgb, const Rectangle& crop)
	{
		logEnterFunction();

		int minv = 255, maxv = 0;
		for (int y = 0; y < ws.height(); y++)
			for (int x = 0; x < ws.width(); x++)
			{
				if (ws.at(x, y) > 0)
				{
					unsigned char c = rgb.at(crop.x+x,crop.y+y).L[COLOR_CHANNEL];
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

			double factor = 255.0 / (maxv - minv);

			for (int y = 0; y < img.getHeight(); y++)
			{
				for (int x = 0; x < img.getWidth(); x++)
				{							
					if (ws.at(x, y) > 0)
					{
						unsigned char c = rgb.at(crop.x + x, crop.y + y).L[COLOR_CHANNEL];
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
		ImageAdapter(RGBStorage& _rgb, Rectangle& _crop, int _diff_bound)
			: rgb(_rgb), crop(_crop), diff_bound(_diff_bound) { }		
		
		virtual bool isFilled(int x, int y) const		
		{
			return rgb.getMaximalIntensityDiff(COLOR_CHANNEL, crop.x + x, crop.y + y, DIFF_ITERATIONS) >= diff_bound;
		}

		virtual int width() const
		{
			return crop.width;
		}

		virtual int height() const
		{
			return crop.height;
		}
	private:
		RGBStorage& rgb;
		Rectangle& crop;
		int diff_bound;
	};

	void RGB_based_init(Image &img, RGBStorage& rgb)
	{	
		logEnterFunction();	
		getLogExt().appendImage("Source image", img);
		
		Rectangle crop(0, 0, rgb.width(), rgb.height());
		RGBStorage interpolated(rgb, INTERPOLATION_LEVEL);
		
		while(true)
		{
			int bound = getIntensityBound(interpolated, crop);						
			WeakSegmentator ws(ImageAdapter(rgb, crop, bound), DIFF_ITERATIONS);					
			ws.eraseNoise(ERASE_NOISE_THRESHOLD);
			if (!ws.needCrop(crop))
			{
				ws.performPixelOptimizations();
				normalizeOuput(img, ws, rgb, crop);				
				break;
			}
		}
			
		getLogExt().appendImage("Filtered image", img);
	}
}