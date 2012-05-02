#pragma once

namespace imago
{
	namespace consts
	{
		const int MaxImageDimensions = 1549; //fuzzed from 1560

		namespace GeneralFiltering
		{
			const double MinimalLineThickness = 0.963276; //fuzzed from 1.0
			const double MaximalLineThickness = 10.155538; //fuzzed from 10.0
			const double MinimalInkPercentage = 0.101630; //fuzzed from 0.1
			const double MaximalInkPercentage = 9.549135; //fuzzed from 10.0
			const int MaxNonBWPixelsProportion = 10; //fuzzed from 10
		}

		namespace PrefilterCV
		{
			const int MinGoodPixelsCount = 15; //fuzzed from 16
			const int MaxBadToGoodRatio = 7; //fuzzed from 7
			const int BorderPartProportion = 40; //fuzzed from 40
			const int MaxRectangleCropLineWidth = 11; //fuzzed from 12
			const int StrongBinarizeSize = 4; //fuzzed from 4
			static const double StrongBinarizeTresh = 1.3;
			const int WeakBinarizeSize = 8; //fuzzed from 8
			static const double WeakBinarizeTresh = 1.2;
		}

		namespace AdaptiveFilter
		{
			const double GuessInkThresholdFactor = 0.585240; //fuzzed from 0.6
			const int InterpolationLevel = 1; //fuzzed from 2
			const int MaxCrops = 1; //fuzzed from 1
			const int MaxRefineIterations = 2; //fuzzed from 2
			const int MaxDiffIterations = 4; //fuzzed from 4
			const int WindowSizeFactor = 2; //fuzzed from 2
		}

		namespace Prefilter
		{
			const int SpotsWindowSize = 3; //fuzzed from 3
			const double GreyTreshMinF = 0.945552; //fuzzed from 0.99
			const double GreyTreshMaxF = 1.025866; //fuzzed from 1.01
			const int ReduceImageDim = 291; //fuzzed from 300
			const int GaussianKernelSize = 4; //fuzzed from 5
			const int Bilateral_d = 4; //fuzzed from 5
			const double BilateralSpace = 20.263344; //fuzzed from 20
			const int MinSSize = 20; //fuzzed from 20
			const int UnsharpSize = 7; //fuzzed from 7
			const double UnsharpAmount = 4.063936; //fuzzed from 4
			const int WienerSize = 5; //fuzzed from 5
			const double TreshFactor = 0.201410; //fuzzed from 0.2
			const int BlockSAdaptive = 6; //fuzzed from 7
			const double MaxLSSplah = 3.096852; //fuzzed from 3.0
			const double MagicCoeff = 7.889438; //fuzzed from 8.0
		}

		namespace Main
		{
			const int DissolvingsFactor = 9; //fuzzed from 10
			const int WarningsRecalcTreshold = 2; //fuzzed from 2
		}

		namespace WedgeBondExtractor
		{
			const int PointsCompareDist = 3; //fuzzed from 3
			
			const int SingleDownCompareDist = 2; //fuzzed from 2
			const double SingleDownEps = 3.256055; //fuzzed from 3.3
			const double SingleDownAngleMax = 46.866565; //fuzzed from 45.0
			const double SingleDownDistancesMax = 10.104358; //fuzzed from 10.0
			const double SingleDownLengthMax = 39.030427; //fuzzed from 40.0
			
			const double SingleUpRatioEps = 1.594451; //fuzzed from 1.6
			const double SingleUpDefCoeff = 0.289502; //fuzzed from 0.28
			const double SingleUpIncCoeff = 0.409093; //fuzzed from 0.4
			const double SingleUpIncLengthTresh = 40.115543; //fuzzed from 40
			const double SingleUpInterpolateEps = 0.071686; //fuzzed from 0.07
			const double SingleUpMagicAddition = 0.214518; //fuzzed from 0.21
			const double SingleUpS2Divisor = 1.532876; //fuzzed from 1.6
			const double SingleUpMinATresh = 1.464607; //fuzzed from 1.5
			const double SingleUpSquareRatio = 0.730967; //fuzzed from 0.7
			const double SingleUpAngleTresh = 0.065109; //fuzzed from 0.065
		}

		namespace Estimation
		{
			const int DefaultLineGridSize = 10; //fuzzed from 10
			const double CircleEps = 0.000010; //fuzzed from 0.00001
			const double CircleGapMin = 0.103393; //fuzzed from 0.1
			const double CircleGapMax = 1.035235; //fuzzed from 1.0
			const double CircleRMax = 1.928285; //fuzzed from 2
			const double CircleAvgRadius = 0.000099; //fuzzed from 0.0001
			const double CircleMaxRatio = 0.308218; //fuzzed from 0.3
		}
		
		namespace Algebra
		{
			const double IntersectionEps = 0.010432; //fuzzed from 0.01
			const double SameLineEps = 0.208715; //fuzzed from 0.2
		}

		namespace Approximator
		{
			const double ApproxEps1 = 1.167412; //fuzzed from 1.13
			const double ApproxEps2 = 0.832280; //fuzzed from 0.8
			const double CalcLineTresh = 0.996513; //fuzzed from 1.0
		}

		namespace CharactersRecognition
		{
			const int MaximalEndpointsUse = 7; //fuzzed from 7
			const bool HackFor3Use = false; //fuzzed from true
			const int ImpossibleToWriteDelta = 0; //fuzzed from 1
			const double WriteProbablyImpossibleFactor = 1.047981; //fuzzed from 1.1
			const double WriteSurelyImpossibleFactor = 1.163724; //fuzzed from 1.2
			const double WriteEasyFactor = 0.914692; //fuzzed from 0.96
			const double WriteVeryEasyFactor = 0.897925; //fuzzed from 0.9
			
			const int DefaultFourierClassesUse = 3; //fuzzed from 3

			const double PossibleCharacterDistanceStrong = 2.928840; //fuzzed from 2.8
			const double PossibleCharacterDistanceWeak = 3.479965; //fuzzed from 3.6
			const double PossibleCharacterMinimalQuality = 0.102627; //fuzzed from 0.1

			const double DescriptorsOddFactorStrong = 2.378708; //fuzzed from 2.5
			const double DescriptorsEvenFactorStrong = 3.526527; //fuzzed from 3.5
			const double DescriptorsOddFactorWeak = 0.866160; //fuzzed from 0.9
			const double DescriptorsEvenFactorWeak = 0.307109; //fuzzed from 0.3

			const double HW_Line = 1.951934; //fuzzed from 1.9
			const double HW_F = 3.432172; //fuzzed from 3.4
			const double HW_Tricky = 2.707879; //fuzzed from 2.8
			const double HW_Hard = 4.421850; //fuzzed from 4.5
			const double HW_Other = 3.362970; //fuzzed from 3.3
		}

		namespace ChemicalStructureRecognizer
		{
			const double Dissolve = 0.434449; //fuzzed from 0.45
			const double DeleteBadTriangles = 1.989492; //fuzzed from 2.0
			const double SymHeightErr = 29.264901; //fuzzed from 28
			const double MaxSymRatio = 1.138140; //fuzzed from 1.14
			const double ParLinesEps = 0.508451; //fuzzed from 0.5
			const int WeakSegmentatorDist = 1; //fuzzed from 1
			const double LineVectorizationFactor = 1.570683; //fuzzed from 1.5
		}

		namespace ContourExtractor
		{
			const double ApproxEps1 = 1.034128; //fuzzed from 1.047
			const double ApproxEps2 = 0.765210; //fuzzed from 0.8
		}

		namespace DoubleBondMaker
		{
			const double LeftLengthTresh = 0.294330; //fuzzed from 0.3
			const double RightLengthTresh = 0.286874; //fuzzed from 0.3
			
			const double Case1LengthTresh = 100.823847; //fuzzed from 100
			const double Case1Factor = 0.498725; //fuzzed from 0.5

			const double Case2LengthTresh = 86.004555; //fuzzed from 85
			const double Case2Factor = 0.765083; //fuzzed from 0.75

			const double Case3Factor = 0.968841; //fuzzed from 0.97
		}

		namespace GraphExtractor
		{
			const double MinimalDistTresh = 2.057433; //fuzzed from 2.0
		}

		namespace ImageUtils
		{
			const double SlashLineDensity = 0.442006; //fuzzed from 0.46
			const double TestPlusDensity = 0.395618; //fuzzed from 0.4
			const double TestPlusSq = 0.383574; //fuzzed from 0.38
			const double TestMinusRatio = 0.345588; //fuzzed from 0.33
			const double TestMinusDensity = 0.785065; //fuzzed from 0.75
			const double TestMinusHeightFactor = 0.772515; //fuzzed from 0.75
		}

		namespace LabelCombiner
		{
			const double MaximalSymbolDistance = 3.066620; //fuzzed from 3.0
			const double TestSlashLineEps = 3.324196; //fuzzed from 3.3
			const double TestMinHeightFactor = 0.429280; //fuzzed from 0.45
			const double TestMaxHeightFactor = 1.196266; //fuzzed from 1.2
			const double RectHeightRatio = 0.501611; //fuzzed from 0.5
			const double H1SuperscriptSpace = 1.076036; //fuzzed from 1.1
			const double H2LowercaseSpace = 0.613905; //fuzzed from 0.6
			const double H3LowercaseSpace = 0.486377; //fuzzed from 0.5
			const double H4SubscriptSpace = 0.518881; //fuzzed from 0.5
			const double FillLabelFactor1 = 0.475040; //fuzzed from 0.5
			const double FillLabelFactor2 = 0.497684; //fuzzed from 0.5
		}

		namespace TripleBondMaker
		{
			const double LeftLengthTresh = 0.237502; //fuzzed from 0.25
			const double RightLengthTresh = 0.238204; //fuzzed from 0.25
		}

		namespace WeakSegmentator
		{
			const double RectangularCropAreaTreshold = 0.293852; //fuzzed from 0.3
			const double RectangularCropFitTreshold = 0.986268; //fuzzed from 0.95
			const double RefineWidth = 0.867308; //fuzzed from 0.9
			const double MinD = 1.469217; //fuzzed from 1.5
			const double Subpixel = 0.507345; //fuzzed from 0.5
		}
	}
}