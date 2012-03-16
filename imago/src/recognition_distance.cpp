#include "recognition_distance.h"
#include <algorithm>
#include "log_ext.h"

namespace imago
{

	void RecognitionDistance::mergeTables(const RecognitionDistance& second)
	{
		for (RecognitionDistance::const_iterator it = second.begin(); it != second.end(); it++)
		{
			if (this->find(it->first) == this->end())
				(*this)[it->first] = it->second;
			else
			{
				(*this)[it->first] = std::min((*this)[it->first], it->second);
			}
		}
	}

	void RecognitionDistance::adjust(double factor, const std::string& sym_set)
	{
		//logEnterFunction();
		getLogExt().append("Distance map adjust for " + sym_set, factor);
		for (size_t u = 0; u < sym_set.size(); u++)
			if (this->find(sym_set[u]) != this->end())
				(*this)[sym_set[u]] *= factor;
	}

	void RecognitionDistance::fillVector(PrVec &out) const
	{
		for (RecognitionDistance::const_iterator it = this->begin(); it != this->end(); it++)
			out.push_back(std::make_pair(it->first, it->second));
	}

	double RecognitionDistance::getQuality() const
	{
		double result = 0.0;
	
		PrVec temp;
		fillVector(temp);

		if (!temp.empty())
		{
			// TODO: really need only 2 max elements that can be done O(n)
			std::sort(temp.begin(), temp.end(), sortCompareFunction);

			result = 1.0; // ? temp[0].second;

			if (temp.size() > 1)
				result = temp[1].second - temp[0].second;
		}

		return result;
	}

	std::string RecognitionDistance::getRangedBest(double max_diff) const
	{
		std::string result;
	
		PrVec temp;
		fillVector(temp);	
	
		if (!temp.empty())
		{
			std::sort(temp.begin(), temp.end(), sortCompareFunction);
			result = temp[0].first;
			for (size_t u = 1; u < temp.size(); u++)
				if (temp[u].second < temp[0].second + max_diff)
					result += temp[u].first;
		}

		return result;
	}

	char RecognitionDistance::getBest(double* dist) const
	{
		double d = DBL_MAX;
		char result = 0;
		for (RecognitionDistance::const_iterator it = this->begin(); it != this->end(); it++)
		{
			if (it->second < d)
			{
				d = it->second;
				result = it->first;
			}
		}
		if (dist != NULL)
			*dist = d;
		return result;
	}
}
