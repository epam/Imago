#pragma once

#include "image.h"

namespace imago
{
	struct RGBData
	{
		static const int CHANNELS_COUNT = 4;
		unsigned char L[CHANNELS_COUNT];		
		RGBData(unsigned char R = 0, unsigned char G = 0, unsigned char B = 0, unsigned char I = 0);
	};

	template <class t>
	class Basic2dStorage
	{
	public:
		Basic2dStorage(int width, int height)
		{
			_w = width;
			_h = height;
			data = new t[_w*_h]();
		}

		Basic2dStorage(int width, int height, t value)
		{
			_w = width;
			_h = height;
			data = new t[_w * _h];
			for (int u = 0; u < _w*_h; u++)
				data[u] = value;
		}

		virtual ~Basic2dStorage()
		{
			if (data)
				delete []data;
		}

		const t& at(int x, int y) const
		{
			return data[x + y * _w];
		}

		t& at(int x, int y)
		{
			return data[x + y * _w];
		}

		int width() const { return _w; }
		int height() const { return _h; }

		bool inRange(int x, int y)
		{
			return x >= 0 && y >= 0 && x < _w && y < _h;
		}
	private:
		int _w, _h;
		t* data;
	};

	class RGBStorage : public Basic2dStorage<RGBData>
	{
	public:
		RGBStorage(int w, int h);

		RGBStorage(const RGBStorage& src, int interpolation = 0);

		virtual ~RGBStorage();

		int getMaximalIntensityDiff(int channel, int x, int y, int iterations);

	private:
		Basic2dStorage<unsigned char> diff_cache;
	};

	template <int bins> class Hist
	{
	public:
		Hist()
		{
			for (int i = 0; i < bins; i++)
				data[i] = 0;
			count = 0;
		}

		void addData(int value)
		{
			if (value < 0)
				data[0]++;
			else if (value >= bins)
				data[bins-1]++;
			else
				data[value]++;
			count++;
		}

		int getValueMoreThan(double percents)
		{
			int sum = data[0], value = 0;
			int lim = count*percents;
			if (lim > count)
				lim = count;
			while ((value+1) < bins && sum < lim)
			{
				sum += data[++value];
			}
			return value;
		}

	private:
		int data[bins];
		int count;
	};

	 void RGB_based_init(Image &img, RGBStorage& rgb);
}