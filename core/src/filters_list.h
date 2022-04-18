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
#ifndef _filters_list_h
#define _filters_list_h

#include <string>
#include <vector>
#include "image.h"
#include "settings.h"

namespace imago
{
	struct FilterEntryDefinition
	{
		typedef bool(*ConditionFunction)(const Image&);
		typedef bool(*FilterFunction)(Settings&, Image&);

		std::string name;
		std::string update_config_string;
		int priority;
		ConditionFunction condition;
		FilterFunction routine;
		
		FilterEntryDefinition(const std::string& _name, int _priority, FilterFunction _f, 
			                  const std::string& _config = "", ConditionFunction _c = NULL);
	};

	class FilterEntries : public std::vector<FilterEntryDefinition>
	{
	public:
		FilterEntries();
	};

	FilterEntries getFiltersList();
}

#endif // _filters_list_h
