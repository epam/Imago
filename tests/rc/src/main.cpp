#include "session_manager.h"
#include "virtual_fs.h"
#include "image_utils.h"
#include "chemical_structure_recognizer.h"
#include "molfile_saver.h"
#include "recognition_settings.h"
#include "log_ext.h"
#include "prefilter.h"
#include "superatom_expansion.h"
#include "output.h"
#include "recognition_tree.h"

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

RecognitionResult recognize(const imago::Image& src, FilterType filterType)
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
			imago::RecognitionTree rt(img);
			rt.segmentate();
			img.copy(rt.getBitmask());
		}
			
		if (filterType == ftCV)
		{
			if (!prefilterCV(img))
			{
				throw std::exception("ftCV filter fails");
			}
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

int performRecognition(const std::string& imageName, int logLevel = 0, FilterType filterType = ftStd)
{
	const int WARNINGS_TRESHOLD = 2;

	int result = 0;
	imago::VirtualFS vfs;

	printf("Recognition of image \"%s\"\n", imageName.c_str());

	try
	{
		qword sid = imago::SessionManager::getInstance().allocSID();
		imago::SessionManager::getInstance().setSID(sid);
      
		imago::Image src_img;	  

		if (logLevel > 0)
		{
			imago::getSettings()["DebugSession"] = true;
			if (logLevel > 1)
				imago::getLogExt().SetVirtualFS(vfs);
		}

		imago::ImageUtils::loadImageFromFile(src_img, imageName.c_str());

		resampleImage(src_img);

		RecognitionResult result;

		if (isAlreadyBinarized(src_img))
		{
			 result = recognize(src_img, ftPass);
		}
		else
		{
			result = recognize(src_img, ftCV);
			if (result.exceptions)
			{
				result = recognize(src_img, ftStd);
				if (result.exceptions)
				{
					result = recognize(src_img, ftAdaptive);
					if (result.exceptions)
					{
						throw std::exception("Recognition fails.");
					}
				}
			} 
			else if (result.warnings > WARNINGS_TRESHOLD)
			{
				RecognitionResult r2 = recognize(src_img, ftStd);
				if (!r2.exceptions && r2.warnings < result.warnings)
					result = r2;
			}
		}
		
		imago::FileOutput fout("molecule.mol");
		fout.writeString(result.molecule);		

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


int main(int argc, char **argv)
{
	std::string image = "";
	int logLevel = 0;
	
	FilterType filterType = ftCV; // !!

	for (int c = 1; c < argc; c++)
	{
		std::string param = argv[c];
		if (param == "-l" || param == "-log")
			logLevel = 1;
		else if (param == "-logvfs")
			logLevel = 2;
		else if (param == "-adaptive")
			filterType = ftAdaptive;
		else if (param == "-cv")
			filterType = ftCV;
		else if (param == "-std")
			filterType = ftStd;
		else 
			image = param;
	}
	
	if (image.empty())
		return 0;
	
	return performRecognition(image, logLevel, filterType);	
}
