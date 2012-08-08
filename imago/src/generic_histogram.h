/****************************************************************************
 * Copyright (C) 2009-2012 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#pragma once
#ifndef _generic_histogram_h
#define _generic_histogram_h

namespace imago
{
	template <int bins> class Histogram
	{
	public:
		Histogram()
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
			double lim = count*percents;
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
}

#endif // _generic_histogram_h
