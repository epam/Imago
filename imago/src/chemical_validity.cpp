#include "chemical_validity.h"
#include "comdef.h"
#include "boost/algorithm/string.hpp"

namespace imago
{
	double compare(const std::string& a, const std::string& b)
	{
		double result = 1.0;
		
		if (a.size() < b.size())
		{
			return 0.0;
		}
		
		if (a.size() > b.size())
		{
			for (size_t u = b.size(); u < a.size(); u++)
			{
				if (a[u] == 'I')
					result *= 0.5;
				else
					return 0.0;
			}
		}

		for (size_t u = 0; u < b.size(); u++)
		{
			// TODO: ...
			if (a[u] == b[u])
				;
			else if (toupper(a[u]) == b[u] || tolower(a[u]) == b[u])
				result *= 0.95;
			else if (a[u] == 'G' && b[u] == 'C')
				result *= 0.6;
			else if (a[u] == 'N' && b[u] == 'H')
				result *= 0.6;
			else if (a[u] == 'e' && b[u] == 'l')
				result *= 0.6;
			else if (a[u] == 'H' && b[u] == 'N')
				result *= 0.6;
			else if (a[u] == 'P' && b[u] == 'H')
				result *= 0.4;
			else if (a[u] == 'I' && b[u] == 'H')
				result *= 0.4;
			else if (a[u] == 'L' && b[u] == 'H')
				result *= 0.4;
			else if (a[u] == 'M' && b[u] == 'H')
				result *= 0.4;
			else if (a[u] == 'Y' && b[u] == 'H')
				result *= 0.4;
			else if (a[u] == 'W' || a[u] == 'Q' || a[u] == 'X')
				result *= 0.1;
			else
			{
				return 0.0;
			}
		}
		return result;
	}


	std::vector<std::string> ChemicalValidity::getAlternatives(const std::string& label)
	{
		std::vector<std::string> result;
		std::string result1; 

		for (size_t pos = 0; pos < label.size(); )
		{
			double best_match_pr = 0.0;
			int best_shift = 0;
			std::string best_match = "";
			for (size_t k = 0; k < elements.size(); k++)
			{
				if (pos + elements[k].name.size() <= label.size())
				{
					double pr = compare(label.substr(pos, elements[k].name.size()), elements[k].name)
						* elements[k].probability * elements[k].name.size();
					if (pr > EPS && pr > best_match_pr)
					{
						best_match = elements[k].name;
						best_match_pr = pr;
						best_shift = elements[k].name.size();
					}
				}				
			}
			
			if (best_match.size() > 0)
			{
				pos += best_shift;
				result1 += best_match;
			}
			else
			{
				// no match;
				return result;
			}
		}


		boost::replace_all(result1, "HH", "H");
		boost::replace_all(result1, "CC", "C");
		boost::replace_all(result1, "II", "H");
		boost::replace_all(result1, "OO", "O");
		boost::replace_all(result1, "BN", "N");

		result.push_back(result1);
		return result;
	}

	double ChemicalValidity::getLabelProbability(const std::string& label)
	{
		double pr = 1.0;
		for (size_t pos = 0; pos < label.size(); )
		{
			double best_match_pr = 0.0;
			std::string best_match = "";
			for (size_t k = 0; k < elements.size(); k++)
			{
				if (elements[k].name.size() > best_match.size() 
					&& pos + elements[k].name.size() <= label.size()
					&& label.substr(pos, elements[k].name.size()) == elements[k].name)
				{
					best_match = elements[k].name;
					best_match_pr = elements[k].probability;
				}
			}
			pr *= best_match_pr;
			if (best_match.size() > 0)
				pos += best_match.size();
			else
				pos++;
		}
		return pr;
	}

	ChemicalValidity::ChemicalValidity()
	{
		elements.push_back(ElementEntry("CH",  1.0));
		elements.push_back(ElementEntry("OH",  1.0));

		elements.push_back(ElementEntry("H",  1.0));
		elements.push_back(ElementEntry("C",  1.0));
		elements.push_back(ElementEntry("N",  1.0));
		elements.push_back(ElementEntry("Li", 1.0));
		elements.push_back(ElementEntry("Cl", 1.0));
		elements.push_back(ElementEntry("O",  1.0));

		elements.push_back(ElementEntry("P",  0.9));
		elements.push_back(ElementEntry("F",  0.9));

		elements.push_back(ElementEntry("K",  0.8));
		elements.push_back(ElementEntry("He", 0.8));		
		elements.push_back(ElementEntry("S",  0.8));
		elements.push_back(ElementEntry("Na", 0.8));
		elements.push_back(ElementEntry("Ca", 0.8));
		elements.push_back(ElementEntry("Fe", 0.8));

		elements.push_back(ElementEntry("OTf",   0.7));
		elements.push_back(ElementEntry("TfO",   0.7));
		elements.push_back(ElementEntry("Ph",    0.7));
		elements.push_back(ElementEntry("AcO",   0.7));
		elements.push_back(ElementEntry("oAc",   0.7));
		elements.push_back(ElementEntry("OAc",   0.7));
		elements.push_back(ElementEntry("NHBoc", 0.7));
		elements.push_back(ElementEntry("NHBOC", 0.7));

		elements.push_back(ElementEntry("Be", 0.6));
		elements.push_back(ElementEntry("B",  0.6));		
		elements.push_back(ElementEntry("Ne", 0.6));		
		elements.push_back(ElementEntry("Mg", 0.6));
		elements.push_back(ElementEntry("Al", 0.6));
		elements.push_back(ElementEntry("Si", 0.6));		
		elements.push_back(ElementEntry("Ar", 0.6));		
		elements.push_back(ElementEntry("Ti", 0.6));
		
		elements.push_back(ElementEntry("Sc", 0.1));		
		elements.push_back(ElementEntry("V",  0.1));
		elements.push_back(ElementEntry("Cr", 0.1));
		elements.push_back(ElementEntry("Mn", 0.1));		
		elements.push_back(ElementEntry("Co", 0.1));
		elements.push_back(ElementEntry("Ni", 0.1));
		elements.push_back(ElementEntry("Cu", 0.1));
		elements.push_back(ElementEntry("Zn", 0.1));
		elements.push_back(ElementEntry("Ga", 0.1));
		elements.push_back(ElementEntry("Ge", 0.1));
		elements.push_back(ElementEntry("As", 0.1));
		elements.push_back(ElementEntry("Se", 0.1));
		elements.push_back(ElementEntry("Br", 0.1));
		elements.push_back(ElementEntry("Kr", 0.1));
		elements.push_back(ElementEntry("Ag", 0.1));
		elements.push_back(ElementEntry("Cd", 0.1));
		elements.push_back(ElementEntry("In", 0.1));
		elements.push_back(ElementEntry("Sn", 0.1));
		elements.push_back(ElementEntry("Sb", 0.1));
		elements.push_back(ElementEntry("Te", 0.1));
		elements.push_back(ElementEntry("J",  0.1));

		elements.push_back(ElementEntry("Xe", 0.01));
		elements.push_back(ElementEntry("Cs", 0.01));
		elements.push_back(ElementEntry("Ba", 0.01));
		elements.push_back(ElementEntry("La", 0.01));
		elements.push_back(ElementEntry("Hf", 0.01));
		elements.push_back(ElementEntry("Ta", 0.01));
		elements.push_back(ElementEntry("W",  0.01));
		elements.push_back(ElementEntry("Re", 0.01));
		elements.push_back(ElementEntry("Em", 0.01));
	}
};