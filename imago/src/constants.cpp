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
			FUZZ LengthFactor_long = 0.301128; // fuzzed, old value = 0.302295
			FUZZ LengthFactor_medium = 0.412195; // fuzzed, old value = 0.416900
			FUZZ LengthFactor_default = 0.478946; // fuzzed, old value = 0.489521
			FUZZ LengthValue_long = 104.576605; // fuzzed, old value = 105.278715
			FUZZ LengthValue_medium = 83.828508; // fuzzed, old value = 82.756203
			FUZZ SpaceMultiply = 1.433167; // fuzzed, old value = 1.452524
			FUZZ AngleTreshold = 0.259030; // fuzzed, old value = 0.255156
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
			FUZZ AddVertexEps = 5.099192; // fuzzed, old value = 5.2
			FUZZ MaxSymRatio = 1.122616; // fuzzed, old value = 1.117503
			FUZZ MinSymRatio = 0.341869; // fuzzed, old value = 0.34
			FUZZ ParLinesEps = 0.513057; // fuzzed, old value = 0.518003
			FUZZ SymHeightErr = 27.170494; // fuzzed, old value = 27.752118
			FUZZ CapitalHeightError = 0.839837; // fuzzed, old value = 0.85
			FUZZ DoubleBondDist = 20; // fuzzed, old value = 20
			FUZZ SegmentVerEps = 4; // fuzzed, old value = 4
			FUZZ CharactersSpaceCoeff = 0.391240; // fuzzed, old value = 0.4
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
			FUZZ LongBond = 118; // fuzzed, old value = 118
			FUZZ LongErr = 0.360257; // fuzzed, old value = 0.355489
			FUZZ MediumBond = 88; // fuzzed, old value = 88
			FUZZ MediumErr = 0.388901; // fuzzed, old value = 0.396206
			FUZZ DefaultErr = 0.640971; // fuzzed, old value = 0.649183
			FUZZ ParBondsEps = 0.349066; // fuzzed, old value = 0.342145
			FUZZ DoubleRatioTresh = 7.457044; // fuzzed, old value = 7.477073
			FUZZ DoubleCoef = 0.080466; // fuzzed, old value = 0.081729
			FUZZ DoubleMagic1 = 0.948187; // fuzzed, old value = 0.943214
			FUZZ DoubleMagic2 = 0.984298; // fuzzed, old value = 0.977482
			FUZZ DoubleTreshMin = 0.101160; // fuzzed, old value = 0.100961
			FUZZ DoubleTreshMax = 0.868968; // fuzzed, old value = 0.854722

			FUZZ MaxLen1 = 164.846209; // fuzzed, old value = 165.079341
			FUZZ MaxLen2 = 122.787381; // fuzzed, old value = 119.844128
			FUZZ MaxLen3 = 115.223338; // fuzzed, old value = 114.410745
			FUZZ MaxLen4 = 109.669810; // fuzzed, old value = 112.350859
			FUZZ MaxLen5 = 85.478967; // fuzzed, old value = 85.481902

			FUZZ MinLen1 = 85.904719; // fuzzed, old value = 84.396100
			FUZZ MinLen2 = 76.648276; // fuzzed, old value = 74.825703

			FUZZ mbe1 = 0.081553; // fuzzed, old value = 0.080418
			FUZZ mbe2 = 0.150084; // fuzzed, old value = 0.146740
			FUZZ mbe3 = 0.207396; // fuzzed, old value = 0.203068
			FUZZ mbe4 = 0.186034; // fuzzed, old value = 0.185673
			FUZZ mbe5 = 0.156560; // fuzzed, old value = 0.155507
			FUZZ mbe6 = 0.207583; // fuzzed, old value = 0.207372
			FUZZ mbe7 = 0.403671; // fuzzed, old value = 0.395602
			FUZZ mbe_def = 0.517421; // fuzzed, old value = 0.519484

			FUZZ DoubleLeftLengthTresh = 0.327897; // fuzzed, old value = 0.320683
			FUZZ DoubleRightLengthTresh = 0.299122; // fuzzed, old value = 0.300917
			FUZZ TripleLeftLengthTresh = 0.261856; // fuzzed, old value = 0.257080
			FUZZ TripleRightLengthTresh = 0.221299; // fuzzed, old value = 0.226614
			FUZZ Case1LengthTresh = 103.451970; // fuzzed, old value = 104.968905
			FUZZ Case1Factor = 0.446116; // fuzzed, old value = 0.445369
			FUZZ Case2LengthTresh = 83.007771; // fuzzed, old value = 81.119412
			FUZZ Case2Factor = 0.700996; // fuzzed, old value = 0.718709
			FUZZ Case3Factor = 0.944560; // fuzzed, old value = 0.932437
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
			FUZZ BaseMult = 0.095763; // fuzzed, old value = 0.096231
			FUZZ BaseSmallErr = 0.152079; // fuzzed, old value = 0.153246
			FUZZ ShortBondLen = 21; // fuzzed, old value = 21
			FUZZ ShortMul = 0.305612; // fuzzed, old value = 0.299155
			FUZZ MediumBondLen = 89; // fuzzed, old value = 88
			FUZZ MediumMul = 0.175148; // fuzzed, old value = 0.175140
			FUZZ MediumSmallErr = 0.130098; // fuzzed, old value = 0.132227
			FUZZ LongBondLen = 103; // fuzzed, old value = 104
			FUZZ LongMul = 0.153756; // fuzzed, old value = 0.153505
			FUZZ LongSmallErr = 0.063796; // fuzzed, old value = 0.062575
			FUZZ BrokenRepairFactor = 2.876024; // fuzzed, old value = 2.862368
			FUZZ BrokenRepairCoef1 = 0.977421; // fuzzed, old value = 0.976380
			FUZZ BrokenRepairCoef2 = 2.688826; // fuzzed, old value = 2.623788
			FUZZ BrokenRepairAngleEps = 0.189200; // fuzzed, old value = 0.192211
			FUZZ DissolveMinErr = 0.175111; // fuzzed, old value = 0.178148
			FUZZ ConnectBlockS = 10.168268; // fuzzed, old value = 9.948668
			FUZZ ConnectFactor = 2.035299; // fuzzed, old value = 1.986648
			FUZZ JoinVerticiesConst = 0.101178; // fuzzed, old value = 0.100288
			FUZZ DissolveConst = 0.095184; // fuzzed, old value = 0.094904
			FUZZ Dissolve2Const = 0.196931; // fuzzed, old value = 0.199403
			FUZZ Join2Const = 0.324191; // fuzzed, old value = 0.330019
			FUZZ Join3Const = 0.188224; // fuzzed, old value = 0.192238
			FUZZ DistTreshLimFactor = 1.939525; // fuzzed, old value = 1.960246
			FUZZ SlopeFact1 = 0.099649; // fuzzed, old value = 0.099581
			FUZZ SlopeFact2 = 0.192488; // fuzzed, old value = 0.195806
			FUZZ ShrinkEps = 0.125260; // fuzzed, old value = 0.127217
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
			FUZZ Contour_Eps1 = 1.139208; // fuzzed, old value = 1.130985
			FUZZ Contour_Eps2 = 0.664179; // fuzzed, old value = 0.680156
		}
		else if (cluster == CLUSTER_SCANNED)
		{
			FUZZ LineThick_Grid = 10; // fuzzed, old value = 10
			FUZZ Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
			FUZZ Circle_GapMin = 0.094918; // fuzzed, old value = 0.095199
			FUZZ Circle_GapMax = 1.001200; // fuzzed, old value = 0.991844
			FUZZ Circle_RMax = 2.126840; // fuzzed, old value = 2.121933
			FUZZ Circle_AvgRadius = 0.000106; // fuzzed, old value = 0.000104
			FUZZ Circle_MaxRatio = 0.320074; // fuzzed, old value = 0.319843
			FUZZ Algebra_IntersectionEps = 0.010090; // fuzzed, old value = 0.010301
			FUZZ Algebra_SameLineEps = 0.209556; // fuzzed, old value = 0.212025
			FUZZ Approx_Eps1 = 1.200332; // fuzzed, old value = 1.196108
			FUZZ Approx_Eps2 = 0.864488; // fuzzed, old value = 0.885824
			FUZZ Approx_CalcLineTresh = 0.895633; // fuzzed, old value = 0.894839
			FUZZ Contour_Eps1 = 1.096938; // fuzzed, old value = 1.111403
			FUZZ Contour_Eps2 = 0.692346; // fuzzed, old value = 0.686504
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
			FUZZ SingleDownEps = 3.084293; // fuzzed, old value = 3.037281
			FUZZ SingleDownAngleMax = 46.495272; // fuzzed, old value = 46.091739
			FUZZ SingleDownDistancesMax = 9.807540; // fuzzed, old value = 9.960804
			FUZZ SingleDownLengthMax = 44.286637; // fuzzed, old value = 43.239626
			FUZZ SingleUpRatioEps = 1.759887; // fuzzed, old value = 1.802933
			FUZZ SingleUpDefCoeff = 0.282408; // fuzzed, old value = 0.277813
			FUZZ SingleUpIncCoeff = 0.427804; // fuzzed, old value = 0.424824
			FUZZ SingleUpIncLengthTresh = 36.785456; // fuzzed, old value = 35.891082
			FUZZ SingleUpInterpolateEps = 0.059811; // fuzzed, old value = 0.059528
			FUZZ SingleUpMagicAddition = 0.219160; // fuzzed, old value = 0.222498
			FUZZ SingleUpS2Divisor = 1.614635; // fuzzed, old value = 1.616496
			FUZZ SingleUpMinATresh = 1.630915; // fuzzed, old value = 1.669259
			FUZZ SingleUpSquareRatio = 0.656983; // fuzzed, old value = 0.651850
			FUZZ SingleUpAngleTresh = 0.069971; // fuzzed, old value = 0.068571
			FUZZ SomeTresh = 0.097744; // fuzzed, old value = 0.098846
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
			FUZZ HackFor3Use = false; // fuzzed, old value = true
			FUZZ ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
			FUZZ WriteProbablyImpossibleFactor = 1.040750; // fuzzed, old value = 1.064738
			FUZZ WriteSurelyImpossibleFactor = 1.158643; // fuzzed, old value = 1.167453
			FUZZ WriteEasyFactor = 0.951037; // fuzzed, old value = 0.930131
			FUZZ WriteVeryEasyFactor = 0.865599; // fuzzed, old value = 0.865807
			FUZZ DefaultFourierClassesUse = 3; // fuzzed, old value = 3
			FUZZ PossibleCharacterDistanceStrong = 2.970385; // fuzzed, old value = 2.932504
			FUZZ PossibleCharacterDistanceWeak = 3.471436; // fuzzed, old value = 3.386928
			FUZZ PossibleCharacterMinimalQuality = 0.101144; // fuzzed, old value = 0.102540
			FUZZ DescriptorsOddFactorStrong = 2.562639; // fuzzed, old value = 2.524500
			FUZZ DescriptorsEvenFactorStrong = 3.659341; // fuzzed, old value = 3.666926
			FUZZ DescriptorsOddFactorWeak = 0.933604; // fuzzed, old value = 0.939928
			FUZZ DescriptorsEvenFactorWeak = 0.290431; // fuzzed, old value = 0.290855
			FUZZ HW_Line = 1.676584; // fuzzed, old value = 1.650729
			FUZZ HW_F = 3.261839; // fuzzed, old value = 3.197663
			FUZZ HW_Tricky = 2.668167; // fuzzed, old value = 2.665887
			FUZZ HW_Hard = 4.394394; // fuzzed, old value = 4.318542
			FUZZ HW_Other = 3.771726; // fuzzed, old value = 3.802253
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
			FUZZ Dissolve = 0.497649; // fuzzed, old value = 0.500003
			FUZZ DeleteBadTriangles = 1.901966; // fuzzed, old value = 1.948795
			FUZZ WeakSegmentatorDist = 1; // fuzzed, old value = 1
			FUZZ LineVectorizationFactor = 1.630420; // fuzzed, old value = 1.603001
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
			FUZZ MinimalDistTresh = 1.959499; // fuzzed, old value = 1.975386
			FUZZ RatioSub = 0.990219; // fuzzed, old value = 0.984835
			FUZZ RatioTresh = 0.409889; // fuzzed, old value = 0.405199
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
			FUZZ SlashLineDensity = 0.465765; // fuzzed, old value = 0.468904
			FUZZ TestPlusDensity = 0.418756; // fuzzed, old value = 0.419729
			FUZZ TestPlusSq = 0.418458; // fuzzed, old value = 0.411096
			FUZZ TestMinusRatio = 0.374581; // fuzzed, old value = 0.375646
			FUZZ TestMinusDensity = 0.624305; // fuzzed, old value = 0.627725
			FUZZ TestMinusHeightFactor = 0.853211; // fuzzed, old value = 0.847227
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
			FUZZ hu_1_1 = 0.204871; // fuzzed, old value = 0.201145
			FUZZ hu_1_2 = 0.080216; // fuzzed, old value = 0.081378
			FUZZ hu_0_1 = 0.237463; // fuzzed, old value = 0.241186
			FUZZ hu_1_3 = 0.082534; // fuzzed, old value = 0.083413
			FUZZ hu_0_2 = 0.249719; // fuzzed, old value = 0.252930
			FUZZ ltFactor1 = 3; // fuzzed, old value = 3
			FUZZ capHeightMin = 0.512089; // fuzzed, old value = 0.516019
			FUZZ capHeightMax = 1.481603; // fuzzed, old value = 1.479097
			FUZZ gdConst = 1.472250; // fuzzed, old value = 1.463841
			FUZZ SurfCoef = 2.922590; // fuzzed, old value = 2.856316
			FUZZ capHeightRatio = 0.245229; // fuzzed, old value = 0.250151
			FUZZ capHeightRatio2 = 1.888187; // fuzzed, old value = 1.868526
			FUZZ getRatio1 = 0.951114; // fuzzed, old value = 0.951051
			FUZZ getRatio2 = 1.058237; // fuzzed, old value = 1.046180
			FUZZ testSlashLine1 = 3.058478; // fuzzed, old value = 3.057179
			FUZZ testSlashLine2 = 2.830938; // fuzzed, old value = 2.835904
			FUZZ minDensity = 0.200432; // fuzzed, old value = 0.203868
			FUZZ maxDensity = 0.867762; // fuzzed, old value = 0.865589
			FUZZ extCapHeightMin = 0.300636; // fuzzed, old value = 0.294801
			FUZZ extCapHeightMax = 2.170688; // fuzzed, old value = 2.119376
			FUZZ extRatioMin = 0.302743; // fuzzed, old value = 0.296814
			FUZZ extRatioMax = 1.484740; // fuzzed, old value = 1.488917
			FUZZ minApproxSegsStrong = 4; // fuzzed, old value = 4
			FUZZ minApproxSegsWeak = 8; // fuzzed, old value = 8
			FUZZ specialSegmentsTreat = 4;
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
			FUZZ underlinePos = 0.454582; // fuzzed, old value = 0.446929
			FUZZ weightUnderline = 0.313585; // fuzzed, old value = 0.306985
			FUZZ ratioBase = 0.812721; // fuzzed, old value = 0.818071
			FUZZ ratioWeight = 0.270907; // fuzzed, old value = 0.276132
			FUZZ adjustDec = 1.210610; // fuzzed, old value = 1.202880
			FUZZ adjustInc = 0.815348; // fuzzed, old value = 0.819723
			FUZZ sameLineEps = 0.128206; // fuzzed, old value = 0.131433
			FUZZ heightRatio = 0.802991; // fuzzed, old value = 0.797775
			FUZZ medHeightFactor = 0.490607; // fuzzed, old value = 0.496510
			FUZZ capHeightError = 0.574141; // fuzzed, old value = 0.569408
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
			FUZZ MaximalSymbolDistance = 2.733513; // fuzzed, old value = 2.718961
			FUZZ TestSlashLineEps = 3.098482; // fuzzed, old value = 3.060226
			FUZZ TestMinHeightFactor = 0.503643; // fuzzed, old value = 0.506338
			FUZZ TestMaxHeightFactor = 1.186065; // fuzzed, old value = 1.179112
			FUZZ RectHeightRatio = 0.502231; // fuzzed, old value = 0.493299
			FUZZ H1SuperscriptSpace = 1.133961; // fuzzed, old value = 1.121025
			FUZZ H2LowercaseSpace = 0.516655; // fuzzed, old value = 0.509972
			FUZZ H3LowercaseSpace = 0.494162; // fuzzed, old value = 0.483682
			FUZZ H4SubscriptSpace = 0.526684; // fuzzed, old value = 0.524257
			FUZZ FillLabelFactor1 = 0.515400; // fuzzed, old value = 0.510524
			FUZZ FillLabelFactor2 = 0.524754; // fuzzed, old value = 0.514933
		}
	}
}
