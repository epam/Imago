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
#ifndef _chemical_validity_h
#define _chemical_validity_h

#include <vector>
#include <string>
#include <map>
#include "superatom.h"

namespace imago
{
	class ChemicalValidity
	{
	public:
		// fills internal elements table
		ChemicalValidity();
		
		// returns probability of superatom existence
		double getLabelProbability(const Superatom& sa) const;

		// updates the non-existent atom to the most close existent alternative
		void updateAlternative(Superatom& sa) const;

	private:
		typedef std::vector<std::string> Strings;
		typedef std::map<std::string, double> Probabilities;

		struct ElementTableEntry
		{
			Strings names;
			Probabilities probability;

			// helper function to initialize both names and probability 
			void push_back(const std::string& name, double prob = 1.0);
		};
	
		ElementTableEntry elements;
		std::map<std::string, Superatom> hacks;

	protected:
		// returns optimal string split by specified dictionary
		static Strings optimalSplit(const std::string& input, const Strings& dictionary);

		// calculates split probability against the 'elements' information
		double calcSplitProbability(const Strings& split) const;

		// returns if atom (short form, one atom) is probable
		bool isProbable(const std::string& atom) const;

		// returns list of alternative characters
		std::string getAlternatives(char base_char, const RecognitionDistance& d) const;

		typedef std::vector<Atom*> AtomRefs;
		// subtask of the updateAlternative function
		bool optimizeAtomGroup(AtomRefs& data) const;
	};
}

#endif
