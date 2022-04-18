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
#ifndef _virtual_fs_h
#define _virtual_fs_h

#include <string>
#include <vector>

namespace imago
{
	struct VirtualFSRecord
	{
		std::string filename;
		std::vector<unsigned char> data;
	};

	class VirtualFS : public std::vector<VirtualFSRecord>
	{
	public:
		bool createNewFile(const std::string& filename, const std::string& data);
		bool appendData(const std::string& filename, const std::string& data);		
		
		// gets internal data to external storage
		void getData(std::vector<char>& output) const;

		// sets internal state by specified input
		void setData(std::vector<char>& input);
		
		// if non-empty, the trailing slash is required
		void storeOnDisk(const std::string& folder = "") const;
	};
};

#endif //_virtual_fs_h
