
void updateSettingsHighResolution(Settings &s)
{
	s.general.UseProbablistics = false;

	FUZZ s.separator.ext2charRatio = 1.272893; // fuzzed, old value = 1.228457

	FUZZ s.molecule.LengthFactor_long = 0.343174; // fuzzed, old value = 0.342378
	FUZZ s.molecule.LengthFactor_medium = 0.441081; // fuzzed, old value = 0.421067
	FUZZ s.molecule.LengthFactor_default = 0.476738; // fuzzed, old value = 0.495114
	FUZZ s.molecule.LengthValue_long = 91.919236; // fuzzed, old value = 94.962996
	FUZZ s.molecule.LengthValue_medium = 87.368441; // fuzzed, old value = 84.232876
	FUZZ s.molecule.SpaceMultiply = 1.578302; // fuzzed, old value = 1.558828
	FUZZ s.molecule.AngleTreshold = 0.247308; // fuzzed, old value = 0.252877
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.379010; // fuzzed, old value = 16.909028
	FUZZ s.estimation.LineThickness = 5.902418; // fuzzed, old value = 6.032835
	FUZZ s.estimation.AvgBondLength = 31.535972; // fuzzed, old value = 31.788254
	FUZZ s.estimation.AddVertexEps = 5.550730; // fuzzed, old value = 5.364589
	FUZZ s.estimation.MaxSymRatio = 0.995853; // fuzzed, old value = 1.031245
	FUZZ s.estimation.MinSymRatio = 0.333823; // fuzzed, old value = 0.328454
	FUZZ s.estimation.ParLinesEps = 0.555143; // fuzzed, old value = 0.542827
	FUZZ s.estimation.SymHeightErr = 27.825479; // fuzzed, old value = 27.521804
	FUZZ s.estimation.CapitalHeightError = 0.863557; // fuzzed, old value = 0.841033
	FUZZ s.estimation.DoubleBondDist = 22; // fuzzed, old value = 22
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.567510; // fuzzed, old value = 0.558278
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.193010; // fuzzed, old value = 0.192857
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 115; // fuzzed, old value = 119
	FUZZ s.mbond.LongErr = 0.431538; // fuzzed, old value = 0.425297
	FUZZ s.mbond.MediumBond = 94; // fuzzed, old value = 96
	FUZZ s.mbond.MediumErr = 0.400231; // fuzzed, old value = 0.387197
	FUZZ s.mbond.DefaultErr = 0.625424; // fuzzed, old value = 0.653412
	FUZZ s.mbond.ParBondsEps = 0.362101; // fuzzed, old value = 0.368385
	FUZZ s.mbond.DoubleRatioTresh = 7.592527; // fuzzed, old value = 7.363217
	FUZZ s.mbond.DoubleCoef = 0.082218; // fuzzed, old value = 0.080862
	FUZZ s.mbond.DoubleMagic1 = 0.876921; // fuzzed, old value = 0.877935
	FUZZ s.mbond.DoubleMagic2 = 1.044212; // fuzzed, old value = 1.047535
	FUZZ s.mbond.DoubleTreshMin = 0.096729; // fuzzed, old value = 0.093278
	FUZZ s.mbond.DoubleTreshMax = 0.795205; // fuzzed, old value = 0.825004
	FUZZ s.mbond.MaxLen1 = 150.816853; // fuzzed, old value = 144.768662
	FUZZ s.mbond.MaxLen2 = 122.068780; // fuzzed, old value = 124.525505
	FUZZ s.mbond.MaxLen3 = 109.942866; // fuzzed, old value = 115.146363
	FUZZ s.mbond.MaxLen4 = 109.961180; // fuzzed, old value = 110.919672
	FUZZ s.mbond.MaxLen5 = 80.559554; // fuzzed, old value = 83.868397
	FUZZ s.mbond.MinLen1 = 85.563499; // fuzzed, old value = 86.559273
	FUZZ s.mbond.MinLen2 = 72.779320; // fuzzed, old value = 70.519039
	FUZZ s.mbond.mbe1 = 0.073623; // fuzzed, old value = 0.076106
	FUZZ s.mbond.mbe2 = 0.145464; // fuzzed, old value = 0.150134
	FUZZ s.mbond.mbe3 = 0.205148; // fuzzed, old value = 0.210272
	FUZZ s.mbond.mbe4 = 0.168916; // fuzzed, old value = 0.174097
	FUZZ s.mbond.mbe5 = 0.166826; // fuzzed, old value = 0.159550
	FUZZ s.mbond.mbe6 = 0.199516; // fuzzed, old value = 0.203386
	FUZZ s.mbond.mbe7 = 0.418707; // fuzzed, old value = 0.409094
	FUZZ s.mbond.mbe_def = 0.534995; // fuzzed, old value = 0.534394
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.322296; // fuzzed, old value = 0.307169
	FUZZ s.mbond.DoubleRightLengthTresh = 0.351446; // fuzzed, old value = 0.343885
	FUZZ s.mbond.TripleLeftLengthTresh = 0.285461; // fuzzed, old value = 0.279280
	FUZZ s.mbond.TripleRightLengthTresh = 0.234787; // fuzzed, old value = 0.233023
	FUZZ s.mbond.Case1LengthTresh = 101.028616; // fuzzed, old value = 98.975080
	FUZZ s.mbond.Case1Factor = 0.452282; // fuzzed, old value = 0.434294
	FUZZ s.mbond.Case2LengthTresh = 80.405600; // fuzzed, old value = 77.113559
	FUZZ s.mbond.Case2Factor = 0.653362; // fuzzed, old value = 0.675419
	FUZZ s.mbond.Case3Factor = 0.845230; // fuzzed, old value = 0.842683
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.093301; // fuzzed, old value = 0.090421
	FUZZ s.skeleton.BaseSmallErr = 0.139537; // fuzzed, old value = 0.140465
	FUZZ s.skeleton.ShortBondLen = 23; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.318256; // fuzzed, old value = 0.328864
	FUZZ s.skeleton.MediumBondLen = 91; // fuzzed, old value = 90
	FUZZ s.skeleton.MediumMul = 0.188791; // fuzzed, old value = 0.188970
	FUZZ s.skeleton.MediumSmallErr = 0.141302; // fuzzed, old value = 0.137190
	FUZZ s.skeleton.LongBondLen = 103; // fuzzed, old value = 108
	FUZZ s.skeleton.LongMul = 0.141575; // fuzzed, old value = 0.136195
	FUZZ s.skeleton.LongSmallErr = 0.054908; // fuzzed, old value = 0.055190
	FUZZ s.skeleton.BrokenRepairFactor = 3.201691; // fuzzed, old value = 3.236903
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.096991; // fuzzed, old value = 1.045592
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.633172; // fuzzed, old value = 2.584007
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.196871; // fuzzed, old value = 0.201864
	FUZZ s.skeleton.DissolveMinErr = 0.191519; // fuzzed, old value = 0.189309
	FUZZ s.skeleton.ConnectBlockS = 10.335364; // fuzzed, old value = 10.044083
	FUZZ s.skeleton.ConnectFactor = 2.103698; // fuzzed, old value = 2.059312
	FUZZ s.skeleton.JoinVerticiesConst = 0.097962; // fuzzed, old value = 0.099172
	FUZZ s.skeleton.DissolveConst = 0.098029; // fuzzed, old value = 0.100556
	FUZZ s.skeleton.Dissolve2Const = 0.199798; // fuzzed, old value = 0.209509
	FUZZ s.skeleton.Join2Const = 0.325471; // fuzzed, old value = 0.340753
	FUZZ s.skeleton.Join3Const = 0.200362; // fuzzed, old value = 0.197636
	FUZZ s.skeleton.DistTreshLimFactor = 1.767938; // fuzzed, old value = 1.825859
	FUZZ s.skeleton.SlopeFact1 = 0.103890; // fuzzed, old value = 0.103476
	FUZZ s.skeleton.SlopeFact2 = 0.177509; // fuzzed, old value = 0.181478
	FUZZ s.skeleton.ShrinkEps = 0.126058; // fuzzed, old value = 0.122952
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10

	FUZZ s.routines.Circle_GapRadiusMax = 1.319888; // fuzzed, old value = 1.290321
	FUZZ s.routines.Circle_GapAngleMax = 0.500330; // fuzzed, old value = 0.478777
	FUZZ s.routines.Circle_MinRadius = 9.427245; // fuzzed, old value = 9.825816
	FUZZ s.routines.Circle_MaxDeviation = 0.194494; // fuzzed, old value = 0.202378
	FUZZ s.routines.Circle_AsCharFactor = 1.470135; // fuzzed, old value = 1.454969

	FUZZ s.routines.Algebra_IntersectionEps = 0.009876; // fuzzed, old value = 0.010044
	FUZZ s.routines.Algebra_SameLineEps = 0.195387; // fuzzed, old value = 0.195141
	FUZZ s.routines.Approx_Eps1 = 1.159225; // fuzzed, old value = 1.171280
	FUZZ s.routines.Approx_Eps2 = 0.852831; // fuzzed, old value = 0.860450
	FUZZ s.routines.Approx_CalcLineTresh = 0.778205; // fuzzed, old value = 0.816059

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.708256; // fuzzed, old value = 2.657036
	FUZZ s.wbe.SingleDownAngleMax = 45.834966; // fuzzed, old value = 45.941874
	FUZZ s.wbe.SingleDownDistancesMax = 9.564777; // fuzzed, old value = 9.451804
	FUZZ s.wbe.SingleDownLengthMax = 41.433257; // fuzzed, old value = 42.945260
	FUZZ s.wbe.SingleUpRatioEps = 1.973868; // fuzzed, old value = 1.903476
	FUZZ s.wbe.SingleUpDefCoeff = 0.273609; // fuzzed, old value = 0.266904
	FUZZ s.wbe.SingleUpIncCoeff = 0.427082; // fuzzed, old value = 0.424490
	FUZZ s.wbe.SingleUpIncLengthTresh = 32.417748; // fuzzed, old value = 32.471112
	FUZZ s.wbe.SingleUpInterpolateEps = 0.062892; // fuzzed, old value = 0.066085
	FUZZ s.wbe.SingleUpMagicAddition = 0.234304; // fuzzed, old value = 0.224346
	FUZZ s.wbe.SingleUpS2Divisor = 1.762814; // fuzzed, old value = 1.712335
	FUZZ s.wbe.SingleUpMinATresh = 1.597938; // fuzzed, old value = 1.645916
	FUZZ s.wbe.SingleUpSquareRatio = 0.645139; // fuzzed, old value = 0.615619
	FUZZ s.wbe.SingleUpAngleTresh = 0.069255; // fuzzed, old value = 0.069989
	FUZZ s.wbe.SomeTresh = 0.103661; // fuzzed, old value = 0.107228
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = true; 
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.044433; // fuzzed, old value = 0.998118
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.191057; // fuzzed, old value = 1.205164
	FUZZ s.characters.WriteEasyFactor = 0.958358; // fuzzed, old value = 0.964168
	FUZZ s.characters.WriteVeryEasyFactor = 0.794908; // fuzzed, old value = 0.796940
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.192273; // fuzzed, old value = 3.110257
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.484949; // fuzzed, old value = 3.464338
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.093063; // fuzzed, old value = 0.097051
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.407118; // fuzzed, old value = 2.343407
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.381408; // fuzzed, old value = 3.436377
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.105042; // fuzzed, old value = 1.053116
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.331835; // fuzzed, old value = 0.320872

	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.465082; // fuzzed, old value = 0.454552
	FUZZ s.csr.DeleteBadTriangles = 1.915549; // fuzzed, old value = 1.882111
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.427663; // fuzzed, old value = 1.463723

	FUZZ s.graph.MinimalDistTresh = 2.085524; // fuzzed, old value = 2.142176
	FUZZ s.graph.RatioSub = 0.947359; // fuzzed, old value = 0.962103
	FUZZ s.graph.RatioTresh = 0.463879; // fuzzed, old value = 0.443022

	FUZZ s.utils.SlashLineDensity = 0.439130; // fuzzed, old value = 0.446247
	FUZZ s.utils.TestPlusDensity = 0.475126; // fuzzed, old value = 0.467570
	FUZZ s.utils.TestPlusSq = 0.409884; // fuzzed, old value = 0.412350
	FUZZ s.utils.TestMinusRatio = 0.349034; // fuzzed, old value = 0.356863
	FUZZ s.utils.TestMinusDensity = 0.568426; // fuzzed, old value = 0.566996
	FUZZ s.utils.TestMinusHeightFactor = 0.708738; // fuzzed, old value = 0.737457

	FUZZ s.separator.hu_1_1 = 0.184967; // fuzzed, old value = 0.193746
	FUZZ s.separator.hu_1_2 = 0.088785; // fuzzed, old value = 0.086949
	FUZZ s.separator.hu_0_1 = 0.230111; // fuzzed, old value = 0.238514
	FUZZ s.separator.hu_1_3 = 0.081856; // fuzzed, old value = 0.081834
	FUZZ s.separator.hu_0_2 = 0.255720; // fuzzed, old value = 0.266757
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.551317; // fuzzed, old value = 0.566844
	FUZZ s.separator.capHeightMax = 1.402423; // fuzzed, old value = 1.346071
	FUZZ s.separator.gdConst = 1.566582; // fuzzed, old value = 1.580729
	FUZZ s.separator.SurfCoef = 2.761859; // fuzzed, old value = 2.708069
	FUZZ s.separator.capHeightRatio = 0.243746; // fuzzed, old value = 0.240702
	FUZZ s.separator.capHeightRatio2 = 1.961336; // fuzzed, old value = 1.919897
	FUZZ s.separator.getRatio1 = 0.964657; // fuzzed, old value = 0.956948
	FUZZ s.separator.getRatio2 = 1.174308; // fuzzed, old value = 1.136410
	FUZZ s.separator.testSlashLine1 = 3.071891; // fuzzed, old value = 3.135648
	FUZZ s.separator.testSlashLine2 = 2.995530; // fuzzed, old value = 3.010123
	FUZZ s.separator.minDensity = 0.192296; // fuzzed, old value = 0.197791
	FUZZ s.separator.maxDensity = 0.775151; // fuzzed, old value = 0.807553
	FUZZ s.separator.extCapHeightMin = 0.300480; // fuzzed, old value = 0.293976
	FUZZ s.separator.extCapHeightMax = 1.952413; // fuzzed, old value = 2.024590
	FUZZ s.separator.extRatioMin = 0.280866; // fuzzed, old value = 0.284612
	FUZZ s.separator.extRatioMax = 1.495395; // fuzzed, old value = 1.475299
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = true; // fuzzed, old value = true

	FUZZ s.labels.underlinePos = 0.479942; // fuzzed, old value = 0.481036
	FUZZ s.labels.weightUnderline = 0.299030; // fuzzed, old value = 0.300502
	FUZZ s.labels.ratioBase = 0.789627; // fuzzed, old value = 0.826703
	FUZZ s.labels.ratioWeight = 0.302852; // fuzzed, old value = 0.294782
	FUZZ s.labels.adjustDec = 1.211822; // fuzzed, old value = 1.240649
	FUZZ s.labels.adjustInc = 0.848904; // fuzzed, old value = 0.839797
	FUZZ s.labels.sameLineEps = 0.131359; // fuzzed, old value = 0.135340
	FUZZ s.labels.heightRatio = 0.872890; // fuzzed, old value = 0.848121
	FUZZ s.labels.medHeightFactor = 0.472194; // fuzzed, old value = 0.463626
	FUZZ s.labels.capHeightError = 0.503947; // fuzzed, old value = 0.519912

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.817095; // fuzzed, old value = 2.907583
	FUZZ s.lcomb.MaximalDistanceFactor = 0.710797; // fuzzed, old value = 0.683355
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.286979; // fuzzed, old value = 0.290503
	FUZZ s.lcomb.FillLabelFactor1 = 0.505083; // fuzzed, old value = 0.507519
	FUZZ s.lcomb.FillLabelFactor2 = 0.488924; // fuzzed, old value = 0.505894

	FUZZ s.p_estimator.DefaultApriority = 0.491940; // fuzzed, old value = 0.497449
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.777357; // fuzzed, old value = 0.765935
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.245846; // fuzzed, old value = 0.245732
	FUZZ s.p_estimator.LogisticScale = 0.944047; // fuzzed, old value = 0.971043
	FUZZ s.p_estimator.LogisticLocation = 0.918053; // fuzzed, old value = 0.951224
}

