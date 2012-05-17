
void updateSettingsScanned(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.302587; // fuzzed, old value = 0.301128
	FUZZ s.molecule.LengthFactor_medium = 0.413869; // fuzzed, old value = 0.412195
	FUZZ s.molecule.LengthFactor_default = 0.482683; // fuzzed, old value = 0.478946
	FUZZ s.molecule.LengthValue_long = 106.597956; // fuzzed, old value = 104.576605
	FUZZ s.molecule.LengthValue_medium = 82.637482; // fuzzed, old value = 83.828508
	FUZZ s.molecule.SpaceMultiply = 1.469594; // fuzzed, old value = 1.433167
	FUZZ s.molecule.AngleTreshold = 0.262416; // fuzzed, old value = 0.259030
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.0;
	FUZZ s.estimation.LineThickness = 6.0;
	FUZZ s.estimation.AvgBondLength = 30.0;
	FUZZ s.estimation.AddVertexEps = 5.052747; // fuzzed, old value = 5.099192
	FUZZ s.estimation.MaxSymRatio = 1.123954; // fuzzed, old value = 1.122616
	FUZZ s.estimation.MinSymRatio = 0.338931; // fuzzed, old value = 0.341869
	FUZZ s.estimation.ParLinesEps = 0.523855; // fuzzed, old value = 0.513057
	FUZZ s.estimation.SymHeightErr = 26.909337; // fuzzed, old value = 27.170494
	FUZZ s.estimation.CapitalHeightError = 0.823201; // fuzzed, old value = 0.839837
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.378645; // fuzzed, old value = 0.391240
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 113; // fuzzed, old value = 118
	FUZZ s.mbond.LongErr = 0.346608; // fuzzed, old value = 0.360257
	FUZZ s.mbond.MediumBond = 89; // fuzzed, old value = 88
	FUZZ s.mbond.MediumErr = 0.391840; // fuzzed, old value = 0.388901
	FUZZ s.mbond.DefaultErr = 0.610753; // fuzzed, old value = 0.640971
	FUZZ s.mbond.ParBondsEps = 0.337947; // fuzzed, old value = 0.349066
	FUZZ s.mbond.DoubleRatioTresh = 7.348546; // fuzzed, old value = 7.457044
	FUZZ s.mbond.DoubleCoef = 0.083989; // fuzzed, old value = 0.080466
	FUZZ s.mbond.DoubleMagic1 = 0.937557; // fuzzed, old value = 0.948187
	FUZZ s.mbond.DoubleMagic2 = 0.975982; // fuzzed, old value = 0.984298
	FUZZ s.mbond.DoubleTreshMin = 0.103846; // fuzzed, old value = 0.101160
	FUZZ s.mbond.DoubleTreshMax = 0.844539; // fuzzed, old value = 0.868968
	FUZZ s.mbond.MaxLen1 = 163.885566; // fuzzed, old value = 164.846209
	FUZZ s.mbond.MaxLen2 = 119.655960; // fuzzed, old value = 122.787381
	FUZZ s.mbond.MaxLen3 = 112.447633; // fuzzed, old value = 115.223338
	FUZZ s.mbond.MaxLen4 = 114.351034; // fuzzed, old value = 109.669810
	FUZZ s.mbond.MaxLen5 = 84.175796; // fuzzed, old value = 85.478967
	FUZZ s.mbond.MinLen1 = 87.203894; // fuzzed, old value = 85.904719
	FUZZ s.mbond.MinLen2 = 73.050015; // fuzzed, old value = 76.648276
	FUZZ s.mbond.mbe1 = 0.082028; // fuzzed, old value = 0.081553
	FUZZ s.mbond.mbe2 = 0.155614; // fuzzed, old value = 0.150084
	FUZZ s.mbond.mbe3 = 0.198843; // fuzzed, old value = 0.207396
	FUZZ s.mbond.mbe4 = 0.195177; // fuzzed, old value = 0.186034
	FUZZ s.mbond.mbe5 = 0.149705; // fuzzed, old value = 0.156560
	FUZZ s.mbond.mbe6 = 0.209757; // fuzzed, old value = 0.207583
	FUZZ s.mbond.mbe7 = 0.420229; // fuzzed, old value = 0.403671
	FUZZ s.mbond.mbe_def = 0.496928; // fuzzed, old value = 0.517421
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.343085; // fuzzed, old value = 0.327897
	FUZZ s.mbond.DoubleRightLengthTresh = 0.291665; // fuzzed, old value = 0.299122
	FUZZ s.mbond.TripleLeftLengthTresh = 0.267913; // fuzzed, old value = 0.261856
	FUZZ s.mbond.TripleRightLengthTresh = 0.231103; // fuzzed, old value = 0.221299
	FUZZ s.mbond.Case1LengthTresh = 106.538922; // fuzzed, old value = 103.451970
	FUZZ s.mbond.Case1Factor = 0.464350; // fuzzed, old value = 0.446116
	FUZZ s.mbond.Case2LengthTresh = 83.874277; // fuzzed, old value = 83.007771
	FUZZ s.mbond.Case2Factor = 0.719857; // fuzzed, old value = 0.700996
	FUZZ s.mbond.Case3Factor = 0.899713; // fuzzed, old value = 0.944560
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.096645; // fuzzed, old value = 0.095763
	FUZZ s.skeleton.BaseSmallErr = 0.148300; // fuzzed, old value = 0.152079
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 21
	FUZZ s.skeleton.ShortMul = 0.301830; // fuzzed, old value = 0.305612
	FUZZ s.skeleton.MediumBondLen = 86; // fuzzed, old value = 89
	FUZZ s.skeleton.MediumMul = 0.166902; // fuzzed, old value = 0.175148
	FUZZ s.skeleton.MediumSmallErr = 0.134690; // fuzzed, old value = 0.130098
	FUZZ s.skeleton.LongBondLen = 101; // fuzzed, old value = 103
	FUZZ s.skeleton.LongMul = 0.156848; // fuzzed, old value = 0.153756
	FUZZ s.skeleton.LongSmallErr = 0.061348; // fuzzed, old value = 0.063796
	FUZZ s.skeleton.BrokenRepairFactor = 3.014032; // fuzzed, old value = 2.876024
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.017943; // fuzzed, old value = 0.977421
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.682044; // fuzzed, old value = 2.688826
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.186894; // fuzzed, old value = 0.189200
	FUZZ s.skeleton.DissolveMinErr = 0.173091; // fuzzed, old value = 0.175111
	FUZZ s.skeleton.ConnectBlockS = 9.975947; // fuzzed, old value = 10.168268
	FUZZ s.skeleton.ConnectFactor = 2.118554; // fuzzed, old value = 2.035299
	FUZZ s.skeleton.JoinVerticiesConst = 0.104625; // fuzzed, old value = 0.101178
	FUZZ s.skeleton.DissolveConst = 0.098007; // fuzzed, old value = 0.095184
	FUZZ s.skeleton.Dissolve2Const = 0.194736; // fuzzed, old value = 0.196931
	FUZZ s.skeleton.Join2Const = 0.327311; // fuzzed, old value = 0.324191
	FUZZ s.skeleton.Join3Const = 0.186985; // fuzzed, old value = 0.188224
	FUZZ s.skeleton.DistTreshLimFactor = 1.998246; // fuzzed, old value = 1.939525
	FUZZ s.skeleton.SlopeFact1 = 0.102186; // fuzzed, old value = 0.099649
	FUZZ s.skeleton.SlopeFact2 = 0.185034; // fuzzed, old value = 0.192488
	FUZZ s.skeleton.ShrinkEps = 0.128250; // fuzzed, old value = 0.125260
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.095870; // fuzzed, old value = 0.094918
	FUZZ s.routines.Circle_GapMax = 1.019180; // fuzzed, old value = 1.001200
	FUZZ s.routines.Circle_RMax = 2.091001; // fuzzed, old value = 2.126840
	FUZZ s.routines.Circle_AvgRadius = 0.000103; // fuzzed, old value = 0.000106
	FUZZ s.routines.Circle_MaxRatio = 0.325535; // fuzzed, old value = 0.320074
	FUZZ s.routines.Algebra_IntersectionEps = 0.010417; // fuzzed, old value = 0.010090
	FUZZ s.routines.Algebra_SameLineEps = 0.215583; // fuzzed, old value = 0.209556
	FUZZ s.routines.Approx_Eps1 = 1.183234; // fuzzed, old value = 1.200332
	FUZZ s.routines.Approx_Eps2 = 0.870484; // fuzzed, old value = 0.864488
	FUZZ s.routines.Approx_CalcLineTresh = 0.918594; // fuzzed, old value = 0.895633
	FUZZ s.routines.Contour_Eps1 = 1.107616; // fuzzed, old value = 1.111403
	FUZZ s.routines.Contour_Eps2 = 0.707938; // fuzzed, old value = 0.686504

	FUZZ s.weak_seg.SubpixelDraw = 0.5;
	FUZZ s.weak_seg.RectangularCropAreaTreshold = 0.292500; // fuzzed, old value = 0.297723
	FUZZ s.weak_seg.RectangularCropFitTreshold = 1.074478; // fuzzed, old value = 1.056949
	FUZZ s.weak_seg.RefineWidth = 0.845834; // fuzzed, old value = 0.860166
	FUZZ s.weak_seg.MinDistanceDraw = 1.308223; // fuzzed, old value = 1.320265

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 3.091668; // fuzzed, old value = 3.084293
	FUZZ s.wbe.SingleDownAngleMax = 46.643341; // fuzzed, old value = 46.495272
	FUZZ s.wbe.SingleDownDistancesMax = 9.623688; // fuzzed, old value = 9.807540
	FUZZ s.wbe.SingleDownLengthMax = 46.422038; // fuzzed, old value = 44.286637
	FUZZ s.wbe.SingleUpRatioEps = 1.700450; // fuzzed, old value = 1.759887
	FUZZ s.wbe.SingleUpDefCoeff = 0.293211; // fuzzed, old value = 0.282408
	FUZZ s.wbe.SingleUpIncCoeff = 0.447362; // fuzzed, old value = 0.427804
	FUZZ s.wbe.SingleUpIncLengthTresh = 36.696824; // fuzzed, old value = 36.785456
	FUZZ s.wbe.SingleUpInterpolateEps = 0.061877; // fuzzed, old value = 0.059811
	FUZZ s.wbe.SingleUpMagicAddition = 0.230087; // fuzzed, old value = 0.219160
	FUZZ s.wbe.SingleUpS2Divisor = 1.556280; // fuzzed, old value = 1.614635
	FUZZ s.wbe.SingleUpMinATresh = 1.592886; // fuzzed, old value = 1.630915
	FUZZ s.wbe.SingleUpSquareRatio = 0.669836; // fuzzed, old value = 0.656983
	FUZZ s.wbe.SingleUpAngleTresh = 0.067123; // fuzzed, old value = 0.069971
	FUZZ s.wbe.SomeTresh = 0.102396; // fuzzed, old value = 0.097744
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = false; // fuzzed, old value = false
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.038928; // fuzzed, old value = 1.040750
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.174147; // fuzzed, old value = 1.158643
	FUZZ s.characters.WriteEasyFactor = 0.986541; // fuzzed, old value = 0.951037
	FUZZ s.characters.WriteVeryEasyFactor = 0.848332; // fuzzed, old value = 0.865599
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.111806; // fuzzed, old value = 2.970385
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.301392; // fuzzed, old value = 3.471436
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.105829; // fuzzed, old value = 0.101144
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.563198; // fuzzed, old value = 2.562639
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.659045; // fuzzed, old value = 3.659341
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.956191; // fuzzed, old value = 0.933604
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.292912; // fuzzed, old value = 0.290431
	FUZZ s.characters.HW_Line = 1.596290; // fuzzed, old value = 1.676584
	FUZZ s.characters.HW_F = 3.187493; // fuzzed, old value = 3.261839
	FUZZ s.characters.HW_Tricky = 2.795053; // fuzzed, old value = 2.668167
	FUZZ s.characters.HW_Hard = 4.440481; // fuzzed, old value = 4.394394
	FUZZ s.characters.HW_Other = 3.836238; // fuzzed, old value = 3.771726

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.479227; // fuzzed, old value = 0.497649
	FUZZ s.csr.DeleteBadTriangles = 1.873039; // fuzzed, old value = 1.901966
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.637170; // fuzzed, old value = 1.630420

	FUZZ s.graph.MinimalDistTresh = 1.879082; // fuzzed, old value = 1.959499
	FUZZ s.graph.RatioSub = 1.006754; // fuzzed, old value = 0.990219
	FUZZ s.graph.RatioTresh = 0.428992; // fuzzed, old value = 0.409889

	FUZZ s.utils.SlashLineDensity = 0.458063; // fuzzed, old value = 0.465765
	FUZZ s.utils.TestPlusDensity = 0.410080; // fuzzed, old value = 0.418756
	FUZZ s.utils.TestPlusSq = 0.405108; // fuzzed, old value = 0.418458
	FUZZ s.utils.TestMinusRatio = 0.364457; // fuzzed, old value = 0.374581
	FUZZ s.utils.TestMinusDensity = 0.620533; // fuzzed, old value = 0.624305
	FUZZ s.utils.TestMinusHeightFactor = 0.874957; // fuzzed, old value = 0.853211

	FUZZ s.separator.hu_1_1 = 0.201784; // fuzzed, old value = 0.204871
	FUZZ s.separator.hu_1_2 = 0.080051; // fuzzed, old value = 0.080216
	FUZZ s.separator.hu_0_1 = 0.234678; // fuzzed, old value = 0.237463
	FUZZ s.separator.hu_1_3 = 0.082361; // fuzzed, old value = 0.082534
	FUZZ s.separator.hu_0_2 = 0.242490; // fuzzed, old value = 0.249719
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.534716; // fuzzed, old value = 0.512089
	FUZZ s.separator.capHeightMax = 1.469799; // fuzzed, old value = 1.481603
	FUZZ s.separator.gdConst = 1.526502; // fuzzed, old value = 1.472250
	FUZZ s.separator.SurfCoef = 2.982488; // fuzzed, old value = 2.922590
	FUZZ s.separator.capHeightRatio = 0.249107; // fuzzed, old value = 0.245229
	FUZZ s.separator.capHeightRatio2 = 1.962704; // fuzzed, old value = 1.888187
	FUZZ s.separator.getRatio1 = 0.993468; // fuzzed, old value = 0.951114
	FUZZ s.separator.getRatio2 = 1.097162; // fuzzed, old value = 1.058237
	FUZZ s.separator.testSlashLine1 = 3.000910; // fuzzed, old value = 3.058478
	FUZZ s.separator.testSlashLine2 = 2.842329; // fuzzed, old value = 2.830938
	FUZZ s.separator.minDensity = 0.192198; // fuzzed, old value = 0.200432
	FUZZ s.separator.maxDensity = 0.867133; // fuzzed, old value = 0.867762
	FUZZ s.separator.extCapHeightMin = 0.296736; // fuzzed, old value = 0.300636
	FUZZ s.separator.extCapHeightMax = 2.117304; // fuzzed, old value = 2.170688
	FUZZ s.separator.extRatioMin = 0.294004; // fuzzed, old value = 0.302743
	FUZZ s.separator.extRatioMax = 1.490723; // fuzzed, old value = 1.484740
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.443050; // fuzzed, old value = 0.454582
	FUZZ s.labels.weightUnderline = 0.314459; // fuzzed, old value = 0.313585
	FUZZ s.labels.ratioBase = 0.820347; // fuzzed, old value = 0.812721
	FUZZ s.labels.ratioWeight = 0.272321; // fuzzed, old value = 0.270907
	FUZZ s.labels.adjustDec = 1.155396; // fuzzed, old value = 1.210610
	FUZZ s.labels.adjustInc = 0.812229; // fuzzed, old value = 0.815348
	FUZZ s.labels.sameLineEps = 0.122416; // fuzzed, old value = 0.128206
	FUZZ s.labels.heightRatio = 0.819953; // fuzzed, old value = 0.802991
	FUZZ s.labels.medHeightFactor = 0.472250; // fuzzed, old value = 0.490607
	FUZZ s.labels.capHeightError = 0.554526; // fuzzed, old value = 0.574141

	FUZZ s.lcomb.MaximalSymbolDistance = 2.628279; // fuzzed, old value = 2.733513
	FUZZ s.lcomb.TestSlashLineEps = 3.092586; // fuzzed, old value = 3.098482
	FUZZ s.lcomb.TestMinHeightFactor = 0.489176; // fuzzed, old value = 0.503643
	FUZZ s.lcomb.TestMaxHeightFactor = 1.161609; // fuzzed, old value = 1.186065
	FUZZ s.lcomb.RectHeightRatio = 0.498516; // fuzzed, old value = 0.502231
	FUZZ s.lcomb.H1SuperscriptSpace = 1.166767; // fuzzed, old value = 1.133961
	FUZZ s.lcomb.H2LowercaseSpace = 0.504302; // fuzzed, old value = 0.516655
	FUZZ s.lcomb.H3LowercaseSpace = 0.476277; // fuzzed, old value = 0.494162
	FUZZ s.lcomb.H4SubscriptSpace = 0.511007; // fuzzed, old value = 0.526684
	FUZZ s.lcomb.FillLabelFactor1 = 0.526067; // fuzzed, old value = 0.515400
	FUZZ s.lcomb.FillLabelFactor2 = 0.511469; // fuzzed, old value = 0.524754
}
