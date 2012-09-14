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

#include "comdef.h"
#include "virtual_fs.h"
#include "image_utils.h"
#include "chemical_structure_recognizer.h"
#include "molfile_saver.h"
#include "log_ext.h"
#include "molecule.h"
#include "prefilter_entry.h"
#include "superatom_expansion.h"
#include "output.h"
#include "settings.h"
#include <time.h>

#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#include <errno.h>
#endif

void dumpVFS(imago::VirtualFS& vfs)
{
	if (!vfs.empty())
	{
		imago::FileOutput flogdump("log_vfs.txt");
		std::vector<char> logdata;
		// store all the vfs contents in one single file (including html, images, etc)
		vfs.getData(logdata);
		flogdump.write(&logdata.at(0), logdata.size());
	}
}

void storeConfigCluster(imago::Settings& vars)
{
	// test config store
	std::string data;
	vars.saveToDataStream(data);

	imago::VirtualFS vfs;
	// store only one file
	char filename[imago::MAX_TEXT_LINE];		
	//srand ( time(NULL) ); // temp
	sprintf(filename, "config_%i.txt", vars.general.ClusterIndex);
	vfs.appendData(filename, data);
	vfs.storeOnDisk();
}

struct RecognitionResult
{
	std::string molecule;
	int warnings;
	bool exceptions;
};

void applyConfig(imago::Settings& vars, const std::string& config)
{
	if (!config.empty())
	{
		printf("Loading configuration cluster [%s]... ", config.c_str());
		bool result = vars.forceSelectCluster(config);
		if (result)
			printf("OK\n");
		else
			printf("FAIL\n");
	}
	else
	{
		vars.selectBestCluster();
	}
}

RecognitionResult recognizeImage(imago::Settings& vars, const imago::Image& src, const std::string& config)
{
	RecognitionResult result;
	result.molecule = "";
	result.exceptions = false;
	result.warnings = 0;
	
	imago::ChemicalStructureRecognizer _csr;
	imago::Molecule mol;

	for (int iter = 0; ; iter++)
	{
		bool good = false;

		try
		{
			imago::Image img;
			img.copy(src);

			if (iter == 0)
			{
				if (!imago::prefilterEntrypoint(vars, img))
					break;
			}
			else
			{
				if (!imago::applyNextPrefilter(vars, img))
					break;
			}

			applyConfig(vars, config);
			_csr.image2mol(vars, img, mol);

			result.molecule = imago::expandSuperatoms(vars, mol);
			result.warnings = mol.getWarningsCount() + mol.getDissolvingsCount() / vars.main.DissolvingsFactor;

			good = result.warnings < vars.main.WarningsRecalcTreshold;
			printf("Filter [%u] done, warnings: %u, good: %u.\n", vars.general.FilterIndex, result.warnings, good);
		}
		catch (std::exception &e)
		{
			result.exceptions = true;
			printf("Filter [%u] exception \"%s\".\n", vars.general.FilterIndex, e.what());
	#ifdef _DEBUG
			throw;
	#endif
		}

		if (good)
			break;
	} // for

	return result;
}


int performFileAction(imago::Settings& vars, const std::string& imageName, const std::string& configName)
{
	int result = 0; // ok mark
	imago::VirtualFS vfs;

	if (vars.general.ExtractCharactersOnly)
	{
		printf("Characters extraction from image \"%s\"\n", imageName.c_str());
	}
	else
	{
		printf("Recognition of image \"%s\"\n", imageName.c_str());
	}

	try
	{
		imago::Image image;	  

		if (vars.general.LogVFSEnabled)
		{
			imago::getLogExt().SetVirtualFS(vfs);
		}

		imago::ImageUtils::loadImageFromFile(image, imageName.c_str());

		if (vars.general.ExtractCharactersOnly)
		{
			imago::prefilterEntrypoint(vars, image);
			applyConfig(vars, configName);
			imago::ChemicalStructureRecognizer _csr;
			_csr.extractCharacters(vars, image);
		}
		else
		{
			RecognitionResult result = recognizeImage(vars, image, configName);		
			imago::FileOutput fout("molecule.mol");
			fout.writeString(result.molecule);
		}

	}
	catch (std::exception &e)
	{
		result = 2; // error mark
		puts(e.what());
#ifdef _DEBUG
		throw;
#endif
	}

	dumpVFS(vfs);

	return result;
}


int getdir(const std::string& dir, std::vector<std::string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) 
    {
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) 
    {
        files.push_back(std::string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		printf("Usage: %s [-log] [-logvfs] [-characters] [-dir dir_name] [-pr] image_path \n", argv[0]);
		printf("  -log: enables debug log output to ./log.html \n");
		printf("  -config cfg_file: loads specified configuration cluster file \n");
		printf("  -logvfs: stores log in single encoded file ./log_vfs.txt \n");
		printf("  -characters: extracts only characters from image(s) and store in ./characters/ \n");
		printf("  -dir dir_name: process every image from dir dir_name \n");
		printf("  -pr: use probablistic separator \n");
		printf("  image_path: full path to image to recognize (may be omitted if -dir specified) \n");
		return 0;
	}

	std::string image = "";
	std::string dir = "";
	std::string config = "";

	imago::Settings vars;

	bool next_arg_dir = false;
	bool next_arg_config = false;

	for (int c = 1; c < argc; c++)
	{
		std::string param = argv[c];
		
		if (param == "-l" || param == "-log")
			vars.general.LogEnabled = true;
		else if (param == "-logvfs")
			vars.general.LogVFSEnabled = true;

		else if (param == "-pr" || param == "-probablistic")
			vars.general.UseProbablistics = true;

		else if (param == "-dir")
			next_arg_dir = true;

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
			else
			{
				image = param;
			}
		}
	}
	
	imago::getLogExt().setLoggingEnabled(vars.general.LogEnabled);
	
	if (!dir.empty())
	{
		std::vector<std::string> files;
		if (getdir(dir, files) != 0)
		{
			printf("Error: can't get the content of directory \"%s\"\n", dir.c_str());
			return 2;
		}
		for (size_t u = 0; u < files.size(); u++)
		{
			if (!files[u].empty() && !(files[u][0] == '.'))
			{
				std::string fullpath = dir + "/" + files[u];
				performFileAction(vars, fullpath, config);	
			}
		}
	}
	else if (!image.empty())
	{
		return performFileAction(vars, image, config);	
	}		
	
	return 1; // "nothing to do" error
}
