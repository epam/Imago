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

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
#include <map>
#include <cmath>
#include <cfloat>
#include <deque>
#include <opencv2/opencv.hpp>

#include "stl_fwd.h"
#include "small_character_recognizer.h"
#include "segment.h"
#include "exception.h"
#include "scanner.h"
#include "segmentator.h"
#include "thin_filter2.h"
#include "image_utils.h"
#include "log_ext.h"
#include "recognition_tree.h"
#include "character_endpoints.h"
#include "prefilter.h" // line thickness estimation, isCircle
#include "settings.h"



using namespace imago;

std::vector<SmallCharRecognizer::CharRecord> SmallCharRecognizer::_data;

struct CharScoreRec
{
	char character;
	double score;
};

bool CompareChars(CharScoreRec csr1, CharScoreRec csr2)
{
	return csr1.score < csr2.score;
}

IntDeque SmallCharRecognizer::calc_template(const Segment* seg)
{
	imago::Segment resImg;
	cv::Mat cv_img, cv_reimg(15, 10, CV_8U);
	imago::ImageUtils::copyImageToMat(*seg, cv_img);
	cv::resize(cv_img, cv_reimg, cv_reimg.size()) ;

	imago::IntDeque img_templ;

	for(int i = 0; i < cv_reimg.cols; i++)
		for(int j = 0; j < cv_reimg.rows; j++)
			img_templ.push_back(cv_reimg.at<unsigned char>(cv::Point(i, j)));
	return img_templ;
}

char SmallCharRecognizer::Recognize(const Settings& vars, const Segment *seg)
{
	char retVal = 0;
	std::vector<CharRecord>::iterator crit;
	std::vector<CharScoreRec> results;
	std::vector<CharScoreRec>::iterator ires;
	
	IntDeque temp = calc_template(seg);
	for(crit = _data.begin(); crit != _data.end(); crit++)
	{
		CharRecord cr = (*crit);
		double score = 0;

		for(size_t i = 0; i < cr.templates.size(); i++)
		{
			int val = cr.templates[i];
			int tval = temp[i];
			score += (val - tval) * (val - tval);
		}
		
		CharScoreRec csrRes;
		csrRes.character = cr.Character;
		csrRes.score = score;
		results.push_back(csrRes);
	}

	std::sort(results.begin(), results.end(), CompareChars);

	if(results[0].score > vars.characters.SmallLetterRecogThreshold)
		return -1;

	std::map<char, double> char_score;
	for(ires = results.begin(); ires != results.end(); ires++)
	{
		char_score[(*ires).character] = 0.0;
	}

	for(ires = results.begin(); ires != results.end() && ires != (results.begin() + 5); ires++) // warning: 5 is the number of closest neighbours
	{
		double s = (*ires).score;
		char_score[(*ires).character] += 1.0 / (s < imago::EPS ? imago::SMALL_EPS : s ) ;
	}

	double score_max = 0;

	for(ires = results.begin(); ires != results.end(); ires++)
	{
		if(char_score[(*ires).character] > score_max)
		{
			score_max = char_score[(*ires).character];
			retVal = (*ires).character;
		}
	}
	return retVal;
}

void SmallCharRecognizer::_loadData( std::istream &in )
{
	char currentChar;
	int templateCount;
	CharRecord currRec;
	std::vector<int> tempEls;
	do
	{
		in >> currentChar >> templateCount;
		currRec.Character = currentChar;
		for(int i = 0; i < templateCount; i++)
		{
			int tempEl;
			for(int j = 0; j < 150; j++) // warning: 150 could change
			{
				in >> tempEl;
				currRec.templates.push_back(tempEl);
			}
			
			_data.push_back(currRec);
			currRec.templates.clear();
		}
		
	}while(!in.eof());
}