/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
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

/**
 * @file HistogramTools.h
 * 
 * @brief   Defines histogram methods on image
 */
#ifndef HistogramTools_h_
#define HistogramTools_h_

#include "image.h"
#include <opencv/cv.h>

namespace imago
{
	class HistogramTools
	{
	public:
		HistogramTools(cv::Mat &img);
		~HistogramTools(void){}
		void ImageAdjust(cv::Mat &result, bool Sigmoid = false);
	private:
		void GetStretchLimits(float &lowLim, float &highLim);
		float _lowLim, _hiLim;
		cv::Mat _image;
		HistogramTools(){}
	};
}
#endif