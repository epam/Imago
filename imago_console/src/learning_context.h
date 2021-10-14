/****************************************************************************
* Copyright (C) from 2009 to Present EPAM Systems.
*
* This file is part of Imago toolkit.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***************************************************************************/

#pragma once

#ifndef _learning_context_h
#define _learning_context_h

#include <string>
#include <vector>
#include <map>

struct LearningContext
{
	bool valid;

	double similarity;
	//std::string vars;
	
	double best_similarity_achieved;
	//std::string best_vars;
	
	std::string reference_file;
	std::string output_file;
		
	double stability;
	double score_stability;

	double time;
	double average_time;

	int attempts;

	LearningContext()
	{
		valid = false;
		similarity = best_similarity_achieved = 0.0;
		score_stability = stability = 1.0;
		time = average_time = 0.0;
		attempts = 0;
	}
};

typedef std::map<std::string, LearningContext> LearningBase;

struct LearningResultRecord
{
	std::string config;
	double average_time;
	double average_score;
	int ok_count;
	int valid_count;
	int work_iteration;

	bool operator<(const LearningResultRecord& second) const
	{
		return ok_count < second.ok_count ||
			      (ok_count == second.ok_count &&
				   average_score < second.average_score);
	}

	LearningResultRecord()
	{
		average_time = average_score = 0.0;
		work_iteration = ok_count = valid_count = 0;		
	}
};

typedef std::vector<LearningResultRecord> LearningHistory;

#endif // _learning_context_h
