
void updateSettingsScanned(Settings &s)
{
	s.general.UseProbablistics = false;
	s.p_estimator.UsePerimeterNormalization = true; 

	FUZZ s.separator.ext2charRatio = 1.805172; // fuzzed, old value = 1.742155
	FUZZ s.separator.SymProbabilityThresh = 0.56;

	FUZZ s.molecule.LengthFactor_long = 0.345425; // fuzzed, old value = 0.344624
	FUZZ s.molecule.LengthFactor_medium = 0.404470; // fuzzed, old value = 0.386117
	FUZZ s.molecule.LengthFactor_default = 0.474696; // fuzzed, old value = 0.492993
	FUZZ s.molecule.LengthValue_long = 110.810921; // fuzzed, old value = 114.480249
	FUZZ s.molecule.LengthValue_medium = 89.450280; // fuzzed, old value = 86.240000
	FUZZ s.molecule.SpaceMultiply = 1.370527; // fuzzed, old value = 1.353617
	FUZZ s.molecule.AngleTreshold = 0.256855; // fuzzed, old value = 0.262638
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.553142; // fuzzed, old value = 16.105494
	FUZZ s.estimation.LineThickness = 6.943756; // fuzzed, old value = 7.097181
	FUZZ s.estimation.AvgBondLength = 31.017772; // fuzzed, old value = 31.265909
	FUZZ s.estimation.AddVertexEps = 4.999934; // fuzzed, old value = 4.832264
	FUZZ s.estimation.MaxSymRatio = 1.135008; // fuzzed, old value = 1.175345
	FUZZ s.estimation.MinSymRatio = 0.302848; // fuzzed, old value = 0.297977
	FUZZ s.estimation.ParLinesEps = 0.581103; // fuzzed, old value = 0.568211
	FUZZ s.estimation.SymHeightErr = 27.732812; // fuzzed, old value = 27.430149
	FUZZ s.estimation.CapitalHeightError = 0.885080; // fuzzed, old value = 0.861994
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.381779; // fuzzed, old value = 0.375568
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.155142; // fuzzed, old value = 0.155019
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 102; // fuzzed, old value = 106
	FUZZ s.mbond.LongErr = 0.333770; // fuzzed, old value = 0.328943
	FUZZ s.mbond.MediumBond = 84; // fuzzed, old value = 85
	FUZZ s.mbond.MediumErr = 0.457432; // fuzzed, old value = 0.442535
	FUZZ s.mbond.DefaultErr = 0.657912; // fuzzed, old value = 0.687354
	FUZZ s.mbond.ParBondsEps = 0.337930; // fuzzed, old value = 0.343795
	FUZZ s.mbond.DoubleRatioTresh = 6.601718; // fuzzed, old value = 6.402333
	FUZZ s.mbond.DoubleCoef = 0.081201; // fuzzed, old value = 0.079862
	FUZZ s.mbond.DoubleMagic1 = 0.882326; // fuzzed, old value = 0.883346
	FUZZ s.mbond.DoubleMagic2 = 0.973134; // fuzzed, old value = 0.976231
	FUZZ s.mbond.DoubleTreshMin = 0.105704; // fuzzed, old value = 0.101932
	FUZZ s.mbond.DoubleTreshMax = 0.738936; // fuzzed, old value = 0.766627
	FUZZ s.mbond.MaxLen1 = 153.418088; // fuzzed, old value = 147.265580
	FUZZ s.mbond.MaxLen2 = 130.365677; // fuzzed, old value = 132.989383
	FUZZ s.mbond.MaxLen3 = 103.528817; // fuzzed, old value = 108.428743
	FUZZ s.mbond.MaxLen4 = 122.510428; // fuzzed, old value = 123.578307
	FUZZ s.mbond.MaxLen5 = 80.687697; // fuzzed, old value = 84.001804
	FUZZ s.mbond.MinLen1 = 90.497281; // fuzzed, old value = 91.550473
	FUZZ s.mbond.MinLen2 = 73.628036; // fuzzed, old value = 71.341397
	FUZZ s.mbond.mbe1 = 0.075109; // fuzzed, old value = 0.077643
	FUZZ s.mbond.mbe2 = 0.161531; // fuzzed, old value = 0.166717
	FUZZ s.mbond.mbe3 = 0.182512; // fuzzed, old value = 0.187070
	FUZZ s.mbond.mbe4 = 0.157249; // fuzzed, old value = 0.162072
	FUZZ s.mbond.mbe5 = 0.165944; // fuzzed, old value = 0.158707
	FUZZ s.mbond.mbe6 = 0.203663; // fuzzed, old value = 0.207614
	FUZZ s.mbond.mbe7 = 0.372383; // fuzzed, old value = 0.363834
	FUZZ s.mbond.mbe_def = 0.496090; // fuzzed, old value = 0.495533
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.372862; // fuzzed, old value = 0.355362
	FUZZ s.mbond.DoubleRightLengthTresh = 0.302374; // fuzzed, old value = 0.295869
	FUZZ s.mbond.TripleLeftLengthTresh = 0.255417; // fuzzed, old value = 0.249887
	FUZZ s.mbond.TripleRightLengthTresh = 0.227683; // fuzzed, old value = 0.225972
	FUZZ s.mbond.Case1LengthTresh = 89.891611; // fuzzed, old value = 88.064449
	FUZZ s.mbond.Case1Factor = 0.368014; // fuzzed, old value = 0.353378
	FUZZ s.mbond.Case2LengthTresh = 88.640922; // fuzzed, old value = 85.011703
	FUZZ s.mbond.Case2Factor = 0.708888; // fuzzed, old value = 0.732819
	FUZZ s.mbond.Case3Factor = 1.050544; // fuzzed, old value = 1.047378
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.112319; // fuzzed, old value = 0.108852
	FUZZ s.skeleton.BaseSmallErr = 0.150004; // fuzzed, old value = 0.151001
	FUZZ s.skeleton.ShortBondLen = 23; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.329297; // fuzzed, old value = 0.340273
	FUZZ s.skeleton.MediumBondLen = 90; // fuzzed, old value = 89
	FUZZ s.skeleton.MediumMul = 0.169881; // fuzzed, old value = 0.170042
	FUZZ s.skeleton.MediumSmallErr = 0.136375; // fuzzed, old value = 0.132406
	FUZZ s.skeleton.LongBondLen = 97; // fuzzed, old value = 101
	FUZZ s.skeleton.LongMul = 0.149354; // fuzzed, old value = 0.143678
	FUZZ s.skeleton.LongSmallErr = 0.060373; // fuzzed, old value = 0.060683
	FUZZ s.skeleton.BrokenRepairFactor = 3.493696; // fuzzed, old value = 3.532120
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.052535; // fuzzed, old value = 1.003219
	FUZZ s.skeleton.BrokenRepairCoef2 = 3.138162; // fuzzed, old value = 3.079568
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.197968; // fuzzed, old value = 0.202989
	FUZZ s.skeleton.DissolveMinErr = 0.185845; // fuzzed, old value = 0.183700
	FUZZ s.skeleton.ConnectBlockS = 10.027128; // fuzzed, old value = 9.744534
	FUZZ s.skeleton.ConnectFactor = 2.187095; // fuzzed, old value = 2.140950
	FUZZ s.skeleton.JoinVerticiesConst = 0.106399; // fuzzed, old value = 0.107713
	FUZZ s.skeleton.DissolveConst = 0.093640; // fuzzed, old value = 0.096054
	FUZZ s.skeleton.Dissolve2Const = 0.179050; // fuzzed, old value = 0.187753
	FUZZ s.skeleton.Join2Const = 0.246172; // fuzzed, old value = 0.257731
	FUZZ s.skeleton.Join3Const = 0.180037; // fuzzed, old value = 0.177588
	FUZZ s.skeleton.DistTreshLimFactor = 1.987990; // fuzzed, old value = 2.053120
	FUZZ s.skeleton.SlopeFact1 = 0.090321; // fuzzed, old value = 0.089961
	FUZZ s.skeleton.SlopeFact2 = 0.162888; // fuzzed, old value = 0.166530
	FUZZ s.skeleton.ShrinkEps = 0.140918; // fuzzed, old value = 0.137446
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	
	FUZZ s.routines.Circle_GapRadiusMax = 1.068727; // fuzzed, old value = 1.044786
	FUZZ s.routines.Circle_GapAngleMax = 0.210368; // fuzzed, old value = 0.201306
	FUZZ s.routines.Circle_MinRadius = 6.663209; // fuzzed, old value = 6.944921
	FUZZ s.routines.Circle_MaxDeviation = 0.009640; // fuzzed, old value = 0.010031
	FUZZ s.routines.Circle_AsCharFactor = 1.044749; // fuzzed, old value = 1.033971
	FUZZ s.routines.Algebra_IntersectionEps = 0.011934; // fuzzed, old value = 0.012137
	FUZZ s.routines.Algebra_SameLineEps = 0.228245; // fuzzed, old value = 0.227958
	FUZZ s.routines.Approx_Eps1 = 1.086365; // fuzzed, old value = 1.097663
	FUZZ s.routines.Approx_Eps2 = 0.863947; // fuzzed, old value = 0.871666
	FUZZ s.routines.Approx_CalcLineTresh = 0.833776; // fuzzed, old value = 0.874333
	FUZZ s.routines.Contour_Eps1 = 0.967737; // fuzzed, old value = 0.953948
	FUZZ s.routines.Contour_Eps2 = 0.664549; // fuzzed, old value = 0.670294

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.491594; // fuzzed, old value = 2.462165
	FUZZ s.wbe.SingleDownAngleMax = 40.973083; // fuzzed, old value = 42.468293
	FUZZ s.wbe.SingleDownDistancesMax = 10.308659; // fuzzed, old value = 9.941032
	FUZZ s.wbe.SingleDownLengthMax = 49.904925; // fuzzed, old value = 48.681970
	FUZZ s.wbe.SingleUpRatioEps = 1.538003; // fuzzed, old value = 1.528670
	FUZZ s.wbe.SingleUpDefCoeff = 0.280094; // fuzzed, old value = 0.280555
	FUZZ s.wbe.SingleUpIncCoeff = 0.470713; // fuzzed, old value = 0.494613
	FUZZ s.wbe.SingleUpIncLengthTresh = 37.082158; // fuzzed, old value = 35.506125
	FUZZ s.wbe.SingleUpInterpolateEps = 0.067357; // fuzzed, old value = 0.065428
	FUZZ s.wbe.SingleUpMagicAddition = 0.233279; // fuzzed, old value = 0.240283
	FUZZ s.wbe.SingleUpS2Divisor = 1.477468; // fuzzed, old value = 1.409862
	FUZZ s.wbe.SingleUpMinATresh = 1.622350; // fuzzed, old value = 1.639555
	FUZZ s.wbe.SingleUpSquareRatio = 0.631715; // fuzzed, old value = 0.653451
	FUZZ s.wbe.SingleUpAngleTresh = 0.071741; // fuzzed, old value = 0.070474
	FUZZ s.wbe.SomeTresh = 0.104236; // fuzzed, old value = 0.104280
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = false;
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.024380; // fuzzed, old value = 1.030590
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.128651; // fuzzed, old value = 1.131536
	FUZZ s.characters.WriteEasyFactor = 1.021107; // fuzzed, old value = 0.989743
	FUZZ s.characters.WriteVeryEasyFactor = 1.009046; // fuzzed, old value = 0.983122
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.096650; // fuzzed, old value = 3.229339
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.039395; // fuzzed, old value = 2.958949
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.095338; // fuzzed, old value = 0.096888
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.539117; // fuzzed, old value = 2.419803
	FUZZ s.characters.DescriptorsEvenFactorStrong = 4.094864; // fuzzed, old value = 3.959577
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.030703; // fuzzed, old value = 1.007367
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.289909; // fuzzed, old value = 0.284848
	
	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.543054; // fuzzed, old value = 0.531277
	FUZZ s.csr.DeleteBadTriangles = 2.047202; // fuzzed, old value = 2.098911
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.668864; // fuzzed, old value = 1.694837

	FUZZ s.graph.MinimalDistTresh = 2.087633; // fuzzed, old value = 1.993768
	FUZZ s.graph.RatioSub = 0.933951; // fuzzed, old value = 0.949086
	FUZZ s.graph.RatioTresh = 0.503967; // fuzzed, old value = 0.495952

	FUZZ s.utils.SlashLineDensity = 0.379186; // fuzzed, old value = 0.381467
	FUZZ s.utils.TestPlusDensity = 0.446697; // fuzzed, old value = 0.456717
	FUZZ s.utils.TestPlusSq = 0.465995; // fuzzed, old value = 0.464823
	FUZZ s.utils.TestMinusRatio = 0.312516; // fuzzed, old value = 0.325179
	FUZZ s.utils.TestMinusDensity = 0.562346; // fuzzed, old value = 0.589037
	FUZZ s.utils.TestMinusHeightFactor = 0.845162; // fuzzed, old value = 0.827681

	FUZZ s.separator.hu_1_1 = 0.226258; // fuzzed, old value = 0.234521
	FUZZ s.separator.hu_1_2 = 0.089869; // fuzzed, old value = 0.089845
	FUZZ s.separator.hu_0_1 = 0.191728; // fuzzed, old value = 0.200003
	FUZZ s.separator.hu_1_3 = 0.091566; // fuzzed, old value = 0.087509
	FUZZ s.separator.hu_0_2 = 0.218593; // fuzzed, old value = 0.224749
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.518936; // fuzzed, old value = 0.523622
	FUZZ s.separator.capHeightMax = 1.579394; // fuzzed, old value = 1.548634
	FUZZ s.separator.gdConst = 1.510097; // fuzzed, old value = 1.491240
	FUZZ s.separator.SurfCoef = 3.259183; // fuzzed, old value = 3.190322
	FUZZ s.separator.capHeightRatio = 0.297791; // fuzzed, old value = 0.295411
	FUZZ s.separator.capHeightRatio2 = 1.891563; // fuzzed, old value = 1.830517
	FUZZ s.separator.getRatio1 = 1.047529; // fuzzed, old value = 1.069270
	FUZZ s.separator.getRatio2 = 1.267302; // fuzzed, old value = 1.273476
	FUZZ s.separator.testSlashLine1 = 2.895111; // fuzzed, old value = 2.977843
	FUZZ s.separator.testSlashLine2 = 2.540979; // fuzzed, old value = 2.647196
	FUZZ s.separator.minDensity = 0.200926; // fuzzed, old value = 0.196577
	FUZZ s.separator.maxDensity = 0.942821; // fuzzed, old value = 0.977675
	FUZZ s.separator.extCapHeightMin = 0.280090; // fuzzed, old value = 0.283825
	FUZZ s.separator.extCapHeightMax = 2.121082; // fuzzed, old value = 2.092577
	FUZZ s.separator.extRatioMin = 0.318446; // fuzzed, old value = 0.326517
	FUZZ s.separator.extRatioMax = 1.545460; // fuzzed, old value = 1.485990
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = false; // fuzzed, old value = false

	FUZZ s.labels.underlinePos = 0.371780; // fuzzed, old value = 0.389237
	FUZZ s.labels.weightUnderline = 0.280021; // fuzzed, old value = 0.272559
	FUZZ s.labels.ratioBase = 0.698628; // fuzzed, old value = 0.715247
	FUZZ s.labels.ratioWeight = 0.291219; // fuzzed, old value = 0.288095
	FUZZ s.labels.adjustDec = 1.264434; // fuzzed, old value = 1.302751
	FUZZ s.labels.adjustInc = 0.780241; // fuzzed, old value = 0.758101
	FUZZ s.labels.sameLineEps = 0.109436; // fuzzed, old value = 0.107450
	FUZZ s.labels.heightRatio = 0.693774; // fuzzed, old value = 0.715752
	FUZZ s.labels.medHeightFactor = 0.524710; // fuzzed, old value = 0.541564
	FUZZ s.labels.capHeightError = 0.483663; // fuzzed, old value = 0.464990

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.822539; // fuzzed, old value = 2.857196
	FUZZ s.lcomb.MaximalDistanceFactor = 0.617346; // fuzzed, old value = 0.620323
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.230155; // fuzzed, old value = 0.238143
	FUZZ s.lcomb.FillLabelFactor1 = 0.471232; // fuzzed, old value = 0.476509
	FUZZ s.lcomb.FillLabelFactor2 = 0.588245; // fuzzed, old value = 0.579601

	FUZZ s.p_estimator.DefaultApriority = 0.502855; // fuzzed, old value = 0.502623
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.799481; // fuzzed, old value = 0.822343
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.248840; // fuzzed, old value = 0.257831
	FUZZ s.p_estimator.LogisticScale = 1.017224; // fuzzed, old value = 0.985688
	FUZZ s.p_estimator.LogisticLocation = 1.066357; // fuzzed, old value = 1.031057
}
