
void updateSettingsHandwritten(Settings &s)
{
	s.general.UseProbablistics = false; 

	FUZZ s.separator.ext2charRatio = 1.272893; // fuzzed, old value = 1.228457

	FUZZ s.molecule.LengthFactor_long = 0.318992; // fuzzed, old value = 0.318252
	FUZZ s.molecule.LengthFactor_medium = 0.433591; // fuzzed, old value = 0.413917
	FUZZ s.molecule.LengthFactor_default = 0.453915; // fuzzed, old value = 0.471411
	FUZZ s.molecule.LengthValue_long = 100.581899; // fuzzed, old value = 103.912509
	FUZZ s.molecule.LengthValue_medium = 89.239098; // fuzzed, old value = 86.036397
	FUZZ s.molecule.SpaceMultiply = 1.557100; // fuzzed, old value = 1.537888
	FUZZ s.molecule.AngleTreshold = 0.247170; // fuzzed, old value = 0.252735
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 15.590773; // fuzzed, old value = 15.169151
	FUZZ s.estimation.LineThickness = 5.554798; // fuzzed, old value = 5.677534
	FUZZ s.estimation.AvgBondLength = 33.360804; // fuzzed, old value = 33.627685
	FUZZ s.estimation.AddVertexEps = 4.848608; // fuzzed, old value = 4.686013
	FUZZ s.estimation.MaxSymRatio = 1.011244; // fuzzed, old value = 1.047183
	FUZZ s.estimation.MinSymRatio = 0.320464; // fuzzed, old value = 0.315310
	FUZZ s.estimation.ParLinesEps = 0.532587; // fuzzed, old value = 0.520771
	FUZZ s.estimation.SymHeightErr = 27.265907; // fuzzed, old value = 26.968339
	FUZZ s.estimation.CapitalHeightError = 0.890525; // fuzzed, old value = 0.867297
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.527522; // fuzzed, old value = 0.518941
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.193010; // fuzzed, old value = 0.192857
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 109; // fuzzed, old value = 113
	FUZZ s.mbond.LongErr = 0.381632; // fuzzed, old value = 0.376113
	FUZZ s.mbond.MediumBond = 90; // fuzzed, old value = 91
	FUZZ s.mbond.MediumErr = 0.409788; // fuzzed, old value = 0.396442
	FUZZ s.mbond.DefaultErr = 0.609025; // fuzzed, old value = 0.636280
	FUZZ s.mbond.ParBondsEps = 0.315158; // fuzzed, old value = 0.320627
	FUZZ s.mbond.DoubleRatioTresh = 7.842538; // fuzzed, old value = 7.605677
	FUZZ s.mbond.DoubleCoef = 0.083781; // fuzzed, old value = 0.082399
	FUZZ s.mbond.DoubleMagic1 = 0.907286; // fuzzed, old value = 0.908335
	FUZZ s.mbond.DoubleMagic2 = 0.994287; // fuzzed, old value = 0.997451
	FUZZ s.mbond.DoubleTreshMin = 0.101993; // fuzzed, old value = 0.098354
	FUZZ s.mbond.DoubleTreshMax = 0.847650; // fuzzed, old value = 0.879415
	FUZZ s.mbond.MaxLen1 = 161.394104; // fuzzed, old value = 154.921735
	FUZZ s.mbond.MaxLen2 = 125.519201; // fuzzed, old value = 128.045368
	FUZZ s.mbond.MaxLen3 = 109.361076; // fuzzed, old value = 114.537037
	FUZZ s.mbond.MaxLen4 = 113.427878; // fuzzed, old value = 114.416588
	FUZZ s.mbond.MaxLen5 = 84.286516; // fuzzed, old value = 87.748438
	FUZZ s.mbond.MinLen1 = 81.481357; // fuzzed, old value = 82.429623
	FUZZ s.mbond.MinLen2 = 75.304087; // fuzzed, old value = 72.965395
	FUZZ s.mbond.mbe1 = 0.076155; // fuzzed, old value = 0.078724
	FUZZ s.mbond.mbe2 = 0.135156; // fuzzed, old value = 0.139495
	FUZZ s.mbond.mbe3 = 0.200258; // fuzzed, old value = 0.205260
	FUZZ s.mbond.mbe4 = 0.173034; // fuzzed, old value = 0.178341
	FUZZ s.mbond.mbe5 = 0.161585; // fuzzed, old value = 0.154538
	FUZZ s.mbond.mbe6 = 0.208159; // fuzzed, old value = 0.212197
	FUZZ s.mbond.mbe7 = 0.391864; // fuzzed, old value = 0.382867
	FUZZ s.mbond.mbe_def = 0.524688; // fuzzed, old value = 0.524099
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.328715; // fuzzed, old value = 0.313287
	FUZZ s.mbond.DoubleRightLengthTresh = 0.339093; // fuzzed, old value = 0.331798
	FUZZ s.mbond.TripleLeftLengthTresh = 0.284048; // fuzzed, old value = 0.277898
	FUZZ s.mbond.TripleRightLengthTresh = 0.233577; // fuzzed, old value = 0.231822
	FUZZ s.mbond.Case1LengthTresh = 107.631652; // fuzzed, old value = 105.443901
	FUZZ s.mbond.Case1Factor = 0.489409; // fuzzed, old value = 0.469945
	FUZZ s.mbond.Case2LengthTresh = 83.616627; // fuzzed, old value = 80.193117
	FUZZ s.mbond.Case2Factor = 0.653142; // fuzzed, old value = 0.675191
	FUZZ s.mbond.Case3Factor = 0.868736; // fuzzed, old value = 0.866118
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.089263; // fuzzed, old value = 0.086508
	FUZZ s.skeleton.BaseSmallErr = 0.140219; // fuzzed, old value = 0.141151
	FUZZ s.skeleton.ShortBondLen = 23; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.321442; // fuzzed, old value = 0.332156
	FUZZ s.skeleton.MediumBondLen = 87; // fuzzed, old value = 86
	FUZZ s.skeleton.MediumMul = 0.192559; // fuzzed, old value = 0.192742
	FUZZ s.skeleton.MediumSmallErr = 0.141087; // fuzzed, old value = 0.136981
	FUZZ s.skeleton.LongBondLen = 96; // fuzzed, old value = 100
	FUZZ s.skeleton.LongMul = 0.140682; // fuzzed, old value = 0.135336
	FUZZ s.skeleton.LongSmallErr = 0.058790; // fuzzed, old value = 0.059091
	FUZZ s.skeleton.BrokenRepairFactor = 3.001942; // fuzzed, old value = 3.034957
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.064631; // fuzzed, old value = 1.014748
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.641621; // fuzzed, old value = 2.592298
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.184619; // fuzzed, old value = 0.189301
	FUZZ s.skeleton.DissolveMinErr = 0.177798; // fuzzed, old value = 0.175746
	FUZZ s.skeleton.ConnectBlockS = 11.098014; // fuzzed, old value = 10.785240
	FUZZ s.skeleton.ConnectFactor = 1.984038; // fuzzed, old value = 1.942177
	FUZZ s.skeleton.JoinVerticiesConst = 0.102851; // fuzzed, old value = 0.104121
	FUZZ s.skeleton.DissolveConst = 0.095890; // fuzzed, old value = 0.098362
	FUZZ s.skeleton.Dissolve2Const = 0.185611; // fuzzed, old value = 0.194633
	FUZZ s.skeleton.Join2Const = 0.319513; // fuzzed, old value = 0.334515
	FUZZ s.skeleton.Join3Const = 0.217437; // fuzzed, old value = 0.214479
	FUZZ s.skeleton.DistTreshLimFactor = 1.711360; // fuzzed, old value = 1.767427
	FUZZ s.skeleton.SlopeFact1 = 0.105489; // fuzzed, old value = 0.105068
	FUZZ s.skeleton.SlopeFact2 = 0.173751; // fuzzed, old value = 0.177636
	FUZZ s.skeleton.ShrinkEps = 0.116572; // fuzzed, old value = 0.113700
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10

	FUZZ s.routines.Circle_GapRadiusMax = 1.267093; // fuzzed, old value = 1.238708
	FUZZ s.routines.Circle_GapAngleMax = 0.500330; // fuzzed, old value = 0.478777
	FUZZ s.routines.Circle_MinRadius = 4.713622; // fuzzed, old value = 4.912908
	FUZZ s.routines.Circle_MaxDeviation = 0.194494; // fuzzed, old value = 0.202378
	FUZZ s.routines.Circle_AsCharFactor = 1.470135; // fuzzed, old value = 1.454969

	FUZZ s.routines.Algebra_IntersectionEps = 0.010265; // fuzzed, old value = 0.010440
	FUZZ s.routines.Algebra_SameLineEps = 0.200218; // fuzzed, old value = 0.199966
	FUZZ s.routines.Approx_Eps1 = 1.110801; // fuzzed, old value = 1.122353
	FUZZ s.routines.Approx_Eps2 = 0.864574; // fuzzed, old value = 0.872298
	FUZZ s.routines.Approx_CalcLineTresh = 0.787739; // fuzzed, old value = 0.826057

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.818591; // fuzzed, old value = 2.765285
	FUZZ s.wbe.SingleDownAngleMax = 45.859912; // fuzzed, old value = 45.966879
	FUZZ s.wbe.SingleDownDistancesMax = 10.006149; // fuzzed, old value = 9.887962
	FUZZ s.wbe.SingleDownLengthMax = 36.290546; // fuzzed, old value = 37.614879
	FUZZ s.wbe.SingleUpRatioEps = 2.029352; // fuzzed, old value = 1.956981
	FUZZ s.wbe.SingleUpDefCoeff = 0.264770; // fuzzed, old value = 0.258282
	FUZZ s.wbe.SingleUpIncCoeff = 0.455527; // fuzzed, old value = 0.452763
	FUZZ s.wbe.SingleUpIncLengthTresh = 36.581274; // fuzzed, old value = 36.641491
	FUZZ s.wbe.SingleUpInterpolateEps = 0.057489; // fuzzed, old value = 0.060408
	FUZZ s.wbe.SingleUpMagicAddition = 0.227892; // fuzzed, old value = 0.218206
	FUZZ s.wbe.SingleUpS2Divisor = 1.910895; // fuzzed, old value = 1.856176
	FUZZ s.wbe.SingleUpMinATresh = 1.736858; // fuzzed, old value = 1.789007
	FUZZ s.wbe.SingleUpSquareRatio = 0.607997; // fuzzed, old value = 0.580176
	FUZZ s.wbe.SingleUpAngleTresh = 0.070297; // fuzzed, old value = 0.071043
	FUZZ s.wbe.SomeTresh = 0.096623; // fuzzed, old value = 0.099948
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = true;
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.091199; // fuzzed, old value = 1.042811
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.186737; // fuzzed, old value = 1.200793
	FUZZ s.characters.WriteEasyFactor = 0.960198; // fuzzed, old value = 0.966019
	FUZZ s.characters.WriteVeryEasyFactor = 0.766066; // fuzzed, old value = 0.768024
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.165521; // fuzzed, old value = 3.084192
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.405659; // fuzzed, old value = 3.385517
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.082709; // fuzzed, old value = 0.086253
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.373304; // fuzzed, old value = 2.310488
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.714176; // fuzzed, old value = 3.774555
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.982021; // fuzzed, old value = 0.935876
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.327467; // fuzzed, old value = 0.316648

	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.489300; // fuzzed, old value = 0.478222
	FUZZ s.csr.DeleteBadTriangles = 2.210624; // fuzzed, old value = 2.172035
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.443338; // fuzzed, old value = 1.479794

	FUZZ s.graph.MinimalDistTresh = 1.773373; // fuzzed, old value = 1.821545
	FUZZ s.graph.RatioSub = 0.998683; // fuzzed, old value = 1.014226
	FUZZ s.graph.RatioTresh = 0.439050; // fuzzed, old value = 0.419309

	FUZZ s.utils.SlashLineDensity = 0.472617; // fuzzed, old value = 0.480276
	FUZZ s.utils.TestPlusDensity = 0.441184; // fuzzed, old value = 0.434167
	FUZZ s.utils.TestPlusSq = 0.426704; // fuzzed, old value = 0.429271
	FUZZ s.utils.TestMinusRatio = 0.367076; // fuzzed, old value = 0.375310
	FUZZ s.utils.TestMinusDensity = 0.600347; // fuzzed, old value = 0.598837
	FUZZ s.utils.TestMinusHeightFactor = 0.741438; // fuzzed, old value = 0.771482

	FUZZ s.separator.hu_1_1 = 0.173944; // fuzzed, old value = 0.182200
	FUZZ s.separator.hu_1_2 = 0.081927; // fuzzed, old value = 0.080232
	FUZZ s.separator.hu_0_1 = 0.234492; // fuzzed, old value = 0.243055
	FUZZ s.separator.hu_1_3 = 0.091775; // fuzzed, old value = 0.091750
	FUZZ s.separator.hu_0_2 = 0.249494; // fuzzed, old value = 0.260262
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.520753; // fuzzed, old value = 0.535419
	FUZZ s.separator.capHeightMax = 1.386770; // fuzzed, old value = 1.331047
	FUZZ s.separator.gdConst = 1.481396; // fuzzed, old value = 1.494774
	FUZZ s.separator.SurfCoef = 2.743604; // fuzzed, old value = 2.690169
	FUZZ s.separator.capHeightRatio = 0.251834; // fuzzed, old value = 0.248689
	FUZZ s.separator.capHeightRatio2 = 1.856000; // fuzzed, old value = 1.816786
	FUZZ s.separator.getRatio1 = 0.875543; // fuzzed, old value = 0.868547
	FUZZ s.separator.getRatio2 = 1.149966; // fuzzed, old value = 1.112853
	FUZZ s.separator.testSlashLine1 = 3.125752; // fuzzed, old value = 3.190627
	FUZZ s.separator.testSlashLine2 = 2.947063; // fuzzed, old value = 2.961420
	FUZZ s.separator.minDensity = 0.199102; // fuzzed, old value = 0.204792
	FUZZ s.separator.maxDensity = 0.802394; // fuzzed, old value = 0.835935
	FUZZ s.separator.extCapHeightMin = 0.304819; // fuzzed, old value = 0.298221
	FUZZ s.separator.extCapHeightMax = 2.004448; // fuzzed, old value = 2.078549
	FUZZ s.separator.extRatioMin = 0.276794; // fuzzed, old value = 0.280485
	FUZZ s.separator.extRatioMax = 1.467764; // fuzzed, old value = 1.448039
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = true; // fuzzed, old value = true

	FUZZ s.labels.underlinePos = 0.462258; // fuzzed, old value = 0.463312
	FUZZ s.labels.weightUnderline = 0.314314; // fuzzed, old value = 0.315862
	FUZZ s.labels.ratioBase = 0.824292; // fuzzed, old value = 0.862996
	FUZZ s.labels.ratioWeight = 0.301878; // fuzzed, old value = 0.293834
	FUZZ s.labels.adjustDec = 1.259990; // fuzzed, old value = 1.289963
	FUZZ s.labels.adjustInc = 0.868384; // fuzzed, old value = 0.859068
	FUZZ s.labels.sameLineEps = 0.114940; // fuzzed, old value = 0.118423
	FUZZ s.labels.heightRatio = 0.835437; // fuzzed, old value = 0.811731
	FUZZ s.labels.medHeightFactor = 0.476406; // fuzzed, old value = 0.467762
	FUZZ s.labels.capHeightError = 0.473745; // fuzzed, old value = 0.488753

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.580020; // fuzzed, old value = 2.662893
	FUZZ s.lcomb.MaximalDistanceFactor = 0.710797; // fuzzed, old value = 0.683355
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.286979; // fuzzed, old value = 0.290503
	FUZZ s.lcomb.FillLabelFactor1 = 0.520573; // fuzzed, old value = 0.523083
	FUZZ s.lcomb.FillLabelFactor2 = 0.458278; // fuzzed, old value = 0.474184

	FUZZ s.p_estimator.DefaultApriority = 0.491940; // fuzzed, old value = 0.497449
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.777357; // fuzzed, old value = 0.765935
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.245846; // fuzzed, old value = 0.245732
	FUZZ s.p_estimator.LogisticScale = 0.944047; // fuzzed, old value = 0.971043
	FUZZ s.p_estimator.LogisticLocation = 0.918053; // fuzzed, old value = 0.951224
}

