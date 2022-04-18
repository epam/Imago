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

#include <string>

namespace platform
{
    // returns error code
    int MKDIR(const std::string& directory);

    // current time ticks in milliseconds
    unsigned int TICKS();

    // current available memory in kilobytes
    unsigned int MEM_AVAIL();

    // platform-depent line ending string
    std::string getLineEndings();

    // returns 'return-code' or negative error code
    int CALL(const std::string& executable, const std::string& parameters, int timelimit = 0);

    // returns true if memory allocation of 'amount' MB is failed. memory is released instantly.
    bool checkMemoryFail(int amount = 32);
}
