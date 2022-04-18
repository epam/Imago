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

#include "image.h"
#include "settings.h"
#include "virtual_fs.h"

namespace recognition_helpers
{
    void dumpVFS(imago::VirtualFS& vfs, const std::string& filename);
    void applyConfig(bool verbose, imago::Settings& vars, const std::string& config);

    struct RecognitionResult
    {
        std::string molecule;
        int warnings;
    };

    RecognitionResult recognizeImage(bool verbose, imago::Settings& vars, const imago::Image& src, const std::string& config);

    int performFilterTest(imago::Settings& vars, const std::string& imageName);

    int performFileAction(bool verbose, imago::Settings& vars, const std::string& imageName, const std::string& configName,
                          const std::string& outputName = "molecule.mol");

}
