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

#include "character_endpoints.h"
#include "log_ext.h"
#include "segment_tools.h"

namespace imago
{
	EndpointsRecord::EndpointsRecord(char _c, int _min, int _max)
		{
			c = _c;
			min = _min;
			max = _max;
		};

	EndpointsData::EndpointsData()
	{
		push_back(EndpointsRecord('0', 0, 2));
		push_back(EndpointsRecord('1', 1, 3));
		push_back(EndpointsRecord('2', 2, 3));
		push_back(EndpointsRecord('3', 2, 4));
		push_back(EndpointsRecord('4', 2, 4));
		push_back(EndpointsRecord('5', 2, 4));
		push_back(EndpointsRecord('6', 1, 2));
		push_back(EndpointsRecord('7', 2, 4));
		push_back(EndpointsRecord('8', 0, 2));
		push_back(EndpointsRecord('9', 1, 2));

		push_back(EndpointsRecord('A', 2, 4));
		push_back(EndpointsRecord('B', 0, 4));
		push_back(EndpointsRecord('C', 2, 2));
		push_back(EndpointsRecord('D', 0, 4));
		push_back(EndpointsRecord('E', 3, 6));
		push_back(EndpointsRecord('F', 3, 5));
		push_back(EndpointsRecord('G', 2, 3));
		push_back(EndpointsRecord('H', 4, 6));
		push_back(EndpointsRecord('I', 2, 6));
		push_back(EndpointsRecord('J', 2, 4));
		push_back(EndpointsRecord('K', 4, 6));
		push_back(EndpointsRecord('L', 2, 4));
		push_back(EndpointsRecord('M', 2, 6));
		push_back(EndpointsRecord('N', 2, 4));
		push_back(EndpointsRecord('O', 0, 2));
		push_back(EndpointsRecord('P', 1, 4));
		push_back(EndpointsRecord('Q', 2, 4));
		push_back(EndpointsRecord('R', 2, 4));
		push_back(EndpointsRecord('S', 2, 2));
		push_back(EndpointsRecord('T', 2, 4));
		push_back(EndpointsRecord('U', 2, 3));
		push_back(EndpointsRecord('V', 2, 3));
		push_back(EndpointsRecord('W', 2, 4));
		push_back(EndpointsRecord('X', 4, 4));
		push_back(EndpointsRecord('Y', 3, 4));
		push_back(EndpointsRecord('Z', 2, 4));

		push_back(EndpointsRecord('a', 1, 2));
		push_back(EndpointsRecord('b', 0, 2));
		push_back(EndpointsRecord('c', 2, 2));
		push_back(EndpointsRecord('d', 2, 4));
		push_back(EndpointsRecord('e', 1, 2));
		push_back(EndpointsRecord('f', 3, 4));
		push_back(EndpointsRecord('g', 1, 2));
		push_back(EndpointsRecord('h', 2, 4));
		push_back(EndpointsRecord('i', 2, 2));
		push_back(EndpointsRecord('j', 2, 2));
		push_back(EndpointsRecord('k', 2, 4));
		push_back(EndpointsRecord('l', 1, 2));
		push_back(EndpointsRecord('m', 2, 6));
		push_back(EndpointsRecord('n', 2, 4));
		push_back(EndpointsRecord('o', 0, 2));
		push_back(EndpointsRecord('p', 1, 3));
		push_back(EndpointsRecord('q', 1, 2));
		push_back(EndpointsRecord('r', 2, 2));
		push_back(EndpointsRecord('s', 2, 2));
		push_back(EndpointsRecord('t', 3, 4));
		push_back(EndpointsRecord('u', 2, 3));
		push_back(EndpointsRecord('v', 2, 3));
		push_back(EndpointsRecord('w', 2, 4));
		push_back(EndpointsRecord('x', 4, 4));
		push_back(EndpointsRecord('y', 2, 4));
		push_back(EndpointsRecord('z', 2, 5));
	}

	void EndpointsData::getImpossibleToWrite(const Settings& vars, int endpoints_count, std::string& probably, std::string& surely) const
	{
		probably = "";
		surely = "";
		for (size_t u = 0; u < size(); u++)
		{
			if (vars.characters.HackFor3Use && endpoints_count == 3 && at(u).min > 3)
				surely.push_back( at(u).c );
			else if (endpoints_count < at(u).min - vars.characters.ImpossibleToWriteDelta || 
				     endpoints_count > at(u).max + vars.characters.ImpossibleToWriteDelta)
				surely.push_back( at(u).c );
			else if (endpoints_count < at(u).min || endpoints_count > at(u).max )
				probably.push_back ( at(u).c );
		}
	}

	bool EndpointsData::adjustByEndpointsInfo(const Settings& vars, const Segment& seg, RecognitionDistance& rec)
	{
		logEnterFunction();

		bool result = false;

		Points2i endpoints = SegmentTools::getEndpoints(seg);
		SegmentTools::logEndpoints(seg, endpoints);

		std::string probably, surely;
		static EndpointsData endpointsHandler;

		if ((int)endpoints.size() <= vars.characters.MaximalEndpointsUse)
		{
			endpointsHandler.getImpossibleToWrite(vars, endpoints.size(), probably, surely);
			rec.adjust(vars.characters.WriteProbablyImpossibleFactor, probably);
			rec.adjust(vars.characters.WriteSurelyImpossibleFactor, surely);
			result = true;
		}
	
		// easy-to-write adjust
		switch(endpoints.size())
		{
		case 0:
			rec.adjust(vars.characters.WriteVeryEasyFactor, "0oO");
			result = true;
			break;
		case 1:
			rec.adjust(vars.characters.WriteEasyFactor, "Ppe");
			result = true;
			break;
		case 2:
			rec.adjust(vars.characters.WriteEasyFactor, "ILNSsZz");
			result = true;
			break;
		case 3:
			rec.adjust(vars.characters.WriteVeryEasyFactor, "3");
			rec.adjust(vars.characters.WriteEasyFactor, "F");
			result = true;
			break;
		case 4:
			rec.adjust(vars.characters.WriteEasyFactor, "fHK");
			result = true;
			break;
		case 6:
			rec.adjust(vars.characters.WriteEasyFactor, "^");
			result = true;
			break;
		};

		return result;
	}
}
