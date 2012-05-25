
// prefilters settings

	PrefilterCVSettings::PrefilterCVSettings()
	{
		FUZZ MaxNonBWPixelsProportion = 10; // fuzzed, old value = 10
		FUZZ MinGoodPixelsCount = 18; // fuzzed, old value = 18
		FUZZ MaxBadToGoodRatio = 8; // fuzzed, old value = 8
		FUZZ BorderPartProportion = 40; // fuzzed, old value = 39
		FUZZ MaxRectangleCropLineWidth = 18; // fuzzed, old value = 18
		FUZZ StrongBinarizeSize = 4; // fuzzed, old value = 4
		FUZZ StrongBinarizeTresh = 1.476136; // fuzzed, old value = 1.408390
		FUZZ WeakBinarizeSize = 7; // fuzzed, old value = 7
		FUZZ WeakBinarizeTresh = 1.035869; // fuzzed, old value = 1.082436

		FUZZ UseTresholdPixelsAddition = false; // fuzzed, old value = true
		FUZZ AdditionPercentage = 0.051913; // fuzzed, old value = 0.05
		FUZZ MinGoodPixelsCount2 = 20; // fuzzed, old value = 20
		FUZZ MaxBadToGoodRatio2 = 7; // fuzzed, old value = 7
		FUZZ MaxFillRatio = 1.271983; // fuzzed, old value = 1.25
	}

	AdaptiveFilterSettings::AdaptiveFilterSettings()
	{
		MaxCrops = 1;
		FUZZ MinimalLineThickness = 1.070772; // fuzzed, old value = 1.042998
		FUZZ MaximalLineThickness = 10.271607; // fuzzed, old value = 9.854576
		FUZZ MinimalInkPercentage = 0.094206; // fuzzed, old value = 0.098601
		FUZZ MaximalInkPercentage = 8.477583; // fuzzed, old value = 8.313816
		FUZZ GuessInkThresholdFactor = 0.579418; // fuzzed, old value = 0.571590
		FUZZ InterpolationLevel = 2; // fuzzed, old value = 2
		FUZZ MaxRefineIterations = 2; // fuzzed, old value = 2
		FUZZ MaxDiffIterations = 4; // fuzzed, old value = 4
		FUZZ WindowSizeFactor = 2; // fuzzed, old value = 2
	}

	PrefilterSettings::PrefilterSettings()
	{
		MakeSegmentsConnected = false;
		FUZZ SpotsWindowSize = 3; // fuzzed, old value = 3
		FUZZ GreyTreshMinF = 1.118538; // fuzzed, old value = 1.143820
		FUZZ GreyTreshMaxF = 0.941271; // fuzzed, old value = 0.919955
		FUZZ ReduceImageDim = 271; // fuzzed, old value = 266
		FUZZ GaussianKernelSize = 5; // fuzzed, old value = 5
		FUZZ Bilateral_d = 5; // fuzzed, old value = 5
		FUZZ BilateralSpace = 21.266713; // fuzzed, old value = 20.404293
		FUZZ MinSSize = 22; // fuzzed, old value = 23
		FUZZ UnsharpSize = 7; // fuzzed, old value = 7
		FUZZ UnsharpAmount = 3.766546; // fuzzed, old value = 3.763852
		FUZZ WienerSize = 5; // fuzzed, old value = 5
		FUZZ TreshFactor = 0.188726; // fuzzed, old value = 0.190834
		FUZZ BlockSAdaptive = 7; // fuzzed, old value = 7
		FUZZ MaxLSSplah = 2.686030; // fuzzed, old value = 2.793071
		FUZZ MagicCoeff = 8.660170; // fuzzed, old value = 8.542990
		FUZZ SAreaTresh = 0.313263; // fuzzed, old value = 0.303613
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

