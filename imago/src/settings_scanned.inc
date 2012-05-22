
void updateSettingsScanned(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.312680; // fuzzed, old value = 0.314012
	FUZZ s.molecule.LengthFactor_medium = 0.422714; // fuzzed, old value = 0.425254
	FUZZ s.molecule.LengthFactor_default = 0.457786; // fuzzed, old value = 0.473692
	FUZZ s.molecule.LengthValue_long = 105.745126; // fuzzed, old value = 110.385832
	FUZZ s.molecule.LengthValue_medium = 82.325241; // fuzzed, old value = 84.327330
	FUZZ s.molecule.SpaceMultiply = 1.505538; // fuzzed, old value = 1.454141
	FUZZ s.molecule.AngleTreshold = 0.249699; // fuzzed, old value = 0.252741
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.577485; // fuzzed, old value = 16.752879
	FUZZ s.estimation.LineThickness = 5.687835; // fuzzed, old value = 5.863939
	FUZZ s.estimation.AvgBondLength = 31.266196; // fuzzed, old value = 30.373043
	FUZZ s.estimation.AddVertexEps = 5.344452; // fuzzed, old value = 5.102932
	FUZZ s.estimation.MaxSymRatio = 1.110051; // fuzzed, old value = 1.143175
	FUZZ s.estimation.MinSymRatio = 0.353041; // fuzzed, old value = 0.346441
	FUZZ s.estimation.ParLinesEps = 0.531078; // fuzzed, old value = 0.524222
	FUZZ s.estimation.SymHeightErr = 26.742640; // fuzzed, old value = 27.279836
	FUZZ s.estimation.CapitalHeightError = 0.805828; // fuzzed, old value = 0.814128
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.378582; // fuzzed, old value = 0.363389
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 120; // fuzzed, old value = 116
	FUZZ s.mbond.LongErr = 0.353499; // fuzzed, old value = 0.337432
	FUZZ s.mbond.MediumBond = 93; // fuzzed, old value = 89
	FUZZ s.mbond.MediumErr = 0.424838; // fuzzed, old value = 0.407329
	FUZZ s.mbond.DefaultErr = 0.623609; // fuzzed, old value = 0.605962
	FUZZ s.mbond.ParBondsEps = 0.343029; // fuzzed, old value = 0.333394
	FUZZ s.mbond.DoubleRatioTresh = 7.120958; // fuzzed, old value = 7.317788
	FUZZ s.mbond.DoubleCoef = 0.083880; // fuzzed, old value = 0.083420
	FUZZ s.mbond.DoubleMagic1 = 0.885687; // fuzzed, old value = 0.907255
	FUZZ s.mbond.DoubleMagic2 = 0.963368; // fuzzed, old value = 0.943431
	FUZZ s.mbond.DoubleTreshMin = 0.100571; // fuzzed, old value = 0.102346
	FUZZ s.mbond.DoubleTreshMax = 0.794882; // fuzzed, old value = 0.830295
	FUZZ s.mbond.MaxLen1 = 153.218157; // fuzzed, old value = 159.358419
	FUZZ s.mbond.MaxLen2 = 116.148307; // fuzzed, old value = 116.553275
	FUZZ s.mbond.MaxLen3 = 108.809015; // fuzzed, old value = 108.464591
	FUZZ s.mbond.MaxLen4 = 123.717600; // fuzzed, old value = 119.464148
	FUZZ s.mbond.MaxLen5 = 80.153664; // fuzzed, old value = 82.832636
	FUZZ s.mbond.MinLen1 = 82.623212; // fuzzed, old value = 84.823731
	FUZZ s.mbond.MinLen2 = 74.847892; // fuzzed, old value = 72.992831
	FUZZ s.mbond.mbe1 = 0.076355; // fuzzed, old value = 0.078323
	FUZZ s.mbond.mbe2 = 0.157922; // fuzzed, old value = 0.154776
	FUZZ s.mbond.mbe3 = 0.200264; // fuzzed, old value = 0.192723
	FUZZ s.mbond.mbe4 = 0.181623; // fuzzed, old value = 0.189723
	FUZZ s.mbond.mbe5 = 0.152260; // fuzzed, old value = 0.150895
	FUZZ s.mbond.mbe6 = 0.217858; // fuzzed, old value = 0.218978
	FUZZ s.mbond.mbe7 = 0.423682; // fuzzed, old value = 0.430371
	FUZZ s.mbond.mbe_def = 0.509344; // fuzzed, old value = 0.502472
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.344517; // fuzzed, old value = 0.357166
	FUZZ s.mbond.DoubleRightLengthTresh = 0.308353; // fuzzed, old value = 0.293936
	FUZZ s.mbond.TripleLeftLengthTresh = 0.261501; // fuzzed, old value = 0.268076
	FUZZ s.mbond.TripleRightLengthTresh = 0.240136; // fuzzed, old value = 0.232532
	FUZZ s.mbond.Case1LengthTresh = 103.494053; // fuzzed, old value = 106.288726
	FUZZ s.mbond.Case1Factor = 0.447583; // fuzzed, old value = 0.449384
	FUZZ s.mbond.Case2LengthTresh = 80.514899; // fuzzed, old value = 81.069722
	FUZZ s.mbond.Case2Factor = 0.666395; // fuzzed, old value = 0.694346
	FUZZ s.mbond.Case3Factor = 0.861618; // fuzzed, old value = 0.874483
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.099101; // fuzzed, old value = 0.100707
	FUZZ s.skeleton.BaseSmallErr = 0.144246; // fuzzed, old value = 0.150632
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.309409; // fuzzed, old value = 0.308850
	FUZZ s.skeleton.MediumBondLen = 86; // fuzzed, old value = 86
	FUZZ s.skeleton.MediumMul = 0.168288; // fuzzed, old value = 0.170786
	FUZZ s.skeleton.MediumSmallErr = 0.132980; // fuzzed, old value = 0.132289
	FUZZ s.skeleton.LongBondLen = 103; // fuzzed, old value = 101
	FUZZ s.skeleton.LongMul = 0.144392; // fuzzed, old value = 0.151900
	FUZZ s.skeleton.LongSmallErr = 0.060447; // fuzzed, old value = 0.061448
	FUZZ s.skeleton.BrokenRepairFactor = 3.118944; // fuzzed, old value = 3.085241
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.998709; // fuzzed, old value = 0.992772
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.528271; // fuzzed, old value = 2.603863
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.188021; // fuzzed, old value = 0.181686
	FUZZ s.skeleton.DissolveMinErr = 0.177181; // fuzzed, old value = 0.179226
	FUZZ s.skeleton.ConnectBlockS = 9.731788; // fuzzed, old value = 9.980438
	FUZZ s.skeleton.ConnectFactor = 2.100716; // fuzzed, old value = 2.163926
	FUZZ s.skeleton.JoinVerticiesConst = 0.103701; // fuzzed, old value = 0.106521
	FUZZ s.skeleton.DissolveConst = 0.093740; // fuzzed, old value = 0.095701
	FUZZ s.skeleton.Dissolve2Const = 0.202972; // fuzzed, old value = 0.199432
	FUZZ s.skeleton.Join2Const = 0.310103; // fuzzed, old value = 0.313818
	FUZZ s.skeleton.Join3Const = 0.195593; // fuzzed, old value = 0.193546
	FUZZ s.skeleton.DistTreshLimFactor = 1.999941; // fuzzed, old value = 1.950554
	FUZZ s.skeleton.SlopeFact1 = 0.101699; // fuzzed, old value = 0.098141
	FUZZ s.skeleton.SlopeFact2 = 0.179138; // fuzzed, old value = 0.181941
	FUZZ s.skeleton.ShrinkEps = 0.134665; // fuzzed, old value = 0.133831
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.096321; // fuzzed, old value = 0.095625
	FUZZ s.routines.Circle_GapMax = 1.044577; // fuzzed, old value = 0.998874
	FUZZ s.routines.Circle_RMax = 2.155625; // fuzzed, old value = 2.154767
	FUZZ s.routines.Circle_AvgRadius = 0.000103; // fuzzed, old value = 0.000104
	FUZZ s.routines.Circle_MaxRatio = 0.330067; // fuzzed, old value = 0.335856
	FUZZ s.routines.Algebra_IntersectionEps = 0.010982; // fuzzed, old value = 0.010758
	FUZZ s.routines.Algebra_SameLineEps = 0.225346; // fuzzed, old value = 0.224346
	FUZZ s.routines.Approx_Eps1 = 1.144582; // fuzzed, old value = 1.152260
	FUZZ s.routines.Approx_Eps2 = 0.820181; // fuzzed, old value = 0.856339
	FUZZ s.routines.Approx_CalcLineTresh = 0.922307; // fuzzed, old value = 0.951213
	FUZZ s.routines.Contour_Eps1 = 1.030649; // fuzzed, old value = 1.058759
	FUZZ s.routines.Contour_Eps2 = 0.697402; // fuzzed, old value = 0.677484

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.963643; // fuzzed, old value = 3.109147
	FUZZ s.wbe.SingleDownAngleMax = 46.300486; // fuzzed, old value = 46.467612
	FUZZ s.wbe.SingleDownDistancesMax = 10.468702; // fuzzed, old value = 10.034737
	FUZZ s.wbe.SingleDownLengthMax = 46.242316; // fuzzed, old value = 46.174323
	FUZZ s.wbe.SingleUpRatioEps = 1.654354; // fuzzed, old value = 1.660498
	FUZZ s.wbe.SingleUpDefCoeff = 0.289348; // fuzzed, old value = 0.302677
	FUZZ s.wbe.SingleUpIncCoeff = 0.448766; // fuzzed, old value = 0.432971
	FUZZ s.wbe.SingleUpIncLengthTresh = 35.703441; // fuzzed, old value = 36.042727
	FUZZ s.wbe.SingleUpInterpolateEps = 0.062180; // fuzzed, old value = 0.064183
	FUZZ s.wbe.SingleUpMagicAddition = 0.235520; // fuzzed, old value = 0.240304
	FUZZ s.wbe.SingleUpS2Divisor = 1.421432; // fuzzed, old value = 1.487086
	FUZZ s.wbe.SingleUpMinATresh = 1.645076; // fuzzed, old value = 1.633013
	FUZZ s.wbe.SingleUpSquareRatio = 0.667113; // fuzzed, old value = 0.639582
	FUZZ s.wbe.SingleUpAngleTresh = 0.066476; // fuzzed, old value = 0.064217
	FUZZ s.wbe.SomeTresh = 0.103502; // fuzzed, old value = 0.103310
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = false
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.063587; // fuzzed, old value = 1.060072
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.151430; // fuzzed, old value = 1.129637
	FUZZ s.characters.WriteEasyFactor = 0.977022; // fuzzed, old value = 1.025604
	FUZZ s.characters.WriteVeryEasyFactor = 0.929563; // fuzzed, old value = 0.888791
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.332524; // fuzzed, old value = 3.192894
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.247586; // fuzzed, old value = 3.354776
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.105269; // fuzzed, old value = 0.109991
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.649531; // fuzzed, old value = 2.527344
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.562179; // fuzzed, old value = 3.503842
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.919815; // fuzzed, old value = 0.934808
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.284952; // fuzzed, old value = 0.279475
	FUZZ s.characters.HW_Line = 1.641786; // fuzzed, old value = 1.663039
	FUZZ s.characters.HW_F = 3.330216; // fuzzed, old value = 3.174725
	FUZZ s.characters.HW_Tricky = 2.738081; // fuzzed, old value = 2.866710
	FUZZ s.characters.HW_Hard = 4.155868; // fuzzed, old value = 4.344854
	FUZZ s.characters.HW_Other = 3.647382; // fuzzed, old value = 3.797047

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.470344; // fuzzed, old value = 0.484603
	FUZZ s.csr.DeleteBadTriangles = 1.908946; // fuzzed, old value = 1.941122
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.628071; // fuzzed, old value = 1.658967

	FUZZ s.graph.MinimalDistTresh = 1.887267; // fuzzed, old value = 1.844241
	FUZZ s.graph.RatioSub = 0.995837; // fuzzed, old value = 1.047079
	FUZZ s.graph.RatioTresh = 0.452384; // fuzzed, old value = 0.433579

	FUZZ s.utils.SlashLineDensity = 0.450761; // fuzzed, old value = 0.459448
	FUZZ s.utils.TestPlusDensity = 0.402547; // fuzzed, old value = 0.423511
	FUZZ s.utils.TestPlusSq = 0.396780; // fuzzed, old value = 0.411163
	FUZZ s.utils.TestMinusRatio = 0.372173; // fuzzed, old value = 0.375232
	FUZZ s.utils.TestMinusDensity = 0.658580; // fuzzed, old value = 0.636711
	FUZZ s.utils.TestMinusHeightFactor = 0.856734; // fuzzed, old value = 0.869324

	FUZZ s.separator.hu_1_1 = 0.209682; // fuzzed, old value = 0.209016
	FUZZ s.separator.hu_1_2 = 0.075512; // fuzzed, old value = 0.078244
	FUZZ s.separator.hu_0_1 = 0.232016; // fuzzed, old value = 0.232186
	FUZZ s.separator.hu_1_3 = 0.079154; // fuzzed, old value = 0.079689
	FUZZ s.separator.hu_0_2 = 0.235494; // fuzzed, old value = 0.234813
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.562693; // fuzzed, old value = 0.541393
	FUZZ s.separator.capHeightMax = 1.389839; // fuzzed, old value = 1.436958
	FUZZ s.separator.gdConst = 1.573590; // fuzzed, old value = 1.601625
	FUZZ s.separator.SurfCoef = 2.873192; // fuzzed, old value = 2.842994
	FUZZ s.separator.capHeightRatio = 0.253290; // fuzzed, old value = 0.243006
	FUZZ s.separator.capHeightRatio2 = 1.999732; // fuzzed, old value = 1.932290
	FUZZ s.separator.getRatio1 = 1.074439; // fuzzed, old value = 1.036623
	FUZZ s.separator.getRatio2 = 1.136332; // fuzzed, old value = 1.117585
	FUZZ s.separator.testSlashLine1 = 2.880112; // fuzzed, old value = 2.874914
	FUZZ s.separator.testSlashLine2 = 2.863996; // fuzzed, old value = 2.934646
	FUZZ s.separator.minDensity = 0.194810; // fuzzed, old value = 0.195797
	FUZZ s.separator.maxDensity = 0.862146; // fuzzed, old value = 0.882856
	FUZZ s.separator.extCapHeightMin = 0.299912; // fuzzed, old value = 0.306905
	FUZZ s.separator.extCapHeightMax = 2.182896; // fuzzed, old value = 2.173104
	FUZZ s.separator.extRatioMin = 0.298597; // fuzzed, old value = 0.302230
	FUZZ s.separator.extRatioMax = 1.601624; // fuzzed, old value = 1.552425
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.437676; // fuzzed, old value = 0.439654
	FUZZ s.labels.weightUnderline = 0.316051; // fuzzed, old value = 0.308302
	FUZZ s.labels.ratioBase = 0.823109; // fuzzed, old value = 0.838920
	FUZZ s.labels.ratioWeight = 0.273495; // fuzzed, old value = 0.275550
	FUZZ s.labels.adjustDec = 1.235308; // fuzzed, old value = 1.202376
	FUZZ s.labels.adjustInc = 0.832994; // fuzzed, old value = 0.798111
	FUZZ s.labels.sameLineEps = 0.118385; // fuzzed, old value = 0.118557
	FUZZ s.labels.heightRatio = 0.826356; // fuzzed, old value = 0.848822
	FUZZ s.labels.medHeightFactor = 0.501382; // fuzzed, old value = 0.488077
	FUZZ s.labels.capHeightError = 0.536500; // fuzzed, old value = 0.542789

	FUZZ s.lcomb.MaximalSymbolDistance = 2.569183; // fuzzed, old value = 2.536481
	FUZZ s.lcomb.TestSlashLineEps = 3.093071; // fuzzed, old value = 2.971877
	FUZZ s.lcomb.TestMinHeightFactor = 0.500579; // fuzzed, old value = 0.487079
	FUZZ s.lcomb.TestMaxHeightFactor = 1.157559; // fuzzed, old value = 1.179453
	FUZZ s.lcomb.RectHeightRatio = 0.502094; // fuzzed, old value = 0.479224
	FUZZ s.lcomb.H1SuperscriptSpace = 1.205005; // fuzzed, old value = 1.200931
	FUZZ s.lcomb.H2LowercaseSpace = 0.508709; // fuzzed, old value = 0.502570
	FUZZ s.lcomb.H3LowercaseSpace = 0.455114; // fuzzed, old value = 0.459702
	FUZZ s.lcomb.H4SubscriptSpace = 0.533377; // fuzzed, old value = 0.534221
	FUZZ s.lcomb.FillLabelFactor1 = 0.545797; // fuzzed, old value = 0.527919
	FUZZ s.lcomb.FillLabelFactor2 = 0.536617; // fuzzed, old value = 0.517290
}
