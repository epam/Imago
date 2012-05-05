#include "constants.h"
#include <algorithm>

imago::Settings& imago_getSettings()
{
	static imago::Settings _ThreadUnsafeSettings;
	return _ThreadUnsafeSettings;
}

namespace imago
{
	#define FUZZ ;

	void imago::Settings::update()
	{
		int cluster = general.IsHandwritten ? CLUSTER_HANDWRITTING : CLUSTER_SCANNED;
		int longestSide = std::max(general.ImageWidth, general.ImageHeight);

		main = MainSettings(cluster, longestSide);
		molecule = MoleculeSettings(cluster, longestSide);
		estimation = EstimationSettings(cluster, longestSide);
	}	

	void NormalizeBySide(double &value, int longestSide)
	{
		// temporary to check the results matching!
		return;

		if (longestSide > 0)
			value = value / 800.0 * (double)longestSide;
	}

	// ------------------------------------------------------------------

	MoleculeSettings::MoleculeSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ LengthFactor_long = 0.307623;
			FUZZ LengthFactor_medium = 0.418885;
			FUZZ LengthFactor_default = 0.480585; 
			FUZZ LengthValue_long = 103.398083;
			FUZZ LengthValue_medium = 84.686506;
			FUZZ SpaceMultiply = 1.449601;
			FUZZ AngleTreshold = 0.249862;
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ LengthFactor_long = 0.307623;
			FUZZ LengthFactor_medium = 0.418885;
			FUZZ LengthFactor_default = 0.480585; 
			FUZZ LengthValue_long = 103.398083;
			FUZZ LengthValue_medium = 84.686506;
			FUZZ SpaceMultiply = 1.449601;
			FUZZ AngleTreshold = 0.249862;
		}

		NormalizeBySide(LengthValue_long, LongestSide);
		NormalizeBySide(LengthValue_medium, LongestSide);
	}

	MainSettings::MainSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ DissolvingsFactor = 9;
			FUZZ WarningsRecalcTreshold = 2;
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ DissolvingsFactor = 9;
			FUZZ WarningsRecalcTreshold = 2;
		}
	}


	EstimationSettings::EstimationSettings(int cluster, int LongestSide)
	{
		// therse should be updated anyway
		CapitalHeight = 16.0;
		LineThickness = 6.0;
		AvgBondLength = 30.0;

		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ AddVertexEps = 5.2;
			FUZZ MaxSymRatio = 1.103637;
			FUZZ MinSymRatio = 0.34;
			FUZZ ParLinesEps = 0.521496;
			FUZZ SymHeightErr = 28.212650;
			FUZZ CapitalHeightError = 0.85;
			FUZZ DoubleBondDist = 20;
			FUZZ SegmentVerEps = 4;
			FUZZ CharactersSpaceCoeff = 0.5;
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ AddVertexEps = 5.2;
			FUZZ MaxSymRatio = 1.103637;
			FUZZ MinSymRatio = 0.34;
			FUZZ ParLinesEps = 0.521496;
			FUZZ SymHeightErr = 28.212650;
			FUZZ CapitalHeightError = 0.85;
			FUZZ DoubleBondDist = 20;
			FUZZ SegmentVerEps = 4;
			FUZZ CharactersSpaceCoeff = 0.4;
		}

		NormalizeBySide(SymHeightErr, LongestSide);
	}
}
