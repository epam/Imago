#pragma once

namespace imago
{
	static const int MaxImageDimensions = 1600;
	
	static const int CLUSTER_SCANNED = 0;
	static const int CLUSTER_HANDWRITTING = 1;

	struct GeneralSettings
	{
		bool LogEnabled;
		bool IsHandwritten;
		int ImageWidth;
		int ImageHeight;
		GeneralSettings()
		{
			LogEnabled = IsHandwritten = false;
			ImageWidth = ImageHeight = 0;
		}
	};

	struct EstimationSettings
	{
		double CapitalHeight;
		double LineThickness;
		double AvgBondLength;
		double AddVertexEps;
		double MaxSymRatio;
		double MinSymRatio;
		double ParLinesEps;
		double SymHeightErr;
		double CapitalHeightError;
		double CharactersSpaceCoeff;
		int DoubleBondDist;
		int SegmentVerEps;
		EstimationSettings(int cluster = CLUSTER_SCANNED, int LongestSide = 0);
	};

	struct MoleculeSettings
	{
		double LengthFactor_long; 
		double LengthFactor_medium; 
		double LengthFactor_default; 
		double LengthValue_long;   
		double LengthValue_medium; 
		double SpaceMultiply;      
		double AngleTreshold;
		MoleculeSettings(int cluster = CLUSTER_SCANNED, int LongestSide = 0);
	};

	struct MainSettings
	{
		int DissolvingsFactor;
		int WarningsRecalcTreshold;
		MainSettings(int cluster = CLUSTER_SCANNED, int LongestSide = 0);
	};

	struct MultipleBondSettings
	{
		double LongBond, LongErr;
		double MediumBond, MediumErr;
		double DefaultErr;
		double ParBondsEps;
		double DoubleRatioTresh, DoubleCoef;
		double DoubleMagic1, DoubleMagic2;
		double DoubleTreshMin, DoubleTreshMax;
		double MaxLen1, MaxLen2, MaxLen3, MaxLen4, MaxLen5, MinLen1, MinLen2;
		double mbe1, mbe2, mbe3, mbe4, mbe5, mbe6, mbe7, mbe_def;
		MultipleBondSettings(int cluster = CLUSTER_SCANNED, int LongestSide = 0);
	};

	struct SkeletonSettings
	{
		double MultiBondErr;
		double BaseMult;
		double BaseSmallErr;
		double ShortBondLen;
		double ShortMul;
		double MediumBondLen;
		double MediumMul;
		double MediumSmallErr;
		double LongBondLen;
		double LongMul;
		double LongSmallErr;
		double BrokenRepairFactor;
		double BrokenRepairCoef1;
		double BrokenRepairCoef2;
		double BrokenRepairAngleEps;
		double DissolveMinErr;
		double ConnectBlockS;
		double ConnectFactor;
		double JoinVerticiesConst;
		double DissolveConst;
		double Dissolve2Const;
		double Join2Const;
		double Join3Const;
		double DistTreshLimFactor;
		double SlopeFact1;
		double SlopeFact2;
		double ShrinkEps;
		SkeletonSettings(int cluster = CLUSTER_SCANNED, int LongestSide = 0);
	};

	struct PrefilterCVSettings
	{
		int MaxNonBWPixelsProportion;
		int MinGoodPixelsCount;
		int MaxBadToGoodRatio;
		int BorderPartProportion;
		int MaxRectangleCropLineWidth;
		int StrongBinarizeSize;
		double StrongBinarizeTresh;
		int WeakBinarizeSize;
		double WeakBinarizeTresh;
		PrefilterCVSettings();
	};

	struct AdaptiveFilterSettings
	{
		double MinimalLineThickness;
		double MaximalLineThickness;
		double MinimalInkPercentage;
		double MaximalInkPercentage;
		double GuessInkThresholdFactor;
		int InterpolationLevel;
		int MaxCrops;
		int MaxRefineIterations;
		int MaxDiffIterations;
		int WindowSizeFactor;
		AdaptiveFilterSettings();
	};

	struct PrefilterSettings
	{
		bool MakeSegmentsConnected;
		int SpotsWindowSize;
		double GreyTreshMinF;
		double GreyTreshMaxF;
		int ReduceImageDim;
		int GaussianKernelSize;
		int Bilateral_d;
		double BilateralSpace;
		int MinSSize;
		int UnsharpSize;
		double UnsharpAmount;
		int WienerSize;
		double TreshFactor;
		int BlockSAdaptive;
		double MaxLSSplah;
		double MagicCoeff;
		double SAreaTresh;
		PrefilterSettings();
	};

	struct RoutinesSettings
	{
		int LineThick_Grid;
		double Circle_Eps;
		double Circle_GapMin;
		double Circle_GapMax;
		double Circle_RMax;
		double Circle_AvgRadius;
		double Circle_MaxRatio;
		double Algebra_IntersectionEps;
		double Algebra_SameLineEps;
		double Approx_Eps1;
		double Approx_Eps2;
		double Approx_CalcLineTresh;
		double Contour_Eps1;
		double Contour_Eps2;
		RoutinesSettings(int cluster = CLUSTER_SCANNED, int LongestSide = 0);
	};

	struct WeakSegmentatorSettings
	{
		double RectangularCropAreaTreshold;
		double RectangularCropFitTreshold;
		double RefineWidth;
		double MinDistanceDraw;
		double SubpixelDraw;
		WeakSegmentatorSettings(int cluster = CLUSTER_SCANNED, int LongestSide = 0);
	};

	struct WedgeBondExtractorSettings
	{
		int PointsCompareDist;
		int SingleDownCompareDist;
		double SingleDownEps;
		double SingleDownAngleMax;
		double SingleDownDistancesMax;
		double SingleDownLengthMax;
		double SingleUpRatioEps;
		double SingleUpDefCoeff;
		double SingleUpIncCoeff;
		double SingleUpIncLengthTresh;
		double SingleUpInterpolateEps;
		double SingleUpMagicAddition;
		double SingleUpS2Divisor;
		double SingleUpMinATresh;
		double SingleUpSquareRatio;
		double SingleUpAngleTresh;
		double SomeTresh;
		WedgeBondExtractorSettings(int cluster = CLUSTER_SCANNED, int LongestSide = 0);
	};

	struct Settings
	{
		GeneralSettings general;
		
		// should be called after general settings filled
		void update();

		// other settings
		MoleculeSettings molecule;
		EstimationSettings estimation;
		MainSettings main;
		MultipleBondSettings mbond;
		SkeletonSettings skeleton;
		PrefilterCVSettings prefilterCV;
		AdaptiveFilterSettings adaptive;
		PrefilterSettings prefilter;
		RoutinesSettings routines;
		WeakSegmentatorSettings weak_seg;
		WedgeBondExtractorSettings wbe;
	};

	namespace consts
	{
		

		

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
			static const bool UseSimpleApproximator = false;

			const double Dissolve = 0.502969; //fuzzed from 0.485932
			const double DeleteBadTriangles = 1.952375; //fuzzed from 1.949059
			
			
			const int WeakSegmentatorDist = 1; //fuzzed from 1
			const double LineVectorizationFactor = 1.578330; //fuzzed from 1.659550
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
			//const int SymHeightErr = 6; //fuzzed from 6
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
	}
}

extern imago::Settings& imago_getSettings();
#define vars imago_getSettings()



