
void updateSettingsHandwritten(Settings &s)
{
	s.general.UseProbablistics = false; 
	s.p_estimator.UsePerimeterNormalization = true;

	FUZZ s.separator.ext2charRatio = 1.145039; // fuzzed, old value = 1.200453
	FUZZ s.separator.SymProbabilityThresh = 0.558107; // fuzzed, old value = 0.56

	FUZZ s.molecule.LengthFactor_long = 0.311065; // fuzzed, old value = 0.305116
	FUZZ s.molecule.LengthFactor_medium = 0.423739; // fuzzed, old value = 0.427121
	FUZZ s.molecule.LengthFactor_default = 0.465946; // fuzzed, old value = 0.458580
	FUZZ s.molecule.LengthValue_long = 98.866303; // fuzzed, old value = 101.633487
	FUZZ s.molecule.LengthValue_medium = 86.564870; // fuzzed, old value = 86.122914
	FUZZ s.molecule.SpaceMultiply = 1.512232; // fuzzed, old value = 1.534797
	FUZZ s.molecule.AngleTreshold = 0.258339; // fuzzed, old value = 0.256054
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 14.683100; // fuzzed, old value = 14.631192
	FUZZ s.estimation.LineThickness = 5.696794; // fuzzed, old value = 5.527422
	FUZZ s.estimation.AvgBondLength = 32.415802; // fuzzed, old value = 33.744115
	FUZZ s.estimation.AddVertexEps = 4.597025; // fuzzed, old value = 4.546128
	FUZZ s.estimation.MaxSymRatio = 0.979026; // fuzzed, old value = 1.014766
	FUZZ s.estimation.MinSymRatio = 0.308291; // fuzzed, old value = 0.321972
	FUZZ s.estimation.ParLinesEps = 0.516294; // fuzzed, old value = 0.537234
	FUZZ s.estimation.SymHeightErr = 28.050962; // fuzzed, old value = 27.261051
	FUZZ s.estimation.CapitalHeightError = 0.805329; // fuzzed, old value = 0.831200
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.492413; // fuzzed, old value = 0.514439
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.185056; // fuzzed, old value = 0.193722
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 116; // fuzzed, old value = 117
	FUZZ s.mbond.LongErr = 0.344449; // fuzzed, old value = 0.360928
	FUZZ s.mbond.MediumBond = 86; // fuzzed, old value = 88
	FUZZ s.mbond.MediumErr = 0.414826; // fuzzed, old value = 0.406320
	FUZZ s.mbond.DefaultErr = 0.584171; // fuzzed, old value = 0.612367
	FUZZ s.mbond.ParBondsEps = 0.327357; // fuzzed, old value = 0.324497
	FUZZ s.mbond.DoubleRatioTresh = 7.170715; // fuzzed, old value = 7.326664
	FUZZ s.mbond.DoubleCoef = 0.084524; // fuzzed, old value = 0.082313
	FUZZ s.mbond.DoubleMagic1 = 0.889154; // fuzzed, old value = 0.911915
	FUZZ s.mbond.DoubleMagic2 = 0.964768; // fuzzed, old value = 0.960738
	FUZZ s.mbond.DoubleTreshMin = 0.095824; // fuzzed, old value = 0.096688
	FUZZ s.mbond.DoubleTreshMax = 0.870871; // fuzzed, old value = 0.896816
	FUZZ s.mbond.MaxLen1 = 150.466442; // fuzzed, old value = 155.388150
	FUZZ s.mbond.MaxLen2 = 129.645746; // fuzzed, old value = 124.975241
	FUZZ s.mbond.MaxLen3 = 115.642728; // fuzzed, old value = 118.006495
	FUZZ s.mbond.MaxLen4 = 106.532853; // fuzzed, old value = 111.383066
	FUZZ s.mbond.MaxLen5 = 87.911983; // fuzzed, old value = 87.584413
	FUZZ s.mbond.MinLen1 = 83.061368; // fuzzed, old value = 82.005362
	FUZZ s.mbond.MinLen2 = 79.038515; // fuzzed, old value = 76.079457
	FUZZ s.mbond.mbe1 = 0.080006; // fuzzed, old value = 0.077572
	FUZZ s.mbond.mbe2 = 0.146232; // fuzzed, old value = 0.146245
	FUZZ s.mbond.mbe3 = 0.209492; // fuzzed, old value = 0.202673
	FUZZ s.mbond.mbe4 = 0.190066; // fuzzed, old value = 0.184078
	FUZZ s.mbond.mbe5 = 0.163248; // fuzzed, old value = 0.158296
	FUZZ s.mbond.mbe6 = 0.211034; // fuzzed, old value = 0.208563
	FUZZ s.mbond.mbe7 = 0.386518; // fuzzed, old value = 0.386316
	FUZZ s.mbond.mbe_def = 0.505787; // fuzzed, old value = 0.500420
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.314939; // fuzzed, old value = 0.315113
	FUZZ s.mbond.DoubleRightLengthTresh = 0.310681; // fuzzed, old value = 0.316605
	FUZZ s.mbond.TripleLeftLengthTresh = 0.271571; // fuzzed, old value = 0.265281
	FUZZ s.mbond.TripleRightLengthTresh = 0.232747; // fuzzed, old value = 0.235888
	FUZZ s.mbond.Case1LengthTresh = 105.324501; // fuzzed, old value = 103.779074
	FUZZ s.mbond.Case1Factor = 0.464696; // fuzzed, old value = 0.481371
	FUZZ s.mbond.Case2LengthTresh = 81.244888; // fuzzed, old value = 81.306550
	FUZZ s.mbond.Case2Factor = 0.671406; // fuzzed, old value = 0.658235
	FUZZ s.mbond.Case3Factor = 0.849037; // fuzzed, old value = 0.844246
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.083855; // fuzzed, old value = 0.083089
	FUZZ s.skeleton.BaseSmallErr = 0.134004; // fuzzed, old value = 0.140521
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.322882; // fuzzed, old value = 0.330932
	FUZZ s.skeleton.MediumBondLen = 81; // fuzzed, old value = 83
	FUZZ s.skeleton.MediumMul = 0.201625; // fuzzed, old value = 0.199677
	FUZZ s.skeleton.MediumSmallErr = 0.144294; // fuzzed, old value = 0.139167
	FUZZ s.skeleton.LongBondLen = 100; // fuzzed, old value = 98
	FUZZ s.skeleton.LongMul = 0.130718; // fuzzed, old value = 0.128743
	FUZZ s.skeleton.LongSmallErr = 0.055342; // fuzzed, old value = 0.056627
	FUZZ s.skeleton.BrokenRepairFactor = 2.858068; // fuzzed, old value = 3.008203
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.992760; // fuzzed, old value = 1.015202
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.666946; // fuzzed, old value = 2.566068
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.192617; // fuzzed, old value = 0.188739
	FUZZ s.skeleton.DissolveMinErr = 0.184358; // fuzzed, old value = 0.178895
	FUZZ s.skeleton.ConnectBlockS = 10.894238; // fuzzed, old value = 10.484776
	FUZZ s.skeleton.ConnectFactor = 1.991390; // fuzzed, old value = 1.897726
	FUZZ s.skeleton.JoinVerticiesConst = 0.100059; // fuzzed, old value = 0.099369
	FUZZ s.skeleton.DissolveConst = 0.102470; // fuzzed, old value = 0.099436
	FUZZ s.skeleton.Dissolve2Const = 0.207920; // fuzzed, old value = 0.200853
	FUZZ s.skeleton.Join2Const = 0.312006; // fuzzed, old value = 0.327789
	FUZZ s.skeleton.Join3Const = 0.212954; // fuzzed, old value = 0.215216
	FUZZ s.skeleton.DistTreshLimFactor = 1.773370; // fuzzed, old value = 1.730551
	FUZZ s.skeleton.SlopeFact1 = 0.106010; // fuzzed, old value = 0.106948
	FUZZ s.skeleton.SlopeFact2 = 0.180003; // fuzzed, old value = 0.184663
	FUZZ s.skeleton.ShrinkEps = 0.117147; // fuzzed, old value = 0.114189
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10

	FUZZ s.routines.Circle_GapRadiusMax = 1.313637; // fuzzed, old value = 1.279636
	FUZZ s.routines.Circle_GapAngleMax = 0.484947; // fuzzed, old value = 0.492134
	FUZZ s.routines.Circle_MinRadius = 5.088080; // fuzzed, old value = 5.149902
	FUZZ s.routines.Circle_MaxDeviation = 0.185635; // fuzzed, old value = 0.192373
	FUZZ s.routines.Circle_AsCharFactor = 1.359021; // fuzzed, old value = 1.410306

	FUZZ s.routines.Algebra_IntersectionEps = 0.010594; // fuzzed, old value = 0.010843
	FUZZ s.routines.Algebra_SameLineEps = 0.192007; // fuzzed, old value = 0.199164
	FUZZ s.routines.Approx_Eps1 = 1.073949; // fuzzed, old value = 1.068602
	FUZZ s.routines.Approx_Eps2 = 0.830558; // fuzzed, old value = 0.851862
	FUZZ s.routines.Approx_CalcLineTresh = 0.895617; // fuzzed, old value = 0.860939

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.947592; // fuzzed, old value = 2.815233
	FUZZ s.wbe.SingleDownAngleMax = 44.455701; // fuzzed, old value = 45.161859
	FUZZ s.wbe.SingleDownDistancesMax = 9.783616; // fuzzed, old value = 9.445860
	FUZZ s.wbe.SingleDownLengthMax = 38.691738; // fuzzed, old value = 38.273286
	FUZZ s.wbe.SingleUpRatioEps = 1.938799; // fuzzed, old value = 1.961726
	FUZZ s.wbe.SingleUpDefCoeff = 0.275925; // fuzzed, old value = 0.269312
	FUZZ s.wbe.SingleUpIncCoeff = 0.446309; // fuzzed, old value = 0.433560
	FUZZ s.wbe.SingleUpIncLengthTresh = 35.228613; // fuzzed, old value = 36.392514
	FUZZ s.wbe.SingleUpInterpolateEps = 0.059978; // fuzzed, old value = 0.062414
	FUZZ s.wbe.SingleUpMagicAddition = 0.209588; // fuzzed, old value = 0.209425
	FUZZ s.wbe.SingleUpS2Divisor = 1.987226; // fuzzed, old value = 1.910544
	FUZZ s.wbe.SingleUpMinATresh = 1.628164; // fuzzed, old value = 1.711366
	FUZZ s.wbe.SingleUpSquareRatio = 0.539789; // fuzzed, old value = 0.560628
	FUZZ s.wbe.SingleUpAngleTresh = 0.075180; // fuzzed, old value = 0.072049
	FUZZ s.wbe.SomeTresh = 0.098701; // fuzzed, old value = 0.103342
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = true;
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 0.967115; // fuzzed, old value = 1.015943
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.207520; // fuzzed, old value = 1.179133
	FUZZ s.characters.WriteEasyFactor = 0.932058; // fuzzed, old value = 0.918959
	FUZZ s.characters.WriteVeryEasyFactor = 0.806775; // fuzzed, old value = 0.768862
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 2.977529; // fuzzed, old value = 2.972517
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.444196; // fuzzed, old value = 3.454375
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.081406; // fuzzed, old value = 0.083534
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.512214; // fuzzed, old value = 2.407954
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.812223; // fuzzed, old value = 3.783638
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.984410; // fuzzed, old value = 0.955165
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.307869; // fuzzed, old value = 0.313682
	FUZZ s.characters.X_Quality = 0.304860; // fuzzed, old value = 0.3
	FUZZ s.characters.MinEndpointsPossible = 4; // fuzzed, old value = 4

	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.485182; // fuzzed, old value = 0.474843
	FUZZ s.csr.DeleteBadTriangles = 2.333846; // fuzzed, old value = 2.259100
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.396952; // fuzzed, old value = 1.437860

	FUZZ s.graph.MinimalDistTresh = 1.753460; // fuzzed, old value = 1.734292
	FUZZ s.graph.RatioSub = 1.005817; // fuzzed, old value = 1.040110
	FUZZ s.graph.RatioTresh = 0.420676; // fuzzed, old value = 0.401984

	FUZZ s.utils.SlashLineDensity = 0.460733; // fuzzed, old value = 0.459195
	FUZZ s.utils.TestPlusDensity = 0.406793; // fuzzed, old value = 0.413130
	FUZZ s.utils.TestPlusSq = 0.446117; // fuzzed, old value = 0.436438
	FUZZ s.utils.TestMinusRatio = 0.366697; // fuzzed, old value = 0.365197
	FUZZ s.utils.TestMinusDensity = 0.591798; // fuzzed, old value = 0.586849
	FUZZ s.utils.TestMinusHeightFactor = 0.757224; // fuzzed, old value = 0.761434

	FUZZ s.separator.hu_1_1 = 0.183111; // fuzzed, old value = 0.175864
	FUZZ s.separator.hu_1_2 = 0.085598; // fuzzed, old value = 0.083046
	FUZZ s.separator.hu_0_1 = 0.229785; // fuzzed, old value = 0.232077
	FUZZ s.separator.hu_1_3 = 0.096859; // fuzzed, old value = 0.094346
	FUZZ s.separator.hu_0_2 = 0.266760; // fuzzed, old value = 0.259685
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.568160; // fuzzed, old value = 0.549026
	FUZZ s.separator.capHeightMax = 1.355798; // fuzzed, old value = 1.343106
	FUZZ s.separator.gdConst = 1.410463; // fuzzed, old value = 1.435235
	FUZZ s.separator.SurfCoef = 2.677680; // fuzzed, old value = 2.576358
	FUZZ s.separator.capHeightRatio = 0.243400; // fuzzed, old value = 0.246602
	FUZZ s.separator.capHeightRatio2 = 1.861074; // fuzzed, old value = 1.858983
	FUZZ s.separator.getRatio1 = 0.910945; // fuzzed, old value = 0.903089
	FUZZ s.separator.getRatio2 = 1.104934; // fuzzed, old value = 1.081185
	FUZZ s.separator.testSlashLine1 = 3.194541; // fuzzed, old value = 3.303156
	FUZZ s.separator.testSlashLine2 = 3.125820; // fuzzed, old value = 2.982528
	FUZZ s.separator.minDensity = 0.209719; // fuzzed, old value = 0.211327
	FUZZ s.separator.maxDensity = 0.867058; // fuzzed, old value = 0.834411
	FUZZ s.separator.extCapHeightMin = 0.306581; // fuzzed, old value = 0.310903
	FUZZ s.separator.extCapHeightMax = 2.052730; // fuzzed, old value = 2.151362
	FUZZ s.separator.extRatioMin = 0.260506; // fuzzed, old value = 0.270888
	FUZZ s.separator.extRatioMax = 1.569421; // fuzzed, old value = 1.511713
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = true; // fuzzed, old value = true

	FUZZ s.labels.underlinePos = 0.446376; // fuzzed, old value = 0.459283
	FUZZ s.labels.weightUnderline = 0.305781; // fuzzed, old value = 0.300695
	FUZZ s.labels.ratioBase = 0.889445; // fuzzed, old value = 0.856634
	FUZZ s.labels.ratioWeight = 0.313236; // fuzzed, old value = 0.301945
	FUZZ s.labels.adjustDec = 1.328436; // fuzzed, old value = 1.324884
	FUZZ s.labels.adjustInc = 0.904405; // fuzzed, old value = 0.893467
	FUZZ s.labels.sameLineEps = 0.128242; // fuzzed, old value = 0.123557
	FUZZ s.labels.heightRatio = 0.864226; // fuzzed, old value = 0.834305
	FUZZ s.labels.medHeightFactor = 0.436038; // fuzzed, old value = 0.457532
	FUZZ s.labels.capHeightError = 0.496767; // fuzzed, old value = 0.491437

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.667453; // fuzzed, old value = 2.583564
	FUZZ s.lcomb.MaximalDistanceFactor = 0.684824; // fuzzed, old value = 0.710885
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.280102; // fuzzed, old value = 0.282795
	FUZZ s.lcomb.FillLabelFactor1 = 0.504584; // fuzzed, old value = 0.515477
	FUZZ s.lcomb.FillLabelFactor2 = 0.476767; // fuzzed, old value = 0.492974

	FUZZ s.p_estimator.DefaultApriority = 0.490433; // fuzzed, old value = 0.488702
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.703882; // fuzzed, old value = 0.736039
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.233887; // fuzzed, old value = 0.242319
	FUZZ s.p_estimator.LogisticScale = 1.030785; // fuzzed, old value = 1.003589
	FUZZ s.p_estimator.LogisticLocation = 0.869620; // fuzzed, old value = 0.910447
}

