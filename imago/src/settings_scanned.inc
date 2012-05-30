
void updateSettingsScanned(Settings &s)
{
	FUZZ s.general.UseProbablistics = false; // fuzzed, old value = false

	FUZZ s.separator.extRatioMax = 2.0;

	FUZZ s.molecule.LengthFactor_long = 0.326257; // fuzzed, old value = 0.321022
	FUZZ s.molecule.LengthFactor_medium = 0.407261; // fuzzed, old value = 0.420107
	FUZZ s.molecule.LengthFactor_default = 0.475722; // fuzzed, old value = 0.460187
	FUZZ s.molecule.LengthValue_long = 105.285405; // fuzzed, old value = 104.091122
	FUZZ s.molecule.LengthValue_medium = 82.218540; // fuzzed, old value = 82.971224
	FUZZ s.molecule.SpaceMultiply = 1.451593; // fuzzed, old value = 1.465563
	FUZZ s.molecule.AngleTreshold = 0.254860; // fuzzed, old value = 0.254622
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.266420; // fuzzed, old value = 17.528950
	FUZZ s.estimation.LineThickness = 6.159861; // fuzzed, old value = 5.893582
	FUZZ s.estimation.AvgBondLength = 31.393091; // fuzzed, old value = 31.301433
	FUZZ s.estimation.AddVertexEps = 5.503704; // fuzzed, old value = 5.301112
	FUZZ s.estimation.MaxSymRatio = 1.111715; // fuzzed, old value = 1.126165
	FUZZ s.estimation.MinSymRatio = 0.345335; // fuzzed, old value = 0.350735
	FUZZ s.estimation.ParLinesEps = 0.531030; // fuzzed, old value = 0.540122
	FUZZ s.estimation.SymHeightErr = 26.219498; // fuzzed, old value = 26.390444
	FUZZ s.estimation.CapitalHeightError = 0.791954; // fuzzed, old value = 0.826375
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.380356; // fuzzed, old value = 0.386344
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 113; // fuzzed, old value = 118
	FUZZ s.mbond.LongErr = 0.334002; // fuzzed, old value = 0.345250
	FUZZ s.mbond.MediumBond = 93; // fuzzed, old value = 95
	FUZZ s.mbond.MediumErr = 0.422610; // fuzzed, old value = 0.420392
	FUZZ s.mbond.DefaultErr = 0.636662; // fuzzed, old value = 0.640290
	FUZZ s.mbond.ParBondsEps = 0.357129; // fuzzed, old value = 0.349891
	FUZZ s.mbond.DoubleRatioTresh = 6.575693; // fuzzed, old value = 6.890152
	FUZZ s.mbond.DoubleCoef = 0.082118; // fuzzed, old value = 0.083351
	FUZZ s.mbond.DoubleMagic1 = 0.936964; // fuzzed, old value = 0.903704
	FUZZ s.mbond.DoubleMagic2 = 0.910859; // fuzzed, old value = 0.929231
	FUZZ s.mbond.DoubleTreshMin = 0.097570; // fuzzed, old value = 0.096268
	FUZZ s.mbond.DoubleTreshMax = 0.788495; // fuzzed, old value = 0.789718
	FUZZ s.mbond.MaxLen1 = 152.199320; // fuzzed, old value = 150.301458
	FUZZ s.mbond.MaxLen2 = 122.354618; // fuzzed, old value = 117.303518
	FUZZ s.mbond.MaxLen3 = 114.914302; // fuzzed, old value = 110.137487
	FUZZ s.mbond.MaxLen4 = 123.201192; // fuzzed, old value = 124.935078
	FUZZ s.mbond.MaxLen5 = 82.261154; // fuzzed, old value = 80.545022
	FUZZ s.mbond.MinLen1 = 82.289846; // fuzzed, old value = 82.954275
	FUZZ s.mbond.MinLen2 = 72.089418; // fuzzed, old value = 71.976402
	FUZZ s.mbond.mbe1 = 0.077937; // fuzzed, old value = 0.077402
	FUZZ s.mbond.mbe2 = 0.161612; // fuzzed, old value = 0.155140
	FUZZ s.mbond.mbe3 = 0.198577; // fuzzed, old value = 0.203549
	FUZZ s.mbond.mbe4 = 0.187475; // fuzzed, old value = 0.180815
	FUZZ s.mbond.mbe5 = 0.150162; // fuzzed, old value = 0.152986
	FUZZ s.mbond.mbe6 = 0.208881; // fuzzed, old value = 0.217324
	FUZZ s.mbond.mbe7 = 0.427654; // fuzzed, old value = 0.413760
	FUZZ s.mbond.mbe_def = 0.485556; // fuzzed, old value = 0.497985
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.369782; // fuzzed, old value = 0.353233
	FUZZ s.mbond.DoubleRightLengthTresh = 0.301503; // fuzzed, old value = 0.309044
	FUZZ s.mbond.TripleLeftLengthTresh = 0.260774; // fuzzed, old value = 0.258566
	FUZZ s.mbond.TripleRightLengthTresh = 0.243434; // fuzzed, old value = 0.232501
	FUZZ s.mbond.Case1LengthTresh = 99.932166; // fuzzed, old value = 101.450031
	FUZZ s.mbond.Case1Factor = 0.420878; // fuzzed, old value = 0.436382
	FUZZ s.mbond.Case2LengthTresh = 83.459482; // fuzzed, old value = 80.704752
	FUZZ s.mbond.Case2Factor = 0.680201; // fuzzed, old value = 0.689868
	FUZZ s.mbond.Case3Factor = 0.923178; // fuzzed, old value = 0.884472
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.100887; // fuzzed, old value = 0.101611
	FUZZ s.skeleton.BaseSmallErr = 0.154586; // fuzzed, old value = 0.148515
	FUZZ s.skeleton.ShortBondLen = 21; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.311474; // fuzzed, old value = 0.307587
	FUZZ s.skeleton.MediumBondLen = 91; // fuzzed, old value = 87
	FUZZ s.skeleton.MediumMul = 0.169169; // fuzzed, old value = 0.174425
	FUZZ s.skeleton.MediumSmallErr = 0.130840; // fuzzed, old value = 0.136617
	FUZZ s.skeleton.LongBondLen = 98; // fuzzed, old value = 101
	FUZZ s.skeleton.LongMul = 0.152036; // fuzzed, old value = 0.146406
	FUZZ s.skeleton.LongSmallErr = 0.061722; // fuzzed, old value = 0.059625
	FUZZ s.skeleton.BrokenRepairFactor = 3.245546; // fuzzed, old value = 3.136218
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.943793; // fuzzed, old value = 0.964520
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.690049; // fuzzed, old value = 2.605072
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.191982; // fuzzed, old value = 0.187225
	FUZZ s.skeleton.DissolveMinErr = 0.174539; // fuzzed, old value = 0.174400
	FUZZ s.skeleton.ConnectBlockS = 10.115969; // fuzzed, old value = 10.054614
	FUZZ s.skeleton.ConnectFactor = 2.047414; // fuzzed, old value = 2.115938
	FUZZ s.skeleton.JoinVerticiesConst = 0.105347; // fuzzed, old value = 0.106920
	FUZZ s.skeleton.DissolveConst = 0.093945; // fuzzed, old value = 0.096648
	FUZZ s.skeleton.Dissolve2Const = 0.200009; // fuzzed, old value = 0.199371
	FUZZ s.skeleton.Join2Const = 0.288378; // fuzzed, old value = 0.302455
	FUZZ s.skeleton.Join3Const = 0.190858; // fuzzed, old value = 0.197244
	FUZZ s.skeleton.DistTreshLimFactor = 1.914312; // fuzzed, old value = 1.930570
	FUZZ s.skeleton.SlopeFact1 = 0.100517; // fuzzed, old value = 0.101889
	FUZZ s.skeleton.SlopeFact2 = 0.168698; // fuzzed, old value = 0.177069
	FUZZ s.skeleton.ShrinkEps = 0.134322; // fuzzed, old value = 0.134801
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.093249; // fuzzed, old value = 0.096824
	FUZZ s.routines.Circle_GapMax = 1.070681; // fuzzed, old value = 1.037537
	FUZZ s.routines.Circle_RMax = 2.223885; // fuzzed, old value = 2.194858
	FUZZ s.routines.Circle_AvgRadius = 0.000105; // fuzzed, old value = 0.000105
	FUZZ s.routines.Circle_MaxRatio = 0.306751; // fuzzed, old value = 0.322105
	FUZZ s.routines.Algebra_IntersectionEps = 0.011099; // fuzzed, old value = 0.011352
	FUZZ s.routines.Algebra_SameLineEps = 0.238074; // fuzzed, old value = 0.228230
	FUZZ s.routines.Approx_Eps1 = 1.146226; // fuzzed, old value = 1.169994
	FUZZ s.routines.Approx_Eps2 = 0.837156; // fuzzed, old value = 0.797894
	FUZZ s.routines.Approx_CalcLineTresh = 0.931762; // fuzzed, old value = 0.912416
	FUZZ s.routines.Contour_Eps1 = 0.997319; // fuzzed, old value = 1.039739
	FUZZ s.routines.Contour_Eps2 = 0.716869; // fuzzed, old value = 0.685176

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.979421; // fuzzed, old value = 2.981664
	FUZZ s.wbe.SingleDownAngleMax = 44.552689; // fuzzed, old value = 46.740957
	FUZZ s.wbe.SingleDownDistancesMax = 10.671219; // fuzzed, old value = 10.733935
	FUZZ s.wbe.SingleDownLengthMax = 48.452524; // fuzzed, old value = 47.645301
	FUZZ s.wbe.SingleUpRatioEps = 1.645117; // fuzzed, old value = 1.646250
	FUZZ s.wbe.SingleUpDefCoeff = 0.289004; // fuzzed, old value = 0.292954
	FUZZ s.wbe.SingleUpIncCoeff = 0.464338; // fuzzed, old value = 0.458588
	FUZZ s.wbe.SingleUpIncLengthTresh = 36.797804; // fuzzed, old value = 35.050723
	FUZZ s.wbe.SingleUpInterpolateEps = 0.064479; // fuzzed, old value = 0.064031
	FUZZ s.wbe.SingleUpMagicAddition = 0.235734; // fuzzed, old value = 0.228246
	FUZZ s.wbe.SingleUpS2Divisor = 1.364030; // fuzzed, old value = 1.363695
	FUZZ s.wbe.SingleUpMinATresh = 1.676936; // fuzzed, old value = 1.671470
	FUZZ s.wbe.SingleUpSquareRatio = 0.660557; // fuzzed, old value = 0.655185
	FUZZ s.wbe.SingleUpAngleTresh = 0.068608; // fuzzed, old value = 0.067840
	FUZZ s.wbe.SomeTresh = 0.104967; // fuzzed, old value = 0.103064
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = false
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.032648; // fuzzed, old value = 1.056262
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.189242; // fuzzed, old value = 1.185488
	FUZZ s.characters.WriteEasyFactor = 0.955733; // fuzzed, old value = 0.999335
	FUZZ s.characters.WriteVeryEasyFactor = 0.943422; // fuzzed, old value = 0.952182
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.200512; // fuzzed, old value = 3.339501
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.212438; // fuzzed, old value = 3.184300
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.100490; // fuzzed, old value = 0.102537
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.700749; // fuzzed, old value = 2.714880
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.730317; // fuzzed, old value = 3.631109
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.857436; // fuzzed, old value = 0.889722
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.287946; // fuzzed, old value = 0.285258
	FUZZ s.characters.HW_Line = 1.576510; // fuzzed, old value = 1.596829
	FUZZ s.characters.HW_F = 3.470959; // fuzzed, old value = 3.403389
	FUZZ s.characters.HW_Tricky = 2.976322; // fuzzed, old value = 2.860566
	FUZZ s.characters.HW_Hard = 4.317237; // fuzzed, old value = 4.218750
	FUZZ s.characters.HW_Other = 3.528245; // fuzzed, old value = 3.559219

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.483161; // fuzzed, old value = 0.466614
	FUZZ s.csr.DeleteBadTriangles = 1.884491; // fuzzed, old value = 1.855713
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.665272; // fuzzed, old value = 1.678800

	FUZZ s.graph.MinimalDistTresh = 2.030016; // fuzzed, old value = 1.937290
	FUZZ s.graph.RatioSub = 1.019085; // fuzzed, old value = 0.988634
	FUZZ s.graph.RatioTresh = 0.457590; // fuzzed, old value = 0.445083

	FUZZ s.utils.SlashLineDensity = 0.417533; // fuzzed, old value = 0.437990
	FUZZ s.utils.TestPlusDensity = 0.412635; // fuzzed, old value = 0.408481
	FUZZ s.utils.TestPlusSq = 0.427405; // fuzzed, old value = 0.410596
	FUZZ s.utils.TestMinusRatio = 0.359109; // fuzzed, old value = 0.359789
	FUZZ s.utils.TestMinusDensity = 0.619346; // fuzzed, old value = 0.640361
	FUZZ s.utils.TestMinusHeightFactor = 0.882863; // fuzzed, old value = 0.864582

	FUZZ s.separator.hu_1_1 = 0.204218; // fuzzed, old value = 0.209062
	FUZZ s.separator.hu_1_2 = 0.077060; // fuzzed, old value = 0.076775
	FUZZ s.separator.hu_0_1 = 0.211903; // fuzzed, old value = 0.222737
	FUZZ s.separator.hu_1_3 = 0.083353; // fuzzed, old value = 0.079899
	FUZZ s.separator.hu_0_2 = 0.221137; // fuzzed, old value = 0.231772
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.548649; // fuzzed, old value = 0.577429
	FUZZ s.separator.capHeightMax = 1.422053; // fuzzed, old value = 1.403834
	FUZZ s.separator.gdConst = 1.577849; // fuzzed, old value = 1.570905
	FUZZ s.separator.SurfCoef = 3.043107; // fuzzed, old value = 2.938822
	FUZZ s.separator.capHeightRatio = 0.255828; // fuzzed, old value = 0.245775
	FUZZ s.separator.capHeightRatio2 = 1.990900; // fuzzed, old value = 1.924607
	FUZZ s.separator.getRatio1 = 1.027050; // fuzzed, old value = 1.072529
	FUZZ s.separator.getRatio2 = 1.178795; // fuzzed, old value = 1.147445
	FUZZ s.separator.testSlashLine1 = 2.800747; // fuzzed, old value = 2.803566
	FUZZ s.separator.testSlashLine2 = 2.825599; // fuzzed, old value = 2.836189
	FUZZ s.separator.minDensity = 0.188964; // fuzzed, old value = 0.198270
	FUZZ s.separator.maxDensity = 0.897243; // fuzzed, old value = 0.870830
	FUZZ s.separator.extCapHeightMin = 0.306803; // fuzzed, old value = 0.299308
	FUZZ s.separator.extCapHeightMax = 2.133889; // fuzzed, old value = 2.127594
	FUZZ s.separator.extRatioMin = 0.306250; // fuzzed, old value = 0.303703
	FUZZ s.separator.extRatioMax = 1.643632; // fuzzed, old value = 1.567555
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.411425; // fuzzed, old value = 0.422000
	FUZZ s.labels.weightUnderline = 0.314497; // fuzzed, old value = 0.320912
	FUZZ s.labels.ratioBase = 0.823183; // fuzzed, old value = 0.814145
	FUZZ s.labels.ratioWeight = 0.289456; // fuzzed, old value = 0.276604
	FUZZ s.labels.adjustDec = 1.219722; // fuzzed, old value = 1.217424
	FUZZ s.labels.adjustInc = 0.782908; // fuzzed, old value = 0.816502
	FUZZ s.labels.sameLineEps = 0.122176; // fuzzed, old value = 0.116926
	FUZZ s.labels.heightRatio = 0.830282; // fuzzed, old value = 0.842262
	FUZZ s.labels.medHeightFactor = 0.498141; // fuzzed, old value = 0.494916
	FUZZ s.labels.capHeightError = 0.540784; // fuzzed, old value = 0.518471

	FUZZ s.lcomb.MaximalSymbolDistance = 2.602331; // fuzzed, old value = 2.600518
	FUZZ s.lcomb.TestSlashLineEps = 3.020770; // fuzzed, old value = 3.064326
	FUZZ s.lcomb.TestMinHeightFactor = 0.513139; // fuzzed, old value = 0.499583
	FUZZ s.lcomb.TestMaxHeightFactor = 1.075404; // fuzzed, old value = 1.131179
	FUZZ s.lcomb.RectHeightRatio = 0.487107; // fuzzed, old value = 0.499670
	FUZZ s.lcomb.H1SuperscriptSpace = 1.155086; // fuzzed, old value = 1.209639
	FUZZ s.lcomb.H2LowercaseSpace = 0.516421; // fuzzed, old value = 0.518512
	FUZZ s.lcomb.H3LowercaseSpace = 0.443479; // fuzzed, old value = 0.460645
	FUZZ s.lcomb.H4SubscriptSpace = 0.545276; // fuzzed, old value = 0.523341
	FUZZ s.lcomb.FillLabelFactor1 = 0.540356; // fuzzed, old value = 0.558316
	FUZZ s.lcomb.FillLabelFactor2 = 0.560563; // fuzzed, old value = 0.536930
}
