
void updateSettingsScanned(Settings &s)
{
	FUZZ s.general.UseProbablistics = false; // fuzzed, old value = false

	FUZZ s.separator.ext2charRatio = 1.825673; // fuzzed, old value = 1.8

	FUZZ s.molecule.LengthFactor_long = 0.328143; // fuzzed, old value = 0.326257
	FUZZ s.molecule.LengthFactor_medium = 0.399042; // fuzzed, old value = 0.407261
	FUZZ s.molecule.LengthFactor_default = 0.461662; // fuzzed, old value = 0.475722
	FUZZ s.molecule.LengthValue_long = 108.941492; // fuzzed, old value = 105.285405
	FUZZ s.molecule.LengthValue_medium = 78.957726; // fuzzed, old value = 82.218540
	FUZZ s.molecule.SpaceMultiply = 1.447843; // fuzzed, old value = 1.451593
	FUZZ s.molecule.AngleTreshold = 0.251429; // fuzzed, old value = 0.254860
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.731897; // fuzzed, old value = 17.266420
	FUZZ s.estimation.LineThickness = 6.101518; // fuzzed, old value = 6.159861
	FUZZ s.estimation.AvgBondLength = 30.355357; // fuzzed, old value = 31.393091
	FUZZ s.estimation.AddVertexEps = 5.258299; // fuzzed, old value = 5.503704
	FUZZ s.estimation.MaxSymRatio = 1.144596; // fuzzed, old value = 1.111715
	FUZZ s.estimation.MinSymRatio = 0.331593; // fuzzed, old value = 0.345335
	FUZZ s.estimation.ParLinesEps = 0.554123; // fuzzed, old value = 0.531030
	FUZZ s.estimation.SymHeightErr = 26.601544; // fuzzed, old value = 26.219498
	FUZZ s.estimation.CapitalHeightError = 0.830952; // fuzzed, old value = 0.791954
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.392604; // fuzzed, old value = 0.380356
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 116; // fuzzed, old value = 113
	FUZZ s.mbond.LongErr = 0.349333; // fuzzed, old value = 0.334002
	FUZZ s.mbond.MediumBond = 90; // fuzzed, old value = 93
	FUZZ s.mbond.MediumErr = 0.417903; // fuzzed, old value = 0.422610
	FUZZ s.mbond.DefaultErr = 0.661368; // fuzzed, old value = 0.636662
	FUZZ s.mbond.ParBondsEps = 0.349765; // fuzzed, old value = 0.357129
	FUZZ s.mbond.DoubleRatioTresh = 6.698078; // fuzzed, old value = 6.575693
	FUZZ s.mbond.DoubleCoef = 0.079779; // fuzzed, old value = 0.082118
	FUZZ s.mbond.DoubleMagic1 = 0.928173; // fuzzed, old value = 0.936964
	FUZZ s.mbond.DoubleMagic2 = 0.893623; // fuzzed, old value = 0.910859
	FUZZ s.mbond.DoubleTreshMin = 0.094915; // fuzzed, old value = 0.097570
	FUZZ s.mbond.DoubleTreshMax = 0.819377; // fuzzed, old value = 0.788495
	FUZZ s.mbond.MaxLen1 = 148.096251; // fuzzed, old value = 152.199320
	FUZZ s.mbond.MaxLen2 = 128.438369; // fuzzed, old value = 122.354618
	FUZZ s.mbond.MaxLen3 = 115.245539; // fuzzed, old value = 114.914302
	FUZZ s.mbond.MaxLen4 = 121.904961; // fuzzed, old value = 123.201192
	FUZZ s.mbond.MaxLen5 = 78.515883; // fuzzed, old value = 82.261154
	FUZZ s.mbond.MinLen1 = 86.077108; // fuzzed, old value = 82.289846
	FUZZ s.mbond.MinLen2 = 70.585346; // fuzzed, old value = 72.089418
	FUZZ s.mbond.mbe1 = 0.078287; // fuzzed, old value = 0.077937
	FUZZ s.mbond.mbe2 = 0.155200; // fuzzed, old value = 0.161612
	FUZZ s.mbond.mbe3 = 0.204358; // fuzzed, old value = 0.198577
	FUZZ s.mbond.mbe4 = 0.181471; // fuzzed, old value = 0.187475
	FUZZ s.mbond.mbe5 = 0.150696; // fuzzed, old value = 0.150162
	FUZZ s.mbond.mbe6 = 0.214467; // fuzzed, old value = 0.208881
	FUZZ s.mbond.mbe7 = 0.409692; // fuzzed, old value = 0.427654
	FUZZ s.mbond.mbe_def = 0.505000; // fuzzed, old value = 0.485556
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.362988; // fuzzed, old value = 0.369782
	FUZZ s.mbond.DoubleRightLengthTresh = 0.300957; // fuzzed, old value = 0.301503
	FUZZ s.mbond.TripleLeftLengthTresh = 0.250670; // fuzzed, old value = 0.260774
	FUZZ s.mbond.TripleRightLengthTresh = 0.237051; // fuzzed, old value = 0.243434
	FUZZ s.mbond.Case1LengthTresh = 96.038663; // fuzzed, old value = 99.932166
	FUZZ s.mbond.Case1Factor = 0.414420; // fuzzed, old value = 0.420878
	FUZZ s.mbond.Case2LengthTresh = 85.787621; // fuzzed, old value = 83.459482
	FUZZ s.mbond.Case2Factor = 0.676897; // fuzzed, old value = 0.680201
	FUZZ s.mbond.Case3Factor = 0.955388; // fuzzed, old value = 0.923178
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.105331; // fuzzed, old value = 0.100887
	FUZZ s.skeleton.BaseSmallErr = 0.158102; // fuzzed, old value = 0.154586
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 21
	FUZZ s.skeleton.ShortMul = 0.320851; // fuzzed, old value = 0.311474
	FUZZ s.skeleton.MediumBondLen = 91; // fuzzed, old value = 91
	FUZZ s.skeleton.MediumMul = 0.165673; // fuzzed, old value = 0.169169
	FUZZ s.skeleton.MediumSmallErr = 0.131925; // fuzzed, old value = 0.130840
	FUZZ s.skeleton.LongBondLen = 95; // fuzzed, old value = 98
	FUZZ s.skeleton.LongMul = 0.151792; // fuzzed, old value = 0.152036
	FUZZ s.skeleton.LongSmallErr = 0.060082; // fuzzed, old value = 0.061722
	FUZZ s.skeleton.BrokenRepairFactor = 3.295135; // fuzzed, old value = 3.245546
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.899700; // fuzzed, old value = 0.943793
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.704543; // fuzzed, old value = 2.690049
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.197811; // fuzzed, old value = 0.191982
	FUZZ s.skeleton.DissolveMinErr = 0.178492; // fuzzed, old value = 0.174539
	FUZZ s.skeleton.ConnectBlockS = 9.720539; // fuzzed, old value = 10.115969
	FUZZ s.skeleton.ConnectFactor = 2.048454; // fuzzed, old value = 2.047414
	FUZZ s.skeleton.JoinVerticiesConst = 0.102113; // fuzzed, old value = 0.105347
	FUZZ s.skeleton.DissolveConst = 0.093752; // fuzzed, old value = 0.093945
	FUZZ s.skeleton.Dissolve2Const = 0.192711; // fuzzed, old value = 0.200009
	FUZZ s.skeleton.Join2Const = 0.286231; // fuzzed, old value = 0.288378
	FUZZ s.skeleton.Join3Const = 0.198023; // fuzzed, old value = 0.190858
	FUZZ s.skeleton.DistTreshLimFactor = 1.968443; // fuzzed, old value = 1.914312
	FUZZ s.skeleton.SlopeFact1 = 0.096790; // fuzzed, old value = 0.100517
	FUZZ s.skeleton.SlopeFact2 = 0.174880; // fuzzed, old value = 0.168698
	FUZZ s.skeleton.ShrinkEps = 0.139416; // fuzzed, old value = 0.134322
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.096091; // fuzzed, old value = 0.093249
	FUZZ s.routines.Circle_GapMax = 1.073493; // fuzzed, old value = 1.070681
	FUZZ s.routines.Circle_RMax = 2.317711; // fuzzed, old value = 2.223885
	FUZZ s.routines.Circle_AvgRadius = 0.000100; // fuzzed, old value = 0.000105
	FUZZ s.routines.Circle_MaxRatio = 0.294712; // fuzzed, old value = 0.306751
	FUZZ s.routines.Algebra_IntersectionEps = 0.011280; // fuzzed, old value = 0.011099
	FUZZ s.routines.Algebra_SameLineEps = 0.229813; // fuzzed, old value = 0.238074
	FUZZ s.routines.Approx_Eps1 = 1.103166; // fuzzed, old value = 1.146226
	FUZZ s.routines.Approx_Eps2 = 0.850123; // fuzzed, old value = 0.837156
	FUZZ s.routines.Approx_CalcLineTresh = 0.970598; // fuzzed, old value = 0.931762
	FUZZ s.routines.Contour_Eps1 = 0.998267; // fuzzed, old value = 0.997319
	FUZZ s.routines.Contour_Eps2 = 0.701048; // fuzzed, old value = 0.716869

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.884470; // fuzzed, old value = 2.979421
	FUZZ s.wbe.SingleDownAngleMax = 44.022481; // fuzzed, old value = 44.552689
	FUZZ s.wbe.SingleDownDistancesMax = 10.309579; // fuzzed, old value = 10.671219
	FUZZ s.wbe.SingleDownLengthMax = 49.263221; // fuzzed, old value = 48.452524
	FUZZ s.wbe.SingleUpRatioEps = 1.588753; // fuzzed, old value = 1.645117
	FUZZ s.wbe.SingleUpDefCoeff = 0.289467; // fuzzed, old value = 0.289004
	FUZZ s.wbe.SingleUpIncCoeff = 0.482375; // fuzzed, old value = 0.464338
	FUZZ s.wbe.SingleUpIncLengthTresh = 35.403863; // fuzzed, old value = 36.797804
	FUZZ s.wbe.SingleUpInterpolateEps = 0.066340; // fuzzed, old value = 0.064479
	FUZZ s.wbe.SingleUpMagicAddition = 0.246178; // fuzzed, old value = 0.235734
	FUZZ s.wbe.SingleUpS2Divisor = 1.398121; // fuzzed, old value = 1.364030
	FUZZ s.wbe.SingleUpMinATresh = 1.727093; // fuzzed, old value = 1.676936
	FUZZ s.wbe.SingleUpSquareRatio = 0.686944; // fuzzed, old value = 0.660557
	FUZZ s.wbe.SingleUpAngleTresh = 0.067796; // fuzzed, old value = 0.068608
	FUZZ s.wbe.SomeTresh = 0.105018; // fuzzed, old value = 0.104967
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = true
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.005147; // fuzzed, old value = 1.032648
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.165551; // fuzzed, old value = 1.189242
	FUZZ s.characters.WriteEasyFactor = 0.954994; // fuzzed, old value = 0.955733
	FUZZ s.characters.WriteVeryEasyFactor = 0.937590; // fuzzed, old value = 0.943422
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.100596; // fuzzed, old value = 3.200512
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.151090; // fuzzed, old value = 3.212438
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.100272; // fuzzed, old value = 0.100490
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.587364; // fuzzed, old value = 2.700749
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.663155; // fuzzed, old value = 3.730317
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.886674; // fuzzed, old value = 0.857436
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.300252; // fuzzed, old value = 0.287946
	FUZZ s.characters.HW_Line = 1.514736; // fuzzed, old value = 1.576510
	FUZZ s.characters.HW_F = 3.499237; // fuzzed, old value = 3.470959
	FUZZ s.characters.HW_Tricky = 3.008418; // fuzzed, old value = 2.976322
	FUZZ s.characters.HW_Hard = 4.191641; // fuzzed, old value = 4.317237
	FUZZ s.characters.HW_Other = 3.636595; // fuzzed, old value = 3.528245

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.506318; // fuzzed, old value = 0.483161
	FUZZ s.csr.DeleteBadTriangles = 1.893943; // fuzzed, old value = 1.884491
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.656589; // fuzzed, old value = 1.665272

	FUZZ s.graph.MinimalDistTresh = 1.977594; // fuzzed, old value = 2.030016
	FUZZ s.graph.RatioSub = 1.004634; // fuzzed, old value = 1.019085
	FUZZ s.graph.RatioTresh = 0.455552; // fuzzed, old value = 0.457590

	FUZZ s.utils.SlashLineDensity = 0.417596; // fuzzed, old value = 0.417533
	FUZZ s.utils.TestPlusDensity = 0.425760; // fuzzed, old value = 0.412635
	FUZZ s.utils.TestPlusSq = 0.431653; // fuzzed, old value = 0.427405
	FUZZ s.utils.TestMinusRatio = 0.351097; // fuzzed, old value = 0.359109
	FUZZ s.utils.TestMinusDensity = 0.590664; // fuzzed, old value = 0.619346
	FUZZ s.utils.TestMinusHeightFactor = 0.865960; // fuzzed, old value = 0.882863

	FUZZ s.separator.hu_1_1 = 0.205260; // fuzzed, old value = 0.204218
	FUZZ s.separator.hu_1_2 = 0.073316; // fuzzed, old value = 0.077060
	FUZZ s.separator.hu_0_1 = 0.211154; // fuzzed, old value = 0.211903
	FUZZ s.separator.hu_1_3 = 0.086343; // fuzzed, old value = 0.083353
	FUZZ s.separator.hu_0_2 = 0.213270; // fuzzed, old value = 0.221137
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.536738; // fuzzed, old value = 0.548649
	FUZZ s.separator.capHeightMax = 1.428743; // fuzzed, old value = 1.422053
	FUZZ s.separator.gdConst = 1.644978; // fuzzed, old value = 1.577849
	FUZZ s.separator.SurfCoef = 3.062094; // fuzzed, old value = 3.043107
	FUZZ s.separator.capHeightRatio = 0.268138; // fuzzed, old value = 0.255828
	FUZZ s.separator.capHeightRatio2 = 1.950693; // fuzzed, old value = 1.990900
	FUZZ s.separator.getRatio1 = 1.021081; // fuzzed, old value = 1.027050
	FUZZ s.separator.getRatio2 = 1.212365; // fuzzed, old value = 1.178795
	FUZZ s.separator.testSlashLine1 = 2.873200; // fuzzed, old value = 2.800747
	FUZZ s.separator.testSlashLine2 = 2.783841; // fuzzed, old value = 2.825599
	FUZZ s.separator.minDensity = 0.197599; // fuzzed, old value = 0.188964
	FUZZ s.separator.maxDensity = 0.914575; // fuzzed, old value = 0.897243
	FUZZ s.separator.extCapHeightMin = 0.298018; // fuzzed, old value = 0.306803
	FUZZ s.separator.extCapHeightMax = 2.202968; // fuzzed, old value = 2.133889
	FUZZ s.separator.extRatioMin = 0.318563; // fuzzed, old value = 0.306250
	FUZZ s.separator.extRatioMax = 1.589661; // fuzzed, old value = 1.643632
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.414514; // fuzzed, old value = 0.411425
	FUZZ s.labels.weightUnderline = 0.305772; // fuzzed, old value = 0.314497
	FUZZ s.labels.ratioBase = 0.827762; // fuzzed, old value = 0.823183
	FUZZ s.labels.ratioWeight = 0.282586; // fuzzed, old value = 0.289456
	FUZZ s.labels.adjustDec = 1.271521; // fuzzed, old value = 1.219722
	FUZZ s.labels.adjustInc = 0.773808; // fuzzed, old value = 0.782908
	FUZZ s.labels.sameLineEps = 0.125695; // fuzzed, old value = 0.122176
	FUZZ s.labels.heightRatio = 0.820358; // fuzzed, old value = 0.830282
	FUZZ s.labels.medHeightFactor = 0.485083; // fuzzed, old value = 0.498141
	FUZZ s.labels.capHeightError = 0.519704; // fuzzed, old value = 0.540784

	FUZZ s.lcomb.MaximalSymbolDistance = 2.631569; // fuzzed, old value = 2.602331
	FUZZ s.lcomb.TestSlashLineEps = 3.138795; // fuzzed, old value = 3.020770
	FUZZ s.lcomb.TestMinHeightFactor = 0.527250; // fuzzed, old value = 0.513139
	FUZZ s.lcomb.TestMaxHeightFactor = 1.047742; // fuzzed, old value = 1.075404
	FUZZ s.lcomb.RectHeightRatio = 0.469624; // fuzzed, old value = 0.487107
	FUZZ s.lcomb.H1SuperscriptSpace = 1.103145; // fuzzed, old value = 1.155086
	FUZZ s.lcomb.H2LowercaseSpace = 0.515508; // fuzzed, old value = 0.516421
	FUZZ s.lcomb.H3LowercaseSpace = 0.434194; // fuzzed, old value = 0.443479
	FUZZ s.lcomb.H4SubscriptSpace = 0.534505; // fuzzed, old value = 0.545276
	FUZZ s.lcomb.FillLabelFactor1 = 0.524573; // fuzzed, old value = 0.540356
	FUZZ s.lcomb.FillLabelFactor2 = 0.555762; // fuzzed, old value = 0.560563
}
