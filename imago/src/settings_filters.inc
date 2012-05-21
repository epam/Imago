
// prefilters settings

	PrefilterCVSettings::PrefilterCVSettings()
	{
		FUZZ MaxNonBWPixelsProportion = 10; // fuzzed, old value = 11
		FUZZ MinGoodPixelsCount = 18; // fuzzed, old value = 18
		FUZZ MaxBadToGoodRatio = 8; // fuzzed, old value = 8
		FUZZ BorderPartProportion = 39; // fuzzed, old value = 38
		FUZZ MaxRectangleCropLineWidth = 11; // fuzzed, old value = 11
		FUZZ StrongBinarizeSize = 4; // fuzzed, old value = 4
		FUZZ StrongBinarizeTresh = 1.417548; // fuzzed, old value = 1.354787
		FUZZ WeakBinarizeSize = 7; // fuzzed, old value = 7
		FUZZ WeakBinarizeTresh = 1.090537; // fuzzed, old value = 1.113397
	}

	AdaptiveFilterSettings::AdaptiveFilterSettings()
	{
		MaxCrops = 1;
		FUZZ MinimalLineThickness = 1.053114; // fuzzed, old value = 1.054819
		FUZZ MaximalLineThickness = 9.942818; // fuzzed, old value = 10.112951
		FUZZ MinimalInkPercentage = 0.097743; // fuzzed, old value = 0.094957
		FUZZ MaximalInkPercentage = 8.364594; // fuzzed, old value = 8.678844
		FUZZ GuessInkThresholdFactor = 0.568091; // fuzzed, old value = 0.586910
		FUZZ InterpolationLevel = 2; // fuzzed, old value = 2
		FUZZ MaxRefineIterations = 2; // fuzzed, old value = 2
		FUZZ MaxDiffIterations = 4; // fuzzed, old value = 4
		FUZZ WindowSizeFactor = 2; // fuzzed, old value = 2
	}

	PrefilterSettings::PrefilterSettings()
	{
		MakeSegmentsConnected = false;
		FUZZ SpotsWindowSize = 3; // fuzzed, old value = 3
		FUZZ GreyTreshMinF = 1.139724; // fuzzed, old value = 1.111086
		FUZZ GreyTreshMaxF = 0.918035; // fuzzed, old value = 0.922988
		FUZZ ReduceImageDim = 267; // fuzzed, old value = 267
		FUZZ GaussianKernelSize = 5; // fuzzed, old value = 5
		FUZZ Bilateral_d = 5; // fuzzed, old value = 5
		FUZZ BilateralSpace = 20.413984; // fuzzed, old value = 19.992708
		FUZZ MinSSize = 23; // fuzzed, old value = 23
		FUZZ UnsharpSize = 7; // fuzzed, old value = 7
		FUZZ UnsharpAmount = 3.738253; // fuzzed, old value = 3.823081
		FUZZ WienerSize = 5; // fuzzed, old value = 5
		FUZZ TreshFactor = 0.190035; // fuzzed, old value = 0.197910
		FUZZ BlockSAdaptive = 7; // fuzzed, old value = 7
		FUZZ MaxLSSplah = 2.777939; // fuzzed, old value = 2.813795
		FUZZ MagicCoeff = 8.505134; // fuzzed, old value = 8.509614
		FUZZ SAreaTresh = 0.305171; // fuzzed, old value = 0.302347
	}

// end of prefilters settings

