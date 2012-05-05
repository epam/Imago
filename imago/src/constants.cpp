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
		mbond = MultipleBondSettings(cluster, longestSide);
		skeleton = SkeletonSettings(cluster, longestSide);
		prefilterCV = PrefilterCVSettings();
		adaptive = AdaptiveFilterSettings();
		prefilter = PrefilterSettings();
		routines = RoutinesSettings(cluster, longestSide);
		weak_seg = WeakSegmentatorSettings(cluster, longestSide);
		wbe = WedgeBondExtractorSettings(cluster, longestSide);
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

	MultipleBondSettings::MultipleBondSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ LongBond = 120; //fuzzed from 125
			FUZZ LongErr = 0.355546; //fuzzed from 0.35
			FUZZ MediumBond = 89; //fuzzed from 85
			FUZZ MediumErr = 0.392531; //fuzzed from 0.4
			FUZZ DefaultErr = 0.633629; //fuzzed from 0.65
			FUZZ ParBondsEps = 0.340174; //fuzzed from 0.335
			FUZZ DoubleRatioTresh = 7.313650; //fuzzed from 7.5
			FUZZ DoubleCoef = 0.082163; //fuzzed from 0.085
			FUZZ DoubleMagic1 = 0.964608; //fuzzed from 0.98
			FUZZ DoubleMagic2 = 0.973610; //fuzzed from 0.98
			FUZZ DoubleTreshMin = 0.101401; //fuzzed from 0.1
			FUZZ DoubleTreshMax = 0.858590; //fuzzed from 0.9

			FUZZ MaxLen1 = 166.686972; //fuzzed from 160.0
			FUZZ MaxLen2 = 120.978614; //fuzzed from 125.0
			FUZZ MaxLen3 = 113.678808; //fuzzed from 110.0
			FUZZ MaxLen4 = 110.078292; //fuzzed from 108.0
			FUZZ MaxLen5 = 86.910405; //fuzzed from 85.0

			FUZZ MinLen1 = 85.970779; //fuzzed from 90.0
			FUZZ MinLen2 = 75.488563; //fuzzed from 75.0

			FUZZ mbe1 = 0.081863; //fuzzed from 0.08
			FUZZ mbe2 = 0.149657; //fuzzed from 0.157
			FUZZ mbe3 = 0.202220; //fuzzed from 0.203
			FUZZ mbe4 = 0.184702; //fuzzed from 0.185
			FUZZ mbe5 = 0.158555; //fuzzed from 0.165
			FUZZ mbe6 = 0.205762; //fuzzed from 0.20
			FUZZ mbe7 = 0.387195; //fuzzed from 0.38
			FUZZ mbe_def = 0.518222; //fuzzed from 0.5
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ LongBond = 120; //fuzzed from 125
			FUZZ LongErr = 0.355546; //fuzzed from 0.35
			FUZZ MediumBond = 89; //fuzzed from 85
			FUZZ MediumErr = 0.392531; //fuzzed from 0.4
			FUZZ DefaultErr = 0.633629; //fuzzed from 0.65
			FUZZ ParBondsEps = 0.340174; //fuzzed from 0.335
			FUZZ DoubleRatioTresh = 7.313650; //fuzzed from 7.5
			FUZZ DoubleCoef = 0.082163; //fuzzed from 0.085
			FUZZ DoubleMagic1 = 0.964608; //fuzzed from 0.98
			FUZZ DoubleMagic2 = 0.973610; //fuzzed from 0.98
			FUZZ DoubleTreshMin = 0.101401; //fuzzed from 0.1
			FUZZ DoubleTreshMax = 0.858590; //fuzzed from 0.9

			FUZZ MaxLen1 = 166.686972; //fuzzed from 160.0
			FUZZ MaxLen2 = 120.978614; //fuzzed from 125.0
			FUZZ MaxLen3 = 113.678808; //fuzzed from 110.0
			FUZZ MaxLen4 = 110.078292; //fuzzed from 108.0
			FUZZ MaxLen5 = 86.910405; //fuzzed from 85.0

			FUZZ MinLen1 = 85.970779; //fuzzed from 90.0
			FUZZ MinLen2 = 75.488563; //fuzzed from 75.0

			FUZZ mbe1 = 0.081863; //fuzzed from 0.08
			FUZZ mbe2 = 0.149657; //fuzzed from 0.157
			FUZZ mbe3 = 0.202220; //fuzzed from 0.203
			FUZZ mbe4 = 0.184702; //fuzzed from 0.185
			FUZZ mbe5 = 0.158555; //fuzzed from 0.165
			FUZZ mbe6 = 0.205762; //fuzzed from 0.20
			FUZZ mbe7 = 0.387195; //fuzzed from 0.38
			FUZZ mbe_def = 0.518222; //fuzzed from 0.5
		}
		
		NormalizeBySide(LongBond, LongestSide);
		NormalizeBySide(MediumBond, LongestSide);
		NormalizeBySide(MaxLen1, LongestSide);
		NormalizeBySide(MaxLen2, LongestSide);
		NormalizeBySide(MaxLen3, LongestSide);
		NormalizeBySide(MaxLen4, LongestSide);
		NormalizeBySide(MaxLen5, LongestSide);
		NormalizeBySide(MinLen1, LongestSide);
		NormalizeBySide(MinLen2, LongestSide);
	}

	SkeletonSettings::SkeletonSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ MultiBondErr = 0.288897; //fuzzed from 0.3
			FUZZ BaseMult = 0.096796; //fuzzed from 0.1
			FUZZ BaseSmallErr = 0.150513; //fuzzed from 0.153
			FUZZ ShortBondLen = 21; //fuzzed from 20
			FUZZ ShortMul = 0.305195; //fuzzed from 0.3
			FUZZ MediumBondLen = 86; //fuzzed from 85
			FUZZ MediumMul = 0.174502; //fuzzed from 0.175
			FUZZ MediumSmallErr = 0.135596; //fuzzed from 0.13
			FUZZ LongBondLen = 102; //fuzzed from 100
			FUZZ LongMul = 0.153650; //fuzzed from 0.15
			FUZZ LongSmallErr = 0.062265; //fuzzed from 0.06
			FUZZ BrokenRepairFactor = 2.916799; //fuzzed from 3.0
			FUZZ BrokenRepairCoef1 = 0.953562; //fuzzed from 1.0
			FUZZ BrokenRepairCoef2 = 2.639729; //fuzzed from 2.7
			FUZZ BrokenRepairAngleEps = 0.196705; //fuzzed from 0.2
			FUZZ DissolveMinErr = 0.175928; //fuzzed from 0.17
			FUZZ ConnectBlockS = 10.137806; //fuzzed from 10.0
			FUZZ ConnectFactor = 2.018851; //fuzzed from 2.0
			FUZZ JoinVerticiesConst = 0.098173; //fuzzed from 0.1
			FUZZ DissolveConst = 0.096792; //fuzzed from 0.1
			FUZZ Dissolve2Const = 0.201523; //fuzzed from 0.2
			FUZZ Join2Const = 0.336929; //fuzzed from 0.33
			FUZZ Join3Const = 0.190316; //fuzzed from 0.2
			FUZZ DistTreshLimFactor = 1.986538; //fuzzed from 2.0
			FUZZ SlopeFact1 = 0.098094; //fuzzed from 0.1
			FUZZ SlopeFact2 = 0.198126; //fuzzed from 0.2
			FUZZ ShrinkEps = 0.124899; //fuzzed from 0.13
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ MultiBondErr = 0.288897; //fuzzed from 0.3
			FUZZ BaseMult = 0.096796; //fuzzed from 0.1
			FUZZ BaseSmallErr = 0.150513; //fuzzed from 0.153
			FUZZ ShortBondLen = 21; //fuzzed from 20
			FUZZ ShortMul = 0.305195; //fuzzed from 0.3
			FUZZ MediumBondLen = 86; //fuzzed from 85
			FUZZ MediumMul = 0.174502; //fuzzed from 0.175
			FUZZ MediumSmallErr = 0.135596; //fuzzed from 0.13
			FUZZ LongBondLen = 102; //fuzzed from 100
			FUZZ LongMul = 0.153650; //fuzzed from 0.15
			FUZZ LongSmallErr = 0.062265; //fuzzed from 0.06
			FUZZ BrokenRepairFactor = 2.916799; //fuzzed from 3.0
			FUZZ BrokenRepairCoef1 = 0.953562; //fuzzed from 1.0
			FUZZ BrokenRepairCoef2 = 2.639729; //fuzzed from 2.7
			FUZZ BrokenRepairAngleEps = 0.196705; //fuzzed from 0.2
			FUZZ DissolveMinErr = 0.175928; //fuzzed from 0.17
			FUZZ ConnectBlockS = 10.137806; //fuzzed from 10.0
			FUZZ ConnectFactor = 2.018851; //fuzzed from 2.0
			FUZZ JoinVerticiesConst = 0.098173; //fuzzed from 0.1
			FUZZ DissolveConst = 0.096792; //fuzzed from 0.1
			FUZZ Dissolve2Const = 0.201523; //fuzzed from 0.2
			FUZZ Join2Const = 0.336929; //fuzzed from 0.33
			FUZZ Join3Const = 0.190316; //fuzzed from 0.2
			FUZZ DistTreshLimFactor = 1.986538; //fuzzed from 2.0
			FUZZ SlopeFact1 = 0.098094; //fuzzed from 0.1
			FUZZ SlopeFact2 = 0.198126; //fuzzed from 0.2
			FUZZ ShrinkEps = 0.124899; //fuzzed from 0.13
		}
		
		NormalizeBySide(ShortBondLen, LongestSide);
		NormalizeBySide(MediumBondLen, LongestSide);
		NormalizeBySide(LongBondLen, LongestSide);
	}

	PrefilterCVSettings::PrefilterCVSettings()
	{
		FUZZ MaxNonBWPixelsProportion = 11; //fuzzed from 11
		FUZZ MinGoodPixelsCount = 18; //fuzzed from 18
		FUZZ MaxBadToGoodRatio = 8; //fuzzed from 8
		FUZZ BorderPartProportion = 40; //fuzzed from 42
		FUZZ MaxRectangleCropLineWidth = 11; //fuzzed from 11
		FUZZ StrongBinarizeSize = 4; //fuzzed from 4
		FUZZ StrongBinarizeTresh = 1.344729; //fuzzed from 1.288367
		FUZZ WeakBinarizeSize = 7; //fuzzed from 7
		FUZZ WeakBinarizeTresh = 1.129019; //fuzzed from 1.178619
	}

	AdaptiveFilterSettings::AdaptiveFilterSettings()
	{
		MaxCrops = 1;
		FUZZ MinimalLineThickness = 1.039231; //fuzzed from 1.093120
		FUZZ MaximalLineThickness = 10.265688; //fuzzed from 9.910034
		FUZZ MinimalInkPercentage = 0.094374; //fuzzed from 0.094627
		FUZZ MaximalInkPercentage = 8.740140; //fuzzed from 9.047041
		FUZZ GuessInkThresholdFactor = 0.587444; //fuzzed from 0.591245
		FUZZ InterpolationLevel = 2; //fuzzed from 2		
		FUZZ MaxRefineIterations = 2; //fuzzed from 2
		FUZZ MaxDiffIterations = 4; //fuzzed from 4
		FUZZ WindowSizeFactor = 2; //fuzzed from 2
	}

	PrefilterSettings::PrefilterSettings()
	{
		MakeSegmentsConnected = false;
		FUZZ SpotsWindowSize = 3; //fuzzed from 3
		FUZZ GreyTreshMinF = 1.085847; //fuzzed from 1.088456
		FUZZ GreyTreshMaxF = 0.953415; //fuzzed from 0.917166
		FUZZ ReduceImageDim = 269; //fuzzed from 268
		FUZZ GaussianKernelSize = 5; //fuzzed from 5
		FUZZ Bilateral_d = 5; //fuzzed from 5
		FUZZ BilateralSpace = 19.414779; //fuzzed from 19.090640
		FUZZ MinSSize = 23; //fuzzed from 23
		FUZZ UnsharpSize = 7; //fuzzed from 7
		FUZZ UnsharpAmount = 3.978068; //fuzzed from 3.918225
		FUZZ WienerSize = 5; //fuzzed from 5
		FUZZ TreshFactor = 0.197020; //fuzzed from 0.205623
		FUZZ BlockSAdaptive = 7; //fuzzed from 7
		FUZZ MaxLSSplah = 2.783276; //fuzzed from 2.810816
		FUZZ MagicCoeff = 8.438847; //fuzzed from 8.652838
		FUZZ SAreaTresh = 0.298385; //fuzzed from 0.3
	}

	RoutinesSettings::RoutinesSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ LineThick_Grid = 10; //fuzzed from 10
			FUZZ Circle_Eps = 0.000009; //fuzzed from 0.000009
			FUZZ Circle_GapMin = 0.096860; //fuzzed from 0.097346
			FUZZ Circle_GapMax = 0.971710; //fuzzed from 0.977436
			FUZZ Circle_RMax = 2.102963; //fuzzed from 2.029622
			FUZZ Circle_AvgRadius = 0.000105; //fuzzed from 0.000100
			FUZZ Circle_MaxRatio = 0.319711; //fuzzed from 0.324951
			FUZZ Algebra_IntersectionEps = 0.010220; //fuzzed from 0.010607
			FUZZ Algebra_SameLineEps = 0.212478; //fuzzed from 0.210793
			FUZZ Approx_Eps1 = 1.184722; //fuzzed from 1.151009
			FUZZ Approx_Eps2 = 0.887856; //fuzzed from 0.856642
			FUZZ Approx_CalcLineTresh = 0.909670; //fuzzed from 0.870146
			FUZZ Contour_Eps1 = 1.123741; //fuzzed from 1.071862
			FUZZ Contour_Eps2 = 0.675823; //fuzzed from 0.705507
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ LineThick_Grid = 10; //fuzzed from 10
			FUZZ Circle_Eps = 0.000009; //fuzzed from 0.000009
			FUZZ Circle_GapMin = 0.096860; //fuzzed from 0.097346
			FUZZ Circle_GapMax = 0.971710; //fuzzed from 0.977436
			FUZZ Circle_RMax = 2.102963; //fuzzed from 2.029622
			FUZZ Circle_AvgRadius = 0.000105; //fuzzed from 0.000100
			FUZZ Circle_MaxRatio = 0.319711; //fuzzed from 0.324951
			FUZZ Algebra_IntersectionEps = 0.010220; //fuzzed from 0.010607
			FUZZ Algebra_SameLineEps = 0.212478; //fuzzed from 0.210793
			FUZZ Approx_Eps1 = 1.184722; //fuzzed from 1.151009
			FUZZ Approx_Eps2 = 0.887856; //fuzzed from 0.856642
			FUZZ Approx_CalcLineTresh = 0.909670; //fuzzed from 0.870146
			FUZZ Contour_Eps1 = 1.123741; //fuzzed from 1.071862
			FUZZ Contour_Eps2 = 0.675823; //fuzzed from 0.705507
		}
	}

	WeakSegmentatorSettings::WeakSegmentatorSettings(int cluster, int LongestSide)
	{
		SubpixelDraw = 0.5;
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ RectangularCropAreaTreshold = 0.298603; //fuzzed from 0.291124
			FUZZ RectangularCropFitTreshold = 1.049695; //fuzzed from 1.023274
			FUZZ RefineWidth = 0.857144; //fuzzed from 0.901301
			FUZZ MinDistanceDraw = 1.352319;
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ RectangularCropAreaTreshold = 0.298603; //fuzzed from 0.291124
			FUZZ RectangularCropFitTreshold = 1.049695; //fuzzed from 1.023274
			FUZZ RefineWidth = 0.857144; //fuzzed from 0.901301
			FUZZ MinDistanceDraw = 1.352319;
		}
	}

	WedgeBondExtractorSettings::WedgeBondExtractorSettings(int cluster, int LongestSide)
	{	
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ PointsCompareDist = 3; //fuzzed from 3			
			FUZZ SingleDownCompareDist = 2; //fuzzed from 2
			FUZZ SingleDownEps = 3.008877; //fuzzed from 2.924434
			FUZZ SingleDownAngleMax = 45.664699; //fuzzed from 43.804412
			FUZZ SingleDownDistancesMax = 9.742339; //fuzzed from 9.354137
			FUZZ SingleDownLengthMax = 44.086214; //fuzzed from 42.785999			
			FUZZ SingleUpRatioEps = 1.839959; //fuzzed from 1.770050
			FUZZ SingleUpDefCoeff = 0.282291; //fuzzed from 0.273103
			FUZZ SingleUpIncCoeff = 0.416666; //fuzzed from 0.420675
			FUZZ SingleUpIncLengthTresh = 36.420517; //fuzzed from 34.979829
			FUZZ SingleUpInterpolateEps = 0.059793; //fuzzed from 0.062390
			FUZZ SingleUpMagicAddition = 0.223878; //fuzzed from 0.213237
			FUZZ SingleUpS2Divisor = 1.644773; //fuzzed from 1.577473
			FUZZ SingleUpMinATresh = 1.701618; //fuzzed from 1.664169
			FUZZ SingleUpSquareRatio = 0.641111; //fuzzed from 0.655334
			FUZZ SingleUpAngleTresh = 0.067432; //fuzzed from 0.069811
			FUZZ SomeTresh = 0.096512; //fuzzed from 0.1
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ PointsCompareDist = 3; //fuzzed from 3			
			FUZZ SingleDownCompareDist = 2; //fuzzed from 2
			FUZZ SingleDownEps = 3.008877; //fuzzed from 2.924434
			FUZZ SingleDownAngleMax = 45.664699; //fuzzed from 43.804412
			FUZZ SingleDownDistancesMax = 9.742339; //fuzzed from 9.354137
			FUZZ SingleDownLengthMax = 44.086214; //fuzzed from 42.785999			
			FUZZ SingleUpRatioEps = 1.839959; //fuzzed from 1.770050
			FUZZ SingleUpDefCoeff = 0.282291; //fuzzed from 0.273103
			FUZZ SingleUpIncCoeff = 0.416666; //fuzzed from 0.420675
			FUZZ SingleUpIncLengthTresh = 36.420517; //fuzzed from 34.979829
			FUZZ SingleUpInterpolateEps = 0.059793; //fuzzed from 0.062390
			FUZZ SingleUpMagicAddition = 0.223878; //fuzzed from 0.213237
			FUZZ SingleUpS2Divisor = 1.644773; //fuzzed from 1.577473
			FUZZ SingleUpMinATresh = 1.701618; //fuzzed from 1.664169
			FUZZ SingleUpSquareRatio = 0.641111; //fuzzed from 0.655334
			FUZZ SingleUpAngleTresh = 0.067432; //fuzzed from 0.069811
			FUZZ SomeTresh = 0.096512; //fuzzed from 0.1
		}

		NormalizeBySide(SingleDownDistancesMax, LongestSide);
		NormalizeBySide(SingleUpIncLengthTresh, LongestSide);
	}
}
