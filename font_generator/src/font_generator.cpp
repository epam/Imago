/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <opencv2/opencv.hpp>

#include "character_recognizer.h"

std::string EscapeCharacter(unsigned char c)
{
	std::string result;
	result += c;
	if (c == '\\' || c == '\"')
		result = "\\" + result;
	return result;
}

int main(int argc, char **argv)
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
			printf("Initialized %u templates.\n", templates.size());
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
						if (c1 > max1) max1 = c1;
						s1 += EscapeCharacter(c1);
					}

					for (size_t u = 0; u < imago::CharacterRecognizerImp::INTERNAL_ARRAY_SIZE; u++)
					{						
						unsigned char c2 = m.penalty_white[u];
						if (c2 > max2) max2 = c2;
						s2 += EscapeCharacter(c2);
					}					

					fprintf(f, "memcpy(m.penalty_ink, \"%s\", %u);\n", s1.c_str(), imago::CharacterRecognizerImp::INTERNAL_ARRAY_SIZE);
					fprintf(f, "memcpy(m.penalty_white, \"%s\", %u);\n", s2.c_str(), imago::CharacterRecognizerImp::INTERNAL_ARRAY_SIZE);
					fprintf(f, "templates.push_back(m);\n");
				}

				printf("Maximal penalty_ink = %u [%s]\n", (unsigned int)max1, (max1 < 255) ? "OK" : "FAIL");
				printf("Maximal penalty_white = %u [%s]\n", (unsigned int)max2, (max2 < 255) ? "OK" : "FAIL");
				printf("Stored %u templates.\n", templates.size());

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
