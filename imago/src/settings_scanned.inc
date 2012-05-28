
void updateSettingsScanned(Settings &s)
{
	FUZZ s.general.UseProbablistics = false; // fuzzed, old value = true

	FUZZ s.molecule.LengthFactor_long = 0.321022; // fuzzed, old value = 0.316012
	FUZZ s.molecule.LengthFactor_medium = 0.420107; // fuzzed, old value = 0.422606
	FUZZ s.molecule.LengthFactor_default = 0.460187; // fuzzed, old value = 0.464193
	FUZZ s.molecule.LengthValue_long = 104.091122; // fuzzed, old value = 106.513793
	FUZZ s.molecule.LengthValue_medium = 82.971224; // fuzzed, old value = 81.716338
	FUZZ s.molecule.SpaceMultiply = 1.465563; // fuzzed, old value = 1.500185
	FUZZ s.molecule.AngleTreshold = 0.254622; // fuzzed, old value = 0.253302
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.528950; // fuzzed, old value = 17.501566
	FUZZ s.estimation.LineThickness = 5.893582; // fuzzed, old value = 5.753109
	FUZZ s.estimation.AvgBondLength = 31.301433; // fuzzed, old value = 31.134817
	FUZZ s.estimation.AddVertexEps = 5.301112; // fuzzed, old value = 5.363650
	FUZZ s.estimation.MaxSymRatio = 1.126165; // fuzzed, old value = 1.115908
	FUZZ s.estimation.MinSymRatio = 0.350735; // fuzzed, old value = 0.355861
	FUZZ s.estimation.ParLinesEps = 0.540122; // fuzzed, old value = 0.537820
	FUZZ s.estimation.SymHeightErr = 26.390444; // fuzzed, old value = 26.385009
	FUZZ s.estimation.CapitalHeightError = 0.826375; // fuzzed, old value = 0.810590
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.386344; // fuzzed, old value = 0.375461
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 118; // fuzzed, old value = 120
	FUZZ s.mbond.LongErr = 0.345250; // fuzzed, old value = 0.352936
	FUZZ s.mbond.MediumBond = 95; // fuzzed, old value = 94
	FUZZ s.mbond.MediumErr = 0.420392; // fuzzed, old value = 0.422021
	FUZZ s.mbond.DefaultErr = 0.640290; // fuzzed, old value = 0.627944
	FUZZ s.mbond.ParBondsEps = 0.349891; // fuzzed, old value = 0.344995
	FUZZ s.mbond.DoubleRatioTresh = 6.890152; // fuzzed, old value = 7.076452
	FUZZ s.mbond.DoubleCoef = 0.083351; // fuzzed, old value = 0.083277
	FUZZ s.mbond.DoubleMagic1 = 0.903704; // fuzzed, old value = 0.896917
	FUZZ s.mbond.DoubleMagic2 = 0.929231; // fuzzed, old value = 0.951504
	FUZZ s.mbond.DoubleTreshMin = 0.096268; // fuzzed, old value = 0.099218
	FUZZ s.mbond.DoubleTreshMax = 0.789718; // fuzzed, old value = 0.795053
	FUZZ s.mbond.MaxLen1 = 150.301458; // fuzzed, old value = 152.872157
	FUZZ s.mbond.MaxLen2 = 117.303518; // fuzzed, old value = 115.763409
	FUZZ s.mbond.MaxLen3 = 110.137487; // fuzzed, old value = 107.611425
	FUZZ s.mbond.MaxLen4 = 124.935078; // fuzzed, old value = 122.295208
	FUZZ s.mbond.MaxLen5 = 80.545022; // fuzzed, old value = 80.483493
	FUZZ s.mbond.MinLen1 = 82.954275; // fuzzed, old value = 83.411028
	FUZZ s.mbond.MinLen2 = 71.976402; // fuzzed, old value = 73.911842
	FUZZ s.mbond.mbe1 = 0.077402; // fuzzed, old value = 0.075822
	FUZZ s.mbond.mbe2 = 0.155140; // fuzzed, old value = 0.155884
	FUZZ s.mbond.mbe3 = 0.203549; // fuzzed, old value = 0.198548
	FUZZ s.mbond.mbe4 = 0.180815; // fuzzed, old value = 0.183109
	FUZZ s.mbond.mbe5 = 0.152986; // fuzzed, old value = 0.153044
	FUZZ s.mbond.mbe6 = 0.217324; // fuzzed, old value = 0.215261
	FUZZ s.mbond.mbe7 = 0.413760; // fuzzed, old value = 0.422149
	FUZZ s.mbond.mbe_def = 0.497985; // fuzzed, old value = 0.509065
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.353233; // fuzzed, old value = 0.349171
	FUZZ s.mbond.DoubleRightLengthTresh = 0.309044; // fuzzed, old value = 0.312950
	FUZZ s.mbond.TripleLeftLengthTresh = 0.258566; // fuzzed, old value = 0.262788
	FUZZ s.mbond.TripleRightLengthTresh = 0.232501; // fuzzed, old value = 0.238341
	FUZZ s.mbond.Case1LengthTresh = 101.450031; // fuzzed, old value = 102.557357
	FUZZ s.mbond.Case1Factor = 0.436382; // fuzzed, old value = 0.445100
	FUZZ s.mbond.Case2LengthTresh = 80.704752; // fuzzed, old value = 80.120482
	FUZZ s.mbond.Case2Factor = 0.689868; // fuzzed, old value = 0.674543
	FUZZ s.mbond.Case3Factor = 0.884472; // fuzzed, old value = 0.862480
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.101611; // fuzzed, old value = 0.098817
	FUZZ s.skeleton.BaseSmallErr = 0.148515; // fuzzed, old value = 0.145356
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.307587; // fuzzed, old value = 0.313137
	FUZZ s.skeleton.MediumBondLen = 87; // fuzzed, old value = 85
	FUZZ s.skeleton.MediumMul = 0.174425; // fuzzed, old value = 0.170226
	FUZZ s.skeleton.MediumSmallErr = 0.136617; // fuzzed, old value = 0.133982
	FUZZ s.skeleton.LongBondLen = 101; // fuzzed, old value = 104
	FUZZ s.skeleton.LongMul = 0.146406; // fuzzed, old value = 0.143594
	FUZZ s.skeleton.LongSmallErr = 0.059625; // fuzzed, old value = 0.059830
	FUZZ s.skeleton.BrokenRepairFactor = 3.136218; // fuzzed, old value = 3.148906
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.964520; // fuzzed, old value = 0.986058
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.605072; // fuzzed, old value = 2.538955
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.187225; // fuzzed, old value = 0.186823
	FUZZ s.skeleton.DissolveMinErr = 0.174400; // fuzzed, old value = 0.178827
	FUZZ s.skeleton.ConnectBlockS = 10.054614; // fuzzed, old value = 9.861923
	FUZZ s.skeleton.ConnectFactor = 2.115938; // fuzzed, old value = 2.110934
	FUZZ s.skeleton.JoinVerticiesConst = 0.106920; // fuzzed, old value = 0.105082
	FUZZ s.skeleton.DissolveConst = 0.096648; // fuzzed, old value = 0.094846
	FUZZ s.skeleton.Dissolve2Const = 0.199371; // fuzzed, old value = 0.205404
	FUZZ s.skeleton.Join2Const = 0.302455; // fuzzed, old value = 0.306431
	FUZZ s.skeleton.Join3Const = 0.197244; // fuzzed, old value = 0.198258
	FUZZ s.skeleton.DistTreshLimFactor = 1.930570; // fuzzed, old value = 1.975177
	FUZZ s.skeleton.SlopeFact1 = 0.101889; // fuzzed, old value = 0.102952
	FUZZ s.skeleton.SlopeFact2 = 0.177069; // fuzzed, old value = 0.179077
	FUZZ s.skeleton.ShrinkEps = 0.134801; // fuzzed, old value = 0.136528
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.096824; // fuzzed, old value = 0.096128
	FUZZ s.routines.Circle_GapMax = 1.037537; // fuzzed, old value = 1.032678
	FUZZ s.routines.Circle_RMax = 2.194858; // fuzzed, old value = 2.169911
	FUZZ s.routines.Circle_AvgRadius = 0.000105; // fuzzed, old value = 0.000104
	FUZZ s.routines.Circle_MaxRatio = 0.322105; // fuzzed, old value = 0.327961
	FUZZ s.routines.Algebra_IntersectionEps = 0.011352; // fuzzed, old value = 0.011097
	FUZZ s.routines.Algebra_SameLineEps = 0.228230; // fuzzed, old value = 0.228698
	FUZZ s.routines.Approx_Eps1 = 1.169994; // fuzzed, old value = 1.149349
	FUZZ s.routines.Approx_Eps2 = 0.797894; // fuzzed, old value = 0.813337
	FUZZ s.routines.Approx_CalcLineTresh = 0.912416; // fuzzed, old value = 0.913179
	FUZZ s.routines.Contour_Eps1 = 1.039739; // fuzzed, old value = 1.016163
	FUZZ s.routines.Contour_Eps2 = 0.685176; // fuzzed, old value = 0.696015

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.981664; // fuzzed, old value = 2.999070
	FUZZ s.wbe.SingleDownAngleMax = 46.740957; // fuzzed, old value = 45.746928
	FUZZ s.wbe.SingleDownDistancesMax = 10.733935; // fuzzed, old value = 10.546371
	FUZZ s.wbe.SingleDownLengthMax = 47.645301; // fuzzed, old value = 46.347715
	FUZZ s.wbe.SingleUpRatioEps = 1.646250; // fuzzed, old value = 1.664250
	FUZZ s.wbe.SingleUpDefCoeff = 0.292954; // fuzzed, old value = 0.287418
	FUZZ s.wbe.SingleUpIncCoeff = 0.458588; // fuzzed, old value = 0.453702
	FUZZ s.wbe.SingleUpIncLengthTresh = 35.050723; // fuzzed, old value = 35.296420
	FUZZ s.wbe.SingleUpInterpolateEps = 0.064031; // fuzzed, old value = 0.062785
	FUZZ s.wbe.SingleUpMagicAddition = 0.228246; // fuzzed, old value = 0.233715
	FUZZ s.wbe.SingleUpS2Divisor = 1.363695; // fuzzed, old value = 1.404760
	FUZZ s.wbe.SingleUpMinATresh = 1.671470; // fuzzed, old value = 1.643360
	FUZZ s.wbe.SingleUpSquareRatio = 0.655185; // fuzzed, old value = 0.658409
	FUZZ s.wbe.SingleUpAngleTresh = 0.067840; // fuzzed, old value = 0.065895
	FUZZ s.wbe.SomeTresh = 0.103064; // fuzzed, old value = 0.103816
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = false; // fuzzed, old value = false
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.056262; // fuzzed, old value = 1.063570
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.185488; // fuzzed, old value = 1.162193
	FUZZ s.characters.WriteEasyFactor = 0.999335; // fuzzed, old value = 0.978644
	FUZZ s.characters.WriteVeryEasyFactor = 0.952182; // fuzzed, old value = 0.940838
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.339501; // fuzzed, old value = 3.292300
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.184300; // fuzzed, old value = 3.211554
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.102537; // fuzzed, old value = 0.104058
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.714880; // fuzzed, old value = 2.657348
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.631109; // fuzzed, old value = 3.535607
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.889722; // fuzzed, old value = 0.912464
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.285258; // fuzzed, old value = 0.282862
	FUZZ s.characters.HW_Line = 1.596829; // fuzzed, old value = 1.637154
	FUZZ s.characters.HW_F = 3.403389; // fuzzed, old value = 3.324046
	FUZZ s.characters.HW_Tricky = 2.860566; // fuzzed, old value = 2.778671
	FUZZ s.characters.HW_Hard = 4.218750; // fuzzed, old value = 4.163263
	FUZZ s.characters.HW_Other = 3.559219; // fuzzed, old value = 3.602790

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.466614; // fuzzed, old value = 0.470698
	FUZZ s.csr.DeleteBadTriangles = 1.855713; // fuzzed, old value = 1.907571
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.678800; // fuzzed, old value = 1.637752

	FUZZ s.graph.MinimalDistTresh = 1.937290; // fuzzed, old value = 1.912639
	FUZZ s.graph.RatioSub = 0.988634; // fuzzed, old value = 0.986857
	FUZZ s.graph.RatioTresh = 0.445083; // fuzzed, old value = 0.446347

	FUZZ s.utils.SlashLineDensity = 0.437990; // fuzzed, old value = 0.448328
	FUZZ s.utils.TestPlusDensity = 0.408481; // fuzzed, old value = 0.403077
	FUZZ s.utils.TestPlusSq = 0.410596; // fuzzed, old value = 0.400018
	FUZZ s.utils.TestMinusRatio = 0.359789; // fuzzed, old value = 0.366870
	FUZZ s.utils.TestMinusDensity = 0.640361; // fuzzed, old value = 0.649586
	FUZZ s.utils.TestMinusHeightFactor = 0.864582; // fuzzed, old value = 0.853522

	FUZZ s.separator.hu_1_1 = 0.209062; // fuzzed, old value = 0.209920
	FUZZ s.separator.hu_1_2 = 0.076775; // fuzzed, old value = 0.074659
	FUZZ s.separator.hu_0_1 = 0.222737; // fuzzed, old value = 0.228817
	FUZZ s.separator.hu_1_3 = 0.079899; // fuzzed, old value = 0.078158
	FUZZ s.separator.hu_0_2 = 0.231772; // fuzzed, old value = 0.236557
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.577429; // fuzzed, old value = 0.562051
	FUZZ s.separator.capHeightMax = 1.403834; // fuzzed, old value = 1.401674
	FUZZ s.separator.gdConst = 1.570905; // fuzzed, old value = 1.572424
	FUZZ s.separator.SurfCoef = 2.938822; // fuzzed, old value = 2.863376
	FUZZ s.separator.capHeightRatio = 0.245775; // fuzzed, old value = 0.251985
	FUZZ s.separator.capHeightRatio2 = 1.924607; // fuzzed, old value = 1.974941
	FUZZ s.separator.getRatio1 = 1.072529; // fuzzed, old value = 1.081847
	FUZZ s.separator.getRatio2 = 1.147445; // fuzzed, old value = 1.137191
	FUZZ s.separator.testSlashLine1 = 2.803566; // fuzzed, old value = 2.839112
	FUZZ s.separator.testSlashLine2 = 2.836189; // fuzzed, old value = 2.836950
	FUZZ s.separator.minDensity = 0.198270; // fuzzed, old value = 0.193435
	FUZZ s.separator.maxDensity = 0.870830; // fuzzed, old value = 0.855132
	FUZZ s.separator.extCapHeightMin = 0.299308; // fuzzed, old value = 0.300755
	FUZZ s.separator.extCapHeightMax = 2.127594; // fuzzed, old value = 2.191625
	FUZZ s.separator.extRatioMin = 0.303703; // fuzzed, old value = 0.302133
	FUZZ s.separator.extRatioMax = 1.567555; // fuzzed, old value = 1.583431
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.422000; // fuzzed, old value = 0.432232
	FUZZ s.labels.weightUnderline = 0.320912; // fuzzed, old value = 0.318194
	FUZZ s.labels.ratioBase = 0.814145; // fuzzed, old value = 0.822552
	FUZZ s.labels.ratioWeight = 0.276604; // fuzzed, old value = 0.274282
	FUZZ s.labels.adjustDec = 1.217424; // fuzzed, old value = 1.233285
	FUZZ s.labels.adjustInc = 0.816502; // fuzzed, old value = 0.840761
	FUZZ s.labels.sameLineEps = 0.116926; // fuzzed, old value = 0.119758
	FUZZ s.labels.heightRatio = 0.842262; // fuzzed, old value = 0.836327
	FUZZ s.labels.medHeightFactor = 0.494916; // fuzzed, old value = 0.499104
	FUZZ s.labels.capHeightError = 0.518471; // fuzzed, old value = 0.534310

	FUZZ s.lcomb.MaximalSymbolDistance = 2.600518; // fuzzed, old value = 2.550223
	FUZZ s.lcomb.TestSlashLineEps = 3.064326; // fuzzed, old value = 3.072363
	FUZZ s.lcomb.TestMinHeightFactor = 0.499583; // fuzzed, old value = 0.494941
	FUZZ s.lcomb.TestMaxHeightFactor = 1.131179; // fuzzed, old value = 1.152213
	FUZZ s.lcomb.RectHeightRatio = 0.499670; // fuzzed, old value = 0.499803
	FUZZ s.lcomb.H1SuperscriptSpace = 1.209639; // fuzzed, old value = 1.221709
	FUZZ s.lcomb.H2LowercaseSpace = 0.518512; // fuzzed, old value = 0.514884
	FUZZ s.lcomb.H3LowercaseSpace = 0.460645; // fuzzed, old value = 0.452245
	FUZZ s.lcomb.H4SubscriptSpace = 0.523341; // fuzzed, old value = 0.530046
	FUZZ s.lcomb.FillLabelFactor1 = 0.558316; // fuzzed, old value = 0.552735
	FUZZ s.lcomb.FillLabelFactor2 = 0.536930; // fuzzed, old value = 0.533105
}
