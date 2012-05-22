
void updateSettingsHighResolution(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.324124; // fuzzed, old value = 0.325504
	FUZZ s.molecule.LengthFactor_medium = 0.420221; // fuzzed, old value = 0.422746
	FUZZ s.molecule.LengthFactor_default = 0.486020; // fuzzed, old value = 0.502907
	FUZZ s.molecule.LengthValue_long = 96.152613; // fuzzed, old value = 100.372344
	FUZZ s.molecule.LengthValue_medium = 85.430506; // fuzzed, old value = 87.508113
	FUZZ s.molecule.SpaceMultiply = 1.576670; // fuzzed, old value = 1.522845
	FUZZ s.molecule.AngleTreshold = 0.258753; // fuzzed, old value = 0.261905
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.236222; // fuzzed, old value = 16.427625
	FUZZ s.estimation.LineThickness = 6.082790; // fuzzed, old value = 6.271123
	FUZZ s.estimation.AvgBondLength = 30.045592; // fuzzed, old value = 29.187307
	FUZZ s.estimation.AddVertexEps = 5.590977; // fuzzed, old value = 5.338316
	FUZZ s.estimation.MaxSymRatio = 1.044062; // fuzzed, old value = 1.075217
	FUZZ s.estimation.MinSymRatio = 0.331161; // fuzzed, old value = 0.324970
	FUZZ s.estimation.ParLinesEps = 0.506585; // fuzzed, old value = 0.500045
	FUZZ s.estimation.SymHeightErr = 29.395708; // fuzzed, old value = 29.986198
	FUZZ s.estimation.CapitalHeightError = 0.840920; // fuzzed, old value = 0.849581
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.549555; // fuzzed, old value = 0.527501
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 124; // fuzzed, old value = 120
	FUZZ s.mbond.LongErr = 0.397510; // fuzzed, old value = 0.379442
	FUZZ s.mbond.MediumBond = 96; // fuzzed, old value = 92
	FUZZ s.mbond.MediumErr = 0.390505; // fuzzed, old value = 0.374411
	FUZZ s.mbond.DefaultErr = 0.651656; // fuzzed, old value = 0.633215
	FUZZ s.mbond.ParBondsEps = 0.357443; // fuzzed, old value = 0.347403
	FUZZ s.mbond.DoubleRatioTresh = 7.105239; // fuzzed, old value = 7.301635
	FUZZ s.mbond.DoubleCoef = 0.080682; // fuzzed, old value = 0.080239
	FUZZ s.mbond.DoubleMagic1 = 0.890559; // fuzzed, old value = 0.912245
	FUZZ s.mbond.DoubleMagic2 = 1.036218; // fuzzed, old value = 1.014773
	FUZZ s.mbond.DoubleTreshMin = 0.095995; // fuzzed, old value = 0.097689
	FUZZ s.mbond.DoubleTreshMax = 0.840206; // fuzzed, old value = 0.877638
	FUZZ s.mbond.MaxLen1 = 152.195706; // fuzzed, old value = 158.294993
	FUZZ s.mbond.MaxLen2 = 125.043360; // fuzzed, old value = 125.479342
	FUZZ s.mbond.MaxLen3 = 111.259457; // fuzzed, old value = 110.907276
	FUZZ s.mbond.MaxLen4 = 111.844062; // fuzzed, old value = 107.998827
	FUZZ s.mbond.MaxLen5 = 85.385902; // fuzzed, old value = 88.239751
	FUZZ s.mbond.MinLen1 = 84.611899; // fuzzed, old value = 86.865383
	FUZZ s.mbond.MinLen2 = 75.956955; // fuzzed, old value = 74.074407
	FUZZ s.mbond.mbe1 = 0.079587; // fuzzed, old value = 0.081638
	FUZZ s.mbond.mbe2 = 0.156165; // fuzzed, old value = 0.153054
	FUZZ s.mbond.mbe3 = 0.209716; // fuzzed, old value = 0.201820
	FUZZ s.mbond.mbe4 = 0.178945; // fuzzed, old value = 0.186926
	FUZZ s.mbond.mbe5 = 0.161898; // fuzzed, old value = 0.160446
	FUZZ s.mbond.mbe6 = 0.212444; // fuzzed, old value = 0.213536
	FUZZ s.mbond.mbe7 = 0.390860; // fuzzed, old value = 0.397030
	FUZZ s.mbond.mbe_def = 0.530534; // fuzzed, old value = 0.523376
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.324307; // fuzzed, old value = 0.336214
	FUZZ s.mbond.DoubleRightLengthTresh = 0.316706; // fuzzed, old value = 0.301899
	FUZZ s.mbond.TripleLeftLengthTresh = 0.261429; // fuzzed, old value = 0.268002
	FUZZ s.mbond.TripleRightLengthTresh = 0.241369; // fuzzed, old value = 0.233726
	FUZZ s.mbond.Case1LengthTresh = 101.723163; // fuzzed, old value = 104.470016
	FUZZ s.mbond.Case1Factor = 0.438665; // fuzzed, old value = 0.440431
	FUZZ s.mbond.Case2LengthTresh = 75.976919; // fuzzed, old value = 76.500471
	FUZZ s.mbond.Case2Factor = 0.679186; // fuzzed, old value = 0.707674
	FUZZ s.mbond.Case3Factor = 0.895626; // fuzzed, old value = 0.908999
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.093965; // fuzzed, old value = 0.095487
	FUZZ s.skeleton.BaseSmallErr = 0.146217; // fuzzed, old value = 0.152690
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.325797; // fuzzed, old value = 0.325208
	FUZZ s.skeleton.MediumBondLen = 88; // fuzzed, old value = 88
	FUZZ s.skeleton.MediumMul = 0.179444; // fuzzed, old value = 0.182107
	FUZZ s.skeleton.MediumSmallErr = 0.140426; // fuzzed, old value = 0.139697
	FUZZ s.skeleton.LongBondLen = 106; // fuzzed, old value = 104
	FUZZ s.skeleton.LongMul = 0.142735; // fuzzed, old value = 0.150157
	FUZZ s.skeleton.LongSmallErr = 0.059545; // fuzzed, old value = 0.060531
	FUZZ s.skeleton.BrokenRepairFactor = 3.060011; // fuzzed, old value = 3.026944
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.006734; // fuzzed, old value = 1.000749
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.612223; // fuzzed, old value = 2.690325
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.209759; // fuzzed, old value = 0.202691
	FUZZ s.skeleton.DissolveMinErr = 0.177584; // fuzzed, old value = 0.179633
	FUZZ s.skeleton.ConnectBlockS = 9.868964; // fuzzed, old value = 10.121119
	FUZZ s.skeleton.ConnectFactor = 2.034564; // fuzzed, old value = 2.095784
	FUZZ s.skeleton.JoinVerticiesConst = 0.098641; // fuzzed, old value = 0.101323
	FUZZ s.skeleton.DissolveConst = 0.097799; // fuzzed, old value = 0.099845
	FUZZ s.skeleton.Dissolve2Const = 0.202550; // fuzzed, old value = 0.199018
	FUZZ s.skeleton.Join2Const = 0.344447; // fuzzed, old value = 0.348574
	FUZZ s.skeleton.Join3Const = 0.185361; // fuzzed, old value = 0.183421
	FUZZ s.skeleton.DistTreshLimFactor = 1.959898; // fuzzed, old value = 1.911499
	FUZZ s.skeleton.SlopeFact1 = 0.102810; // fuzzed, old value = 0.099213
	FUZZ s.skeleton.SlopeFact2 = 0.187030; // fuzzed, old value = 0.189956
	FUZZ s.skeleton.ShrinkEps = 0.125537; // fuzzed, old value = 0.124760
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.100554; // fuzzed, old value = 0.099827
	FUZZ s.routines.Circle_GapMax = 0.932546; // fuzzed, old value = 0.891744
	FUZZ s.routines.Circle_RMax = 1.977611; // fuzzed, old value = 1.976824
	FUZZ s.routines.Circle_AvgRadius = 0.000107; // fuzzed, old value = 0.000108
	FUZZ s.routines.Circle_MaxRatio = 0.316171; // fuzzed, old value = 0.321716
	FUZZ s.routines.Algebra_IntersectionEps = 0.010270; // fuzzed, old value = 0.010061
	FUZZ s.routines.Algebra_SameLineEps = 0.204530; // fuzzed, old value = 0.203622
	FUZZ s.routines.Approx_Eps1 = 1.186415; // fuzzed, old value = 1.194374
	FUZZ s.routines.Approx_Eps2 = 0.853606; // fuzzed, old value = 0.891238
	FUZZ s.routines.Approx_CalcLineTresh = 0.883062; // fuzzed, old value = 0.910738

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.825313; // fuzzed, old value = 2.965677
	FUZZ s.wbe.SingleDownAngleMax = 43.369028; // fuzzed, old value = 44.299925
	FUZZ s.wbe.SingleDownDistancesMax = 9.387568; // fuzzed, old value = 9.848462
	FUZZ s.wbe.SingleDownLengthMax = 45.148061; // fuzzed, old value = 45.311027
	FUZZ s.wbe.SingleUpRatioEps = 1.857780; // fuzzed, old value = 1.780768
	FUZZ s.wbe.SingleUpDefCoeff = 0.276198; // fuzzed, old value = 0.275792
	FUZZ s.wbe.SingleUpIncCoeff = 0.403629; // fuzzed, old value = 0.405128
	FUZZ s.wbe.SingleUpIncLengthTresh = 33.085597; // fuzzed, old value = 34.609693
	FUZZ s.wbe.SingleUpInterpolateEps = 0.064242; // fuzzed, old value = 0.061981
	FUZZ s.wbe.SingleUpMagicAddition = 0.222099; // fuzzed, old value = 0.224210
	FUZZ s.wbe.SingleUpS2Divisor = 1.676413; // fuzzed, old value = 1.730414
	FUZZ s.wbe.SingleUpMinATresh = 1.664201; // fuzzed, old value = 1.698006
	FUZZ s.wbe.SingleUpSquareRatio = 0.624243; // fuzzed, old value = 0.653076
	FUZZ s.wbe.SingleUpAngleTresh = 0.066464; // fuzzed, old value = 0.065977
	FUZZ s.wbe.SomeTresh = 0.102920; // fuzzed, old value = 0.098673
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = false; // fuzzed, old value = true
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.037296; // fuzzed, old value = 1.072382
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.190245; // fuzzed, old value = 1.149205
	FUZZ s.characters.WriteEasyFactor = 0.943543; // fuzzed, old value = 0.940425
	FUZZ s.characters.WriteVeryEasyFactor = 0.848463; // fuzzed, old value = 0.832404
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.095659; // fuzzed, old value = 2.959878
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.440570; // fuzzed, old value = 3.356067
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.104028; // fuzzed, old value = 0.099669
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.475237; // fuzzed, old value = 2.556935
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.440898; // fuzzed, old value = 3.595237
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.043977; // fuzzed, old value = 0.995833
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.311881; // fuzzed, old value = 0.306773
	FUZZ s.characters.HW_Line = 1.625300; // fuzzed, old value = 1.651793
	FUZZ s.characters.HW_F = 3.339170; // fuzzed, old value = 3.274989
	FUZZ s.characters.HW_Tricky = 2.724553; // fuzzed, old value = 2.759822
	FUZZ s.characters.HW_Hard = 4.529712; // fuzzed, old value = 4.318216
	FUZZ s.characters.HW_Other = 3.439210; // fuzzed, old value = 3.600776

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.472175; // fuzzed, old value = 0.493647
	FUZZ s.csr.DeleteBadTriangles = 1.817066; // fuzzed, old value = 1.891627
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.488868; // fuzzed, old value = 1.513964

	FUZZ s.graph.MinimalDistTresh = 2.175454; // fuzzed, old value = 2.096127
	FUZZ s.graph.RatioSub = 0.928355; // fuzzed, old value = 0.945973
	FUZZ s.graph.RatioTresh = 0.422903; // fuzzed, old value = 0.413262

	FUZZ s.utils.SlashLineDensity = 0.462468; // fuzzed, old value = 0.486265
	FUZZ s.utils.TestPlusDensity = 0.448106; // fuzzed, old value = 0.429479
	FUZZ s.utils.TestPlusSq = 0.410437; // fuzzed, old value = 0.418347
	FUZZ s.utils.TestMinusRatio = 0.344846; // fuzzed, old value = 0.362805
	FUZZ s.utils.TestMinusDensity = 0.584567; // fuzzed, old value = 0.605758
	FUZZ s.utils.TestMinusHeightFactor = 0.776910; // fuzzed, old value = 0.783296

	FUZZ s.separator.hu_1_1 = 0.204844; // fuzzed, old value = 0.198042
	FUZZ s.separator.hu_1_2 = 0.085645; // fuzzed, old value = 0.086904
	FUZZ s.separator.hu_0_1 = 0.243846; // fuzzed, old value = 0.243071
	FUZZ s.separator.hu_1_3 = 0.078700; // fuzzed, old value = 0.081547
	FUZZ s.separator.hu_0_2 = 0.257481; // fuzzed, old value = 0.257670
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.537944; // fuzzed, old value = 0.536388
	FUZZ s.separator.capHeightMax = 1.401996; // fuzzed, old value = 1.395258
	FUZZ s.separator.gdConst = 1.572080; // fuzzed, old value = 1.512571
	FUZZ s.separator.SurfCoef = 2.784337; // fuzzed, old value = 2.878732
	FUZZ s.separator.capHeightRatio = 0.240364; // fuzzed, old value = 0.244646
	FUZZ s.separator.capHeightRatio2 = 1.906820; // fuzzed, old value = 1.886779
	FUZZ s.separator.getRatio1 = 0.953113; // fuzzed, old value = 0.914414
	FUZZ s.separator.getRatio2 = 1.118809; // fuzzed, old value = 1.081077
	FUZZ s.separator.testSlashLine1 = 2.980766; // fuzzed, old value = 2.875854
	FUZZ s.separator.testSlashLine2 = 2.978094; // fuzzed, old value = 2.928962
	FUZZ s.separator.minDensity = 0.199811; // fuzzed, old value = 0.199450
	FUZZ s.separator.maxDensity = 0.841907; // fuzzed, old value = 0.862675
	FUZZ s.separator.extCapHeightMin = 0.298906; // fuzzed, old value = 0.300420
	FUZZ s.separator.extCapHeightMax = 2.002356; // fuzzed, old value = 2.050456
	FUZZ s.separator.extRatioMin = 0.280323; // fuzzed, old value = 0.286860
	FUZZ s.separator.extRatioMax = 1.479012; // fuzzed, old value = 1.472377
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.489715; // fuzzed, old value = 0.479917
	FUZZ s.labels.weightUnderline = 0.297516; // fuzzed, old value = 0.295936
	FUZZ s.labels.ratioBase = 0.822450; // fuzzed, old value = 0.826168
	FUZZ s.labels.ratioWeight = 0.301135; // fuzzed, old value = 0.293752
	FUZZ s.labels.adjustDec = 1.217858; // fuzzed, old value = 1.241252
	FUZZ s.labels.adjustInc = 0.822190; // fuzzed, old value = 0.828367
	FUZZ s.labels.sameLineEps = 0.136769; // fuzzed, old value = 0.133123
	FUZZ s.labels.heightRatio = 0.851375; // fuzzed, old value = 0.815722
	FUZZ s.labels.medHeightFactor = 0.469583; // fuzzed, old value = 0.470264
	FUZZ s.labels.capHeightError = 0.540661; // fuzzed, old value = 0.555360

	FUZZ s.lcomb.MaximalSymbolDistance = 2.879636; // fuzzed, old value = 2.803218
	FUZZ s.lcomb.TestSlashLineEps = 2.902987; // fuzzed, old value = 2.937016
	FUZZ s.lcomb.TestMinHeightFactor = 0.527117; // fuzzed, old value = 0.520408
	FUZZ s.lcomb.TestMaxHeightFactor = 1.186715; // fuzzed, old value = 1.140217
	FUZZ s.lcomb.RectHeightRatio = 0.501979; // fuzzed, old value = 0.488442
	FUZZ s.lcomb.H1SuperscriptSpace = 1.126268; // fuzzed, old value = 1.147570
	FUZZ s.lcomb.H2LowercaseSpace = 0.542800; // fuzzed, old value = 0.518076
	FUZZ s.lcomb.H3LowercaseSpace = 0.474390; // fuzzed, old value = 0.472786
	FUZZ s.lcomb.H4SubscriptSpace = 0.530197; // fuzzed, old value = 0.523799
	FUZZ s.lcomb.FillLabelFactor1 = 0.481058; // fuzzed, old value = 0.485908
	FUZZ s.lcomb.FillLabelFactor2 = 0.518346; // fuzzed, old value = 0.519166
}

