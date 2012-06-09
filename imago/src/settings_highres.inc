
void updateSettingsHighResolution(Settings &s)
{
	s.general.UseProbablistics = false;

	FUZZ s.separator.ext2charRatio = 1.2;

	FUZZ s.molecule.LengthFactor_long = 0.329933; // fuzzed, old value = 0.327577
	FUZZ s.molecule.LengthFactor_medium = 0.414396; // fuzzed, old value = 0.420114
	FUZZ s.molecule.LengthFactor_default = 0.506995; // fuzzed, old value = 0.492822
	FUZZ s.molecule.LengthValue_long = 96.119201; // fuzzed, old value = 96.851551
	FUZZ s.molecule.LengthValue_medium = 85.394816; // fuzzed, old value = 84.798635
	FUZZ s.molecule.SpaceMultiply = 1.543451; // fuzzed, old value = 1.571064
	FUZZ s.molecule.AngleTreshold = 0.257380; // fuzzed, old value = 0.262487
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.107238; // fuzzed, old value = 17.161776
	FUZZ s.estimation.LineThickness = 6.162020; // fuzzed, old value = 6.152596
	FUZZ s.estimation.AvgBondLength = 30.432327; // fuzzed, old value = 29.919342
	FUZZ s.estimation.AddVertexEps = 5.600535; // fuzzed, old value = 5.611061
	FUZZ s.estimation.MaxSymRatio = 1.060708; // fuzzed, old value = 1.049570
	FUZZ s.estimation.MinSymRatio = 0.340565; // fuzzed, old value = 0.333807
	FUZZ s.estimation.ParLinesEps = 0.523253; // fuzzed, old value = 0.513016
	FUZZ s.estimation.SymHeightErr = 28.866829; // fuzzed, old value = 29.002597
	FUZZ s.estimation.CapitalHeightError = 0.841468; // fuzzed, old value = 0.845889
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.535984; // fuzzed, old value = 0.545024
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.2;
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 123; // fuzzed, old value = 124
	FUZZ s.mbond.LongErr = 0.408196; // fuzzed, old value = 0.396877
	FUZZ s.mbond.MediumBond = 98; // fuzzed, old value = 97
	FUZZ s.mbond.MediumErr = 0.387146; // fuzzed, old value = 0.387916
	FUZZ s.mbond.DefaultErr = 0.642675; // fuzzed, old value = 0.656186
	FUZZ s.mbond.ParBondsEps = 0.352485; // fuzzed, old value = 0.359492
	FUZZ s.mbond.DoubleRatioTresh = 7.222879; // fuzzed, old value = 7.060831
	FUZZ s.mbond.DoubleCoef = 0.081992; // fuzzed, old value = 0.080102
	FUZZ s.mbond.DoubleMagic1 = 0.912936; // fuzzed, old value = 0.901851
	FUZZ s.mbond.DoubleMagic2 = 1.024289; // fuzzed, old value = 1.023456
	FUZZ s.mbond.DoubleTreshMin = 0.094883; // fuzzed, old value = 0.094704
	FUZZ s.mbond.DoubleTreshMax = 0.821201; // fuzzed, old value = 0.840386
	FUZZ s.mbond.MaxLen1 = 147.364301; // fuzzed, old value = 151.852015
	FUZZ s.mbond.MaxLen2 = 122.048735; // fuzzed, old value = 124.628985
	FUZZ s.mbond.MaxLen3 = 109.885495; // fuzzed, old value = 110.034897
	FUZZ s.mbond.MaxLen4 = 108.031373; // fuzzed, old value = 110.558181
	FUZZ s.mbond.MaxLen5 = 83.964874; // fuzzed, old value = 85.737262
	FUZZ s.mbond.MinLen1 = 84.373774; // fuzzed, old value = 85.418678
	FUZZ s.mbond.MinLen2 = 73.755743; // fuzzed, old value = 75.007035
	FUZZ s.mbond.mbe1 = 0.079550; // fuzzed, old value = 0.079031
	FUZZ s.mbond.mbe2 = 0.157175; // fuzzed, old value = 0.154150
	FUZZ s.mbond.mbe3 = 0.213047; // fuzzed, old value = 0.207919
	FUZZ s.mbond.mbe4 = 0.178446; // fuzzed, old value = 0.180409
	FUZZ s.mbond.mbe5 = 0.157898; // fuzzed, old value = 0.162732
	FUZZ s.mbond.mbe6 = 0.204297; // fuzzed, old value = 0.209911
	FUZZ s.mbond.mbe7 = 0.391210; // fuzzed, old value = 0.389446
	FUZZ s.mbond.mbe_def = 0.530971; // fuzzed, old value = 0.530244
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.320618; // fuzzed, old value = 0.328688
	FUZZ s.mbond.DoubleRightLengthTresh = 0.327756; // fuzzed, old value = 0.321428
	FUZZ s.mbond.TripleLeftLengthTresh = 0.267104; // fuzzed, old value = 0.262715
	FUZZ s.mbond.TripleRightLengthTresh = 0.239327; // fuzzed, old value = 0.239565
	FUZZ s.mbond.Case1LengthTresh = 98.221044; // fuzzed, old value = 100.802495
	FUZZ s.mbond.Case1Factor = 0.438109; // fuzzed, old value = 0.436231
	FUZZ s.mbond.Case2LengthTresh = 76.174484; // fuzzed, old value = 75.604732
	FUZZ s.mbond.Case2Factor = 0.677452; // fuzzed, old value = 0.687491
	FUZZ s.mbond.Case3Factor = 0.878380; // fuzzed, old value = 0.896522
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.090968; // fuzzed, old value = 0.093695
	FUZZ s.skeleton.BaseSmallErr = 0.145948; // fuzzed, old value = 0.147343
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.326711; // fuzzed, old value = 0.329723
	FUZZ s.skeleton.MediumBondLen = 87; // fuzzed, old value = 87
	FUZZ s.skeleton.MediumMul = 0.181296; // fuzzed, old value = 0.181510
	FUZZ s.skeleton.MediumSmallErr = 0.138014; // fuzzed, old value = 0.141484
	FUZZ s.skeleton.LongBondLen = 107; // fuzzed, old value = 107
	FUZZ s.skeleton.LongMul = 0.139814; // fuzzed, old value = 0.141946
	FUZZ s.skeleton.LongSmallErr = 0.058012; // fuzzed, old value = 0.058937
	FUZZ s.skeleton.BrokenRepairFactor = 3.101007; // fuzzed, old value = 3.089407
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.997585; // fuzzed, old value = 0.993982
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.643939; // fuzzed, old value = 2.623262
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.212134; // fuzzed, old value = 0.208422
	FUZZ s.skeleton.DissolveMinErr = 0.184073; // fuzzed, old value = 0.179234
	FUZZ s.skeleton.ConnectBlockS = 10.113731; // fuzzed, old value = 10.000933
	FUZZ s.skeleton.ConnectFactor = 2.098928; // fuzzed, old value = 2.044460
	FUZZ s.skeleton.JoinVerticiesConst = 0.097434; // fuzzed, old value = 0.099955
	FUZZ s.skeleton.DissolveConst = 0.099071; // fuzzed, old value = 0.098953
	FUZZ s.skeleton.Dissolve2Const = 0.204770; // fuzzed, old value = 0.204977
	FUZZ s.skeleton.Join2Const = 0.345750; // fuzzed, old value = 0.340369
	FUZZ s.skeleton.Join3Const = 0.191760; // fuzzed, old value = 0.187886
	FUZZ s.skeleton.DistTreshLimFactor = 1.882995; // fuzzed, old value = 1.935630
	FUZZ s.skeleton.SlopeFact1 = 0.107118; // fuzzed, old value = 0.104076
	FUZZ s.skeleton.SlopeFact2 = 0.185570; // fuzzed, old value = 0.186967
	FUZZ s.skeleton.ShrinkEps = 0.127320; // fuzzed, old value = 0.127274
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10

	FUZZ s.routines.Circle_GapRadiusMax = 1.25;
	FUZZ s.routines.Circle_GapAngleMax = 0.5;
	FUZZ s.routines.Circle_MinRadius = 10.0;
	FUZZ s.routines.Circle_MaxDeviation = 0.2;
	FUZZ s.routines.Circle_AsCharFactor = 1.4;

	FUZZ s.routines.Algebra_IntersectionEps = 0.010292; // fuzzed, old value = 0.010378
	FUZZ s.routines.Algebra_SameLineEps = 0.201977; // fuzzed, old value = 0.207572
	FUZZ s.routines.Approx_Eps1 = 1.199592; // fuzzed, old value = 1.191356
	FUZZ s.routines.Approx_Eps2 = 0.853566; // fuzzed, old value = 0.846483
	FUZZ s.routines.Approx_CalcLineTresh = 0.851438; // fuzzed, old value = 0.874323

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.764149; // fuzzed, old value = 2.821331
	FUZZ s.wbe.SingleDownAngleMax = 44.867863; // fuzzed, old value = 43.580169
	FUZZ s.wbe.SingleDownDistancesMax = 9.551511; // fuzzed, old value = 9.499786
	FUZZ s.wbe.SingleDownLengthMax = 44.093312; // fuzzed, old value = 44.608281
	FUZZ s.wbe.SingleUpRatioEps = 1.903618; // fuzzed, old value = 1.871563
	FUZZ s.wbe.SingleUpDefCoeff = 0.276430; // fuzzed, old value = 0.276828
	FUZZ s.wbe.SingleUpIncCoeff = 0.406141; // fuzzed, old value = 0.406043
	FUZZ s.wbe.SingleUpIncLengthTresh = 32.282101; // fuzzed, old value = 32.864907
	FUZZ s.wbe.SingleUpInterpolateEps = 0.066895; // fuzzed, old value = 0.064949
	FUZZ s.wbe.SingleUpMagicAddition = 0.221899; // fuzzed, old value = 0.219567
	FUZZ s.wbe.SingleUpS2Divisor = 1.713263; // fuzzed, old value = 1.692711
	FUZZ s.wbe.SingleUpMinATresh = 1.623249; // fuzzed, old value = 1.651449
	FUZZ s.wbe.SingleUpSquareRatio = 0.602825; // fuzzed, old value = 0.616921
	FUZZ s.wbe.SingleUpAngleTresh = 0.068178; // fuzzed, old value = 0.066395
	FUZZ s.wbe.SomeTresh = 0.103020; // fuzzed, old value = 0.101577
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = true; 
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7	
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.018301; // fuzzed, old value = 1.037340
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.194095; // fuzzed, old value = 1.182250
	FUZZ s.characters.WriteEasyFactor = 0.937532; // fuzzed, old value = 0.943528
	FUZZ s.characters.WriteVeryEasyFactor = 0.830893; // fuzzed, old value = 0.856394
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.133057; // fuzzed, old value = 3.133209
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.368611; // fuzzed, old value = 3.466852
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.102116; // fuzzed, old value = 0.102772
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.452249; // fuzzed, old value = 2.447774
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.431513; // fuzzed, old value = 3.401322
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.048093; // fuzzed, old value = 1.047057
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.306496; // fuzzed, old value = 0.309555

	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.459060; // fuzzed, old value = 0.473015
	FUZZ s.csr.DeleteBadTriangles = 1.840575; // fuzzed, old value = 1.794851
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.456201; // fuzzed, old value = 1.487796

	FUZZ s.graph.MinimalDistTresh = 2.181059; // fuzzed, old value = 2.165100
	FUZZ s.graph.RatioSub = 0.953543; // fuzzed, old value = 0.933875
	FUZZ s.graph.RatioTresh = 0.425507; // fuzzed, old value = 0.428588

	FUZZ s.utils.SlashLineDensity = 0.446883; // fuzzed, old value = 0.458298
	FUZZ s.utils.TestPlusDensity = 0.449941; // fuzzed, old value = 0.442127
	FUZZ s.utils.TestPlusSq = 0.410484; // fuzzed, old value = 0.408222
	FUZZ s.utils.TestMinusRatio = 0.349959; // fuzzed, old value = 0.345300
	FUZZ s.utils.TestMinusDensity = 0.583367; // fuzzed, old value = 0.589338
	FUZZ s.utils.TestMinusHeightFactor = 0.754625; // fuzzed, old value = 0.765840

	FUZZ s.separator.hu_1_1 = 0.201860; // fuzzed, old value = 0.202047
	FUZZ s.separator.hu_1_2 = 0.085774; // fuzzed, old value = 0.085324
	FUZZ s.separator.hu_0_1 = 0.237021; // fuzzed, old value = 0.244123
	FUZZ s.separator.hu_1_3 = 0.078775; // fuzzed, old value = 0.077811
	FUZZ s.separator.hu_0_2 = 0.256344; // fuzzed, old value = 0.253931
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.554483; // fuzzed, old value = 0.540371
	FUZZ s.separator.capHeightMax = 1.352450; // fuzzed, old value = 1.388439
	FUZZ s.separator.gdConst = 1.607762; // fuzzed, old value = 1.570286
	FUZZ s.separator.SurfCoef = 2.830323; // fuzzed, old value = 2.808046
	FUZZ s.separator.capHeightRatio = 0.240685; // fuzzed, old value = 0.240186
	FUZZ s.separator.capHeightRatio2 = 1.920779; // fuzzed, old value = 1.900306
	FUZZ s.separator.getRatio1 = 0.958444; // fuzzed, old value = 0.948203
	FUZZ s.separator.getRatio2 = 1.131309; // fuzzed, old value = 1.104939
	FUZZ s.separator.testSlashLine1 = 3.003573; // fuzzed, old value = 3.001317
	FUZZ s.separator.testSlashLine2 = 2.996119; // fuzzed, old value = 2.980345
	FUZZ s.separator.minDensity = 0.202036; // fuzzed, old value = 0.196967
	FUZZ s.separator.maxDensity = 0.845004; // fuzzed, old value = 0.833956
	FUZZ s.separator.extCapHeightMin = 0.303064; // fuzzed, old value = 0.296796
	FUZZ s.separator.extCapHeightMax = 1.996973; // fuzzed, old value = 1.986065
	FUZZ s.separator.extRatioMin = 0.281311; // fuzzed, old value = 0.281111
	FUZZ s.separator.extRatioMax = 1.459820; // fuzzed, old value = 1.484926
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = true;

	FUZZ s.labels.underlinePos = 0.505753; // fuzzed, old value = 0.493972
	FUZZ s.labels.weightUnderline = 0.299877; // fuzzed, old value = 0.294700
	FUZZ s.labels.ratioBase = 0.792477; // fuzzed, old value = 0.812221
	FUZZ s.labels.ratioWeight = 0.308817; // fuzzed, old value = 0.303176
	FUZZ s.labels.adjustDec = 1.220214; // fuzzed, old value = 1.217033
	FUZZ s.labels.adjustInc = 0.848047; // fuzzed, old value = 0.824556
	FUZZ s.labels.sameLineEps = 0.136370; // fuzzed, old value = 0.136545
	FUZZ s.labels.heightRatio = 0.884890; // fuzzed, old value = 0.859314
	FUZZ s.labels.medHeightFactor = 0.477681; // fuzzed, old value = 0.475030
	FUZZ s.labels.capHeightError = 0.535593; // fuzzed, old value = 0.547185

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.879197; // fuzzed, old value = 2.866555
	FUZZ s.lcomb.MaximalDistanceFactor = 0.7;
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.3;
	FUZZ s.lcomb.FillLabelFactor1 = 0.487643; // fuzzed, old value = 0.478025
	FUZZ s.lcomb.FillLabelFactor2 = 0.527013; // fuzzed, old value = 0.515109

	FUZZ s.p_estimator.DefaultApriority = 0.5;
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.8;
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.25;
	FUZZ s.p_estimator.LogisticScale = 1.0;
	FUZZ s.p_estimator.LogisticLocation = 1.0;
}

