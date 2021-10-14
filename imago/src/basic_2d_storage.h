/****************************************************************************
* Copyright (C) from 2009 to Present EPAM Systems.
*
* This file is part of Imago toolkit.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***************************************************************************/

#pragma once
#ifndef _basic_2d_storage_h
#define _basic_2d_storage_h

namespace imago
{
	// two-dimensional storage for specified type data
	template <class t> class Basic2dStorage
	{
	public:
		// initialize dimensions and data pointer, fill with zero, fast
		Basic2dStorage(int width, int height)
		{
			_w = width;
			_h = height;
			data = new t[_w*_h]();
		}

		// initialize dimensions and data pointer, fill with 'value'
		Basic2dStorage(int width, int height, t value)
		{
			_w = width;
			_h = height;
			data = new t[_w * _h];
			for (int u = 0; u < _w*_h; u++)
				data[u] = value;
		}

		// delete data pointer
		virtual ~Basic2dStorage()
		{
			if (data)
				delete []data;
		}

		// index operator
		const t& at(int x, int y) const
		{
			return data[x + y * _w];
		}

		// index operator
		t& at(int x, int y)
		{
			return data[x + y * _w];
		}

		// dimensions getters
		int width() const { return _w; }
		int height() const { return _h; }

		// return true if point (x,y) fits in storage
		bool inRange(int x, int y) const
		{
			return x >= 0 && y >= 0 && x < _w && y < _h;
		}

	private:
		int _w, _h;
		t* data;
	};
}

#endif
