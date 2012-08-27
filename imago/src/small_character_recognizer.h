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
#ifndef small_character_recognizer_h
#define small_character_recognizer_h

#include <string>
#include <vector>
#include <map>
#include "character_recognizer_data.h"
#include "symbol_features.h"
#include "segment.h"
#include "stl_fwd.h"
#include "recognition_distance.h"
#include "segment_tools.h"
#include "settings.h"

namespace imago
{
	class SmallCharRecognizer
	{
	public:
		SmallCharRecognizer()
		{
			if(_data.empty())
			{
				std::string fontdata;
				const char *_char_tempdata[] = {
					#include "char.templates.inc"
				};
			   for (int i = 0; _char_tempdata[i] != 0; ++i)
				  fontdata += _char_tempdata[i];

			   std::istringstream in(fontdata);
			   _loadData(in);
			}
		}

		char Recognize(const Settings& vars, const Segment *seg);

	private:
		
		struct CharRecord
		{
			char Character;
			IntDeque templates;
		};

		void _loadData( std::istream &in );
		static std::vector<CharRecord> _data;
		IntDeque calc_template(const Segment* seg);
	};
}

#endif // small_character_recognizer.h