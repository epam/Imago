#pragma once

#include <vector>
#include <string>

namespace imago
{
	class ChemicalValidity
	{
	public:
		ChemicalValidity();
		
		double getLabelProbability(const std::string& label);

		std::vector<std::string> getAlternatives(const std::string& label);

	private:
		struct ElementEntry
		{
			std::string name;
			double probability;
			ElementEntry(std::string n, double p = 1.0)
			{
				name = n;
				probability = p;
			}
		};
		typedef std::vector<ElementEntry> ElementTable;

		ElementTable elements;
	};
}