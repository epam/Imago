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
#ifndef _recognition_tree_h
#define _recognition_tree_h

#include "recognition_distance.h"
#include <vector>

namespace imago
{	
	class CharacterRecognitionEntry
	{
	public:
		char selected_character;
		RecognitionDistance alternatives;

		CharacterRecognitionEntry(const RecognitionDistance& src);
	};

	class CharactersRecognitionGroup : public std::vector<CharacterRecognitionEntry>
	{
	};
}

#endif // _recognition_tree_h
