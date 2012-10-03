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

typedef std::vector<std::string> strings;

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

struct RecognitionResult
{
	std::string molecule;
	int warnings;
};

RecognitionResult recognizeImage(imago::Settings& vars, const imago::Image& src, const std::string& config)
{
	std::vector<RecognitionResult> results;
		
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

			RecognitionResult result;
			result.molecule = imago::expandSuperatoms(vars, mol);
			result.warnings = mol.getWarningsCount() + mol.getDissolvingsCount() / vars.main.DissolvingsFactor;
			results.push_back(result);

			good = result.warnings <= vars.main.WarningsRecalcTreshold;
			printf("Filter [%u] done, warnings: %u, good: %u.\n", vars.general.FilterIndex, result.warnings, good);
		}
		catch (std::exception &e)
		{
			printf("Filter [%u] exception \"%s\".\n", vars.general.FilterIndex, e.what());
	#ifdef _DEBUG
			throw;
	#endif
		}

		if (good)
			break;
	} // for

	RecognitionResult result;
	result.warnings = 999;
	// select the best one
	for (size_t u = 0; u < results.size(); u++)
	{
		if (results[u].warnings < result.warnings)
		{
			result = results[u];
		}
	}
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

int performMachineLearning(imago::Settings& vars, const strings& imageSet, const std::string& configName)
{
	int result = 0; // ok mark
	try
	{
		for (size_t u = 0; u < imageSet.size(); u++)
		{
			printf("Image: %s\n", imageSet[u].c_str());
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

	return result;
}


int getdir(const std::string& dir, strings &files, bool recursive)
{
    DIR *dp;
    struct dirent *dirp;
	
	strings todo;

    if((dp = opendir(dir.c_str())) == NULL) 
    {
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) 
    {
		if (dirp->d_type == DT_REG)
		{
			files.push_back(dir + "/" + std::string(dirp->d_name));
		}
		else if (recursive && dirp->d_type == DT_DIR)
		{
			if (dirp->d_name[0] != '.')
			{
				todo.push_back(dir + "/" + dirp->d_name);				
			}
		}
    }
    closedir(dp);

	for (size_t u = 0; u < todo.size(); u++)
	{
		getdir(todo[u], files, recursive);
	}

    return 0;
}

bool isSupportedImageType(const std::string& filename)
{
	size_t idx = filename.rfind('.');
	if (idx != std::string::npos)
	{
		std::string ext = filename.substr(idx+1);
		std::transform(ext.begin(), ext.end(), ext.begin(), toupper);

		// from OpenCV documentation:
		if (ext == "BMP"  ||  
			ext == "DIB"  ||
			ext == "JPEG" || 
			ext == "JPG"  ||
			ext == "JPE"  ||
			ext == "PNG"  || 
			ext == "PBM"  ||
			ext == "PGM"  ||
			ext == "PPM"  ||
			ext == "SR"   ||
			ext == "RAS"  ||
			ext == "TIFF" ||
			ext == "TIF") // nice vertical lines
		{
			return true;
		}
	}
	return false;
}

void filterOnlyImages(strings& files)
{
	strings out; // O(N)

	for (size_t u = 0; u < files.size(); u++)
	{
		if (isSupportedImageType(files[u]))
		{
			out.push_back(files[u]);
		}
	}

	files = out;
}

int main(int argc, char **argv)
{
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
		printf("\n  BATCHES: \n");
		printf("  -dir dir_name: process every image from dir dir_name \n");
		printf("    -rec: process directory recursively \n");
		printf("    -images: skip non-supported files from directory \n");				
		return 0;
	}

	std::string image = "";
	std::string dir = "";
	std::string config = "";

	imago::Settings vars;

	bool next_arg_dir = false;
	bool next_arg_config = false;
	
	bool recursive = false;
	bool pass = false;
	bool learning = false;
	bool filter = false;

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

		else if (param == "-rec" || param == "-r")
			recursive = true;

		else if (param == "-images" || param == "-i")
			filter = true;

		else if (param == "-learn" || param == "-optimize")
			learning = true;

		else if (param == "-pass")
			pass = true;

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
				if (param[0] == '-' && param.find('.') == std::string::npos)
				{
					printf("Unknown option: '%s'\n", param.c_str());
					return 1;
				}
				else
				{
					image = param;
				}
			}
		}
	}
	
	imago::getLogExt().setLoggingEnabled(vars.general.LogEnabled);
	
	if (!dir.empty())
	{
		strings files;
		
		if (getdir(dir, files, recursive) != 0)
		{
			printf("Error: can't get the content of directory \"%s\"\n", dir.c_str());
			return 2;
		}

		if (filter || learning)
		{
			filterOnlyImages(files);
		}

		if (learning)
		{			
			return performMachineLearning(vars, files, config);
		}
		else
		{
			for (size_t u = 0; u < files.size(); u++)
			{
				if (pass)
					printf("Skipped file '%s'\n", files[u].c_str());
				else
					performFileAction(vars, files[u], config);	
			}
		}
	}
	else if (!image.empty())
	{
		return performFileAction(vars, image, config);	
	}		
	
	return 1; // "nothing to do" error
}
