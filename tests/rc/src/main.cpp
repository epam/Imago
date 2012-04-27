#include "session_manager.h"
#include "virtual_fs.h"
#include "image_utils.h"
#include "chemical_structure_recognizer.h"
#include "molfile_saver.h"
#include "recognition_settings.h"
#include "log_ext.h"
#include "prefilter.h"
#include "prefilter_cv.h"
#include "adaptive_filter.h"
#include "superatom_expansion.h"
#include "output.h"

#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif


enum FilterType
{
	ftStd = 0,
	ftAdaptive = 1,
	ftCV = 2,
	ftPass = 3
};

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

RecognitionResult recognizeImage(const imago::Image& src, FilterType filterType)
{
	RecognitionResult result;
	result.molecule = "";
	result.exceptions = false;
	result.warnings = 0;
	try
	{
		imago::ChemicalStructureRecognizer &csr = imago::getRecognizer();
		imago::Molecule mol;
		imago::Image img;
		img.copy(src);

		if (filterType == ftAdaptive)
		{
			imago::AdaptiveFilter::process(img);
		}
			
		if (filterType == ftCV)
		{
			prefilterCV(img);
		}
			
		if (filterType == ftStd)
		{
			prefilterImage(img, csr.getCharacterRecognizer());
		}

		csr.image2mol(img, mol);
		result.molecule = imago::expandSuperatoms(mol);
		result.warnings = mol.getWarningsCount() + mol.getDissolvingsCount() / 10;

		printf("Filter [%u], warnings: %u\n", filterType, result.warnings);
	}
	catch (std::exception &e)
	{
		result.exceptions = true;
		printf("Filter [%u], exception \"%s\"\n", filterType, e.what());
	}
	return result;
}

// TODO: provide general function; recognize : Image -> molecule_string
//       and call it from bindings (for Ipad and etc)

struct FileActionParams
{
	int logLevel;
	FilterType defaultFilter;
	bool extractCharactersOnly;
	FileActionParams()
	{
		logLevel = 0;
		defaultFilter = ftCV;
		extractCharactersOnly = false;
	}
};

int performFileAction(const std::string& imageName, const FileActionParams& params)
{
	const int WARNINGS_TRESHOLD = 2;

	int result = 0; // ok mark
	imago::VirtualFS vfs;

	printf("Recognition of image \"%s\"\n", imageName.c_str());

	try
	{
		qword sid = imago::SessionManager::getInstance().allocSID();
		imago::SessionManager::getInstance().setSID(sid);
      
		imago::Image src_img;	  

		if (params.logLevel > 0)
		{
			imago::getSettings()["DebugSession"] = true;
			if (params.logLevel > 1)
				imago::getLogExt().SetVirtualFS(vfs);
		}

		imago::ImageUtils::loadImageFromFile(src_img, imageName.c_str());

		resampleImage(src_img);

		if (params.extractCharactersOnly)
		{
			if (!isBinarized(src_img))
			{
				prefilterCV(src_img);
			}
			imago::ChemicalStructureRecognizer &csr = imago::getRecognizer();
			csr.extractCharacters(src_img);
		}
		else
		{
			RecognitionResult result;

			if (isBinarized(src_img))
			{
				imago::getSettings().set("IsHandwritten", false);

				result = recognizeImage(src_img, ftPass);
			}
			else
			{
				imago::getSettings().set("IsHandwritten", true);

				result = recognizeImage(src_img, ftCV);
				if (result.exceptions)
				{
					result = recognizeImage(src_img, ftStd);
					if (result.exceptions)
					{
						result = recognizeImage(src_img, ftAdaptive);
						if (result.exceptions)
						{
							throw std::exception("Recognition fails.");
						}
					}
				} 
				else if (result.warnings > WARNINGS_TRESHOLD)
				{
					RecognitionResult r2 = recognizeImage(src_img, ftStd);
					if (!r2.exceptions && r2.warnings < result.warnings)
						result = r2;
				}
			}
		
			imago::FileOutput fout("molecule.mol");
			fout.writeString(result.molecule);
		}

		imago::SessionManager::getInstance().releaseSID(sid);      
	}
	catch (std::exception &e)
	{
		result = 2; // error mark
		puts(e.what());
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
	std::string image = "";
	std::string dir = "";

	FileActionParams fp;

	bool next_arg_dir = false;

	for (int c = 1; c < argc; c++)
	{
		std::string param = argv[c];
		
		if (param == "-l" || param == "-log")
			fp.logLevel = 1;
		else if (param == "-logvfs")
			fp.logLevel = 2;

		else if (param == "-adaptive")
			fp.defaultFilter = ftAdaptive;
		else if (param == "-cv")
			fp.defaultFilter = ftCV;
		else if (param == "-std")
			fp.defaultFilter = ftStd;

		else if (param == "-dir")
			next_arg_dir = true;
		else if (param == "-characters")
			fp.extractCharactersOnly = true;

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
				performFileAction(fullpath, fp);	
			}
		}
	}
	else if (!image.empty())
	{
		return performFileAction(image, fp);	
	}
	
	return 0;
}
