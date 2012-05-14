#include "constants.h"
#include <algorithm>

namespace imago
{
	#define FUZZ ; // marker for constants allowed to adjust automatically

	void imago::Settings::update()
	{
		int cluster = general.IsHandwritten ? CLUSTER_HANDWRITTING : CLUSTER_SCANNED;
		int longestSide = std::max(general.OriginalImageWidth, general.OriginalImageHeight);

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
		characters = CharactersRecognitionSettings(cluster, longestSide);
		csr = ChemicalStructureRecognizerSettings(cluster, longestSide);
		graph = GraphExtractorSettings(cluster, longestSide);
		utils = ImageUtilsSettings(cluster, longestSide);
		separator = SeparatorSettings(cluster, longestSide);
		labels = LabelLogicSettings(cluster, longestSide);
		lcomb = LabelCombinerSettings(cluster, longestSide);
	}	

	void NormalizeBySide(double &value, int longestSide)
	{
		return; // temporary, works not fine now

		if (longestSide > 0)
			value = value * sqrt((double)longestSide / 1200.0);
	}

	// ------------------------------------------------------------------

	MoleculeSettings::MoleculeSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ LengthFactor_long = 0.316981; // fuzzed, old value = 0.310291
			FUZZ LengthFactor_medium = 0.426186; // fuzzed, old value = 0.425901
			FUZZ LengthFactor_default = 0.481170; // fuzzed, old value = 0.487716
			FUZZ LengthValue_long = 103.962175; // fuzzed, old value = 105.474833
			FUZZ LengthValue_medium = 84.220093; // fuzzed, old value = 83.108601
			FUZZ SpaceMultiply = 1.462494; // fuzzed, old value = 1.471014
			FUZZ AngleTreshold = 0.252597; // fuzzed, old value = 0.248073
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ LengthFactor_long = 0.302587; // fuzzed, old value = 0.301128
			FUZZ LengthFactor_medium = 0.413869; // fuzzed, old value = 0.412195
			FUZZ LengthFactor_default = 0.482683; // fuzzed, old value = 0.478946
			FUZZ LengthValue_long = 106.597956; // fuzzed, old value = 104.576605
			FUZZ LengthValue_medium = 82.637482; // fuzzed, old value = 83.828508
			FUZZ SpaceMultiply = 1.469594; // fuzzed, old value = 1.433167
			FUZZ AngleTreshold = 0.262416; // fuzzed, old value = 0.259030
		}

		NormalizeBySide(LengthValue_long, LongestSide);
		NormalizeBySide(LengthValue_medium, LongestSide);
	}

	MainSettings::MainSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ DissolvingsFactor = 9; // fuzzed, old value = 9
			FUZZ WarningsRecalcTreshold = 2; // fuzzed, old value = 2
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ DissolvingsFactor = 9; // fuzzed, old value = 9
			FUZZ WarningsRecalcTreshold = 2; // fuzzed, old value = 2
		}
	}


	EstimationSettings::EstimationSettings(int cluster, int LongestSide)
	{
		// these should be updated anyway
		CapitalHeight = 16.0;
		LineThickness = 6.0;
		AvgBondLength = 30.0;

		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ AddVertexEps = 5.171899; // fuzzed, old value = 5.2
			FUZZ MaxSymRatio = 1.073283; // fuzzed, old value = 1.077193
			FUZZ MinSymRatio = 0.332828; // fuzzed, old value = 0.34
			FUZZ ParLinesEps = 0.512849; // fuzzed, old value = 0.513493
			FUZZ SymHeightErr = 28.737111; // fuzzed, old value = 28.206860
			FUZZ CapitalHeightError = 0.849315; // fuzzed, old value = 0.85
			FUZZ DoubleBondDist = 20; // fuzzed, old value = 20
			FUZZ SegmentVerEps = 4; // fuzzed, old value = 4
			FUZZ CharactersSpaceCoeff = 0.510033; // fuzzed, old value = 0.5
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ AddVertexEps = 5.052747; // fuzzed, old value = 5.099192
			FUZZ MaxSymRatio = 1.123954; // fuzzed, old value = 1.122616
			FUZZ MinSymRatio = 0.338931; // fuzzed, old value = 0.341869
			FUZZ ParLinesEps = 0.523855; // fuzzed, old value = 0.513057
			FUZZ SymHeightErr = 26.909337; // fuzzed, old value = 27.170494
			FUZZ CapitalHeightError = 0.823201; // fuzzed, old value = 0.839837
			FUZZ DoubleBondDist = 21; // fuzzed, old value = 20
			FUZZ SegmentVerEps = 4; // fuzzed, old value = 4
			FUZZ CharactersSpaceCoeff = 0.378645; // fuzzed, old value = 0.391240
		}

		NormalizeBySide(SymHeightErr, LongestSide);
	}

	MultipleBondSettings::MultipleBondSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ LongBond = 119; // fuzzed, old value = 118
			FUZZ LongErr = 0.362768; // fuzzed, old value = 0.356396
			FUZZ MediumBond = 90; // fuzzed, old value = 90
			FUZZ MediumErr = 0.392199; // fuzzed, old value = 0.387344
			FUZZ DefaultErr = 0.635246; // fuzzed, old value = 0.637428
			FUZZ ParBondsEps = 0.336346; // fuzzed, old value = 0.333194
			FUZZ DoubleRatioTresh = 7.338240; // fuzzed, old value = 7.273803
			FUZZ DoubleCoef = 0.082408; // fuzzed, old value = 0.080612
			FUZZ DoubleMagic1 = 0.946310; // fuzzed, old value = 0.951135
			FUZZ DoubleMagic2 = 1.015646; // fuzzed, old value = 0.995650
			FUZZ DoubleTreshMin = 0.100697; // fuzzed, old value = 0.101219
			FUZZ DoubleTreshMax = 0.882991; // fuzzed, old value = 0.877551

			FUZZ MaxLen1 = 164.156731; // fuzzed, old value = 167.283046
			FUZZ MaxLen2 = 122.830393; // fuzzed, old value = 122.202449
			FUZZ MaxLen3 = 109.414501; // fuzzed, old value = 111.537811
			FUZZ MaxLen4 = 109.194680; // fuzzed, old value = 108.957840
			FUZZ MaxLen5 = 85.838948; // fuzzed, old value = 86.211570

			FUZZ MinLen1 = 86.382026; // fuzzed, old value = 85.596967
			FUZZ MinLen2 = 76.351772; // fuzzed, old value = 75.189012

			FUZZ mbe1 = 0.082278; // fuzzed, old value = 0.082698
			FUZZ mbe2 = 0.152398; // fuzzed, old value = 0.149319
			FUZZ mbe3 = 0.200465; // fuzzed, old value = 0.200630
			FUZZ mbe4 = 0.184519; // fuzzed, old value = 0.188662
			FUZZ mbe5 = 0.158265; // fuzzed, old value = 0.161782
			FUZZ mbe6 = 0.209079; // fuzzed, old value = 0.208906
			FUZZ mbe7 = 0.391566; // fuzzed, old value = 0.396539
			FUZZ mbe_def = 0.519814; // fuzzed, old value = 0.510852

			FUZZ DoubleLeftLengthTresh = 0.330903; // fuzzed, old value = 0.323348
			FUZZ DoubleRightLengthTresh = 0.310036; // fuzzed, old value = 0.311682
			FUZZ TripleLeftLengthTresh = 0.255772; // fuzzed, old value = 0.253714
			FUZZ TripleRightLengthTresh = 0.228044; // fuzzed, old value = 0.232986
			FUZZ Case1LengthTresh = 102.074306; // fuzzed, old value = 104.213876
			FUZZ Case1Factor = 0.438170; // fuzzed, old value = 0.447831
			FUZZ Case2LengthTresh = 78.284797; // fuzzed, old value = 79.384028
			FUZZ Case2Factor = 0.699134; // fuzzed, old value = 0.698154
			FUZZ Case3Factor = 0.912423; // fuzzed, old value = 0.904546
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ LongBond = 113; // fuzzed, old value = 118
			FUZZ LongErr = 0.346608; // fuzzed, old value = 0.360257
			FUZZ MediumBond = 89; // fuzzed, old value = 88
			FUZZ MediumErr = 0.391840; // fuzzed, old value = 0.388901
			FUZZ DefaultErr = 0.610753; // fuzzed, old value = 0.640971
			FUZZ ParBondsEps = 0.337947; // fuzzed, old value = 0.349066
			FUZZ DoubleRatioTresh = 7.348546; // fuzzed, old value = 7.457044
			FUZZ DoubleCoef = 0.083989; // fuzzed, old value = 0.080466
			FUZZ DoubleMagic1 = 0.937557; // fuzzed, old value = 0.948187
			FUZZ DoubleMagic2 = 0.975982; // fuzzed, old value = 0.984298
			FUZZ DoubleTreshMin = 0.103846; // fuzzed, old value = 0.101160
			FUZZ DoubleTreshMax = 0.844539; // fuzzed, old value = 0.868968

			FUZZ MaxLen1 = 163.885566; // fuzzed, old value = 164.846209
			FUZZ MaxLen2 = 119.655960; // fuzzed, old value = 122.787381
			FUZZ MaxLen3 = 112.447633; // fuzzed, old value = 115.223338
			FUZZ MaxLen4 = 114.351034; // fuzzed, old value = 109.669810
			FUZZ MaxLen5 = 84.175796; // fuzzed, old value = 85.478967

			FUZZ MinLen1 = 87.203894; // fuzzed, old value = 85.904719
			FUZZ MinLen2 = 73.050015; // fuzzed, old value = 76.648276

			FUZZ mbe1 = 0.082028; // fuzzed, old value = 0.081553
			FUZZ mbe2 = 0.155614; // fuzzed, old value = 0.150084
			FUZZ mbe3 = 0.198843; // fuzzed, old value = 0.207396
			FUZZ mbe4 = 0.195177; // fuzzed, old value = 0.186034
			FUZZ mbe5 = 0.149705; // fuzzed, old value = 0.156560
			FUZZ mbe6 = 0.209757; // fuzzed, old value = 0.207583
			FUZZ mbe7 = 0.420229; // fuzzed, old value = 0.403671
			FUZZ mbe_def = 0.496928; // fuzzed, old value = 0.517421

			FUZZ DoubleLeftLengthTresh = 0.343085; // fuzzed, old value = 0.327897
			FUZZ DoubleRightLengthTresh = 0.291665; // fuzzed, old value = 0.299122
			FUZZ TripleLeftLengthTresh = 0.267913; // fuzzed, old value = 0.261856
			FUZZ TripleRightLengthTresh = 0.231103; // fuzzed, old value = 0.221299
			FUZZ Case1LengthTresh = 106.538922; // fuzzed, old value = 103.451970
			FUZZ Case1Factor = 0.464350; // fuzzed, old value = 0.446116
			FUZZ Case2LengthTresh = 83.874277; // fuzzed, old value = 83.007771
			FUZZ Case2Factor = 0.719857; // fuzzed, old value = 0.700996
			FUZZ Case3Factor = 0.899713; // fuzzed, old value = 0.944560
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
			FUZZ BaseMult = 0.095546; // fuzzed, old value = 0.096488
			FUZZ BaseSmallErr = 0.151619; // fuzzed, old value = 0.150201
			FUZZ ShortBondLen = 21; // fuzzed, old value = 21
			FUZZ ShortMul = 0.311016; // fuzzed, old value = 0.307241
			FUZZ MediumBondLen = 84; // fuzzed, old value = 85
			FUZZ MediumMul = 0.175004; // fuzzed, old value = 0.177298
			FUZZ MediumSmallErr = 0.139131; // fuzzed, old value = 0.137212
			FUZZ LongBondLen = 102; // fuzzed, old value = 104
			FUZZ LongMul = 0.149453; // fuzzed, old value = 0.151405
			FUZZ LongSmallErr = 0.062468; // fuzzed, old value = 0.063768
			FUZZ BrokenRepairFactor = 2.958580; // fuzzed, old value = 2.965542
			FUZZ BrokenRepairCoef1 = 0.969769; // fuzzed, old value = 0.960452
			FUZZ BrokenRepairCoef2 = 2.674973; // fuzzed, old value = 2.697598
			FUZZ BrokenRepairAngleEps = 0.204331; // fuzzed, old value = 0.200919
			FUZZ DissolveMinErr = 0.173591; // fuzzed, old value = 0.177721
			FUZZ ConnectBlockS = 10.342266; // fuzzed, old value = 10.167484
			FUZZ ConnectFactor = 1.996873; // fuzzed, old value = 2.039006
			FUZZ JoinVerticiesConst = 0.099156; // fuzzed, old value = 0.100225
			FUZZ DissolveConst = 0.097573; // fuzzed, old value = 0.097109
			FUZZ Dissolve2Const = 0.200409; // fuzzed, old value = 0.201833
			FUZZ Join2Const = 0.340481; // fuzzed, old value = 0.344747
			FUZZ Join3Const = 0.188169; // fuzzed, old value = 0.185757
			FUZZ DistTreshLimFactor = 2.006374; // fuzzed, old value = 1.961816
			FUZZ SlopeFact1 = 0.099698; // fuzzed, old value = 0.097837
			FUZZ SlopeFact2 = 0.193475; // fuzzed, old value = 0.197422
			FUZZ ShrinkEps = 0.124536; // fuzzed, old value = 0.125378
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ BaseMult = 0.096645; // fuzzed, old value = 0.095763
			FUZZ BaseSmallErr = 0.148300; // fuzzed, old value = 0.152079
			FUZZ ShortBondLen = 22; // fuzzed, old value = 21
			FUZZ ShortMul = 0.301830; // fuzzed, old value = 0.305612
			FUZZ MediumBondLen = 86; // fuzzed, old value = 89
			FUZZ MediumMul = 0.166902; // fuzzed, old value = 0.175148
			FUZZ MediumSmallErr = 0.134690; // fuzzed, old value = 0.130098
			FUZZ LongBondLen = 101; // fuzzed, old value = 103
			FUZZ LongMul = 0.156848; // fuzzed, old value = 0.153756
			FUZZ LongSmallErr = 0.061348; // fuzzed, old value = 0.063796
			FUZZ BrokenRepairFactor = 3.014032; // fuzzed, old value = 2.876024
			FUZZ BrokenRepairCoef1 = 1.017943; // fuzzed, old value = 0.977421
			FUZZ BrokenRepairCoef2 = 2.682044; // fuzzed, old value = 2.688826
			FUZZ BrokenRepairAngleEps = 0.186894; // fuzzed, old value = 0.189200
			FUZZ DissolveMinErr = 0.173091; // fuzzed, old value = 0.175111
			FUZZ ConnectBlockS = 9.975947; // fuzzed, old value = 10.168268
			FUZZ ConnectFactor = 2.118554; // fuzzed, old value = 2.035299
			FUZZ JoinVerticiesConst = 0.104625; // fuzzed, old value = 0.101178
			FUZZ DissolveConst = 0.098007; // fuzzed, old value = 0.095184
			FUZZ Dissolve2Const = 0.194736; // fuzzed, old value = 0.196931
			FUZZ Join2Const = 0.327311; // fuzzed, old value = 0.324191
			FUZZ Join3Const = 0.186985; // fuzzed, old value = 0.188224
			FUZZ DistTreshLimFactor = 1.998246; // fuzzed, old value = 1.939525
			FUZZ SlopeFact1 = 0.102186; // fuzzed, old value = 0.099649
			FUZZ SlopeFact2 = 0.185034; // fuzzed, old value = 0.192488
			FUZZ ShrinkEps = 0.128250; // fuzzed, old value = 0.125260
		}
		
		NormalizeBySide(ShortBondLen, LongestSide);
		NormalizeBySide(MediumBondLen, LongestSide);
		NormalizeBySide(LongBondLen, LongestSide);
	}

	PrefilterCVSettings::PrefilterCVSettings()
	{
		FUZZ MaxNonBWPixelsProportion = 11; // fuzzed, old value = 11
		FUZZ MinGoodPixelsCount = 18; // fuzzed, old value = 18
		FUZZ MaxBadToGoodRatio = 8; // fuzzed, old value = 8
		FUZZ BorderPartProportion = 38; // fuzzed, old value = 39
		FUZZ MaxRectangleCropLineWidth = 11; // fuzzed, old value = 11
		FUZZ StrongBinarizeSize = 4; // fuzzed, old value = 4
		FUZZ StrongBinarizeTresh = 1.354787; // fuzzed, old value = 1.367176
		FUZZ WeakBinarizeSize = 7; // fuzzed, old value = 7
		FUZZ WeakBinarizeTresh = 1.113397; // fuzzed, old value = 1.123864
	}

	AdaptiveFilterSettings::AdaptiveFilterSettings()
	{
		MaxCrops = 1;
		FUZZ MinimalLineThickness = 1.054819; // fuzzed, old value = 1.059996
		FUZZ MaximalLineThickness = 10.112951; // fuzzed, old value = 10.245661
		FUZZ MinimalInkPercentage = 0.094957; // fuzzed, old value = 0.093563
		FUZZ MaximalInkPercentage = 8.678844; // fuzzed, old value = 8.789066
		FUZZ GuessInkThresholdFactor = 0.586910; // fuzzed, old value = 0.601815
		FUZZ InterpolationLevel = 2; // fuzzed, old value = 2
		FUZZ MaxRefineIterations = 2; // fuzzed, old value = 2
		FUZZ MaxDiffIterations = 4; // fuzzed, old value = 4
		FUZZ WindowSizeFactor = 2; // fuzzed, old value = 2
	}

	PrefilterSettings::PrefilterSettings()
	{
		MakeSegmentsConnected = false;
		FUZZ SpotsWindowSize = 3; // fuzzed, old value = 3
		FUZZ GreyTreshMinF = 1.111086; // fuzzed, old value = 1.112125
		FUZZ GreyTreshMaxF = 0.922988; // fuzzed, old value = 0.940712
		FUZZ ReduceImageDim = 267; // fuzzed, old value = 262
		FUZZ GaussianKernelSize = 5; // fuzzed, old value = 5
		FUZZ Bilateral_d = 5; // fuzzed, old value = 5
		FUZZ BilateralSpace = 19.992708; // fuzzed, old value = 19.632423
		FUZZ MinSSize = 23; // fuzzed, old value = 23
		FUZZ UnsharpSize = 7; // fuzzed, old value = 7
		FUZZ UnsharpAmount = 3.823081; // fuzzed, old value = 3.886963
		FUZZ WienerSize = 5; // fuzzed, old value = 5
		FUZZ TreshFactor = 0.197910; // fuzzed, old value = 0.200800
		FUZZ BlockSAdaptive = 7; // fuzzed, old value = 7
		FUZZ MaxLSSplah = 2.813795; // fuzzed, old value = 2.795620
		FUZZ MagicCoeff = 8.509614; // fuzzed, old value = 8.618952
		FUZZ SAreaTresh = 0.302347; // fuzzed, old value = 0.296142
	}

	RoutinesSettings::RoutinesSettings(int cluster, int LongestSide)
	{
		Contour_Eps1 = 1.130985;
		Contour_Eps2 = 0.680156; 

		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ LineThick_Grid = 10; // fuzzed, old value = 10
			FUZZ Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
			FUZZ Circle_GapMin = 0.096100; // fuzzed, old value = 0.096720
			FUZZ Circle_GapMax = 0.925721; // fuzzed, old value = 0.948295
			FUZZ Circle_RMax = 2.025760; // fuzzed, old value = 2.070044
			FUZZ Circle_AvgRadius = 0.000109; // fuzzed, old value = 0.000107
			FUZZ Circle_MaxRatio = 0.321018; // fuzzed, old value = 0.320620
			FUZZ Algebra_IntersectionEps = 0.010066; // fuzzed, old value = 0.010024
			FUZZ Algebra_SameLineEps = 0.211599; // fuzzed, old value = 0.213441
			FUZZ Approx_Eps1 = 1.167437; // fuzzed, old value = 1.172875
			FUZZ Approx_Eps2 = 0.888855; // fuzzed, old value = 0.888022
			FUZZ Approx_CalcLineTresh = 0.910098; // fuzzed, old value = 0.896885
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ LineThick_Grid = 10; // fuzzed, old value = 10
			FUZZ Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
			FUZZ Circle_GapMin = 0.095870; // fuzzed, old value = 0.094918
			FUZZ Circle_GapMax = 1.019180; // fuzzed, old value = 1.001200
			FUZZ Circle_RMax = 2.091001; // fuzzed, old value = 2.126840
			FUZZ Circle_AvgRadius = 0.000103; // fuzzed, old value = 0.000106
			FUZZ Circle_MaxRatio = 0.325535; // fuzzed, old value = 0.320074
			FUZZ Algebra_IntersectionEps = 0.010417; // fuzzed, old value = 0.010090
			FUZZ Algebra_SameLineEps = 0.215583; // fuzzed, old value = 0.209556
			FUZZ Approx_Eps1 = 1.183234; // fuzzed, old value = 1.200332
			FUZZ Approx_Eps2 = 0.870484; // fuzzed, old value = 0.864488
			FUZZ Approx_CalcLineTresh = 0.918594; // fuzzed, old value = 0.895633
			FUZZ Contour_Eps1 = 1.107616; // fuzzed, old value = 1.111403
			FUZZ Contour_Eps2 = 0.707938; // fuzzed, old value = 0.686504
		}
	}

	WeakSegmentatorSettings::WeakSegmentatorSettings(int cluster, int LongestSide)
	{
		SubpixelDraw = 0.5;
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ RectangularCropAreaTreshold = 0.300326; // fuzzed, old value = 0.303089
			FUZZ RectangularCropFitTreshold = 1.067597; // fuzzed, old value = 1.047984
			FUZZ RefineWidth = 0.867841; // fuzzed, old value = 0.878408
			FUZZ MinDistanceDraw = 1.378518; // fuzzed, old value = 1.359330
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ RectangularCropAreaTreshold = 0.292500; // fuzzed, old value = 0.297723
			FUZZ RectangularCropFitTreshold = 1.074478; // fuzzed, old value = 1.056949
			FUZZ RefineWidth = 0.845834; // fuzzed, old value = 0.860166
			FUZZ MinDistanceDraw = 1.308223; // fuzzed, old value = 1.320265
		}
	}

	WedgeBondExtractorSettings::WedgeBondExtractorSettings(int cluster, int LongestSide)
	{	
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ PointsCompareDist = 3; // fuzzed, old value = 3
			FUZZ SingleDownCompareDist = 2; // fuzzed, old value = 2
			FUZZ SingleDownEps = 2.967701; // fuzzed, old value = 2.986749
			FUZZ SingleDownAngleMax = 44.790036; // fuzzed, old value = 44.686832
			FUZZ SingleDownDistancesMax = 9.483096; // fuzzed, old value = 9.723407
			FUZZ SingleDownLengthMax = 43.273222; // fuzzed, old value = 43.390249
			FUZZ SingleUpRatioEps = 1.852297; // fuzzed, old value = 1.817359
			FUZZ SingleUpDefCoeff = 0.271484; // fuzzed, old value = 0.276434
			FUZZ SingleUpIncCoeff = 0.422746; // fuzzed, old value = 0.420674
			FUZZ SingleUpIncLengthTresh = 35.707890; // fuzzed, old value = 36.248318
			FUZZ SingleUpInterpolateEps = 0.061760; // fuzzed, old value = 0.060273
			FUZZ SingleUpMagicAddition = 0.223457; // fuzzed, old value = 0.220682
			FUZZ SingleUpS2Divisor = 1.674376; // fuzzed, old value = 1.652226
			FUZZ SingleUpMinATresh = 1.713060; // fuzzed, old value = 1.732313
			FUZZ SingleUpSquareRatio = 0.643772; // fuzzed, old value = 0.651217
			FUZZ SingleUpAngleTresh = 0.067078; // fuzzed, old value = 0.066675
			FUZZ SomeTresh = 0.096287; // fuzzed, old value = 0.096837
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ PointsCompareDist = 3; // fuzzed, old value = 3
			FUZZ SingleDownCompareDist = 2; // fuzzed, old value = 2
			FUZZ SingleDownEps = 3.091668; // fuzzed, old value = 3.084293
			FUZZ SingleDownAngleMax = 46.643341; // fuzzed, old value = 46.495272
			FUZZ SingleDownDistancesMax = 9.623688; // fuzzed, old value = 9.807540
			FUZZ SingleDownLengthMax = 46.422038; // fuzzed, old value = 44.286637
			FUZZ SingleUpRatioEps = 1.700450; // fuzzed, old value = 1.759887
			FUZZ SingleUpDefCoeff = 0.293211; // fuzzed, old value = 0.282408
			FUZZ SingleUpIncCoeff = 0.447362; // fuzzed, old value = 0.427804
			FUZZ SingleUpIncLengthTresh = 36.696824; // fuzzed, old value = 36.785456
			FUZZ SingleUpInterpolateEps = 0.061877; // fuzzed, old value = 0.059811
			FUZZ SingleUpMagicAddition = 0.230087; // fuzzed, old value = 0.219160
			FUZZ SingleUpS2Divisor = 1.556280; // fuzzed, old value = 1.614635
			FUZZ SingleUpMinATresh = 1.592886; // fuzzed, old value = 1.630915
			FUZZ SingleUpSquareRatio = 0.669836; // fuzzed, old value = 0.656983
			FUZZ SingleUpAngleTresh = 0.067123; // fuzzed, old value = 0.069971
			FUZZ SomeTresh = 0.102396; // fuzzed, old value = 0.097744
		}

		NormalizeBySide(SingleDownDistancesMax, LongestSide);
		NormalizeBySide(SingleUpIncLengthTresh, LongestSide);
	}

	CharactersRecognitionSettings::CharactersRecognitionSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ MaximalEndpointsUse = 7; // fuzzed, old value = 7
			FUZZ HackFor3Use = true; // fuzzed, old value = false
			FUZZ ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
			FUZZ WriteProbablyImpossibleFactor = 1.083217; // fuzzed, old value = 1.059999
			FUZZ WriteSurelyImpossibleFactor = 1.173916; // fuzzed, old value = 1.172434
			FUZZ WriteEasyFactor = 0.927424; // fuzzed, old value = 0.915540
			FUZZ WriteVeryEasyFactor = 0.838911; // fuzzed, old value = 0.840880
			FUZZ DefaultFourierClassesUse = 3; // fuzzed, old value = 3
			FUZZ PossibleCharacterDistanceStrong = 2.947747; // fuzzed, old value = 2.979810
			FUZZ PossibleCharacterDistanceWeak = 3.417408; // fuzzed, old value = 3.471420
			FUZZ PossibleCharacterMinimalQuality = 0.098672; // fuzzed, old value = 0.100693
			FUZZ DescriptorsOddFactorStrong = 2.525097; // fuzzed, old value = 2.509563
			FUZZ DescriptorsEvenFactorStrong = 3.674343; // fuzzed, old value = 3.688597
			FUZZ DescriptorsOddFactorWeak = 0.985313; // fuzzed, old value = 0.961806
			FUZZ DescriptorsEvenFactorWeak = 0.299341; // fuzzed, old value = 0.297176
			FUZZ HW_Line = 1.652416; // fuzzed, old value = 1.662506
			FUZZ HW_F = 3.195723; // fuzzed, old value = 3.234215
			FUZZ HW_Tricky = 2.636925; // fuzzed, old value = 2.665344
			FUZZ HW_Hard = 4.313760; // fuzzed, old value = 4.224281
			FUZZ HW_Other = 3.627372; // fuzzed, old value = 3.687904
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ MaximalEndpointsUse = 7; // fuzzed, old value = 7
			FUZZ HackFor3Use = false; // fuzzed, old value = false
			FUZZ ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
			FUZZ WriteProbablyImpossibleFactor = 1.038928; // fuzzed, old value = 1.040750
			FUZZ WriteSurelyImpossibleFactor = 1.174147; // fuzzed, old value = 1.158643
			FUZZ WriteEasyFactor = 0.986541; // fuzzed, old value = 0.951037
			FUZZ WriteVeryEasyFactor = 0.848332; // fuzzed, old value = 0.865599
			FUZZ DefaultFourierClassesUse = 3; // fuzzed, old value = 3
			FUZZ PossibleCharacterDistanceStrong = 3.111806; // fuzzed, old value = 2.970385
			FUZZ PossibleCharacterDistanceWeak = 3.301392; // fuzzed, old value = 3.471436
			FUZZ PossibleCharacterMinimalQuality = 0.105829; // fuzzed, old value = 0.101144
			FUZZ DescriptorsOddFactorStrong = 2.563198; // fuzzed, old value = 2.562639
			FUZZ DescriptorsEvenFactorStrong = 3.659045; // fuzzed, old value = 3.659341
			FUZZ DescriptorsOddFactorWeak = 0.956191; // fuzzed, old value = 0.933604
			FUZZ DescriptorsEvenFactorWeak = 0.292912; // fuzzed, old value = 0.290431
			FUZZ HW_Line = 1.596290; // fuzzed, old value = 1.676584
			FUZZ HW_F = 3.187493; // fuzzed, old value = 3.261839
			FUZZ HW_Tricky = 2.795053; // fuzzed, old value = 2.668167
			FUZZ HW_Hard = 4.440481; // fuzzed, old value = 4.394394
			FUZZ HW_Other = 3.836238; // fuzzed, old value = 3.771726
		}
	}

	ChemicalStructureRecognizerSettings::ChemicalStructureRecognizerSettings(int cluster, int LongestSide)
	{
		UseSimpleApproximator = false;
		if (cluster == CLUSTER_HANDWRITTING)
		{			
			FUZZ Dissolve = 0.514321; // fuzzed, old value = 0.506744
			FUZZ DeleteBadTriangles = 1.966536; // fuzzed, old value = 1.922332
			FUZZ WeakSegmentatorDist = 1; // fuzzed, old value = 1
			FUZZ LineVectorizationFactor = 1.531569; // fuzzed, old value = 1.570169
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ Dissolve = 0.479227; // fuzzed, old value = 0.497649
			FUZZ DeleteBadTriangles = 1.873039; // fuzzed, old value = 1.901966
			FUZZ WeakSegmentatorDist = 1; // fuzzed, old value = 1
			FUZZ LineVectorizationFactor = 1.637170; // fuzzed, old value = 1.630420
		}
	}

	GraphExtractorSettings::GraphExtractorSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ MinimalDistTresh = 2.004029; // fuzzed, old value = 1.977390
			FUZZ RatioSub = 0.984608; // fuzzed, old value = 0.974303
			FUZZ RatioTresh = 0.412152; // fuzzed, old value = 0.404344
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ MinimalDistTresh = 1.879082; // fuzzed, old value = 1.959499
			FUZZ RatioSub = 1.006754; // fuzzed, old value = 0.990219
			FUZZ RatioTresh = 0.428992; // fuzzed, old value = 0.409889
		}
	}

	ImageUtilsSettings::ImageUtilsSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ SlashLineDensity = 0.474664; // fuzzed, old value = 0.472121
			FUZZ TestPlusDensity = 0.410279; // fuzzed, old value = 0.407646
			FUZZ TestPlusSq = 0.428529; // fuzzed, old value = 0.418509
			FUZZ TestMinusRatio = 0.373873; // fuzzed, old value = 0.381624
			FUZZ TestMinusDensity = 0.621663; // fuzzed, old value = 0.620425
			FUZZ TestMinusHeightFactor = 0.823575; // fuzzed, old value = 0.824377
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ SlashLineDensity = 0.458063; // fuzzed, old value = 0.465765
			FUZZ TestPlusDensity = 0.410080; // fuzzed, old value = 0.418756
			FUZZ TestPlusSq = 0.405108; // fuzzed, old value = 0.418458
			FUZZ TestMinusRatio = 0.364457; // fuzzed, old value = 0.374581
			FUZZ TestMinusDensity = 0.620533; // fuzzed, old value = 0.624305
			FUZZ TestMinusHeightFactor = 0.874957; // fuzzed, old value = 0.853211
		}
	}

	SeparatorSettings::SeparatorSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ hu_1_1 = 0.206236; // fuzzed, old value = 0.206212
			FUZZ hu_1_2 = 0.082857; // fuzzed, old value = 0.081201
			FUZZ hu_0_1 = 0.247124; // fuzzed, old value = 0.244022
			FUZZ hu_1_3 = 0.083077; // fuzzed, old value = 0.083327
			FUZZ hu_0_2 = 0.252649; // fuzzed, old value = 0.246898
			FUZZ ltFactor1 = 3; // fuzzed, old value = 3
			FUZZ capHeightMin = 0.526091; // fuzzed, old value = 0.523632
			FUZZ capHeightMax = 1.462641; // fuzzed, old value = 1.489373
			FUZZ gdConst = 1.508315; // fuzzed, old value = 1.488979
			FUZZ SurfCoef = 2.967974; // fuzzed, old value = 2.950396
			FUZZ capHeightRatio = 0.252671; // fuzzed, old value = 0.247625
			FUZZ capHeightRatio2 = 1.883936; // fuzzed, old value = 1.846762
			FUZZ getRatio1 = 0.927556; // fuzzed, old value = 0.929616
			FUZZ getRatio2 = 1.055364; // fuzzed, old value = 1.064626
			FUZZ testSlashLine1 = 3.019029; // fuzzed, old value = 3.065937
			FUZZ testSlashLine2 = 2.839300; // fuzzed, old value = 2.846517
			FUZZ minDensity = 0.205953; // fuzzed, old value = 0.203749
			FUZZ maxDensity = 0.869689; // fuzzed, old value = 0.870391
			FUZZ extCapHeightMin = 0.299702; // fuzzed, old value = 0.292781
			FUZZ extCapHeightMax = 1.993425; // fuzzed, old value = 2.030029
			FUZZ extRatioMin = 0.279701; // fuzzed, old value = 0.283704
			FUZZ extRatioMax = 1.454048; // fuzzed, old value = 1.467740
			FUZZ minApproxSegsStrong = 4; // fuzzed, old value = 4
			FUZZ minApproxSegsWeak = 8; // fuzzed, old value = 8
			FUZZ specialSegmentsTreat = 4;
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ hu_1_1 = 0.201784; // fuzzed, old value = 0.204871
			FUZZ hu_1_2 = 0.080051; // fuzzed, old value = 0.080216
			FUZZ hu_0_1 = 0.234678; // fuzzed, old value = 0.237463
			FUZZ hu_1_3 = 0.082361; // fuzzed, old value = 0.082534
			FUZZ hu_0_2 = 0.242490; // fuzzed, old value = 0.249719
			FUZZ ltFactor1 = 3; // fuzzed, old value = 3
			FUZZ capHeightMin = 0.534716; // fuzzed, old value = 0.512089
			FUZZ capHeightMax = 1.469799; // fuzzed, old value = 1.481603
			FUZZ gdConst = 1.526502; // fuzzed, old value = 1.472250
			FUZZ SurfCoef = 2.982488; // fuzzed, old value = 2.922590
			FUZZ capHeightRatio = 0.249107; // fuzzed, old value = 0.245229
			FUZZ capHeightRatio2 = 1.962704; // fuzzed, old value = 1.888187
			FUZZ getRatio1 = 0.993468; // fuzzed, old value = 0.951114
			FUZZ getRatio2 = 1.097162; // fuzzed, old value = 1.058237
			FUZZ testSlashLine1 = 3.000910; // fuzzed, old value = 3.058478
			FUZZ testSlashLine2 = 2.842329; // fuzzed, old value = 2.830938
			FUZZ minDensity = 0.192198; // fuzzed, old value = 0.200432
			FUZZ maxDensity = 0.867133; // fuzzed, old value = 0.867762
			FUZZ extCapHeightMin = 0.296736; // fuzzed, old value = 0.300636
			FUZZ extCapHeightMax = 2.117304; // fuzzed, old value = 2.170688
			FUZZ extRatioMin = 0.294004; // fuzzed, old value = 0.302743
			FUZZ extRatioMax = 1.490723; // fuzzed, old value = 1.484740
			FUZZ minApproxSegsStrong = 4; // fuzzed, old value = 4
			FUZZ minApproxSegsWeak = 8; // fuzzed, old value = 8
			FUZZ specialSegmentsTreat = 4; // fuzzed, old value = 4
		}
	}

	LabelLogicSettings::LabelLogicSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ underlinePos = 0.458077; // fuzzed, old value = 0.455822
			FUZZ weightUnderline = 0.295327; // fuzzed, old value = 0.298289
			FUZZ ratioBase = 0.850364; // fuzzed, old value = 0.836667
			FUZZ ratioWeight = 0.281577; // fuzzed, old value = 0.280956
			FUZZ adjustDec = 1.236935; // fuzzed, old value = 1.241587
			FUZZ adjustInc = 0.828826; // fuzzed, old value = 0.831224
			FUZZ sameLineEps = 0.130081; // fuzzed, old value = 0.129109
			FUZZ heightRatio = 0.784089; // fuzzed, old value = 0.803107
			FUZZ medHeightFactor = 0.469961; // fuzzed, old value = 0.480666
			FUZZ capHeightError = 0.553314; // fuzzed, old value = 0.552481
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ underlinePos = 0.443050; // fuzzed, old value = 0.454582
			FUZZ weightUnderline = 0.314459; // fuzzed, old value = 0.313585
			FUZZ ratioBase = 0.820347; // fuzzed, old value = 0.812721
			FUZZ ratioWeight = 0.272321; // fuzzed, old value = 0.270907
			FUZZ adjustDec = 1.155396; // fuzzed, old value = 1.210610
			FUZZ adjustInc = 0.812229; // fuzzed, old value = 0.815348
			FUZZ sameLineEps = 0.122416; // fuzzed, old value = 0.128206
			FUZZ heightRatio = 0.819953; // fuzzed, old value = 0.802991
			FUZZ medHeightFactor = 0.472250; // fuzzed, old value = 0.490607
			FUZZ capHeightError = 0.554526; // fuzzed, old value = 0.574141
		}
	}

	LabelCombinerSettings::LabelCombinerSettings(int cluster, int LongestSide)
	{
		if (cluster == CLUSTER_HANDWRITTING)
		{
			FUZZ MaximalSymbolDistance = 2.695199; // fuzzed, old value = 2.669409
			FUZZ TestSlashLineEps = 3.084827; // fuzzed, old value = 3.010708
			FUZZ TestMinHeightFactor = 0.505587; // fuzzed, old value = 0.514248
			FUZZ TestMaxHeightFactor = 1.166178; // fuzzed, old value = 1.176732
			FUZZ RectHeightRatio = 0.497129; // fuzzed, old value = 0.491839
			FUZZ H1SuperscriptSpace = 1.151222; // fuzzed, old value = 1.134113
			FUZZ H2LowercaseSpace = 0.527924; // fuzzed, old value = 0.524777
			FUZZ H3LowercaseSpace = 0.494933; // fuzzed, old value = 0.488424
			FUZZ H4SubscriptSpace = 0.538893; // fuzzed, old value = 0.538443
			FUZZ FillLabelFactor1 = 0.488917; // fuzzed, old value = 0.495971
			FUZZ FillLabelFactor2 = 0.519302; // fuzzed, old value = 0.526847
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ MaximalSymbolDistance = 2.628279; // fuzzed, old value = 2.733513
			FUZZ TestSlashLineEps = 3.092586; // fuzzed, old value = 3.098482
			FUZZ TestMinHeightFactor = 0.489176; // fuzzed, old value = 0.503643
			FUZZ TestMaxHeightFactor = 1.161609; // fuzzed, old value = 1.186065
			FUZZ RectHeightRatio = 0.498516; // fuzzed, old value = 0.502231
			FUZZ H1SuperscriptSpace = 1.166767; // fuzzed, old value = 1.133961
			FUZZ H2LowercaseSpace = 0.504302; // fuzzed, old value = 0.516655
			FUZZ H3LowercaseSpace = 0.476277; // fuzzed, old value = 0.494162
			FUZZ H4SubscriptSpace = 0.511007; // fuzzed, old value = 0.526684
			FUZZ FillLabelFactor1 = 0.526067; // fuzzed, old value = 0.515400
			FUZZ FillLabelFactor2 = 0.511469; // fuzzed, old value = 0.524754
		}
	}
}
