
void updateSettingsHandwritten(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.300291; // fuzzed, old value = 0.301284
	FUZZ s.molecule.LengthFactor_medium = 0.410554; // fuzzed, old value = 0.413086
	FUZZ s.molecule.LengthFactor_default = 0.459773; // fuzzed, old value = 0.462752
	FUZZ s.molecule.LengthValue_long = 105.890326; // fuzzed, old value = 105.214238
	FUZZ s.molecule.LengthValue_medium = 86.429321; // fuzzed, old value = 87.259669
	FUZZ s.molecule.SpaceMultiply = 1.539902; // fuzzed, old value = 1.555491
	FUZZ s.molecule.AngleTreshold = 0.259290; // fuzzed, old value = 0.258607
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 15.410388; // fuzzed, old value = 15.462677
	FUZZ s.estimation.LineThickness = 5.666331; // fuzzed, old value = 5.724547
	FUZZ s.estimation.AvgBondLength = 31.992206; // fuzzed, old value = 31.784183
	FUZZ s.estimation.AddVertexEps = 4.815249; // fuzzed, old value = 4.883766
	FUZZ s.estimation.MaxSymRatio = 1.068820; // fuzzed, old value = 1.060198
	FUZZ s.estimation.MinSymRatio = 0.314059; // fuzzed, old value = 0.317908
	FUZZ s.estimation.ParLinesEps = 0.482207; // fuzzed, old value = 0.486001
	FUZZ s.estimation.SymHeightErr = 28.995321; // fuzzed, old value = 28.804558
	FUZZ s.estimation.CapitalHeightError = 0.860348; // fuzzed, old value = 0.867180
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.517521; // fuzzed, old value = 0.510833
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 119; // fuzzed, old value = 117
	FUZZ s.mbond.LongErr = 0.350776; // fuzzed, old value = 0.351540
	FUZZ s.mbond.MediumBond = 91; // fuzzed, old value = 91
	FUZZ s.mbond.MediumErr = 0.396461; // fuzzed, old value = 0.399829
	FUZZ s.mbond.DefaultErr = 0.641293; // fuzzed, old value = 0.634570
	FUZZ s.mbond.ParBondsEps = 0.308974; // fuzzed, old value = 0.311104
	FUZZ s.mbond.DoubleRatioTresh = 7.317275; // fuzzed, old value = 7.339204
	FUZZ s.mbond.DoubleCoef = 0.081785; // fuzzed, old value = 0.082216
	FUZZ s.mbond.DoubleMagic1 = 0.927627; // fuzzed, old value = 0.921396
	FUZZ s.mbond.DoubleMagic2 = 0.977206; // fuzzed, old value = 0.986674
	FUZZ s.mbond.DoubleTreshMin = 0.102167; // fuzzed, old value = 0.101219
	FUZZ s.mbond.DoubleTreshMax = 0.896716; // fuzzed, old value = 0.895620
	FUZZ s.mbond.MaxLen1 = 161.125225; // fuzzed, old value = 162.869661
	FUZZ s.mbond.MaxLen2 = 128.525889; // fuzzed, old value = 128.577862
	FUZZ s.mbond.MaxLen3 = 112.197821; // fuzzed, old value = 110.670699
	FUZZ s.mbond.MaxLen4 = 115.936867; // fuzzed, old value = 115.370121
	FUZZ s.mbond.MaxLen5 = 90.064140; // fuzzed, old value = 89.336149
	FUZZ s.mbond.MinLen1 = 80.614145; // fuzzed, old value = 80.575157
	FUZZ s.mbond.MinLen2 = 78.356195; // fuzzed, old value = 78.591956
	FUZZ s.mbond.mbe1 = 0.083390; // fuzzed, old value = 0.082326
	FUZZ s.mbond.mbe2 = 0.145912; // fuzzed, old value = 0.145100
	FUZZ s.mbond.mbe3 = 0.202791; // fuzzed, old value = 0.204717
	FUZZ s.mbond.mbe4 = 0.183036; // fuzzed, old value = 0.183307
	FUZZ s.mbond.mbe5 = 0.157634; // fuzzed, old value = 0.156813
	FUZZ s.mbond.mbe6 = 0.221834; // fuzzed, old value = 0.221646
	FUZZ s.mbond.mbe7 = 0.362117; // fuzzed, old value = 0.365801
	FUZZ s.mbond.mbe_def = 0.525713; // fuzzed, old value = 0.520314
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.335614; // fuzzed, old value = 0.330767
	FUZZ s.mbond.DoubleRightLengthTresh = 0.306757; // fuzzed, old value = 0.305574
	FUZZ s.mbond.TripleLeftLengthTresh = 0.257104; // fuzzed, old value = 0.260135
	FUZZ s.mbond.TripleRightLengthTresh = 0.237417; // fuzzed, old value = 0.240125
	FUZZ s.mbond.Case1LengthTresh = 107.347987; // fuzzed, old value = 108.371592
	FUZZ s.mbond.Case1Factor = 0.478469; // fuzzed, old value = 0.474674
	FUZZ s.mbond.Case2LengthTresh = 77.943034; // fuzzed, old value = 79.011083
	FUZZ s.mbond.Case2Factor = 0.682229; // fuzzed, old value = 0.678957
	FUZZ s.mbond.Case3Factor = 0.915713; // fuzzed, old value = 0.920534
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.090440; // fuzzed, old value = 0.089899
	FUZZ s.skeleton.BaseSmallErr = 0.146370; // fuzzed, old value = 0.146932
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.330055; // fuzzed, old value = 0.329058
	FUZZ s.skeleton.MediumBondLen = 83; // fuzzed, old value = 84
	FUZZ s.skeleton.MediumMul = 0.183278; // fuzzed, old value = 0.183025
	FUZZ s.skeleton.MediumSmallErr = 0.140761; // fuzzed, old value = 0.140212
	FUZZ s.skeleton.LongBondLen = 99; // fuzzed, old value = 98
	FUZZ s.skeleton.LongMul = 0.141244; // fuzzed, old value = 0.141836
	FUZZ s.skeleton.LongSmallErr = 0.062828; // fuzzed, old value = 0.063755
	FUZZ s.skeleton.BrokenRepairFactor = 2.903938; // fuzzed, old value = 2.869102
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.962459; // fuzzed, old value = 0.977036
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.655046; // fuzzed, old value = 2.620605
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.195865; // fuzzed, old value = 0.196705
	FUZZ s.skeleton.DissolveMinErr = 0.163281; // fuzzed, old value = 0.164861
	FUZZ s.skeleton.ConnectBlockS = 10.657107; // fuzzed, old value = 10.597200
	FUZZ s.skeleton.ConnectFactor = 1.894034; // fuzzed, old value = 1.918836
	FUZZ s.skeleton.JoinVerticiesConst = 0.102674; // fuzzed, old value = 0.103564
	FUZZ s.skeleton.DissolveConst = 0.095441; // fuzzed, old value = 0.095666
	FUZZ s.skeleton.Dissolve2Const = 0.190253; // fuzzed, old value = 0.188169
	FUZZ s.skeleton.Join2Const = 0.341443; // fuzzed, old value = 0.338141
	FUZZ s.skeleton.Join3Const = 0.198263; // fuzzed, old value = 0.201158
	FUZZ s.skeleton.DistTreshLimFactor = 1.917850; // fuzzed, old value = 1.897177
	FUZZ s.skeleton.SlopeFact1 = 0.105007; // fuzzed, old value = 0.104391
	FUZZ s.skeleton.SlopeFact2 = 0.184048; // fuzzed, old value = 0.183071
	FUZZ s.skeleton.ShrinkEps = 0.114648; // fuzzed, old value = 0.116091
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.096353; // fuzzed, old value = 0.095234
	FUZZ s.routines.Circle_GapMax = 0.902363; // fuzzed, old value = 0.915234
	FUZZ s.routines.Circle_RMax = 1.969116; // fuzzed, old value = 1.941688
	FUZZ s.routines.Circle_AvgRadius = 0.000107; // fuzzed, old value = 0.000107
	FUZZ s.routines.Circle_MaxRatio = 0.347513; // fuzzed, old value = 0.342852
	FUZZ s.routines.Algebra_IntersectionEps = 0.010559; // fuzzed, old value = 0.010676
	FUZZ s.routines.Algebra_SameLineEps = 0.209463; // fuzzed, old value = 0.209587
	FUZZ s.routines.Approx_Eps1 = 1.140706; // fuzzed, old value = 1.136856
	FUZZ s.routines.Approx_Eps2 = 0.870213; // fuzzed, old value = 0.865361
	FUZZ s.routines.Approx_CalcLineTresh = 0.896660; // fuzzed, old value = 0.893882

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.915566; // fuzzed, old value = 2.940418
	FUZZ s.wbe.SingleDownAngleMax = 43.151820; // fuzzed, old value = 43.392633
	FUZZ s.wbe.SingleDownDistancesMax = 9.811254; // fuzzed, old value = 9.820762
	FUZZ s.wbe.SingleDownLengthMax = 39.772123; // fuzzed, old value = 39.544267
	FUZZ s.wbe.SingleUpRatioEps = 1.906442; // fuzzed, old value = 1.910000
	FUZZ s.wbe.SingleUpDefCoeff = 0.263626; // fuzzed, old value = 0.267276
	FUZZ s.wbe.SingleUpIncCoeff = 0.435523; // fuzzed, old value = 0.430513
	FUZZ s.wbe.SingleUpIncLengthTresh = 37.085282; // fuzzed, old value = 37.334897
	FUZZ s.wbe.SingleUpInterpolateEps = 0.058061; // fuzzed, old value = 0.058723
	FUZZ s.wbe.SingleUpMagicAddition = 0.217482; // fuzzed, old value = 0.216021
	FUZZ s.wbe.SingleUpS2Divisor = 1.813581; // fuzzed, old value = 1.817237
	FUZZ s.wbe.SingleUpMinATresh = 1.806719; // fuzzed, old value = 1.808883
	FUZZ s.wbe.SingleUpSquareRatio = 0.586198; // fuzzed, old value = 0.588303
	FUZZ s.wbe.SingleUpAngleTresh = 0.067992; // fuzzed, old value = 0.067465
	FUZZ s.wbe.SomeTresh = 0.095223; // fuzzed, old value = 0.095932
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = true
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.073186; // fuzzed, old value = 1.083744
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.171736; // fuzzed, old value = 1.185928
	FUZZ s.characters.WriteEasyFactor = 0.937333; // fuzzed, old value = 0.945353
	FUZZ s.characters.WriteVeryEasyFactor = 0.827071; // fuzzed, old value = 0.817677
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.047948; // fuzzed, old value = 3.069717
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.371444; // fuzzed, old value = 3.362290
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.093476; // fuzzed, old value = 0.092454
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.470925; // fuzzed, old value = 2.440465
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.797440; // fuzzed, old value = 3.779521
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.933239; // fuzzed, old value = 0.927754
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.308022; // fuzzed, old value = 0.307776
	FUZZ s.characters.HW_Line = 1.699422; // fuzzed, old value = 1.700824
	FUZZ s.characters.HW_F = 3.258666; // fuzzed, old value = 3.307657
	FUZZ s.characters.HW_Tricky = 2.631134; // fuzzed, old value = 2.610371
	FUZZ s.characters.HW_Hard = 4.298957; // fuzzed, old value = 4.300786
	FUZZ s.characters.HW_Other = 3.882564; // fuzzed, old value = 3.871023

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.491256; // fuzzed, old value = 0.496762
	FUZZ s.csr.DeleteBadTriangles = 2.085972; // fuzzed, old value = 2.096970
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.505556; // fuzzed, old value = 1.505216

	FUZZ s.graph.MinimalDistTresh = 1.877048; // fuzzed, old value = 1.849841
	FUZZ s.graph.RatioSub = 0.970492; // fuzzed, old value = 0.978650
	FUZZ s.graph.RatioTresh = 0.404600; // fuzzed, old value = 0.400267

	FUZZ s.utils.SlashLineDensity = 0.495016; // fuzzed, old value = 0.497735
	FUZZ s.utils.TestPlusDensity = 0.412321; // fuzzed, old value = 0.416094
	FUZZ s.utils.TestPlusSq = 0.423349; // fuzzed, old value = 0.427280
	FUZZ s.utils.TestMinusRatio = 0.364156; // fuzzed, old value = 0.362671
	FUZZ s.utils.TestMinusDensity = 0.617603; // fuzzed, old value = 0.617397
	FUZZ s.utils.TestMinusHeightFactor = 0.807737; // fuzzed, old value = 0.812755

	FUZZ s.separator.hu_1_1 = 0.190714; // fuzzed, old value = 0.192638
	FUZZ s.separator.hu_1_2 = 0.077971; // fuzzed, old value = 0.079029
	FUZZ s.separator.hu_0_1 = 0.251199; // fuzzed, old value = 0.248488
	FUZZ s.separator.hu_1_3 = 0.088410; // fuzzed, old value = 0.088236
	FUZZ s.separator.hu_0_2 = 0.254508; // fuzzed, old value = 0.251211
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.512340; // fuzzed, old value = 0.508121
	FUZZ s.separator.capHeightMax = 1.393920; // fuzzed, old value = 1.386347
	FUZZ s.separator.gdConst = 1.480990; // fuzzed, old value = 1.486596
	FUZZ s.separator.SurfCoef = 2.769373; // fuzzed, old value = 2.765933
	FUZZ s.separator.capHeightRatio = 0.247622; // fuzzed, old value = 0.248339
	FUZZ s.separator.capHeightRatio2 = 1.828220; // fuzzed, old value = 1.804413
	FUZZ s.separator.getRatio1 = 0.873364; // fuzzed, old value = 0.865066
	FUZZ s.separator.getRatio2 = 1.100404; // fuzzed, old value = 1.095616
	FUZZ s.separator.testSlashLine1 = 3.031481; // fuzzed, old value = 3.033029
	FUZZ s.separator.testSlashLine2 = 2.920080; // fuzzed, old value = 2.929910
	FUZZ s.separator.minDensity = 0.208950; // fuzzed, old value = 0.206885
	FUZZ s.separator.maxDensity = 0.865841; // fuzzed, old value = 0.871496
	FUZZ s.separator.extCapHeightMin = 0.301233; // fuzzed, old value = 0.303222
	FUZZ s.separator.extCapHeightMax = 2.063316; // fuzzed, old value = 2.055723
	FUZZ s.separator.extRatioMin = 0.279865; // fuzzed, old value = 0.276259
	FUZZ s.separator.extRatioMax = 1.450104; // fuzzed, old value = 1.451684
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.470466; // fuzzed, old value = 0.471671
	FUZZ s.labels.weightUnderline = 0.316860; // fuzzed, old value = 0.312722
	FUZZ s.labels.ratioBase = 0.864702; // fuzzed, old value = 0.858557
	FUZZ s.labels.ratioWeight = 0.300562; // fuzzed, old value = 0.300167
	FUZZ s.labels.adjustDec = 1.249451; // fuzzed, old value = 1.266265
	FUZZ s.labels.adjustInc = 0.845088; // fuzzed, old value = 0.841056
	FUZZ s.labels.sameLineEps = 0.118343; // fuzzed, old value = 0.119673
	FUZZ s.labels.heightRatio = 0.809215; // fuzzed, old value = 0.814846
	FUZZ s.labels.medHeightFactor = 0.474628; // fuzzed, old value = 0.473773
	FUZZ s.labels.capHeightError = 0.515577; // fuzzed, old value = 0.508258

	FUZZ s.lcomb.MaximalSymbolDistance = 2.603792; // fuzzed, old value = 2.637298
	FUZZ s.lcomb.TestSlashLineEps = 3.132723; // fuzzed, old value = 3.130045
	FUZZ s.lcomb.TestMinHeightFactor = 0.455726; // fuzzed, old value = 0.462420
	FUZZ s.lcomb.TestMaxHeightFactor = 1.141902; // fuzzed, old value = 1.148579
	FUZZ s.lcomb.RectHeightRatio = 0.525356; // fuzzed, old value = 0.520647
	FUZZ s.lcomb.H1SuperscriptSpace = 1.153104; // fuzzed, old value = 1.141253
	FUZZ s.lcomb.H2LowercaseSpace = 0.515209; // fuzzed, old value = 0.510965
	FUZZ s.lcomb.H3LowercaseSpace = 0.496692; // fuzzed, old value = 0.499333
	FUZZ s.lcomb.H4SubscriptSpace = 0.518478; // fuzzed, old value = 0.517426
	FUZZ s.lcomb.FillLabelFactor1 = 0.502890; // fuzzed, old value = 0.495811
	FUZZ s.lcomb.FillLabelFactor2 = 0.485085; // fuzzed, old value = 0.485855
}

