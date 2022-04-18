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

	std::string Atom::getPrintableForm(bool expanded) const
	{
		const Atom& a = *this;

		std::string molecule;

		if (a.getLabelFirst() != 0) 
			molecule.push_back(a.getLabelFirst());

		if (a.getLabelSecond() != 0) 
			molecule.push_back(a.getLabelSecond());

		if ((a.getLabelFirst() == 'R' || a.getLabelFirst() == 'Z') && a.getLabelSecond() == 0)
		{
			if (a.charge > 0)
			{
				char buffer[32];
				sprintf(buffer, "%i", a.charge);
				molecule += buffer;
			}
		}
		else
		{
			if (expanded && a.charge != 0)
			{
				char buffer[32];
				if (a.charge < 0)
					sprintf(buffer, "%i", a.charge);
				else
					sprintf(buffer, "+%i", a.charge);
				molecule += buffer;
			}					
		}
		if (expanded && a.count != 0)
		{
			char buffer[32];
			sprintf(buffer, "x%i", a.count);
			molecule += buffer;
		}
		if (expanded && a.isotope != 0)
		{
			char buffer[32];
			sprintf(buffer, "{isotope:%i}", a.isotope);
			molecule += buffer;
		}
		return molecule;
	}

	std::string Superatom::getPrintableForm(bool expanded) const
	{
		std::string molecule;
		for (size_t i = 0; i < atoms.size(); i++)
		{
			molecule += atoms[i].getPrintableForm(expanded);
		};
		return molecule;
	}

	Superatom::Superatom(const Atom& a1)
	{
		atoms.push_back(a1);
	}

	Superatom::Superatom(const Atom& a1, const Atom& a2)
	{
		atoms.push_back(a1);
		atoms.push_back(a2);
	}

	Superatom::Superatom(const Atom& a1, const Atom& a2, const Atom& a3)
	{
		atoms.push_back(a1);
		atoms.push_back(a2);
		atoms.push_back(a3);
	}
}