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

#include "file_helpers.h"
#include "recognition_helpers.h"
#include "machine_learning.h"
#include "similarity_tools.h"
#include "settings.h"
#include "log_ext.h"

int main(int argc, char **argv)
{
	imago::Settings vars;
	vars.general.TimeLimit = 10000; // ms, default timelimit value

	if (argc <= 1)
	{
		printf("Usage: %s [option]* [batches] [mode] [image_path] \n", argv[0]);				
		printf("\n  MODE SWITCHES: \n");
		printf("  image_path: full path to image to recognize (may be omitted if other switch is specified) \n");
		printf("  -characters: extracts only characters from image(s) and store in ./characters/ \n");
		printf("  -learn dir_name: process machine learning for specified collection \n");
		printf("\n  OPTION SWITCHES: \n");
		printf("  -config cfg_file: use specified configuration cluster file \n");		
		printf("  -log: enables debug log output to ./log.html \n");
		printf("  -logvfs: stores log in single encoded file ./log_vfs.txt \n");		
		printf("  -pr: use probablistic separator (experimental) \n");
		printf("  -tl time_in_ms: timelimit per single image process (default is %u) \n", vars.general.TimeLimit);
		printf("\n  BATCHES: \n");
		printf("  -dir dir_name: process every image from dir dir_name \n");
		printf("    -rec: process directory recursively \n");
		printf("    -images: skip non-supported files from directory \n");				
		return 0;
	}

	std::string image = "";
	std::string dir = "";
	std::string config = "";
	std::string sim_tool = "";
	std::string sim_param = "";

	bool next_arg_dir = false;
	bool next_arg_config = false;
	bool next_arg_sim_tool = false;
	bool next_arg_sim_param = false;
	bool next_arg_tl = false;	

	bool mode_recursive = false;
	bool mode_pass = false;
	bool mode_learning = false;
	bool mode_filter = false;

	for (int c = 1; c < argc; c++)
	{
		std::string param = argv[c];

		if (param.empty())
			continue;
		
		if (param == "-l" || param == "-log")
			vars.general.LogEnabled = true;

		else if (param == "-logvfs")
			vars.general.LogVFSEnabled = true;

		else if (param == "-pr" || param == "-probablistic")
			vars.general.UseProbablistics = true;

		else if (param == "-dir")
			next_arg_dir = true;

		else if (param == "-tl")
			next_arg_tl = true;

		else if (param == "-similarity")
			next_arg_sim_tool = true;

		else if (param == "-sparam")
			next_arg_sim_param = true;		

		else if (param == "-r" || param == "-rec")
			mode_recursive = true;

		else if (param == "-i" || param == "-images")
			mode_filter = true;

		else if (param == "-learn" || param == "-optimize")
			mode_learning = true;

		else if (param == "-learnd")
		{
			mode_learning = true;
			mode_recursive = true;
			mode_filter = true;
			next_arg_dir = true;
			sim_tool = "C:\\python27\\python.exe";
			sim_param = "C:\\imago-testing\\similarity\\compare-molecules.py";
		}

		else if (param == "-pass")
			mode_pass = true;

		else if (param == "-config")
			next_arg_config = true;

		else if (param == "-characters")
			vars.general.ExtractCharactersOnly = true;

		else 
		{
			if (next_arg_config)
			{
				config = param;
				next_arg_config = false;
			}
			else if (next_arg_dir)
			{
				dir = param;
				next_arg_dir = false;
			}
			else if (next_arg_sim_tool)
			{
				sim_tool = param;
				next_arg_sim_tool = false;
			}
			else if (next_arg_sim_param)
			{
				sim_param = param;
				next_arg_sim_param = false;
			}
			else if (next_arg_tl)
			{
				vars.general.TimeLimit = atoi(param.c_str());
				next_arg_tl = false;
			}
			else
			{
				if (param[0] == '-' && param.find('.') == std::string::npos)
				{
					printf("Unknown option: '%s'\n", param.c_str());
					return 1;
				}
				else
				{
					if (image.empty())
					{
						image = param;
					}
					else
					{
						printf("Image file is already specified ('%s'), the second definition unallowed ('%s')\n", image.c_str(), param.c_str());
						return 1;
					}
				}
			}
		}
	}

	similarity_tools::setExternalSimilarityTool(sim_tool, sim_param);
	
	imago::getLogExt().setLoggingEnabled(vars.general.LogEnabled);
	
	if (!dir.empty())
	{
		strings files;
		
		if (file_helpers::getDirectoryContent(dir, files, mode_recursive) != 0)
		{
			printf("[ERROR] Can't get the content of directory '%s'\n", dir.c_str());
			return 2;
		}

		if (mode_filter || mode_learning)
		{
			file_helpers::filterOnlyImages(files);
		}

		if (mode_learning)
		{			
			return machine_learning::performMachineLearning(vars, files, config);
		}
		else // process or pass
		{
			for (size_t u = 0; u < files.size(); u++)
			{
				if (mode_pass)
				{
					printf("Skipped file '%s'\n", files[u].c_str());
				}
				else
				{
					std::string output = files[u] + ".result.mol";
					recognition_helpers::performFileAction(true, vars, files[u], config, output);	
				}
			}
		}
	}
	else if (!image.empty()) // process single file
	{
		return recognition_helpers::performFileAction(true, vars, image, config);	
	}		
	
	return 1; // "nothing to do" error
}
