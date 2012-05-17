
// prefilters settings

	PrefilterCVSettings::PrefilterCVSettings()
	{
		FUZZ MaxNonBWPixelsProportion = 11; // fuzzed, old value = 11
		FUZZ MinGoodPixelsCount = 18; // fuzzed, old value = 18
		FUZZ MaxBadToGoodRatio = 8; // fuzzed, old value = 8
		FUZZ BorderPartProportion = 38; // fuzzed, old value = 39
		FUZZ MaxRectangleCropLineWidth = 11; // fuzzed, old value = 11
		FUZZ StrongBinarizeSize = 4; // fuzzed, old value = 4
		FUZZ StrongBinarizeTresh = 1.354787; // fuzzed, old value = 1.367176
		FUZZ WeakBinarizeSize = 7; // fuzzed, old value = 7
		FUZZ WeakBinarizeTresh = 1.113397; // fuzzed, old value = 1.123864
	}

	AdaptiveFilterSettings::AdaptiveFilterSettings()
	{
		MaxCrops = 1;
		FUZZ MinimalLineThickness = 1.054819; // fuzzed, old value = 1.059996
		FUZZ MaximalLineThickness = 10.112951; // fuzzed, old value = 10.245661
		FUZZ MinimalInkPercentage = 0.094957; // fuzzed, old value = 0.093563
		FUZZ MaximalInkPercentage = 8.678844; // fuzzed, old value = 8.789066
		FUZZ GuessInkThresholdFactor = 0.586910; // fuzzed, old value = 0.601815
		FUZZ InterpolationLevel = 2; // fuzzed, old value = 2
		FUZZ MaxRefineIterations = 2; // fuzzed, old value = 2
		FUZZ MaxDiffIterations = 4; // fuzzed, old value = 4
		FUZZ WindowSizeFactor = 2; // fuzzed, old value = 2
	}

	PrefilterSettings::PrefilterSettings()
	{
		MakeSegmentsConnected = false;
		FUZZ SpotsWindowSize = 3; // fuzzed, old value = 3
		FUZZ GreyTreshMinF = 1.111086; // fuzzed, old value = 1.112125
		FUZZ GreyTreshMaxF = 0.922988; // fuzzed, old value = 0.940712
		FUZZ ReduceImageDim = 267; // fuzzed, old value = 262
		FUZZ GaussianKernelSize = 5; // fuzzed, old value = 5
		FUZZ Bilateral_d = 5; // fuzzed, old value = 5
		FUZZ BilateralSpace = 19.992708; // fuzzed, old value = 19.632423
		FUZZ MinSSize = 23; // fuzzed, old value = 23
		FUZZ UnsharpSize = 7; // fuzzed, old value = 7
		FUZZ UnsharpAmount = 3.823081; // fuzzed, old value = 3.886963
		FUZZ WienerSize = 5; // fuzzed, old value = 5
		FUZZ TreshFactor = 0.197910; // fuzzed, old value = 0.200800
		FUZZ BlockSAdaptive = 7; // fuzzed, old value = 7
		FUZZ MaxLSSplah = 2.813795; // fuzzed, old value = 2.795620
		FUZZ MagicCoeff = 8.509614; // fuzzed, old value = 8.618952
		FUZZ SAreaTresh = 0.302347; // fuzzed, old value = 0.296142
	}

// end of prefilters settings

