#pragma once

namespace imago
{
	namespace consts
	{
		const int MaxImageDimensions = 1560;

		namespace GeneralFiltering
		{
			const double MinimalLineThickness = 1.0;
			const double MaximalLineThickness = 10.0;
			const double MinimalInkPercentage = 0.1;
			const double MaximalInkPercentage = 10.0;
			const int MaxNonBWPixelsProportion = 10;
		}

		namespace PrefilterCV
		{
			const int MinGoodPixelsCount = 10;
			const int MaxBadToGoodRatio = 6;
			const int BorderPartProportion = 40;
			const int MaxRectangleCropLineWidth = 12;
			const int StrongBinarizeSize = 4;
			const double StrongBinarizeTresh = 1.3;
			const int WeakBinarizeSize = 8;
			const double WeakBinarizeTresh = 1.2;
		}

		namespace AdaptiveFilter
		{
			const double GuessInkThresholdFactor = 0.6;
			const int InterpolationLevel = 2;
			const int MaxCrops = 1;
			const int MaxRefineIterations = 2;
			const int MaxDiffIterations = 4;
			const int WindowSizeFactor = 2;
		}

		namespace Prefilter
		{
			const int SpotsWindowSize = 3;
			const double GreyTreshMinF = 0.99;
			const double GreyTreshMaxF = 1.01;
			const int ReduceImageDim = 300;
			const int GaussianKernelSize = 5;
			const int Bilateral_d = 5;
			const double BilateralSpace = 20;
			const int MinSSize = 20;
			const int UnsharpSize = 7;
			const double UnsharpAmount = 4;
			const int WienerSize = 5;
			const double TreshFactor = 0.2;
			const int BlockSAdaptive = 7;
			const double MaxLSSplah = 3.0;
			const double MagicCoeff = 8.0;
		}

		namespace Main
		{
			const int DissolvingsFactor = 10;
			const int WarningsRecalcTreshold = 2;
		}

		namespace WedgeBondExtractor
		{
			const int PointsCompareDist = 3;
			
			const int SingleDownCompareDist = 2;
			const double SingleDownEps = 3.3;
			const double SingleDownAngleMax = 45.0;
			const double SingleDownDistancesMax = 10.0;
			const double SingleDownLengthMax = 40.0;
			
			const double SingleUpRatioEps = 1.6;
			const double SingleUpDefCoeff = 0.28;
			const double SingleUpIncCoeff = 0.4;
			const double SingleUpIncLengthTresh = 40;
			const double SingleUpInterpolateEps = 0.07;
			const double SingleUpMagicAddition = 0.21;
			const double SingleUpS2Divisor = 1.6;
			const double SingleUpMinATresh = 1.5;
			const double SingleUpSquareRatio = 0.7;
			const double SingleUpAngleTresh = 0.065;
		}

		namespace Estimation
		{
			const int DefaultLineGridSize = 10;
			const double CircleEps = 0.00001;
			const double CircleGapMin = 0.1;
			const double CircleGapMax = 1.0;
			const double CircleRMax = 2;
			const double CircleAvgRadius = 0.0001;
			const double CircleMaxRatio = 0.3;
		}
		
		namespace Algebra
		{
			const double IntersectionEps = 0.01;
			const double SameLineEps = 0.2;
		}

		namespace Approximator
		{
			const double ApproxEps1 = 1.13;
			const double ApproxEps2 = 0.8;
			const double CalcLineTresh = 1.0;
		}

		namespace CharactersRecognition
		{
			const int MaximalEndpointsUse = 7;
			const bool HackFor3Use = true;
			const int ImpossibleToWriteDelta = 1; // [1,2]
			const double WriteProbablyImpossibleFactor = 1.1;
			const double WriteSurelyImpossibleFactor = 1.2;
			const double WriteEasyFactor = 0.96;
			const double WriteVeryEasyFactor = 0.9;
			
			const int DefaultFourierClassesUse = 3;

			const double PossibleCharacterDistanceStrong = 2.8;
			const double PossibleCharacterDistanceWeak = 3.6;
			const double PossibleCharacterMinimalQuality = 0.1;

			const double DescriptorsOddFactorStrong = 2.5;
			const double DescriptorsEvenFactorStrong = 3.5;
			const double DescriptorsOddFactorWeak = 0.9;
			const double DescriptorsEvenFactorWeak = 0.3;

			const double HW_Line = 1.9;
			const double HW_F = 3.4;
			const double HW_Tricky = 2.8;
			const double HW_Hard = 4.5;
			const double HW_Other = 3.3;
		}

		namespace ChemicalStructureRecognizer
		{
			const double Dissolve = 0.45;
			const double DeleteBadTriangles = 2.0;
			const double SymHeightErr = 28;
			const double MaxSymRatio = 1.14;
			const double ParLinesEps = 0.5;
			const int WeakSegmentatorDist = 1;
			const double LineVectorizationFactor = 1.5;
		}

		namespace ContourExtractor
		{
			const double ApproxEps1 = 1.047;
			const double ApproxEps2 = 0.8;
		}

		namespace DoubleBondMaker
		{
			const double LeftLengthTresh = 0.3;
			const double RightLengthTresh = 0.3;
			
			const double Case1LengthTresh = 100;
			const double Case1Factor = 0.5;

			const double Case2LengthTresh = 85;
			const double Case2Factor = 0.75;

			const double Case3Factor = 0.97;
		}

		namespace GraphExtractor
		{
			const double MinimalDistTresh = 2.0;
		}

		namespace ImageUtils
		{
			const double SlashLineDensity = 0.46;
			const double TestPlusDensity = 0.4;
			const double TestPlusSq = 0.38;
			const double TestMinusRatio = 0.33;
			const double TestMinusDensity = 0.75;
			const double TestMinusHeightFactor = 0.75;
		}

		namespace LabelCombiner
		{
			const double MaximalSymbolDistance = 3.0;
			const double TestSlashLineEps = 3.3;
			const double TestMinHeightFactor = 0.45;
			const double TestMaxHeightFactor = 1.2;
			const double RectHeightRatio = 0.5;
			const double H1SuperscriptSpace = 1.1;
			const double H2LowercaseSpace = 0.6;
			const double H3LowercaseSpace = 0.5;
			const double H4SubscriptSpace = 0.5;
			const double FillLabelFactor1 = 0.5;
			const double FillLabelFactor2 = 0.5;
		}

		namespace TripleBondMaker
		{
			const double LeftLengthTresh = 0.25;
			const double RightLengthTresh = 0.25;
		}

		namespace WeakSegmentator
		{
			const double RectangularCropAreaTreshold = 0.3;
			const double RectangularCropFitTreshold = 0.95;
			const double RefineWidth = 0.9;
			const double MinD = 1.5;
			const double Subpixel = 0.5;
		}
	}
}