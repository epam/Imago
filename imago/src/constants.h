#pragma once

namespace imago
{
	namespace consts
	{
		const int MaxImageDimensions = 1573; //fuzzed from 1581

		namespace GeneralFiltering
		{
			const double MinimalLineThickness = 1.093120; //fuzzed from 1.104232
			const double MaximalLineThickness = 9.910034; //fuzzed from 9.571711
			const double MinimalInkPercentage = 0.094627; //fuzzed from 0.091585
			const double MaximalInkPercentage = 9.047041; //fuzzed from 9.246460
			const int MaxNonBWPixelsProportion = 11; //fuzzed from 11
		}

		namespace PrefilterCV
		{
			const int MinGoodPixelsCount = 18; //fuzzed from 18
			const int MaxBadToGoodRatio = 8; //fuzzed from 8
			const int BorderPartProportion = 42; //fuzzed from 41
			const int MaxRectangleCropLineWidth = 11; //fuzzed from 11
			const int StrongBinarizeSize = 4; //fuzzed from 4
			const double StrongBinarizeTresh = 1.288367; //fuzzed from 1.3
			const int WeakBinarizeSize = 7; //fuzzed from 7
			const double WeakBinarizeTresh = 1.178619; //fuzzed from 1.2
		}

		namespace AdaptiveFilter
		{
			const double GuessInkThresholdFactor = 0.591245; //fuzzed from 0.596047
			const int InterpolationLevel = 2; //fuzzed from 2
			const int MaxCrops = 1; //fuzzed from 1
			const int MaxRefineIterations = 2; //fuzzed from 2
			const int MaxDiffIterations = 4; //fuzzed from 4
			const int WindowSizeFactor = 2; //fuzzed from 2
		}

		namespace Prefilter
		{
			const int SpotsWindowSize = 3; //fuzzed from 3
			const double GreyTreshMinF = 1.088456; //fuzzed from 1.050166
			const double GreyTreshMaxF = 0.917166; //fuzzed from 0.888928
			const int ReduceImageDim = 268; //fuzzed from 271
			const int GaussianKernelSize = 5; //fuzzed from 5
			const int Bilateral_d = 5; //fuzzed from 5
			const double BilateralSpace = 19.090640; //fuzzed from 19.585025
			const int MinSSize = 23; //fuzzed from 22
			const int UnsharpSize = 7; //fuzzed from 7
			const double UnsharpAmount = 3.918225; //fuzzed from 3.787088
			const int WienerSize = 5; //fuzzed from 5
			const double TreshFactor = 0.205623; //fuzzed from 0.204337
			const int BlockSAdaptive = 7; //fuzzed from 7
			const double MaxLSSplah = 2.810816; //fuzzed from 2.816809
			const double MagicCoeff = 8.652838; //fuzzed from 8.879879
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
			const double SingleDownEps = 2.924434; //fuzzed from 3.031920
			const double SingleDownAngleMax = 43.804412; //fuzzed from 42.823782
			const double SingleDownDistancesMax = 9.354137; //fuzzed from 9.213881
			const double SingleDownLengthMax = 42.785999; //fuzzed from 41.262093
			
			const double SingleUpRatioEps = 1.770050; //fuzzed from 1.750987
			const double SingleUpDefCoeff = 0.273103; //fuzzed from 0.278988
			const double SingleUpIncCoeff = 0.420675; //fuzzed from 0.433114
			const double SingleUpIncLengthTresh = 34.979829; //fuzzed from 35.186773
			const double SingleUpInterpolateEps = 0.062390; //fuzzed from 0.062678
			const double SingleUpMagicAddition = 0.213237; //fuzzed from 0.216350
			const double SingleUpS2Divisor = 1.577473; //fuzzed from 1.601459
			const double SingleUpMinATresh = 1.664169; //fuzzed from 1.611784
			const double SingleUpSquareRatio = 0.655334; //fuzzed from 0.656748
			const double SingleUpAngleTresh = 0.069811; //fuzzed from 0.071140
		}

		namespace Estimation
		{
			const int DefaultLineGridSize = 10; //fuzzed from 10
			const double CircleEps = 0.000009; //fuzzed from 0.000009
			const double CircleGapMin = 0.097346; //fuzzed from 0.099763
			const double CircleGapMax = 0.977436; //fuzzed from 0.975475
			const double CircleRMax = 2.029622; //fuzzed from 2.062937
			const double CircleAvgRadius = 0.000100; //fuzzed from 0.000102
			const double CircleMaxRatio = 0.324951; //fuzzed from 0.330572
		}
		
		namespace Algebra
		{
			const double IntersectionEps = 0.010607; //fuzzed from 0.010765
			const double SameLineEps = 0.210793; //fuzzed from 0.205654
		}

		namespace Approximator
		{
			const double ApproxEps1 = 1.151009; //fuzzed from 1.133470
			const double ApproxEps2 = 0.856642; //fuzzed from 0.874279
			const double CalcLineTresh = 0.870146; //fuzzed from 0.893227
		}

		namespace CharactersRecognition
		{
			const int MaximalEndpointsUse = 7; //fuzzed from 7
			const bool HackFor3Use = true; //fuzzed from true
			const int ImpossibleToWriteDelta = 1; //fuzzed from 1
			const double WriteProbablyImpossibleFactor = 1.005475; //fuzzed from 1.004899
			const double WriteSurelyImpossibleFactor = 1.124832; //fuzzed from 1.128271
			const double WriteEasyFactor = 0.950438; //fuzzed from 0.951683
			const double WriteVeryEasyFactor = 0.901469; //fuzzed from 0.878552
			
			const int DefaultFourierClassesUse = 3; //fuzzed from 3

			const double PossibleCharacterDistanceStrong = 3.110220; //fuzzed from 3.055896
			const double PossibleCharacterDistanceWeak = 3.337396; //fuzzed from 3.376600
			const double PossibleCharacterMinimalQuality = 0.107186; //fuzzed from 0.108302

			const double DescriptorsOddFactorStrong = 2.554166; //fuzzed from 2.589620
			const double DescriptorsEvenFactorStrong = 3.668659; //fuzzed from 3.715032
			const double DescriptorsOddFactorWeak = 0.952039; //fuzzed from 0.956537
			const double DescriptorsEvenFactorWeak = 0.308966; //fuzzed from 0.302464

			const double HW_Line = 1.755339; //fuzzed from 1.703336
			const double HW_F = 3.176429; //fuzzed from 3.277002
			const double HW_Tricky = 2.675140; //fuzzed from 2.725518
			const double HW_Hard = 4.185870; //fuzzed from 4.323407
			const double HW_Other = 3.795295; //fuzzed from 3.706483
		}

		namespace ChemicalStructureRecognizer
		{
			const double Dissolve = 0.485932; //fuzzed from 0.503661
			const double DeleteBadTriangles = 1.949059; //fuzzed from 1.971274
			const double SymHeightErr = 28.296199; //fuzzed from 28.951613
			const double MaxSymRatio = 1.088366; //fuzzed from 1.068700
			const double ParLinesEps = 0.502616; //fuzzed from 0.491602
			const int WeakSegmentatorDist = 1; //fuzzed from 1
			const double LineVectorizationFactor = 1.659550; //fuzzed from 1.675289
		}

		namespace ContourExtractor
		{
			const double ApproxEps1 = 1.071862; //fuzzed from 1.100397
			const double ApproxEps2 = 0.705507; //fuzzed from 0.728108
		}

		namespace DoubleBondMaker
		{
			const double LeftLengthTresh = 0.336559; //fuzzed from 0.330549
			const double RightLengthTresh = 0.315862; //fuzzed from 0.324925
			
			const double Case1LengthTresh = 98.753050; //fuzzed from 100.440611
			const double Case1Factor = 0.452482; //fuzzed from 0.458970

			const double Case2LengthTresh = 78.349477; //fuzzed from 80.863426
			const double Case2Factor = 0.747774; //fuzzed from 0.738467

			const double Case3Factor = 0.931997; //fuzzed from 0.963217
		}

		namespace GraphExtractor
		{
			const double MinimalDistTresh = 1.960915; //fuzzed from 1.984184
		}

		namespace ImageUtils
		{
			const double SlashLineDensity = 0.471726; //fuzzed from 0.460058
			const double TestPlusDensity = 0.445301; //fuzzed from 0.440466
			const double TestPlusSq = 0.413735; //fuzzed from 0.427367
			const double TestMinusRatio = 0.362069; //fuzzed from 0.360811
			const double TestMinusDensity = 0.661621; //fuzzed from 0.665978
			const double TestMinusHeightFactor = 0.822925; //fuzzed from 0.804078
		}

		namespace LabelCombiner
		{
			const double MaximalSymbolDistance = 2.808261; //fuzzed from 2.789892
			const double TestSlashLineEps = 3.093311; //fuzzed from 2.997149
			const double TestMinHeightFactor = 0.498066; //fuzzed from 0.492815
			const double TestMaxHeightFactor = 1.163865; //fuzzed from 1.155152
			const double RectHeightRatio = 0.515512; //fuzzed from 0.535243
			const double H1SuperscriptSpace = 1.120885; //fuzzed from 1.106576
			const double H2LowercaseSpace = 0.518601; //fuzzed from 0.526337
			const double H3LowercaseSpace = 0.483285; //fuzzed from 0.495203
			const double H4SubscriptSpace = 0.545265; //fuzzed from 0.532340
			const double FillLabelFactor1 = 0.482907; //fuzzed from 0.470841
			const double FillLabelFactor2 = 0.541671; //fuzzed from 0.556324
		}

		namespace TripleBondMaker
		{
			const double LeftLengthTresh = 0.263060; //fuzzed from 0.253636
			const double RightLengthTresh = 0.237006; //fuzzed from 0.244363
		}

		namespace WeakSegmentator
		{
			const double RectangularCropAreaTreshold = 0.291124; //fuzzed from 0.290690
			const double RectangularCropFitTreshold = 1.023274; //fuzzed from 1.016868
			const double RefineWidth = 0.901301; //fuzzed from 0.911931
			const double MinD = 1.379527; //fuzzed from 1.340012
			const double Subpixel = 0.440379; //fuzzed from 0.450875
		}
	}
}