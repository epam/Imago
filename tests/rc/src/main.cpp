#include "comdef.h"
#include "virtual_fs.h"
#include "image_utils.h"
#include "chemical_structure_recognizer.h"
#include "molfile_saver.h"
#include "log_ext.h"
#include "prefilter.h"
#include "molecule.h"
#include "prefilter_cv.h"
#include "adaptive_filter.h"
#include "superatom_expansion.h"
#include "output.h"
#include "constants.h"

#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif

void dumpVFS(imago::VirtualFS& vfs)
{
	if (!vfs.empty())
	{
		imago::FileOutput flogdump("log_vfs.txt");
		std::vector<char> logdata;
		vfs.getData(logdata);
		flogdump.write(&logdata.at(0), logdata.size());
	}
}

struct RecognitionResult
{
	std::string molecule;
	int warnings;
	bool exceptions;
};

RecognitionResult recognizeImage(imago::Settings& vars, const imago::Image& src)
{
	RecognitionResult result;
	result.molecule = "";
	result.exceptions = false;
	result.warnings = 0;
	try
	{
		imago::ChemicalStructureRecognizer _csr;
		imago::Molecule mol;
		imago::Image img;
		img.copy(src);

		if (vars.general.DefaultFilterType == imago::ftAdaptive)
		{
			imago::AdaptiveFilter::process(vars, img);
		}
			
		if (vars.general.DefaultFilterType == imago::ftCV)
		{
			prefilterCV(vars, img);
		}
			
		if (vars.general.DefaultFilterType == imago::ftStd)
		{
			prefilterImage(vars, img, _csr.getCharacterRecognizer());
		}

		_csr.image2mol(vars, img, mol);
		result.molecule = imago::expandSuperatoms(vars, mol);
		result.warnings = mol.getWarningsCount() + mol.getDissolvingsCount() / vars.main.DissolvingsFactor;

		printf("Filter [%s] done, warnings: %u.\n", imago::FilterName[vars.general.DefaultFilterType], result.warnings);
	}
	catch (std::exception &e)
	{
		result.exceptions = true;
		printf("Filter [%s] exception \"%s\".\n", imago::FilterName[vars.general.DefaultFilterType], e.what());
#ifdef _DEBUG
		throw;
#endif
	}
	return result;
}


int performFileAction(imago::Settings& vars, const std::string& imageName)
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
		imago::Image src_img;	  

		if (vars.general.LogVFSEnabled)
		{
			imago::getLogExt().SetVirtualFS(vfs);
		}

		imago::ImageUtils::loadImageFromFile(src_img, imageName.c_str());

		resampleImage(src_img);

		if (vars.general.ExtractCharactersOnly)
		{
			if (!isBinarized(vars, src_img))
			{
				prefilterCV(vars, src_img);
			}
			
			imago::ChemicalStructureRecognizer _csr;
			_csr.extractCharacters(vars, src_img);
		}
		else
		{
			RecognitionResult result;

			if (isBinarized(vars, src_img))
			{
				vars.general.IsHandwritten = false;

				vars.general.DefaultFilterType = imago::ftPass;
				result = recognizeImage(vars, src_img);
			}
			else
			{
				vars.general.IsHandwritten = true;

				vars.general.DefaultFilterType = imago::ftCV;
				result = recognizeImage(vars, src_img);
				if (result.exceptions)
				{
					vars.general.DefaultFilterType = imago::ftStd;
					result = recognizeImage(vars, src_img);
					if (result.exceptions)
					{
						vars.general.DefaultFilterType = imago::ftAdaptive;
						result = recognizeImage(vars, src_img);
						if (result.exceptions)
						{
							throw std::exception("Recognition fails.");
						}
					}
				} 
				else if (result.warnings > vars.main.WarningsRecalcTreshold)
				{
					vars.general.DefaultFilterType = imago::ftStd;
					RecognitionResult r2 = recognizeImage(vars, src_img);
					if (!r2.exceptions && r2.warnings < result.warnings)
						result = r2;
				}
			}
		
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
		printf("Usage: %s [-log] [-logvfs] [-characters] [-dir dir_name] image_path \n", argv[0]);
		printf("  -log: enables debug log output to ./log.html \n");
		printf("  -logvfs: stores log in single encoded file ./log_vfs.txt \n");
		printf("  -characters: extracts only characters from image(s) and store in ./characters/ \n");
		printf("  -dir dir_name: process every image from dir dir_name \n");
		printf("  image_path: full path to image to recognize (may be omitted if -dir specified) \n");
		return 0;
	}

	std::string image = "";
	std::string dir = "";

	imago::Settings vars;

	bool next_arg_dir = false;

	for (int c = 1; c < argc; c++)
	{
		std::string param = argv[c];
		
		if (param == "-l" || param == "-log")
			vars.general.LogEnabled = true;
		else if (param == "-logvfs")
			vars.general.LogVFSEnabled = true;

		else if (param == "-adaptive")
			vars.general.DefaultFilterType = imago::ftAdaptive;
		else if (param == "-cv")
			vars.general.DefaultFilterType = imago::ftCV;
		else if (param == "-std")
			vars.general.DefaultFilterType = imago::ftStd;

		else if (param == "-dir")
			next_arg_dir = true;
		else if (param == "-characters")
			vars.general.ExtractCharactersOnly = true;

		else 
		{
			if (next_arg_dir)
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

	// temporary workaround (cause it's thread insenisive now)
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
				performFileAction(vars, fullpath);	
			}
		}
	}
	else if (!image.empty())
	{
		return performFileAction(vars, image);	
	}
	
	return 0;
}
