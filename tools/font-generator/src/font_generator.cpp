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

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "character_recognizer.h"

std::string EscapeCharacter(unsigned char c)
{
    std::string result;
    {
        char buf[16] = {0};
        sprintf(buf, "%x", (unsigned int)c);
        result = (std::string)("\\x") + buf;
    }
    return result;
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("Usage: %s symbols_dir output_file\n", argv[0]);
        return 1;
    }
    else
    {
        std::string dir = argv[1];
        std::string file = argv[2];
        imago::Settings vars;
        imago::CharacterRecognizerImp::Templates templates;
        if (imago::CharacterRecognizerImp::initializeTemplates(vars, dir, templates))
        {
            printf("Initialized %u templates.\n", (unsigned)templates.size());
            FILE* f = fopen(file.c_str(), "w");
            if (f != NULL)
            {
                fprintf(f, "imago::CharacterRecognizerImp::MatchRecord m;\n");
                size_t dim = imago::CharacterRecognizerImp::REQUIRED_SIZE + 2 * imago::CharacterRecognizerImp::PENALTY_SHIFT;

                unsigned char max1 = 0, max2 = 0;

                for (size_t x = 0; x < templates.size(); x++)
                {
                    imago::CharacterRecognizerImp::MatchRecord& m = templates[x];
                    fprintf(f, "m.text = \"%s\";\n", m.text.c_str());
                    fprintf(f, "m.wh_ratio = %g;\n", m.wh_ratio);

                    std::string s1, s2;

                    for (size_t u = 0; u < imago::CharacterRecognizerImp::INTERNAL_ARRAY_SIZE; u++)
                    {
                        unsigned char c1 = m.penalty_ink[u];
                        if (c1 > max1)
                            max1 = c1;
                        s1 += EscapeCharacter(c1);
                    }

                    for (size_t u = 0; u < imago::CharacterRecognizerImp::INTERNAL_ARRAY_SIZE; u++)
                    {
                        unsigned char c2 = m.penalty_white[u];
                        if (c2 > max2)
                            max2 = c2;
                        s2 += EscapeCharacter(c2);
                    }

                    fprintf(f, "memcpy(m.penalty_ink, \"%s\", %u);\n", s1.c_str(), imago::CharacterRecognizerImp::INTERNAL_ARRAY_SIZE);
                    fprintf(f, "memcpy(m.penalty_white, \"%s\", %u);\n", s2.c_str(), imago::CharacterRecognizerImp::INTERNAL_ARRAY_SIZE);
                    fprintf(f, "templates.push_back(m);\n");
                }

                printf("Maximal penalty_ink = %u [%s]\n", (unsigned int)max1, (max1 < 255) ? "OK" : "FAIL");
                printf("Maximal penalty_white = %u [%s]\n", (unsigned int)max2, (max2 < 255) ? "OK" : "FAIL");
                printf("Stored %u templates.\n", (unsigned)templates.size());

                fclose(f);
            }
            else
            {
                printf("Failed to open output file: '%s'\n", file.c_str());
                return 2;
            }
        }
        else
        {
            printf("Failed to load templates: '%s'\n", dir.c_str());
            return 2;
        }
    }

    return 0;
}
