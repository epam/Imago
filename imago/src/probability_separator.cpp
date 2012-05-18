#include "probability_separator.h"

using namespace imago;

double jointPS[8][10] = {
	{0.0093,    0.0080,    0.0134,    0.0145,    0.0134,    0.0129,    0.0096,    0.0054,    0.0088,    0.0103},
	{0.0134,    0.0165,    0.0225,    0.0217,    0.0163,    0.0189,    0.0134,    0.0096,    0.0067,    0.0129},
	{0.0034,    0.0150,    0.0176,    0.0121,    0.0098,    0.0098,    0.0062,    0.0065,    0.0049,    0.0057},
	{0.0248,    0.0393,    0.0256,    0.0269,    0.0155,    0.0119,    0.0114,    0.0109,    0.0052,    0.0057},
	{0.0114,    0.0085,    0.0114,    0.0158,    0.0140,    0.0134,    0.0090,    0.0101,    0.0083,    0.0075},
	{0.0178,    0.0165,    0.0145,    0.0132,    0.0129,    0.0134,    0.0119,    0.0109,    0.0127,    0.0173},
	{0.0039,    0.0152,    0.0186,    0.0152,    0.0106,    0.0057,    0.0067,    0.0031,    0.0057,    0.0041},
	{0.0114,    0.0196,    0.0189,    0.0158,    0.0160,    0.0155,    0.0124,    0.0098,    0.0072,    0.0083}
};

double jointPG[8][10] = {
	{0.0220,    0.0116,    0.0070,    0.0058,    0.0116,    0.0174,    0.0070,    0.0058,    0.0093,    0.0046},
	{0.0336,    0.0139,    0.0035,    0.0127,    0.0162,    0.0220,    0.0197,    0.0081,    0.0174,    0.0058},
	{0.0139,    0.0162,    0.0070,    0.0035,    0.0046,    0.0081,    0.0046,    0.0046,    0.0046,    0.0035},
	{0.0730,    0.0151,    0.0093,    0.0081,    0.0116,    0.0058,    0.0232,    0.0290,    0.0151,    0.0209},
	{0.0104,    0.0058,    0.0046,    0.0093,    0.0070,    0.0093,    0.0139,    0.0093,    0.0081,    0.0151},
	{0.0209,    0.0116,    0.0058,    0.0104,    0.0185,    0.0151,    0.0220,    0.0093,    0.0070,    0.0104},
	{0.0104,    0.0220,    0.0093,    0.0035,    0.0058,    0.0023,    0.0070,    0.0035,    0.0023,    0.0035},
	{0.0417,    0.0174,    0.0046,    0.0046,    0.0058,    0.0070,    0.0255,    0.0185,    0.0185,    0.0267}
};


int getAngleDirection(imago::ComplexNumber vec)
{
	double pi_8 = imago::PI_4 / 2.0;
	double angle = vec.getAngle();
		if(angle < 0)
			angle  += 2 * imago::PI;
		
		if(angle < pi_8 || angle >= 15.0 * pi_8)
			return 0;//"E";
		else
			if(angle >= pi_8 && angle < 3.0 * pi_8)
				return 1;// "NE";
			else
				if(angle >= 3.0 * pi_8 && angle < pi_8 * 5.0)
					return 2; // "N";
				else
					if(angle >= pi_8 * 5.0 && angle < pi_8 * 7.0)
						return 3; // "NW";
					else
						if(angle >= pi_8 * 7.0 && angle < pi_8 * 9.0)
							return 4; // "W";
		
		if(angle >= 9.0 * pi_8 && angle < 11.0 * pi_8)
				return 5; // "SW";
			else
				if(angle >= 11.0 * pi_8 && angle < pi_8 * 13.0)
					return 6; // "S";
				else
					if(angle >= pi_8 * 13.0 && angle < pi_8 * 15.0)
						return 7; // "SE";

}

void ProbabilitySeparator::CalculateProbabilities(Segment seg, double& char_probability, double& bond_probability, 
			double char_apriory, double bond_apriory)
{
	ComplexContour contour  = ComplexContour::RetrieveContour(seg);
	contour.Normalize();

	double bond_prob = 1.0,
		char_prob = 1.0;

	for(int i = 0; i < contour.Size(); i++)
	{
		imago::ComplexNumber cn = contour.getContour(i);

		int binD = 7 - getAngleDirection(cn);
		int binS = ((int)(cn.getRadius() * 10)) % 10;

		bond_prob *= jointPG[binD][binS];
		char_prob *= jointPS[binD][binS];
	}

	char_prob *= char_apriory;
	bond_prob *= bond_apriory;

	char_probability = char_prob / (char_prob + bond_prob);
	bond_probability = bond_prob / (char_prob + bond_prob);
}