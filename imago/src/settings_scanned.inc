
void updateSettingsScanned(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.311649; // fuzzed, old value = 0.312680
	FUZZ s.molecule.LengthFactor_medium = 0.420123; // fuzzed, old value = 0.422714
	FUZZ s.molecule.LengthFactor_default = 0.454839; // fuzzed, old value = 0.457786
	FUZZ s.molecule.LengthValue_long = 106.424626; // fuzzed, old value = 105.745126
	FUZZ s.molecule.LengthValue_medium = 81.541849; // fuzzed, old value = 82.325241
	FUZZ s.molecule.SpaceMultiply = 1.490449; // fuzzed, old value = 1.505538
	FUZZ s.molecule.AngleTreshold = 0.250358; // fuzzed, old value = 0.249699
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.518045; // fuzzed, old value = 17.577485
	FUZZ s.estimation.LineThickness = 5.629992; // fuzzed, old value = 5.687835
	FUZZ s.estimation.AvgBondLength = 31.470828; // fuzzed, old value = 31.266196
	FUZZ s.estimation.AddVertexEps = 5.269472; // fuzzed, old value = 5.344452
	FUZZ s.estimation.MaxSymRatio = 1.119078; // fuzzed, old value = 1.110051
	FUZZ s.estimation.MinSymRatio = 0.348766; // fuzzed, old value = 0.353041
	FUZZ s.estimation.ParLinesEps = 0.526932; // fuzzed, old value = 0.531078
	FUZZ s.estimation.SymHeightErr = 26.919748; // fuzzed, old value = 26.742640
	FUZZ s.estimation.CapitalHeightError = 0.799480; // fuzzed, old value = 0.805828
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.383539; // fuzzed, old value = 0.378582
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 122; // fuzzed, old value = 120
	FUZZ s.mbond.LongErr = 0.352730; // fuzzed, old value = 0.353499
	FUZZ s.mbond.MediumBond = 93; // fuzzed, old value = 93
	FUZZ s.mbond.MediumErr = 0.421260; // fuzzed, old value = 0.424838
	FUZZ s.mbond.DefaultErr = 0.630216; // fuzzed, old value = 0.623609
	FUZZ s.mbond.ParBondsEps = 0.340680; // fuzzed, old value = 0.343029
	FUZZ s.mbond.DoubleRatioTresh = 7.099681; // fuzzed, old value = 7.120958
	FUZZ s.mbond.DoubleCoef = 0.083440; // fuzzed, old value = 0.083880
	FUZZ s.mbond.DoubleMagic1 = 0.891677; // fuzzed, old value = 0.885687
	FUZZ s.mbond.DoubleMagic2 = 0.954124; // fuzzed, old value = 0.963368
	FUZZ s.mbond.DoubleTreshMin = 0.101513; // fuzzed, old value = 0.100571
	FUZZ s.mbond.DoubleTreshMax = 0.795855; // fuzzed, old value = 0.794882
	FUZZ s.mbond.MaxLen1 = 151.577095; // fuzzed, old value = 153.218157
	FUZZ s.mbond.MaxLen2 = 116.101358; // fuzzed, old value = 116.148307
	FUZZ s.mbond.MaxLen3 = 110.310448; // fuzzed, old value = 108.809015
	FUZZ s.mbond.MaxLen4 = 124.325352; // fuzzed, old value = 123.717600
	FUZZ s.mbond.MaxLen5 = 80.806828; // fuzzed, old value = 80.153664
	FUZZ s.mbond.MinLen1 = 82.663191; // fuzzed, old value = 82.623212
	FUZZ s.mbond.MinLen2 = 74.623362; // fuzzed, old value = 74.847892
	FUZZ s.mbond.mbe1 = 0.077342; // fuzzed, old value = 0.076355
	FUZZ s.mbond.mbe2 = 0.158806; // fuzzed, old value = 0.157922
	FUZZ s.mbond.mbe3 = 0.198380; // fuzzed, old value = 0.200264
	FUZZ s.mbond.mbe4 = 0.181354; // fuzzed, old value = 0.181623
	FUZZ s.mbond.mbe5 = 0.153057; // fuzzed, old value = 0.152260
	FUZZ s.mbond.mbe6 = 0.218043; // fuzzed, old value = 0.217858
	FUZZ s.mbond.mbe7 = 0.419415; // fuzzed, old value = 0.423682
	FUZZ s.mbond.mbe_def = 0.514630; // fuzzed, old value = 0.509344
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.349566; // fuzzed, old value = 0.344517
	FUZZ s.mbond.DoubleRightLengthTresh = 0.309546; // fuzzed, old value = 0.308353
	FUZZ s.mbond.TripleLeftLengthTresh = 0.258454; // fuzzed, old value = 0.261501
	FUZZ s.mbond.TripleRightLengthTresh = 0.237428; // fuzzed, old value = 0.240136
	FUZZ s.mbond.Case1LengthTresh = 102.516518; // fuzzed, old value = 103.494053
	FUZZ s.mbond.Case1Factor = 0.451161; // fuzzed, old value = 0.447583
	FUZZ s.mbond.Case2LengthTresh = 79.426521; // fuzzed, old value = 80.514899
	FUZZ s.mbond.Case2Factor = 0.669606; // fuzzed, old value = 0.666395
	FUZZ s.mbond.Case3Factor = 0.857105; // fuzzed, old value = 0.861618
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.099697; // fuzzed, old value = 0.099101
	FUZZ s.skeleton.BaseSmallErr = 0.143694; // fuzzed, old value = 0.144246
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.310346; // fuzzed, old value = 0.309409
	FUZZ s.skeleton.MediumBondLen = 85; // fuzzed, old value = 86
	FUZZ s.skeleton.MediumMul = 0.168521; // fuzzed, old value = 0.168288
	FUZZ s.skeleton.MediumSmallErr = 0.133501; // fuzzed, old value = 0.132980
	FUZZ s.skeleton.LongBondLen = 104; // fuzzed, old value = 103
	FUZZ s.skeleton.LongMul = 0.143790; // fuzzed, old value = 0.144392
	FUZZ s.skeleton.LongSmallErr = 0.059568; // fuzzed, old value = 0.060447
	FUZZ s.skeleton.BrokenRepairFactor = 3.156813; // fuzzed, old value = 3.118944
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.983809; // fuzzed, old value = 0.998709
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.561498; // fuzzed, old value = 2.528271
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.187219; // fuzzed, old value = 0.188021
	FUZZ s.skeleton.DissolveMinErr = 0.175483; // fuzzed, old value = 0.177181
	FUZZ s.skeleton.ConnectBlockS = 9.786803; // fuzzed, old value = 9.731788
	FUZZ s.skeleton.ConnectFactor = 2.073564; // fuzzed, old value = 2.100716
	FUZZ s.skeleton.JoinVerticiesConst = 0.102810; // fuzzed, old value = 0.103701
	FUZZ s.skeleton.DissolveConst = 0.093520; // fuzzed, old value = 0.093740
	FUZZ s.skeleton.Dissolve2Const = 0.205220; // fuzzed, old value = 0.202972
	FUZZ s.skeleton.Join2Const = 0.313131; // fuzzed, old value = 0.310103
	FUZZ s.skeleton.Join3Const = 0.192778; // fuzzed, old value = 0.195593
	FUZZ s.skeleton.DistTreshLimFactor = 2.021733; // fuzzed, old value = 1.999941
	FUZZ s.skeleton.SlopeFact1 = 0.102299; // fuzzed, old value = 0.101699
	FUZZ s.skeleton.SlopeFact2 = 0.180094; // fuzzed, old value = 0.179138
	FUZZ s.skeleton.ShrinkEps = 0.132991; // fuzzed, old value = 0.134665
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.097453; // fuzzed, old value = 0.096321
	FUZZ s.routines.Circle_GapMax = 1.029887; // fuzzed, old value = 1.044577
	FUZZ s.routines.Circle_RMax = 2.186075; // fuzzed, old value = 2.155625
	FUZZ s.routines.Circle_AvgRadius = 0.000103; // fuzzed, old value = 0.000103
	FUZZ s.routines.Circle_MaxRatio = 0.334554; // fuzzed, old value = 0.330067
	FUZZ s.routines.Algebra_IntersectionEps = 0.010862; // fuzzed, old value = 0.010982
	FUZZ s.routines.Algebra_SameLineEps = 0.225213; // fuzzed, old value = 0.225346
	FUZZ s.routines.Approx_Eps1 = 1.148458; // fuzzed, old value = 1.144582
	FUZZ s.routines.Approx_Eps2 = 0.824779; // fuzzed, old value = 0.820181
	FUZZ s.routines.Approx_CalcLineTresh = 0.925173; // fuzzed, old value = 0.922307
	FUZZ s.routines.Contour_Eps1 = 1.023683; // fuzzed, old value = 1.030649
	FUZZ s.routines.Contour_Eps2 = 0.707557; // fuzzed, old value = 0.697402

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.960774; // fuzzed, old value = 2.963643
	FUZZ s.wbe.SingleDownAngleMax = 46.567272; // fuzzed, old value = 46.300486
	FUZZ s.wbe.SingleDownDistancesMax = 10.449202; // fuzzed, old value = 10.468702
	FUZZ s.wbe.SingleDownLengthMax = 45.610748; // fuzzed, old value = 46.242316
	FUZZ s.wbe.SingleUpRatioEps = 1.673608; // fuzzed, old value = 1.654354
	FUZZ s.wbe.SingleUpDefCoeff = 0.287413; // fuzzed, old value = 0.289348
	FUZZ s.wbe.SingleUpIncCoeff = 0.443707; // fuzzed, old value = 0.448766
	FUZZ s.wbe.SingleUpIncLengthTresh = 35.944992; // fuzzed, old value = 35.703441
	FUZZ s.wbe.SingleUpInterpolateEps = 0.062055; // fuzzed, old value = 0.062180
	FUZZ s.wbe.SingleUpMagicAddition = 0.235238; // fuzzed, old value = 0.235520
	FUZZ s.wbe.SingleUpS2Divisor = 1.416347; // fuzzed, old value = 1.421432
	FUZZ s.wbe.SingleUpMinATresh = 1.657921; // fuzzed, old value = 1.645076
	FUZZ s.wbe.SingleUpSquareRatio = 0.662186; // fuzzed, old value = 0.667113
	FUZZ s.wbe.SingleUpAngleTresh = 0.065895; // fuzzed, old value = 0.066476
	FUZZ s.wbe.SomeTresh = 0.103638; // fuzzed, old value = 0.103502
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = true
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.054564; // fuzzed, old value = 1.063587
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.164659; // fuzzed, old value = 1.151430
	FUZZ s.characters.WriteEasyFactor = 0.969962; // fuzzed, old value = 0.977022
	FUZZ s.characters.WriteVeryEasyFactor = 0.922971; // fuzzed, old value = 0.929563
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.369359; // fuzzed, old value = 3.332524
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.288120; // fuzzed, old value = 3.247586
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.105768; // fuzzed, old value = 0.105269
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.665196; // fuzzed, old value = 2.649531
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.565031; // fuzzed, old value = 3.562179
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.919057; // fuzzed, old value = 0.919815
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.280731; // fuzzed, old value = 0.284952
	FUZZ s.characters.HW_Line = 1.654845; // fuzzed, old value = 1.641786
	FUZZ s.characters.HW_F = 3.328800; // fuzzed, old value = 3.330216
	FUZZ s.characters.HW_Tricky = 2.746245; // fuzzed, old value = 2.738081
	FUZZ s.characters.HW_Hard = 4.109807; // fuzzed, old value = 4.155868
	FUZZ s.characters.HW_Other = 3.628252; // fuzzed, old value = 3.647382

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.472676; // fuzzed, old value = 0.470344
	FUZZ s.csr.DeleteBadTriangles = 1.909377; // fuzzed, old value = 1.908946
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.614500; // fuzzed, old value = 1.628071

	FUZZ s.graph.MinimalDistTresh = 1.907699; // fuzzed, old value = 1.887267
	FUZZ s.graph.RatioSub = 0.990397; // fuzzed, old value = 0.995837
	FUZZ s.graph.RatioTresh = 0.448282; // fuzzed, old value = 0.452384

	FUZZ s.utils.SlashLineDensity = 0.446614; // fuzzed, old value = 0.450761
	FUZZ s.utils.TestPlusDensity = 0.404195; // fuzzed, old value = 0.402547
	FUZZ s.utils.TestPlusSq = 0.396912; // fuzzed, old value = 0.396780
	FUZZ s.utils.TestMinusRatio = 0.369875; // fuzzed, old value = 0.372173
	FUZZ s.utils.TestMinusDensity = 0.652001; // fuzzed, old value = 0.658580
	FUZZ s.utils.TestMinusHeightFactor = 0.845265; // fuzzed, old value = 0.856734

	FUZZ s.separator.hu_1_1 = 0.211970; // fuzzed, old value = 0.209682
	FUZZ s.separator.hu_1_2 = 0.075661; // fuzzed, old value = 0.075512
	FUZZ s.separator.hu_0_1 = 0.235061; // fuzzed, old value = 0.232016
	FUZZ s.separator.hu_1_3 = 0.078610; // fuzzed, old value = 0.079154
	FUZZ s.separator.hu_0_2 = 0.237449; // fuzzed, old value = 0.235494
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.560571; // fuzzed, old value = 0.562693
	FUZZ s.separator.capHeightMax = 1.391568; // fuzzed, old value = 1.389839
	FUZZ s.separator.gdConst = 1.569050; // fuzzed, old value = 1.573590
	FUZZ s.separator.SurfCoef = 2.911100; // fuzzed, old value = 2.873192
	FUZZ s.separator.capHeightRatio = 0.255720; // fuzzed, old value = 0.253290
	FUZZ s.separator.capHeightRatio2 = 2.008472; // fuzzed, old value = 1.999732
	FUZZ s.separator.getRatio1 = 1.073891; // fuzzed, old value = 1.074439
	FUZZ s.separator.getRatio2 = 1.132520; // fuzzed, old value = 1.136332
	FUZZ s.separator.testSlashLine1 = 2.908863; // fuzzed, old value = 2.880112
	FUZZ s.separator.testSlashLine2 = 2.845412; // fuzzed, old value = 2.863996
	FUZZ s.separator.minDensity = 0.193532; // fuzzed, old value = 0.194810
	FUZZ s.separator.maxDensity = 0.865331; // fuzzed, old value = 0.862146
	FUZZ s.separator.extCapHeightMin = 0.303826; // fuzzed, old value = 0.299912
	FUZZ s.separator.extCapHeightMax = 2.180521; // fuzzed, old value = 2.182896
	FUZZ s.separator.extRatioMin = 0.299102; // fuzzed, old value = 0.298597
	FUZZ s.separator.extRatioMax = 1.602931; // fuzzed, old value = 1.601624
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.440809; // fuzzed, old value = 0.437676
	FUZZ s.labels.weightUnderline = 0.316466; // fuzzed, old value = 0.316051
	FUZZ s.labels.ratioBase = 0.812179; // fuzzed, old value = 0.823109
	FUZZ s.labels.ratioWeight = 0.274806; // fuzzed, old value = 0.273495
	FUZZ s.labels.adjustDec = 1.221579; // fuzzed, old value = 1.235308
	FUZZ s.labels.adjustInc = 0.827237; // fuzzed, old value = 0.832994
	FUZZ s.labels.sameLineEps = 0.118599; // fuzzed, old value = 0.118385
	FUZZ s.labels.heightRatio = 0.838256; // fuzzed, old value = 0.826356
	FUZZ s.labels.medHeightFactor = 0.495012; // fuzzed, old value = 0.501382
	FUZZ s.labels.capHeightError = 0.536959; // fuzzed, old value = 0.536500

	FUZZ s.lcomb.MaximalSymbolDistance = 2.531993; // fuzzed, old value = 2.569183
	FUZZ s.lcomb.TestSlashLineEps = 3.075090; // fuzzed, old value = 3.093071
	FUZZ s.lcomb.TestMinHeightFactor = 0.505107; // fuzzed, old value = 0.500579
	FUZZ s.lcomb.TestMaxHeightFactor = 1.169579; // fuzzed, old value = 1.157559
	FUZZ s.lcomb.RectHeightRatio = 0.506264; // fuzzed, old value = 0.502094
	FUZZ s.lcomb.H1SuperscriptSpace = 1.198632; // fuzzed, old value = 1.205005
	FUZZ s.lcomb.H2LowercaseSpace = 0.509743; // fuzzed, old value = 0.508709
	FUZZ s.lcomb.H3LowercaseSpace = 0.461612; // fuzzed, old value = 0.455114
	FUZZ s.lcomb.H4SubscriptSpace = 0.532531; // fuzzed, old value = 0.533377
	FUZZ s.lcomb.FillLabelFactor1 = 0.539188; // fuzzed, old value = 0.545797
	FUZZ s.lcomb.FillLabelFactor2 = 0.528730; // fuzzed, old value = 0.536617
}
