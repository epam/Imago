#pragma once

namespace imago
{
	namespace consts
	{
		const int MaxImageDimensions = 1600;

		namespace Molecule
		{
			const double space1 = 0.3;
			const double space2 = 0.4;
			const double space3 = 0.46;
			const double spaceMul = 1.5;
			const double angTresh = 0.25;
			const double len1 = 100.0;
			const double len2 = 85.0;
		}

		namespace MultipleBond
		{
			const int LongBond = 125;
			const double LongErr = 0.35;
			const int MediumBond = 85;
			const double MediumErr = 0.4;
			//const int ShortBond = 20;
			const double DefaultErr = 0.65;
			const double ParLinesEps = 0.335;
			const double DoubleRatioTresh = 7.5;
			const double DoubleCoef = 0.085;
			const double DoubleMagic1 = 0.98;
			const double DoubleMagic2 = 0.98;
			const double DoubleTreshMin = 0.1;
			const double DoubleTreshMax = 0.9;			

			const double MaxLen1 = 160.0;
			const double MaxLen2 = 125.0;
			const double MaxLen3 = 110.0;
			const double MaxLen4 = 108.0;
			const double MaxLen5 = 85.0;

			const double MinLen1 = 90.0;
			const double MinLen2 = 75.0;

			const double mbe1 = 0.08;
			const double mbe2 = 0.157;
			const double mbe3 = 0.203;
			const double mbe4 = 0.185;
			const double mbe5 = 0.165;
			const double mbe6 = 0.20;
			const double mbe7 = 0.38;
			const double mbe_def = 0.5;
		}

		namespace Skeleton
		{
			const double MultiBondErr = 0.3;
			const double BaseMult = 0.1;
			const double BaseSmallErr = 0.153;
			const int ShortBondLen = 20;
			const double ShortMul = 0.3;
			const int MediumBondLen = 85;
			const double MediumMul = 0.175;
			const double MediumSmallErr = 0.13;
			const int LongBondLen = 100;
			const double LongMul = 0.15;
			const double LongSmallErr = 0.06;
			const double BrokenRepairFactor = 3.0;
			const double BrokenRepairCoef1 = 1.0;
			const double BrokenRepairCoef2 = 2.7;
			const double BrokenRepairAngleEps = 0.2;
			const double DissolveMinErr = 0.17;
			const double ConnectBlockS = 10.0;
			const double ConnectFactor = 2.0;
			const double JoinVerticiesConst = 0.1;
			const double DissolveConst = 0.1;
			const double Dissolve2Const = 0.2;
			const double Join2Const = 0.33;
			const double Join3Const = 0.2;
			const double DistTreshLimFactor = 2.0;
			const double SlopeFact1 = 0.1;
			const double SlopeFact2 = 0.2;
			const double ShrinkEps = 0.13;
		}

		namespace GeneralFiltering
		{
			const double MinimalLineThickness = 1.093120; 
			const double MaximalLineThickness = 9.910034; 
			const double MinimalInkPercentage = 0.094627; 
			const double MaximalInkPercentage = 9.047041; 
			const int MaxNonBWPixelsProportion = 11; 
		}

		namespace PrefilterCV
		{
			const int MinGoodPixelsCount = 18;
			const int MaxBadToGoodRatio = 8; 
			const int BorderPartProportion = 42; 
			const int MaxRectangleCropLineWidth = 11; 
			const int StrongBinarizeSize = 4; 
			const double StrongBinarizeTresh = 1.288367; 
			const int WeakBinarizeSize = 7; 
			const double WeakBinarizeTresh = 1.178619;
		}

		namespace AdaptiveFilter
		{
			const double GuessInkThresholdFactor = 0.591245;
			const int InterpolationLevel = 2; 
			const int MaxCrops = 1; 
			const int MaxRefineIterations = 2; 
			const int MaxDiffIterations = 4; 
			const int WindowSizeFactor = 2; 
		}

		namespace Prefilter
		{
			const int SpotsWindowSize = 3;
			const double GreyTreshMinF = 1.088456; 
			const double GreyTreshMaxF = 0.917166;
			const int ReduceImageDim = 268; 
			const int GaussianKernelSize = 5; 
			const int Bilateral_d = 5; 
			const double BilateralSpace = 19.090640; 
			const int MinSSize = 23; 
			const int UnsharpSize = 7; 
			const double UnsharpAmount = 3.918225; 
			const int WienerSize = 5; 
			const double TreshFactor = 0.205623; 
			const int BlockSAdaptive = 7; 
			const double MaxLSSplah = 2.810816; 
			const double MagicCoeff = 8.652838;
			const double SAreaTresh = 0.3;
		}

		namespace Main
		{
			const int DissolvingsFactor = 9; 
			const int WarningsRecalcTreshold = 2; 
		}

		namespace WedgeBondExtractor
		{
			const int PointsCompareDist = 3;
			
			const int SingleDownCompareDist = 2; 
			const double SingleDownEps = 2.924434; 
			const double SingleDownAngleMax = 43.804412; 
			const double SingleDownDistancesMax = 9.354137; 
			const double SingleDownLengthMax = 42.785999; 
			
			const double SingleUpRatioEps = 1.770050; 
			const double SingleUpDefCoeff = 0.273103; 
			const double SingleUpIncCoeff = 0.420675; 
			const double SingleUpIncLengthTresh = 34.979829; 
			const double SingleUpInterpolateEps = 0.062390; 
			const double SingleUpMagicAddition = 0.213237; 
			const double SingleUpS2Divisor = 1.577473; 
			const double SingleUpMinATresh = 1.664169; 
			const double SingleUpSquareRatio = 0.655334; 
			const double SingleUpAngleTresh = 0.069811; 
			
			const double SomeTresh = 0.1;
		}

		namespace Estimation
		{
			const int DefaultLineGridSize = 10; 
			const double CircleEps = 0.000009;
			const double CircleGapMin = 0.097346; 
			const double CircleGapMax = 0.977436; 
			const double CircleRMax = 2.029622; 
			const double CircleAvgRadius = 0.000100;
			const double CircleMaxRatio = 0.324951;
		}
		
		namespace Algebra
		{
			const double IntersectionEps = 0.010607; 
			const double SameLineEps = 0.210793; 
		}

		namespace Approximator
		{
			const double ApproxEps1 = 1.151009; 
			const double ApproxEps2 = 0.856642; 
			const double CalcLineTresh = 0.870146; 
		}

		namespace CharactersRecognition
		{
			const int MaximalEndpointsUse = 7;
			const bool HackFor3Use = true; 
			const int ImpossibleToWriteDelta = 1; 
			const double WriteProbablyImpossibleFactor = 1.005475;
			const double WriteSurelyImpossibleFactor = 1.124832; 
			const double WriteEasyFactor = 0.950438; 
			const double WriteVeryEasyFactor = 0.901469; 
			
			const int DefaultFourierClassesUse = 3;

			const double PossibleCharacterDistanceStrong = 3.110220; 
			const double PossibleCharacterDistanceWeak = 3.337396; 
			const double PossibleCharacterMinimalQuality = 0.107186; 

			const double DescriptorsOddFactorStrong = 2.554166;
			const double DescriptorsEvenFactorStrong = 3.668659;
			const double DescriptorsOddFactorWeak = 0.952039; 
			const double DescriptorsEvenFactorWeak = 0.308966;

			const double HW_Line = 1.755339; 
			const double HW_F = 3.176429; 
			const double HW_Tricky = 2.675140; 
			const double HW_Hard = 4.185870; 
			const double HW_Other = 3.795295;
		}

		namespace ChemicalStructureRecognizer
		{
			const double Dissolve = 0.485932; 
			const double DeleteBadTriangles = 1.949059; 
			const double SymHeightErr = 28.296199; 
			const double MaxSymRatio = 1.088366; 
			const double ParLinesEps = 0.502616; 
			const int WeakSegmentatorDist = 1; 
			const double LineVectorizationFactor = 1.659550; 
		}

		namespace ContourExtractor
		{
			const double ApproxEps1 = 1.071862; 
			const double ApproxEps2 = 0.705507; 
		}

		namespace DoubleBondMaker
		{
			const double LeftLengthTresh = 0.336559;
			const double RightLengthTresh = 0.315862;
			
			const double Case1LengthTresh = 98.753050;
			const double Case1Factor = 0.452482; 

			const double Case2LengthTresh = 78.349477; 
			const double Case2Factor = 0.747774; 

			const double Case3Factor = 0.931997; 
		}

		namespace GraphExtractor
		{
			const double MinimalDistTresh = 1.960915;

			const double RatioSub = 1.0;
			const double RatioTresh = 0.4;
		}

		namespace ImageUtils
		{
			const double SlashLineDensity = 0.471726; 
			const double TestPlusDensity = 0.445301; 
			const double TestPlusSq = 0.413735; 
			const double TestMinusRatio = 0.362069; 
			const double TestMinusDensity = 0.661621; 
			const double TestMinusHeightFactor = 0.822925; 
		}

		namespace Separator
		{
			const int SegmentVerEps = 4;
			const int SymHeightErr = 6;
			const int DoubleBondDist = 20;
			const double hu_1_1 = 0.204424;
			const double hu_1_2 = 0.07919;
			const double hu_0_1 = 0.248338;
			const double hu_1_3 = 0.07919;
			const double hu_0_2 = 0.248338;
			const int ltFactor1 = 3;
			const double capHeightMin = 0.5;
			const double capHeightMax = 1.5;
			const double gdConst = 1.5;
			const double SurfCoef = 3.0;
			const double capHeightRatio = 0.25;
			const double capHeightRatio2 = 1.8;
			const double getRatio1 = 0.96;
			const double getRatio2 = 1.05;
			const double testSlashLine1 = 3.2;
			const double testSlashLine2 = 3.0;
			const double minDensity = 0.2;
			const double maxDensity = 0.9;
			const double extCapHeightMin = 0.3;
			const double extCapHeightMax = 2.0;
			const double extRatioMin = 0.3;
			const double extRatioMax = 1.5;
			const int minApproxSegsStrong = 4;
			const int minApproxSegsWeak = 8;
		}

		namespace LabelLogic
		{
			const double underlinePos = 0.45;
			const double weightUnderline = 0.3;
			const double ratioBase = 0.8;
			const double ratioWeight = 0.266;
			const double adjustDec = 1.2;
			const double adjustInc = 0.85;
			const double sameLineEps = 0.13;
			const double heightRatio = 0.85;
			const double medHeightFactor = 0.5;
			const double capHeightError = 0.56;
		}

		namespace LabelCombiner
		{
			const double MaximalSymbolDistance = 2.808261;
			const double TestSlashLineEps = 3.093311; 
			const double TestMinHeightFactor = 0.498066; 
			const double TestMaxHeightFactor = 1.163865; 
			const double RectHeightRatio = 0.515512; 
			const double H1SuperscriptSpace = 1.120885;
			const double H2LowercaseSpace = 0.518601; 
			const double H3LowercaseSpace = 0.483285; 
			const double H4SubscriptSpace = 0.545265; 
			const double FillLabelFactor1 = 0.482907; 
			const double FillLabelFactor2 = 0.541671; 
		}

		namespace TripleBondMaker
		{
			const double LeftLengthTresh = 0.263060; 
			const double RightLengthTresh = 0.237006;
		}

		namespace WeakSegmentator
		{
			const double RectangularCropAreaTreshold = 0.291124;
			const double RectangularCropFitTreshold = 1.023274; 
			const double RefineWidth = 0.901301; 
			const double MinD = 1.379527;
			const double Subpixel = 0.440379;
		}
	}
}