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

#ifndef _file_helpers_h_
#define _file_helpers_h_

#include <string>
#include <vector>

typedef std::vector<std::string> strings;

namespace file_helpers
{
	size_t getLastSlashPos(const std::string& filename);
	bool getReferenceFileName(const std::string& image, std::string& output);
	bool getOnlyFileName(const std::string& image, std::string& output);
	int  getDirectoryContent(const std::string& dir, strings &files, bool recursive);
	bool isSupportedImageType(const std::string& filename);
	void filterOnlyImages(strings& files);
}

#endif // _file_helpers_h_
