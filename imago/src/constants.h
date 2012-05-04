#pragma once

namespace imago
{
	namespace consts
	{
		const int MaxImageDimensions = 1566; //fuzzed from 1600

		namespace Molecule
		{
			const double space1 = 0.307623; //fuzzed from 0.3
			const double space2 = 0.418885; //fuzzed from 0.4
			const double space3 = 0.480585; //fuzzed from 0.46
			const double spaceMul = 1.449601; //fuzzed from 1.5
			const double angTresh = 0.249862; //fuzzed from 0.25
			const double len1 = 103.398083; //fuzzed from 100.0
			const double len2 = 84.686506; //fuzzed from 85.0
		}

		namespace MultipleBond
		{
			const int LongBond = 120; //fuzzed from 125
			const double LongErr = 0.355546; //fuzzed from 0.35
			const int MediumBond = 89; //fuzzed from 85
			const double MediumErr = 0.392531; //fuzzed from 0.4
			//const int ShortBond = 20;
			const double DefaultErr = 0.633629; //fuzzed from 0.65
			const double ParLinesEps = 0.340174; //fuzzed from 0.335
			const double DoubleRatioTresh = 7.313650; //fuzzed from 7.5
			const double DoubleCoef = 0.082163; //fuzzed from 0.085
			const double DoubleMagic1 = 0.964608; //fuzzed from 0.98
			const double DoubleMagic2 = 0.973610; //fuzzed from 0.98
			const double DoubleTreshMin = 0.101401; //fuzzed from 0.1
			const double DoubleTreshMax = 0.858590; //fuzzed from 0.9

			const double MaxLen1 = 166.686972; //fuzzed from 160.0
			const double MaxLen2 = 120.978614; //fuzzed from 125.0
			const double MaxLen3 = 113.678808; //fuzzed from 110.0
			const double MaxLen4 = 110.078292; //fuzzed from 108.0
			const double MaxLen5 = 86.910405; //fuzzed from 85.0

			const double MinLen1 = 85.970779; //fuzzed from 90.0
			const double MinLen2 = 75.488563; //fuzzed from 75.0

			const double mbe1 = 0.081863; //fuzzed from 0.08
			const double mbe2 = 0.149657; //fuzzed from 0.157
			const double mbe3 = 0.202220; //fuzzed from 0.203
			const double mbe4 = 0.184702; //fuzzed from 0.185
			const double mbe5 = 0.158555; //fuzzed from 0.165
			const double mbe6 = 0.205762; //fuzzed from 0.20
			const double mbe7 = 0.387195; //fuzzed from 0.38
			const double mbe_def = 0.518222; //fuzzed from 0.5
		}

		namespace Skeleton
		{
			const double MultiBondErr = 0.288897; //fuzzed from 0.3
			const double BaseMult = 0.096796; //fuzzed from 0.1
			const double BaseSmallErr = 0.150513; //fuzzed from 0.153
			const int ShortBondLen = 21; //fuzzed from 20
			const double ShortMul = 0.305195; //fuzzed from 0.3
			const int MediumBondLen = 86; //fuzzed from 85
			const double MediumMul = 0.174502; //fuzzed from 0.175
			const double MediumSmallErr = 0.135596; //fuzzed from 0.13
			const int LongBondLen = 102; //fuzzed from 100
			const double LongMul = 0.153650; //fuzzed from 0.15
			const double LongSmallErr = 0.062265; //fuzzed from 0.06
			const double BrokenRepairFactor = 2.916799; //fuzzed from 3.0
			const double BrokenRepairCoef1 = 0.953562; //fuzzed from 1.0
			const double BrokenRepairCoef2 = 2.639729; //fuzzed from 2.7
			const double BrokenRepairAngleEps = 0.196705; //fuzzed from 0.2
			const double DissolveMinErr = 0.175928; //fuzzed from 0.17
			const double ConnectBlockS = 10.137806; //fuzzed from 10.0
			const double ConnectFactor = 2.018851; //fuzzed from 2.0
			const double JoinVerticiesConst = 0.098173; //fuzzed from 0.1
			const double DissolveConst = 0.096792; //fuzzed from 0.1
			const double Dissolve2Const = 0.201523; //fuzzed from 0.2
			const double Join2Const = 0.336929; //fuzzed from 0.33
			const double Join3Const = 0.190316; //fuzzed from 0.2
			const double DistTreshLimFactor = 1.986538; //fuzzed from 2.0
			const double SlopeFact1 = 0.098094; //fuzzed from 0.1
			const double SlopeFact2 = 0.198126; //fuzzed from 0.2
			const double ShrinkEps = 0.124899; //fuzzed from 0.13
		}

		namespace GeneralFiltering
		{
			const double MinimalLineThickness = 1.039231; //fuzzed from 1.093120
			const double MaximalLineThickness = 10.265688; //fuzzed from 9.910034
			const double MinimalInkPercentage = 0.094374; //fuzzed from 0.094627
			const double MaximalInkPercentage = 8.740140; //fuzzed from 9.047041
			const int MaxNonBWPixelsProportion = 11; //fuzzed from 11
		}

		namespace PrefilterCV
		{
			const int MinGoodPixelsCount = 18; //fuzzed from 18
			const int MaxBadToGoodRatio = 8; //fuzzed from 8
			const int BorderPartProportion = 40; //fuzzed from 42
			const int MaxRectangleCropLineWidth = 11; //fuzzed from 11
			const int StrongBinarizeSize = 4; //fuzzed from 4
			const double StrongBinarizeTresh = 1.344729; //fuzzed from 1.288367
			const int WeakBinarizeSize = 7; //fuzzed from 7
			const double WeakBinarizeTresh = 1.129019; //fuzzed from 1.178619
		}

		namespace AdaptiveFilter
		{
			const double GuessInkThresholdFactor = 0.587444; //fuzzed from 0.591245
			const int InterpolationLevel = 2; //fuzzed from 2
			const int MaxCrops = 1; //fuzzed from 1
			const int MaxRefineIterations = 2; //fuzzed from 2
			const int MaxDiffIterations = 4; //fuzzed from 4
			const int WindowSizeFactor = 2; //fuzzed from 2
		}

		namespace Prefilter
		{
			const int SpotsWindowSize = 3; //fuzzed from 3
			const double GreyTreshMinF = 1.085847; //fuzzed from 1.088456
			const double GreyTreshMaxF = 0.953415; //fuzzed from 0.917166
			const int ReduceImageDim = 269; //fuzzed from 268
			const int GaussianKernelSize = 5; //fuzzed from 5
			const int Bilateral_d = 5; //fuzzed from 5
			const double BilateralSpace = 19.414779; //fuzzed from 19.090640
			const int MinSSize = 23; //fuzzed from 23
			const int UnsharpSize = 7; //fuzzed from 7
			const double UnsharpAmount = 3.978068; //fuzzed from 3.918225
			const int WienerSize = 5; //fuzzed from 5
			const double TreshFactor = 0.197020; //fuzzed from 0.205623
			const int BlockSAdaptive = 7; //fuzzed from 7
			const double MaxLSSplah = 2.783276; //fuzzed from 2.810816
			const double MagicCoeff = 8.438847; //fuzzed from 8.652838
			const double SAreaTresh = 0.298385; //fuzzed from 0.3
		}

		namespace Main
		{
			const int DissolvingsFactor = 9; //fuzzed from 9
			const int WarningsRecalcTreshold = 2; //fuzzed from 2
		}

		namespace WedgeBondExtractor
		{
			const int PointsCompareDist = 3; //fuzzed from 3
			
			const int SingleDownCompareDist = 2; //fuzzed from 2
			const double SingleDownEps = 3.008877; //fuzzed from 2.924434
			const double SingleDownAngleMax = 45.664699; //fuzzed from 43.804412
			const double SingleDownDistancesMax = 9.742339; //fuzzed from 9.354137
			const double SingleDownLengthMax = 44.086214; //fuzzed from 42.785999
			
			const double SingleUpRatioEps = 1.839959; //fuzzed from 1.770050
			const double SingleUpDefCoeff = 0.282291; //fuzzed from 0.273103
			const double SingleUpIncCoeff = 0.416666; //fuzzed from 0.420675
			const double SingleUpIncLengthTresh = 36.420517; //fuzzed from 34.979829
			const double SingleUpInterpolateEps = 0.059793; //fuzzed from 0.062390
			const double SingleUpMagicAddition = 0.223878; //fuzzed from 0.213237
			const double SingleUpS2Divisor = 1.644773; //fuzzed from 1.577473
			const double SingleUpMinATresh = 1.701618; //fuzzed from 1.664169
			const double SingleUpSquareRatio = 0.641111; //fuzzed from 0.655334
			const double SingleUpAngleTresh = 0.067432; //fuzzed from 0.069811
			
			const double SomeTresh = 0.096512; //fuzzed from 0.1
		}

		namespace Estimation
		{
			const int DefaultLineGridSize = 10; //fuzzed from 10
			const double CircleEps = 0.000009; //fuzzed from 0.000009
			const double CircleGapMin = 0.096860; //fuzzed from 0.097346
			const double CircleGapMax = 0.971710; //fuzzed from 0.977436
			const double CircleRMax = 2.102963; //fuzzed from 2.029622
			const double CircleAvgRadius = 0.000105; //fuzzed from 0.000100
			const double CircleMaxRatio = 0.319711; //fuzzed from 0.324951
		}
		
		namespace Algebra
		{
			const double IntersectionEps = 0.010220; //fuzzed from 0.010607
			const double SameLineEps = 0.212478; //fuzzed from 0.210793
		}

		namespace Approximator
		{
			const double ApproxEps1 = 1.184722; //fuzzed from 1.151009
			const double ApproxEps2 = 0.887856; //fuzzed from 0.856642
			const double CalcLineTresh = 0.909670; //fuzzed from 0.870146
		}

		namespace CharactersRecognition
		{
			const int MaximalEndpointsUse = 7; //fuzzed from 7
			const bool HackFor3Use = true; //fuzzed from true
			const int ImpossibleToWriteDelta = 1; //fuzzed from 1
			const double WriteProbablyImpossibleFactor = 1.025579; //fuzzed from 1.005475
			const double WriteSurelyImpossibleFactor = 1.172038; //fuzzed from 1.124832
			const double WriteEasyFactor = 0.950538; //fuzzed from 0.950438
			const double WriteVeryEasyFactor = 0.861989; //fuzzed from 0.901469
			
			const int DefaultFourierClassesUse = 3; //fuzzed from 3

			const double PossibleCharacterDistanceStrong = 3.001713; //fuzzed from 3.110220
			const double PossibleCharacterDistanceWeak = 3.480779; //fuzzed from 3.337396
			const double PossibleCharacterMinimalQuality = 0.102027; //fuzzed from 0.107186

			const double DescriptorsOddFactorStrong = 2.541862; //fuzzed from 2.554166
			const double DescriptorsEvenFactorStrong = 3.715868; //fuzzed from 3.668659
			const double DescriptorsOddFactorWeak = 0.946020; //fuzzed from 0.952039
			const double DescriptorsEvenFactorWeak = 0.299552; //fuzzed from 0.308966

			const double HW_Line = 1.715817; //fuzzed from 1.755339
			const double HW_F = 3.258852; //fuzzed from 3.176429
			const double HW_Tricky = 2.613660; //fuzzed from 2.675140
			const double HW_Hard = 4.370636; //fuzzed from 4.185870
			const double HW_Other = 3.805273; //fuzzed from 3.795295
		}

		namespace ChemicalStructureRecognizer
		{
			const double Dissolve = 0.502969; //fuzzed from 0.485932
			const double DeleteBadTriangles = 1.952375; //fuzzed from 1.949059
			const double SymHeightErr = 28.212650; //fuzzed from 28.296199
			const double MaxSymRatio = 1.103637; //fuzzed from 1.088366
			const double ParLinesEps = 0.521496; //fuzzed from 0.502616
			const int WeakSegmentatorDist = 1; //fuzzed from 1
			const double LineVectorizationFactor = 1.578330; //fuzzed from 1.659550
		}

		namespace ContourExtractor
		{
			const double ApproxEps1 = 1.123741; //fuzzed from 1.071862
			const double ApproxEps2 = 0.675823; //fuzzed from 0.705507
		}

		namespace DoubleBondMaker
		{
			const double LeftLengthTresh = 0.327570; //fuzzed from 0.336559
			const double RightLengthTresh = 0.315731; //fuzzed from 0.315862
			
			const double Case1LengthTresh = 102.782043; //fuzzed from 98.753050
			const double Case1Factor = 0.450273; //fuzzed from 0.452482

			const double Case2LengthTresh = 80.980534; //fuzzed from 78.349477
			const double Case2Factor = 0.716376; //fuzzed from 0.747774

			const double Case3Factor = 0.916153; //fuzzed from 0.931997
		}

		namespace GraphExtractor
		{
			const double MinimalDistTresh = 1.980547; //fuzzed from 1.960915

			const double RatioSub = 0.982591; //fuzzed from 1.0
			const double RatioTresh = 0.390179; //fuzzed from 0.4
		}

		namespace ImageUtils
		{
			const double SlashLineDensity = 0.472098; //fuzzed from 0.471726
			const double TestPlusDensity = 0.425686; //fuzzed from 0.445301
			const double TestPlusSq = 0.421232; //fuzzed from 0.413735
			const double TestMinusRatio = 0.374708; //fuzzed from 0.362069
			const double TestMinusDensity = 0.639021; //fuzzed from 0.661621
			const double TestMinusHeightFactor = 0.827580; //fuzzed from 0.822925
		}

		namespace Separator
		{
			const int SegmentVerEps = 4; //fuzzed from 4
			const int SymHeightErr = 6; //fuzzed from 6
			const int DoubleBondDist = 20; //fuzzed from 20
			const double hu_1_1 = 0.199816; //fuzzed from 0.204424
			const double hu_1_2 = 0.081394; //fuzzed from 0.07919
			const double hu_0_1 = 0.242677; //fuzzed from 0.248338
			const double hu_1_3 = 0.082532; //fuzzed from 0.07919
			const double hu_0_2 = 0.251853; //fuzzed from 0.248338
			const int ltFactor1 = 3; //fuzzed from 3
			const double capHeightMin = 0.524367; //fuzzed from 0.5
			const double capHeightMax = 1.469542; //fuzzed from 1.5
			const double gdConst = 1.526224; //fuzzed from 1.5
			const double SurfCoef = 2.865619; //fuzzed from 3.0
			const double capHeightRatio = 0.252356; //fuzzed from 0.25
			const double capHeightRatio2 = 1.858715; //fuzzed from 1.8
			const double getRatio1 = 0.951728; //fuzzed from 0.96
			const double getRatio2 = 1.073513; //fuzzed from 1.05
			const double testSlashLine1 = 3.137464; //fuzzed from 3.2
			const double testSlashLine2 = 2.951947; //fuzzed from 3.0
			const double minDensity = 0.199442; //fuzzed from 0.2
			const double maxDensity = 0.868659; //fuzzed from 0.9
			const double extCapHeightMin = 0.285352; //fuzzed from 0.3
			const double extCapHeightMax = 2.069884; //fuzzed from 2.0
			const double extRatioMin = 0.292182; //fuzzed from 0.3
			const double extRatioMax = 1.484012; //fuzzed from 1.5
			const int minApproxSegsStrong = 4; //fuzzed from 4
			const int minApproxSegsWeak = 8; //fuzzed from 8
		}

		namespace LabelLogic
		{
			const double underlinePos = 0.461956; //fuzzed from 0.45
			const double weightUnderline = 0.305701; //fuzzed from 0.3
			const double ratioBase = 0.836528; //fuzzed from 0.8
			const double ratioWeight = 0.276296; //fuzzed from 0.266
			const double adjustDec = 1.242949; //fuzzed from 1.2
			const double adjustInc = 0.833078; //fuzzed from 0.85
			const double sameLineEps = 0.129725; //fuzzed from 0.13
			const double heightRatio = 0.824740; //fuzzed from 0.85
			const double medHeightFactor = 0.496049; //fuzzed from 0.5
			const double capHeightError = 0.565914; //fuzzed from 0.56
		}

		namespace LabelCombiner
		{
			const double MaximalSymbolDistance = 2.669776; //fuzzed from 2.808261
			const double TestSlashLineEps = 2.945150; //fuzzed from 3.093311
			const double TestMinHeightFactor = 0.501754; //fuzzed from 0.498066
			const double TestMaxHeightFactor = 1.208078; //fuzzed from 1.163865
			const double RectHeightRatio = 0.505892; //fuzzed from 0.515512
			const double H1SuperscriptSpace = 1.145896; //fuzzed from 1.120885
			const double H2LowercaseSpace = 0.522418; //fuzzed from 0.518601
			const double H3LowercaseSpace = 0.490625; //fuzzed from 0.483285
			const double H4SubscriptSpace = 0.541011; //fuzzed from 0.545265
			const double FillLabelFactor1 = 0.502930; //fuzzed from 0.482907
			const double FillLabelFactor2 = 0.518600; //fuzzed from 0.541671
		}

		namespace TripleBondMaker
		{
			const double LeftLengthTresh = 0.251075; //fuzzed from 0.263060
			const double RightLengthTresh = 0.230011; //fuzzed from 0.237006
		}

		namespace WeakSegmentator
		{
			const double RectangularCropAreaTreshold = 0.298603; //fuzzed from 0.291124
			const double RectangularCropFitTreshold = 1.049695; //fuzzed from 1.023274
			const double RefineWidth = 0.857144; //fuzzed from 0.901301
			const double MinD = 1.352319; //fuzzed from 1.379527
			const double Subpixel = 0.432968; //fuzzed from 0.440379
		}
	}
}