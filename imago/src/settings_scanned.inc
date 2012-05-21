
void updateSettingsScanned(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.314012; // fuzzed, old value = 0.302587
	FUZZ s.molecule.LengthFactor_medium = 0.425254; // fuzzed, old value = 0.413869
	FUZZ s.molecule.LengthFactor_default = 0.473692; // fuzzed, old value = 0.482683
	FUZZ s.molecule.LengthValue_long = 110.385832; // fuzzed, old value = 106.597956
	FUZZ s.molecule.LengthValue_medium = 84.327330; // fuzzed, old value = 82.637482
	FUZZ s.molecule.SpaceMultiply = 1.454141; // fuzzed, old value = 1.469594
	FUZZ s.molecule.AngleTreshold = 0.252741; // fuzzed, old value = 0.262416
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.752879; // fuzzed, old value = 16.0
	FUZZ s.estimation.LineThickness = 5.863939; // fuzzed, old value = 6.0
	FUZZ s.estimation.AvgBondLength = 30.373043; // fuzzed, old value = 30.0
	FUZZ s.estimation.AddVertexEps = 5.102932; // fuzzed, old value = 5.052747
	FUZZ s.estimation.MaxSymRatio = 1.143175; // fuzzed, old value = 1.123954
	FUZZ s.estimation.MinSymRatio = 0.346441; // fuzzed, old value = 0.338931
	FUZZ s.estimation.ParLinesEps = 0.524222; // fuzzed, old value = 0.523855
	FUZZ s.estimation.SymHeightErr = 27.279836; // fuzzed, old value = 26.909337
	FUZZ s.estimation.CapitalHeightError = 0.814128; // fuzzed, old value = 0.823201
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.363389; // fuzzed, old value = 0.378645
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 116; // fuzzed, old value = 113
	FUZZ s.mbond.LongErr = 0.337432; // fuzzed, old value = 0.346608
	FUZZ s.mbond.MediumBond = 89; // fuzzed, old value = 89
	FUZZ s.mbond.MediumErr = 0.407329; // fuzzed, old value = 0.391840
	FUZZ s.mbond.DefaultErr = 0.605962; // fuzzed, old value = 0.610753
	FUZZ s.mbond.ParBondsEps = 0.333394; // fuzzed, old value = 0.337947
	FUZZ s.mbond.DoubleRatioTresh = 7.317788; // fuzzed, old value = 7.348546
	FUZZ s.mbond.DoubleCoef = 0.083420; // fuzzed, old value = 0.083989
	FUZZ s.mbond.DoubleMagic1 = 0.907255; // fuzzed, old value = 0.937557
	FUZZ s.mbond.DoubleMagic2 = 0.943431; // fuzzed, old value = 0.975982
	FUZZ s.mbond.DoubleTreshMin = 0.102346; // fuzzed, old value = 0.103846
	FUZZ s.mbond.DoubleTreshMax = 0.830295; // fuzzed, old value = 0.844539
	FUZZ s.mbond.MaxLen1 = 159.358419; // fuzzed, old value = 163.885566
	FUZZ s.mbond.MaxLen2 = 116.553275; // fuzzed, old value = 119.655960
	FUZZ s.mbond.MaxLen3 = 108.464591; // fuzzed, old value = 112.447633
	FUZZ s.mbond.MaxLen4 = 119.464148; // fuzzed, old value = 114.351034
	FUZZ s.mbond.MaxLen5 = 82.832636; // fuzzed, old value = 84.175796
	FUZZ s.mbond.MinLen1 = 84.823731; // fuzzed, old value = 87.203894
	FUZZ s.mbond.MinLen2 = 72.992831; // fuzzed, old value = 73.050015
	FUZZ s.mbond.mbe1 = 0.078323; // fuzzed, old value = 0.082028
	FUZZ s.mbond.mbe2 = 0.154776; // fuzzed, old value = 0.155614
	FUZZ s.mbond.mbe3 = 0.192723; // fuzzed, old value = 0.198843
	FUZZ s.mbond.mbe4 = 0.189723; // fuzzed, old value = 0.195177
	FUZZ s.mbond.mbe5 = 0.150895; // fuzzed, old value = 0.149705
	FUZZ s.mbond.mbe6 = 0.218978; // fuzzed, old value = 0.209757
	FUZZ s.mbond.mbe7 = 0.430371; // fuzzed, old value = 0.420229
	FUZZ s.mbond.mbe_def = 0.502472; // fuzzed, old value = 0.496928
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.357166; // fuzzed, old value = 0.343085
	FUZZ s.mbond.DoubleRightLengthTresh = 0.293936; // fuzzed, old value = 0.291665
	FUZZ s.mbond.TripleLeftLengthTresh = 0.268076; // fuzzed, old value = 0.267913
	FUZZ s.mbond.TripleRightLengthTresh = 0.232532; // fuzzed, old value = 0.231103
	FUZZ s.mbond.Case1LengthTresh = 106.288726; // fuzzed, old value = 106.538922
	FUZZ s.mbond.Case1Factor = 0.449384; // fuzzed, old value = 0.464350
	FUZZ s.mbond.Case2LengthTresh = 81.069722; // fuzzed, old value = 83.874277
	FUZZ s.mbond.Case2Factor = 0.694346; // fuzzed, old value = 0.719857
	FUZZ s.mbond.Case3Factor = 0.874483; // fuzzed, old value = 0.899713
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.100707; // fuzzed, old value = 0.096645
	FUZZ s.skeleton.BaseSmallErr = 0.150632; // fuzzed, old value = 0.148300
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.308850; // fuzzed, old value = 0.301830
	FUZZ s.skeleton.MediumBondLen = 86; // fuzzed, old value = 86
	FUZZ s.skeleton.MediumMul = 0.170786; // fuzzed, old value = 0.166902
	FUZZ s.skeleton.MediumSmallErr = 0.132289; // fuzzed, old value = 0.134690
	FUZZ s.skeleton.LongBondLen = 101; // fuzzed, old value = 101
	FUZZ s.skeleton.LongMul = 0.151900; // fuzzed, old value = 0.156848
	FUZZ s.skeleton.LongSmallErr = 0.061448; // fuzzed, old value = 0.061348
	FUZZ s.skeleton.BrokenRepairFactor = 3.085241; // fuzzed, old value = 3.014032
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.992772; // fuzzed, old value = 1.017943
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.603863; // fuzzed, old value = 2.682044
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.181686; // fuzzed, old value = 0.186894
	FUZZ s.skeleton.DissolveMinErr = 0.179226; // fuzzed, old value = 0.173091
	FUZZ s.skeleton.ConnectBlockS = 9.980438; // fuzzed, old value = 9.975947
	FUZZ s.skeleton.ConnectFactor = 2.163926; // fuzzed, old value = 2.118554
	FUZZ s.skeleton.JoinVerticiesConst = 0.106521; // fuzzed, old value = 0.104625
	FUZZ s.skeleton.DissolveConst = 0.095701; // fuzzed, old value = 0.098007
	FUZZ s.skeleton.Dissolve2Const = 0.199432; // fuzzed, old value = 0.194736
	FUZZ s.skeleton.Join2Const = 0.313818; // fuzzed, old value = 0.327311
	FUZZ s.skeleton.Join3Const = 0.193546; // fuzzed, old value = 0.186985
	FUZZ s.skeleton.DistTreshLimFactor = 1.950554; // fuzzed, old value = 1.998246
	FUZZ s.skeleton.SlopeFact1 = 0.098141; // fuzzed, old value = 0.102186
	FUZZ s.skeleton.SlopeFact2 = 0.181941; // fuzzed, old value = 0.185034
	FUZZ s.skeleton.ShrinkEps = 0.133831; // fuzzed, old value = 0.128250
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.095625; // fuzzed, old value = 0.095870
	FUZZ s.routines.Circle_GapMax = 0.998874; // fuzzed, old value = 1.019180
	FUZZ s.routines.Circle_RMax = 2.154767; // fuzzed, old value = 2.091001
	FUZZ s.routines.Circle_AvgRadius = 0.000104; // fuzzed, old value = 0.000103
	FUZZ s.routines.Circle_MaxRatio = 0.335856; // fuzzed, old value = 0.325535
	FUZZ s.routines.Algebra_IntersectionEps = 0.010758; // fuzzed, old value = 0.010417
	FUZZ s.routines.Algebra_SameLineEps = 0.224346; // fuzzed, old value = 0.215583
	FUZZ s.routines.Approx_Eps1 = 1.152260; // fuzzed, old value = 1.183234
	FUZZ s.routines.Approx_Eps2 = 0.856339; // fuzzed, old value = 0.870484
	FUZZ s.routines.Approx_CalcLineTresh = 0.951213; // fuzzed, old value = 0.918594
	FUZZ s.routines.Contour_Eps1 = 1.058759; // fuzzed, old value = 1.107616
	FUZZ s.routines.Contour_Eps2 = 0.677484; // fuzzed, old value = 0.707938

	FUZZ s.weak_seg.SubpixelDraw = 0.524678; // fuzzed, old value = 0.5
	FUZZ s.weak_seg.RectangularCropAreaTreshold = 0.289043; // fuzzed, old value = 0.292500
	FUZZ s.weak_seg.RectangularCropFitTreshold = 1.037117; // fuzzed, old value = 1.074478
	FUZZ s.weak_seg.RefineWidth = 0.828440; // fuzzed, old value = 0.845834
	FUZZ s.weak_seg.MinDistanceDraw = 1.272875; // fuzzed, old value = 1.308223

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 3.109147; // fuzzed, old value = 3.091668
	FUZZ s.wbe.SingleDownAngleMax = 46.467612; // fuzzed, old value = 46.643341
	FUZZ s.wbe.SingleDownDistancesMax = 10.034737; // fuzzed, old value = 9.623688
	FUZZ s.wbe.SingleDownLengthMax = 46.174323; // fuzzed, old value = 46.422038
	FUZZ s.wbe.SingleUpRatioEps = 1.660498; // fuzzed, old value = 1.700450
	FUZZ s.wbe.SingleUpDefCoeff = 0.302677; // fuzzed, old value = 0.293211
	FUZZ s.wbe.SingleUpIncCoeff = 0.432971; // fuzzed, old value = 0.447362
	FUZZ s.wbe.SingleUpIncLengthTresh = 36.042727; // fuzzed, old value = 36.696824
	FUZZ s.wbe.SingleUpInterpolateEps = 0.064183; // fuzzed, old value = 0.061877
	FUZZ s.wbe.SingleUpMagicAddition = 0.240304; // fuzzed, old value = 0.230087
	FUZZ s.wbe.SingleUpS2Divisor = 1.487086; // fuzzed, old value = 1.556280
	FUZZ s.wbe.SingleUpMinATresh = 1.633013; // fuzzed, old value = 1.592886
	FUZZ s.wbe.SingleUpSquareRatio = 0.639582; // fuzzed, old value = 0.669836
	FUZZ s.wbe.SingleUpAngleTresh = 0.064217; // fuzzed, old value = 0.067123
	FUZZ s.wbe.SomeTresh = 0.103310; // fuzzed, old value = 0.102396
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = false; // fuzzed, old value = false
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.060072; // fuzzed, old value = 1.038928
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.129637; // fuzzed, old value = 1.174147
	FUZZ s.characters.WriteEasyFactor = 1.025604; // fuzzed, old value = 0.986541
	FUZZ s.characters.WriteVeryEasyFactor = 0.888791; // fuzzed, old value = 0.848332
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.192894; // fuzzed, old value = 3.111806
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.354776; // fuzzed, old value = 3.301392
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.109991; // fuzzed, old value = 0.105829
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.527344; // fuzzed, old value = 2.563198
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.503842; // fuzzed, old value = 3.659045
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.934808; // fuzzed, old value = 0.956191
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.279475; // fuzzed, old value = 0.292912
	FUZZ s.characters.HW_Line = 1.663039; // fuzzed, old value = 1.596290
	FUZZ s.characters.HW_F = 3.174725; // fuzzed, old value = 3.187493
	FUZZ s.characters.HW_Tricky = 2.866710; // fuzzed, old value = 2.795053
	FUZZ s.characters.HW_Hard = 4.344854; // fuzzed, old value = 4.440481
	FUZZ s.characters.HW_Other = 3.797047; // fuzzed, old value = 3.836238

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.484603; // fuzzed, old value = 0.479227
	FUZZ s.csr.DeleteBadTriangles = 1.941122; // fuzzed, old value = 1.873039
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.658967; // fuzzed, old value = 1.637170

	FUZZ s.graph.MinimalDistTresh = 1.844241; // fuzzed, old value = 1.879082
	FUZZ s.graph.RatioSub = 1.047079; // fuzzed, old value = 1.006754
	FUZZ s.graph.RatioTresh = 0.433579; // fuzzed, old value = 0.428992

	FUZZ s.utils.SlashLineDensity = 0.459448; // fuzzed, old value = 0.458063
	FUZZ s.utils.TestPlusDensity = 0.423511; // fuzzed, old value = 0.410080
	FUZZ s.utils.TestPlusSq = 0.411163; // fuzzed, old value = 0.405108
	FUZZ s.utils.TestMinusRatio = 0.375232; // fuzzed, old value = 0.364457
	FUZZ s.utils.TestMinusDensity = 0.636711; // fuzzed, old value = 0.620533
	FUZZ s.utils.TestMinusHeightFactor = 0.869324; // fuzzed, old value = 0.874957

	FUZZ s.separator.hu_1_1 = 0.209016; // fuzzed, old value = 0.201784
	FUZZ s.separator.hu_1_2 = 0.078244; // fuzzed, old value = 0.080051
	FUZZ s.separator.hu_0_1 = 0.232186; // fuzzed, old value = 0.234678
	FUZZ s.separator.hu_1_3 = 0.079689; // fuzzed, old value = 0.082361
	FUZZ s.separator.hu_0_2 = 0.234813; // fuzzed, old value = 0.242490
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.541393; // fuzzed, old value = 0.534716
	FUZZ s.separator.capHeightMax = 1.436958; // fuzzed, old value = 1.469799
	FUZZ s.separator.gdConst = 1.601625; // fuzzed, old value = 1.526502
	FUZZ s.separator.SurfCoef = 2.842994; // fuzzed, old value = 2.982488
	FUZZ s.separator.capHeightRatio = 0.243006; // fuzzed, old value = 0.249107
	FUZZ s.separator.capHeightRatio2 = 1.932290; // fuzzed, old value = 1.962704
	FUZZ s.separator.getRatio1 = 1.036623; // fuzzed, old value = 0.993468
	FUZZ s.separator.getRatio2 = 1.117585; // fuzzed, old value = 1.097162
	FUZZ s.separator.testSlashLine1 = 2.874914; // fuzzed, old value = 3.000910
	FUZZ s.separator.testSlashLine2 = 2.934646; // fuzzed, old value = 2.842329
	FUZZ s.separator.minDensity = 0.195797; // fuzzed, old value = 0.192198
	FUZZ s.separator.maxDensity = 0.882856; // fuzzed, old value = 0.867133
	FUZZ s.separator.extCapHeightMin = 0.306905; // fuzzed, old value = 0.296736
	FUZZ s.separator.extCapHeightMax = 2.173104; // fuzzed, old value = 2.117304
	FUZZ s.separator.extRatioMin = 0.302230; // fuzzed, old value = 0.294004
	FUZZ s.separator.extRatioMax = 1.552425; // fuzzed, old value = 1.490723
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.439654; // fuzzed, old value = 0.443050
	FUZZ s.labels.weightUnderline = 0.308302; // fuzzed, old value = 0.314459
	FUZZ s.labels.ratioBase = 0.838920; // fuzzed, old value = 0.820347
	FUZZ s.labels.ratioWeight = 0.275550; // fuzzed, old value = 0.272321
	FUZZ s.labels.adjustDec = 1.202376; // fuzzed, old value = 1.155396
	FUZZ s.labels.adjustInc = 0.798111; // fuzzed, old value = 0.812229
	FUZZ s.labels.sameLineEps = 0.118557; // fuzzed, old value = 0.122416
	FUZZ s.labels.heightRatio = 0.848822; // fuzzed, old value = 0.819953
	FUZZ s.labels.medHeightFactor = 0.488077; // fuzzed, old value = 0.472250
	FUZZ s.labels.capHeightError = 0.542789; // fuzzed, old value = 0.554526

	FUZZ s.lcomb.MaximalSymbolDistance = 2.536481; // fuzzed, old value = 2.628279
	FUZZ s.lcomb.TestSlashLineEps = 2.971877; // fuzzed, old value = 3.092586
	FUZZ s.lcomb.TestMinHeightFactor = 0.487079; // fuzzed, old value = 0.489176
	FUZZ s.lcomb.TestMaxHeightFactor = 1.179453; // fuzzed, old value = 1.161609
	FUZZ s.lcomb.RectHeightRatio = 0.479224; // fuzzed, old value = 0.498516
	FUZZ s.lcomb.H1SuperscriptSpace = 1.200931; // fuzzed, old value = 1.166767
	FUZZ s.lcomb.H2LowercaseSpace = 0.502570; // fuzzed, old value = 0.504302
	FUZZ s.lcomb.H3LowercaseSpace = 0.459702; // fuzzed, old value = 0.476277
	FUZZ s.lcomb.H4SubscriptSpace = 0.534221; // fuzzed, old value = 0.511007
	FUZZ s.lcomb.FillLabelFactor1 = 0.527919; // fuzzed, old value = 0.526067
	FUZZ s.lcomb.FillLabelFactor2 = 0.517290; // fuzzed, old value = 0.511469
}
