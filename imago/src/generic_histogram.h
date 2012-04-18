#pragma once

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
