// mol-compare.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

#ifdef WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif

struct Bond
{
	int from, to;
	std::string type;
	Bond(int _from, int _to, std::string _type)
	{
		from = _from;
		to = _to;
		type = _type;
	}
};

typedef std::vector<std::string> Elements;
typedef std::vector<Bond> Bonds;

void ReadSection(std::ifstream& in, Bonds& b, Elements& e, bool elementSection)
{	
	while (!in.eof())
	{
		std::string prefix;
		in >> prefix;
		if (prefix != "M") // line sync
			continue;

		std::string version;
		in >> version;
		// ignore

		std::string object;
		in >> object;

		if (object == "END")
			break;

		if (elementSection)
		{
			// lines like: M  V30 1 X 11.942546 -0.567518 0 0

			std::string element;
			double x, y, z;
			in >> element >> x >> y >> z;
			if (!in.bad())
			{
				e.push_back(element);						
			}
			else
				in.clear(); // reset bad format bit
		}
		else // bond section
		{
			// lines like: M  V30 1 1 4 9 [CFG]
					
			std::string bondtype;
			int from, to;
			in >> bondtype >> from >> to;
			if (!in.bad())
			{
				b.push_back(Bond(from, to, bondtype));						
			}
			else
				in.clear(); // reset bad format bit
		}
	}				
}

bool SimpilifiedReadMolFile(const std::string& filename, Elements& e, Bonds& b)
{
	std::ifstream in(filename);
	if (!in.is_open())
		return false;
	
	std::string version = "";

	while (!in.eof())
	{
		std::string prefix;
		in >> prefix;
		if (prefix == "V3000") // found V3000 version
		{
			version = prefix;
			break;
		}
		else if (prefix == "V2000") // found V2000 version
		{
			version = prefix;
			break;
		}
		else
		{
			// try next record
			continue;
		}
	}
	
	in.seekg(0, std::ios_base::beg); // restart


	if (version == "V2000")
	{
		char ignore[1024];

		std::string header;
		in >> header;
		int atoms, bonds;
		in >> atoms >> bonds;
		in.getline(ignore, 1024);

		for (int line = 0; line < atoms; line++)
		{			
			double x, y, z;
			std::string element;
			in >> x >> y >> z >> element;
			e.push_back(element);
			in.getline(ignore, 1024);
		}
		for (int line = 0; line < bonds; line++)
		{
			int from, to;
			std::string type;
			in >> from >> to >> type;
			b.push_back(Bond(from, to, type));
			in.getline(ignore, 1024);
		}
	}

	if (version == "V3000")
	{
		while (!in.eof())
		{
			std::string prefix;
			in >> prefix;
			if (prefix != "M") // line sync
				continue;

			std::string version, object, type;
			in >> version >> object >> type;

			if (object == "BEGIN" && type == "ATOM")
				ReadSection(in, b, e, true);
			else if (object == "BEGIN" && type == "BOND")
				ReadSection(in, b, e, false);
		}
	}

	in.close();
	return true;
}

void printExt(const std::string& caption, const std::vector<std::string>& v1)
{
	printf("%s: ", caption.c_str());
	for (size_t u = 0; u < v1.size(); u++)
		printf("%s ", v1[u].c_str());
	printf("\n");
}

bool compareExt(const std::string& type, 
	            const std::vector<std::string>& v1, const std::vector<std::string>& v2, bool verbose)
{
	bool good = true;
	
	typedef std::map<std::string, int> Dictionary;
	Dictionary d1, d2;
	
	#define IM_TOO_LAZY(v1,d1) \
		for (size_t u = 0; u < v1.size(); u++) d1[v1[u]] = 0; \
		for (size_t u = 0; u < v1.size(); u++) d1[v1[u]]++;

	IM_TOO_LAZY(v1,d1); 
	IM_TOO_LAZY(v2,d2);
	
	#define IM_TOO_LAZY_2(d1,d2,s1,s2) \
	for (Dictionary::iterator it = d1.begin(); it != d1.end(); it++)\
	{\
		int c1 = it->second;\
		int c2 = d2.find(it->first) != d2.end() ? d2[it->first] : 0;\
		if (c1 > c2)\
		{\
			if (verbose) printf("%s %s exists in %s, but doesn't exists in %s (x %u)\n", \
				type.c_str(), it->first.c_str(), s1, s2, c1 - c2);\
			good = false;\
		}\
	}\

	IM_TOO_LAZY_2(d1,d2, "[1]", "[2]");
	IM_TOO_LAZY_2(d2,d1, "[2]", "[1]");

	return good;
}

int MainCompare(const std::string& file1, const std::string& file2, bool verbose = true)
{
	Elements e1, e2;
	Bonds b1, b2;

	if (!SimpilifiedReadMolFile(file1, e1, b1) || e1.empty())
	{
		if (verbose) printf("ERROR: Failed to read first specified mol file: '%s'\n", file1.c_str());
		return 1;
	}

	if (!SimpilifiedReadMolFile(file2, e2, b2) || e2.empty())
	{
		if (verbose) printf("ERROR: Failed to read second specified mol file: '%s'\n", file2.c_str());
		return 2;
	}

	bool compare_fail = !compareExt("Element", e1, e2, verbose);
	
	std::vector<std::string> b1s, b2s;		
	try
	{
		for (size_t u = 0; u < b1.size(); u++)
			b1s.push_back(e1[b1[u].from-1] + "-" + e1[b1[u].to-1] + ":" + b1[u].type);			

		for (size_t u = 0; u < b2.size(); u++)
			b2s.push_back(e2[b2[u].from-1] + "-" + e2[b2[u].to-1] + ":" + b2[u].type);			
	}
	catch(std::exception &e)
	{
		printf("EXCEPTION: %s\n", e.what());
	}

	if (verbose)
	{
		printExt("Bonds of [1]: ", b1s);
		printExt("Bonds of [2]: ", b2s);
	}

	if (!compareExt("Bond", b1s, b2s, verbose))
		compare_fail = true;

	if (compare_fail)
	{
		if (verbose) printf("DIFF: Files are different (3).\n");
		return 3;
	}
	else
	{
		if (verbose) printf("DIFF: No differences encountered (0).\n");
	}

	return 0;
}

int getdir(const std::string& dir, std::vector<std::string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(std::string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

bool filecopy(const char* from, const char* to)
{
#ifdef WIN32
	return 0 != CopyFile(from, to, FALSE);
#else
	// TODO: check
	return 0 == system((std::string("cp") + " \"" + from + "\" \"" + to + "\"").c_str());
#endif
}

std::string ReadSingleWordFile(const std::string& filename)
{
	std::ifstream in(filename);
	if (!in.is_open())
		return "";
	std::string result;
	in >> result;
	in.close();
	return result;
}

void WriteStringFile(const std::string& filename, const std::string& data)
{
	std::ofstream out(filename);
	if (out.is_open())
	{
		out << data;
		out.close();
	}
}

int main(int argc, char* argv[])
{
	bool minus_e = (argc > 2) && (std::string(argv[1]) == "-e");

	if ((argc == 4) && minus_e)
	{		
		const std::string MOLECULE = "./molecule.mol";

		std::string exename = argv[2];
		std::string testset = argv[3];

		std::vector<std::string> files;

		if (getdir(testset, files) != 0)
		{
			printf("ERROR: can not open dir '%s', maybe non-existent\n", testset);
		}
		else
		{
			std::vector<std::string> stats;

			for (size_t u = 0; u < files.size(); u++)
			{
				std::string name, ext;
				size_t i = files[u].find_last_of('.');
				if (i == std::string::npos)
				{
					continue;
				}
				else
				{
					name = files[u].substr(0, i);
					ext = files[u].substr(i+1);
					std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
				}
				if (ext == "jpg" || ext == "jpeg" || ext == "png")
				{
					std::string fullpath = testset + "/" + files[u];
					printf("Touching file %s ...\n", fullpath.c_str());
					
#ifdef WIN32
					std::string verbose = "1>NUL 2>NUL"; // disable screen text output
#else
					// TODO
					std::string verbose = "";
#endif

					if (system((exename + " " + fullpath + " " + verbose).c_str()) != 0)
					{
						printf("ERROR: Error calling executable file.\n");
						break;
					}
					
					std::string comppath = testset + "/" + name + ".mol";
					std::string respath = testset + "/" + name + ".res.txt";

					// now the MOLECULE file should be produced
					int res = MainCompare(MOLECULE, comppath);
					if (res == 0)
					{
						stats.push_back(name + "... " + "SAME, " + ReadSingleWordFile(respath));
					}
					else if (res == 1)
					{
						printf("ERROR: The '%s' file is not created by executable for some reason\n", MOLECULE.c_str());
						break;
					}
					else if (res == 2)
					{						
						stats.push_back(name + "... " + "CREATED");
						filecopy(MOLECULE.c_str(), comppath.c_str());
						WriteStringFile(respath, "NEED MANUAL CHECK\nTHEN WRITE OK or BAD");
						printf("The '%s' compare file was not created before, so the current output will be saved there\n", comppath.c_str());
					}
					else if (res == 3)
					{												
						std::string storepath = testset + "/" + name + ".last.mol";
						filecopy(MOLECULE.c_str(), storepath.c_str());
						
						std::string oldresult = ReadSingleWordFile(respath);
						if (oldresult == "OK")
							stats.push_back(name + "... " + "REGRESSION");
						else if (oldresult == "BAD")
							stats.push_back(name + "... " + "IMPROVEMENT?");
						else
							stats.push_back(name + "... " + "DIFFERS");

						printf("File content is not same as before, added '%s' to manual verify\n", storepath.c_str());
					}

					printf("\n");
				} // if jpg/png
			} // for

			printf("\n\nProcessed %i files, results are:\n", stats.size());
			for (size_t u = 0; u < stats.size(); u++)
				printf("[%i] %s\n", u+1, stats[u].c_str());
		}
	}
	else if (argc == 3)
	{
		return MainCompare(argv[1], argv[2]);
	}
	else
	{
		printf("USAGE: mol-compare molfile1.mol molfile2.mol\n");
		printf("or mol-comapre -e imagotest test_set_path (imagotest should produce molecule.mol)\n");
		return 1;
	}

	return 0;
}

