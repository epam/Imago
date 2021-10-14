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
#ifndef _superatom_h
#define _superatom_h

#include <vector>
#include <string>
#include "vec2d.h"
#include "recognition_tree.h"

namespace imago
{
	struct Atom
	{
		// list of used characters with their probabilities
		CharactersRecognitionGroup labels;	   

		// adds a character to atom label by probability table
		void addLabel(const RecognitionDistance& dist);

		// adds a character to atom label by exact value
		void addLabel(const char c);

		// sets the whole label by specified string
		void setLabel(const std::string& str);
      
		// returns first label char (the most probable: selected_character) or NULL (if none specified)
		char getLabelFirst() const;

		// returns second label char (the most probable: selected_character) or NULL (if none specified)
		char getLabelSecond() const;

		// chemical configuration
		int charge, isotope, count;

		// returns printable form of the atom's content
		// expanded - use chemical configuration too
		std::string getPrintableForm(bool expanded = true) const;
		      
		Atom();
	};

	struct Superatom
	{
		// list of used atoms in order
		std::vector<Atom> atoms;

		// returns printable form of the whole molecule content
		// apply 'expanded' rule to all subatoms
		std::string getPrintableForm(bool expanded = true) const;

		Superatom() {};

		// some useful constructors to create superatom from atoms fast
		Superatom(const Atom& a1);
		Superatom(const Atom& a1, const Atom& a2);
		Superatom(const Atom& a1, const Atom& a2, const Atom& a3);
	};
}


#endif	/* _superatom_h */
