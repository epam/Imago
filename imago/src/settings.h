/****************************************************************************
 * Copyright (C) 2009-2012 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#pragma once
#ifndef _settings_h
#define _settings_h

#include "recognition_distance.h"
#include "reference_object.h"

namespace imago
{
	static const int MaxImageDimensions = 2560;
	
	/// ------------------ cluster-independ settings ------------------ ///

	struct GeneralSettings
	{		
		int    ClusterIndex;
		int    FilterIndex;
		int    OriginalImageWidth;
		int    OriginalImageHeight;
		int    ImageWidth;
		int    ImageHeight;
		int    StartTime;
		int    TimeLimit;		
		bool   LogEnabled;
		bool   LogVFSEnabled;		
		bool   ExtractCharactersOnly;
		bool   UseProbablistics;		
		bool   ImageAlreadyBinarized;
		GeneralSettings();
	};

	struct DynamicEstimationSettings
	{		
		double AvgBondLength;
		double CapitalHeight;
		double LineThickness;
		DynamicEstimationSettings();
	};

	struct RecognitionCaches // caches for character recognizer, etc
	{
		RecognitionDistanceCacheType* PCacheClean;   
		RecognitionDistanceCacheType* PCacheAdjusted;

		RecognitionCaches();
		virtual ~RecognitionCaches();
	};	

	/// ------------------ cluster-depending settings ------------------ ///

	#pragma pack (push, 1)

	// DO NOT FORGET TO ADD REFERENCES TO ALL NEW VARIABLES IN SETTINGS.CPP:fillReferenceMap()

	struct PrefilterCVSettings // POD
	{		
		int    OtsuThresholdValue;
		int    MaxNonBWPixelsProportion;
		int    MinGoodPixelsCount;
		int    MaxBadToGoodRatio;
		int    BorderPartProportion;
		int    MaxRectangleCropLineWidth;
		int    MaxRectangleCropLineWidthAlreadyBinarized;
		int    StrongBinarizeSize;
		int    WeakBinarizeSize;
		int    MinGoodPixelsCount2;
		int    MaxBadToGoodRatio2;
		int    BinarizerFrameGap;
		int    BinarizerThreshold;
		double StrongBinarizeTresh;
		double WeakBinarizeTresh;		
		double AdditionPercentage;
		double MaxFillRatio;
		double HighResPassBound;
		bool   UseOtsuPixelsAddition;
	};

	struct AdaptiveFilterSettings // POD
	{
		int    InterpolationLevel;
		int    MaxCrops;
		int    MaxRefineIterations;
		int    MaxDiffIterations;
		int    WindowSizeFactor;
		double MinimalLineThickness;
		double MaximalLineThickness;
		double MinimalInkPercentage;
		double MaximalInkPercentage;
		double GuessInkThresholdFactor;
	};

	struct PrefilterSettings // POD
	{		
		int    SpotsWindowSize;
		int    ReduceImageDim;
		int    GaussianKernelSize;
		int    Bilateral_d;
		int    MinSSize;
		int    UnsharpSize;
		int    WienerSize;
		int    BlockSAdaptive;
		double GreyTreshMinF;
		double GreyTreshMaxF;		
		double BilateralSpace;		
		double UnsharpAmount;		
		double TreshFactor;		
		double MaxLSSplah;
		double MagicCoeff;
		double SAreaTresh;
		bool   MakeSegmentsConnected;
	};

	struct WeakSegmentatorSettings // POD
	{
		double RectangularCropAreaTreshold;
		double RectangularCropFitTreshold;
		double RefineWidth;
		double MinDistanceDraw;
		double SubpixelDraw;
	};

	struct RetinexFilterSettings // POD
	{
		int StartIteration;
		int EndIteration;
		int IterationStep;
		int ContrastNominal;
		double ContrastDropPercentage;
	};

	struct LabelRemoverSettings // POD
	{
		int    MinCapitalHeight;
		int    MaxCapitalHeight;
		int    MinLabelChars;
		int    MaxLabelLines;
		int    PixGapX;
		int    PixGapY;
		double HeightFactor;
		double CenterShiftMax;
		double MinimalDensity;		
	};

	struct EstimationSettings // POD
	{
		int    DoubleBondDist;
		int    SegmentVerEps;		
		double CapitalHeightError;		
		double ParLinesEps;
		double MaxSymRatio;
		double MinSymRatio;
		double SymHeightErr;
		double CharactersSpaceCoeff;
		double MaxSymbolHeightPercentsOfImage;
	};

	struct MoleculeSettings // POD
	{
		double LengthFactor_long;
		double LengthFactor_medium;
		double LengthFactor_default; 
		double LengthValue_long;
		double LengthValue_medium; 
		double SpaceMultiply;
		double AngleTreshold;
	};

	struct MainSettings // POD
	{
		int    DissolvingsFactor;
		int    WarningsRecalcTreshold;
	};

	struct MultipleBondSettings // POD
	{
		double LongBond;
		double LongErr;
		double MediumBond;
		double MediumErr;
		double DefaultErr;
		double ParBondsEps;
		double DoubleRatioTresh;
		double DoubleCoef;
		double DoubleMagic1;
		double DoubleMagic2;
		double DoubleTreshMin;
		double DoubleTreshMax;
		double MaxLen1;
		double MaxLen2;
		double MaxLen3; 
		double MaxLen4; 
		double MaxLen5;
		double MinLen1;
		double MinLen2;
		double mbe1;
		double mbe2;
		double mbe3;
		double mbe4;
		double mbe5;
		double mbe6;
		double mbe7;
		double mbe_def;
		double DoubleLeftLengthTresh;
		double DoubleRightLengthTresh;
		double TripleLeftLengthTresh;
		double TripleRightLengthTresh;
		double Case1LengthTresh;
		double Case2LengthTresh;
		double Case1Factor;
		double Case2Factor;
		double Case3Factor;
	};

	struct SkeletonSettings // POD
	{
		double ShortBondLen;
		double MediumBondLen;
		double LongBondLen;
		double ShortMul;
		double MediumMul; 
		double LongMul;
		double BaseMult;
		double MediumSmallErr;
		double LongSmallErr;
		double BaseSmallErr;
		double BrokenRepairCoef1;
		double BrokenRepairCoef2;
		double BrokenRepairFactor;
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
	};

	struct RoutinesSettings // POD
	{
		int    LineThick_Grid;		
		double Circle_GapRadiusMax;
		double Circle_GapAngleMax;
		double Circle_MinRadius; 
		double Circle_MaxDeviation;
		double Circle_AsCharFactor;
		double Algebra_IntersectionEps;
		double Algebra_SameLineEps;
		double Approx_Eps1;
		double Approx_Eps2;
		double Approx_CalcLineTresh;		
	};

	struct WedgeBondExtractorSettings // POD
	{
		int PointsCompareDist;
		int SingleDownCompareDist;
		int MinimalSingleDownSegsCount;
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
		double SingleUpSlopeThresh;
		double SingleUpThickThresh;
		double SomeTresh;
	};

	struct CharactersRecognitionSettings // POD
	{		
		int    MinEndpointsPossible;
		int    MaximalEndpointsUse;
		int    ImpossibleToWriteDelta;
		int    DefaultFourierClassesUse;
		double WriteProbablyImpossibleFactor;
		double WriteSurelyImpossibleFactor;
		double WriteEasyFactor;
		double WriteVeryEasyFactor;		
		double PossibleCharacterDistanceStrong;
		double PossibleCharacterDistanceWeak;
		double PossibleCharacterMinimalQuality;
		double DescriptorsOddFactorStrong;
		double DescriptorsEvenFactorStrong;
		double DescriptorsOddFactorWeak;
		double DescriptorsEvenFactorWeak;
		double X_Quality;		
		double SmallLetterRecogThreshold;
		double Contour_Eps1;
		double Contour_Eps2;
		double Contour_Eps1_generator;
		double Contour_Eps2_generator;
		int    Filter_Threshold_generator;
		bool   HackFor3Use;
	};
	
	struct ChemicalStructureRecognizerSettings // POD
	{
		int    WeakSegmentatorDist;
		double Dissolve;
		double DeleteBadTriangles;		
		double LineVectorizationFactor;
		int    ReconnectMinBads; 
		double ReconnectSurelyBadCoef; 
		double ReconnectSurelyGoodCoef;
		double ReconnectProbablyGoodCoef;
		bool   UseDPApproximator;
		bool   StableDecorner;
	};

	struct GraphExtractorSettings // POD
	{
		double MinimalDistTresh;
		double RatioSub;
		double RatioTresh;
	};

	struct ImageUtilsSettings // POD
	{
		double SlashLineDensity;
		double TestPlusDensity;
		double TestPlusSq;
		double TestMinusRatio;
		double TestMinusDensity;
		double TestMinusHeightFactor;
	};

	struct SeparatorSettings // POD
	{		
		int    ltFactor1;
		int    minApproxSegsStrong;
		int    minApproxSegsWeak;
		int    specialSegmentsTreat;
		double hu_1_1;
		double hu_1_2;
		double hu_0_1;
		double hu_1_3;
		double hu_0_2;		
		double capHeightMin;
		double capHeightMax;
		double gdConst;
		double SurfCoef;
		double capHeightRatio;
		double capHeightRatio2;
		double getRatio1;
		double getRatio2;
		double testSlashLine1;
		double testSlashLine2;
		double minDensity;
		double maxDensity;
		double extCapHeightMin;
		double extCapHeightMax;
		double extRatioMin;
		double extRatioMax;
		double ext2charRatio;
		double SymProbabilityThresh;		
		bool   UseVoteArray;
	};

	struct LabelLogicSettings // POD
	{
		double underlinePos;
		double weightUnderline;
		double ratioBase;
		double ratioWeight;
		double adjustDec;
		double adjustInc;
		double sameLineEps;
		double heightRatio;
		double medHeightFactor;
		double capHeightError;
	};

	struct LabelCombinerSettings // POD
	{
		double MaximalSymbolRecognitionDistance;
		double FillLabelFactor1;
		double FillLabelFactor2;
		double MaximalDistanceFactor;
		double MaximalYDistanceFactor;
	};

	struct ProbabilitySettings // POD
	{		
		double DefaultApriority;
		double ApriorProb4SymbolCase;
		double MinRatio2ConsiderGrPr;
		double LogisticScale;
		double LogisticLocation;		
		bool   UsePerimeterNormalization;
	};

	#pragma pack (pop)

	/// ------------------ end of cluster-depending settings ------------------ ///

	struct Settings
	{
		Settings(); // default constructor

		// loads settings from file, etc.
		bool fillFromDataStream(const std::string& data);

		// stores settings into file, etc.
		void saveToDataStream(std::string& data);

		// should be called after general settings are filled
		void selectBestCluster();

		// loads configuration from file
		bool forceSelectCluster(const std::string& clusterFileName);

		// returns true if timelimit occures
		bool checkTimeLimit();
		bool checkTimeLimit() const;

		// general settings and caches - shouldn't be loaded from config
		int _configVersion;
		GeneralSettings general;
		DynamicEstimationSettings dynamic;
		RecognitionCaches caches;

		// other settings, should be updated
		PrefilterCVSettings prefilterCV;
		AdaptiveFilterSettings adaptive;
		PrefilterSettings prefilter;		
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
		ProbabilitySettings p_estimator;
		LabelRemoverSettings lab_remover;		
		RetinexFilterSettings retinex;

		void _fillReferenceMap(ReferenceAssignmentMap& result);
	};
}

#endif //_settings_h
