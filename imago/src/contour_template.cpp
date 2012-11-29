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

#include "contour_template.h"
#include <sstream>
#include <complex>

using namespace imago;

const int ContourTemplate::filter1[4] = {  1, 1, 1, 1 };
const int ContourTemplate::filter2[4] = { -1, -1, 1, 1 };
const int ContourTemplate::filter3[4] = { -1, 1, 1, -1 };
const int ContourTemplate::filter4[4] = { -1, 1, -1, 1 };


ContourTemplate::ContourTemplate(void)
{
}


ContourTemplate::~ContourTemplate(void)
{
}

void ContourTemplate::_calculateAutoCorrelation(ComplexContour& c, int* val)
{
	double cd[] = {0.0, 0.0, 0.0, 0.0};

	if(val == NULL || 
		(sizeof(val) != 4))
		throw LogicException("Not valid return parameter or size different from 4");


	std::vector<ComplexNumber> autoCorr = c.AutoCorrelation(true);
	int count = autoCorr.size();
	for (int i = 0; i < count; i++)
	{
		double v = autoCorr[i].getRadius();
		int j = 4*(i + 0.0)/count;
  
		cd[0] += filter1[j] * v;
		cd[1] += filter2[j] * v;
		cd[2] += filter3[j] * v;
		cd[3] += filter4[j] * v;
	}
  
	for(int i =0;i<4;i++)
		val[i] = (int)(100 * cd[i] / count);
}

//double ContourTemplate::CompareInterCorrelation(ComplexContour c)
//{
//	double rate = 0;
//	
//	return rate;
//}
//
//double ContourTemplate::CompareAutoCorrelation(ComplexContour c)
//{
//	double rate = 0;
//
//	return rate;
//}

TemplateFound TemplateComparer::Find(ComplexContour &c, char &ch)
{
	double maxIRate = 0;
	double maxARate = 0;
	std::deque<ContourTemplate>::iterator tit;
	TemplateFound retVal;


	for(tit = _temps.begin(); tit != _temps.end(); tit++)
	{
		ContourTemplate ct = *tit;
		int td[4], sd[4];

		ComplexContour tempc = c;
		tempc.Equalize(ct.GetContourSize());//ct.getContour().Size());
		tempc.NormalizeByPerimeter();
		
		ContourTemplate::_calculateAutoCorrelation(ct.getContour(), td);
		ContourTemplate::_calculateAutoCorrelation(tempc, sd);

		int maxdescdiff = 0;
		for(int i=0;i<4;i++)
			if( imago::absolute(sd[i] - td[i]) > maxdescdiff)
				maxdescdiff = imago::absolute(sd[i] - td[i]);
		/*if(maxdescdiff > imago::maxACFDescriptorDeviation)
			continue;*/
		

		ComplexContour actempc = tempc.AutoCorrelation(true);
		ComplexContour ctempc(ct.getContour().AutoCorrelation(true));
		double arate = ctempc.NormDot(actempc).getRadius();
		retVal._autoCorrDiffRate = arate;

		std::vector<ComplexNumber> icf = tempc.InterCorrelation(ct.getContour());
		ComplexContour cicf(icf);
		ComplexNumber fmn = cicf.FindMaxNorm();
		double irate = fmn.getRadius() / (ct.getContour().getNorm()  * tempc.getNorm());
		if(irate > maxIRate)
		{
			retVal._autoCorrDiffRate = arate;
			retVal._interCorrRate = irate;
			retVal._acfddeviation[0] = imago::absolute(sd[0] - td[0]);
			retVal._acfddeviation[1] = imago::absolute(sd[1] - td[1]);
			retVal._acfddeviation[2] = imago::absolute(sd[2] - td[2]);
			retVal._acfddeviation[3] = imago::absolute(sd[3] - td[3]);
			retVal._angle = fmn.getAngle();
			maxIRate = irate;
			ch = ct.getChar();
		}
	}

	return retVal;
}

void TemplateComparer::LoadTemplates()
{
	/*std::string fontdata;
   extern const char *_imago_fontshapedata[];
   for (int i = 0; _imago_fontshapedata[i] != 0; ++i)
      fontdata += _imago_fontshapedata[i];

   std::istringstream in(fontdata);

   _temps.clear();

   int cont_count;
   in >> cont_count;
   for(int i=0; i < cont_count; i++)
   {
	   int contour_length;
	   std::vector<ComplexNumber> contour;
	   in >> contour_length;
	   for(int j = 0; j< contour_length/2; j++)
	   {
		   double varR, varI;
		   in >> varR;
		   in >> varI;
		   contour.push_back(ComplexNumber(varR, varI));
	   }
	   ComplexContour cc(contour);
	   cc.Normalize();
	   _temps.push_back(ContourTemplate(cc));
   }*/
	_temps.clear();
	_temps.push_back(ContourTemplate(ComplexContour("-5 2 -8 15 -1 10 4 13 0 -21 10 -19"), '('));
	_temps.push_back(ContourTemplate(ComplexContour("1 4 10 1 1 43 -12 4 13 2 3 -3 0 -49 -16 -2"), ']'));
	_temps.push_back(ContourTemplate(ComplexContour("0 50 3 3 10 0 3 -2 -13 -5 0 -41 13 -5 -16 0"), '['));
	_temps.push_back(ContourTemplate(ComplexContour("0 50 13 3 -10 -7 0 -41 11 -6 -14 1"), '['));
	_temps.push_back(ContourTemplate(ComplexContour("0 19 -10 21 5 -3 7 -12 1 -18 -3 -7"), ')'));
}