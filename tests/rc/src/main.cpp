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
	ftCV = 2
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

void performRecognition(const std::string& imageName, int logLevel = 0, FilterType filterType = ftStd)
{
	imago::VirtualFS vfs;

	try
	{
		qword sid = imago::SessionManager::getInstance().allocSID();
		imago::SessionManager::getInstance().setSID(sid);
      
		imago::Image img;	  

		if (logLevel > 0)
		{
			imago::getSettings()["DebugSession"] = true;
			if (logLevel > 1)
				imago::getLogExt().SetVirtualFS(vfs);
		}

		imago::getSettings()["AdaptiveFilter"] = filterType;

		imago::ChemicalStructureRecognizer &csr = imago::getRecognizer();

		imago::ImageUtils::loadImageFromFile(img, imageName.c_str());

		imago::Molecule mol;

		resampleImage(img);

		if (!isAlreadyBinarized(img))
		{
			if (filterType == ftAdaptive)
			{
				imago::RecognitionTree rt(img);
				rt.segmentate();
				img.copy(rt.getBitmask());
			}
			else if (filterType == ftCV)
			{
				prefilterCV(img);
			}
			else // -std
			{
				prefilterImage(img, csr.getCharacterRecognizer());
			}
		}
		
		csr.image2mol(img, mol);

		std::string molfile = imago::expandSuperatoms(mol);

		imago::FileOutput fout("molecule.mol");
		fout.writeString(molfile);		

		imago::SessionManager::getInstance().releaseSID(sid);      
	}
	catch (std::exception &e)
	{
		puts(e.what());
	}

	dumpVFS(vfs);
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
	
	if (!image.empty())
		performRecognition(image, logLevel, filterType);
	
	return 0;
}
