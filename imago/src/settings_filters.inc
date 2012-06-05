
// prefilters settings

	PrefilterCVSettings::PrefilterCVSettings()
	{
		FUZZ MaxNonBWPixelsProportion = 10; // fuzzed, old value = 10
		FUZZ MinGoodPixelsCount = 18; // fuzzed, old value = 18
		FUZZ MaxBadToGoodRatio = 8; // fuzzed, old value = 8
		FUZZ BorderPartProportion = 41; // fuzzed, old value = 40
		FUZZ MaxRectangleCropLineWidth = 18; // fuzzed, old value = 18
		FUZZ MaxRectangleCropLineWidthAlreadyBinarized = 2;
		FUZZ StrongBinarizeSize = 4; // fuzzed, old value = 4
		FUZZ StrongBinarizeTresh = 1.450192; // fuzzed, old value = 1.476136
		FUZZ WeakBinarizeSize = 7; // fuzzed, old value = 7
		FUZZ WeakBinarizeTresh = 1.033653; // fuzzed, old value = 1.035869

		FUZZ UseTresholdPixelsAddition = false; // fuzzed, old value = false
		FUZZ AdditionPercentage = 0.051748; // fuzzed, old value = 0.051913
		FUZZ MinGoodPixelsCount2 = 20; // fuzzed, old value = 20
		FUZZ MaxBadToGoodRatio2 = 7; // fuzzed, old value = 7
		FUZZ MaxFillRatio = 1.269597; // fuzzed, old value = 1.271983

		FUZZ HighResPassBound = 0.75;
	}

	AdaptiveFilterSettings::AdaptiveFilterSettings()
	{
		MaxCrops = 1;
		FUZZ MinimalLineThickness = 1.082135; // fuzzed, old value = 1.070772
		FUZZ MaximalLineThickness = 10.479563; // fuzzed, old value = 10.271607
		FUZZ MinimalInkPercentage = 0.096086; // fuzzed, old value = 0.094206
		FUZZ MaximalInkPercentage = 8.437897; // fuzzed, old value = 8.477583
		FUZZ GuessInkThresholdFactor = 0.576389; // fuzzed, old value = 0.579418
		FUZZ InterpolationLevel = 2; // fuzzed, old value = 2
		FUZZ MaxRefineIterations = 2; // fuzzed, old value = 2
		FUZZ MaxDiffIterations = 4; // fuzzed, old value = 4
		FUZZ WindowSizeFactor = 2; // fuzzed, old value = 2
	}

	PrefilterSettings::PrefilterSettings()
	{
		MakeSegmentsConnected = false;
		FUZZ SpotsWindowSize = 3; // fuzzed, old value = 3
		FUZZ GreyTreshMinF = 1.131234; // fuzzed, old value = 1.118538
		FUZZ GreyTreshMaxF = 0.939402; // fuzzed, old value = 0.941271
		FUZZ ReduceImageDim = 265; // fuzzed, old value = 271
		FUZZ GaussianKernelSize = 5; // fuzzed, old value = 5
		FUZZ Bilateral_d = 5; // fuzzed, old value = 5
		FUZZ BilateralSpace = 21.768418; // fuzzed, old value = 21.266713
		FUZZ MinSSize = 22; // fuzzed, old value = 22
		FUZZ UnsharpSize = 7; // fuzzed, old value = 7
		FUZZ UnsharpAmount = 3.773667; // fuzzed, old value = 3.766546
		FUZZ WienerSize = 5; // fuzzed, old value = 5
		FUZZ TreshFactor = 0.183149; // fuzzed, old value = 0.188726
		FUZZ BlockSAdaptive = 7; // fuzzed, old value = 7
		FUZZ MaxLSSplah = 2.682383; // fuzzed, old value = 2.686030
		FUZZ MagicCoeff = 8.462242; // fuzzed, old value = 8.660170
		FUZZ SAreaTresh = 0.306787; // fuzzed, old value = 0.313263
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

