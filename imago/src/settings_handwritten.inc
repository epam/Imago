
void updateSettingsHandwritten(Settings &s)
{
	s.general.UseProbablistics = false; 
	s.p_estimator.UsePerimeterNormalization = true;
	s.csr.StableDecorner = true;

	FUZZ s.separator.ext2charRatio = 1.200453; // fuzzed, old value = 1.228457
	FUZZ s.separator.SymProbabilityThresh = 0.56;

	FUZZ s.molecule.LengthFactor_long = 0.305116; // fuzzed, old value = 0.318252
	FUZZ s.molecule.LengthFactor_medium = 0.427121; // fuzzed, old value = 0.413917
	FUZZ s.molecule.LengthFactor_default = 0.458580; // fuzzed, old value = 0.471411
	FUZZ s.molecule.LengthValue_long = 101.633487; // fuzzed, old value = 103.912509
	FUZZ s.molecule.LengthValue_medium = 86.122914; // fuzzed, old value = 86.036397
	FUZZ s.molecule.SpaceMultiply = 1.534797; // fuzzed, old value = 1.537888
	FUZZ s.molecule.AngleTreshold = 0.256054; // fuzzed, old value = 0.252735
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 14.631192; // fuzzed, old value = 15.169151
	FUZZ s.estimation.LineThickness = 5.527422; // fuzzed, old value = 5.677534
	FUZZ s.estimation.AvgBondLength = 33.744115; // fuzzed, old value = 33.627685
	FUZZ s.estimation.AddVertexEps = 4.546128; // fuzzed, old value = 4.686013
	FUZZ s.estimation.MaxSymRatio = 1.014766; // fuzzed, old value = 1.047183
	FUZZ s.estimation.MinSymRatio = 0.321972; // fuzzed, old value = 0.315310
	FUZZ s.estimation.ParLinesEps = 0.537234; // fuzzed, old value = 0.520771
	FUZZ s.estimation.SymHeightErr = 27.261051; // fuzzed, old value = 26.968339
	FUZZ s.estimation.CapitalHeightError = 0.831200; // fuzzed, old value = 0.867297
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.514439; // fuzzed, old value = 0.518941
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.193722; // fuzzed, old value = 0.192857
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 117; // fuzzed, old value = 113
	FUZZ s.mbond.LongErr = 0.360928; // fuzzed, old value = 0.376113
	FUZZ s.mbond.MediumBond = 88; // fuzzed, old value = 91
	FUZZ s.mbond.MediumErr = 0.406320; // fuzzed, old value = 0.396442
	FUZZ s.mbond.DefaultErr = 0.612367; // fuzzed, old value = 0.636280
	FUZZ s.mbond.ParBondsEps = 0.324497; // fuzzed, old value = 0.320627
	FUZZ s.mbond.DoubleRatioTresh = 7.326664; // fuzzed, old value = 7.605677
	FUZZ s.mbond.DoubleCoef = 0.082313; // fuzzed, old value = 0.082399
	FUZZ s.mbond.DoubleMagic1 = 0.911915; // fuzzed, old value = 0.908335
	FUZZ s.mbond.DoubleMagic2 = 0.960738; // fuzzed, old value = 0.997451
	FUZZ s.mbond.DoubleTreshMin = 0.096688; // fuzzed, old value = 0.098354
	FUZZ s.mbond.DoubleTreshMax = 0.896816; // fuzzed, old value = 0.879415
	FUZZ s.mbond.MaxLen1 = 155.388150; // fuzzed, old value = 154.921735
	FUZZ s.mbond.MaxLen2 = 124.975241; // fuzzed, old value = 128.045368
	FUZZ s.mbond.MaxLen3 = 118.006495; // fuzzed, old value = 114.537037
	FUZZ s.mbond.MaxLen4 = 111.383066; // fuzzed, old value = 114.416588
	FUZZ s.mbond.MaxLen5 = 87.584413; // fuzzed, old value = 87.748438
	FUZZ s.mbond.MinLen1 = 82.005362; // fuzzed, old value = 82.429623
	FUZZ s.mbond.MinLen2 = 76.079457; // fuzzed, old value = 72.965395
	FUZZ s.mbond.mbe1 = 0.077572; // fuzzed, old value = 0.078724
	FUZZ s.mbond.mbe2 = 0.146245; // fuzzed, old value = 0.139495
	FUZZ s.mbond.mbe3 = 0.202673; // fuzzed, old value = 0.205260
	FUZZ s.mbond.mbe4 = 0.184078; // fuzzed, old value = 0.178341
	FUZZ s.mbond.mbe5 = 0.158296; // fuzzed, old value = 0.154538
	FUZZ s.mbond.mbe6 = 0.208563; // fuzzed, old value = 0.212197
	FUZZ s.mbond.mbe7 = 0.386316; // fuzzed, old value = 0.382867
	FUZZ s.mbond.mbe_def = 0.500420; // fuzzed, old value = 0.524099
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.315113; // fuzzed, old value = 0.313287
	FUZZ s.mbond.DoubleRightLengthTresh = 0.316605; // fuzzed, old value = 0.331798
	FUZZ s.mbond.TripleLeftLengthTresh = 0.265281; // fuzzed, old value = 0.277898
	FUZZ s.mbond.TripleRightLengthTresh = 0.235888; // fuzzed, old value = 0.231822
	FUZZ s.mbond.Case1LengthTresh = 103.779074; // fuzzed, old value = 105.443901
	FUZZ s.mbond.Case1Factor = 0.481371; // fuzzed, old value = 0.469945
	FUZZ s.mbond.Case2LengthTresh = 81.306550; // fuzzed, old value = 80.193117
	FUZZ s.mbond.Case2Factor = 0.658235; // fuzzed, old value = 0.675191
	FUZZ s.mbond.Case3Factor = 0.844246; // fuzzed, old value = 0.866118
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.083089; // fuzzed, old value = 0.086508
	FUZZ s.skeleton.BaseSmallErr = 0.140521; // fuzzed, old value = 0.141151
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.330932; // fuzzed, old value = 0.332156
	FUZZ s.skeleton.MediumBondLen = 83; // fuzzed, old value = 86
	FUZZ s.skeleton.MediumMul = 0.199677; // fuzzed, old value = 0.192742
	FUZZ s.skeleton.MediumSmallErr = 0.139167; // fuzzed, old value = 0.136981
	FUZZ s.skeleton.LongBondLen = 98; // fuzzed, old value = 100
	FUZZ s.skeleton.LongMul = 0.128743; // fuzzed, old value = 0.135336
	FUZZ s.skeleton.LongSmallErr = 0.056627; // fuzzed, old value = 0.059091
	FUZZ s.skeleton.BrokenRepairFactor = 3.008203; // fuzzed, old value = 3.034957
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.015202; // fuzzed, old value = 1.014748
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.566068; // fuzzed, old value = 2.592298
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.188739; // fuzzed, old value = 0.189301
	FUZZ s.skeleton.DissolveMinErr = 0.178895; // fuzzed, old value = 0.175746
	FUZZ s.skeleton.ConnectBlockS = 10.484776; // fuzzed, old value = 10.785240
	FUZZ s.skeleton.ConnectFactor = 1.897726; // fuzzed, old value = 1.942177
	FUZZ s.skeleton.JoinVerticiesConst = 0.099369; // fuzzed, old value = 0.104121
	FUZZ s.skeleton.DissolveConst = 0.099436; // fuzzed, old value = 0.098362
	FUZZ s.skeleton.Dissolve2Const = 0.200853; // fuzzed, old value = 0.194633
	FUZZ s.skeleton.Join2Const = 0.327789; // fuzzed, old value = 0.334515
	FUZZ s.skeleton.Join3Const = 0.215216; // fuzzed, old value = 0.214479
	FUZZ s.skeleton.DistTreshLimFactor = 1.730551; // fuzzed, old value = 1.767427
	FUZZ s.skeleton.SlopeFact1 = 0.106948; // fuzzed, old value = 0.105068
	FUZZ s.skeleton.SlopeFact2 = 0.184663; // fuzzed, old value = 0.177636
	FUZZ s.skeleton.ShrinkEps = 0.114189; // fuzzed, old value = 0.113700
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10

	FUZZ s.routines.Circle_GapRadiusMax = 1.279636; // fuzzed, old value = 1.238708
	FUZZ s.routines.Circle_GapAngleMax = 0.492134; // fuzzed, old value = 0.478777
	FUZZ s.routines.Circle_MinRadius = 5.149902; // fuzzed, old value = 4.912908
	FUZZ s.routines.Circle_MaxDeviation = 0.192373; // fuzzed, old value = 0.202378
	FUZZ s.routines.Circle_AsCharFactor = 1.410306; // fuzzed, old value = 1.454969

	FUZZ s.routines.Algebra_IntersectionEps = 0.010843; // fuzzed, old value = 0.010440
	FUZZ s.routines.Algebra_SameLineEps = 0.199164; // fuzzed, old value = 0.199966
	FUZZ s.routines.Approx_Eps1 = 1.068602; // fuzzed, old value = 1.122353
	FUZZ s.routines.Approx_Eps2 = 0.851862; // fuzzed, old value = 0.872298
	FUZZ s.routines.Approx_CalcLineTresh = 0.860939; // fuzzed, old value = 0.826057

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.815233; // fuzzed, old value = 2.765285
	FUZZ s.wbe.SingleDownAngleMax = 45.161859; // fuzzed, old value = 45.966879
	FUZZ s.wbe.SingleDownDistancesMax = 9.445860; // fuzzed, old value = 9.887962
	FUZZ s.wbe.SingleDownLengthMax = 38.273286; // fuzzed, old value = 37.614879
	FUZZ s.wbe.SingleUpRatioEps = 1.961726; // fuzzed, old value = 1.956981
	FUZZ s.wbe.SingleUpDefCoeff = 0.269312; // fuzzed, old value = 0.258282
	FUZZ s.wbe.SingleUpIncCoeff = 0.433560; // fuzzed, old value = 0.452763
	FUZZ s.wbe.SingleUpIncLengthTresh = 36.392514; // fuzzed, old value = 36.641491
	FUZZ s.wbe.SingleUpInterpolateEps = 0.062414; // fuzzed, old value = 0.060408
	FUZZ s.wbe.SingleUpMagicAddition = 0.209425; // fuzzed, old value = 0.218206
	FUZZ s.wbe.SingleUpS2Divisor = 1.910544; // fuzzed, old value = 1.856176
	FUZZ s.wbe.SingleUpMinATresh = 1.711366; // fuzzed, old value = 1.789007
	FUZZ s.wbe.SingleUpSquareRatio = 0.560628; // fuzzed, old value = 0.580176
	FUZZ s.wbe.SingleUpAngleTresh = 0.072049; // fuzzed, old value = 0.071043
	FUZZ s.wbe.SomeTresh = 0.103342; // fuzzed, old value = 0.099948
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = true;
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.015943; // fuzzed, old value = 1.042811
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.179133; // fuzzed, old value = 1.200793
	FUZZ s.characters.WriteEasyFactor = 0.918959; // fuzzed, old value = 0.966019
	FUZZ s.characters.WriteVeryEasyFactor = 0.768862; // fuzzed, old value = 0.768024
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 2.972517; // fuzzed, old value = 3.084192
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.454375; // fuzzed, old value = 3.385517
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.083534; // fuzzed, old value = 0.086253
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.407954; // fuzzed, old value = 2.310488
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.783638; // fuzzed, old value = 3.774555
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.955165; // fuzzed, old value = 0.935876
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.313682; // fuzzed, old value = 0.316648
	FUZZ s.characters.X_Quality = 0.3;
	FUZZ s.characters.MinEndpointsPossible = 4;

	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.474843; // fuzzed, old value = 0.478222
	FUZZ s.csr.DeleteBadTriangles = 2.259100; // fuzzed, old value = 2.172035
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.437860; // fuzzed, old value = 1.479794

	FUZZ s.graph.MinimalDistTresh = 1.734292; // fuzzed, old value = 1.821545
	FUZZ s.graph.RatioSub = 1.040110; // fuzzed, old value = 1.014226
	FUZZ s.graph.RatioTresh = 0.401984; // fuzzed, old value = 0.419309

	FUZZ s.utils.SlashLineDensity = 0.459195; // fuzzed, old value = 0.480276
	FUZZ s.utils.TestPlusDensity = 0.413130; // fuzzed, old value = 0.434167
	FUZZ s.utils.TestPlusSq = 0.436438; // fuzzed, old value = 0.429271
	FUZZ s.utils.TestMinusRatio = 0.365197; // fuzzed, old value = 0.375310
	FUZZ s.utils.TestMinusDensity = 0.586849; // fuzzed, old value = 0.598837
	FUZZ s.utils.TestMinusHeightFactor = 0.761434; // fuzzed, old value = 0.771482

	FUZZ s.separator.hu_1_1 = 0.175864; // fuzzed, old value = 0.182200
	FUZZ s.separator.hu_1_2 = 0.083046; // fuzzed, old value = 0.080232
	FUZZ s.separator.hu_0_1 = 0.232077; // fuzzed, old value = 0.243055
	FUZZ s.separator.hu_1_3 = 0.094346; // fuzzed, old value = 0.091750
	FUZZ s.separator.hu_0_2 = 0.259685; // fuzzed, old value = 0.260262
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.549026; // fuzzed, old value = 0.535419
	FUZZ s.separator.capHeightMax = 1.343106; // fuzzed, old value = 1.331047
	FUZZ s.separator.gdConst = 1.435235; // fuzzed, old value = 1.494774
	FUZZ s.separator.SurfCoef = 2.576358; // fuzzed, old value = 2.690169
	FUZZ s.separator.capHeightRatio = 0.246602; // fuzzed, old value = 0.248689
	FUZZ s.separator.capHeightRatio2 = 1.858983; // fuzzed, old value = 1.816786
	FUZZ s.separator.getRatio1 = 0.903089; // fuzzed, old value = 0.868547
	FUZZ s.separator.getRatio2 = 1.081185; // fuzzed, old value = 1.112853
	FUZZ s.separator.testSlashLine1 = 3.303156; // fuzzed, old value = 3.190627
	FUZZ s.separator.testSlashLine2 = 2.982528; // fuzzed, old value = 2.961420
	FUZZ s.separator.minDensity = 0.211327; // fuzzed, old value = 0.204792
	FUZZ s.separator.maxDensity = 0.834411; // fuzzed, old value = 0.835935
	FUZZ s.separator.extCapHeightMin = 0.310903; // fuzzed, old value = 0.298221
	FUZZ s.separator.extCapHeightMax = 2.151362; // fuzzed, old value = 2.078549
	FUZZ s.separator.extRatioMin = 0.270888; // fuzzed, old value = 0.280485
	FUZZ s.separator.extRatioMax = 1.511713; // fuzzed, old value = 1.448039
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = true; // fuzzed, old value = true

	FUZZ s.labels.underlinePos = 0.459283; // fuzzed, old value = 0.463312
	FUZZ s.labels.weightUnderline = 0.300695; // fuzzed, old value = 0.315862
	FUZZ s.labels.ratioBase = 0.856634; // fuzzed, old value = 0.862996
	FUZZ s.labels.ratioWeight = 0.301945; // fuzzed, old value = 0.293834
	FUZZ s.labels.adjustDec = 1.324884; // fuzzed, old value = 1.289963
	FUZZ s.labels.adjustInc = 0.893467; // fuzzed, old value = 0.859068
	FUZZ s.labels.sameLineEps = 0.123557; // fuzzed, old value = 0.118423
	FUZZ s.labels.heightRatio = 0.834305; // fuzzed, old value = 0.811731
	FUZZ s.labels.medHeightFactor = 0.457532; // fuzzed, old value = 0.467762
	FUZZ s.labels.capHeightError = 0.491437; // fuzzed, old value = 0.488753

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.583564; // fuzzed, old value = 2.662893
	FUZZ s.lcomb.MaximalDistanceFactor = 0.683355; // fuzzed, old value = 0.683355
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.282795; // fuzzed, old value = 0.290503
	FUZZ s.lcomb.FillLabelFactor1 = 0.515477; // fuzzed, old value = 0.523083
	FUZZ s.lcomb.FillLabelFactor2 = 0.492974; // fuzzed, old value = 0.474184

	FUZZ s.p_estimator.DefaultApriority = 0.488702; // fuzzed, old value = 0.497449
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.736039; // fuzzed, old value = 0.765935
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.242319; // fuzzed, old value = 0.245732
	FUZZ s.p_estimator.LogisticScale = 1.003589; // fuzzed, old value = 0.971043
	FUZZ s.p_estimator.LogisticLocation = 0.910447; // fuzzed, old value = 0.951224
}

