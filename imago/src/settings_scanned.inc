
void updateSettingsScanned(Settings &s)
{
	FUZZ s.general.UseProbablistics = false; // fuzzed, old value = false

	FUZZ s.separator.ext2charRatio = 1.817831; // fuzzed, old value = 1.825673

	FUZZ s.molecule.LengthFactor_long = 0.315152; // fuzzed, old value = 0.328143
	FUZZ s.molecule.LengthFactor_medium = 0.389830; // fuzzed, old value = 0.399042
	FUZZ s.molecule.LengthFactor_default = 0.449027; // fuzzed, old value = 0.461662
	FUZZ s.molecule.LengthValue_long = 105.508872; // fuzzed, old value = 108.941492
	FUZZ s.molecule.LengthValue_medium = 80.993297; // fuzzed, old value = 78.957726
	FUZZ s.molecule.SpaceMultiply = 1.429923; // fuzzed, old value = 1.447843
	FUZZ s.molecule.AngleTreshold = 0.263010; // fuzzed, old value = 0.251429
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 18.573252; // fuzzed, old value = 17.731897
	FUZZ s.estimation.LineThickness = 6.299226; // fuzzed, old value = 6.101518
	FUZZ s.estimation.AvgBondLength = 29.895446; // fuzzed, old value = 30.355357
	FUZZ s.estimation.AddVertexEps = 5.050122; // fuzzed, old value = 5.258299
	FUZZ s.estimation.MaxSymRatio = 1.168082; // fuzzed, old value = 1.144596
	FUZZ s.estimation.MinSymRatio = 0.322742; // fuzzed, old value = 0.331593
	FUZZ s.estimation.ParLinesEps = 0.545863; // fuzzed, old value = 0.554123
	FUZZ s.estimation.SymHeightErr = 26.091749; // fuzzed, old value = 26.601544
	FUZZ s.estimation.CapitalHeightError = 0.852278; // fuzzed, old value = 0.830952
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.401027; // fuzzed, old value = 0.392604
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 112; // fuzzed, old value = 116
	FUZZ s.mbond.LongErr = 0.350717; // fuzzed, old value = 0.349333
	FUZZ s.mbond.MediumBond = 86; // fuzzed, old value = 90
	FUZZ s.mbond.MediumErr = 0.437198; // fuzzed, old value = 0.417903
	FUZZ s.mbond.DefaultErr = 0.673239; // fuzzed, old value = 0.661368
	FUZZ s.mbond.ParBondsEps = 0.343600; // fuzzed, old value = 0.349765
	FUZZ s.mbond.DoubleRatioTresh = 6.413808; // fuzzed, old value = 6.698078
	FUZZ s.mbond.DoubleCoef = 0.076054; // fuzzed, old value = 0.079779
	FUZZ s.mbond.DoubleMagic1 = 0.902185; // fuzzed, old value = 0.928173
	FUZZ s.mbond.DoubleMagic2 = 0.928028; // fuzzed, old value = 0.893623
	FUZZ s.mbond.DoubleTreshMin = 0.094928; // fuzzed, old value = 0.094915
	FUZZ s.mbond.DoubleTreshMax = 0.815465; // fuzzed, old value = 0.819377
	FUZZ s.mbond.MaxLen1 = 152.490507; // fuzzed, old value = 148.096251
	FUZZ s.mbond.MaxLen2 = 133.330018; // fuzzed, old value = 128.438369
	FUZZ s.mbond.MaxLen3 = 116.978601; // fuzzed, old value = 115.245539
	FUZZ s.mbond.MaxLen4 = 123.764210; // fuzzed, old value = 121.904961
	FUZZ s.mbond.MaxLen5 = 75.254072; // fuzzed, old value = 78.515883
	FUZZ s.mbond.MinLen1 = 89.185441; // fuzzed, old value = 86.077108
	FUZZ s.mbond.MinLen2 = 71.636468; // fuzzed, old value = 70.585346
	FUZZ s.mbond.mbe1 = 0.077716; // fuzzed, old value = 0.078287
	FUZZ s.mbond.mbe2 = 0.158104; // fuzzed, old value = 0.155200
	FUZZ s.mbond.mbe3 = 0.205715; // fuzzed, old value = 0.204358
	FUZZ s.mbond.mbe4 = 0.174596; // fuzzed, old value = 0.181471
	FUZZ s.mbond.mbe5 = 0.156193; // fuzzed, old value = 0.150696
	FUZZ s.mbond.mbe6 = 0.224181; // fuzzed, old value = 0.214467
	FUZZ s.mbond.mbe7 = 0.413945; // fuzzed, old value = 0.409692
	FUZZ s.mbond.mbe_def = 0.519528; // fuzzed, old value = 0.505000
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.369505; // fuzzed, old value = 0.362988
	FUZZ s.mbond.DoubleRightLengthTresh = 0.304404; // fuzzed, old value = 0.300957
	FUZZ s.mbond.TripleLeftLengthTresh = 0.254558; // fuzzed, old value = 0.250670
	FUZZ s.mbond.TripleRightLengthTresh = 0.236216; // fuzzed, old value = 0.237051
	FUZZ s.mbond.Case1LengthTresh = 94.473679; // fuzzed, old value = 96.038663
	FUZZ s.mbond.Case1Factor = 0.394970; // fuzzed, old value = 0.414420
	FUZZ s.mbond.Case2LengthTresh = 89.005933; // fuzzed, old value = 85.787621
	FUZZ s.mbond.Case2Factor = 0.676557; // fuzzed, old value = 0.676897
	FUZZ s.mbond.Case3Factor = 0.992474; // fuzzed, old value = 0.955388
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.103365; // fuzzed, old value = 0.105331
	FUZZ s.skeleton.BaseSmallErr = 0.160245; // fuzzed, old value = 0.158102
	FUZZ s.skeleton.ShortBondLen = 21; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.334081; // fuzzed, old value = 0.320851
	FUZZ s.skeleton.MediumBondLen = 88; // fuzzed, old value = 91
	FUZZ s.skeleton.MediumMul = 0.161867; // fuzzed, old value = 0.165673
	FUZZ s.skeleton.MediumSmallErr = 0.138174; // fuzzed, old value = 0.131925
	FUZZ s.skeleton.LongBondLen = 95; // fuzzed, old value = 95
	FUZZ s.skeleton.LongMul = 0.150246; // fuzzed, old value = 0.151792
	FUZZ s.skeleton.LongSmallErr = 0.062965; // fuzzed, old value = 0.060082
	FUZZ s.skeleton.BrokenRepairFactor = 3.388874; // fuzzed, old value = 3.295135
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.902884; // fuzzed, old value = 0.899700
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.798138; // fuzzed, old value = 2.704543
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.198789; // fuzzed, old value = 0.197811
	FUZZ s.skeleton.DissolveMinErr = 0.170569; // fuzzed, old value = 0.178492
	FUZZ s.skeleton.ConnectBlockS = 9.833995; // fuzzed, old value = 9.720539
	FUZZ s.skeleton.ConnectFactor = 2.027852; // fuzzed, old value = 2.048454
	FUZZ s.skeleton.JoinVerticiesConst = 0.097398; // fuzzed, old value = 0.102113
	FUZZ s.skeleton.DissolveConst = 0.093940; // fuzzed, old value = 0.093752
	FUZZ s.skeleton.Dissolve2Const = 0.188921; // fuzzed, old value = 0.192711
	FUZZ s.skeleton.Join2Const = 0.286146; // fuzzed, old value = 0.286231
	FUZZ s.skeleton.Join3Const = 0.190007; // fuzzed, old value = 0.198023
	FUZZ s.skeleton.DistTreshLimFactor = 2.034017; // fuzzed, old value = 1.968443
	FUZZ s.skeleton.SlopeFact1 = 0.094975; // fuzzed, old value = 0.096790
	FUZZ s.skeleton.SlopeFact2 = 0.173540; // fuzzed, old value = 0.174880
	FUZZ s.skeleton.ShrinkEps = 0.133261; // fuzzed, old value = 0.139416
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.096133; // fuzzed, old value = 0.096091
	FUZZ s.routines.Circle_GapMax = 1.072875; // fuzzed, old value = 1.073493
	FUZZ s.routines.Circle_RMax = 2.412228; // fuzzed, old value = 2.317711
	FUZZ s.routines.Circle_AvgRadius = 0.000102; // fuzzed, old value = 0.000100
	FUZZ s.routines.Circle_MaxRatio = 0.292861; // fuzzed, old value = 0.294712
	FUZZ s.routines.Algebra_IntersectionEps = 0.011089; // fuzzed, old value = 0.011280
	FUZZ s.routines.Algebra_SameLineEps = 0.229721; // fuzzed, old value = 0.229813
	FUZZ s.routines.Approx_Eps1 = 1.114736; // fuzzed, old value = 1.103166
	FUZZ s.routines.Approx_Eps2 = 0.853248; // fuzzed, old value = 0.850123
	FUZZ s.routines.Approx_CalcLineTresh = 0.945804; // fuzzed, old value = 0.970598
	FUZZ s.routines.Contour_Eps1 = 0.975754; // fuzzed, old value = 0.998267
	FUZZ s.routines.Contour_Eps2 = 0.682406; // fuzzed, old value = 0.701048

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.751391; // fuzzed, old value = 2.884470
	FUZZ s.wbe.SingleDownAngleMax = 43.151557; // fuzzed, old value = 44.022481
	FUZZ s.wbe.SingleDownDistancesMax = 10.024443; // fuzzed, old value = 10.309579
	FUZZ s.wbe.SingleDownLengthMax = 49.693731; // fuzzed, old value = 49.263221
	FUZZ s.wbe.SingleUpRatioEps = 1.640030; // fuzzed, old value = 1.588753
	FUZZ s.wbe.SingleUpDefCoeff = 0.289574; // fuzzed, old value = 0.289467
	FUZZ s.wbe.SingleUpIncCoeff = 0.491721; // fuzzed, old value = 0.482375
	FUZZ s.wbe.SingleUpIncLengthTresh = 36.262785; // fuzzed, old value = 35.403863
	FUZZ s.wbe.SingleUpInterpolateEps = 0.064918; // fuzzed, old value = 0.066340
	FUZZ s.wbe.SingleUpMagicAddition = 0.244908; // fuzzed, old value = 0.246178
	FUZZ s.wbe.SingleUpS2Divisor = 1.398371; // fuzzed, old value = 1.398121
	FUZZ s.wbe.SingleUpMinATresh = 1.720929; // fuzzed, old value = 1.727093
	FUZZ s.wbe.SingleUpSquareRatio = 0.684612; // fuzzed, old value = 0.686944
	FUZZ s.wbe.SingleUpAngleTresh = 0.067938; // fuzzed, old value = 0.067796
	FUZZ s.wbe.SomeTresh = 0.104934; // fuzzed, old value = 0.105018
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = false; // fuzzed, old value = true
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.014210; // fuzzed, old value = 1.005147
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.177124; // fuzzed, old value = 1.165551
	FUZZ s.characters.WriteEasyFactor = 0.992805; // fuzzed, old value = 0.954994
	FUZZ s.characters.WriteVeryEasyFactor = 0.948974; // fuzzed, old value = 0.937590
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.194507; // fuzzed, old value = 3.100596
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.059400; // fuzzed, old value = 3.151090
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.096811; // fuzzed, old value = 0.100272
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.609470; // fuzzed, old value = 2.587364
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.738476; // fuzzed, old value = 3.663155
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.927528; // fuzzed, old value = 0.886674
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.294104; // fuzzed, old value = 0.300252
	FUZZ s.characters.HW_Line = 1.537709; // fuzzed, old value = 1.514736
	FUZZ s.characters.HW_F = 3.332573; // fuzzed, old value = 3.499237
	FUZZ s.characters.HW_Tricky = 3.014611; // fuzzed, old value = 3.008418
	FUZZ s.characters.HW_Hard = 4.350860; // fuzzed, old value = 4.191641
	FUZZ s.characters.HW_Other = 3.704123; // fuzzed, old value = 3.636595

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.522418; // fuzzed, old value = 0.506318
	FUZZ s.csr.DeleteBadTriangles = 1.926071; // fuzzed, old value = 1.893943
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.666288; // fuzzed, old value = 1.656589

	FUZZ s.graph.MinimalDistTresh = 2.069352; // fuzzed, old value = 1.977594
	FUZZ s.graph.RatioSub = 1.036255; // fuzzed, old value = 1.004634
	FUZZ s.graph.RatioTresh = 0.449162; // fuzzed, old value = 0.455552

	FUZZ s.utils.SlashLineDensity = 0.398294; // fuzzed, old value = 0.417596
	FUZZ s.utils.TestPlusDensity = 0.436384; // fuzzed, old value = 0.425760
	FUZZ s.utils.TestPlusSq = 0.445527; // fuzzed, old value = 0.431653
	FUZZ s.utils.TestMinusRatio = 0.338805; // fuzzed, old value = 0.351097
	FUZZ s.utils.TestMinusDensity = 0.592761; // fuzzed, old value = 0.590664
	FUZZ s.utils.TestMinusHeightFactor = 0.888058; // fuzzed, old value = 0.865960

	FUZZ s.separator.hu_1_1 = 0.215473; // fuzzed, old value = 0.205260
	FUZZ s.separator.hu_1_2 = 0.076792; // fuzzed, old value = 0.073316
	FUZZ s.separator.hu_0_1 = 0.205034; // fuzzed, old value = 0.211154
	FUZZ s.separator.hu_1_3 = 0.087845; // fuzzed, old value = 0.086343
	FUZZ s.separator.hu_0_2 = 0.208118; // fuzzed, old value = 0.213270
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.547635; // fuzzed, old value = 0.536738
	FUZZ s.separator.capHeightMax = 1.389777; // fuzzed, old value = 1.428743
	FUZZ s.separator.gdConst = 1.563537; // fuzzed, old value = 1.644978
	FUZZ s.separator.SurfCoef = 3.104292; // fuzzed, old value = 3.062094
	FUZZ s.separator.capHeightRatio = 0.262520; // fuzzed, old value = 0.268138
	FUZZ s.separator.capHeightRatio2 = 2.015533; // fuzzed, old value = 1.950693
	FUZZ s.separator.getRatio1 = 1.046155; // fuzzed, old value = 1.021081
	FUZZ s.separator.getRatio2 = 1.245533; // fuzzed, old value = 1.212365
	FUZZ s.separator.testSlashLine1 = 2.940416; // fuzzed, old value = 2.873200
	FUZZ s.separator.testSlashLine2 = 2.694239; // fuzzed, old value = 2.783841
	FUZZ s.separator.minDensity = 0.207364; // fuzzed, old value = 0.197599
	FUZZ s.separator.maxDensity = 0.889576; // fuzzed, old value = 0.914575
	FUZZ s.separator.extCapHeightMin = 0.301238; // fuzzed, old value = 0.298018
	FUZZ s.separator.extCapHeightMax = 2.173322; // fuzzed, old value = 2.202968
	FUZZ s.separator.extRatioMin = 0.317737; // fuzzed, old value = 0.318563
	FUZZ s.separator.extRatioMax = 1.549829; // fuzzed, old value = 1.589661
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.399110; // fuzzed, old value = 0.414514
	FUZZ s.labels.weightUnderline = 0.292984; // fuzzed, old value = 0.305772
	FUZZ s.labels.ratioBase = 0.808756; // fuzzed, old value = 0.827762
	FUZZ s.labels.ratioWeight = 0.273840; // fuzzed, old value = 0.282586
	FUZZ s.labels.adjustDec = 1.281131; // fuzzed, old value = 1.271521
	FUZZ s.labels.adjustInc = 0.787364; // fuzzed, old value = 0.773808
	FUZZ s.labels.sameLineEps = 0.119902; // fuzzed, old value = 0.125695
	FUZZ s.labels.heightRatio = 0.793881; // fuzzed, old value = 0.820358
	FUZZ s.labels.medHeightFactor = 0.505379; // fuzzed, old value = 0.485083
	FUZZ s.labels.capHeightError = 0.503738; // fuzzed, old value = 0.519704

	FUZZ s.lcomb.MaximalSymbolDistance = 2.627132; // fuzzed, old value = 2.631569
	FUZZ s.lcomb.TestSlashLineEps = 3.280245; // fuzzed, old value = 3.138795
	FUZZ s.lcomb.TestMinHeightFactor = 0.553344; // fuzzed, old value = 0.527250
	FUZZ s.lcomb.TestMaxHeightFactor = 1.061835; // fuzzed, old value = 1.047742
	FUZZ s.lcomb.RectHeightRatio = 0.472451; // fuzzed, old value = 0.469624
	FUZZ s.lcomb.H1SuperscriptSpace = 1.077203; // fuzzed, old value = 1.103145
	FUZZ s.lcomb.H2LowercaseSpace = 0.497997; // fuzzed, old value = 0.515508
	FUZZ s.lcomb.H3LowercaseSpace = 0.437745; // fuzzed, old value = 0.434194
	FUZZ s.lcomb.H4SubscriptSpace = 0.512326; // fuzzed, old value = 0.534505
	FUZZ s.lcomb.FillLabelFactor1 = 0.524486; // fuzzed, old value = 0.524573
	FUZZ s.lcomb.FillLabelFactor2 = 0.545255; // fuzzed, old value = 0.555762
}
