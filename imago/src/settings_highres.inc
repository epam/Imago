
void updateSettingsHighResolution(Settings &s)
{
	s.general.UseProbablistics = false;

	FUZZ s.separator.ext2charRatio = 1.228457; // fuzzed, old value = 1.2

	FUZZ s.molecule.LengthFactor_long = 0.342378; // fuzzed, old value = 0.329933
	FUZZ s.molecule.LengthFactor_medium = 0.421067; // fuzzed, old value = 0.414396
	FUZZ s.molecule.LengthFactor_default = 0.495114; // fuzzed, old value = 0.506995
	FUZZ s.molecule.LengthValue_long = 94.962996; // fuzzed, old value = 96.119201
	FUZZ s.molecule.LengthValue_medium = 84.232876; // fuzzed, old value = 85.394816
	FUZZ s.molecule.SpaceMultiply = 1.558828; // fuzzed, old value = 1.543451
	FUZZ s.molecule.AngleTreshold = 0.252877; // fuzzed, old value = 0.257380
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.909028; // fuzzed, old value = 17.107238
	FUZZ s.estimation.LineThickness = 6.032835; // fuzzed, old value = 6.162020
	FUZZ s.estimation.AvgBondLength = 31.788254; // fuzzed, old value = 30.432327
	FUZZ s.estimation.AddVertexEps = 5.364589; // fuzzed, old value = 5.600535
	FUZZ s.estimation.MaxSymRatio = 1.031245; // fuzzed, old value = 1.060708
	FUZZ s.estimation.MinSymRatio = 0.328454; // fuzzed, old value = 0.340565
	FUZZ s.estimation.ParLinesEps = 0.542827; // fuzzed, old value = 0.523253
	FUZZ s.estimation.SymHeightErr = 27.521804; // fuzzed, old value = 28.866829
	FUZZ s.estimation.CapitalHeightError = 0.841033; // fuzzed, old value = 0.841468
	FUZZ s.estimation.DoubleBondDist = 22; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.558278; // fuzzed, old value = 0.535984
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.192857; // fuzzed, old value = 0.2
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 119; // fuzzed, old value = 123
	FUZZ s.mbond.LongErr = 0.425297; // fuzzed, old value = 0.408196
	FUZZ s.mbond.MediumBond = 96; // fuzzed, old value = 98
	FUZZ s.mbond.MediumErr = 0.387197; // fuzzed, old value = 0.387146
	FUZZ s.mbond.DefaultErr = 0.653412; // fuzzed, old value = 0.642675
	FUZZ s.mbond.ParBondsEps = 0.368385; // fuzzed, old value = 0.352485
	FUZZ s.mbond.DoubleRatioTresh = 7.363217; // fuzzed, old value = 7.222879
	FUZZ s.mbond.DoubleCoef = 0.080862; // fuzzed, old value = 0.081992
	FUZZ s.mbond.DoubleMagic1 = 0.877935; // fuzzed, old value = 0.912936
	FUZZ s.mbond.DoubleMagic2 = 1.047535; // fuzzed, old value = 1.024289
	FUZZ s.mbond.DoubleTreshMin = 0.093278; // fuzzed, old value = 0.094883
	FUZZ s.mbond.DoubleTreshMax = 0.825004; // fuzzed, old value = 0.821201
	FUZZ s.mbond.MaxLen1 = 144.768662; // fuzzed, old value = 147.364301
	FUZZ s.mbond.MaxLen2 = 124.525505; // fuzzed, old value = 122.048735
	FUZZ s.mbond.MaxLen3 = 115.146363; // fuzzed, old value = 109.885495
	FUZZ s.mbond.MaxLen4 = 110.919672; // fuzzed, old value = 108.031373
	FUZZ s.mbond.MaxLen5 = 83.868397; // fuzzed, old value = 83.964874
	FUZZ s.mbond.MinLen1 = 86.559273; // fuzzed, old value = 84.373774
	FUZZ s.mbond.MinLen2 = 70.519039; // fuzzed, old value = 73.755743
	FUZZ s.mbond.mbe1 = 0.076106; // fuzzed, old value = 0.079550
	FUZZ s.mbond.mbe2 = 0.150134; // fuzzed, old value = 0.157175
	FUZZ s.mbond.mbe3 = 0.210272; // fuzzed, old value = 0.213047
	FUZZ s.mbond.mbe4 = 0.174097; // fuzzed, old value = 0.178446
	FUZZ s.mbond.mbe5 = 0.159550; // fuzzed, old value = 0.157898
	FUZZ s.mbond.mbe6 = 0.203386; // fuzzed, old value = 0.204297
	FUZZ s.mbond.mbe7 = 0.409094; // fuzzed, old value = 0.391210
	FUZZ s.mbond.mbe_def = 0.534394; // fuzzed, old value = 0.530971
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.307169; // fuzzed, old value = 0.320618
	FUZZ s.mbond.DoubleRightLengthTresh = 0.343885; // fuzzed, old value = 0.327756
	FUZZ s.mbond.TripleLeftLengthTresh = 0.279280; // fuzzed, old value = 0.267104
	FUZZ s.mbond.TripleRightLengthTresh = 0.233023; // fuzzed, old value = 0.239327
	FUZZ s.mbond.Case1LengthTresh = 98.975080; // fuzzed, old value = 98.221044
	FUZZ s.mbond.Case1Factor = 0.434294; // fuzzed, old value = 0.438109
	FUZZ s.mbond.Case2LengthTresh = 77.113559; // fuzzed, old value = 76.174484
	FUZZ s.mbond.Case2Factor = 0.675419; // fuzzed, old value = 0.677452
	FUZZ s.mbond.Case3Factor = 0.842683; // fuzzed, old value = 0.878380
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.090421; // fuzzed, old value = 0.090968
	FUZZ s.skeleton.BaseSmallErr = 0.140465; // fuzzed, old value = 0.145948
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.328864; // fuzzed, old value = 0.326711
	FUZZ s.skeleton.MediumBondLen = 90; // fuzzed, old value = 87
	FUZZ s.skeleton.MediumMul = 0.188970; // fuzzed, old value = 0.181296
	FUZZ s.skeleton.MediumSmallErr = 0.137190; // fuzzed, old value = 0.138014
	FUZZ s.skeleton.LongBondLen = 108; // fuzzed, old value = 107
	FUZZ s.skeleton.LongMul = 0.136195; // fuzzed, old value = 0.139814
	FUZZ s.skeleton.LongSmallErr = 0.055190; // fuzzed, old value = 0.058012
	FUZZ s.skeleton.BrokenRepairFactor = 3.236903; // fuzzed, old value = 3.101007
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.045592; // fuzzed, old value = 0.997585
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.584007; // fuzzed, old value = 2.643939
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.201864; // fuzzed, old value = 0.212134
	FUZZ s.skeleton.DissolveMinErr = 0.189309; // fuzzed, old value = 0.184073
	FUZZ s.skeleton.ConnectBlockS = 10.044083; // fuzzed, old value = 10.113731
	FUZZ s.skeleton.ConnectFactor = 2.059312; // fuzzed, old value = 2.098928
	FUZZ s.skeleton.JoinVerticiesConst = 0.099172; // fuzzed, old value = 0.097434
	FUZZ s.skeleton.DissolveConst = 0.100556; // fuzzed, old value = 0.099071
	FUZZ s.skeleton.Dissolve2Const = 0.209509; // fuzzed, old value = 0.204770
	FUZZ s.skeleton.Join2Const = 0.340753; // fuzzed, old value = 0.345750
	FUZZ s.skeleton.Join3Const = 0.197636; // fuzzed, old value = 0.191760
	FUZZ s.skeleton.DistTreshLimFactor = 1.825859; // fuzzed, old value = 1.882995
	FUZZ s.skeleton.SlopeFact1 = 0.103476; // fuzzed, old value = 0.107118
	FUZZ s.skeleton.SlopeFact2 = 0.181478; // fuzzed, old value = 0.185570
	FUZZ s.skeleton.ShrinkEps = 0.122952; // fuzzed, old value = 0.127320
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10

	FUZZ s.routines.Circle_GapRadiusMax = 1.290321; // fuzzed, old value = 1.25
	FUZZ s.routines.Circle_GapAngleMax = 0.478777; // fuzzed, old value = 0.5
	FUZZ s.routines.Circle_MinRadius = 9.825816; // fuzzed, old value = 10.0
	FUZZ s.routines.Circle_MaxDeviation = 0.202378; // fuzzed, old value = 0.2
	FUZZ s.routines.Circle_AsCharFactor = 1.454969; // fuzzed, old value = 1.4

	FUZZ s.routines.Algebra_IntersectionEps = 0.010044; // fuzzed, old value = 0.010292
	FUZZ s.routines.Algebra_SameLineEps = 0.195141; // fuzzed, old value = 0.201977
	FUZZ s.routines.Approx_Eps1 = 1.171280; // fuzzed, old value = 1.199592
	FUZZ s.routines.Approx_Eps2 = 0.860450; // fuzzed, old value = 0.853566
	FUZZ s.routines.Approx_CalcLineTresh = 0.816059; // fuzzed, old value = 0.851438

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.657036; // fuzzed, old value = 2.764149
	FUZZ s.wbe.SingleDownAngleMax = 45.941874; // fuzzed, old value = 44.867863
	FUZZ s.wbe.SingleDownDistancesMax = 9.451804; // fuzzed, old value = 9.551511
	FUZZ s.wbe.SingleDownLengthMax = 42.945260; // fuzzed, old value = 44.093312
	FUZZ s.wbe.SingleUpRatioEps = 1.903476; // fuzzed, old value = 1.903618
	FUZZ s.wbe.SingleUpDefCoeff = 0.266904; // fuzzed, old value = 0.276430
	FUZZ s.wbe.SingleUpIncCoeff = 0.424490; // fuzzed, old value = 0.406141
	FUZZ s.wbe.SingleUpIncLengthTresh = 32.471112; // fuzzed, old value = 32.282101
	FUZZ s.wbe.SingleUpInterpolateEps = 0.066085; // fuzzed, old value = 0.066895
	FUZZ s.wbe.SingleUpMagicAddition = 0.224346; // fuzzed, old value = 0.221899
	FUZZ s.wbe.SingleUpS2Divisor = 1.712335; // fuzzed, old value = 1.713263
	FUZZ s.wbe.SingleUpMinATresh = 1.645916; // fuzzed, old value = 1.623249
	FUZZ s.wbe.SingleUpSquareRatio = 0.615619; // fuzzed, old value = 0.602825
	FUZZ s.wbe.SingleUpAngleTresh = 0.069989; // fuzzed, old value = 0.068178
	FUZZ s.wbe.SomeTresh = 0.107228; // fuzzed, old value = 0.103020
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = true; 
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 0.998118; // fuzzed, old value = 1.018301
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.205164; // fuzzed, old value = 1.194095
	FUZZ s.characters.WriteEasyFactor = 0.964168; // fuzzed, old value = 0.937532
	FUZZ s.characters.WriteVeryEasyFactor = 0.796940; // fuzzed, old value = 0.830893
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.110257; // fuzzed, old value = 3.133057
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.464338; // fuzzed, old value = 3.368611
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.097051; // fuzzed, old value = 0.102116
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.343407; // fuzzed, old value = 2.452249
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.436377; // fuzzed, old value = 3.431513
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.053116; // fuzzed, old value = 1.048093
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.320872; // fuzzed, old value = 0.306496

	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.454552; // fuzzed, old value = 0.459060
	FUZZ s.csr.DeleteBadTriangles = 1.882111; // fuzzed, old value = 1.840575
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.463723; // fuzzed, old value = 1.456201

	FUZZ s.graph.MinimalDistTresh = 2.142176; // fuzzed, old value = 2.181059
	FUZZ s.graph.RatioSub = 0.962103; // fuzzed, old value = 0.953543
	FUZZ s.graph.RatioTresh = 0.443022; // fuzzed, old value = 0.425507

	FUZZ s.utils.SlashLineDensity = 0.446247; // fuzzed, old value = 0.446883
	FUZZ s.utils.TestPlusDensity = 0.467570; // fuzzed, old value = 0.449941
	FUZZ s.utils.TestPlusSq = 0.412350; // fuzzed, old value = 0.410484
	FUZZ s.utils.TestMinusRatio = 0.356863; // fuzzed, old value = 0.349959
	FUZZ s.utils.TestMinusDensity = 0.566996; // fuzzed, old value = 0.583367
	FUZZ s.utils.TestMinusHeightFactor = 0.737457; // fuzzed, old value = 0.754625

	FUZZ s.separator.hu_1_1 = 0.193746; // fuzzed, old value = 0.201860
	FUZZ s.separator.hu_1_2 = 0.086949; // fuzzed, old value = 0.085774
	FUZZ s.separator.hu_0_1 = 0.238514; // fuzzed, old value = 0.237021
	FUZZ s.separator.hu_1_3 = 0.081834; // fuzzed, old value = 0.078775
	FUZZ s.separator.hu_0_2 = 0.266757; // fuzzed, old value = 0.256344
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.566844; // fuzzed, old value = 0.554483
	FUZZ s.separator.capHeightMax = 1.346071; // fuzzed, old value = 1.352450
	FUZZ s.separator.gdConst = 1.580729; // fuzzed, old value = 1.607762
	FUZZ s.separator.SurfCoef = 2.708069; // fuzzed, old value = 2.830323
	FUZZ s.separator.capHeightRatio = 0.240702; // fuzzed, old value = 0.240685
	FUZZ s.separator.capHeightRatio2 = 1.919897; // fuzzed, old value = 1.920779
	FUZZ s.separator.getRatio1 = 0.956948; // fuzzed, old value = 0.958444
	FUZZ s.separator.getRatio2 = 1.136410; // fuzzed, old value = 1.131309
	FUZZ s.separator.testSlashLine1 = 3.135648; // fuzzed, old value = 3.003573
	FUZZ s.separator.testSlashLine2 = 3.010123; // fuzzed, old value = 2.996119
	FUZZ s.separator.minDensity = 0.197791; // fuzzed, old value = 0.202036
	FUZZ s.separator.maxDensity = 0.807553; // fuzzed, old value = 0.845004
	FUZZ s.separator.extCapHeightMin = 0.293976; // fuzzed, old value = 0.303064
	FUZZ s.separator.extCapHeightMax = 2.024590; // fuzzed, old value = 1.996973
	FUZZ s.separator.extRatioMin = 0.284612; // fuzzed, old value = 0.281311
	FUZZ s.separator.extRatioMax = 1.475299; // fuzzed, old value = 1.459820
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = true; // fuzzed, old value = true

	FUZZ s.labels.underlinePos = 0.481036; // fuzzed, old value = 0.505753
	FUZZ s.labels.weightUnderline = 0.300502; // fuzzed, old value = 0.299877
	FUZZ s.labels.ratioBase = 0.826703; // fuzzed, old value = 0.792477
	FUZZ s.labels.ratioWeight = 0.294782; // fuzzed, old value = 0.308817
	FUZZ s.labels.adjustDec = 1.240649; // fuzzed, old value = 1.220214
	FUZZ s.labels.adjustInc = 0.839797; // fuzzed, old value = 0.848047
	FUZZ s.labels.sameLineEps = 0.135340; // fuzzed, old value = 0.136370
	FUZZ s.labels.heightRatio = 0.848121; // fuzzed, old value = 0.884890
	FUZZ s.labels.medHeightFactor = 0.463626; // fuzzed, old value = 0.477681
	FUZZ s.labels.capHeightError = 0.519912; // fuzzed, old value = 0.535593

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.907583; // fuzzed, old value = 2.879197
	FUZZ s.lcomb.MaximalDistanceFactor = 0.683355; // fuzzed, old value = 0.7
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.290503; // fuzzed, old value = 0.3
	FUZZ s.lcomb.FillLabelFactor1 = 0.507519; // fuzzed, old value = 0.487643
	FUZZ s.lcomb.FillLabelFactor2 = 0.505894; // fuzzed, old value = 0.527013

	FUZZ s.p_estimator.DefaultApriority = 0.497449; // fuzzed, old value = 0.5
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.765935; // fuzzed, old value = 0.8
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.245732; // fuzzed, old value = 0.25
	FUZZ s.p_estimator.LogisticScale = 0.971043; // fuzzed, old value = 1.0
	FUZZ s.p_estimator.LogisticLocation = 0.951224; // fuzzed, old value = 1.0
}

