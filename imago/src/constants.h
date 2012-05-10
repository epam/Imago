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
		int OriginalImageWidth;
		int OriginalImageHeight;
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
			const double WriteProbablyImpossibleFactor = 1.046730; //fuzzed from 1.025579
			const double WriteSurelyImpossibleFactor = 1.155355; //fuzzed from 1.172038
			const double WriteEasyFactor = 0.937002; //fuzzed from 0.950538
			const double WriteVeryEasyFactor = 0.858265; //fuzzed from 0.861989
			
			const int DefaultFourierClassesUse = 3; //fuzzed from 3

			const double PossibleCharacterDistanceStrong = 2.961838; //fuzzed from 3.001713
			const double PossibleCharacterDistanceWeak = 3.438545; //fuzzed from 3.480779
			const double PossibleCharacterMinimalQuality = 0.101465; //fuzzed from 0.102027

			const double DescriptorsOddFactorStrong = 2.543958; //fuzzed from 2.541862
			const double DescriptorsEvenFactorStrong = 3.749121; //fuzzed from 3.715868
			const double DescriptorsOddFactorWeak = 0.956401; //fuzzed from 0.946020
			const double DescriptorsEvenFactorWeak = 0.292766; //fuzzed from 0.299552

			const double HW_Line = 1.683180; //fuzzed from 1.715817
			const double HW_F = 3.182398; //fuzzed from 3.258852
			const double HW_Tricky = 2.617124; //fuzzed from 2.613660
			const double HW_Hard = 4.261644; //fuzzed from 4.370636
			const double HW_Other = 3.756106; //fuzzed from 3.805273
		}

		namespace ChemicalStructureRecognizer
		{
			static const bool UseSimpleApproximator = false;

			const double Dissolve = 0.499845; //fuzzed from 0.502969
			const double DeleteBadTriangles = 1.938750; //fuzzed from 1.952375
			
			
			const int WeakSegmentatorDist = 1; //fuzzed from 1
			const double LineVectorizationFactor = 1.573529; //fuzzed from 1.578330
		}

		namespace DoubleBondMaker
		{
			const double LeftLengthTresh = 0.322094; //fuzzed from 0.327570
			const double RightLengthTresh = 0.307856; //fuzzed from 0.315731
			
			const double Case1LengthTresh = 102.570547; //fuzzed from 102.782043
			const double Case1Factor = 0.454008; //fuzzed from 0.450273

			const double Case2LengthTresh = 80.525857; //fuzzed from 80.980534
			const double Case2Factor = 0.714327; //fuzzed from 0.716376

			const double Case3Factor = 0.910078; //fuzzed from 0.916153
		}

		namespace GraphExtractor
		{
			const double MinimalDistTresh = 1.987439; //fuzzed from 1.980547

			const double RatioSub = 0.997247; //fuzzed from 0.982591
			const double RatioTresh = 0.396361; //fuzzed from 0.390179
		}

		namespace ImageUtils
		{
			const double SlashLineDensity = 0.472472; //fuzzed from 0.472098
			const double TestPlusDensity = 0.416082; //fuzzed from 0.425686
			const double TestPlusSq = 0.418662; //fuzzed from 0.421232
			const double TestMinusRatio = 0.377571; //fuzzed from 0.374708
			const double TestMinusDensity = 0.635891; //fuzzed from 0.639021
			const double TestMinusHeightFactor = 0.842092; //fuzzed from 0.827580
		}

		namespace Separator
		{
			//const int SymHeightErr = 6; //fuzzed from 6
			const double hu_1_1 = 0.201446; //fuzzed from 0.199816
			const double hu_1_2 = 0.081428; //fuzzed from 0.081394
			const double hu_0_1 = 0.240900; //fuzzed from 0.242677
			const double hu_1_3 = 0.082495; //fuzzed from 0.082532
			const double hu_0_2 = 0.246948; //fuzzed from 0.251853
			const int ltFactor1 = 3; //fuzzed from 3
			const double capHeightMin = 0.512869; //fuzzed from 0.524367
			const double capHeightMax = 1.453239; //fuzzed from 1.469542
			const double gdConst = 1.499669; //fuzzed from 1.526224
			const double SurfCoef = 2.903305; //fuzzed from 2.865619
			const double capHeightRatio = 0.250076; //fuzzed from 0.252356
			const double capHeightRatio2 = 1.879189; //fuzzed from 1.858715
			const double getRatio1 = 0.932427; //fuzzed from 0.951728
			const double getRatio2 = 1.067133; //fuzzed from 1.073513
			const double testSlashLine1 = 3.117584; //fuzzed from 3.137464
			const double testSlashLine2 = 2.893067; //fuzzed from 2.951947
			const double minDensity = 0.199655; //fuzzed from 0.199442
			const double maxDensity = 0.881712; //fuzzed from 0.868659
			const double extCapHeightMin = 0.289489; //fuzzed from 0.285352
			const double extCapHeightMax = 2.069933; //fuzzed from 2.069884
			const double extRatioMin = 0.290043; //fuzzed from 0.292182
			const double extRatioMax = 1.467457; //fuzzed from 1.484012
			const int minApproxSegsStrong = 4; //fuzzed from 4
			const int minApproxSegsWeak = 8; //fuzzed from 8
		}

		namespace LabelLogic
		{
			const double underlinePos = 0.455575; //fuzzed from 0.461956
			const double weightUnderline = 0.303806; //fuzzed from 0.305701
			const double ratioBase = 0.822301; //fuzzed from 0.836528
			const double ratioWeight = 0.278613; //fuzzed from 0.276296
			const double adjustDec = 1.231845; //fuzzed from 1.242949
			const double adjustInc = 0.814867; //fuzzed from 0.833078
			const double sameLineEps = 0.129919; //fuzzed from 0.129725
			const double heightRatio = 0.810683; //fuzzed from 0.824740
			const double medHeightFactor = 0.492709; //fuzzed from 0.496049
			const double capHeightError = 0.563351; //fuzzed from 0.565914
		}

		namespace LabelCombiner
		{
			const double MaximalSymbolDistance = 2.730463; //fuzzed from 2.669776
			const double TestSlashLineEps = 2.987886; //fuzzed from 2.945150
			const double TestMinHeightFactor = 0.510776; //fuzzed from 0.501754
			const double TestMaxHeightFactor = 1.205275; //fuzzed from 1.208078
			const double RectHeightRatio = 0.497612; //fuzzed from 0.505892
			const double H1SuperscriptSpace = 1.133820; //fuzzed from 1.145896
			const double H2LowercaseSpace = 0.516874; //fuzzed from 0.522418
			const double H3LowercaseSpace = 0.484226; //fuzzed from 0.490625
			const double H4SubscriptSpace = 0.529349; //fuzzed from 0.541011
			const double FillLabelFactor1 = 0.501753; //fuzzed from 0.502930
			const double FillLabelFactor2 = 0.516108; //fuzzed from 0.518600
		}

		namespace TripleBondMaker
		{
			const double LeftLengthTresh = 0.251938; //fuzzed from 0.251075
			const double RightLengthTresh = 0.230476; //fuzzed from 0.230011
		}		
	}
}

extern imago::Settings& imago_getSettings();
#define vars imago_getSettings()



