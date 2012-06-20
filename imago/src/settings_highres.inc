
void updateSettingsHighResolution(Settings &s)
{
	s.general.UseProbablistics = false;
	s.p_estimator.UsePerimeterNormalization = true;

	FUZZ s.separator.ext2charRatio = 1.200453; // fuzzed, old value = 1.228457

	FUZZ s.molecule.LengthFactor_long = 0.328246; // fuzzed, old value = 0.342378
	FUZZ s.molecule.LengthFactor_medium = 0.434499; // fuzzed, old value = 0.421067
	FUZZ s.molecule.LengthFactor_default = 0.481638; // fuzzed, old value = 0.495114
	FUZZ s.molecule.LengthValue_long = 92.880256; // fuzzed, old value = 94.962996
	FUZZ s.molecule.LengthValue_medium = 84.317579; // fuzzed, old value = 84.232876
	FUZZ s.molecule.SpaceMultiply = 1.555695; // fuzzed, old value = 1.558828
	FUZZ s.molecule.AngleTreshold = 0.256197; // fuzzed, old value = 0.252877
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.309366; // fuzzed, old value = 16.909028
	FUZZ s.estimation.LineThickness = 5.873329; // fuzzed, old value = 6.032835
	FUZZ s.estimation.AvgBondLength = 31.898315; // fuzzed, old value = 31.788254
	FUZZ s.estimation.AddVertexEps = 5.204447; // fuzzed, old value = 5.364589
	FUZZ s.estimation.MaxSymRatio = 0.999321; // fuzzed, old value = 1.031245
	FUZZ s.estimation.MinSymRatio = 0.335394; // fuzzed, old value = 0.328454
	FUZZ s.estimation.ParLinesEps = 0.559987; // fuzzed, old value = 0.542827
	FUZZ s.estimation.SymHeightErr = 27.820523; // fuzzed, old value = 27.521804
	FUZZ s.estimation.CapitalHeightError = 0.806030; // fuzzed, old value = 0.841033
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 22
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.553435; // fuzzed, old value = 0.558278
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.193722; // fuzzed, old value = 0.192857
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 123; // fuzzed, old value = 119
	FUZZ s.mbond.LongErr = 0.408126; // fuzzed, old value = 0.425297
	FUZZ s.mbond.MediumBond = 93; // fuzzed, old value = 96
	FUZZ s.mbond.MediumErr = 0.396845; // fuzzed, old value = 0.387197
	FUZZ s.mbond.DefaultErr = 0.628855; // fuzzed, old value = 0.653412
	FUZZ s.mbond.ParBondsEps = 0.372832; // fuzzed, old value = 0.368385
	FUZZ s.mbond.DoubleRatioTresh = 7.093099; // fuzzed, old value = 7.363217
	FUZZ s.mbond.DoubleCoef = 0.080777; // fuzzed, old value = 0.080862
	FUZZ s.mbond.DoubleMagic1 = 0.881395; // fuzzed, old value = 0.877935
	FUZZ s.mbond.DoubleMagic2 = 1.008979; // fuzzed, old value = 1.047535
	FUZZ s.mbond.DoubleTreshMin = 0.091698; // fuzzed, old value = 0.093278
	FUZZ s.mbond.DoubleTreshMax = 0.841328; // fuzzed, old value = 0.825004
	FUZZ s.mbond.MaxLen1 = 145.204510; // fuzzed, old value = 144.768662
	FUZZ s.mbond.MaxLen2 = 121.539774; // fuzzed, old value = 124.525505
	FUZZ s.mbond.MaxLen3 = 118.634278; // fuzzed, old value = 115.146363
	FUZZ s.mbond.MaxLen4 = 107.978864; // fuzzed, old value = 110.919672
	FUZZ s.mbond.MaxLen5 = 83.711625; // fuzzed, old value = 83.868397
	FUZZ s.mbond.MinLen1 = 86.113757; // fuzzed, old value = 86.559273
	FUZZ s.mbond.MinLen2 = 73.528694; // fuzzed, old value = 70.519039
	FUZZ s.mbond.mbe1 = 0.074992; // fuzzed, old value = 0.076106
	FUZZ s.mbond.mbe2 = 0.157399; // fuzzed, old value = 0.150134
	FUZZ s.mbond.mbe3 = 0.207621; // fuzzed, old value = 0.210272
	FUZZ s.mbond.mbe4 = 0.179698; // fuzzed, old value = 0.174097
	FUZZ s.mbond.mbe5 = 0.163430; // fuzzed, old value = 0.159550
	FUZZ s.mbond.mbe6 = 0.199903; // fuzzed, old value = 0.203386
	FUZZ s.mbond.mbe7 = 0.412779; // fuzzed, old value = 0.409094
	FUZZ s.mbond.mbe_def = 0.510249; // fuzzed, old value = 0.534394
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.308959; // fuzzed, old value = 0.307169
	FUZZ s.mbond.DoubleRightLengthTresh = 0.328139; // fuzzed, old value = 0.343885
	FUZZ s.mbond.TripleLeftLengthTresh = 0.266600; // fuzzed, old value = 0.279280
	FUZZ s.mbond.TripleRightLengthTresh = 0.237110; // fuzzed, old value = 0.233023
	FUZZ s.mbond.Case1LengthTresh = 97.412387; // fuzzed, old value = 98.975080
	FUZZ s.mbond.Case1Factor = 0.444853; // fuzzed, old value = 0.434294
	FUZZ s.mbond.Case2LengthTresh = 78.184234; // fuzzed, old value = 77.113559
	FUZZ s.mbond.Case2Factor = 0.658458; // fuzzed, old value = 0.675419
	FUZZ s.mbond.Case3Factor = 0.821403; // fuzzed, old value = 0.842683
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.086847; // fuzzed, old value = 0.090421
	FUZZ s.skeleton.BaseSmallErr = 0.139838; // fuzzed, old value = 0.140465
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.327652; // fuzzed, old value = 0.328864
	FUZZ s.skeleton.MediumBondLen = 87; // fuzzed, old value = 90
	FUZZ s.skeleton.MediumMul = 0.195770; // fuzzed, old value = 0.188970
	FUZZ s.skeleton.MediumSmallErr = 0.139379; // fuzzed, old value = 0.137190
	FUZZ s.skeleton.LongBondLen = 105; // fuzzed, old value = 108
	FUZZ s.skeleton.LongMul = 0.129561; // fuzzed, old value = 0.136195
	FUZZ s.skeleton.LongSmallErr = 0.052888; // fuzzed, old value = 0.055190
	FUZZ s.skeleton.BrokenRepairFactor = 3.208369; // fuzzed, old value = 3.236903
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.046059; // fuzzed, old value = 1.045592
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.557861; // fuzzed, old value = 2.584007
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.201264; // fuzzed, old value = 0.201864
	FUZZ s.skeleton.DissolveMinErr = 0.192701; // fuzzed, old value = 0.189309
	FUZZ s.skeleton.ConnectBlockS = 9.764267; // fuzzed, old value = 10.044083
	FUZZ s.skeleton.ConnectFactor = 2.012180; // fuzzed, old value = 2.059312
	FUZZ s.skeleton.JoinVerticiesConst = 0.094646; // fuzzed, old value = 0.099172
	FUZZ s.skeleton.DissolveConst = 0.101654; // fuzzed, old value = 0.100556
	FUZZ s.skeleton.Dissolve2Const = 0.216204; // fuzzed, old value = 0.209509
	FUZZ s.skeleton.Join2Const = 0.333901; // fuzzed, old value = 0.340753
	FUZZ s.skeleton.Join3Const = 0.198315; // fuzzed, old value = 0.197636
	FUZZ s.skeleton.DistTreshLimFactor = 1.787764; // fuzzed, old value = 1.825859
	FUZZ s.skeleton.SlopeFact1 = 0.105327; // fuzzed, old value = 0.103476
	FUZZ s.skeleton.SlopeFact2 = 0.188657; // fuzzed, old value = 0.181478
	FUZZ s.skeleton.ShrinkEps = 0.123481; // fuzzed, old value = 0.122952
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10

	FUZZ s.routines.Circle_GapRadiusMax = 1.332954; // fuzzed, old value = 1.290321
	FUZZ s.routines.Circle_GapAngleMax = 0.492134; // fuzzed, old value = 0.478777
	FUZZ s.routines.Circle_MinRadius = 10.299804; // fuzzed, old value = 9.825816
	FUZZ s.routines.Circle_MaxDeviation = 0.192373; // fuzzed, old value = 0.202378
	FUZZ s.routines.Circle_AsCharFactor = 1.410306; // fuzzed, old value = 1.454969

	FUZZ s.routines.Algebra_IntersectionEps = 0.010432; // fuzzed, old value = 0.010044
	FUZZ s.routines.Algebra_SameLineEps = 0.194358; // fuzzed, old value = 0.195141
	FUZZ s.routines.Approx_Eps1 = 1.115186; // fuzzed, old value = 1.171280
	FUZZ s.routines.Approx_Eps2 = 0.840292; // fuzzed, old value = 0.860450
	FUZZ s.routines.Approx_CalcLineTresh = 0.850519; // fuzzed, old value = 0.816059

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.705028; // fuzzed, old value = 2.657036
	FUZZ s.wbe.SingleDownAngleMax = 45.137292; // fuzzed, old value = 45.941874
	FUZZ s.wbe.SingleDownDistancesMax = 9.029203; // fuzzed, old value = 9.451804
	FUZZ s.wbe.SingleDownLengthMax = 43.696969; // fuzzed, old value = 42.945260
	FUZZ s.wbe.SingleUpRatioEps = 1.908091; // fuzzed, old value = 1.903476
	FUZZ s.wbe.SingleUpDefCoeff = 0.278302; // fuzzed, old value = 0.266904
	FUZZ s.wbe.SingleUpIncCoeff = 0.406486; // fuzzed, old value = 0.424490
	FUZZ s.wbe.SingleUpIncLengthTresh = 32.250473; // fuzzed, old value = 32.471112
	FUZZ s.wbe.SingleUpInterpolateEps = 0.068279; // fuzzed, old value = 0.066085
	FUZZ s.wbe.SingleUpMagicAddition = 0.215318; // fuzzed, old value = 0.224346
	FUZZ s.wbe.SingleUpS2Divisor = 1.762490; // fuzzed, old value = 1.712335
	FUZZ s.wbe.SingleUpMinATresh = 1.574485; // fuzzed, old value = 1.645916
	FUZZ s.wbe.SingleUpSquareRatio = 0.594876; // fuzzed, old value = 0.615619
	FUZZ s.wbe.SingleUpAngleTresh = 0.070980; // fuzzed, old value = 0.069989
	FUZZ s.wbe.SomeTresh = 0.110870; // fuzzed, old value = 0.107228
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = true; 
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 0.972401; // fuzzed, old value = 0.998118
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.183425; // fuzzed, old value = 1.205164
	FUZZ s.characters.WriteEasyFactor = 0.917198; // fuzzed, old value = 0.964168
	FUZZ s.characters.WriteVeryEasyFactor = 0.797809; // fuzzed, old value = 0.796940
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 2.997639; // fuzzed, old value = 3.110257
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.534799; // fuzzed, old value = 3.464338
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.093991; // fuzzed, old value = 0.097051
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.442262; // fuzzed, old value = 2.343407
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.444646; // fuzzed, old value = 3.436377
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.074821; // fuzzed, old value = 1.053116
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.317866; // fuzzed, old value = 0.320872

	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.451340; // fuzzed, old value = 0.454552
	FUZZ s.csr.DeleteBadTriangles = 1.957555; // fuzzed, old value = 1.882111
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.422244; // fuzzed, old value = 1.463723

	FUZZ s.graph.MinimalDistTresh = 2.039565; // fuzzed, old value = 2.142176
	FUZZ s.graph.RatioSub = 0.986657; // fuzzed, old value = 0.962103
	FUZZ s.graph.RatioTresh = 0.424717; // fuzzed, old value = 0.443022

	FUZZ s.utils.SlashLineDensity = 0.426660; // fuzzed, old value = 0.446247
	FUZZ s.utils.TestPlusDensity = 0.444915; // fuzzed, old value = 0.467570
	FUZZ s.utils.TestPlusSq = 0.419234; // fuzzed, old value = 0.412350
	FUZZ s.utils.TestMinusRatio = 0.347247; // fuzzed, old value = 0.356863
	FUZZ s.utils.TestMinusDensity = 0.555646; // fuzzed, old value = 0.566996
	FUZZ s.utils.TestMinusHeightFactor = 0.727853; // fuzzed, old value = 0.737457

	FUZZ s.separator.hu_1_1 = 0.187009; // fuzzed, old value = 0.193746
	FUZZ s.separator.hu_1_2 = 0.089999; // fuzzed, old value = 0.086949
	FUZZ s.separator.hu_0_1 = 0.227741; // fuzzed, old value = 0.238514
	FUZZ s.separator.hu_1_3 = 0.084149; // fuzzed, old value = 0.081834
	FUZZ s.separator.hu_0_2 = 0.266166; // fuzzed, old value = 0.266757
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.581250; // fuzzed, old value = 0.566844
	FUZZ s.separator.capHeightMax = 1.358266; // fuzzed, old value = 1.346071
	FUZZ s.separator.gdConst = 1.517767; // fuzzed, old value = 1.580729
	FUZZ s.separator.SurfCoef = 2.593501; // fuzzed, old value = 2.708069
	FUZZ s.separator.capHeightRatio = 0.238682; // fuzzed, old value = 0.240702
	FUZZ s.separator.capHeightRatio2 = 1.964489; // fuzzed, old value = 1.919897
	FUZZ s.separator.getRatio1 = 0.995006; // fuzzed, old value = 0.956948
	FUZZ s.separator.getRatio2 = 1.104071; // fuzzed, old value = 1.136410
	FUZZ s.separator.testSlashLine1 = 3.246238; // fuzzed, old value = 3.135648
	FUZZ s.separator.testSlashLine2 = 3.031578; // fuzzed, old value = 3.010123
	FUZZ s.separator.minDensity = 0.204102; // fuzzed, old value = 0.197791
	FUZZ s.separator.maxDensity = 0.806080; // fuzzed, old value = 0.807553
	FUZZ s.separator.extCapHeightMin = 0.306478; // fuzzed, old value = 0.293976
	FUZZ s.separator.extCapHeightMax = 2.095513; // fuzzed, old value = 2.024590
	FUZZ s.separator.extRatioMin = 0.274874; // fuzzed, old value = 0.284612
	FUZZ s.separator.extRatioMax = 1.540172; // fuzzed, old value = 1.475299
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = true; // fuzzed, old value = true

	FUZZ s.labels.underlinePos = 0.476853; // fuzzed, old value = 0.481036
	FUZZ s.labels.weightUnderline = 0.286072; // fuzzed, old value = 0.300502
	FUZZ s.labels.ratioBase = 0.820609; // fuzzed, old value = 0.826703
	FUZZ s.labels.ratioWeight = 0.302920; // fuzzed, old value = 0.294782
	FUZZ s.labels.adjustDec = 1.274235; // fuzzed, old value = 1.240649
	FUZZ s.labels.adjustInc = 0.873424; // fuzzed, old value = 0.839797
	FUZZ s.labels.sameLineEps = 0.141207; // fuzzed, old value = 0.135340
	FUZZ s.labels.heightRatio = 0.871707; // fuzzed, old value = 0.848121
	FUZZ s.labels.medHeightFactor = 0.453486; // fuzzed, old value = 0.463626
	FUZZ s.labels.capHeightError = 0.522767; // fuzzed, old value = 0.519912

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.820964; // fuzzed, old value = 2.907583
	FUZZ s.lcomb.MaximalDistanceFactor = 0.710885; // fuzzed, old value = 0.683355
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.282795; // fuzzed, old value = 0.290503
	FUZZ s.lcomb.FillLabelFactor1 = 0.500139; // fuzzed, old value = 0.507519
	FUZZ s.lcomb.FillLabelFactor2 = 0.525941; // fuzzed, old value = 0.505894

	FUZZ s.p_estimator.DefaultApriority = 0.488702; // fuzzed, old value = 0.497449
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.736039; // fuzzed, old value = 0.765935
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.242319; // fuzzed, old value = 0.245732
	FUZZ s.p_estimator.LogisticScale = 1.003589; // fuzzed, old value = 0.971043
	FUZZ s.p_estimator.LogisticLocation = 0.910447; // fuzzed, old value = 0.951224
}

