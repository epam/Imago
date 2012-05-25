
void updateSettingsScanned(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.316012; // fuzzed, old value = 0.312680
	FUZZ s.molecule.LengthFactor_medium = 0.422606; // fuzzed, old value = 0.422714
	FUZZ s.molecule.LengthFactor_default = 0.464193; // fuzzed, old value = 0.457786
	FUZZ s.molecule.LengthValue_long = 106.513793; // fuzzed, old value = 105.745126
	FUZZ s.molecule.LengthValue_medium = 81.716338; // fuzzed, old value = 82.325241
	FUZZ s.molecule.SpaceMultiply = 1.500185; // fuzzed, old value = 1.505538
	FUZZ s.molecule.AngleTreshold = 0.253302; // fuzzed, old value = 0.249699
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.501566; // fuzzed, old value = 17.577485
	FUZZ s.estimation.LineThickness = 5.753109; // fuzzed, old value = 5.687835
	FUZZ s.estimation.AvgBondLength = 31.134817; // fuzzed, old value = 31.266196
	FUZZ s.estimation.AddVertexEps = 5.363650; // fuzzed, old value = 5.344452
	FUZZ s.estimation.MaxSymRatio = 1.115908; // fuzzed, old value = 1.110051
	FUZZ s.estimation.MinSymRatio = 0.355861; // fuzzed, old value = 0.353041
	FUZZ s.estimation.ParLinesEps = 0.537820; // fuzzed, old value = 0.531078
	FUZZ s.estimation.SymHeightErr = 26.385009; // fuzzed, old value = 26.742640
	FUZZ s.estimation.CapitalHeightError = 0.810590; // fuzzed, old value = 0.805828
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.375461; // fuzzed, old value = 0.378582
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 120; // fuzzed, old value = 120
	FUZZ s.mbond.LongErr = 0.352936; // fuzzed, old value = 0.353499
	FUZZ s.mbond.MediumBond = 94; // fuzzed, old value = 93
	FUZZ s.mbond.MediumErr = 0.422021; // fuzzed, old value = 0.424838
	FUZZ s.mbond.DefaultErr = 0.627944; // fuzzed, old value = 0.623609
	FUZZ s.mbond.ParBondsEps = 0.344995; // fuzzed, old value = 0.343029
	FUZZ s.mbond.DoubleRatioTresh = 7.076452; // fuzzed, old value = 7.120958
	FUZZ s.mbond.DoubleCoef = 0.083277; // fuzzed, old value = 0.083880
	FUZZ s.mbond.DoubleMagic1 = 0.896917; // fuzzed, old value = 0.885687
	FUZZ s.mbond.DoubleMagic2 = 0.951504; // fuzzed, old value = 0.963368
	FUZZ s.mbond.DoubleTreshMin = 0.099218; // fuzzed, old value = 0.100571
	FUZZ s.mbond.DoubleTreshMax = 0.795053; // fuzzed, old value = 0.794882
	FUZZ s.mbond.MaxLen1 = 152.872157; // fuzzed, old value = 153.218157
	FUZZ s.mbond.MaxLen2 = 115.763409; // fuzzed, old value = 116.148307
	FUZZ s.mbond.MaxLen3 = 107.611425; // fuzzed, old value = 108.809015
	FUZZ s.mbond.MaxLen4 = 122.295208; // fuzzed, old value = 123.717600
	FUZZ s.mbond.MaxLen5 = 80.483493; // fuzzed, old value = 80.153664
	FUZZ s.mbond.MinLen1 = 83.411028; // fuzzed, old value = 82.623212
	FUZZ s.mbond.MinLen2 = 73.911842; // fuzzed, old value = 74.847892
	FUZZ s.mbond.mbe1 = 0.075822; // fuzzed, old value = 0.076355
	FUZZ s.mbond.mbe2 = 0.155884; // fuzzed, old value = 0.157922
	FUZZ s.mbond.mbe3 = 0.198548; // fuzzed, old value = 0.200264
	FUZZ s.mbond.mbe4 = 0.183109; // fuzzed, old value = 0.181623
	FUZZ s.mbond.mbe5 = 0.153044; // fuzzed, old value = 0.152260
	FUZZ s.mbond.mbe6 = 0.215261; // fuzzed, old value = 0.217858
	FUZZ s.mbond.mbe7 = 0.422149; // fuzzed, old value = 0.423682
	FUZZ s.mbond.mbe_def = 0.509065; // fuzzed, old value = 0.509344
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.349171; // fuzzed, old value = 0.344517
	FUZZ s.mbond.DoubleRightLengthTresh = 0.312950; // fuzzed, old value = 0.308353
	FUZZ s.mbond.TripleLeftLengthTresh = 0.262788; // fuzzed, old value = 0.261501
	FUZZ s.mbond.TripleRightLengthTresh = 0.238341; // fuzzed, old value = 0.240136
	FUZZ s.mbond.Case1LengthTresh = 102.557357; // fuzzed, old value = 103.494053
	FUZZ s.mbond.Case1Factor = 0.445100; // fuzzed, old value = 0.447583
	FUZZ s.mbond.Case2LengthTresh = 80.120482; // fuzzed, old value = 80.514899
	FUZZ s.mbond.Case2Factor = 0.674543; // fuzzed, old value = 0.666395
	FUZZ s.mbond.Case3Factor = 0.862480; // fuzzed, old value = 0.861618
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.098817; // fuzzed, old value = 0.099101
	FUZZ s.skeleton.BaseSmallErr = 0.145356; // fuzzed, old value = 0.144246
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.313137; // fuzzed, old value = 0.309409
	FUZZ s.skeleton.MediumBondLen = 85; // fuzzed, old value = 86
	FUZZ s.skeleton.MediumMul = 0.170226; // fuzzed, old value = 0.168288
	FUZZ s.skeleton.MediumSmallErr = 0.133982; // fuzzed, old value = 0.132980
	FUZZ s.skeleton.LongBondLen = 104; // fuzzed, old value = 103
	FUZZ s.skeleton.LongMul = 0.143594; // fuzzed, old value = 0.144392
	FUZZ s.skeleton.LongSmallErr = 0.059830; // fuzzed, old value = 0.060447
	FUZZ s.skeleton.BrokenRepairFactor = 3.148906; // fuzzed, old value = 3.118944
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.986058; // fuzzed, old value = 0.998709
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.538955; // fuzzed, old value = 2.528271
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.186823; // fuzzed, old value = 0.188021
	FUZZ s.skeleton.DissolveMinErr = 0.178827; // fuzzed, old value = 0.177181
	FUZZ s.skeleton.ConnectBlockS = 9.861923; // fuzzed, old value = 9.731788
	FUZZ s.skeleton.ConnectFactor = 2.110934; // fuzzed, old value = 2.100716
	FUZZ s.skeleton.JoinVerticiesConst = 0.105082; // fuzzed, old value = 0.103701
	FUZZ s.skeleton.DissolveConst = 0.094846; // fuzzed, old value = 0.093740
	FUZZ s.skeleton.Dissolve2Const = 0.205404; // fuzzed, old value = 0.202972
	FUZZ s.skeleton.Join2Const = 0.306431; // fuzzed, old value = 0.310103
	FUZZ s.skeleton.Join3Const = 0.198258; // fuzzed, old value = 0.195593
	FUZZ s.skeleton.DistTreshLimFactor = 1.975177; // fuzzed, old value = 1.999941
	FUZZ s.skeleton.SlopeFact1 = 0.102952; // fuzzed, old value = 0.101699
	FUZZ s.skeleton.SlopeFact2 = 0.179077; // fuzzed, old value = 0.179138
	FUZZ s.skeleton.ShrinkEps = 0.136528; // fuzzed, old value = 0.134665
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.096128; // fuzzed, old value = 0.096321
	FUZZ s.routines.Circle_GapMax = 1.032678; // fuzzed, old value = 1.044577
	FUZZ s.routines.Circle_RMax = 2.169911; // fuzzed, old value = 2.155625
	FUZZ s.routines.Circle_AvgRadius = 0.000104; // fuzzed, old value = 0.000103
	FUZZ s.routines.Circle_MaxRatio = 0.327961; // fuzzed, old value = 0.330067
	FUZZ s.routines.Algebra_IntersectionEps = 0.011097; // fuzzed, old value = 0.010982
	FUZZ s.routines.Algebra_SameLineEps = 0.228698; // fuzzed, old value = 0.225346
	FUZZ s.routines.Approx_Eps1 = 1.149349; // fuzzed, old value = 1.144582
	FUZZ s.routines.Approx_Eps2 = 0.813337; // fuzzed, old value = 0.820181
	FUZZ s.routines.Approx_CalcLineTresh = 0.913179; // fuzzed, old value = 0.922307
	FUZZ s.routines.Contour_Eps1 = 1.016163; // fuzzed, old value = 1.030649
	FUZZ s.routines.Contour_Eps2 = 0.696015; // fuzzed, old value = 0.697402

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.999070; // fuzzed, old value = 2.963643
	FUZZ s.wbe.SingleDownAngleMax = 45.746928; // fuzzed, old value = 46.300486
	FUZZ s.wbe.SingleDownDistancesMax = 10.546371; // fuzzed, old value = 10.468702
	FUZZ s.wbe.SingleDownLengthMax = 46.347715; // fuzzed, old value = 46.242316
	FUZZ s.wbe.SingleUpRatioEps = 1.664250; // fuzzed, old value = 1.654354
	FUZZ s.wbe.SingleUpDefCoeff = 0.287418; // fuzzed, old value = 0.289348
	FUZZ s.wbe.SingleUpIncCoeff = 0.453702; // fuzzed, old value = 0.448766
	FUZZ s.wbe.SingleUpIncLengthTresh = 35.296420; // fuzzed, old value = 35.703441
	FUZZ s.wbe.SingleUpInterpolateEps = 0.062785; // fuzzed, old value = 0.062180
	FUZZ s.wbe.SingleUpMagicAddition = 0.233715; // fuzzed, old value = 0.235520
	FUZZ s.wbe.SingleUpS2Divisor = 1.404760; // fuzzed, old value = 1.421432
	FUZZ s.wbe.SingleUpMinATresh = 1.643360; // fuzzed, old value = 1.645076
	FUZZ s.wbe.SingleUpSquareRatio = 0.658409; // fuzzed, old value = 0.667113
	FUZZ s.wbe.SingleUpAngleTresh = 0.065895; // fuzzed, old value = 0.066476
	FUZZ s.wbe.SomeTresh = 0.103816; // fuzzed, old value = 0.103502
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = false; // fuzzed, old value = true
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.063570; // fuzzed, old value = 1.063587
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.162193; // fuzzed, old value = 1.151430
	FUZZ s.characters.WriteEasyFactor = 0.978644; // fuzzed, old value = 0.977022
	FUZZ s.characters.WriteVeryEasyFactor = 0.940838; // fuzzed, old value = 0.929563
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.292300; // fuzzed, old value = 3.332524
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.211554; // fuzzed, old value = 3.247586
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.104058; // fuzzed, old value = 0.105269
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.657348; // fuzzed, old value = 2.649531
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.535607; // fuzzed, old value = 3.562179
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.912464; // fuzzed, old value = 0.919815
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.282862; // fuzzed, old value = 0.284952
	FUZZ s.characters.HW_Line = 1.637154; // fuzzed, old value = 1.641786
	FUZZ s.characters.HW_F = 3.324046; // fuzzed, old value = 3.330216
	FUZZ s.characters.HW_Tricky = 2.778671; // fuzzed, old value = 2.738081
	FUZZ s.characters.HW_Hard = 4.163263; // fuzzed, old value = 4.155868
	FUZZ s.characters.HW_Other = 3.602790; // fuzzed, old value = 3.647382

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.470698; // fuzzed, old value = 0.470344
	FUZZ s.csr.DeleteBadTriangles = 1.907571; // fuzzed, old value = 1.908946
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.637752; // fuzzed, old value = 1.628071

	FUZZ s.graph.MinimalDistTresh = 1.912639; // fuzzed, old value = 1.887267
	FUZZ s.graph.RatioSub = 0.986857; // fuzzed, old value = 0.995837
	FUZZ s.graph.RatioTresh = 0.446347; // fuzzed, old value = 0.452384

	FUZZ s.utils.SlashLineDensity = 0.448328; // fuzzed, old value = 0.450761
	FUZZ s.utils.TestPlusDensity = 0.403077; // fuzzed, old value = 0.402547
	FUZZ s.utils.TestPlusSq = 0.400018; // fuzzed, old value = 0.396780
	FUZZ s.utils.TestMinusRatio = 0.366870; // fuzzed, old value = 0.372173
	FUZZ s.utils.TestMinusDensity = 0.649586; // fuzzed, old value = 0.658580
	FUZZ s.utils.TestMinusHeightFactor = 0.853522; // fuzzed, old value = 0.856734

	FUZZ s.separator.hu_1_1 = 0.209920; // fuzzed, old value = 0.209682
	FUZZ s.separator.hu_1_2 = 0.074659; // fuzzed, old value = 0.075512
	FUZZ s.separator.hu_0_1 = 0.228817; // fuzzed, old value = 0.232016
	FUZZ s.separator.hu_1_3 = 0.078158; // fuzzed, old value = 0.079154
	FUZZ s.separator.hu_0_2 = 0.236557; // fuzzed, old value = 0.235494
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.562051; // fuzzed, old value = 0.562693
	FUZZ s.separator.capHeightMax = 1.401674; // fuzzed, old value = 1.389839
	FUZZ s.separator.gdConst = 1.572424; // fuzzed, old value = 1.573590
	FUZZ s.separator.SurfCoef = 2.863376; // fuzzed, old value = 2.873192
	FUZZ s.separator.capHeightRatio = 0.251985; // fuzzed, old value = 0.253290
	FUZZ s.separator.capHeightRatio2 = 1.974941; // fuzzed, old value = 1.999732
	FUZZ s.separator.getRatio1 = 1.081847; // fuzzed, old value = 1.074439
	FUZZ s.separator.getRatio2 = 1.137191; // fuzzed, old value = 1.136332
	FUZZ s.separator.testSlashLine1 = 2.839112; // fuzzed, old value = 2.880112
	FUZZ s.separator.testSlashLine2 = 2.836950; // fuzzed, old value = 2.863996
	FUZZ s.separator.minDensity = 0.193435; // fuzzed, old value = 0.194810
	FUZZ s.separator.maxDensity = 0.855132; // fuzzed, old value = 0.862146
	FUZZ s.separator.extCapHeightMin = 0.300755; // fuzzed, old value = 0.299912
	FUZZ s.separator.extCapHeightMax = 2.191625; // fuzzed, old value = 2.182896
	FUZZ s.separator.extRatioMin = 0.302133; // fuzzed, old value = 0.298597
	FUZZ s.separator.extRatioMax = 1.583431; // fuzzed, old value = 1.601624
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.432232; // fuzzed, old value = 0.437676
	FUZZ s.labels.weightUnderline = 0.318194; // fuzzed, old value = 0.316051
	FUZZ s.labels.ratioBase = 0.822552; // fuzzed, old value = 0.823109
	FUZZ s.labels.ratioWeight = 0.274282; // fuzzed, old value = 0.273495
	FUZZ s.labels.adjustDec = 1.233285; // fuzzed, old value = 1.235308
	FUZZ s.labels.adjustInc = 0.840761; // fuzzed, old value = 0.832994
	FUZZ s.labels.sameLineEps = 0.119758; // fuzzed, old value = 0.118385
	FUZZ s.labels.heightRatio = 0.836327; // fuzzed, old value = 0.826356
	FUZZ s.labels.medHeightFactor = 0.499104; // fuzzed, old value = 0.501382
	FUZZ s.labels.capHeightError = 0.534310; // fuzzed, old value = 0.536500

	FUZZ s.lcomb.MaximalSymbolDistance = 2.550223; // fuzzed, old value = 2.569183
	FUZZ s.lcomb.TestSlashLineEps = 3.072363; // fuzzed, old value = 3.093071
	FUZZ s.lcomb.TestMinHeightFactor = 0.494941; // fuzzed, old value = 0.500579
	FUZZ s.lcomb.TestMaxHeightFactor = 1.152213; // fuzzed, old value = 1.157559
	FUZZ s.lcomb.RectHeightRatio = 0.499803; // fuzzed, old value = 0.502094
	FUZZ s.lcomb.H1SuperscriptSpace = 1.221709; // fuzzed, old value = 1.205005
	FUZZ s.lcomb.H2LowercaseSpace = 0.514884; // fuzzed, old value = 0.508709
	FUZZ s.lcomb.H3LowercaseSpace = 0.452245; // fuzzed, old value = 0.455114
	FUZZ s.lcomb.H4SubscriptSpace = 0.530046; // fuzzed, old value = 0.533377
	FUZZ s.lcomb.FillLabelFactor1 = 0.552735; // fuzzed, old value = 0.545797
	FUZZ s.lcomb.FillLabelFactor2 = 0.533105; // fuzzed, old value = 0.536617
}
