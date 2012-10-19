#include "machine_learning.h"
#include <time.h>
#include "platform_tools.h"
#include "exception.h"
#include "recognition_helpers.h"
#include "similarity_tools.h"
#include "scanner.h"
#include "output.h"
#include "virtual_fs.h"

namespace machine_learning
{
	const double LEARNING_ABNORMAL_TIME = 2500;          /* ms, time to assume there's something wrong */ 
	const double LEARNING_SUSPICIOUS_TIME_FACTOR = 2.0;  /* abs, if current time > average * this_const then probably constant set is bad */
	const int    LEARNING_MAX_CONFIGS = 20;              /* abs, maximal configs stored in history */
	const int    LEARNING_TOP_USE = 3;                   /* abs, maximal best configs count to branch from them */
	const int    LEARNING_VERBOSE_TIME = 15000;          /* ms, print on screen progress every such time */
	const double LEARNING_MULTIPLIER_BASE = 0.1;         /* %, constants variation threshold */
	const double LEARNING_LOG_START = 2.79;              /* abs, constants variation logarithmic base */
	const double LEARNING_QUICKCHECK_BASE_PERCENT = 0.1; /* %, target percent of whole images set to perform the quickcheck */
	const int    LEARNING_QUICKCHECK_MAX_COUNT = 30;     /* abs, maximal count of quickcheck subset */
	const double LEARNING_PERCENT_OF_CONSTS_TO_CHANGE = 0.1; /* % */

	double getWorstAllowedDelta(int imagesCount)  /* %, worst similarity delta (in average) allowed for further checks */
	{
		if (imagesCount < LEARNING_QUICKCHECK_MAX_COUNT)
			return -0.3;
		else if (imagesCount < 100)
			return -0.2;
		else if (imagesCount < 1000)
			return -0.15;
		else
			return -0.1;
	}

	double frand()
	{
		return (double)(rand() % RAND_MAX) / (double)RAND_MAX; // [0..1)
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
			if (frand() > LEARNING_PERCENT_OF_CONSTS_TO_CHANGE)
				continue;

			double rand_11 = (frand() - 0.5) * 2.0; // [-1..1)
			double rand_mp = rand_11 * multiplier;

			switch (it->second.getType())
			{
			case imago::DataTypeReference::otBool: 
				{
					bool& value = *(it->second.getBool());
					bool new_value = rand_11 >= 0.0;
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
					double addition = value * rand_mp;
					if (imago::absolute(addition) < 1.0)
					{
						if (addition < 0.0)
							addition = -1.0;
						else
							addition = +1.0;
					}
					int new_value = (int)(value + addition);
					if (value != new_value)
					{
						value = new_value;
						changed++;
					}
				}
				break;

			case imago::DataTypeReference::otDouble:
				{
					double& value = *(it->second.getDouble());
					double new_value = value + value * rand_mp;
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

	void runSingleItem(LearningContext& ctx, LearningResultRecord& res, const std::string& image_name, int timelimit_value, bool init)
	{
		int action_error = 0;
		double cur_work_time = 0.0;
		double cur_similarity = 0.0;

		{
			imago::Settings temp_vars;				
			temp_vars.fillFromDataStream(res.config);
			temp_vars.general.TimeLimit = timelimit_value;				
			
			unsigned int start_time = platform::TICKS();				
			action_error = recognition_helpers::performFileAction(false, temp_vars, image_name, "", ctx.output_file);				
			unsigned int end_time = platform::TICKS();		
			cur_work_time = end_time - start_time;
		}		

		if (cur_work_time > timelimit_value)
		{
			if (init)
			{
				printf("TL: %g ms\n", cur_work_time);
				ctx.valid = false; // not valid for learning
			}
		}
		else
		{
			try
			{
				cur_similarity = similarity_tools::getSimilarity(ctx);
				if (init)
				{
					printf("%g (%g ms)\n", cur_similarity, cur_work_time);
				}
			}
			catch(imago::ImagoException &e)
			{
				printf("%s\n", e.what());
				if (init)
					ctx.valid = false;
			}
		}

		res.average_score += cur_similarity;
		res.average_time += cur_work_time;

		if (cur_similarity >= 100.0 - imago::EPS)
		{
			res.ok_count++;
		}
			
		double cur_stability = (action_error == 0) ? 1.0 : 0.0;

		if (init)
		{
			ctx.attempts = 1;
			ctx.stability = cur_stability;
			ctx.score_stability = 1.0;
			ctx.best_similarity_achieved = cur_similarity;
			ctx.average_time = cur_work_time;
		}
		else
		{
			double cur_score_stability = (imago::absolute(ctx.similarity - cur_similarity) < imago::EPS) ? 1.0 : 0.0;
			ctx.stability = (cur_stability + ctx.stability * ctx.attempts) / (ctx.attempts + 1);
			ctx.score_stability = (cur_score_stability + ctx.score_stability * ctx.attempts) / (ctx.attempts + 1);
			ctx.average_time = (cur_work_time + ctx.average_time * ctx.attempts) / (ctx.attempts + 1);			
			ctx.attempts++;
		}

		ctx.similarity = cur_similarity;
		ctx.time = cur_work_time;
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

	bool storeConfig(const LearningResultRecord& res, const std::string& prefix)
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

	const int LEARNING_PROGRESSFILE_MAGIC = 57005;

	bool readLearningProgress(LearningBase& base, LearningHistory& history, bool quiet, const std::string& filename)
	{
		try
		{
			imago::FileScanner fi("%s", filename.c_str());

			if (fi.readBinaryInt() != LEARNING_PROGRESSFILE_MAGIC)
				throw imago::ImagoException("Wrong progress file header");
			int base_count = fi.readBinaryInt();

			for (int i = 0; i < base_count; i++)
			{	
				std::string name;
				fi.readBinaryString(name);
				LearningContext temp;
				fi.readBinaryString(temp.reference_file);
				fi.readBinaryString(temp.output_file);
				temp.valid = fi.readBinaryInt() != 0;
				temp.attempts = fi.readBinaryInt();
				temp.average_time = fi.readBinaryDouble();
				temp.time = fi.readBinaryDouble();
				temp.best_similarity_achieved = fi.readBinaryDouble();
				temp.similarity = fi.readBinaryDouble();
				temp.stability = fi.readBinaryDouble();
				temp.score_stability = fi.readBinaryDouble();
				base[name] = temp;
			}			

			if (fi.readBinaryInt() != LEARNING_PROGRESSFILE_MAGIC)
				throw imago::ImagoException("Progress file is probably damaged");
			int history_count = fi.readBinaryInt();

			for (int i = 0; i < history_count; i++)
			{
				LearningResultRecord res;
				res.work_iteration = fi.readBinaryInt();
				res.valid_count = fi.readBinaryInt();
				res.ok_count = fi.readBinaryInt();
				res.average_score = fi.readBinaryDouble();
				res.average_time = fi.readBinaryDouble();
				fi.readBinaryString(res.config);
				history.push_back(res);
			}

			if (fi.readBinaryInt() != LEARNING_PROGRESSFILE_MAGIC)
				throw imago::ImagoException("Progress file has bad ending");

			return true;
		}
		catch (imago::ImagoException &e)
		{
			if (!quiet)
			{
				printf("readLearningProgress exception: '%s'\n", e.what());
			}
		}
		return false;
	}

	bool storeLearningProgress(const LearningBase& base, const LearningHistory& history, const std::string& filename)
	{
		try
		{
			imago::FileOutput fo("%s", filename.c_str());
			fo.writeBinaryInt(LEARNING_PROGRESSFILE_MAGIC);
			fo.writeBinaryInt(base.size());
			for (LearningBase::const_iterator it = base.begin(); it != base.end(); it++)
			{		
				fo.writeBinaryString(it->first.c_str());
				fo.writeBinaryString(it->second.reference_file.c_str());
				fo.writeBinaryString(it->second.output_file.c_str());
				fo.writeBinaryInt(it->second.valid);
				fo.writeBinaryInt(it->second.attempts);
				fo.writeBinaryDouble(it->second.average_time);
				fo.writeBinaryDouble(it->second.time);
				fo.writeBinaryDouble(it->second.best_similarity_achieved);
				fo.writeBinaryDouble(it->second.similarity);
				fo.writeBinaryDouble(it->second.stability);
				fo.writeBinaryDouble(it->second.score_stability);
			}			
			fo.writeBinaryInt(LEARNING_PROGRESSFILE_MAGIC);
			fo.writeBinaryInt(history.size());
			for (LearningHistory::const_iterator it = history.begin(); it != history.end(); it++)
			{
				fo.writeBinaryInt(it->work_iteration);
				fo.writeBinaryInt(it->valid_count);
				fo.writeBinaryInt(it->ok_count);
				fo.writeBinaryDouble(it->average_score);
				fo.writeBinaryDouble(it->average_time);
				fo.writeBinaryString(it->config.c_str());
			}
			fo.writeBinaryInt(LEARNING_PROGRESSFILE_MAGIC);
			printf("[Learning] Temporary learning progress is stored.\n");
			return true;
		}
		catch (imago::ImagoException &e)
		{
			printf("storeLearningProgress exception: '%s'\n", e.what());
			printf("[Learning] Failed to store temporary learning progress!\n");
		}
		return false;
	}

	int performMachineLearning(imago::Settings& vars, const strings& imageSet, const std::string& configName)
	{
		int result = 0; // ok mark
		int timelimit_default_value = vars.general.TimeLimit;
	
		try
		{
			LearningBase base;
			LearningHistory history;
			int work_iteration = 1;
			
			bool progress_loaded = false;

			if (readLearningProgress(base, history, true))
			{
				printf("[Learning] Loaded previous progress (%u, %u)\n", base.size(), history.size());

				if (base.size() != imageSet.size())
				{
					printf("[Learning] But image set is changed, recalculation is required\n");
				}
				else
				{
					// estimate work_iteration
					for (LearningHistory::const_iterator it = history.begin(); it != history.end(); it++)
						if (it->work_iteration > work_iteration)
							work_iteration = it->work_iteration;
					printf("[Learning] Estimated start work iteration: %u\n", work_iteration);
					progress_loaded = true;
				}
			}
			
			if (!progress_loaded)
			{
				base.clear();
				history.clear();

				// step 0: prepare learning base
				printf("[Learning] filling learning base for %u images\n", imageSet.size());
				for (size_t u = 0; u < imageSet.size(); u++)
				{			
					const std::string& file = imageSet[u];

					LearningContext ctx;
					if (file_helpers::getReferenceFileName(file, ctx.reference_file))
					{
						try
						{
							imago::FileScanner fsc("%s", ctx.reference_file.c_str());
					
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
				
				// step 1: get initial results
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
						runSingleItem(it->second, result_record, it->first, timelimit_default_value, true /*init*/);
						if (it->second.valid)
						{
							result_record.valid_count++;
						}
					}
				}

				if (updateResult(result_record, history))
				{
					storeConfig(result_record, "base");
					storeLearningProgress(base, history);
				}
				else
				{
					printf("[ERROR] No valid entries!\n");
					return 5;
				}				
				// end of step 1
			} // end if
		
			std::vector<LearningBase::iterator> valid_indexes;
			for (LearningBase::iterator it = base.begin(); it != base.end(); it++)
			{
				if (it->second.valid)
				{
					valid_indexes.push_back(it);					
				}
			}

			volatile bool work_continue = valid_indexes.size() > 0;
			for (; work_continue; work_iteration++)
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
					if (platform::checkMemoryFail())
					{
						printf("Out of memory, process exit\n");
						return 77;
					}

					cfg_counter++;
					printf("[Learning] Work iteration %u:%u, selected the start config with score %g\n", work_iteration, cfg_counter, history[cfg_id].average_score);
					std::string base_config = history[cfg_id].config;

					LearningResultRecord res;
					res.work_iteration = work_iteration;
					res.config = modifyConfig(base_config, base, work_iteration);

					// now recheck the config
					unsigned int last_out_time = platform::TICKS();					
					
					printf("[Learning] Sorting by stability... ");
					for (size_t i = 0; i < valid_indexes.size(); i++)
					{
						for (size_t j = i + 1; j < valid_indexes.size(); j++)
						{
							if (valid_indexes[i]->second.score_stability > valid_indexes[j]->second.score_stability)
							{
								LearningBase::iterator temp = valid_indexes[i];
								valid_indexes[i] = valid_indexes[j];
								valid_indexes[j] = temp;
							}
						}
					}
					printf("Done.\n");

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
								runSingleItem(it->second, res, it->first, timelimit_default_value);
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
									if (delta < getWorstAllowedDelta(count))
									{
										printf("[Learning] New results are probably worser, skipping\n");
										goto break_iteration;
									}
								}
							} // if LEARNING_VERBOSE_TIME
						} // for idx
					
						printf("[Learning] Got delta: %g\n", delta);
						if (quick_check && delta < getWorstAllowedDelta(count))
						{
							printf("[Learning] Quickcheck results are worser, skipping\n");
							goto break_iteration;
						}
					}
				
					if (updateResult(res, history))
					{
						storeLearningProgress(base, history);
					}

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

}
