
void updateSettingsScanned(Settings &s)
{
	s.general.UseProbablistics = false;
	s.p_estimator.UsePerimeterNormalization = true; 

	FUZZ s.separator.ext2charRatio = 1.755319; // fuzzed, old value = 1.774531
	FUZZ s.separator.SymProbabilityThresh = 0.617778; // fuzzed, old value = 0.594290

	FUZZ s.molecule.LengthFactor_long = 0.345180; // fuzzed, old value = 0.353589
	FUZZ s.molecule.LengthFactor_medium = 0.379301; // fuzzed, old value = 0.391335
	FUZZ s.molecule.LengthFactor_default = 0.473293; // fuzzed, old value = 0.458738
	FUZZ s.molecule.LengthValue_long = 105.229242; // fuzzed, old value = 103.489779
	FUZZ s.molecule.LengthValue_medium = 92.051658; // fuzzed, old value = 91.834592
	FUZZ s.molecule.SpaceMultiply = 1.185265; // fuzzed, old value = 1.187321
	FUZZ s.molecule.AngleTreshold = 0.264773; // fuzzed, old value = 0.270732
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.344803; // fuzzed, old value = 16.792724
	FUZZ s.estimation.LineThickness = 7.283648; // fuzzed, old value = 7.225357
	FUZZ s.estimation.AvgBondLength = 28.257653; // fuzzed, old value = 28.462608
	FUZZ s.estimation.AddVertexEps = 5.192835; // fuzzed, old value = 4.995724
	FUZZ s.estimation.MaxSymRatio = 1.053373; // fuzzed, old value = 1.107000
	FUZZ s.estimation.MinSymRatio = 0.298746; // fuzzed, old value = 0.285846
	FUZZ s.estimation.ParLinesEps = 0.533526; // fuzzed, old value = 0.552002
	FUZZ s.estimation.SymHeightErr = 27.151107; // fuzzed, old value = 27.969571
	FUZZ s.estimation.CapitalHeightError = 0.717162; // fuzzed, old value = 0.732853
	FUZZ s.estimation.DoubleBondDist = 19; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.320745; // fuzzed, old value = 0.333673
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.157168; // fuzzed, old value = 0.161271
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 101; // fuzzed, old value = 97
	FUZZ s.mbond.LongErr = 0.345980; // fuzzed, old value = 0.358157
	FUZZ s.mbond.MediumBond = 82; // fuzzed, old value = 84
	FUZZ s.mbond.MediumErr = 0.488262; // fuzzed, old value = 0.478652
	FUZZ s.mbond.DefaultErr = 0.584065; // fuzzed, old value = 0.580151
	FUZZ s.mbond.ParBondsEps = 0.377247; // fuzzed, old value = 0.371063
	FUZZ s.mbond.DoubleRatioTresh = 7.055080; // fuzzed, old value = 7.014460
	FUZZ s.mbond.DoubleCoef = 0.087933; // fuzzed, old value = 0.084084
	FUZZ s.mbond.DoubleMagic1 = 0.762639; // fuzzed, old value = 0.793018
	FUZZ s.mbond.DoubleMagic2 = 0.879116; // fuzzed, old value = 0.894817
	FUZZ s.mbond.DoubleTreshMin = 0.105452; // fuzzed, old value = 0.101762
	FUZZ s.mbond.DoubleTreshMax = 0.687212; // fuzzed, old value = 0.679261
	FUZZ s.mbond.MaxLen1 = 157.789477; // fuzzed, old value = 162.757846
	FUZZ s.mbond.MaxLen2 = 134.392061; // fuzzed, old value = 133.088873
	FUZZ s.mbond.MaxLen3 = 107.212601; // fuzzed, old value = 107.205894
	FUZZ s.mbond.MaxLen4 = 115.092737; // fuzzed, old value = 116.339139
	FUZZ s.mbond.MaxLen5 = 75.260640; // fuzzed, old value = 74.485371
	FUZZ s.mbond.MinLen1 = 79.173070; // fuzzed, old value = 77.318967
	FUZZ s.mbond.MinLen2 = 80.353457; // fuzzed, old value = 82.623997
	FUZZ s.mbond.mbe1 = 0.075628; // fuzzed, old value = 0.072101
	FUZZ s.mbond.mbe2 = 0.167488; // fuzzed, old value = 0.161936
	FUZZ s.mbond.mbe3 = 0.177848; // fuzzed, old value = 0.170567
	FUZZ s.mbond.mbe4 = 0.161561; // fuzzed, old value = 0.153941
	FUZZ s.mbond.mbe5 = 0.180485; // fuzzed, old value = 0.179342
	FUZZ s.mbond.mbe6 = 0.213659; // fuzzed, old value = 0.206701
	FUZZ s.mbond.mbe7 = 0.412891; // fuzzed, old value = 0.405372
	FUZZ s.mbond.mbe_def = 0.573218; // fuzzed, old value = 0.555370
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.406591; // fuzzed, old value = 0.394318
	FUZZ s.mbond.DoubleRightLengthTresh = 0.344375; // fuzzed, old value = 0.333874
	FUZZ s.mbond.TripleLeftLengthTresh = 0.277098; // fuzzed, old value = 0.266706
	FUZZ s.mbond.TripleRightLengthTresh = 0.243946; // fuzzed, old value = 0.234583
	FUZZ s.mbond.Case1LengthTresh = 88.298265; // fuzzed, old value = 91.059909
	FUZZ s.mbond.Case1Factor = 0.358745; // fuzzed, old value = 0.350568
	FUZZ s.mbond.Case2LengthTresh = 85.085872; // fuzzed, old value = 88.513132
	FUZZ s.mbond.Case2Factor = 0.667684; // fuzzed, old value = 0.656119
	FUZZ s.mbond.Case3Factor = 0.899318; // fuzzed, old value = 0.911078
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.101828; // fuzzed, old value = 0.105446
	FUZZ s.skeleton.BaseSmallErr = 0.143777; // fuzzed, old value = 0.142150
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 23
	FUZZ s.skeleton.ShortMul = 0.313221; // fuzzed, old value = 0.319675
	FUZZ s.skeleton.MediumBondLen = 102; // fuzzed, old value = 97
	FUZZ s.skeleton.MediumMul = 0.178974; // fuzzed, old value = 0.174741
	FUZZ s.skeleton.MediumSmallErr = 0.125351; // fuzzed, old value = 0.130133
	FUZZ s.skeleton.LongBondLen = 89; // fuzzed, old value = 92
	FUZZ s.skeleton.LongMul = 0.136323; // fuzzed, old value = 0.143128
	FUZZ s.skeleton.LongSmallErr = 0.055669; // fuzzed, old value = 0.058402
	FUZZ s.skeleton.BrokenRepairFactor = 3.488668; // fuzzed, old value = 3.530762
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.035404; // fuzzed, old value = 1.051655
	FUZZ s.skeleton.BrokenRepairCoef2 = 3.198264; // fuzzed, old value = 3.183927
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.182784; // fuzzed, old value = 0.177702
	FUZZ s.skeleton.DissolveMinErr = 0.196712; // fuzzed, old value = 0.193186
	FUZZ s.skeleton.ConnectBlockS = 9.464835; // fuzzed, old value = 9.737110
	FUZZ s.skeleton.ConnectFactor = 2.481941; // fuzzed, old value = 2.567178
	FUZZ s.skeleton.JoinVerticiesConst = 0.099280; // fuzzed, old value = 0.100176
	FUZZ s.skeleton.DissolveConst = 0.100677; // fuzzed, old value = 0.099488
	FUZZ s.skeleton.Dissolve2Const = 0.196365; // fuzzed, old value = 0.204460
	FUZZ s.skeleton.Join2Const = 0.209048; // fuzzed, old value = 0.218853
	FUZZ s.skeleton.Join3Const = 0.154838; // fuzzed, old value = 0.158067
	FUZZ s.skeleton.DistTreshLimFactor = 2.097187; // fuzzed, old value = 2.011705
	FUZZ s.skeleton.SlopeFact1 = 0.084871; // fuzzed, old value = 0.084126
	FUZZ s.skeleton.SlopeFact2 = 0.172082; // fuzzed, old value = 0.171282
	FUZZ s.skeleton.ShrinkEps = 0.149117; // fuzzed, old value = 0.148880
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	
	FUZZ s.routines.Circle_GapRadiusMax = 1.167287; // fuzzed, old value = 1.219945
	FUZZ s.routines.Circle_GapAngleMax = 0.214440; // fuzzed, old value = 0.211626
	FUZZ s.routines.Circle_MinRadius = 5.835283; // fuzzed, old value = 6.056196
	FUZZ s.routines.Circle_MaxDeviation = 0.009273; // fuzzed, old value = 0.009138
	FUZZ s.routines.Circle_AsCharFactor = 1.112924; // fuzzed, old value = 1.087470
	FUZZ s.routines.Algebra_IntersectionEps = 0.011772; // fuzzed, old value = 0.012304
	FUZZ s.routines.Algebra_SameLineEps = 0.216001; // fuzzed, old value = 0.218254
	FUZZ s.routines.Approx_Eps1 = 0.967950; // fuzzed, old value = 0.960157
	FUZZ s.routines.Approx_Eps2 = 0.827956; // fuzzed, old value = 0.825622
	FUZZ s.routines.Approx_CalcLineTresh = 0.813365; // fuzzed, old value = 0.802077
	FUZZ s.routines.Contour_Eps1 = 0.987701; // fuzzed, old value = 0.980031
	FUZZ s.routines.Contour_Eps2 = 0.621925; // fuzzed, old value = 0.652436

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.662791; // fuzzed, old value = 2.586511
	FUZZ s.wbe.SingleDownAngleMax = 51.730105; // fuzzed, old value = 49.546430
	FUZZ s.wbe.SingleDownDistancesMax = 10.255996; // fuzzed, old value = 10.507451
	FUZZ s.wbe.SingleDownLengthMax = 51.175536; // fuzzed, old value = 50.707336
	FUZZ s.wbe.SomeTresh = 0.129687; // fuzzed, old value = 0.129289

	FUZZ s.wbe.SingleUpRatioEps = 1.607234; // fuzzed, old value = 1.531990
	FUZZ s.wbe.SingleUpDefCoeff = 0.276465; // fuzzed, old value = 0.289316
	FUZZ s.wbe.SingleUpIncCoeff = 0.434523; // fuzzed, old value = 0.447693
	FUZZ s.wbe.SingleUpIncLengthTresh = 33.482017; // fuzzed, old value = 34.588540
	FUZZ s.wbe.SingleUpInterpolateEps = 0.068573; // fuzzed, old value = 0.071319
	FUZZ s.wbe.SingleUpMagicAddition = 0.218523; // fuzzed, old value = 0.211217
	FUZZ s.wbe.SingleUpS2Divisor = 1.568714; // fuzzed, old value = 1.613958
	FUZZ s.wbe.SingleUpMinATresh = 1.604374; // fuzzed, old value = 1.624018
	FUZZ s.wbe.SingleUpSquareRatio = 0.580403; // fuzzed, old value = 0.573586
	FUZZ s.wbe.SingleUpAngleTresh = 0.076463; // fuzzed, old value = 0.075966
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = false;
	FUZZ s.characters.MaximalEndpointsUse = 6; // fuzzed, old value = 6
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.013063; // fuzzed, old value = 1.055716
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.176900; // fuzzed, old value = 1.164232
	FUZZ s.characters.WriteEasyFactor = 1.022834; // fuzzed, old value = 1.008169
	FUZZ s.characters.WriteVeryEasyFactor = 1.023170; // fuzzed, old value = 1.027080
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 2.917067; // fuzzed, old value = 2.946004
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.374086; // fuzzed, old value = 3.302985
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.085562; // fuzzed, old value = 0.089897
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.627825; // fuzzed, old value = 2.633044
	FUZZ s.characters.DescriptorsEvenFactorStrong = 4.032184; // fuzzed, old value = 4.163078
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.990455; // fuzzed, old value = 0.972565
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.259387; // fuzzed, old value = 0.268273
	FUZZ s.characters.X_Quality = 0.112594; // fuzzed, old value = 0.109278
	FUZZ s.characters.MinEndpointsPossible = 4; // fuzzed, old value = 4
	
	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.484530; // fuzzed, old value = 0.502633
	FUZZ s.csr.DeleteBadTriangles = 1.931194; // fuzzed, old value = 2.008064
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.608142; // fuzzed, old value = 1.574297

	FUZZ s.graph.MinimalDistTresh = 2.408616; // fuzzed, old value = 2.466159
	FUZZ s.graph.RatioSub = 0.907920; // fuzzed, old value = 0.893443
	FUZZ s.graph.RatioTresh = 0.469437; // fuzzed, old value = 0.477176

	FUZZ s.utils.SlashLineDensity = 0.398557; // fuzzed, old value = 0.411511
	FUZZ s.utils.TestPlusDensity = 0.440823; // fuzzed, old value = 0.457418
	FUZZ s.utils.TestPlusSq = 0.529765; // fuzzed, old value = 0.507304
	FUZZ s.utils.TestMinusRatio = 0.306360; // fuzzed, old value = 0.303036
	FUZZ s.utils.TestMinusDensity = 0.599157; // fuzzed, old value = 0.590034
	FUZZ s.utils.TestMinusHeightFactor = 0.884661; // fuzzed, old value = 0.843076

	FUZZ s.separator.hu_1_1 = 0.211667; // fuzzed, old value = 0.217657
	FUZZ s.separator.hu_1_2 = 0.090549; // fuzzed, old value = 0.092536
	FUZZ s.separator.hu_0_1 = 0.187956; // fuzzed, old value = 0.181678
	FUZZ s.separator.hu_1_3 = 0.098919; // fuzzed, old value = 0.099738
	FUZZ s.separator.hu_0_2 = 0.227881; // fuzzed, old value = 0.239692
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.473771; // fuzzed, old value = 0.487291
	FUZZ s.separator.capHeightMax = 1.634305; // fuzzed, old value = 1.585603
	FUZZ s.separator.gdConst = 1.487580; // fuzzed, old value = 1.528281
	FUZZ s.separator.SurfCoef = 3.358868; // fuzzed, old value = 3.231201
	FUZZ s.separator.capHeightRatio = 0.319991; // fuzzed, old value = 0.331877
	FUZZ s.separator.capHeightRatio2 = 2.072853; // fuzzed, old value = 2.171431
	FUZZ s.separator.getRatio1 = 1.000982; // fuzzed, old value = 0.963598
	FUZZ s.separator.getRatio2 = 1.361253; // fuzzed, old value = 1.329942
	FUZZ s.separator.testSlashLine1 = 2.793254; // fuzzed, old value = 2.803440
	FUZZ s.separator.testSlashLine2 = 2.498902; // fuzzed, old value = 2.426928
	FUZZ s.separator.minDensity = 0.197472; // fuzzed, old value = 0.192539
	FUZZ s.separator.maxDensity = 0.996398; // fuzzed, old value = 0.951803
	FUZZ s.separator.extCapHeightMin = 0.312820; // fuzzed, old value = 0.307928
	FUZZ s.separator.extCapHeightMax = 2.190841; // fuzzed, old value = 2.234919
	FUZZ s.separator.extRatioMin = 0.303784; // fuzzed, old value = 0.299709
	FUZZ s.separator.extRatioMax = 1.302494; // fuzzed, old value = 1.354984
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 9; // fuzzed, old value = 9
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = false; // fuzzed, old value = false

	FUZZ s.labels.underlinePos = 0.427261; // fuzzed, old value = 0.429213
	FUZZ s.labels.weightUnderline = 0.284974; // fuzzed, old value = 0.280091
	FUZZ s.labels.ratioBase = 0.682996; // fuzzed, old value = 0.662331
	FUZZ s.labels.ratioWeight = 0.248854; // fuzzed, old value = 0.261594
	FUZZ s.labels.adjustDec = 1.279041; // fuzzed, old value = 1.339033
	FUZZ s.labels.adjustInc = 0.768713; // fuzzed, old value = 0.804306
	FUZZ s.labels.sameLineEps = 0.090471; // fuzzed, old value = 0.094947
	FUZZ s.labels.heightRatio = 0.779538; // fuzzed, old value = 0.772778
	FUZZ s.labels.medHeightFactor = 0.628123; // fuzzed, old value = 0.616474
	FUZZ s.labels.capHeightError = 0.520798; // fuzzed, old value = 0.497631

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.491587; // fuzzed, old value = 2.582944
	FUZZ s.lcomb.MaximalDistanceFactor = 0.588459; // fuzzed, old value = 0.570641
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.218266; // fuzzed, old value = 0.208459
	FUZZ s.lcomb.FillLabelFactor1 = 0.472013; // fuzzed, old value = 0.487336
	FUZZ s.lcomb.FillLabelFactor2 = 0.539873; // fuzzed, old value = 0.539997

	FUZZ s.p_estimator.DefaultApriority = 0.525200; // fuzzed, old value = 0.546622
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.765507; // fuzzed, old value = 0.737595
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.260139; // fuzzed, old value = 0.259158
	FUZZ s.p_estimator.LogisticScale = 1.025648; // fuzzed, old value = 0.993478
	FUZZ s.p_estimator.LogisticLocation = 0.876903; // fuzzed, old value = 0.908998
}
