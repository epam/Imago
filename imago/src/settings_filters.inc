
// prefilters settings

	PrefilterCVSettings::PrefilterCVSettings()
	{
		FUZZ MaxNonBWPixelsProportion = 10; // fuzzed, old value = 10
		FUZZ MinGoodPixelsCount = 18; // fuzzed, old value = 18
		FUZZ MaxBadToGoodRatio = 8; // fuzzed, old value = 8
		FUZZ BorderPartProportion = 39; // fuzzed, old value = 39
		FUZZ MaxRectangleCropLineWidth = 18; // fuzzed, old value = 18
		FUZZ StrongBinarizeSize = 4; // fuzzed, old value = 4
		FUZZ StrongBinarizeTresh = 1.408390; // fuzzed, old value = 1.417548
		FUZZ WeakBinarizeSize = 7; // fuzzed, old value = 7
		FUZZ WeakBinarizeTresh = 1.082436; // fuzzed, old value = 1.090537

		FUZZ UseTresholdPixelsAddition = true;
		FUZZ AdditionPercentage = 0.05;
		FUZZ MinGoodPixelsCount2 = 20;
		FUZZ MaxBadToGoodRatio2 = 7;
		FUZZ MaxFillRatio = 1.25;
	}

	AdaptiveFilterSettings::AdaptiveFilterSettings()
	{
		MaxCrops = 1;
		FUZZ MinimalLineThickness = 1.042998; // fuzzed, old value = 1.053114
		FUZZ MaximalLineThickness = 9.854576; // fuzzed, old value = 9.942818
		FUZZ MinimalInkPercentage = 0.098601; // fuzzed, old value = 0.097743
		FUZZ MaximalInkPercentage = 8.313816; // fuzzed, old value = 8.364594
		FUZZ GuessInkThresholdFactor = 0.571590; // fuzzed, old value = 0.568091
		FUZZ InterpolationLevel = 2; // fuzzed, old value = 2
		FUZZ MaxRefineIterations = 2; // fuzzed, old value = 2
		FUZZ MaxDiffIterations = 4; // fuzzed, old value = 4
		FUZZ WindowSizeFactor = 2; // fuzzed, old value = 2		
	}

	PrefilterSettings::PrefilterSettings()
	{
		MakeSegmentsConnected = false;
		FUZZ SpotsWindowSize = 3; // fuzzed, old value = 3
		FUZZ GreyTreshMinF = 1.143820; // fuzzed, old value = 1.139724
		FUZZ GreyTreshMaxF = 0.919955; // fuzzed, old value = 0.918035
		FUZZ ReduceImageDim = 266; // fuzzed, old value = 267
		FUZZ GaussianKernelSize = 5; // fuzzed, old value = 5
		FUZZ Bilateral_d = 5; // fuzzed, old value = 5
		FUZZ BilateralSpace = 20.404293; // fuzzed, old value = 20.413984
		FUZZ MinSSize = 23; // fuzzed, old value = 23
		FUZZ UnsharpSize = 7; // fuzzed, old value = 7
		FUZZ UnsharpAmount = 3.763852; // fuzzed, old value = 3.738253
		FUZZ WienerSize = 5; // fuzzed, old value = 5
		FUZZ TreshFactor = 0.190834; // fuzzed, old value = 0.190035
		FUZZ BlockSAdaptive = 7; // fuzzed, old value = 7
		FUZZ MaxLSSplah = 2.793071; // fuzzed, old value = 2.777939
		FUZZ MagicCoeff = 8.542990; // fuzzed, old value = 8.505134
		FUZZ SAreaTresh = 0.303613; // fuzzed, old value = 0.305171
	}

	WeakSegmentatorSettings::WeakSegmentatorSettings()
	{
		SubpixelDraw = 0.5;
		RectangularCropAreaTreshold = 0.3;
		RectangularCropFitTreshold = 0.9;
		RefineWidth = 0.8;
		MinDistanceDraw = 1.2;
	}

// end of prefilters settings

