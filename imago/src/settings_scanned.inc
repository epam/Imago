
void updateSettingsScanned(Settings &s)
{
	FUZZ s.general.UseProbablistics = false; // fuzzed, old value = false

	FUZZ s.separator.ext2charRatio = 1.767319; // fuzzed, old value = 1.771798

	FUZZ s.molecule.LengthFactor_long = 0.340889; // fuzzed, old value = 0.338853
	FUZZ s.molecule.LengthFactor_medium = 0.393316; // fuzzed, old value = 0.397616
	FUZZ s.molecule.LengthFactor_default = 0.477074; // fuzzed, old value = 0.468480
	FUZZ s.molecule.LengthValue_long = 111.357898; // fuzzed, old value = 110.844809
	FUZZ s.molecule.LengthValue_medium = 84.472918; // fuzzed, old value = 82.817862
	FUZZ s.molecule.SpaceMultiply = 1.375891; // fuzzed, old value = 1.390003
	FUZZ s.molecule.AngleTreshold = 0.261624; // fuzzed, old value = 0.263779
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.889670; // fuzzed, old value = 16.542347
	FUZZ s.estimation.LineThickness = 6.937200; // fuzzed, old value = 6.901316
	FUZZ s.estimation.AvgBondLength = 30.607329; // fuzzed, old value = 30.471534
	FUZZ s.estimation.AddVertexEps = 4.750233; // fuzzed, old value = 4.667805
	FUZZ s.estimation.MaxSymRatio = 1.210384; // fuzzed, old value = 1.186188
	FUZZ s.estimation.MinSymRatio = 0.299972; // fuzzed, old value = 0.304743
	FUZZ s.estimation.ParLinesEps = 0.565289; // fuzzed, old value = 0.563354
	FUZZ s.estimation.SymHeightErr = 27.576883; // fuzzed, old value = 27.409354
	FUZZ s.estimation.CapitalHeightError = 0.846774; // fuzzed, old value = 0.834278
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.373133; // fuzzed, old value = 0.378156
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.152958; // fuzzed, old value = 0.153076
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 103; // fuzzed, old value = 106
	FUZZ s.mbond.LongErr = 0.317139; // fuzzed, old value = 0.321693
	FUZZ s.mbond.MediumBond = 83; // fuzzed, old value = 82
	FUZZ s.mbond.MediumErr = 0.460874; // fuzzed, old value = 0.456050
	FUZZ s.mbond.DefaultErr = 0.678407; // fuzzed, old value = 0.665182
	FUZZ s.mbond.ParBondsEps = 0.356066; // fuzzed, old value = 0.358454
	FUZZ s.mbond.DoubleRatioTresh = 6.349077; // fuzzed, old value = 6.332510
	FUZZ s.mbond.DoubleCoef = 0.077616; // fuzzed, old value = 0.076883
	FUZZ s.mbond.DoubleMagic1 = 0.862940; // fuzzed, old value = 0.873083
	FUZZ s.mbond.DoubleMagic2 = 0.967086; // fuzzed, old value = 0.951512
	FUZZ s.mbond.DoubleTreshMin = 0.104527; // fuzzed, old value = 0.102096
	FUZZ s.mbond.DoubleTreshMax = 0.798826; // fuzzed, old value = 0.800839
	FUZZ s.mbond.MaxLen1 = 153.764202; // fuzzed, old value = 153.323071
	FUZZ s.mbond.MaxLen2 = 137.258959; // fuzzed, old value = 138.763497
	FUZZ s.mbond.MaxLen3 = 109.608049; // fuzzed, old value = 109.301081
	FUZZ s.mbond.MaxLen4 = 122.631261; // fuzzed, old value = 125.160190
	FUZZ s.mbond.MaxLen5 = 80.706855; // fuzzed, old value = 79.612238
	FUZZ s.mbond.MinLen1 = 87.642060; // fuzzed, old value = 88.889324
	FUZZ s.mbond.MinLen2 = 73.703987; // fuzzed, old value = 72.571954
	FUZZ s.mbond.mbe1 = 0.076706; // fuzzed, old value = 0.076154
	FUZZ s.mbond.mbe2 = 0.161620; // fuzzed, old value = 0.160425
	FUZZ s.mbond.mbe3 = 0.190503; // fuzzed, old value = 0.189353
	FUZZ s.mbond.mbe4 = 0.168650; // fuzzed, old value = 0.166404
	FUZZ s.mbond.mbe5 = 0.156199; // fuzzed, old value = 0.155661
	FUZZ s.mbond.mbe6 = 0.212919; // fuzzed, old value = 0.211763
	FUZZ s.mbond.mbe7 = 0.373622; // fuzzed, old value = 0.380054
	FUZZ s.mbond.mbe_def = 0.518862; // fuzzed, old value = 0.531358
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.350223; // fuzzed, old value = 0.346371
	FUZZ s.mbond.DoubleRightLengthTresh = 0.305265; // fuzzed, old value = 0.303215
	FUZZ s.mbond.TripleLeftLengthTresh = 0.243861; // fuzzed, old value = 0.240531
	FUZZ s.mbond.TripleRightLengthTresh = 0.227698; // fuzzed, old value = 0.225971
	FUZZ s.mbond.Case1LengthTresh = 91.532935; // fuzzed, old value = 90.183296
	FUZZ s.mbond.Case1Factor = 0.368663; // fuzzed, old value = 0.368570
	FUZZ s.mbond.Case2LengthTresh = 82.468096; // fuzzed, old value = 84.376922
	FUZZ s.mbond.Case2Factor = 0.701315; // fuzzed, old value = 0.695911
	FUZZ s.mbond.Case3Factor = 1.034542; // fuzzed, old value = 1.010147
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.106433; // fuzzed, old value = 0.106559
	FUZZ s.skeleton.BaseSmallErr = 0.154460; // fuzzed, old value = 0.156184
	FUZZ s.skeleton.ShortBondLen = 21; // fuzzed, old value = 21
	FUZZ s.skeleton.ShortMul = 0.332122; // fuzzed, old value = 0.324988
	FUZZ s.skeleton.MediumBondLen = 91; // fuzzed, old value = 89
	FUZZ s.skeleton.MediumMul = 0.168570; // fuzzed, old value = 0.166926
	FUZZ s.skeleton.MediumSmallErr = 0.128446; // fuzzed, old value = 0.128049
	FUZZ s.skeleton.LongBondLen = 100; // fuzzed, old value = 98
	FUZZ s.skeleton.LongMul = 0.139225; // fuzzed, old value = 0.142736
	FUZZ s.skeleton.LongSmallErr = 0.062579; // fuzzed, old value = 0.062092
	FUZZ s.skeleton.BrokenRepairFactor = 3.367153; // fuzzed, old value = 3.405501
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.961410; // fuzzed, old value = 0.967483
	FUZZ s.skeleton.BrokenRepairCoef2 = 3.130242; // fuzzed, old value = 3.087550
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.207376; // fuzzed, old value = 0.209671
	FUZZ s.skeleton.DissolveMinErr = 0.177770; // fuzzed, old value = 0.176070
	FUZZ s.skeleton.ConnectBlockS = 9.387327; // fuzzed, old value = 9.625256
	FUZZ s.skeleton.ConnectFactor = 2.123681; // fuzzed, old value = 2.077395
	FUZZ s.skeleton.JoinVerticiesConst = 0.104686; // fuzzed, old value = 0.105085
	FUZZ s.skeleton.DissolveConst = 0.098735; // fuzzed, old value = 0.097277
	FUZZ s.skeleton.Dissolve2Const = 0.192749; // fuzzed, old value = 0.191600
	FUZZ s.skeleton.Join2Const = 0.266918; // fuzzed, old value = 0.264572
	FUZZ s.skeleton.Join3Const = 0.182588; // fuzzed, old value = 0.183748
	FUZZ s.skeleton.DistTreshLimFactor = 2.148678; // fuzzed, old value = 2.105590
	FUZZ s.skeleton.SlopeFact1 = 0.090052; // fuzzed, old value = 0.091244
	FUZZ s.skeleton.SlopeFact2 = 0.161803; // fuzzed, old value = 0.161702
	FUZZ s.skeleton.ShrinkEps = 0.138146; // fuzzed, old value = 0.140281
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	
	FUZZ s.routines.Circle_GapRadiusMax = 1.042189; // fuzzed, old value = 1.050731
	FUZZ s.routines.Circle_GapAngleMax = 0.207993; // fuzzed, old value = 0.203439
	FUZZ s.routines.Circle_MinRadius = 6.771566; // fuzzed, old value = 6.900335
	FUZZ s.routines.Circle_MaxDeviation = 0.010555; // fuzzed, old value = 0.010575
	FUZZ s.routines.Circle_AsCharFactor = 1.084621; // fuzzed, old value = 1.077311

	FUZZ s.routines.Algebra_IntersectionEps = 0.011577; // fuzzed, old value = 0.011465
	FUZZ s.routines.Algebra_SameLineEps = 0.229190; // fuzzed, old value = 0.224437
	FUZZ s.routines.Approx_Eps1 = 1.116990; // fuzzed, old value = 1.141541
	FUZZ s.routines.Approx_Eps2 = 0.850903; // fuzzed, old value = 0.851725
	FUZZ s.routines.Approx_CalcLineTresh = 0.898889; // fuzzed, old value = 0.914830
	FUZZ s.routines.Contour_Eps1 = 0.969275; // fuzzed, old value = 0.965831
	FUZZ s.routines.Contour_Eps2 = 0.669568; // fuzzed, old value = 0.683620

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.512641; // fuzzed, old value = 2.542952
	FUZZ s.wbe.SingleDownAngleMax = 43.474725; // fuzzed, old value = 43.126895
	FUZZ s.wbe.SingleDownDistancesMax = 10.081656; // fuzzed, old value = 10.048758
	FUZZ s.wbe.SingleDownLengthMax = 50.032921; // fuzzed, old value = 50.556936
	FUZZ s.wbe.SingleUpRatioEps = 1.568361; // fuzzed, old value = 1.605023
	FUZZ s.wbe.SingleUpDefCoeff = 0.276846; // fuzzed, old value = 0.273551
	FUZZ s.wbe.SingleUpIncCoeff = 0.484086; // fuzzed, old value = 0.494887
	FUZZ s.wbe.SingleUpIncLengthTresh = 35.298162; // fuzzed, old value = 35.194914
	FUZZ s.wbe.SingleUpInterpolateEps = 0.063635; // fuzzed, old value = 0.065090
	FUZZ s.wbe.SingleUpMagicAddition = 0.245117; // fuzzed, old value = 0.251085
	FUZZ s.wbe.SingleUpS2Divisor = 1.427349; // fuzzed, old value = 1.459195
	FUZZ s.wbe.SingleUpMinATresh = 1.704276; // fuzzed, old value = 1.693127
	FUZZ s.wbe.SingleUpSquareRatio = 0.631337; // fuzzed, old value = 0.624043
	FUZZ s.wbe.SingleUpAngleTresh = 0.069033; // fuzzed, old value = 0.067596
	FUZZ s.wbe.SomeTresh = 0.102061; // fuzzed, old value = 0.101527
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = false; // fuzzed, old value = false
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.006098; // fuzzed, old value = 0.985291
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.077772; // fuzzed, old value = 1.098267
	FUZZ s.characters.WriteEasyFactor = 0.956053; // fuzzed, old value = 0.962507
	FUZZ s.characters.WriteVeryEasyFactor = 0.974528; // fuzzed, old value = 0.965804
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.169545; // fuzzed, old value = 3.138903
	FUZZ s.characters.PossibleCharacterDistanceWeak = 2.937536; // fuzzed, old value = 2.994244
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.097843; // fuzzed, old value = 0.098364
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.516186; // fuzzed, old value = 2.553251
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.802056; // fuzzed, old value = 3.801960
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.002519; // fuzzed, old value = 0.978328
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.284260; // fuzzed, old value = 0.288967
	FUZZ s.characters.HW_Line = 1.566174; // fuzzed, old value = 1.538010
	FUZZ s.characters.HW_F = 3.510578; // fuzzed, old value = 3.433685
	FUZZ s.characters.HW_Tricky = 3.038015; // fuzzed, old value = 3.087902
	FUZZ s.characters.HW_Hard = 4.286724; // fuzzed, old value = 4.238485
	FUZZ s.characters.HW_Other = 3.623028; // fuzzed, old value = 3.554941

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.524853; // fuzzed, old value = 0.513776
	FUZZ s.csr.DeleteBadTriangles = 2.030885; // fuzzed, old value = 1.987894
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.757086; // fuzzed, old value = 1.787322

	FUZZ s.graph.MinimalDistTresh = 1.988540; // fuzzed, old value = 1.967968
	FUZZ s.graph.RatioSub = 0.977444; // fuzzed, old value = 0.997638
	FUZZ s.graph.RatioTresh = 0.483066; // fuzzed, old value = 0.472818

	FUZZ s.utils.SlashLineDensity = 0.380602; // fuzzed, old value = 0.377128
	FUZZ s.utils.TestPlusDensity = 0.446602; // fuzzed, old value = 0.449545
	FUZZ s.utils.TestPlusSq = 0.444991; // fuzzed, old value = 0.438382
	FUZZ s.utils.TestMinusRatio = 0.323241; // fuzzed, old value = 0.320861
	FUZZ s.utils.TestMinusDensity = 0.612802; // fuzzed, old value = 0.617105
	FUZZ s.utils.TestMinusHeightFactor = 0.858695; // fuzzed, old value = 0.841425

	FUZZ s.separator.hu_1_1 = 0.225440; // fuzzed, old value = 0.226956
	FUZZ s.separator.hu_1_2 = 0.086412; // fuzzed, old value = 0.085619
	FUZZ s.separator.hu_0_1 = 0.208317; // fuzzed, old value = 0.211932
	FUZZ s.separator.hu_1_3 = 0.089391; // fuzzed, old value = 0.089489
	FUZZ s.separator.hu_0_2 = 0.219407; // fuzzed, old value = 0.217154
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.535304; // fuzzed, old value = 0.544131
	FUZZ s.separator.capHeightMax = 1.503544; // fuzzed, old value = 1.482986
	FUZZ s.separator.gdConst = 1.553112; // fuzzed, old value = 1.574764
	FUZZ s.separator.SurfCoef = 3.133748; // fuzzed, old value = 3.126147
	FUZZ s.separator.capHeightRatio = 0.285849; // fuzzed, old value = 0.281610
	FUZZ s.separator.capHeightRatio2 = 1.892839; // fuzzed, old value = 1.921472
	FUZZ s.separator.getRatio1 = 1.032438; // fuzzed, old value = 1.030272
	FUZZ s.separator.getRatio2 = 1.219021; // fuzzed, old value = 1.228747
	FUZZ s.separator.testSlashLine1 = 3.122285; // fuzzed, old value = 3.101050
	FUZZ s.separator.testSlashLine2 = 2.577383; // fuzzed, old value = 2.550970
	FUZZ s.separator.minDensity = 0.191005; // fuzzed, old value = 0.195769
	FUZZ s.separator.maxDensity = 0.944421; // fuzzed, old value = 0.926268
	FUZZ s.separator.extCapHeightMin = 0.285472; // fuzzed, old value = 0.288028
	FUZZ s.separator.extCapHeightMax = 2.105819; // fuzzed, old value = 2.058896
	FUZZ s.separator.extRatioMin = 0.329231; // fuzzed, old value = 0.330762
	FUZZ s.separator.extRatioMax = 1.516666; // fuzzed, old value = 1.546139
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = false; // fuzzed, old value = false

	FUZZ s.labels.underlinePos = 0.390269; // fuzzed, old value = 0.399299
	FUZZ s.labels.weightUnderline = 0.278459; // fuzzed, old value = 0.279264
	FUZZ s.labels.ratioBase = 0.731026; // fuzzed, old value = 0.743367
	FUZZ s.labels.ratioWeight = 0.283072; // fuzzed, old value = 0.282293
	FUZZ s.labels.adjustDec = 1.270792; // fuzzed, old value = 1.282061
	FUZZ s.labels.adjustInc = 0.791853; // fuzzed, old value = 0.777948
	FUZZ s.labels.sameLineEps = 0.112452; // fuzzed, old value = 0.113361
	FUZZ s.labels.heightRatio = 0.751725; // fuzzed, old value = 0.757841
	FUZZ s.labels.medHeightFactor = 0.534892; // fuzzed, old value = 0.536691
	FUZZ s.labels.capHeightError = 0.484007; // fuzzed, old value = 0.494046

	FUZZ s.lcomb.MaximalSymbolDistance = 2.750317; // fuzzed, old value = 2.802787
	FUZZ s.lcomb.TestSlashLineEps = 3.601734; // fuzzed, old value = 3.522082
	FUZZ s.lcomb.TestMinHeightFactor = 0.582599; // fuzzed, old value = 0.588148
	FUZZ s.lcomb.TestMaxHeightFactor = 1.104559; // fuzzed, old value = 1.110332
	FUZZ s.lcomb.RectHeightRatio = 0.471060; // fuzzed, old value = 0.480207
	FUZZ s.lcomb.H1SuperscriptSpace = 1.046869; // fuzzed, old value = 1.066519
	FUZZ s.lcomb.H2LowercaseSpace = 0.446648; // fuzzed, old value = 0.441986
	FUZZ s.lcomb.H3LowercaseSpace = 0.443243; // fuzzed, old value = 0.451438
	FUZZ s.lcomb.H4SubscriptSpace = 0.505836; // fuzzed, old value = 0.497856
	FUZZ s.lcomb.FillLabelFactor1 = 0.481139; // fuzzed, old value = 0.492940
	FUZZ s.lcomb.FillLabelFactor2 = 0.562802; // fuzzed, old value = 0.555682

	FUZZ s.p_estimator.DefaultApriority = 0.528095; // fuzzed, old value = 0.521156
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.807739; // fuzzed, old value = 0.791410
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.254350; // fuzzed, old value = 0.248403
	FUZZ s.p_estimator.LogisticScale = 0.965468; // fuzzed, old value = 0.957780
	FUZZ s.p_estimator.LogisticLocation = 0.997255; // fuzzed, old value = 1.008000
}
