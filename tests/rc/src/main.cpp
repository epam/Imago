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
#include <iterator>
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


static int   LEARNING_VAR_TIMELIMIT = 10000;         /* ms, maximal time to process single image */
const double LEARNING_ABNORMAL_TIME = 2500;          /* ms, time to assume there's something wrong */ 
const double LEARNING_SUSPICIOUS_TIME_FACTOR = 2.0;  /* abs, if current time > average * this_const then probably constant set is bad */
const int    LEARNING_MAX_CONFIGS = 20;              /* abs, maximal configs stored in history */
const int    LEARNING_TOP_USE = 3;                   /* abs, maximal best configs count to branch from them */
const int    LEARNING_VERBOSE_TIME = 15000;          /* ms, print on screen progress every such time */
const double LEARNING_MULTIPLIER_BASE = 0.1;         /* %, constants variation threshold */
const double LEARNING_LOG_START = 2.79;              /* abs, constants variation logarithmic base */
const double LEARNING_QUICKCHECK_BASE_PERCENT = 0.1; /* %, target percent of whole images set to perform the quickcheck */
const int    LEARNING_QUICKCHECK_MAX_COUNT = 10;     /* abs, maximal count of quickcheck subset */
const double LEARNING_WORST_DELTA_ALLOWED = -1.0;    /* %, worst similarity delta (in average) allowed for further checks */
const double LEARNING_SUSPICIOUS_DELTA_FACTOR = 2.0; /* abs, factor for current similarity delta allowed */


void dumpVFS(imago::VirtualFS& vfs, const std::string& filename)
{
	// store all the vfs contents in one single file (including html, images, etc)
	if (!vfs.empty())
	{
		imago::FileOutput filedump(filename.c_str());
		std::vector<char> data;		
		vfs.getData(data); 
		filedump.write(&data.at(0), data.size());
	}
}

void applyConfig(bool verbose, imago::Settings& vars, const std::string& config)
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

RecognitionResult recognizeImage(bool verbose, imago::Settings& vars, const imago::Image& src, const std::string& config)
{
	std::vector<RecognitionResult> results;
		
	imago::ChemicalStructureRecognizer _csr;
	imago::Molecule mol;

	for (int iter = 0; ; iter++)
	{
		bool good = false;

		vars.general.StartTime = 0;

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

			applyConfig(verbose, vars, config);
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
				printf("Filter [%u] exception '%s'.\n", vars.general.FilterIndex, e.what());

	#ifdef _DEBUG
			throw;
	#endif
		}

		if (good)
			break;
	} // for

	RecognitionResult result;
	result.warnings = 999; // just big number to override
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


int performFileAction(bool verbose, imago::Settings& vars, const std::string& imageName, const std::string& configName,
	                  const std::string& outputName = "molecule.mol")
{
	int result = 0; // ok mark
	imago::VirtualFS vfs;

	if (vars.general.ExtractCharactersOnly)
	{
		if (verbose)
			printf("Characters extraction from image '%s'\n", imageName.c_str());
	}
	else
	{
		if (verbose)
			printf("Recognition of image '%s'\n", imageName.c_str());
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
			applyConfig(verbose, vars, configName);
			imago::ChemicalStructureRecognizer _csr;
			_csr.extractCharacters(vars, image);
		}
		else
		{
			RecognitionResult result = recognizeImage(verbose, vars, image, configName);		
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

	dumpVFS(vfs, "log_vfs.txt");

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

	double multiplier = LEARNING_MULTIPLIER_BASE / log(double(iteration) + LEARNING_LOG_START);

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
			double new_value = value + value * rand11 * multiplier;
			if (value != new_value)
			{
				value = new_value;
				changed++;
			}
			}
			break;
		}
	}

	printf("[Learning] Config modified, changed %u values, multiplier: %g\n", changed, multiplier);

	std::string output;
	vars.saveToDataStream(output);
	return output;
}

void runSingleItem(LearningContext& ctx, LearningResultRecord& res, const std::string& image_name, bool init = false)
{
	imago::Settings temp_vars;				
	temp_vars.fillFromDataStream(res.config);
	temp_vars.general.TimeLimit = LEARNING_VAR_TIMELIMIT;
				
	unsigned int start_time = platform::TICKS();				
	int action_error = performFileAction(false, temp_vars, image_name, "", ctx.output_file);				
	unsigned int end_time = platform::TICKS();		

	double work_time = end_time - start_time;
	bool timelimit = work_time > LEARNING_VAR_TIMELIMIT;
	
	double similarity = 0.0;

	try
	{
		similarity = timelimit ? 0.0 : getSimilarity(ctx);
				
		res.average_score += similarity;
		res.average_time += work_time;

		if (similarity >= 100.0 - imago::EPS)
		{
			res.ok_count++;
		}

		if (init)
		{
			if (timelimit)
			{
				printf("TL: %g ms\n", work_time);
			}
			else
			{
				printf("%g (%g ms)\n", similarity, work_time);
			}
		}
	}
	catch(imago::FileNotFoundException &e)
	{
		printf("%s\n", e.what());
		if (init)
			ctx.valid = false;
	}

	if (timelimit && init)
		ctx.valid = false; // not valid for learning

	ctx.similarity = similarity;
	ctx.time = work_time;
	
	if (init)
	{
		ctx.attempts = 1;
		ctx.stability = (action_error == 0) ? 1.0 : 0.0;
		ctx.best_similarity_achieved = similarity;
		ctx.average_time = work_time;
	}
	else
	{
		ctx.stability = (((action_error == 0) ? 1.0 : 0.0) + ctx.stability * ctx.attempts) / (ctx.attempts + 1);
		ctx.average_time = (work_time + ctx.average_time * ctx.attempts) / (ctx.attempts + 1);
		ctx.attempts++;
	}
}

bool updateResult(LearningResultRecord& result_record, LearningHistory& history)
{
	if (result_record.valid_count)
	{
		result_record.average_score /= result_record.valid_count;
		result_record.average_time /= result_record.valid_count;
		printf("[Learning] result: %u vaild, %u ok, %g average score, %g ms average time\n",
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

bool storeConfig(const LearningResultRecord& res, const std::string& prefix = "")
{
	try
	{
		imago::VirtualFS vfs;
		char filename[imago::MAX_TEXT_LINE];		
		sprintf(filename, "%sconfig_%uOK_%g.txt", prefix.c_str(), res.ok_count, res.average_score);
		vfs.appendData(filename, res.config);
		vfs.storeOnDisk();
	}
	catch (imago::ImagoException &e)
	{
		printf("storeConfig exception: '%s'\n", e.what());
		return false;
	}
	return true;
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
			printf("[Learning] filling learning base for %u images\n", imageSet.size());
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
						printf("[ERROR] Can not open reference file: '%s'\n", ctx.reference_file.c_str());
					}
				}
				else
				{
					printf("[ERROR] Can not obtain reference filename for: '%s'\n", file.c_str());
				}

				// TODO: probably is better to place them in some temp folder
				ctx.output_file = file + ".temp.mol";

				base[file] = ctx;
			}
		} // end of step 0

		// step 1: get initial results
		{
			printf("[Learning] getting initial results for %u images\n", base.size());
		
			int visual_counter = 0;
			LearningResultRecord result_record;
			vars.saveToDataStream(result_record.config);

			for (LearningBase::iterator it = base.begin(); it != base.end(); it++)
			{
				printf("Image (%u/%u): %s... ", ++visual_counter, base.size(), it->first.c_str());

				if (!it->second.valid)
				{
					printf("skipped\n");
				}
				else
				{									
					runSingleItem(it->second, result_record, it->first, true /*init*/);
					if (it->second.valid)
					{
						result_record.valid_count++;
					}
				}
			}

			if (!updateResult(result_record, history))
			{
				printf("[ERROR] No valid entries!\n");
				return 5;
			}

			storeConfig(result_record, "base");
			
		} // end of step 1
		
		volatile bool work_continue = true;
		for (int work_iteration = 1; work_continue; work_iteration++)
		{
			// arrange configs by OK count, then by similarity
			std::stable_sort(history.begin(), history.end());
			
			// remove the worst ones [non-optimal]
			while (history.size() >= LEARNING_MAX_CONFIGS)
				history.erase(history.begin());

			// check all N top configs
			int limit = (int)history.size() - LEARNING_TOP_USE;
			int cfg_counter = 0;
			int cfg_best_idx = history.size() - 1;

			for (int cfg_id = cfg_best_idx; cfg_id >= 0 && cfg_id >= limit; cfg_id--)
			{
				cfg_counter++;
				printf("[Learning] Work iteration %u:%u, selected the start config with score %g\n", work_iteration, cfg_counter, history[cfg_id].average_score);
				std::string base_config = history[cfg_id].config;

				LearningResultRecord res;
				res.config = modifyConfig(base_config, base, work_iteration);

				// now recheck the config
				unsigned int last_out_time = platform::TICKS();				

				std::vector<LearningBase::iterator> valid_indexes;
				for (LearningBase::iterator it = base.begin(); it != base.end(); it++)
				{
					if (it->second.valid)
					{
						valid_indexes.push_back(it);					
					}
				}
				std::random_shuffle(valid_indexes.begin(), valid_indexes.end());

				int qc_pos = int(LEARNING_QUICKCHECK_BASE_PERCENT * (double)(valid_indexes.size()));
				if (qc_pos == 0)
					qc_pos = 1;
				if (qc_pos > LEARNING_QUICKCHECK_MAX_COUNT)
					qc_pos = LEARNING_QUICKCHECK_MAX_COUNT;
				
				double delta = 0.0;

				for (int subset = 0; subset < 2; subset++)
				{					
					size_t start_idx = 0; 
					size_t end_idx = valid_indexes.size();

					bool quick_check = subset == 0;

					if (quick_check)
					{
						end_idx = qc_pos;
						printf("[Learning] Quick pre-check (%u images)...\n", end_idx - start_idx);
						
					}
					else
					{
						start_idx = qc_pos;
						printf("[Learning] Full check (%u images)...\n", end_idx - start_idx);
					}
					
					delta = 0.0;

					int count = end_idx - start_idx;

					for (size_t idx = start_idx; idx < end_idx; idx++)
					{
						LearningBase::iterator& it = valid_indexes[idx];

						int pos = idx-start_idx + 1;

						res.valid_count++;
						try
						{
							double avg_time = it->second.average_time;
							runSingleItem(it->second, res, it->first);
							if (quick_check &&
								it->second.time > LEARNING_SUSPICIOUS_TIME_FACTOR * avg_time &&
								it->second.time > LEARNING_ABNORMAL_TIME)
							{
								printf("Process takes too much time (%g vs %g) on image ('%s'), probably bad constants set, ignoring\n", it->second.time, avg_time, it->first.c_str());									
								goto break_iteration;
							}
							delta += (it->second.similarity - it->second.best_similarity_achieved) / (double)(count);
						}
						catch(...)
						{
							printf("Some exception in performMachineLearning() loop\n");
							// TODO: handle?
						}

						if (platform::TICKS() - last_out_time > LEARNING_VERBOSE_TIME)
						{
							last_out_time = platform::TICKS();
							printf("Image (%u/%u): %s... %g\n", pos, count, it->first.c_str(), it->second.similarity);
							if (!quick_check && pos > qc_pos) // count of processed is greater than pre-test collection
							{
								printf("[Learning] Current delta: %g; current OK count: %u\n", delta, res.ok_count);
								if (delta < LEARNING_SUSPICIOUS_DELTA_FACTOR * LEARNING_WORST_DELTA_ALLOWED)
								{
									printf("[Learning] New results are probably worser, skipping\n");
									goto break_iteration;
								}
							}
						} // if LEARNING_VERBOSE_TIME
					} // for idx
					
					printf("[Learning] Got delta: %g\n", delta);
					if (quick_check && delta < LEARNING_WORST_DELTA_ALLOWED)
					{
						printf("[Learning] Quickcheck results are worser, skipping\n");
						goto break_iteration;
					}
				}
				
				updateResult(res, history);

				if (history[cfg_best_idx] < res)
				{
					printf("[Learning] --- Got better result (%g, %u OK), saving\n", res.average_score, res.ok_count);
					storeConfig(res);

					// commit best_similarity_achieved:
					for (LearningBase::iterator it = base.begin(); it != base.end(); it++)
						it->second.best_similarity_achieved = it->second.similarity;
				}
				else
				{
					storeConfig(res, "bad/");
				}

				break_iteration: continue;
			} // for cfg_id
		} // while
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
		printf("  -tl time_in_ms: timelimit per single image process (default is %u) \n", LEARNING_VAR_TIMELIMIT);
		printf("\n  BATCHES: \n");
		printf("  -dir dir_name: process every image from dir dir_name \n");
		printf("    -rec: process directory recursively \n");
		printf("    -images: skip non-supported files from directory \n");				
		return 0;
	}

	imago::Settings vars;
	vars.general.TimeLimit = LEARNING_VAR_TIMELIMIT;

	std::string image = "";
	std::string dir = "";
	std::string config = "";
	std::string sim_tool = "";
	std::string sim_param = "";

	bool next_arg_dir = false;
	bool next_arg_config = false;
	bool next_arg_sim_tool = false;
	bool next_arg_sim_param = false;
	bool next_arg_tl = false;	

	bool mode_recursive = false;
	bool mode_pass = false;
	bool mode_learning = false;
	bool mode_filter = false;

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

		else if (param == "-tl")
			next_arg_tl = true;

		else if (param == "-similarity")
			next_arg_sim_tool = true;

		else if (param == "-sparam")
			next_arg_sim_param = true;		

		else if (param == "-r" || param == "-rec")
			mode_recursive = true;

		else if (param == "-i" || param == "-images")
			mode_filter = true;

		else if (param == "-learn" || param == "-optimize")
			mode_learning = true;

		else if (param == "-pass")
			mode_pass = true;

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
			else if (next_arg_tl)
			{
				LEARNING_VAR_TIMELIMIT = vars.general.TimeLimit = atoi(param.c_str());
				next_arg_tl = false;
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
					if (image.empty())
					{
						image = param;
					}
					else
					{
						printf("Image file is already specified ('%s'), the second definition unallowed ('%s')\n", image.c_str(), param.c_str());
						return 1;
					}
				}
			}
		}
	}

	setExternalSimilarityTool(sim_tool, sim_param);
	
	imago::getLogExt().setLoggingEnabled(vars.general.LogEnabled);
	
	if (!dir.empty())
	{
		strings files;
		
		if (getDirectoryContent(dir, files, mode_recursive) != 0)
		{
			printf("[ERROR] Can't get the content of directory '%s'\n", dir.c_str());
			return 2;
		}

		if (mode_filter || mode_learning)
		{
			filterOnlyImages(files);
		}

		if (mode_learning)
		{			
			return performMachineLearning(vars, files, config);
		}
		else // process or pass
		{
			for (size_t u = 0; u < files.size(); u++)
			{
				if (mode_pass)
				{
					printf("Skipped file '%s'\n", files[u].c_str());
				}
				else
				{
					std::string output = files[u] + ".result.mol";
					performFileAction(true, vars, files[u], config, output);	
				}
			}
		}
	}
	else if (!image.empty()) // process single file
	{
		return performFileAction(true, vars, image, config);	
	}		
	
	return 1; // "nothing to do" error
}
