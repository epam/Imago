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
 * @file   contour_template.h
 * 
 * @brief  Template for ComplexContours
 */

#pragma once
#ifndef _contour_template_h
#define _contour_template_h

#include "complex_contour.h"

namespace imago
{
	const int maxACFDescriptorDeviation = 4;

	class ContourTemplate
	{
	public:
		ContourTemplate(void);
		~ContourTemplate(void);
		ContourTemplate(ComplexContour cont):_contour(cont)
		{
			CONTOUR_SIZE = 40;
			_contour.Equalize(CONTOUR_SIZE);
			_contour.Normalize();
			_calculateAutoCorrelation(_contour, _acf);
		}

		ComplexContour& getContour()
		{
			return _contour;
		}
		////return the rate of similarity
		//double CompareInterCorrelation(ComplexContour c);

		//double CompareAutoCorrelation(ComplexContour c);
		void SaveTemplate();
		void LoadTemplate();
		int GetContourSize() const
		{
			return CONTOUR_SIZE;
		}
		
		static void _calculateAutoCorrelation(ComplexContour& c, int *val);
	private:
		

		static const int filter1[4];
		static const int filter2[4];
		static const int filter3[4];
		static const int filter4[4];

		int CONTOUR_SIZE;
		
		int _acf[4];

		ComplexContour _contour;
	};

	struct TemplateFound
	{
		TemplateFound()
		{
			int maxdev = imago::maxACFDescriptorDeviation + 1;
			for(int i=0;i<4;i++)
				_acfddeviation[i] = maxdev;
			_interCorrRate = 0.0;
			_autoCorrDiffRate = 0.0;
			_angle = -1.0;
		}
		// auto correlation function descriptor deviations
		int _acfddeviation[4];
		double _interCorrRate;
		double _autoCorrDiffRate;
		double _angle;
	};

	class TemplateComparer{
	public:
		void LoadTemplates();

		TemplateFound Find(ComplexContour c);

	private:
		std::deque<ContourTemplate> _temps;

	};

}

#endif