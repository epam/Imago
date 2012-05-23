
void updateSettingsHighResolution(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.323056; // fuzzed, old value = 0.324124
	FUZZ s.molecule.LengthFactor_medium = 0.417645; // fuzzed, old value = 0.420221
	FUZZ s.molecule.LengthFactor_default = 0.482891; // fuzzed, old value = 0.486020
	FUZZ s.molecule.LengthValue_long = 96.770473; // fuzzed, old value = 96.152613
	FUZZ s.molecule.LengthValue_medium = 84.617564; // fuzzed, old value = 85.430506
	FUZZ s.molecule.SpaceMultiply = 1.560868; // fuzzed, old value = 1.576670
	FUZZ s.molecule.AngleTreshold = 0.259436; // fuzzed, old value = 0.258753
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.177936; // fuzzed, old value = 17.236222
	FUZZ s.estimation.LineThickness = 6.020931; // fuzzed, old value = 6.082790
	FUZZ s.estimation.AvgBondLength = 30.242236; // fuzzed, old value = 30.045592
	FUZZ s.estimation.AddVertexEps = 5.512538; // fuzzed, old value = 5.590977
	FUZZ s.estimation.MaxSymRatio = 1.052553; // fuzzed, old value = 1.044062
	FUZZ s.estimation.MinSymRatio = 0.327151; // fuzzed, old value = 0.331161
	FUZZ s.estimation.ParLinesEps = 0.502630; // fuzzed, old value = 0.506585
	FUZZ s.estimation.SymHeightErr = 29.590386; // fuzzed, old value = 29.395708
	FUZZ s.estimation.CapitalHeightError = 0.834295; // fuzzed, old value = 0.840920
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.556750; // fuzzed, old value = 0.549555
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 126; // fuzzed, old value = 124
	FUZZ s.mbond.LongErr = 0.396646; // fuzzed, old value = 0.397510
	FUZZ s.mbond.MediumBond = 96; // fuzzed, old value = 96
	FUZZ s.mbond.MediumErr = 0.387216; // fuzzed, old value = 0.390505
	FUZZ s.mbond.DefaultErr = 0.658560; // fuzzed, old value = 0.651656
	FUZZ s.mbond.ParBondsEps = 0.354995; // fuzzed, old value = 0.357443
	FUZZ s.mbond.DoubleRatioTresh = 7.084009; // fuzzed, old value = 7.105239
	FUZZ s.mbond.DoubleCoef = 0.080259; // fuzzed, old value = 0.080682
	FUZZ s.mbond.DoubleMagic1 = 0.896582; // fuzzed, old value = 0.890559
	FUZZ s.mbond.DoubleMagic2 = 1.026275; // fuzzed, old value = 1.036218
	FUZZ s.mbond.DoubleTreshMin = 0.096894; // fuzzed, old value = 0.095995
	FUZZ s.mbond.DoubleTreshMax = 0.841234; // fuzzed, old value = 0.840206
	FUZZ s.mbond.MaxLen1 = 150.565595; // fuzzed, old value = 152.195706
	FUZZ s.mbond.MaxLen2 = 124.992815; // fuzzed, old value = 125.043360
	FUZZ s.mbond.MaxLen3 = 112.794703; // fuzzed, old value = 111.259457
	FUZZ s.mbond.MaxLen4 = 112.393486; // fuzzed, old value = 111.844062
	FUZZ s.mbond.MaxLen5 = 86.081703; // fuzzed, old value = 85.385902
	FUZZ s.mbond.MinLen1 = 84.652840; // fuzzed, old value = 84.611899
	FUZZ s.mbond.MinLen2 = 75.729098; // fuzzed, old value = 75.956955
	FUZZ s.mbond.mbe1 = 0.080616; // fuzzed, old value = 0.079587
	FUZZ s.mbond.mbe2 = 0.157039; // fuzzed, old value = 0.156165
	FUZZ s.mbond.mbe3 = 0.207743; // fuzzed, old value = 0.209716
	FUZZ s.mbond.mbe4 = 0.178680; // fuzzed, old value = 0.178945
	FUZZ s.mbond.mbe5 = 0.162746; // fuzzed, old value = 0.161898
	FUZZ s.mbond.mbe6 = 0.212624; // fuzzed, old value = 0.212444
	FUZZ s.mbond.mbe7 = 0.386923; // fuzzed, old value = 0.390860
	FUZZ s.mbond.mbe_def = 0.536040; // fuzzed, old value = 0.530534
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.329059; // fuzzed, old value = 0.324307
	FUZZ s.mbond.DoubleRightLengthTresh = 0.317932; // fuzzed, old value = 0.316706
	FUZZ s.mbond.TripleLeftLengthTresh = 0.258383; // fuzzed, old value = 0.261429
	FUZZ s.mbond.TripleRightLengthTresh = 0.238647; // fuzzed, old value = 0.241369
	FUZZ s.mbond.Case1LengthTresh = 100.762355; // fuzzed, old value = 101.723163
	FUZZ s.mbond.Case1Factor = 0.442172; // fuzzed, old value = 0.438665
	FUZZ s.mbond.Case2LengthTresh = 74.949885; // fuzzed, old value = 75.976919
	FUZZ s.mbond.Case2Factor = 0.682459; // fuzzed, old value = 0.679186
	FUZZ s.mbond.Case3Factor = 0.890935; // fuzzed, old value = 0.895626
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.094530; // fuzzed, old value = 0.093965
	FUZZ s.skeleton.BaseSmallErr = 0.145658; // fuzzed, old value = 0.146217
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.326784; // fuzzed, old value = 0.325797
	FUZZ s.skeleton.MediumBondLen = 87; // fuzzed, old value = 88
	FUZZ s.skeleton.MediumMul = 0.179692; // fuzzed, old value = 0.179444
	FUZZ s.skeleton.MediumSmallErr = 0.140976; // fuzzed, old value = 0.140426
	FUZZ s.skeleton.LongBondLen = 107; // fuzzed, old value = 106
	FUZZ s.skeleton.LongMul = 0.142139; // fuzzed, old value = 0.142735
	FUZZ s.skeleton.LongSmallErr = 0.058679; // fuzzed, old value = 0.059545
	FUZZ s.skeleton.BrokenRepairFactor = 3.097165; // fuzzed, old value = 3.060011
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.991714; // fuzzed, old value = 1.006734
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.646554; // fuzzed, old value = 2.612223
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.208864; // fuzzed, old value = 0.209759
	FUZZ s.skeleton.DissolveMinErr = 0.175882; // fuzzed, old value = 0.177584
	FUZZ s.skeleton.ConnectBlockS = 9.924754; // fuzzed, old value = 9.868964
	FUZZ s.skeleton.ConnectFactor = 2.008267; // fuzzed, old value = 2.034564
	FUZZ s.skeleton.JoinVerticiesConst = 0.097794; // fuzzed, old value = 0.098641
	FUZZ s.skeleton.DissolveConst = 0.097569; // fuzzed, old value = 0.097799
	FUZZ s.skeleton.Dissolve2Const = 0.204793; // fuzzed, old value = 0.202550
	FUZZ s.skeleton.Join2Const = 0.347810; // fuzzed, old value = 0.344447
	FUZZ s.skeleton.Join3Const = 0.182693; // fuzzed, old value = 0.185361
	FUZZ s.skeleton.DistTreshLimFactor = 1.981254; // fuzzed, old value = 1.959898
	FUZZ s.skeleton.SlopeFact1 = 0.103416; // fuzzed, old value = 0.102810
	FUZZ s.skeleton.SlopeFact2 = 0.188029; // fuzzed, old value = 0.187030
	FUZZ s.skeleton.ShrinkEps = 0.123977; // fuzzed, old value = 0.125537
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.101736; // fuzzed, old value = 0.100554
	FUZZ s.routines.Circle_GapMax = 0.919431; // fuzzed, old value = 0.932546
	FUZZ s.routines.Circle_RMax = 2.005546; // fuzzed, old value = 1.977611
	FUZZ s.routines.Circle_AvgRadius = 0.000107; // fuzzed, old value = 0.000107
	FUZZ s.routines.Circle_MaxRatio = 0.320469; // fuzzed, old value = 0.316171
	FUZZ s.routines.Algebra_IntersectionEps = 0.010157; // fuzzed, old value = 0.010270
	FUZZ s.routines.Algebra_SameLineEps = 0.204409; // fuzzed, old value = 0.204530
	FUZZ s.routines.Approx_Eps1 = 1.190432; // fuzzed, old value = 1.186415
	FUZZ s.routines.Approx_Eps2 = 0.858392; // fuzzed, old value = 0.853606
	FUZZ s.routines.Approx_CalcLineTresh = 0.885806; // fuzzed, old value = 0.883062

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.801434; // fuzzed, old value = 2.825313
	FUZZ s.wbe.SingleDownAngleMax = 43.128346; // fuzzed, old value = 43.369028
	FUZZ s.wbe.SingleDownDistancesMax = 9.378479; // fuzzed, old value = 9.387568
	FUZZ s.wbe.SingleDownLengthMax = 45.408206; // fuzzed, old value = 45.148061
	FUZZ s.wbe.SingleUpRatioEps = 1.854320; // fuzzed, old value = 1.857780
	FUZZ s.wbe.SingleUpDefCoeff = 0.272426; // fuzzed, old value = 0.276198
	FUZZ s.wbe.SingleUpIncCoeff = 0.408326; // fuzzed, old value = 0.403629
	FUZZ s.wbe.SingleUpIncLengthTresh = 32.864392; // fuzzed, old value = 33.085597
	FUZZ s.wbe.SingleUpInterpolateEps = 0.063518; // fuzzed, old value = 0.064242
	FUZZ s.wbe.SingleUpMagicAddition = 0.223602; // fuzzed, old value = 0.222099
	FUZZ s.wbe.SingleUpS2Divisor = 1.673040; // fuzzed, old value = 1.676413
	FUZZ s.wbe.SingleUpMinATresh = 1.662210; // fuzzed, old value = 1.664201
	FUZZ s.wbe.SingleUpSquareRatio = 0.622010; // fuzzed, old value = 0.624243
	FUZZ s.wbe.SingleUpAngleTresh = 0.066983; // fuzzed, old value = 0.066464
	FUZZ s.wbe.SomeTresh = 0.102160; // fuzzed, old value = 0.102920
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = false
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.027191; // fuzzed, old value = 1.037296
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.176002; // fuzzed, old value = 1.190245
	FUZZ s.characters.WriteEasyFactor = 0.935538; // fuzzed, old value = 0.943543
	FUZZ s.characters.WriteVeryEasyFactor = 0.858211; // fuzzed, old value = 0.848463
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.073706; // fuzzed, old value = 3.095659
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.449937; // fuzzed, old value = 3.440570
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.105178; // fuzzed, old value = 0.104028
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.506131; // fuzzed, old value = 2.475237
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.457212; // fuzzed, old value = 3.440898
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.050149; // fuzzed, old value = 1.043977
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.312131; // fuzzed, old value = 0.311881
	FUZZ s.characters.HW_Line = 1.623960; // fuzzed, old value = 1.625300
	FUZZ s.characters.HW_F = 3.289712; // fuzzed, old value = 3.339170
	FUZZ s.characters.HW_Tricky = 2.746224; // fuzzed, old value = 2.724553
	FUZZ s.characters.HW_Hard = 4.527786; // fuzzed, old value = 4.529712
	FUZZ s.characters.HW_Other = 3.449464; // fuzzed, old value = 3.439210

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.466942; // fuzzed, old value = 0.472175
	FUZZ s.csr.DeleteBadTriangles = 1.807536; // fuzzed, old value = 1.817066
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.489204; // fuzzed, old value = 1.488868

	FUZZ s.graph.MinimalDistTresh = 2.207450; // fuzzed, old value = 2.175454
	FUZZ s.graph.RatioSub = 0.920617; // fuzzed, old value = 0.928355
	FUZZ s.graph.RatioTresh = 0.427481; // fuzzed, old value = 0.422903

	FUZZ s.utils.SlashLineDensity = 0.459942; // fuzzed, old value = 0.462468
	FUZZ s.utils.TestPlusDensity = 0.444043; // fuzzed, old value = 0.448106
	FUZZ s.utils.TestPlusSq = 0.406661; // fuzzed, old value = 0.410437
	FUZZ s.utils.TestMinusRatio = 0.346258; // fuzzed, old value = 0.344846
	FUZZ s.utils.TestMinusDensity = 0.584762; // fuzzed, old value = 0.584567
	FUZZ s.utils.TestMinusHeightFactor = 0.772113; // fuzzed, old value = 0.776910

	FUZZ s.separator.hu_1_1 = 0.202798; // fuzzed, old value = 0.204844
	FUZZ s.separator.hu_1_2 = 0.084498; // fuzzed, old value = 0.085645
	FUZZ s.separator.hu_0_1 = 0.246507; // fuzzed, old value = 0.243846
	FUZZ s.separator.hu_1_3 = 0.078855; // fuzzed, old value = 0.078700
	FUZZ s.separator.hu_0_2 = 0.260861; // fuzzed, old value = 0.257481
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.542411; // fuzzed, old value = 0.537944
	FUZZ s.separator.capHeightMax = 1.409655; // fuzzed, old value = 1.401996
	FUZZ s.separator.gdConst = 1.566152; // fuzzed, old value = 1.572080
	FUZZ s.separator.SurfCoef = 2.787800; // fuzzed, old value = 2.784337
	FUZZ s.separator.capHeightRatio = 0.239670; // fuzzed, old value = 0.240364
	FUZZ s.separator.capHeightRatio2 = 1.931978; // fuzzed, old value = 1.906820
	FUZZ s.separator.getRatio1 = 0.962255; // fuzzed, old value = 0.953113
	FUZZ s.separator.getRatio2 = 1.123699; // fuzzed, old value = 1.118809
	FUZZ s.separator.testSlashLine1 = 2.979245; // fuzzed, old value = 2.980766
	FUZZ s.separator.testSlashLine2 = 2.968102; // fuzzed, old value = 2.978094
	FUZZ s.separator.minDensity = 0.201806; // fuzzed, old value = 0.199811
	FUZZ s.separator.maxDensity = 0.836444; // fuzzed, old value = 0.841907
	FUZZ s.separator.extCapHeightMin = 0.296945; // fuzzed, old value = 0.298906
	FUZZ s.separator.extCapHeightMax = 2.009752; // fuzzed, old value = 2.002356
	FUZZ s.separator.extRatioMin = 0.283982; // fuzzed, old value = 0.280323
	FUZZ s.separator.extRatioMax = 1.477403; // fuzzed, old value = 1.479012
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.488464; // fuzzed, old value = 0.489715
	FUZZ s.labels.weightUnderline = 0.301452; // fuzzed, old value = 0.297516
	FUZZ s.labels.ratioBase = 0.828337; // fuzzed, old value = 0.822450
	FUZZ s.labels.ratioWeight = 0.301531; // fuzzed, old value = 0.301135
	FUZZ s.labels.adjustDec = 1.201686; // fuzzed, old value = 1.217858
	FUZZ s.labels.adjustInc = 0.826132; // fuzzed, old value = 0.822190
	FUZZ s.labels.sameLineEps = 0.135249; // fuzzed, old value = 0.136769
	FUZZ s.labels.heightRatio = 0.845491; // fuzzed, old value = 0.851375
	FUZZ s.labels.medHeightFactor = 0.470430; // fuzzed, old value = 0.469583
	FUZZ s.labels.capHeightError = 0.548447; // fuzzed, old value = 0.540661

	FUZZ s.lcomb.MaximalSymbolDistance = 2.843051; // fuzzed, old value = 2.879636
	FUZZ s.lcomb.TestSlashLineEps = 2.905471; // fuzzed, old value = 2.902987
	FUZZ s.lcomb.TestMinHeightFactor = 0.519487; // fuzzed, old value = 0.527117
	FUZZ s.lcomb.TestMaxHeightFactor = 1.179816; // fuzzed, old value = 1.186715
	FUZZ s.lcomb.RectHeightRatio = 0.506520; // fuzzed, old value = 0.501979
	FUZZ s.lcomb.H1SuperscriptSpace = 1.137963; // fuzzed, old value = 1.126268
	FUZZ s.lcomb.H2LowercaseSpace = 0.547308; // fuzzed, old value = 0.542800
	FUZZ s.lcomb.H3LowercaseSpace = 0.471881; // fuzzed, old value = 0.474390
	FUZZ s.lcomb.H4SubscriptSpace = 0.531275; // fuzzed, old value = 0.530197
	FUZZ s.lcomb.FillLabelFactor1 = 0.487926; // fuzzed, old value = 0.481058
	FUZZ s.lcomb.FillLabelFactor2 = 0.517524; // fuzzed, old value = 0.518346
}

