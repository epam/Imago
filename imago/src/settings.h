#pragma once

namespace imago
{
	enum FilterType
	{
		ftStd = 0,
		ftAdaptive = 1,
		ftCV = 2,
		ftPass = 3
	};

	static const char* FilterName[4] = {"std", "adaptive", "CV", "passthru" };

	static const int MaxImageDimensions = 1600;
	
	enum ClusterType
	{
		ctDetermine = -1,
		ctScanned = 0,
		ctHandwritten = 1,
		ctHighResolution = 2,
		ctClustersTotalCount // should set automatically
	};

	/// ------------------ cluster-independ settings ------------------ ///

	struct GeneralSettings
	{
		FilterType DefaultFilterType;
		bool LogEnabled;
		bool LogVFSEnabled;
		bool ExtractCharactersOnly;
		bool IsHandwritten;
		bool UseProbablistics;
		int OriginalImageWidth;
		int OriginalImageHeight;
		int ImageWidth;
		int ImageHeight;
		GeneralSettings()
		{
			LogEnabled = LogVFSEnabled = ExtractCharactersOnly = false;
			IsHandwritten = true;
			UseProbablistics = false;
			OriginalImageWidth = OriginalImageHeight = ImageWidth = ImageHeight = 0;
			DefaultFilterType = ftCV;
		}
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
		
		bool UseTresholdPixelsAddition;
		double AdditionPercentage;
		int MinGoodPixelsCount2;
		int MaxBadToGoodRatio2;
		double MaxFillRatio;
		double HighResPassBound;

		PrefilterCVSettings();
	};

	struct AdaptiveFilterSettings
	{
		double MinimalLineThickness, MaximalLineThickness;
		double MinimalInkPercentage, MaximalInkPercentage;
		double GuessInkThresholdFactor;
		int InterpolationLevel;
		int MaxCrops, MaxRefineIterations, MaxDiffIterations;
		int WindowSizeFactor;
		AdaptiveFilterSettings();
	};

	struct PrefilterSettings
	{
		bool MakeSegmentsConnected;
		int SpotsWindowSize;
		double GreyTreshMinF, GreyTreshMaxF;
		int ReduceImageDim, GaussianKernelSize;
		int Bilateral_d;
		double BilateralSpace;
		int MinSSize, UnsharpSize;
		double UnsharpAmount;
		int WienerSize;
		double TreshFactor;
		int BlockSAdaptive;
		double MaxLSSplah;
		double MagicCoeff;
		double SAreaTresh;
		PrefilterSettings();
	};

	struct WeakSegmentatorSettings
	{
		double RectangularCropAreaTreshold, RectangularCropFitTreshold;
		double RefineWidth, MinDistanceDraw, SubpixelDraw;
		WeakSegmentatorSettings();
	};

	/// ------------------ cluster-depending settings ------------------ ///

	struct EstimationSettings
	{
		double CapitalHeight, CapitalHeightError;
		double LineThickness, AvgBondLength;
		double AddVertexEps, ParLinesEps;
		double MaxSymRatio, MinSymRatio, SymHeightErr;
		double CharactersSpaceCoeff;
		int DoubleBondDist;
		int SegmentVerEps;
	};

	struct MoleculeSettings
	{
		double LengthFactor_long, LengthFactor_medium, LengthFactor_default; 
		double LengthValue_long, LengthValue_medium; 
		double SpaceMultiply, AngleTreshold;
	};

	struct MainSettings
	{
		int DissolvingsFactor, WarningsRecalcTreshold;
	};

	struct MultipleBondSettings
	{
		double LongBond, LongErr;
		double MediumBond, MediumErr, DefaultErr;
		double ParBondsEps;
		double DoubleRatioTresh, DoubleCoef;
		double DoubleMagic1, DoubleMagic2;
		double DoubleTreshMin, DoubleTreshMax;
		double MaxLen1, MaxLen2, MaxLen3, MaxLen4, MaxLen5, MinLen1, MinLen2;
		double mbe1, mbe2, mbe3, mbe4, mbe5, mbe6, mbe7, mbe_def;
		double DoubleLeftLengthTresh, DoubleRightLengthTresh;
		double TripleLeftLengthTresh, TripleRightLengthTresh;
		double Case1LengthTresh, Case2LengthTresh;
		double Case1Factor, Case2Factor, Case3Factor;
	};

	struct SkeletonSettings
	{
		double ShortBondLen, MediumBondLen, LongBondLen;
		double ShortMul, MediumMul, LongMul, BaseMult;
		double MediumSmallErr, LongSmallErr, BaseSmallErr;
		double BrokenRepairCoef1, BrokenRepairCoef2;
		double BrokenRepairFactor, BrokenRepairAngleEps;
		double DissolveMinErr;
		double ConnectBlockS, ConnectFactor;
		double JoinVerticiesConst;
		double DissolveConst, Dissolve2Const;
		double Join2Const, Join3Const;
		double DistTreshLimFactor;
		double SlopeFact1, SlopeFact2;
		double ShrinkEps;
	};

	struct RoutinesSettings
	{
		int LineThick_Grid;

		double Circle_GapRadiusMax;
		double Circle_GapAngleMax;
		double Circle_MinRadius; 
		double Circle_MaxDeviation;
		double Circle_AsCharFactor;
		
		double Algebra_IntersectionEps, Algebra_SameLineEps;
		double Approx_Eps1, Approx_Eps2;
		double Approx_CalcLineTresh;
		double Contour_Eps1, Contour_Eps2;
	};

	struct WedgeBondExtractorSettings
	{
		int PointsCompareDist, SingleDownCompareDist;
		double SingleDownEps, SingleDownAngleMax;
		double SingleDownDistancesMax, SingleDownLengthMax;
		double SingleUpRatioEps, SingleUpDefCoeff;
		double SingleUpIncCoeff, SingleUpIncLengthTresh;
		double SingleUpInterpolateEps, SingleUpMagicAddition;
		double SingleUpS2Divisor, SingleUpMinATresh;
		double SingleUpSquareRatio, SingleUpAngleTresh;
		double SomeTresh;
	};

	struct CharactersRecognitionSettings
	{
		int MaximalEndpointsUse;
		bool HackFor3Use;
		double WriteProbablyImpossibleFactor, WriteSurelyImpossibleFactor;
		double WriteEasyFactor, WriteVeryEasyFactor;
		int ImpossibleToWriteDelta, DefaultFourierClassesUse;
		double PossibleCharacterDistanceStrong, PossibleCharacterDistanceWeak;
		double PossibleCharacterMinimalQuality;
		double DescriptorsOddFactorStrong, DescriptorsEvenFactorStrong;
		double DescriptorsOddFactorWeak, DescriptorsEvenFactorWeak;
		double HW_Line, HW_F, HW_Tricky, HW_Hard, HW_Other;
	};

	struct ChemicalStructureRecognizerSettings
	{
		bool UseSimpleApproximator;
		double Dissolve;
		double DeleteBadTriangles;
		int WeakSegmentatorDist;
		double LineVectorizationFactor;
	};

	struct GraphExtractorSettings
	{
		double MinimalDistTresh;
		double RatioSub;
		double RatioTresh;
	};

	struct ImageUtilsSettings
	{
		double SlashLineDensity;
		double TestPlusDensity, TestPlusSq;
		double TestMinusRatio, TestMinusDensity, TestMinusHeightFactor;
	};

	struct SeparatorSettings
	{
		double hu_1_1, hu_1_2, hu_0_1, hu_1_3, hu_0_2;
		int ltFactor1;
		double capHeightMin, capHeightMax;
		double gdConst, SurfCoef;
		double capHeightRatio, capHeightRatio2;
		double getRatio1, getRatio2;
		double testSlashLine1, testSlashLine2;
		double minDensity, maxDensity;
		double extCapHeightMin, extCapHeightMax;
		double extRatioMin, extRatioMax;
		double ext2charRatio;
		int minApproxSegsStrong, minApproxSegsWeak;
		int specialSegmentsTreat;
	};

	struct LabelLogicSettings
	{
		double underlinePos, weightUnderline;
		double ratioBase, ratioWeight;
		double adjustDec, adjustInc;
		double sameLineEps, heightRatio;
		double medHeightFactor, capHeightError;
	};

	struct LabelCombinerSettings
	{
		double MaximalSymbolDistance;
		double TestSlashLineEps;
		double TestMinHeightFactor, TestMaxHeightFactor;
		double RectHeightRatio;
		double H1SuperscriptSpace, H2LowercaseSpace;
		double H3LowercaseSpace, H4SubscriptSpace;
		double FillLabelFactor1, FillLabelFactor2;
	};

	struct Settings
	{
		Settings(); // default constructor

		GeneralSettings general;

		PrefilterCVSettings prefilterCV;
		AdaptiveFilterSettings adaptive;
		PrefilterSettings prefilter;

		// should be called after general settings filled
		void updateCluster(ClusterType ct = ctDetermine);

		// other settings, should be updated
		MoleculeSettings molecule;
		EstimationSettings estimation;
		MainSettings main;
		MultipleBondSettings mbond;
		SkeletonSettings skeleton;
		RoutinesSettings routines;
		WeakSegmentatorSettings weak_seg;
		WedgeBondExtractorSettings wbe;
		CharactersRecognitionSettings characters;
		ChemicalStructureRecognizerSettings csr;
		GraphExtractorSettings graph;
		ImageUtilsSettings utils;
		SeparatorSettings separator;
		LabelLogicSettings labels;
		LabelCombinerSettings lcomb;
	};
}
