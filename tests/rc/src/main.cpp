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

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <time.h>

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
#include "scanner.h"
#include "settings.h"
#include "platform_tools.h"

#include "file_helpers.h"
#include "learning_context.h"
#include "similarity_tools.h"


static bool verbose = true;


const int LEARNING_MAX_CONFIGS = 200;
const int LEARNING_TOP_USE = 3;
const double LEARNING_ABNORMAL_TIME = 3000; // ms
const int LEARNING_VERBOSE_TIME = 5000; // ms

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
	sprintf(filename, "config_%i.txt", vars.general.ClusterIndex);
	vfs.appendData(filename, data);
	vfs.storeOnDisk();
}

void applyConfig(imago::Settings& vars, const std::string& config)
{
	if (!config.empty())
	{
		if (verbose)
			printf("Loading configuration cluster [%s]... ", config.c_str());

		bool result = vars.forceSelectCluster(config);

		if (verbose)
		{
			if (result)
				printf("OK\n");
			else
				printf("FAIL\n");
		}
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
			
			if (verbose)
				printf("Filter [%u] done, warnings: %u, good: %u.\n", vars.general.FilterIndex, result.warnings, good);
		}
		catch (std::exception &e)
		{
			if (verbose)
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


int performFileAction(imago::Settings& vars, const std::string& imageName, const std::string& configName,
	                  const std::string& outputName = "molecule.mol")
{
	int result = 0; // ok mark
	imago::VirtualFS vfs;

	if (vars.general.ExtractCharactersOnly)
	{
		if (verbose)
			printf("Characters extraction from image \"%s\"\n", imageName.c_str());
	}
	else
	{
		if (verbose)
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
			imago::FileOutput fout(outputName.c_str());
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

std::string modifyConfig(const std::string& config, const LearningBase& learning, int iteration)
{
	imago::Settings vars;
	vars.fillFromDataStream(config);

	srand ( (unsigned int)time (NULL));

	imago::ReferenceAssignmentMap rmap;
	vars._fillReferenceMap(rmap);

	int changed = 0;

	double multiplier = 0.1 / log(double(iteration) + 1.79);

	for (imago::ReferenceAssignmentMap::const_iterator it = rmap.begin(); it != rmap.end(); it++)
	{
		double rand05 = (double)(rand() % RAND_MAX) / (double)RAND_MAX; // [0..0.5)
		double rand11 = (rand05 - 0.5) * 2.0; // [-1..1)

		switch (it->second.getType())
		{
		/*case imago::DataTypeReference::otBool: // TODO: temp
			{
			bool& value = *(it->second.getBool());
			bool new_value = rand05 >= 0.5;
			if (value != new_value)
			{
				value = new_value;
				changed++;
			}
			}
			break;

		case imago::DataTypeReference::otInt:
			{
			int& value = *(it->second.getInt());
			int new_value = (int)(value + value * rand11 * 0.05); // +-5%
			if (value != new_value)
			{
				value = new_value;
				changed++;
			}
			}
			break;*/

		case imago::DataTypeReference::otDouble:
			{
			double& value = *(it->second.getDouble());
			double new_value = value + value * rand11 * multiplier; // +- // TODO
			if (value != new_value)
			{
				value = new_value;
				changed++;
			}
			}
			break;
		}
	}

	printf("Learning: Config modified, changed %u values, multiplier: %g\n", changed, multiplier);

	std::string output;
	vars.saveToDataStream(output);
	return output;
}


void runSingleItem(LearningContext& ctx, LearningResultRecord& res, const std::string& image_name, bool init = false)
{
	imago::Settings temp_vars;				
	temp_vars.fillFromDataStream(res.config);
				
	unsigned int start_time = platform::TICKS();
				
	verbose = false;
	int action_error = performFileAction(temp_vars, image_name, "", ctx.output_file);
	verbose = true; // TODO: restore old value
		
	unsigned int end_time = platform::TICKS();		
	double work_time = end_time - start_time;
	
	double similarity = 0.0;

	try
	{
		similarity = getSimilarity(ctx);
				
		res.average_score += similarity;
		res.average_time += work_time;

		if (similarity >= 100.0 - imago::EPS)
		{
			res.ok_count++;
		}

		if (init)
			printf("%g (%g ms)\n", similarity, work_time);
	}
	catch(imago::FileNotFoundException &e)
	{
		printf("%s\n", e.what());
		ctx.valid = false;
	}

	ctx.vars = res.config;
	ctx.similarity = similarity;
	ctx.time = work_time;
	
	if (init)
	{
		ctx.attempts = 1;
		ctx.stability = (action_error == 0) ? 1.0 : 0.0;
		ctx.best_vars = res.config;
		ctx.best_similarity = similarity;
		ctx.average_time = work_time;
	}
	else
	{
		ctx.stability = (((action_error == 0) ? 1.0 : 0.0) + ctx.stability * ctx.attempts) / (ctx.attempts + 1);
		ctx.average_time = (work_time + ctx.average_time * ctx.attempts) / (ctx.attempts + 1);
		if (ctx.similarity > ctx.best_similarity)
		{
			ctx.best_similarity = ctx.similarity;
			ctx.best_vars = ctx.vars;
		}
		ctx.attempts++;
	}
}

bool updateResult(LearningResultRecord& result_record, LearningHistory& history)
{
	if (result_record.valid_count)
	{
		result_record.average_score /= result_record.valid_count;
		result_record.average_time /= result_record.valid_count;
		printf("Learning: result: %u vaild, %u ok, %g average score, %g ms average time\n",
			result_record.valid_count, result_record.ok_count, 
			result_record.average_score, result_record.average_time);
		history.push_back(result_record);
		return true;
	}
	else
	{
		return false;
	}
}

int performMachineLearning(imago::Settings& vars, const strings& imageSet, const std::string& configName)
{
	int result = 0; // ok mark
	
	try
	{
		LearningBase base;
		LearningHistory history;

		// step 0: prepare learning base
		{
			printf("Learning: filling learning base for %u images\n", imageSet.size());
			for (size_t u = 0; u < imageSet.size(); u++)
			{			
				const std::string& file = imageSet[u];

				LearningContext ctx;
				if (getReferenceFileName(file, ctx.reference_file))
				{
					try
					{
						imago::FileScanner fsc(ctx.reference_file.c_str());
					
						ctx.valid = true;
					}
					catch (imago::FileNotFoundException&)
					{
						printf("[ERROR] Can not open reference file: %s\n", ctx.reference_file.c_str());
					}
				}
				else
				{
					printf("[ERROR] Can not obtain reference filename for: %s\n", file.c_str());
				}

				// TODO: probably is better to place them in some temp folder
				ctx.output_file = file + ".temp.mol";

				base[file] = ctx;
			}
		} // end of step 0

		// step 1: get initial results
		{
			printf("Learning: getting initial results for %u images\n", base.size());
		
			int counter = 0;
			LearningResultRecord result_record;
			vars.saveToDataStream(result_record.config);

			for (LearningBase::iterator it = base.begin(); it != base.end(); it++)
			{
				counter++;

				printf("Image (%u/%u): %s... ", counter, base.size(), it->first.c_str());

				if (!it->second.valid)
				{
					printf("skipped\n");
				}
				else
				{				
					result_record.valid_count++;					
					runSingleItem(it->second, result_record, it->first, true /*init*/);
				}
			}

			if (!updateResult(result_record, history))
			{
				printf("[ERROR] No valid entries!\n");
				return 5;
			}
			
		} // end of step 1
		
		volatile bool work_continue = true;
		for (int work_iteration = 1; work_continue; work_iteration++)
		{
			// arrange configs by 
			std::sort(history.begin(), history.end());
			
			// remove the worst ones [non-optimal]
			while (history.size() >= LEARNING_MAX_CONFIGS)
				history.erase(history.begin());

			// check all N top configs
			int limit = (int)history.size() - LEARNING_TOP_USE;
			bool ok = false;
			int cfg_counter = 0;
			int cfg_best_idx = history.size() - 1;
			for (int cfg_id = cfg_best_idx; cfg_id >= 0 && cfg_id >= limit; cfg_id--)
			{
				cfg_counter++;
				printf("Learning: Work iteration %u:%u, selected the start config with score %g\n", work_iteration, cfg_counter, history[cfg_id].average_score);
				std::string base_config = history[cfg_id].config;

				LearningResultRecord res;
				res.config = modifyConfig(base_config, base, work_iteration);

				// now recheck the config
				unsigned int last_out_time = platform::TICKS();
				int counter = 0;

				for (LearningBase::iterator it = base.begin(); it != base.end(); it++)
				{
					counter++;

					if (it->second.valid)
					{									
						res.valid_count++;
						try
						{
							double avg_time = it->second.average_time;
							runSingleItem(it->second, res, it->first);
							if (it->second.time > 2.0 * avg_time &&
								it->second.time > LEARNING_ABNORMAL_TIME) // TODO
							{
								printf("Process takes too much time (%g vs %g) on image (%s), probably bad constants set, ignoring\n",
									   it->second.time, 
									   avg_time,
									   it->first.c_str());
								ok = true; // Temporary, TODO
								goto break_iteration;
							}
						}
						catch(...)
						{
							// TODO
						}

						if (platform::TICKS() - last_out_time > LEARNING_VERBOSE_TIME)
						{
							printf("Image (%u/%u): %s... %g\n", counter, base.size(), it->first.c_str(), it->second.similarity);
							last_out_time = platform::TICKS();
						}
					}
				}
				
				// update result entry
				if (updateResult(res, history))
				{
					ok = true;
				}

				if (history[cfg_best_idx] < res)
				{
					printf("Learning: --- Got better result (%g), saving\n", res.average_score);
					imago::VirtualFS vfs;
					char filename[imago::MAX_TEXT_LINE];		
					sprintf(filename, "config_%g.txt", res.average_score);
					vfs.appendData(filename, res.config);
					vfs.storeOnDisk();
				}

				break_iteration: continue;
			}

			if (!ok)
			{
				printf("Learning: no more learning success, exiting.\n");
				work_continue = false;
			}			
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
	std::string sim_tool = "";
	std::string sim_param = "";

	imago::Settings vars;

	bool next_arg_dir = false;
	bool next_arg_config = false;
	bool next_arg_sim_tool = false;
	bool next_arg_sim_param = false;
	
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

		else if (param == "-similarity")
			next_arg_sim_tool = true;

		else if (param == "-sparam")
			next_arg_sim_param = true;		

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

	setExternalSimilarityTool(sim_tool, sim_param);
	
	imago::getLogExt().setLoggingEnabled(vars.general.LogEnabled);
	
	if (!dir.empty())
	{
		strings files;
		
		if (getDirectoryContent(dir, files, recursive) != 0)
		{
			printf("[ERROR] Can't get the content of directory \"%s\"\n", dir.c_str());
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
				{
					printf("Skipped file '%s'\n", files[u].c_str());
				}
				else
				{
					std::string output = files[u] + ".result.mol";
					performFileAction(vars, files[u], config, output);	
				}
			}
		}
	}
	else if (!image.empty())
	{
		return performFileAction(vars, image, config);	
	}		
	
	return 1; // "nothing to do" error
}
