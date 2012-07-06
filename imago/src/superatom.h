/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
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
		CharactersRecognitionGroup labels;	   

		void addLabel(const RecognitionDistance& dist);
		void addLabel(const char c);

		void setLabel(const std::string& str);
      
		char getLabelFirst() const;
		char getLabelSecond() const;

		int charge;
		int isotope;
		int count;
      
		Atom();
	};

	struct Superatom
	{
		std::vector<Atom> atoms;
	};
}


#endif	/* _superatom_h */

