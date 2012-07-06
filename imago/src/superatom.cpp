#include "superatom.h"

namespace imago
{
	void Atom::addLabel(const RecognitionDistance& dist)
	{
		labels.push_back(CharacterRecognitionEntry(dist));
	}

	void Atom::addLabel(const char c)
	{
		RecognitionDistance dist;
		dist[c] = 1.0;
		labels.push_back(CharacterRecognitionEntry(dist));
	}

	void Atom::setLabel(const std::string& str)
	{
		labels.clear();
		for (size_t u = 0; u < str.size(); u++)
			addLabel(str[u]);
	}
      
	char Atom::getLabelFirst() const
	{
		if (labels.size() > 0)
			return labels[0].selected_character;
		else
			return 0;
	}

	char Atom::getLabelSecond() const
	{
		if (labels.size() > 1)
			return labels[1].selected_character;
		else
			return 0;
	}
      
    Atom::Atom()
    {
        isotope = count = 0;
        charge = 0;
    }
}