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
#ifndef _character_endpoints_h
#define _character_endpoints_h

#include <vector>
#include <string>
#include "stl_fwd.h"
#include "settings.h"
#include "segment.h"
#include "recognition_distance.h"

namespace imago
{
	struct EndpointsRecord
	{
		char c;
		int min, max;
		EndpointsRecord(char _c, int _min, int _max);
	};

	class EndpointsData : public std::vector<EndpointsRecord>
	{
	public:
		EndpointsData();
				
		bool adjustByEndpointsInfo(const Settings& vars, const Segment& seg, RecognitionDistance& rec);

	protected:
		void getImpossibleToWrite(const Settings& vars, int endpointsCount, std::string& probably, std::string& surely) const;
	};
}

#endif //_character_endpoints_h
