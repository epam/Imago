
void updateSettingsHandwritten(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.304494; // fuzzed, old value = 0.301284
	FUZZ s.molecule.LengthFactor_medium = 0.412981; // fuzzed, old value = 0.413086
	FUZZ s.molecule.LengthFactor_default = 0.469229; // fuzzed, old value = 0.462752
	FUZZ s.molecule.LengthValue_long = 105.979046; // fuzzed, old value = 105.214238
	FUZZ s.molecule.LengthValue_medium = 86.614269; // fuzzed, old value = 87.259669
	FUZZ s.molecule.SpaceMultiply = 1.549960; // fuzzed, old value = 1.555491
	FUZZ s.molecule.AngleTreshold = 0.262339; // fuzzed, old value = 0.258607
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 15.395892; // fuzzed, old value = 15.462677
	FUZZ s.estimation.LineThickness = 5.790242; // fuzzed, old value = 5.724547
	FUZZ s.estimation.AvgBondLength = 31.650628; // fuzzed, old value = 31.784183
	FUZZ s.estimation.AddVertexEps = 4.901309; // fuzzed, old value = 4.883766
	FUZZ s.estimation.MaxSymRatio = 1.065791; // fuzzed, old value = 1.060198
	FUZZ s.estimation.MinSymRatio = 0.320448; // fuzzed, old value = 0.317908
	FUZZ s.estimation.ParLinesEps = 0.492171; // fuzzed, old value = 0.486001
	FUZZ s.estimation.SymHeightErr = 28.419353; // fuzzed, old value = 28.804558
	FUZZ s.estimation.CapitalHeightError = 0.872305; // fuzzed, old value = 0.867180
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.506621; // fuzzed, old value = 0.510833
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 117; // fuzzed, old value = 117
	FUZZ s.mbond.LongErr = 0.350980; // fuzzed, old value = 0.351540
	FUZZ s.mbond.MediumBond = 92; // fuzzed, old value = 91
	FUZZ s.mbond.MediumErr = 0.397178; // fuzzed, old value = 0.399829
	FUZZ s.mbond.DefaultErr = 0.638981; // fuzzed, old value = 0.634570
	FUZZ s.mbond.ParBondsEps = 0.312887; // fuzzed, old value = 0.311104
	FUZZ s.mbond.DoubleRatioTresh = 7.293334; // fuzzed, old value = 7.339204
	FUZZ s.mbond.DoubleCoef = 0.081625; // fuzzed, old value = 0.082216
	FUZZ s.mbond.DoubleMagic1 = 0.933079; // fuzzed, old value = 0.921396
	FUZZ s.mbond.DoubleMagic2 = 0.974523; // fuzzed, old value = 0.986674
	FUZZ s.mbond.DoubleTreshMin = 0.099858; // fuzzed, old value = 0.101219
	FUZZ s.mbond.DoubleTreshMax = 0.895812; // fuzzed, old value = 0.895620
	FUZZ s.mbond.MaxLen1 = 162.501866; // fuzzed, old value = 162.869661
	FUZZ s.mbond.MaxLen2 = 128.151774; // fuzzed, old value = 128.577862
	FUZZ s.mbond.MaxLen3 = 109.452619; // fuzzed, old value = 110.670699
	FUZZ s.mbond.MaxLen4 = 114.043701; // fuzzed, old value = 115.370121
	FUZZ s.mbond.MaxLen5 = 89.703764; // fuzzed, old value = 89.336149
	FUZZ s.mbond.MinLen1 = 81.343445; // fuzzed, old value = 80.575157
	FUZZ s.mbond.MinLen2 = 77.609083; // fuzzed, old value = 78.591956
	FUZZ s.mbond.mbe1 = 0.081751; // fuzzed, old value = 0.082326
	FUZZ s.mbond.mbe2 = 0.143227; // fuzzed, old value = 0.145100
	FUZZ s.mbond.mbe3 = 0.202963; // fuzzed, old value = 0.204717
	FUZZ s.mbond.mbe4 = 0.184807; // fuzzed, old value = 0.183307
	FUZZ s.mbond.mbe5 = 0.157620; // fuzzed, old value = 0.156813
	FUZZ s.mbond.mbe6 = 0.219004; // fuzzed, old value = 0.221646
	FUZZ s.mbond.mbe7 = 0.364478; // fuzzed, old value = 0.365801
	FUZZ s.mbond.mbe_def = 0.520029; // fuzzed, old value = 0.520314
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.335235; // fuzzed, old value = 0.330767
	FUZZ s.mbond.DoubleRightLengthTresh = 0.310130; // fuzzed, old value = 0.305574
	FUZZ s.mbond.TripleLeftLengthTresh = 0.261415; // fuzzed, old value = 0.260135
	FUZZ s.mbond.TripleRightLengthTresh = 0.238330; // fuzzed, old value = 0.240125
	FUZZ s.mbond.Case1LengthTresh = 107.390751; // fuzzed, old value = 108.371592
	FUZZ s.mbond.Case1Factor = 0.472041; // fuzzed, old value = 0.474674
	FUZZ s.mbond.Case2LengthTresh = 78.624033; // fuzzed, old value = 79.011083
	FUZZ s.mbond.Case2Factor = 0.687259; // fuzzed, old value = 0.678957
	FUZZ s.mbond.Case3Factor = 0.921455; // fuzzed, old value = 0.920534
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.089641; // fuzzed, old value = 0.089899
	FUZZ s.skeleton.BaseSmallErr = 0.148063; // fuzzed, old value = 0.146932
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.333023; // fuzzed, old value = 0.329058
	FUZZ s.skeleton.MediumBondLen = 83; // fuzzed, old value = 84
	FUZZ s.skeleton.MediumMul = 0.185132; // fuzzed, old value = 0.183025
	FUZZ s.skeleton.MediumSmallErr = 0.141269; // fuzzed, old value = 0.140212
	FUZZ s.skeleton.LongBondLen = 99; // fuzzed, old value = 98
	FUZZ s.skeleton.LongMul = 0.141052; // fuzzed, old value = 0.141836
	FUZZ s.skeleton.LongSmallErr = 0.063104; // fuzzed, old value = 0.063755
	FUZZ s.skeleton.BrokenRepairFactor = 2.896664; // fuzzed, old value = 2.869102
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.964660; // fuzzed, old value = 0.977036
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.631679; // fuzzed, old value = 2.620605
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.195451; // fuzzed, old value = 0.196705
	FUZZ s.skeleton.DissolveMinErr = 0.166393; // fuzzed, old value = 0.164861
	FUZZ s.skeleton.ConnectBlockS = 10.738907; // fuzzed, old value = 10.597200
	FUZZ s.skeleton.ConnectFactor = 1.928169; // fuzzed, old value = 1.918836
	FUZZ s.skeleton.JoinVerticiesConst = 0.104943; // fuzzed, old value = 0.103564
	FUZZ s.skeleton.DissolveConst = 0.096794; // fuzzed, old value = 0.095666
	FUZZ s.skeleton.Dissolve2Const = 0.190423; // fuzzed, old value = 0.188169
	FUZZ s.skeleton.Join2Const = 0.334137; // fuzzed, old value = 0.338141
	FUZZ s.skeleton.Join3Const = 0.203898; // fuzzed, old value = 0.201158
	FUZZ s.skeleton.DistTreshLimFactor = 1.873685; // fuzzed, old value = 1.897177
	FUZZ s.skeleton.SlopeFact1 = 0.105677; // fuzzed, old value = 0.104391
	FUZZ s.skeleton.SlopeFact2 = 0.183009; // fuzzed, old value = 0.183071
	FUZZ s.skeleton.ShrinkEps = 0.117697; // fuzzed, old value = 0.116091
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.095043; // fuzzed, old value = 0.095234
	FUZZ s.routines.Circle_GapMax = 0.904809; // fuzzed, old value = 0.915234
	FUZZ s.routines.Circle_RMax = 1.954556; // fuzzed, old value = 1.941688
	FUZZ s.routines.Circle_AvgRadius = 0.000108; // fuzzed, old value = 0.000107
	FUZZ s.routines.Circle_MaxRatio = 0.340664; // fuzzed, old value = 0.342852
	FUZZ s.routines.Algebra_IntersectionEps = 0.010788; // fuzzed, old value = 0.010676
	FUZZ s.routines.Algebra_SameLineEps = 0.212704; // fuzzed, old value = 0.209587
	FUZZ s.routines.Approx_Eps1 = 1.141590; // fuzzed, old value = 1.136856
	FUZZ s.routines.Approx_Eps2 = 0.858140; // fuzzed, old value = 0.865361
	FUZZ s.routines.Approx_CalcLineTresh = 0.885036; // fuzzed, old value = 0.893882

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.936273; // fuzzed, old value = 2.940418
	FUZZ s.wbe.SingleDownAngleMax = 43.603889; // fuzzed, old value = 43.392633
	FUZZ s.wbe.SingleDownDistancesMax = 9.938159; // fuzzed, old value = 9.820762
	FUZZ s.wbe.SingleDownLengthMax = 39.071484; // fuzzed, old value = 39.544267
	FUZZ s.wbe.SingleUpRatioEps = 1.924171; // fuzzed, old value = 1.910000
	FUZZ s.wbe.SingleUpDefCoeff = 0.267885; // fuzzed, old value = 0.267276
	FUZZ s.wbe.SingleUpIncCoeff = 0.433088; // fuzzed, old value = 0.430513
	FUZZ s.wbe.SingleUpIncLengthTresh = 37.085863; // fuzzed, old value = 37.334897
	FUZZ s.wbe.SingleUpInterpolateEps = 0.059369; // fuzzed, old value = 0.058723
	FUZZ s.wbe.SingleUpMagicAddition = 0.213558; // fuzzed, old value = 0.216021
	FUZZ s.wbe.SingleUpS2Divisor = 1.834904; // fuzzed, old value = 1.817237
	FUZZ s.wbe.SingleUpMinATresh = 1.795022; // fuzzed, old value = 1.808883
	FUZZ s.wbe.SingleUpSquareRatio = 0.581403; // fuzzed, old value = 0.588303
	FUZZ s.wbe.SingleUpAngleTresh = 0.067395; // fuzzed, old value = 0.067465
	FUZZ s.wbe.SomeTresh = 0.094680; // fuzzed, old value = 0.095932
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = true
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.083790; // fuzzed, old value = 1.083744
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.177962; // fuzzed, old value = 1.185928
	FUZZ s.characters.WriteEasyFactor = 0.945338; // fuzzed, old value = 0.945353
	FUZZ s.characters.WriteVeryEasyFactor = 0.825320; // fuzzed, old value = 0.817677
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.106952; // fuzzed, old value = 3.069717
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.387974; // fuzzed, old value = 3.362290
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.091338; // fuzzed, old value = 0.092454
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.413388; // fuzzed, old value = 2.440465
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.736050; // fuzzed, old value = 3.779521
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.930491; // fuzzed, old value = 0.927754
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.305480; // fuzzed, old value = 0.307776
	FUZZ s.characters.HW_Line = 1.687232; // fuzzed, old value = 1.700824
	FUZZ s.characters.HW_F = 3.283401; // fuzzed, old value = 3.307657
	FUZZ s.characters.HW_Tricky = 2.603006; // fuzzed, old value = 2.610371
	FUZZ s.characters.HW_Hard = 4.292818; // fuzzed, old value = 4.300786
	FUZZ s.characters.HW_Other = 3.928408; // fuzzed, old value = 3.871023

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.497646; // fuzzed, old value = 0.496762
	FUZZ s.csr.DeleteBadTriangles = 2.071333; // fuzzed, old value = 2.096970
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.504132; // fuzzed, old value = 1.505216

	FUZZ s.graph.MinimalDistTresh = 1.841037; // fuzzed, old value = 1.849841
	FUZZ s.graph.RatioSub = 0.984469; // fuzzed, old value = 0.978650
	FUZZ s.graph.RatioTresh = 0.405648; // fuzzed, old value = 0.400267

	FUZZ s.utils.SlashLineDensity = 0.493247; // fuzzed, old value = 0.497735
	FUZZ s.utils.TestPlusDensity = 0.410542; // fuzzed, old value = 0.416094
	FUZZ s.utils.TestPlusSq = 0.424974; // fuzzed, old value = 0.427280
	FUZZ s.utils.TestMinusRatio = 0.363149; // fuzzed, old value = 0.362671
	FUZZ s.utils.TestMinusDensity = 0.622435; // fuzzed, old value = 0.617397
	FUZZ s.utils.TestMinusHeightFactor = 0.801175; // fuzzed, old value = 0.812755

	FUZZ s.separator.hu_1_1 = 0.190007; // fuzzed, old value = 0.192638
	FUZZ s.separator.hu_1_2 = 0.078733; // fuzzed, old value = 0.079029
	FUZZ s.separator.hu_0_1 = 0.248770; // fuzzed, old value = 0.248488
	FUZZ s.separator.hu_1_3 = 0.087239; // fuzzed, old value = 0.088236
	FUZZ s.separator.hu_0_2 = 0.247747; // fuzzed, old value = 0.251211
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.510414; // fuzzed, old value = 0.508121
	FUZZ s.separator.capHeightMax = 1.372942; // fuzzed, old value = 1.386347
	FUZZ s.separator.gdConst = 1.484899; // fuzzed, old value = 1.486596
	FUZZ s.separator.SurfCoef = 2.789485; // fuzzed, old value = 2.765933
	FUZZ s.separator.capHeightRatio = 0.248155; // fuzzed, old value = 0.248339
	FUZZ s.separator.capHeightRatio2 = 1.798248; // fuzzed, old value = 1.804413
	FUZZ s.separator.getRatio1 = 0.860610; // fuzzed, old value = 0.865066
	FUZZ s.separator.getRatio2 = 1.082034; // fuzzed, old value = 1.095616
	FUZZ s.separator.testSlashLine1 = 3.053940; // fuzzed, old value = 3.033029
	FUZZ s.separator.testSlashLine2 = 2.932124; // fuzzed, old value = 2.929910
	FUZZ s.separator.minDensity = 0.203940; // fuzzed, old value = 0.206885
	FUZZ s.separator.maxDensity = 0.863266; // fuzzed, old value = 0.871496
	FUZZ s.separator.extCapHeightMin = 0.301081; // fuzzed, old value = 0.303222
	FUZZ s.separator.extCapHeightMax = 2.038997; // fuzzed, old value = 2.055723
	FUZZ s.separator.extRatioMin = 0.277035; // fuzzed, old value = 0.276259
	FUZZ s.separator.extRatioMax = 1.457489; // fuzzed, old value = 1.451684
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.475771; // fuzzed, old value = 0.471671
	FUZZ s.labels.weightUnderline = 0.309763; // fuzzed, old value = 0.312722
	FUZZ s.labels.ratioBase = 0.847879; // fuzzed, old value = 0.858557
	FUZZ s.labels.ratioWeight = 0.302202; // fuzzed, old value = 0.300167
	FUZZ s.labels.adjustDec = 1.265408; // fuzzed, old value = 1.266265
	FUZZ s.labels.adjustInc = 0.843477; // fuzzed, old value = 0.841056
	FUZZ s.labels.sameLineEps = 0.119477; // fuzzed, old value = 0.119673
	FUZZ s.labels.heightRatio = 0.822444; // fuzzed, old value = 0.814846
	FUZZ s.labels.medHeightFactor = 0.479269; // fuzzed, old value = 0.473773
	FUZZ s.labels.capHeightError = 0.514391; // fuzzed, old value = 0.508258

	FUZZ s.lcomb.MaximalSymbolDistance = 2.625318; // fuzzed, old value = 2.637298
	FUZZ s.lcomb.TestSlashLineEps = 3.117265; // fuzzed, old value = 3.130045
	FUZZ s.lcomb.TestMinHeightFactor = 0.459007; // fuzzed, old value = 0.462420
	FUZZ s.lcomb.TestMaxHeightFactor = 1.140889; // fuzzed, old value = 1.148579
	FUZZ s.lcomb.RectHeightRatio = 0.514783; // fuzzed, old value = 0.520647
	FUZZ s.lcomb.H1SuperscriptSpace = 1.135982; // fuzzed, old value = 1.141253
	FUZZ s.lcomb.H2LowercaseSpace = 0.508634; // fuzzed, old value = 0.510965
	FUZZ s.lcomb.H3LowercaseSpace = 0.506255; // fuzzed, old value = 0.499333
	FUZZ s.lcomb.H4SubscriptSpace = 0.523707; // fuzzed, old value = 0.517426
	FUZZ s.lcomb.FillLabelFactor1 = 0.492685; // fuzzed, old value = 0.495811
	FUZZ s.lcomb.FillLabelFactor2 = 0.482821; // fuzzed, old value = 0.485855
}

