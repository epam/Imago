// mol-compare.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <vector>
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

void ReadElementsSection(std::ifstream& in, Elements& e)
{
	// lines like: M  V30 1 X 11.942546 -0.567518 0 0
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

		// else object - is numberic id

		std::string element;
		double posx, posy, posz, somewhat;
		in >> element >> posx >> posy >> posz >> somewhat;
		if (!in.bad())
		{
			e.push_back(element);						
		}
		else
			in.clear(); // reset bad format bit
	}				
}

void ReadBondsSection(std::ifstream& in, Bonds& b)
{
	// lines like: M  V30 1 1 4 9 [CFG]
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

		// else object - is numberic id
					
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

bool SimpilifiedReadMolFile(const std::string& filename, Elements& e, Bonds& b)
{
	std::ifstream in(filename);
	if (!in.is_open())
		return false;
	
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

		if (object == "COUNTS")
		{
			int elems, bonds, some1, some2, some3;
			in >> elems >> bonds >> some1 >> some2 >> some3;
			e.reserve(elems);
			b.reserve(bonds);
		} 
		else if (object == "BEGIN")
		{
			std::string type;
			in >> type;
			if (type == "ATOM")
			{
				ReadElementsSection(in, e);
			}
			else if (type == "BOND")
			{
				ReadBondsSection(in, b);
			}
		}
	}
	
	in.close();
	return true;
}

int MainCompare(const std::string& file1, const std::string& file2, bool verbose = true)
{
	Elements e1, e2;
	Bonds b1, b2;

	if (!SimpilifiedReadMolFile(file1, e1, b1))
	{
		if (verbose) printf("ERROR: Failed to read first specified mol file: '%s'\n", file1.c_str());
		return 1;
	}

	if (!SimpilifiedReadMolFile(file2, e2, b2))
	{
		if (verbose) printf("ERROR: Failed to read second specified mol file: '%s'\n", file2.c_str());
		return 2;
	}

	bool compare_fail = false, order_fail = false;

	if (e1.size() != e2.size())
	{
		if (verbose) printf("DIFF: Elements count mismatch: %i vs %i\n", e1.size(), e2.size());
		compare_fail = true;
	}
	else
	{
		for (size_t u = 0; u < e1.size(); u++)
		{
			if (e1[u] != e2[u])
			{					
				if (verbose) printf("NOTE: Elements on position %i mismatch: '%s' vs '%s'\n", u, e1[u].c_str(), e2[u].c_str());
				order_fail = true;
			}
		}
	}

	if (b1.size() != b2.size())
	{
		if (verbose) printf("DIFF: Bonds count mismatch: %i vs %i\n", b1.size(), b2.size());
		compare_fail = true;
	}
	else
	{
		std::vector<std::string> bl1, bl2;
		for (size_t u = 0; u < b1.size(); u++)
		{
			bl1.push_back(e1[b1[u].from-1] + "-" + e1[b1[u].to-1] + ":" + b1[u].type);
			bl2.push_back(e2[b2[u].from-1] + "-" + e2[b2[u].to-1] + ":" + b2[u].type);
		}

		bool bond_order_fail = false;

		for (size_t u = 0; u < bl1.size(); u++)
		{
			if (bl1[u] != bl2[u])
			{					
				bond_order_fail = true;					
				break;
			}
		}				

		std::sort(bl1.begin(), bl1.end());
		std::sort(bl2.begin(), bl2.end());

		for (size_t u = 0; u < bl1.size(); u++)
		{
			if (bl1[u] != bl2[u])
			{
				compare_fail = true;
				if (verbose) printf("DIFF: Bonds differs '%s' vs '%s'\n", bl1[u].c_str(), bl2[u].c_str());
			}
		}

		if (!compare_fail && bond_order_fail)
		{
			if (verbose) printf("DIFF: Bonds definition order differs\n");
			order_fail = true;
		}
	}

	if (compare_fail)
	{
		if (verbose) printf("DIFF: Files are different (3).\n");
		return 3;
	}
	else if (order_fail)
	{
		if (verbose) printf("DIFF: File elemens order differs, but files are semantically equal (0).\n");
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
					int res = MainCompare(MOLECULE, comppath, false);
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

