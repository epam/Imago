
void updateSettingsHandwritten(Settings &s)
{
	s.general.UseProbablistics = false; 
	s.p_estimator.UsePerimeterNormalization = true;

	FUZZ s.separator.ext2charRatio = 1.233508; // fuzzed, old value = 1.200453
	FUZZ s.separator.SymProbabilityThresh = 0.584908; // fuzzed, old value = 0.56

	FUZZ s.molecule.LengthFactor_long = 0.304363; // fuzzed, old value = 0.305116
	FUZZ s.molecule.LengthFactor_medium = 0.430500; // fuzzed, old value = 0.427121
	FUZZ s.molecule.LengthFactor_default = 0.446902; // fuzzed, old value = 0.458580
	FUZZ s.molecule.LengthValue_long = 102.872152; // fuzzed, old value = 101.633487
	FUZZ s.molecule.LengthValue_medium = 89.933354; // fuzzed, old value = 86.122914
	FUZZ s.molecule.SpaceMultiply = 1.519984; // fuzzed, old value = 1.534797
	FUZZ s.molecule.AngleTreshold = 0.267148; // fuzzed, old value = 0.256054
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 13.979069; // fuzzed, old value = 14.631192
	FUZZ s.estimation.LineThickness = 5.525035; // fuzzed, old value = 5.527422
	FUZZ s.estimation.AvgBondLength = 34.494081; // fuzzed, old value = 33.744115
	FUZZ s.estimation.AddVertexEps = 4.523590; // fuzzed, old value = 4.546128
	FUZZ s.estimation.MaxSymRatio = 1.000769; // fuzzed, old value = 1.014766
	FUZZ s.estimation.MinSymRatio = 0.334178; // fuzzed, old value = 0.321972
	FUZZ s.estimation.ParLinesEps = 0.534572; // fuzzed, old value = 0.537234
	FUZZ s.estimation.SymHeightErr = 26.535618; // fuzzed, old value = 27.261051
	FUZZ s.estimation.CapitalHeightError = 0.814320; // fuzzed, old value = 0.831200
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.498595; // fuzzed, old value = 0.514439
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.201760; // fuzzed, old value = 0.193722
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 114; // fuzzed, old value = 117
	FUZZ s.mbond.LongErr = 0.374398; // fuzzed, old value = 0.360928
	FUZZ s.mbond.MediumBond = 89; // fuzzed, old value = 88
	FUZZ s.mbond.MediumErr = 0.407026; // fuzzed, old value = 0.406320
	FUZZ s.mbond.DefaultErr = 0.630787; // fuzzed, old value = 0.612367
	FUZZ s.mbond.ParBondsEps = 0.319848; // fuzzed, old value = 0.324497
	FUZZ s.mbond.DoubleRatioTresh = 7.692438; // fuzzed, old value = 7.326664
	FUZZ s.mbond.DoubleCoef = 0.078645; // fuzzed, old value = 0.082313
	FUZZ s.mbond.DoubleMagic1 = 0.930179; // fuzzed, old value = 0.911915
	FUZZ s.mbond.DoubleMagic2 = 0.965598; // fuzzed, old value = 0.960738
	FUZZ s.mbond.DoubleTreshMin = 0.096391; // fuzzed, old value = 0.096688
	FUZZ s.mbond.DoubleTreshMax = 0.879200; // fuzzed, old value = 0.896816
	FUZZ s.mbond.MaxLen1 = 155.870196; // fuzzed, old value = 155.388150
	FUZZ s.mbond.MaxLen2 = 126.893903; // fuzzed, old value = 124.975241
	FUZZ s.mbond.MaxLen3 = 116.645713; // fuzzed, old value = 118.006495
	FUZZ s.mbond.MaxLen4 = 115.343696; // fuzzed, old value = 111.383066
	FUZZ s.mbond.MaxLen5 = 83.804734; // fuzzed, old value = 87.584413
	FUZZ s.mbond.MinLen1 = 79.521826; // fuzzed, old value = 82.005362
	FUZZ s.mbond.MinLen2 = 72.859425; // fuzzed, old value = 76.079457
	FUZZ s.mbond.mbe1 = 0.077086; // fuzzed, old value = 0.077572
	FUZZ s.mbond.mbe2 = 0.145777; // fuzzed, old value = 0.146245
	FUZZ s.mbond.mbe3 = 0.196719; // fuzzed, old value = 0.202673
	FUZZ s.mbond.mbe4 = 0.184060; // fuzzed, old value = 0.184078
	FUZZ s.mbond.mbe5 = 0.159959; // fuzzed, old value = 0.158296
	FUZZ s.mbond.mbe6 = 0.204645; // fuzzed, old value = 0.208563
	FUZZ s.mbond.mbe7 = 0.393320; // fuzzed, old value = 0.386316
	FUZZ s.mbond.mbe_def = 0.520664; // fuzzed, old value = 0.500420
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.309949; // fuzzed, old value = 0.315113
	FUZZ s.mbond.DoubleRightLengthTresh = 0.331089; // fuzzed, old value = 0.316605
	FUZZ s.mbond.TripleLeftLengthTresh = 0.256909; // fuzzed, old value = 0.265281
	FUZZ s.mbond.TripleRightLengthTresh = 0.229110; // fuzzed, old value = 0.235888
	FUZZ s.mbond.Case1LengthTresh = 104.348058; // fuzzed, old value = 103.779074
	FUZZ s.mbond.Case1Factor = 0.461410; // fuzzed, old value = 0.481371
	FUZZ s.mbond.Case2LengthTresh = 83.831204; // fuzzed, old value = 81.306550
	FUZZ s.mbond.Case2Factor = 0.639907; // fuzzed, old value = 0.658235
	FUZZ s.mbond.Case3Factor = 0.812067; // fuzzed, old value = 0.844246
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.086122; // fuzzed, old value = 0.083089
	FUZZ s.skeleton.BaseSmallErr = 0.138042; // fuzzed, old value = 0.140521
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.324359; // fuzzed, old value = 0.330932
	FUZZ s.skeleton.MediumBondLen = 84; // fuzzed, old value = 83
	FUZZ s.skeleton.MediumMul = 0.204499; // fuzzed, old value = 0.199677
	FUZZ s.skeleton.MediumSmallErr = 0.144372; // fuzzed, old value = 0.139167
	FUZZ s.skeleton.LongBondLen = 96; // fuzzed, old value = 98
	FUZZ s.skeleton.LongMul = 0.128764; // fuzzed, old value = 0.128743
	FUZZ s.skeleton.LongSmallErr = 0.054634; // fuzzed, old value = 0.056627
	FUZZ s.skeleton.BrokenRepairFactor = 3.124259; // fuzzed, old value = 3.008203
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.044575; // fuzzed, old value = 1.015202
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.638957; // fuzzed, old value = 2.566068
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.179594; // fuzzed, old value = 0.188739
	FUZZ s.skeleton.DissolveMinErr = 0.173168; // fuzzed, old value = 0.178895
	FUZZ s.skeleton.ConnectBlockS = 10.059827; // fuzzed, old value = 10.484776
	FUZZ s.skeleton.ConnectFactor = 1.930805; // fuzzed, old value = 1.897726
	FUZZ s.skeleton.JoinVerticiesConst = 0.102531; // fuzzed, old value = 0.099369
	FUZZ s.skeleton.DissolveConst = 0.101163; // fuzzed, old value = 0.099436
	FUZZ s.skeleton.Dissolve2Const = 0.209702; // fuzzed, old value = 0.200853
	FUZZ s.skeleton.Join2Const = 0.313213; // fuzzed, old value = 0.327789
	FUZZ s.skeleton.Join3Const = 0.209148; // fuzzed, old value = 0.215216
	FUZZ s.skeleton.DistTreshLimFactor = 1.808158; // fuzzed, old value = 1.730551
	FUZZ s.skeleton.SlopeFact1 = 0.105692; // fuzzed, old value = 0.106948
	FUZZ s.skeleton.SlopeFact2 = 0.191353; // fuzzed, old value = 0.184663
	FUZZ s.skeleton.ShrinkEps = 0.115374; // fuzzed, old value = 0.114189
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10

	FUZZ s.routines.Circle_GapRadiusMax = 1.331843; // fuzzed, old value = 1.279636
	FUZZ s.routines.Circle_GapAngleMax = 0.511778; // fuzzed, old value = 0.492134
	FUZZ s.routines.Circle_MinRadius = 5.028734; // fuzzed, old value = 5.149902
	FUZZ s.routines.Circle_MaxDeviation = 0.194776; // fuzzed, old value = 0.192373
	FUZZ s.routines.Circle_AsCharFactor = 1.375256; // fuzzed, old value = 1.410306

	FUZZ s.routines.Algebra_IntersectionEps = 0.010862; // fuzzed, old value = 0.010843
	FUZZ s.routines.Algebra_SameLineEps = 0.208744; // fuzzed, old value = 0.199164
	FUZZ s.routines.Approx_Eps1 = 1.037573; // fuzzed, old value = 1.068602
	FUZZ s.routines.Approx_Eps2 = 0.890581; // fuzzed, old value = 0.851862
	FUZZ s.routines.Approx_CalcLineTresh = 0.823223; // fuzzed, old value = 0.860939

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.730944; // fuzzed, old value = 2.815233
	FUZZ s.wbe.SingleDownAngleMax = 45.118237; // fuzzed, old value = 45.161859
	FUZZ s.wbe.SingleDownDistancesMax = 9.309377; // fuzzed, old value = 9.445860
	FUZZ s.wbe.SingleDownLengthMax = 39.976586; // fuzzed, old value = 38.273286
	FUZZ s.wbe.SingleUpRatioEps = 2.051371; // fuzzed, old value = 1.961726
	FUZZ s.wbe.SingleUpDefCoeff = 0.257822; // fuzzed, old value = 0.269312
	FUZZ s.wbe.SingleUpIncCoeff = 0.424296; // fuzzed, old value = 0.433560
	FUZZ s.wbe.SingleUpIncLengthTresh = 36.042161; // fuzzed, old value = 36.392514
	FUZZ s.wbe.SingleUpInterpolateEps = 0.065249; // fuzzed, old value = 0.062414
	FUZZ s.wbe.SingleUpMagicAddition = 0.211116; // fuzzed, old value = 0.209425
	FUZZ s.wbe.SingleUpS2Divisor = 1.893311; // fuzzed, old value = 1.910544
	FUZZ s.wbe.SingleUpMinATresh = 1.740277; // fuzzed, old value = 1.711366
	FUZZ s.wbe.SingleUpSquareRatio = 0.562586; // fuzzed, old value = 0.560628
	FUZZ s.wbe.SingleUpAngleTresh = 0.074642; // fuzzed, old value = 0.072049
	FUZZ s.wbe.SomeTresh = 0.098765; // fuzzed, old value = 0.103342
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = true;
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 0.986846; // fuzzed, old value = 1.015943
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.129148; // fuzzed, old value = 1.179133
	FUZZ s.characters.WriteEasyFactor = 0.961572; // fuzzed, old value = 0.918959
	FUZZ s.characters.WriteVeryEasyFactor = 0.792290; // fuzzed, old value = 0.768862
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 2.885941; // fuzzed, old value = 2.972517
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.337709; // fuzzed, old value = 3.454375
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.080789; // fuzzed, old value = 0.083534
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.345288; // fuzzed, old value = 2.407954
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.645113; // fuzzed, old value = 3.783638
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.954671; // fuzzed, old value = 0.955165
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.321782; // fuzzed, old value = 0.313682
	FUZZ s.characters.X_Quality = 0.285033; // fuzzed, old value = 0.3
	FUZZ s.characters.MinEndpointsPossible = 4; // fuzzed, old value = 4

	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.459570; // fuzzed, old value = 0.474843
	FUZZ s.csr.DeleteBadTriangles = 2.215558; // fuzzed, old value = 2.259100
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.428164; // fuzzed, old value = 1.437860

	FUZZ s.graph.MinimalDistTresh = 1.707037; // fuzzed, old value = 1.734292
	FUZZ s.graph.RatioSub = 1.015867; // fuzzed, old value = 1.040110
	FUZZ s.graph.RatioTresh = 0.400420; // fuzzed, old value = 0.401984

	FUZZ s.utils.SlashLineDensity = 0.467729; // fuzzed, old value = 0.459195
	FUZZ s.utils.TestPlusDensity = 0.432560; // fuzzed, old value = 0.413130
	FUZZ s.utils.TestPlusSq = 0.440805; // fuzzed, old value = 0.436438
	FUZZ s.utils.TestMinusRatio = 0.371939; // fuzzed, old value = 0.365197
	FUZZ s.utils.TestMinusDensity = 0.600888; // fuzzed, old value = 0.586849
	FUZZ s.utils.TestMinusHeightFactor = 0.758437; // fuzzed, old value = 0.761434

	FUZZ s.separator.hu_1_1 = 0.179569; // fuzzed, old value = 0.175864
	FUZZ s.separator.hu_1_2 = 0.078962; // fuzzed, old value = 0.083046
	FUZZ s.separator.hu_0_1 = 0.234420; // fuzzed, old value = 0.232077
	FUZZ s.separator.hu_1_3 = 0.098886; // fuzzed, old value = 0.094346
	FUZZ s.separator.hu_0_2 = 0.247252; // fuzzed, old value = 0.259685
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.533163; // fuzzed, old value = 0.549026
	FUZZ s.separator.capHeightMax = 1.310226; // fuzzed, old value = 1.343106
	FUZZ s.separator.gdConst = 1.396710; // fuzzed, old value = 1.435235
	FUZZ s.separator.SurfCoef = 2.480029; // fuzzed, old value = 2.576358
	FUZZ s.separator.capHeightRatio = 0.234808; // fuzzed, old value = 0.246602
	FUZZ s.separator.capHeightRatio2 = 1.941953; // fuzzed, old value = 1.858983
	FUZZ s.separator.getRatio1 = 0.929356; // fuzzed, old value = 0.903089
	FUZZ s.separator.getRatio2 = 1.086037; // fuzzed, old value = 1.081185
	FUZZ s.separator.testSlashLine1 = 3.300974; // fuzzed, old value = 3.303156
	FUZZ s.separator.testSlashLine2 = 2.921329; // fuzzed, old value = 2.982528
	FUZZ s.separator.minDensity = 0.213719; // fuzzed, old value = 0.211327
	FUZZ s.separator.maxDensity = 0.876098; // fuzzed, old value = 0.834411
	FUZZ s.separator.extCapHeightMin = 0.319862; // fuzzed, old value = 0.310903
	FUZZ s.separator.extCapHeightMax = 2.078743; // fuzzed, old value = 2.151362
	FUZZ s.separator.extRatioMin = 0.272762; // fuzzed, old value = 0.270888
	FUZZ s.separator.extRatioMax = 1.437885; // fuzzed, old value = 1.511713
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = true; // fuzzed, old value = true

	FUZZ s.labels.underlinePos = 0.449923; // fuzzed, old value = 0.459283
	FUZZ s.labels.weightUnderline = 0.312203; // fuzzed, old value = 0.300695
	FUZZ s.labels.ratioBase = 0.837172; // fuzzed, old value = 0.856634
	FUZZ s.labels.ratioWeight = 0.302383; // fuzzed, old value = 0.301945
	FUZZ s.labels.adjustDec = 1.321000; // fuzzed, old value = 1.324884
	FUZZ s.labels.adjustInc = 0.876124; // fuzzed, old value = 0.893467
	FUZZ s.labels.sameLineEps = 0.129074; // fuzzed, old value = 0.123557
	FUZZ s.labels.heightRatio = 0.818800; // fuzzed, old value = 0.834305
	FUZZ s.labels.medHeightFactor = 0.464784; // fuzzed, old value = 0.457532
	FUZZ s.labels.capHeightError = 0.507940; // fuzzed, old value = 0.491437

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.587786; // fuzzed, old value = 2.583564
	FUZZ s.lcomb.MaximalDistanceFactor = 0.732750; // fuzzed, old value = 0.710885
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.283490; // fuzzed, old value = 0.282795
	FUZZ s.lcomb.FillLabelFactor1 = 0.506890; // fuzzed, old value = 0.515477
	FUZZ s.lcomb.FillLabelFactor2 = 0.484664; // fuzzed, old value = 0.492974

	FUZZ s.p_estimator.DefaultApriority = 0.496084; // fuzzed, old value = 0.488702
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.735240; // fuzzed, old value = 0.736039
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.251302; // fuzzed, old value = 0.242319
	FUZZ s.p_estimator.LogisticScale = 1.021508; // fuzzed, old value = 1.003589
	FUZZ s.p_estimator.LogisticLocation = 0.953877; // fuzzed, old value = 0.910447
}

