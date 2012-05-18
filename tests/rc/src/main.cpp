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
#include "complex_contour.h"
#include "contour_template.h"

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

imago::VirtualFS fs;
std::string data("");

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
	bool testShapes;
	FileActionParams()
	{
		logLevel = 0;
		defaultFilter = ftCV;
		extractCharactersOnly = false;
		testShapes = false;
	}
};

double jointPS[8][10] = {
	{0.0093,    0.0080,    0.0134,    0.0145,    0.0134,    0.0129,    0.0096,    0.0054,    0.0088,    0.0103},
	{0.0134,    0.0165,    0.0225,    0.0217,    0.0163,    0.0189,    0.0134,    0.0096,    0.0067,    0.0129},
	{0.0034,    0.0150,    0.0176,    0.0121,    0.0098,    0.0098,    0.0062,    0.0065,    0.0049,    0.0057},
	{0.0248,    0.0393,    0.0256,    0.0269,    0.0155,    0.0119,    0.0114,    0.0109,    0.0052,    0.0057},
	{0.0114,    0.0085,    0.0114,    0.0158,    0.0140,    0.0134,    0.0090,    0.0101,    0.0083,    0.0075},
	{0.0178,    0.0165,    0.0145,    0.0132,    0.0129,    0.0134,    0.0119,    0.0109,    0.0127,    0.0173},
	{0.0039,    0.0152,    0.0186,    0.0152,    0.0106,    0.0057,    0.0067,    0.0031,    0.0057,    0.0041},
	{0.0114,    0.0196,    0.0189,    0.0158,    0.0160,    0.0155,    0.0124,    0.0098,    0.0072,    0.0083}
};

double jointPG[8][10] = {
	{0.0220,    0.0116,    0.0070,    0.0058,    0.0116,    0.0174,    0.0070,    0.0058,    0.0093,    0.0046},
	{0.0336,    0.0139,    0.0035,    0.0127,    0.0162,    0.0220,    0.0197,    0.0081,    0.0174,    0.0058},
	{0.0139,    0.0162,    0.0070,    0.0035,    0.0046,    0.0081,    0.0046,    0.0046,    0.0046,    0.0035},
	{0.0730,    0.0151,    0.0093,    0.0081,    0.0116,    0.0058,    0.0232,    0.0290,    0.0151,    0.0209},
	{0.0104,    0.0058,    0.0046,    0.0093,    0.0070,    0.0093,    0.0139,    0.0093,    0.0081,    0.0151},
	{0.0209,    0.0116,    0.0058,    0.0104,    0.0185,    0.0151,    0.0220,    0.0093,    0.0070,    0.0104},
	{0.0104,    0.0220,    0.0093,    0.0035,    0.0058,    0.0023,    0.0070,    0.0035,    0.0023,    0.0035},
	{0.0417,    0.0174,    0.0046,    0.0046,    0.0058,    0.0070,    0.0255,    0.0185,    0.0185,    0.0267}
};

int TP=0, FP=0, TN=0, FN=0;

int getAngleDirection(imago::ComplexNumber vec)
{
	double pi_8 = imago::PI_4 / 2.0;
	double angle = vec.getAngle();
		if(angle < 0)
			angle  += 2 * imago::PI;
		
		if(angle < pi_8 || angle >= 15.0 * pi_8)
			return 0;//"E";
		else
			if(angle >= pi_8 && angle < 3.0 * pi_8)
				return 1;// "NE";
			else
				if(angle >= 3.0 * pi_8 && angle < pi_8 * 5.0)
					return 2; // "N";
				else
					if(angle >= pi_8 * 5.0 && angle < pi_8 * 7.0)
						return 3; // "NW";
					else
						if(angle >= pi_8 * 7.0 && angle < pi_8 * 9.0)
							return 4; // "W";
		
		if(angle >= 9.0 * pi_8 && angle < 11.0 * pi_8)
				return 5; // "SW";
			else
				if(angle >= 11.0 * pi_8 && angle < pi_8 * 13.0)
					return 6; // "S";
				else
					if(angle >= pi_8 * 13.0 && angle < pi_8 * 15.0)
						return 7; // "SE";

}

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
		if(params.testShapes)
		{
			imago::TemplateComparer tc;
			tc.LoadTemplates();
			imago::getSettings().set("imgWidth", src_img.getWidth());
			imago::getSettings().set("imgHeight", src_img.getHeight());
			imago::ComplexContour cont = imago::ComplexContour::RetrieveContour(src_img);
			cont.Normalize();
			double gposterior = 1., sposterior = 1.;
			for(int i= 0; i < cont.Size(); i++)
			{
				imago::ComplexNumber cn = cont.getContour(i);
				int binD = 7 - getAngleDirection(cn);
				int binS = ((int)(cn.getRadius() * 10)) % 10;
				gposterior *= jointPG[binD][binS];
				sposterior *= jointPS[binD][binS];
			}

			bool symbolCase = true;
			if(symbolCase)
			{
				if(gposterior < sposterior)
					TP++;
				else
					FN++;
			}
			else
			{
				if(gposterior < sposterior)
					FP++;
				else
					TN++;
			}

			imago::TemplateFound tf = tc.Find(cont);
			imago::getLogExt().appendImage("Symbol", src_img);
			imago::getLogExt().append("Descriptor deviation 1 ", tf._acfddeviation[0]);
			imago::getLogExt().append("Descriptor deviation 2 ", tf._acfddeviation[1]);
			imago::getLogExt().append("Descriptor deviation 3 ", tf._acfddeviation[2]);
			imago::getLogExt().append("Descriptor deviation 4 ", tf._acfddeviation[3]);

			imago::getLogExt().append("Auto correlation rate", tf._autoCorrDiffRate);
			imago::getLogExt().append("Inter correlation rate", tf._interCorrRate);
			imago::getLogExt().append("Angle", tf._angle);

			std::ostringstream ss;
			
			ss << tf._autoCorrDiffRate << " " << tf._interCorrRate << " " << tf._angle << " ";
			ss << tf._acfddeviation[0] << " " << tf._acfddeviation[1] << " " << tf._acfddeviation[2] << " " << tf._acfddeviation[3];
			ss << "\r\n";
			data +=ss.str();
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
		else if (param == "-shapes")
		{
			fp.testShapes = true;
		}
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

	if(data.size() > 0)
	{
		fs.createNewFile("dataAn.txt", data);
		fs.storeOnDisk();
	}
	return 0;
}
