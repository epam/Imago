
void updateSettingsHighResolution(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.327577; // fuzzed, old value = 0.324124
	FUZZ s.molecule.LengthFactor_medium = 0.420114; // fuzzed, old value = 0.420221
	FUZZ s.molecule.LengthFactor_default = 0.492822; // fuzzed, old value = 0.486020
	FUZZ s.molecule.LengthValue_long = 96.851551; // fuzzed, old value = 96.152613
	FUZZ s.molecule.LengthValue_medium = 84.798635; // fuzzed, old value = 85.430506
	FUZZ s.molecule.SpaceMultiply = 1.571064; // fuzzed, old value = 1.576670
	FUZZ s.molecule.AngleTreshold = 0.262487; // fuzzed, old value = 0.258753
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.161776; // fuzzed, old value = 17.236222
	FUZZ s.estimation.LineThickness = 6.152596; // fuzzed, old value = 6.082790
	FUZZ s.estimation.AvgBondLength = 29.919342; // fuzzed, old value = 30.045592
	FUZZ s.estimation.AddVertexEps = 5.611061; // fuzzed, old value = 5.590977
	FUZZ s.estimation.MaxSymRatio = 1.049570; // fuzzed, old value = 1.044062
	FUZZ s.estimation.MinSymRatio = 0.333807; // fuzzed, old value = 0.331161
	FUZZ s.estimation.ParLinesEps = 0.513016; // fuzzed, old value = 0.506585
	FUZZ s.estimation.SymHeightErr = 29.002597; // fuzzed, old value = 29.395708
	FUZZ s.estimation.CapitalHeightError = 0.845889; // fuzzed, old value = 0.840920
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.545024; // fuzzed, old value = 0.549555
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 124; // fuzzed, old value = 124
	FUZZ s.mbond.LongErr = 0.396877; // fuzzed, old value = 0.397510
	FUZZ s.mbond.MediumBond = 97; // fuzzed, old value = 96
	FUZZ s.mbond.MediumErr = 0.387916; // fuzzed, old value = 0.390505
	FUZZ s.mbond.DefaultErr = 0.656186; // fuzzed, old value = 0.651656
	FUZZ s.mbond.ParBondsEps = 0.359492; // fuzzed, old value = 0.357443
	FUZZ s.mbond.DoubleRatioTresh = 7.060831; // fuzzed, old value = 7.105239
	FUZZ s.mbond.DoubleCoef = 0.080102; // fuzzed, old value = 0.080682
	FUZZ s.mbond.DoubleMagic1 = 0.901851; // fuzzed, old value = 0.890559
	FUZZ s.mbond.DoubleMagic2 = 1.023456; // fuzzed, old value = 1.036218
	FUZZ s.mbond.DoubleTreshMin = 0.094704; // fuzzed, old value = 0.095995
	FUZZ s.mbond.DoubleTreshMax = 0.840386; // fuzzed, old value = 0.840206
	FUZZ s.mbond.MaxLen1 = 151.852015; // fuzzed, old value = 152.195706
	FUZZ s.mbond.MaxLen2 = 124.628985; // fuzzed, old value = 125.043360
	FUZZ s.mbond.MaxLen3 = 110.034897; // fuzzed, old value = 111.259457
	FUZZ s.mbond.MaxLen4 = 110.558181; // fuzzed, old value = 111.844062
	FUZZ s.mbond.MaxLen5 = 85.737262; // fuzzed, old value = 85.385902
	FUZZ s.mbond.MinLen1 = 85.418678; // fuzzed, old value = 84.611899
	FUZZ s.mbond.MinLen2 = 75.007035; // fuzzed, old value = 75.956955
	FUZZ s.mbond.mbe1 = 0.079031; // fuzzed, old value = 0.079587
	FUZZ s.mbond.mbe2 = 0.154150; // fuzzed, old value = 0.156165
	FUZZ s.mbond.mbe3 = 0.207919; // fuzzed, old value = 0.209716
	FUZZ s.mbond.mbe4 = 0.180409; // fuzzed, old value = 0.178945
	FUZZ s.mbond.mbe5 = 0.162732; // fuzzed, old value = 0.161898
	FUZZ s.mbond.mbe6 = 0.209911; // fuzzed, old value = 0.212444
	FUZZ s.mbond.mbe7 = 0.389446; // fuzzed, old value = 0.390860
	FUZZ s.mbond.mbe_def = 0.530244; // fuzzed, old value = 0.530534
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.328688; // fuzzed, old value = 0.324307
	FUZZ s.mbond.DoubleRightLengthTresh = 0.321428; // fuzzed, old value = 0.316706
	FUZZ s.mbond.TripleLeftLengthTresh = 0.262715; // fuzzed, old value = 0.261429
	FUZZ s.mbond.TripleRightLengthTresh = 0.239565; // fuzzed, old value = 0.241369
	FUZZ s.mbond.Case1LengthTresh = 100.802495; // fuzzed, old value = 101.723163
	FUZZ s.mbond.Case1Factor = 0.436231; // fuzzed, old value = 0.438665
	FUZZ s.mbond.Case2LengthTresh = 75.604732; // fuzzed, old value = 75.976919
	FUZZ s.mbond.Case2Factor = 0.687491; // fuzzed, old value = 0.679186
	FUZZ s.mbond.Case3Factor = 0.896522; // fuzzed, old value = 0.895626
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.093695; // fuzzed, old value = 0.093965
	FUZZ s.skeleton.BaseSmallErr = 0.147343; // fuzzed, old value = 0.146217
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.329723; // fuzzed, old value = 0.325797
	FUZZ s.skeleton.MediumBondLen = 87; // fuzzed, old value = 88
	FUZZ s.skeleton.MediumMul = 0.181510; // fuzzed, old value = 0.179444
	FUZZ s.skeleton.MediumSmallErr = 0.141484; // fuzzed, old value = 0.140426
	FUZZ s.skeleton.LongBondLen = 107; // fuzzed, old value = 106
	FUZZ s.skeleton.LongMul = 0.141946; // fuzzed, old value = 0.142735
	FUZZ s.skeleton.LongSmallErr = 0.058937; // fuzzed, old value = 0.059545
	FUZZ s.skeleton.BrokenRepairFactor = 3.089407; // fuzzed, old value = 3.060011
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.993982; // fuzzed, old value = 1.006734
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.623262; // fuzzed, old value = 2.612223
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.208422; // fuzzed, old value = 0.209759
	FUZZ s.skeleton.DissolveMinErr = 0.179234; // fuzzed, old value = 0.177584
	FUZZ s.skeleton.ConnectBlockS = 10.000933; // fuzzed, old value = 9.868964
	FUZZ s.skeleton.ConnectFactor = 2.044460; // fuzzed, old value = 2.034564
	FUZZ s.skeleton.JoinVerticiesConst = 0.099955; // fuzzed, old value = 0.098641
	FUZZ s.skeleton.DissolveConst = 0.098953; // fuzzed, old value = 0.097799
	FUZZ s.skeleton.Dissolve2Const = 0.204977; // fuzzed, old value = 0.202550
	FUZZ s.skeleton.Join2Const = 0.340369; // fuzzed, old value = 0.344447
	FUZZ s.skeleton.Join3Const = 0.187886; // fuzzed, old value = 0.185361
	FUZZ s.skeleton.DistTreshLimFactor = 1.935630; // fuzzed, old value = 1.959898
	FUZZ s.skeleton.SlopeFact1 = 0.104076; // fuzzed, old value = 0.102810
	FUZZ s.skeleton.SlopeFact2 = 0.186967; // fuzzed, old value = 0.187030
	FUZZ s.skeleton.ShrinkEps = 0.127274; // fuzzed, old value = 0.125537
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.100353; // fuzzed, old value = 0.100554
	FUZZ s.routines.Circle_GapMax = 0.921923; // fuzzed, old value = 0.932546
	FUZZ s.routines.Circle_RMax = 1.990717; // fuzzed, old value = 1.977611
	FUZZ s.routines.Circle_AvgRadius = 0.000108; // fuzzed, old value = 0.000107
	FUZZ s.routines.Circle_MaxRatio = 0.314153; // fuzzed, old value = 0.316171
	FUZZ s.routines.Algebra_IntersectionEps = 0.010378; // fuzzed, old value = 0.010270
	FUZZ s.routines.Algebra_SameLineEps = 0.207572; // fuzzed, old value = 0.204530
	FUZZ s.routines.Approx_Eps1 = 1.191356; // fuzzed, old value = 1.186415
	FUZZ s.routines.Approx_Eps2 = 0.846483; // fuzzed, old value = 0.853606
	FUZZ s.routines.Approx_CalcLineTresh = 0.874323; // fuzzed, old value = 0.883062

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.821331; // fuzzed, old value = 2.825313
	FUZZ s.wbe.SingleDownAngleMax = 43.580169; // fuzzed, old value = 43.369028
	FUZZ s.wbe.SingleDownDistancesMax = 9.499786; // fuzzed, old value = 9.387568
	FUZZ s.wbe.SingleDownLengthMax = 44.608281; // fuzzed, old value = 45.148061
	FUZZ s.wbe.SingleUpRatioEps = 1.871563; // fuzzed, old value = 1.857780
	FUZZ s.wbe.SingleUpDefCoeff = 0.276828; // fuzzed, old value = 0.276198
	FUZZ s.wbe.SingleUpIncCoeff = 0.406043; // fuzzed, old value = 0.403629
	FUZZ s.wbe.SingleUpIncLengthTresh = 32.864907; // fuzzed, old value = 33.085597
	FUZZ s.wbe.SingleUpInterpolateEps = 0.064949; // fuzzed, old value = 0.064242
	FUZZ s.wbe.SingleUpMagicAddition = 0.219567; // fuzzed, old value = 0.222099
	FUZZ s.wbe.SingleUpS2Divisor = 1.692711; // fuzzed, old value = 1.676413
	FUZZ s.wbe.SingleUpMinATresh = 1.651449; // fuzzed, old value = 1.664201
	FUZZ s.wbe.SingleUpSquareRatio = 0.616921; // fuzzed, old value = 0.624243
	FUZZ s.wbe.SingleUpAngleTresh = 0.066395; // fuzzed, old value = 0.066464
	FUZZ s.wbe.SomeTresh = 0.101577; // fuzzed, old value = 0.102920
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = false
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.037340; // fuzzed, old value = 1.037296
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.182250; // fuzzed, old value = 1.190245
	FUZZ s.characters.WriteEasyFactor = 0.943528; // fuzzed, old value = 0.943543
	FUZZ s.characters.WriteVeryEasyFactor = 0.856394; // fuzzed, old value = 0.848463
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.133209; // fuzzed, old value = 3.095659
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.466852; // fuzzed, old value = 3.440570
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.102772; // fuzzed, old value = 0.104028
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.447774; // fuzzed, old value = 2.475237
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.401322; // fuzzed, old value = 3.440898
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.047057; // fuzzed, old value = 1.043977
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.309555; // fuzzed, old value = 0.311881
	FUZZ s.characters.HW_Line = 1.612312; // fuzzed, old value = 1.625300
	FUZZ s.characters.HW_F = 3.314683; // fuzzed, old value = 3.339170
	FUZZ s.characters.HW_Tricky = 2.716866; // fuzzed, old value = 2.724553
	FUZZ s.characters.HW_Hard = 4.521320; // fuzzed, old value = 4.529712
	FUZZ s.characters.HW_Other = 3.490194; // fuzzed, old value = 3.439210

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.473015; // fuzzed, old value = 0.472175
	FUZZ s.csr.DeleteBadTriangles = 1.794851; // fuzzed, old value = 1.817066
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.487796; // fuzzed, old value = 1.488868

	FUZZ s.graph.MinimalDistTresh = 2.165100; // fuzzed, old value = 2.175454
	FUZZ s.graph.RatioSub = 0.933875; // fuzzed, old value = 0.928355
	FUZZ s.graph.RatioTresh = 0.428588; // fuzzed, old value = 0.422903

	FUZZ s.utils.SlashLineDensity = 0.458298; // fuzzed, old value = 0.462468
	FUZZ s.utils.TestPlusDensity = 0.442127; // fuzzed, old value = 0.448106
	FUZZ s.utils.TestPlusSq = 0.408222; // fuzzed, old value = 0.410437
	FUZZ s.utils.TestMinusRatio = 0.345300; // fuzzed, old value = 0.344846
	FUZZ s.utils.TestMinusDensity = 0.589338; // fuzzed, old value = 0.584567
	FUZZ s.utils.TestMinusHeightFactor = 0.765840; // fuzzed, old value = 0.776910

	FUZZ s.separator.hu_1_1 = 0.202047; // fuzzed, old value = 0.204844
	FUZZ s.separator.hu_1_2 = 0.085324; // fuzzed, old value = 0.085645
	FUZZ s.separator.hu_0_1 = 0.244123; // fuzzed, old value = 0.243846
	FUZZ s.separator.hu_1_3 = 0.077811; // fuzzed, old value = 0.078700
	FUZZ s.separator.hu_0_2 = 0.253931; // fuzzed, old value = 0.257481
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.540371; // fuzzed, old value = 0.537944
	FUZZ s.separator.capHeightMax = 1.388439; // fuzzed, old value = 1.401996
	FUZZ s.separator.gdConst = 1.570286; // fuzzed, old value = 1.572080
	FUZZ s.separator.SurfCoef = 2.808046; // fuzzed, old value = 2.784337
	FUZZ s.separator.capHeightRatio = 0.240186; // fuzzed, old value = 0.240364
	FUZZ s.separator.capHeightRatio2 = 1.900306; // fuzzed, old value = 1.906820
	FUZZ s.separator.getRatio1 = 0.948203; // fuzzed, old value = 0.953113
	FUZZ s.separator.getRatio2 = 1.104939; // fuzzed, old value = 1.118809
	FUZZ s.separator.testSlashLine1 = 3.001317; // fuzzed, old value = 2.980766
	FUZZ s.separator.testSlashLine2 = 2.980345; // fuzzed, old value = 2.978094
	FUZZ s.separator.minDensity = 0.196967; // fuzzed, old value = 0.199811
	FUZZ s.separator.maxDensity = 0.833956; // fuzzed, old value = 0.841907
	FUZZ s.separator.extCapHeightMin = 0.296796; // fuzzed, old value = 0.298906
	FUZZ s.separator.extCapHeightMax = 1.986065; // fuzzed, old value = 2.002356
	FUZZ s.separator.extRatioMin = 0.281111; // fuzzed, old value = 0.280323
	FUZZ s.separator.extRatioMax = 1.484926; // fuzzed, old value = 1.479012
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.493972; // fuzzed, old value = 0.489715
	FUZZ s.labels.weightUnderline = 0.294700; // fuzzed, old value = 0.297516
	FUZZ s.labels.ratioBase = 0.812221; // fuzzed, old value = 0.822450
	FUZZ s.labels.ratioWeight = 0.303176; // fuzzed, old value = 0.301135
	FUZZ s.labels.adjustDec = 1.217033; // fuzzed, old value = 1.217858
	FUZZ s.labels.adjustInc = 0.824556; // fuzzed, old value = 0.822190
	FUZZ s.labels.sameLineEps = 0.136545; // fuzzed, old value = 0.136769
	FUZZ s.labels.heightRatio = 0.859314; // fuzzed, old value = 0.851375
	FUZZ s.labels.medHeightFactor = 0.475030; // fuzzed, old value = 0.469583
	FUZZ s.labels.capHeightError = 0.547185; // fuzzed, old value = 0.540661

	FUZZ s.lcomb.MaximalSymbolDistance = 2.866555; // fuzzed, old value = 2.879636
	FUZZ s.lcomb.TestSlashLineEps = 2.891134; // fuzzed, old value = 2.902987
	FUZZ s.lcomb.TestMinHeightFactor = 0.523227; // fuzzed, old value = 0.527117
	FUZZ s.lcomb.TestMaxHeightFactor = 1.178770; // fuzzed, old value = 1.186715
	FUZZ s.lcomb.RectHeightRatio = 0.496325; // fuzzed, old value = 0.501979
	FUZZ s.lcomb.H1SuperscriptSpace = 1.121066; // fuzzed, old value = 1.126268
	FUZZ s.lcomb.H2LowercaseSpace = 0.540323; // fuzzed, old value = 0.542800
	FUZZ s.lcomb.H3LowercaseSpace = 0.480966; // fuzzed, old value = 0.474390
	FUZZ s.lcomb.H4SubscriptSpace = 0.536633; // fuzzed, old value = 0.530197
	FUZZ s.lcomb.FillLabelFactor1 = 0.478025; // fuzzed, old value = 0.481058
	FUZZ s.lcomb.FillLabelFactor2 = 0.515109; // fuzzed, old value = 0.518346
}

