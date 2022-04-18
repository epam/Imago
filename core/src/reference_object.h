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
#ifndef _reference_object_h
#define _reference_object_h

#include <map>
#include <string>

namespace imago
{
	class DataTypeReference
	{
	public:
		enum ObjectType
		{
			otUndef,
			otBool,
			otInt,
			otDouble
		};

		DataTypeReference() : b_value(NULL)
		{
			type = otUndef;
		}

		explicit DataTypeReference(bool& value) : b_value(&value)
		{
			type = otBool;
		}

		explicit DataTypeReference(int& value) : i_value(&value)
		{
			type = otInt;
		}

		explicit DataTypeReference(double& value) : d_value(&value)
		{
			type = otDouble;			
		}

		ObjectType getType() const
		{
			return type;
		}

		bool* getBool() const
		{
			return b_value;
		}

		int* getInt() const
		{
			return i_value;
		}

		double* getDouble() const
		{
			return d_value;
		}

	private:
		union
		{
			bool* b_value;
			int* i_value;
			double* d_value;
		};
		ObjectType type;
	};

	typedef std::map<std::string, DataTypeReference> ReferenceAssignmentMap;
}

#endif // _reference_object_h
