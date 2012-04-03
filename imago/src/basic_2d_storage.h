#pragma once

namespace imago
{
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

		bool inRange(int x, int y) const
		{
			return x >= 0 && y >= 0 && x < _w && y < _h;
		}
	private:
		int _w, _h;
		t* data;
	};
}
