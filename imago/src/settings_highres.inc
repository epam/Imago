
void updateSettingsHighResolution(Settings &s)
{
	s.general.UseProbablistics = false;
	s.p_estimator.UsePerimeterNormalization = true;

	FUZZ s.separator.ext2charRatio = 1.145039; // fuzzed, old value = 1.200453
	FUZZ s.separator.SymProbabilityThresh = 0.558107; // fuzzed, old value = 0.56

	FUZZ s.molecule.LengthFactor_long = 0.334646; // fuzzed, old value = 0.328246
	FUZZ s.molecule.LengthFactor_medium = 0.431059; // fuzzed, old value = 0.434499
	FUZZ s.molecule.LengthFactor_default = 0.489375; // fuzzed, old value = 0.481638
	FUZZ s.molecule.LengthValue_long = 90.351397; // fuzzed, old value = 92.880256
	FUZZ s.molecule.LengthValue_medium = 84.750270; // fuzzed, old value = 84.317579
	FUZZ s.molecule.SpaceMultiply = 1.532823; // fuzzed, old value = 1.555695
	FUZZ s.molecule.AngleTreshold = 0.258483; // fuzzed, old value = 0.256197
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.367228; // fuzzed, old value = 16.309366
	FUZZ s.estimation.LineThickness = 6.053300; // fuzzed, old value = 5.873329
	FUZZ s.estimation.AvgBondLength = 30.642660; // fuzzed, old value = 31.898315
	FUZZ s.estimation.AddVertexEps = 5.262715; // fuzzed, old value = 5.204447
	FUZZ s.estimation.MaxSymRatio = 0.964125; // fuzzed, old value = 0.999321
	FUZZ s.estimation.MinSymRatio = 0.321142; // fuzzed, old value = 0.335394
	FUZZ s.estimation.ParLinesEps = 0.538161; // fuzzed, old value = 0.559987
	FUZZ s.estimation.SymHeightErr = 28.626645; // fuzzed, old value = 27.820523
	FUZZ s.estimation.CapitalHeightError = 0.780943; // fuzzed, old value = 0.806030
	FUZZ s.estimation.DoubleBondDist = 22; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.529739; // fuzzed, old value = 0.553435
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.185056; // fuzzed, old value = 0.193722
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 122; // fuzzed, old value = 123
	FUZZ s.mbond.LongErr = 0.389492; // fuzzed, old value = 0.408126
	FUZZ s.mbond.MediumBond = 91; // fuzzed, old value = 93
	FUZZ s.mbond.MediumErr = 0.405153; // fuzzed, old value = 0.396845
	FUZZ s.mbond.DefaultErr = 0.599899; // fuzzed, old value = 0.628855
	FUZZ s.mbond.ParBondsEps = 0.376117; // fuzzed, old value = 0.372832
	FUZZ s.mbond.DoubleRatioTresh = 6.942121; // fuzzed, old value = 7.093099
	FUZZ s.mbond.DoubleCoef = 0.082946; // fuzzed, old value = 0.080777
	FUZZ s.mbond.DoubleMagic1 = 0.859396; // fuzzed, old value = 0.881395
	FUZZ s.mbond.DoubleMagic2 = 1.013211; // fuzzed, old value = 1.008979
	FUZZ s.mbond.DoubleTreshMin = 0.090879; // fuzzed, old value = 0.091698
	FUZZ s.mbond.DoubleTreshMax = 0.816988; // fuzzed, old value = 0.841328
	FUZZ s.mbond.MaxLen1 = 140.605355; // fuzzed, old value = 145.204510
	FUZZ s.mbond.MaxLen2 = 126.081890; // fuzzed, old value = 121.539774
	FUZZ s.mbond.MaxLen3 = 116.257936; // fuzzed, old value = 118.634278
	FUZZ s.mbond.MaxLen4 = 103.276888; // fuzzed, old value = 107.978864
	FUZZ s.mbond.MaxLen5 = 84.024710; // fuzzed, old value = 83.711625
	FUZZ s.mbond.MinLen1 = 87.222668; // fuzzed, old value = 86.113757
	FUZZ s.mbond.MinLen2 = 76.388542; // fuzzed, old value = 73.528694
	FUZZ s.mbond.mbe1 = 0.077345; // fuzzed, old value = 0.074992
	FUZZ s.mbond.mbe2 = 0.157385; // fuzzed, old value = 0.157399
	FUZZ s.mbond.mbe3 = 0.214606; // fuzzed, old value = 0.207621
	FUZZ s.mbond.mbe4 = 0.185543; // fuzzed, old value = 0.179698
	FUZZ s.mbond.mbe5 = 0.168543; // fuzzed, old value = 0.163430
	FUZZ s.mbond.mbe6 = 0.202272; // fuzzed, old value = 0.199903
	FUZZ s.mbond.mbe7 = 0.412995; // fuzzed, old value = 0.412779
	FUZZ s.mbond.mbe_def = 0.515722; // fuzzed, old value = 0.510249
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.308789; // fuzzed, old value = 0.308959
	FUZZ s.mbond.DoubleRightLengthTresh = 0.321999; // fuzzed, old value = 0.328139
	FUZZ s.mbond.TripleLeftLengthTresh = 0.272921; // fuzzed, old value = 0.266600
	FUZZ s.mbond.TripleRightLengthTresh = 0.233952; // fuzzed, old value = 0.237110
	FUZZ s.mbond.Case1LengthTresh = 98.863004; // fuzzed, old value = 97.412387
	FUZZ s.mbond.Case1Factor = 0.429443; // fuzzed, old value = 0.444853
	FUZZ s.mbond.Case2LengthTresh = 78.124940; // fuzzed, old value = 78.184234
	FUZZ s.mbond.Case2Factor = 0.671633; // fuzzed, old value = 0.658458
	FUZZ s.mbond.Case3Factor = 0.826064; // fuzzed, old value = 0.821403
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.087648; // fuzzed, old value = 0.086847
	FUZZ s.skeleton.BaseSmallErr = 0.133352; // fuzzed, old value = 0.139838
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.319682; // fuzzed, old value = 0.327652
	FUZZ s.skeleton.MediumBondLen = 85; // fuzzed, old value = 87
	FUZZ s.skeleton.MediumMul = 0.197680; // fuzzed, old value = 0.195770
	FUZZ s.skeleton.MediumSmallErr = 0.144513; // fuzzed, old value = 0.139379
	FUZZ s.skeleton.LongBondLen = 107; // fuzzed, old value = 105
	FUZZ s.skeleton.LongMul = 0.131548; // fuzzed, old value = 0.129561
	FUZZ s.skeleton.LongSmallErr = 0.051688; // fuzzed, old value = 0.052888
	FUZZ s.skeleton.BrokenRepairFactor = 3.048244; // fuzzed, old value = 3.208369
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.022935; // fuzzed, old value = 1.046059
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.658417; // fuzzed, old value = 2.557861
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.205399; // fuzzed, old value = 0.201264
	FUZZ s.skeleton.DissolveMinErr = 0.198586; // fuzzed, old value = 0.192701
	FUZZ s.skeleton.ConnectBlockS = 10.145591; // fuzzed, old value = 9.764267
	FUZZ s.skeleton.ConnectFactor = 2.111493; // fuzzed, old value = 2.012180
	FUZZ s.skeleton.JoinVerticiesConst = 0.095304; // fuzzed, old value = 0.094646
	FUZZ s.skeleton.DissolveConst = 0.104756; // fuzzed, old value = 0.101654
	FUZZ s.skeleton.Dissolve2Const = 0.223811; // fuzzed, old value = 0.216204
	FUZZ s.skeleton.Join2Const = 0.317823; // fuzzed, old value = 0.333901
	FUZZ s.skeleton.Join3Const = 0.196230; // fuzzed, old value = 0.198315
	FUZZ s.skeleton.DistTreshLimFactor = 1.831998; // fuzzed, old value = 1.787764
	FUZZ s.skeleton.SlopeFact1 = 0.104403; // fuzzed, old value = 0.105327
	FUZZ s.skeleton.SlopeFact2 = 0.183896; // fuzzed, old value = 0.188657
	FUZZ s.skeleton.ShrinkEps = 0.126680; // fuzzed, old value = 0.123481
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10

	FUZZ s.routines.Circle_GapRadiusMax = 1.368372; // fuzzed, old value = 1.332954
	FUZZ s.routines.Circle_GapAngleMax = 0.484947; // fuzzed, old value = 0.492134
	FUZZ s.routines.Circle_MinRadius = 10.176160; // fuzzed, old value = 10.299804
	FUZZ s.routines.Circle_MaxDeviation = 0.185635; // fuzzed, old value = 0.192373
	FUZZ s.routines.Circle_AsCharFactor = 1.359021; // fuzzed, old value = 1.410306

	FUZZ s.routines.Algebra_IntersectionEps = 0.010193; // fuzzed, old value = 0.010432
	FUZZ s.routines.Algebra_SameLineEps = 0.187373; // fuzzed, old value = 0.194358
	FUZZ s.routines.Approx_Eps1 = 1.120766; // fuzzed, old value = 1.115186
	FUZZ s.routines.Approx_Eps2 = 0.819278; // fuzzed, old value = 0.840292
	FUZZ s.routines.Approx_CalcLineTresh = 0.884778; // fuzzed, old value = 0.850519

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.832206; // fuzzed, old value = 2.705028
	FUZZ s.wbe.SingleDownAngleMax = 44.431518; // fuzzed, old value = 45.137292
	FUZZ s.wbe.SingleDownDistancesMax = 9.352060; // fuzzed, old value = 9.029203
	FUZZ s.wbe.SingleDownLengthMax = 44.174719; // fuzzed, old value = 43.696969
	FUZZ s.wbe.SingleUpRatioEps = 1.885791; // fuzzed, old value = 1.908091
	FUZZ s.wbe.SingleUpDefCoeff = 0.285135; // fuzzed, old value = 0.278302
	FUZZ s.wbe.SingleUpIncCoeff = 0.418439; // fuzzed, old value = 0.406486
	FUZZ s.wbe.SingleUpIncLengthTresh = 31.219043; // fuzzed, old value = 32.250473
	FUZZ s.wbe.SingleUpInterpolateEps = 0.065614; // fuzzed, old value = 0.068279
	FUZZ s.wbe.SingleUpMagicAddition = 0.215486; // fuzzed, old value = 0.215318
	FUZZ s.wbe.SingleUpS2Divisor = 1.833230; // fuzzed, old value = 1.762490
	FUZZ s.wbe.SingleUpMinATresh = 1.497937; // fuzzed, old value = 1.574485
	FUZZ s.wbe.SingleUpSquareRatio = 0.572764; // fuzzed, old value = 0.594876
	FUZZ s.wbe.SingleUpAngleTresh = 0.074065; // fuzzed, old value = 0.070980
	FUZZ s.wbe.SomeTresh = 0.105891; // fuzzed, old value = 0.110870
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = true; 
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 0.925665; // fuzzed, old value = 0.972401
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.211915; // fuzzed, old value = 1.183425
	FUZZ s.characters.WriteEasyFactor = 0.930271; // fuzzed, old value = 0.917198
	FUZZ s.characters.WriteVeryEasyFactor = 0.837149; // fuzzed, old value = 0.797809
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.002693; // fuzzed, old value = 2.997639
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.524383; // fuzzed, old value = 3.534799
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.091597; // fuzzed, old value = 0.093991
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.548007; // fuzzed, old value = 2.442262
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.470670; // fuzzed, old value = 3.444646
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.107730; // fuzzed, old value = 1.074821
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.311975; // fuzzed, old value = 0.317866
	FUZZ s.characters.X_Quality = 0.304860; // fuzzed, old value = 0.3
	FUZZ s.characters.MinEndpointsPossible = 4; // fuzzed, old value = 4

	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.461167; // fuzzed, old value = 0.451340
	FUZZ s.csr.DeleteBadTriangles = 2.022324; // fuzzed, old value = 1.957555
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.381780; // fuzzed, old value = 1.422244

	FUZZ s.graph.MinimalDistTresh = 2.062107; // fuzzed, old value = 2.039565
	FUZZ s.graph.RatioSub = 0.954126; // fuzzed, old value = 0.986657
	FUZZ s.graph.RatioTresh = 0.444466; // fuzzed, old value = 0.424717

	FUZZ s.utils.SlashLineDensity = 0.428089; // fuzzed, old value = 0.426660
	FUZZ s.utils.TestPlusDensity = 0.438090; // fuzzed, old value = 0.444915
	FUZZ s.utils.TestPlusSq = 0.428531; // fuzzed, old value = 0.419234
	FUZZ s.utils.TestMinusRatio = 0.348673; // fuzzed, old value = 0.347247
	FUZZ s.utils.TestMinusDensity = 0.560332; // fuzzed, old value = 0.555646
	FUZZ s.utils.TestMinusHeightFactor = 0.723829; // fuzzed, old value = 0.727853

	FUZZ s.separator.hu_1_1 = 0.194715; // fuzzed, old value = 0.187009
	FUZZ s.separator.hu_1_2 = 0.092764; // fuzzed, old value = 0.089999
	FUZZ s.separator.hu_0_1 = 0.225492; // fuzzed, old value = 0.227741
	FUZZ s.separator.hu_1_3 = 0.086390; // fuzzed, old value = 0.084149
	FUZZ s.separator.hu_0_2 = 0.273418; // fuzzed, old value = 0.266166
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.601507; // fuzzed, old value = 0.581250
	FUZZ s.separator.capHeightMax = 1.371102; // fuzzed, old value = 1.358266
	FUZZ s.separator.gdConst = 1.491571; // fuzzed, old value = 1.517767
	FUZZ s.separator.SurfCoef = 2.695497; // fuzzed, old value = 2.593501
	FUZZ s.separator.capHeightRatio = 0.235583; // fuzzed, old value = 0.238682
	FUZZ s.separator.capHeightRatio2 = 1.966698; // fuzzed, old value = 1.964489
	FUZZ s.separator.getRatio1 = 1.003662; // fuzzed, old value = 0.995006
	FUZZ s.separator.getRatio2 = 1.128323; // fuzzed, old value = 1.104071
	FUZZ s.separator.testSlashLine1 = 3.139495; // fuzzed, old value = 3.246238
	FUZZ s.separator.testSlashLine2 = 3.177226; // fuzzed, old value = 3.031578
	FUZZ s.separator.minDensity = 0.202549; // fuzzed, old value = 0.204102
	FUZZ s.separator.maxDensity = 0.837619; // fuzzed, old value = 0.806080
	FUZZ s.separator.extCapHeightMin = 0.302217; // fuzzed, old value = 0.306478
	FUZZ s.separator.extCapHeightMax = 1.999441; // fuzzed, old value = 2.095513
	FUZZ s.separator.extRatioMin = 0.264339; // fuzzed, old value = 0.274874
	FUZZ s.separator.extRatioMax = 1.598967; // fuzzed, old value = 1.540172
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = true; // fuzzed, old value = true

	FUZZ s.labels.underlinePos = 0.463452; // fuzzed, old value = 0.476853
	FUZZ s.labels.weightUnderline = 0.290911; // fuzzed, old value = 0.286072
	FUZZ s.labels.ratioBase = 0.852040; // fuzzed, old value = 0.820609
	FUZZ s.labels.ratioWeight = 0.314247; // fuzzed, old value = 0.302920
	FUZZ s.labels.adjustDec = 1.277651; // fuzzed, old value = 1.274235
	FUZZ s.labels.adjustInc = 0.884117; // fuzzed, old value = 0.873424
	FUZZ s.labels.sameLineEps = 0.146561; // fuzzed, old value = 0.141207
	FUZZ s.labels.heightRatio = 0.902970; // fuzzed, old value = 0.871707
	FUZZ s.labels.medHeightFactor = 0.432182; // fuzzed, old value = 0.453486
	FUZZ s.labels.capHeightError = 0.528436; // fuzzed, old value = 0.522767

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.912561; // fuzzed, old value = 2.820964
	FUZZ s.lcomb.MaximalDistanceFactor = 0.684824; // fuzzed, old value = 0.710885
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.280102; // fuzzed, old value = 0.282795
	FUZZ s.lcomb.FillLabelFactor1 = 0.489570; // fuzzed, old value = 0.500139
	FUZZ s.lcomb.FillLabelFactor2 = 0.508650; // fuzzed, old value = 0.525941

	FUZZ s.p_estimator.DefaultApriority = 0.490433; // fuzzed, old value = 0.488702
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.703882; // fuzzed, old value = 0.736039
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.233887; // fuzzed, old value = 0.242319
	FUZZ s.p_estimator.LogisticScale = 1.030785; // fuzzed, old value = 1.003589
	FUZZ s.p_estimator.LogisticLocation = 0.869620; // fuzzed, old value = 0.910447
}

