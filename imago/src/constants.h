#pragma once

namespace imago
{
	namespace consts
	{
		const int MaxImageDimensions = 1597; //fuzzed from 1560

		namespace GeneralFiltering
		{
			const double MinimalLineThickness = 0.996120; //fuzzed from 1.0
			const double MaximalLineThickness = 9.937178; //fuzzed from 10.0
			const double MinimalInkPercentage = 0.099939; //fuzzed from 0.1
			const double MaximalInkPercentage = 10.099933; //fuzzed from 10.0
			const int MaxNonBWPixelsProportion = 9; //fuzzed from 10
		}

		namespace PrefilterCV
		{
			const int MinGoodPixelsCount = 15; //fuzzed from 16
			const int MaxBadToGoodRatio = 7; //fuzzed from 7
			const int BorderPartProportion = 38; //fuzzed from 40
			const int MaxRectangleCropLineWidth = 11; //fuzzed from 12
			const int StrongBinarizeSize = 4; //fuzzed from 4
			static const double StrongBinarizeTresh = 1.3;
			const int WeakBinarizeSize = 7; //fuzzed from 8
			static const double WeakBinarizeTresh = 1.2;
		}

		namespace AdaptiveFilter
		{
			const double GuessInkThresholdFactor = 0.581311; //fuzzed from 0.6
			const int InterpolationLevel = 1; //fuzzed from 2
			const int MaxCrops = 1; //fuzzed from 1
			const int MaxRefineIterations = 2; //fuzzed from 2
			const int MaxDiffIterations = 3; //fuzzed from 4
			const int WindowSizeFactor = 2; //fuzzed from 2
		}

		namespace Prefilter
		{
			const int SpotsWindowSize = 3; //fuzzed from 3
			const double GreyTreshMinF = 0.993624; //fuzzed from 0.99
			const double GreyTreshMaxF = 1.055168; //fuzzed from 1.01
			const int ReduceImageDim = 311; //fuzzed from 300
			const int GaussianKernelSize = 4; //fuzzed from 5
			const int Bilateral_d = 5; //fuzzed from 5
			const double BilateralSpace = 19.055116; //fuzzed from 20
			const int MinSSize = 19; //fuzzed from 20
			const int UnsharpSize = 7; //fuzzed from 7
			const double UnsharpAmount = 4.069051; //fuzzed from 4
			const int WienerSize = 5; //fuzzed from 5
			const double TreshFactor = 0.191885; //fuzzed from 0.2
			const int BlockSAdaptive = 7; //fuzzed from 7
			const double MaxLSSplah = 3.036389; //fuzzed from 3.0
			const double MagicCoeff = 8.206000; //fuzzed from 8.0
		}

		namespace Main
		{
			const int DissolvingsFactor = 10; //fuzzed from 10
			const int WarningsRecalcTreshold = 2; //fuzzed from 2
		}

		namespace WedgeBondExtractor
		{
			const int PointsCompareDist = 3; //fuzzed from 3
			
			const int SingleDownCompareDist = 2; //fuzzed from 2
			const double SingleDownEps = 3.274344; //fuzzed from 3.3
			const double SingleDownAngleMax = 43.755966; //fuzzed from 45.0
			const double SingleDownDistancesMax = 10.354366; //fuzzed from 10.0
			const double SingleDownLengthMax = 38.695456; //fuzzed from 40.0
			
			const double SingleUpRatioEps = 1.541065; //fuzzed from 1.6
			const double SingleUpDefCoeff = 0.275873; //fuzzed from 0.28
			const double SingleUpIncCoeff = 0.395085; //fuzzed from 0.4
			const double SingleUpIncLengthTresh = 41.323222; //fuzzed from 40
			const double SingleUpInterpolateEps = 0.070841; //fuzzed from 0.07
			const double SingleUpMagicAddition = 0.201714; //fuzzed from 0.21
			const double SingleUpS2Divisor = 1.628324; //fuzzed from 1.6
			const double SingleUpMinATresh = 1.517622; //fuzzed from 1.5
			const double SingleUpSquareRatio = 0.673173; //fuzzed from 0.7
			const double SingleUpAngleTresh = 0.063681; //fuzzed from 0.065
		}

		namespace Estimation
		{
			const int DefaultLineGridSize = 9; //fuzzed from 10
			const double CircleEps = 0.000010; //fuzzed from 0.00001
			const double CircleGapMin = 0.104168; //fuzzed from 0.1
			const double CircleGapMax = 1.023989; //fuzzed from 1.0
			const double CircleRMax = 1.943995; //fuzzed from 2
			const double CircleAvgRadius = 0.000101; //fuzzed from 0.0001
			const double CircleMaxRatio = 0.301989; //fuzzed from 0.3
		}
		
		namespace Algebra
		{
			const double IntersectionEps = 0.009813; //fuzzed from 0.01
			const double SameLineEps = 0.204812; //fuzzed from 0.2
		}

		namespace Approximator
		{
			const double ApproxEps1 = 1.173747; //fuzzed from 1.13
			const double ApproxEps2 = 0.789000; //fuzzed from 0.8
			const double CalcLineTresh = 0.958924; //fuzzed from 1.0
		}

		namespace CharactersRecognition
		{
			const int MaximalEndpointsUse = 6; //fuzzed from 7
			const bool HackFor3Use = true; //fuzzed from true
			const int ImpossibleToWriteDelta = 0; //fuzzed from 1
			const double WriteProbablyImpossibleFactor = 1.050163; //fuzzed from 1.1
			const double WriteSurelyImpossibleFactor = 1.167602; //fuzzed from 1.2
			const double WriteEasyFactor = 0.933721; //fuzzed from 0.96
			const double WriteVeryEasyFactor = 0.880753; //fuzzed from 0.9
			
			const int DefaultFourierClassesUse = 2; //fuzzed from 3

			const double PossibleCharacterDistanceStrong = 2.748588; //fuzzed from 2.8
			const double PossibleCharacterDistanceWeak = 3.701039; //fuzzed from 3.6
			const double PossibleCharacterMinimalQuality = 0.097858; //fuzzed from 0.1

			const double DescriptorsOddFactorStrong = 2.401811; //fuzzed from 2.5
			const double DescriptorsEvenFactorStrong = 3.338982; //fuzzed from 3.5
			const double DescriptorsOddFactorWeak = 0.884480; //fuzzed from 0.9
			const double DescriptorsEvenFactorWeak = 0.311309; //fuzzed from 0.3

			const double HW_Line = 1.896930; //fuzzed from 1.9
			const double HW_F = 3.543769; //fuzzed from 3.4
			const double HW_Tricky = 2.730652; //fuzzed from 2.8
			const double HW_Hard = 4.521870; //fuzzed from 4.5
			const double HW_Other = 3.343986; //fuzzed from 3.3
		}

		namespace ChemicalStructureRecognizer
		{
			const double Dissolve = 0.448914; //fuzzed from 0.45
			const double DeleteBadTriangles = 1.921357; //fuzzed from 2.0
			const double SymHeightErr = 29.096902; //fuzzed from 28
			const double MaxSymRatio = 1.144855; //fuzzed from 1.14
			const double ParLinesEps = 0.522861; //fuzzed from 0.5
			const int WeakSegmentatorDist = 1; //fuzzed from 1
			const double LineVectorizationFactor = 1.526306; //fuzzed from 1.5
		}

		namespace ContourExtractor
		{
			const double ApproxEps1 = 1.045471; //fuzzed from 1.047
			const double ApproxEps2 = 0.784342; //fuzzed from 0.8
		}

		namespace DoubleBondMaker
		{
			const double LeftLengthTresh = 0.291643; //fuzzed from 0.3
			const double RightLengthTresh = 0.299601; //fuzzed from 0.3
			
			const double Case1LengthTresh = 102.260048; //fuzzed from 100
			const double Case1Factor = 0.482321; //fuzzed from 0.5

			const double Case2LengthTresh = 82.782456; //fuzzed from 85
			const double Case2Factor = 0.719401; //fuzzed from 0.75

			const double Case3Factor = 0.927483; //fuzzed from 0.97
		}

		namespace GraphExtractor
		{
			const double MinimalDistTresh = 1.960689; //fuzzed from 2.0
		}

		namespace ImageUtils
		{
			const double SlashLineDensity = 0.456252; //fuzzed from 0.46
			const double TestPlusDensity = 0.386990; //fuzzed from 0.4
			const double TestPlusSq = 0.369883; //fuzzed from 0.38
			const double TestMinusRatio = 0.335832; //fuzzed from 0.33
			const double TestMinusDensity = 0.725922; //fuzzed from 0.75
			const double TestMinusHeightFactor = 0.757985; //fuzzed from 0.75
		}

		namespace LabelCombiner
		{
			const double MaximalSymbolDistance = 3.071830; //fuzzed from 3.0
			const double TestSlashLineEps = 3.444999; //fuzzed from 3.3
			const double TestMinHeightFactor = 0.450326; //fuzzed from 0.45
			const double TestMaxHeightFactor = 1.248889; //fuzzed from 1.2
			const double RectHeightRatio = 0.478740; //fuzzed from 0.5
			const double H1SuperscriptSpace = 1.147463; //fuzzed from 1.1
			const double H2LowercaseSpace = 0.593848; //fuzzed from 0.6
			const double H3LowercaseSpace = 0.477646; //fuzzed from 0.5
			const double H4SubscriptSpace = 0.522069; //fuzzed from 0.5
			const double FillLabelFactor1 = 0.483321; //fuzzed from 0.5
			const double FillLabelFactor2 = 0.522826; //fuzzed from 0.5
		}

		namespace TripleBondMaker
		{
			const double LeftLengthTresh = 0.244541; //fuzzed from 0.25
			const double RightLengthTresh = 0.248651; //fuzzed from 0.25
		}

		namespace WeakSegmentator
		{
			const double RectangularCropAreaTreshold = 0.295649; //fuzzed from 0.3
			const double RectangularCropFitTreshold = 0.945890; //fuzzed from 0.95
			const double RefineWidth = 0.860567; //fuzzed from 0.9
			const double MinD = 1.549076; //fuzzed from 1.5
			const double Subpixel = 0.492658; //fuzzed from 0.5
		}
	}
}