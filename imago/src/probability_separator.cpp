#include "probability_separator.h"

using namespace imago;

double jointPS[8][10] = {
	{0.0175,    0.0205,    0.0147,    0.0171,    0.0144,    0.0178,    0.0146,    0.0082,    0.0097,    0.0119},
    {0.0034,    0.0059,    0.0107,    0.0141,    0.0179,    0.0115,    0.0079,    0.0053,    0.0056,    0.0051},
    {0.0303,    0.0072,    0.0132,    0.0157,    0.0219,    0.0207,    0.0132,    0.0115,    0.0129,    0.0190},
    {0.0046,    0.0068,    0.0082,    0.0118,    0.0104,    0.0104,    0.0097,    0.0074,    0.0071,    0.0051},
    {0.0160,    0.0321,    0.0225,    0.0268,    0.0243,    0.0147,    0.0150,    0.0097,    0.0075,    0.0079},
    {0.0032,    0.0090,    0.0093,    0.0119,    0.0119,    0.0110,    0.0081,    0.0096,    0.0071,    0.0041},
    {0.0207,    0.0096,    0.0168,    0.0274,    0.0280,    0.0240,    0.0166,    0.0127,    0.0121,    0.0171},
    {0.0031,    0.0097,    0.0085,    0.0090,    0.0116,    0.0099,    0.0065,    0.0069,    0.0044,    0.0026}
};

double jointPG[8][10] = {
	{0.0449,    0.0146,    0.0105,    0.0077,    0.0095,    0.0086,    0.0108,    0.0155,    0.0146,    0.0255},
    {0.0198,    0.0138,    0.0074,    0.0034,    0.0052,    0.0045,    0.0050,    0.0050,    0.0045,    0.0081},
    {0.0394,    0.0093,    0.0065,    0.0076,    0.0089,    0.0127,    0.0114,    0.0074,    0.0059,    0.0169},
    {0.0182,    0.0091,    0.0059,    0.0040,    0.0038,    0.0079,    0.0079,    0.0079,    0.0105,    0.0146},
    {0.0934,    0.0279,    0.0115,    0.0096,    0.0122,    0.0098,    0.0122,    0.0160,    0.0186,    0.0267},
    {0.0213,    0.0114,    0.0074,    0.0046,    0.0033,    0.0048,    0.0064,    0.0045,    0.0050,    0.0088},
    {0.0428,    0.0108,    0.0083,    0.0086,    0.0100,    0.0146,    0.0095,    0.0079,    0.0088,    0.0160},
    {0.0219,    0.0103,    0.0062,    0.0029,    0.0067,    0.0079,    0.0107,    0.0057,    0.0071,    0.0133}
};


int ProbabilitySeparator::getAngleDirection(ComplexNumber vec)
{
	double pi_8 = imago::PI / 8.0;
	double angle = vec.getAngle();
	int retVal = 0;
	if(angle < 0)
		angle  += 2 * imago::PI;
		
	if(angle < pi_8 || angle >= 15.0 * pi_8)
		retVal =  0;//"E";
	else
		if(angle >= pi_8 && angle < 3.0 * pi_8)
			retVal =  1;// "NE";
		else
			if(angle >= 3.0 * pi_8 && angle < pi_8 * 5.0)
				retVal =  2; // "N";
			else
				if(angle >= pi_8 * 5.0 && angle < pi_8 * 7.0)
					retVal =  3; // "NW";
				else
					if(angle >= pi_8 * 7.0 && angle < pi_8 * 9.0)
						retVal =  4; // "W";
		
	if(angle >= 9.0 * pi_8 && angle < 11.0 * pi_8)
			retVal =  5; // "SW";
		else
			if(angle >= 11.0 * pi_8 && angle < pi_8 * 13.0)
				retVal =  6; // "S";
			else
				if(angle >= pi_8 * 13.0 && angle < pi_8 * 15.0)
					retVal =  7; // "SE";
	return retVal;
}

void ProbabilitySeparator::CalculateProbabilities(const Settings& vars, 
	        Image& seg, double& char_probability, double& bond_probability, 
			double char_apriory, double bond_apriory)
{
	/*Image img(seg.getWidth(), seg.getHeight());
	seg.extract(0, 0, img.getWidth(), img.getHeight(), img);*/
	ComplexContour contour  = ComplexContour::RetrieveContour(vars, seg);
	contour.Normalize();

	double bond_prob = 1.0,
		char_prob = 1.0;

	for(int i = 0; i < contour.Size(); i++)
	{
		imago::ComplexNumber cn = contour.getContour(i);

		int binD = getAngleDirection(cn);
		int binS = ((int)(cn.getRadius() * 10)) % 10;

		bond_prob *= jointPG[binD][binS];
		char_prob *= jointPS[binD][binS];
	}

	char_prob *= char_apriory;
	bond_prob *= bond_apriory;

	char_probability = char_prob / (char_prob + bond_prob);
	bond_probability = bond_prob / (char_prob + bond_prob);
}