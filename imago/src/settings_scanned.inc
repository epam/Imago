
void updateSettingsScanned(Settings &s)
{
	s.general.UseProbablistics = false; 

	FUZZ s.separator.ext2charRatio = 1.742155; // fuzzed, old value = 1.767319

	FUZZ s.molecule.LengthFactor_long = 0.344624; // fuzzed, old value = 0.340889
	FUZZ s.molecule.LengthFactor_medium = 0.386117; // fuzzed, old value = 0.393316
	FUZZ s.molecule.LengthFactor_default = 0.492993; // fuzzed, old value = 0.477074
	FUZZ s.molecule.LengthValue_long = 114.480249; // fuzzed, old value = 111.357898
	FUZZ s.molecule.LengthValue_medium = 86.240000; // fuzzed, old value = 84.472918
	FUZZ s.molecule.SpaceMultiply = 1.353617; // fuzzed, old value = 1.375891
	FUZZ s.molecule.AngleTreshold = 0.262638; // fuzzed, old value = 0.261624
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.105494; // fuzzed, old value = 16.889670
	FUZZ s.estimation.LineThickness = 7.097181; // fuzzed, old value = 6.937200
	FUZZ s.estimation.AvgBondLength = 31.265909; // fuzzed, old value = 30.607329
	FUZZ s.estimation.AddVertexEps = 4.832264; // fuzzed, old value = 4.750233
	FUZZ s.estimation.MaxSymRatio = 1.175345; // fuzzed, old value = 1.210384
	FUZZ s.estimation.MinSymRatio = 0.297977; // fuzzed, old value = 0.299972
	FUZZ s.estimation.ParLinesEps = 0.568211; // fuzzed, old value = 0.565289
	FUZZ s.estimation.SymHeightErr = 27.430149; // fuzzed, old value = 27.576883
	FUZZ s.estimation.CapitalHeightError = 0.861994; // fuzzed, old value = 0.846774
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.375568; // fuzzed, old value = 0.373133
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.155019; // fuzzed, old value = 0.152958
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 106; // fuzzed, old value = 103
	FUZZ s.mbond.LongErr = 0.328943; // fuzzed, old value = 0.317139
	FUZZ s.mbond.MediumBond = 85; // fuzzed, old value = 83
	FUZZ s.mbond.MediumErr = 0.442535; // fuzzed, old value = 0.460874
	FUZZ s.mbond.DefaultErr = 0.687354; // fuzzed, old value = 0.678407
	FUZZ s.mbond.ParBondsEps = 0.343795; // fuzzed, old value = 0.356066
	FUZZ s.mbond.DoubleRatioTresh = 6.402333; // fuzzed, old value = 6.349077
	FUZZ s.mbond.DoubleCoef = 0.079862; // fuzzed, old value = 0.077616
	FUZZ s.mbond.DoubleMagic1 = 0.883346; // fuzzed, old value = 0.862940
	FUZZ s.mbond.DoubleMagic2 = 0.976231; // fuzzed, old value = 0.967086
	FUZZ s.mbond.DoubleTreshMin = 0.101932; // fuzzed, old value = 0.104527
	FUZZ s.mbond.DoubleTreshMax = 0.766627; // fuzzed, old value = 0.798826
	FUZZ s.mbond.MaxLen1 = 147.265580; // fuzzed, old value = 153.764202
	FUZZ s.mbond.MaxLen2 = 132.989383; // fuzzed, old value = 137.258959
	FUZZ s.mbond.MaxLen3 = 108.428743; // fuzzed, old value = 109.608049
	FUZZ s.mbond.MaxLen4 = 123.578307; // fuzzed, old value = 122.631261
	FUZZ s.mbond.MaxLen5 = 84.001804; // fuzzed, old value = 80.706855
	FUZZ s.mbond.MinLen1 = 91.550473; // fuzzed, old value = 87.642060
	FUZZ s.mbond.MinLen2 = 71.341397; // fuzzed, old value = 73.703987
	FUZZ s.mbond.mbe1 = 0.077643; // fuzzed, old value = 0.076706
	FUZZ s.mbond.mbe2 = 0.166717; // fuzzed, old value = 0.161620
	FUZZ s.mbond.mbe3 = 0.187070; // fuzzed, old value = 0.190503
	FUZZ s.mbond.mbe4 = 0.162072; // fuzzed, old value = 0.168650
	FUZZ s.mbond.mbe5 = 0.158707; // fuzzed, old value = 0.156199
	FUZZ s.mbond.mbe6 = 0.207614; // fuzzed, old value = 0.212919
	FUZZ s.mbond.mbe7 = 0.363834; // fuzzed, old value = 0.373622
	FUZZ s.mbond.mbe_def = 0.495533; // fuzzed, old value = 0.518862
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.355362; // fuzzed, old value = 0.350223
	FUZZ s.mbond.DoubleRightLengthTresh = 0.295869; // fuzzed, old value = 0.305265
	FUZZ s.mbond.TripleLeftLengthTresh = 0.249887; // fuzzed, old value = 0.243861
	FUZZ s.mbond.TripleRightLengthTresh = 0.225972; // fuzzed, old value = 0.227698
	FUZZ s.mbond.Case1LengthTresh = 88.064449; // fuzzed, old value = 91.532935
	FUZZ s.mbond.Case1Factor = 0.353378; // fuzzed, old value = 0.368663
	FUZZ s.mbond.Case2LengthTresh = 85.011703; // fuzzed, old value = 82.468096
	FUZZ s.mbond.Case2Factor = 0.732819; // fuzzed, old value = 0.701315
	FUZZ s.mbond.Case3Factor = 1.047378; // fuzzed, old value = 1.034542
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.108852; // fuzzed, old value = 0.106433
	FUZZ s.skeleton.BaseSmallErr = 0.151001; // fuzzed, old value = 0.154460
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 21
	FUZZ s.skeleton.ShortMul = 0.340273; // fuzzed, old value = 0.332122
	FUZZ s.skeleton.MediumBondLen = 89; // fuzzed, old value = 91
	FUZZ s.skeleton.MediumMul = 0.170042; // fuzzed, old value = 0.168570
	FUZZ s.skeleton.MediumSmallErr = 0.132406; // fuzzed, old value = 0.128446
	FUZZ s.skeleton.LongBondLen = 101; // fuzzed, old value = 100
	FUZZ s.skeleton.LongMul = 0.143678; // fuzzed, old value = 0.139225
	FUZZ s.skeleton.LongSmallErr = 0.060683; // fuzzed, old value = 0.062579
	FUZZ s.skeleton.BrokenRepairFactor = 3.532120; // fuzzed, old value = 3.367153
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.003219; // fuzzed, old value = 0.961410
	FUZZ s.skeleton.BrokenRepairCoef2 = 3.079568; // fuzzed, old value = 3.130242
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.202989; // fuzzed, old value = 0.207376
	FUZZ s.skeleton.DissolveMinErr = 0.183700; // fuzzed, old value = 0.177770
	FUZZ s.skeleton.ConnectBlockS = 9.744534; // fuzzed, old value = 9.387327
	FUZZ s.skeleton.ConnectFactor = 2.140950; // fuzzed, old value = 2.123681
	FUZZ s.skeleton.JoinVerticiesConst = 0.107713; // fuzzed, old value = 0.104686
	FUZZ s.skeleton.DissolveConst = 0.096054; // fuzzed, old value = 0.098735
	FUZZ s.skeleton.Dissolve2Const = 0.187753; // fuzzed, old value = 0.192749
	FUZZ s.skeleton.Join2Const = 0.257731; // fuzzed, old value = 0.266918
	FUZZ s.skeleton.Join3Const = 0.177588; // fuzzed, old value = 0.182588
	FUZZ s.skeleton.DistTreshLimFactor = 2.053120; // fuzzed, old value = 2.148678
	FUZZ s.skeleton.SlopeFact1 = 0.089961; // fuzzed, old value = 0.090052
	FUZZ s.skeleton.SlopeFact2 = 0.166530; // fuzzed, old value = 0.161803
	FUZZ s.skeleton.ShrinkEps = 0.137446; // fuzzed, old value = 0.138146
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	
	FUZZ s.routines.Circle_GapRadiusMax = 1.044786; // fuzzed, old value = 1.042189
	FUZZ s.routines.Circle_GapAngleMax = 0.201306; // fuzzed, old value = 0.207993
	FUZZ s.routines.Circle_MinRadius = 6.944921; // fuzzed, old value = 6.771566
	FUZZ s.routines.Circle_MaxDeviation = 0.010031; // fuzzed, old value = 0.010555
	FUZZ s.routines.Circle_AsCharFactor = 1.033971; // fuzzed, old value = 1.084621
	FUZZ s.routines.Algebra_IntersectionEps = 0.012137; // fuzzed, old value = 0.011577
	FUZZ s.routines.Algebra_SameLineEps = 0.227958; // fuzzed, old value = 0.229190
	FUZZ s.routines.Approx_Eps1 = 1.097663; // fuzzed, old value = 1.116990
	FUZZ s.routines.Approx_Eps2 = 0.871666; // fuzzed, old value = 0.850903
	FUZZ s.routines.Approx_CalcLineTresh = 0.874333; // fuzzed, old value = 0.898889
	FUZZ s.routines.Contour_Eps1 = 0.953948; // fuzzed, old value = 0.969275
	FUZZ s.routines.Contour_Eps2 = 0.670294; // fuzzed, old value = 0.669568

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.462165; // fuzzed, old value = 2.512641
	FUZZ s.wbe.SingleDownAngleMax = 42.468293; // fuzzed, old value = 43.474725
	FUZZ s.wbe.SingleDownDistancesMax = 9.941032; // fuzzed, old value = 10.081656
	FUZZ s.wbe.SingleDownLengthMax = 48.681970; // fuzzed, old value = 50.032921
	FUZZ s.wbe.SingleUpRatioEps = 1.528670; // fuzzed, old value = 1.568361
	FUZZ s.wbe.SingleUpDefCoeff = 0.280555; // fuzzed, old value = 0.276846
	FUZZ s.wbe.SingleUpIncCoeff = 0.494613; // fuzzed, old value = 0.484086
	FUZZ s.wbe.SingleUpIncLengthTresh = 35.506125; // fuzzed, old value = 35.298162
	FUZZ s.wbe.SingleUpInterpolateEps = 0.065428; // fuzzed, old value = 0.063635
	FUZZ s.wbe.SingleUpMagicAddition = 0.240283; // fuzzed, old value = 0.245117
	FUZZ s.wbe.SingleUpS2Divisor = 1.409862; // fuzzed, old value = 1.427349
	FUZZ s.wbe.SingleUpMinATresh = 1.639555; // fuzzed, old value = 1.704276
	FUZZ s.wbe.SingleUpSquareRatio = 0.653451; // fuzzed, old value = 0.631337
	FUZZ s.wbe.SingleUpAngleTresh = 0.070474; // fuzzed, old value = 0.069033
	FUZZ s.wbe.SomeTresh = 0.104280; // fuzzed, old value = 0.102061
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = false;
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.030590; // fuzzed, old value = 1.006098
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.131536; // fuzzed, old value = 1.077772
	FUZZ s.characters.WriteEasyFactor = 0.989743; // fuzzed, old value = 0.956053
	FUZZ s.characters.WriteVeryEasyFactor = 0.983122; // fuzzed, old value = 0.974528
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.229339; // fuzzed, old value = 3.169545
	FUZZ s.characters.PossibleCharacterDistanceWeak = 2.958949; // fuzzed, old value = 2.937536
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.096888; // fuzzed, old value = 0.097843
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.419803; // fuzzed, old value = 2.516186
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.959577; // fuzzed, old value = 3.802056
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.007367; // fuzzed, old value = 1.002519
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.284848; // fuzzed, old value = 0.284260
	
	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.531277; // fuzzed, old value = 0.524853
	FUZZ s.csr.DeleteBadTriangles = 2.098911; // fuzzed, old value = 2.030885
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.694837; // fuzzed, old value = 1.757086

	FUZZ s.graph.MinimalDistTresh = 1.993768; // fuzzed, old value = 1.988540
	FUZZ s.graph.RatioSub = 0.949086; // fuzzed, old value = 0.977444
	FUZZ s.graph.RatioTresh = 0.495952; // fuzzed, old value = 0.483066

	FUZZ s.utils.SlashLineDensity = 0.381467; // fuzzed, old value = 0.380602
	FUZZ s.utils.TestPlusDensity = 0.456717; // fuzzed, old value = 0.446602
	FUZZ s.utils.TestPlusSq = 0.464823; // fuzzed, old value = 0.444991
	FUZZ s.utils.TestMinusRatio = 0.325179; // fuzzed, old value = 0.323241
	FUZZ s.utils.TestMinusDensity = 0.589037; // fuzzed, old value = 0.612802
	FUZZ s.utils.TestMinusHeightFactor = 0.827681; // fuzzed, old value = 0.858695

	FUZZ s.separator.hu_1_1 = 0.234521; // fuzzed, old value = 0.225440
	FUZZ s.separator.hu_1_2 = 0.089845; // fuzzed, old value = 0.086412
	FUZZ s.separator.hu_0_1 = 0.200003; // fuzzed, old value = 0.208317
	FUZZ s.separator.hu_1_3 = 0.087509; // fuzzed, old value = 0.089391
	FUZZ s.separator.hu_0_2 = 0.224749; // fuzzed, old value = 0.219407
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.523622; // fuzzed, old value = 0.535304
	FUZZ s.separator.capHeightMax = 1.548634; // fuzzed, old value = 1.503544
	FUZZ s.separator.gdConst = 1.491240; // fuzzed, old value = 1.553112
	FUZZ s.separator.SurfCoef = 3.190322; // fuzzed, old value = 3.133748
	FUZZ s.separator.capHeightRatio = 0.295411; // fuzzed, old value = 0.285849
	FUZZ s.separator.capHeightRatio2 = 1.830517; // fuzzed, old value = 1.892839
	FUZZ s.separator.getRatio1 = 1.069270; // fuzzed, old value = 1.032438
	FUZZ s.separator.getRatio2 = 1.273476; // fuzzed, old value = 1.219021
	FUZZ s.separator.testSlashLine1 = 2.977843; // fuzzed, old value = 3.122285
	FUZZ s.separator.testSlashLine2 = 2.647196; // fuzzed, old value = 2.577383
	FUZZ s.separator.minDensity = 0.196577; // fuzzed, old value = 0.191005
	FUZZ s.separator.maxDensity = 0.977675; // fuzzed, old value = 0.944421
	FUZZ s.separator.extCapHeightMin = 0.283825; // fuzzed, old value = 0.285472
	FUZZ s.separator.extCapHeightMax = 2.092577; // fuzzed, old value = 2.105819
	FUZZ s.separator.extRatioMin = 0.326517; // fuzzed, old value = 0.329231
	FUZZ s.separator.extRatioMax = 1.485990; // fuzzed, old value = 1.516666
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = false; // fuzzed, old value = false

	FUZZ s.labels.underlinePos = 0.389237; // fuzzed, old value = 0.390269
	FUZZ s.labels.weightUnderline = 0.272559; // fuzzed, old value = 0.278459
	FUZZ s.labels.ratioBase = 0.715247; // fuzzed, old value = 0.731026
	FUZZ s.labels.ratioWeight = 0.288095; // fuzzed, old value = 0.283072
	FUZZ s.labels.adjustDec = 1.302751; // fuzzed, old value = 1.270792
	FUZZ s.labels.adjustInc = 0.758101; // fuzzed, old value = 0.791853
	FUZZ s.labels.sameLineEps = 0.107450; // fuzzed, old value = 0.112452
	FUZZ s.labels.heightRatio = 0.715752; // fuzzed, old value = 0.751725
	FUZZ s.labels.medHeightFactor = 0.541564; // fuzzed, old value = 0.534892
	FUZZ s.labels.capHeightError = 0.464990; // fuzzed, old value = 0.484007

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.857196; // fuzzed, old value = 2.750317
	FUZZ s.lcomb.MaximalDistanceFactor = 0.620323; // fuzzed, old value = 0.65
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.238143; // fuzzed, old value = 0.25
	FUZZ s.lcomb.FillLabelFactor1 = 0.476509; // fuzzed, old value = 0.481139
	FUZZ s.lcomb.FillLabelFactor2 = 0.579601; // fuzzed, old value = 0.562802

	FUZZ s.p_estimator.DefaultApriority = 0.502623; // fuzzed, old value = 0.528095
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.822343; // fuzzed, old value = 0.807739
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.257831; // fuzzed, old value = 0.254350
	FUZZ s.p_estimator.LogisticScale = 0.985688; // fuzzed, old value = 0.965468
	FUZZ s.p_estimator.LogisticLocation = 1.031057; // fuzzed, old value = 0.997255
}
