
void updateSettingsHandwritten(Settings &s)
{
	FUZZ s.general.UseProbablistics = false; // fuzzed, old value = true

	FUZZ s.separator.ext2charRatio = 1.2;

	FUZZ s.molecule.LengthFactor_long = 0.306684; // fuzzed, old value = 0.304494
	FUZZ s.molecule.LengthFactor_medium = 0.407360; // fuzzed, old value = 0.412981
	FUZZ s.molecule.LengthFactor_default = 0.482723; // fuzzed, old value = 0.469229
	FUZZ s.molecule.LengthValue_long = 105.177678; // fuzzed, old value = 105.979046
	FUZZ s.molecule.LengthValue_medium = 87.223215; // fuzzed, old value = 86.614269
	FUZZ s.molecule.SpaceMultiply = 1.522718; // fuzzed, old value = 1.549960
	FUZZ s.molecule.AngleTreshold = 0.257235; // fuzzed, old value = 0.262339
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 15.346966; // fuzzed, old value = 15.395892
	FUZZ s.estimation.LineThickness = 5.799111; // fuzzed, old value = 5.790242
	FUZZ s.estimation.AvgBondLength = 32.193297; // fuzzed, old value = 31.650628
	FUZZ s.estimation.AddVertexEps = 4.892114; // fuzzed, old value = 4.901309
	FUZZ s.estimation.MaxSymRatio = 1.077101; // fuzzed, old value = 1.065791
	FUZZ s.estimation.MinSymRatio = 0.326936; // fuzzed, old value = 0.320448
	FUZZ s.estimation.ParLinesEps = 0.501992; // fuzzed, old value = 0.492171
	FUZZ s.estimation.SymHeightErr = 28.286315; // fuzzed, old value = 28.419353
	FUZZ s.estimation.CapitalHeightError = 0.867746; // fuzzed, old value = 0.872305
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.498218; // fuzzed, old value = 0.506621
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 116; // fuzzed, old value = 117
	FUZZ s.mbond.LongErr = 0.360990; // fuzzed, old value = 0.350980
	FUZZ s.mbond.MediumBond = 93; // fuzzed, old value = 92
	FUZZ s.mbond.MediumErr = 0.396389; // fuzzed, old value = 0.397178
	FUZZ s.mbond.DefaultErr = 0.625824; // fuzzed, old value = 0.638981
	FUZZ s.mbond.ParBondsEps = 0.306788; // fuzzed, old value = 0.312887
	FUZZ s.mbond.DoubleRatioTresh = 7.460718; // fuzzed, old value = 7.293334
	FUZZ s.mbond.DoubleCoef = 0.083551; // fuzzed, old value = 0.081625
	FUZZ s.mbond.DoubleMagic1 = 0.944548; // fuzzed, old value = 0.933079
	FUZZ s.mbond.DoubleMagic2 = 0.975316; // fuzzed, old value = 0.974523
	FUZZ s.mbond.DoubleTreshMin = 0.100047; // fuzzed, old value = 0.099858
	FUZZ s.mbond.DoubleTreshMax = 0.875361; // fuzzed, old value = 0.895812
	FUZZ s.mbond.MaxLen1 = 157.699414; // fuzzed, old value = 162.501866
	FUZZ s.mbond.MaxLen2 = 125.498590; // fuzzed, old value = 128.151774
	FUZZ s.mbond.MaxLen3 = 109.304008; // fuzzed, old value = 109.452619
	FUZZ s.mbond.MaxLen4 = 111.437231; // fuzzed, old value = 114.043701
	FUZZ s.mbond.MaxLen5 = 87.849379; // fuzzed, old value = 89.703764
	FUZZ s.mbond.MinLen1 = 80.348392; // fuzzed, old value = 81.343445
	FUZZ s.mbond.MinLen2 = 76.314382; // fuzzed, old value = 77.609083
	FUZZ s.mbond.mbe1 = 0.082287; // fuzzed, old value = 0.081751
	FUZZ s.mbond.mbe2 = 0.146037; // fuzzed, old value = 0.143227
	FUZZ s.mbond.mbe3 = 0.207969; // fuzzed, old value = 0.202963
	FUZZ s.mbond.mbe4 = 0.182796; // fuzzed, old value = 0.184807
	FUZZ s.mbond.mbe5 = 0.152938; // fuzzed, old value = 0.157620
	FUZZ s.mbond.mbe6 = 0.213147; // fuzzed, old value = 0.219004
	FUZZ s.mbond.mbe7 = 0.366129; // fuzzed, old value = 0.364478
	FUZZ s.mbond.mbe_def = 0.520742; // fuzzed, old value = 0.520029
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.327004; // fuzzed, old value = 0.335235
	FUZZ s.mbond.DoubleRightLengthTresh = 0.316236; // fuzzed, old value = 0.310130
	FUZZ s.mbond.TripleLeftLengthTresh = 0.265782; // fuzzed, old value = 0.261415
	FUZZ s.mbond.TripleRightLengthTresh = 0.238093; // fuzzed, old value = 0.238330
	FUZZ s.mbond.Case1LengthTresh = 104.640582; // fuzzed, old value = 107.390751
	FUZZ s.mbond.Case1Factor = 0.474073; // fuzzed, old value = 0.472041
	FUZZ s.mbond.Case2LengthTresh = 79.216539; // fuzzed, old value = 78.624033
	FUZZ s.mbond.Case2Factor = 0.677224; // fuzzed, old value = 0.687259
	FUZZ s.mbond.Case3Factor = 0.902808; // fuzzed, old value = 0.921455
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.087032; // fuzzed, old value = 0.089641
	FUZZ s.skeleton.BaseSmallErr = 0.146661; // fuzzed, old value = 0.148063
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.329981; // fuzzed, old value = 0.333023
	FUZZ s.skeleton.MediumBondLen = 83; // fuzzed, old value = 83
	FUZZ s.skeleton.MediumMul = 0.184914; // fuzzed, old value = 0.185132
	FUZZ s.skeleton.MediumSmallErr = 0.137804; // fuzzed, old value = 0.141269
	FUZZ s.skeleton.LongBondLen = 99; // fuzzed, old value = 99
	FUZZ s.skeleton.LongMul = 0.138933; // fuzzed, old value = 0.141052
	FUZZ s.skeleton.LongSmallErr = 0.062113; // fuzzed, old value = 0.063104
	FUZZ s.skeleton.BrokenRepairFactor = 2.907540; // fuzzed, old value = 2.896664
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.968157; // fuzzed, old value = 0.964660
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.652422; // fuzzed, old value = 2.631679
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.198932; // fuzzed, old value = 0.195451
	FUZZ s.skeleton.DissolveMinErr = 0.170885; // fuzzed, old value = 0.166393
	FUZZ s.skeleton.ConnectBlockS = 10.860028; // fuzzed, old value = 10.738907
	FUZZ s.skeleton.ConnectFactor = 1.979539; // fuzzed, old value = 1.928169
	FUZZ s.skeleton.JoinVerticiesConst = 0.102296; // fuzzed, old value = 0.104943
	FUZZ s.skeleton.DissolveConst = 0.096910; // fuzzed, old value = 0.096794
	FUZZ s.skeleton.Dissolve2Const = 0.190231; // fuzzed, old value = 0.190423
	FUZZ s.skeleton.Join2Const = 0.339420; // fuzzed, old value = 0.334137
	FUZZ s.skeleton.Join3Const = 0.208102; // fuzzed, old value = 0.203898
	FUZZ s.skeleton.DistTreshLimFactor = 1.822734; // fuzzed, old value = 1.873685
	FUZZ s.skeleton.SlopeFact1 = 0.108766; // fuzzed, old value = 0.105677
	FUZZ s.skeleton.SlopeFact2 = 0.181641; // fuzzed, old value = 0.183009
	FUZZ s.skeleton.ShrinkEps = 0.117740; // fuzzed, old value = 0.117697
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10

	FUZZ s.routines.Circle_GapRadiusMax = 1.2;
	FUZZ s.routines.Circle_GapAngleMax = 0.5;
	FUZZ s.routines.Circle_MinRadius = 10.0;
	FUZZ s.routines.Circle_MaxDeviation = 0.2;

	FUZZ s.routines.Algebra_IntersectionEps = 0.010698; // fuzzed, old value = 0.010788
	FUZZ s.routines.Algebra_SameLineEps = 0.206971; // fuzzed, old value = 0.212704
	FUZZ s.routines.Approx_Eps1 = 1.149482; // fuzzed, old value = 1.141590
	FUZZ s.routines.Approx_Eps2 = 0.865320; // fuzzed, old value = 0.858140
	FUZZ s.routines.Approx_CalcLineTresh = 0.861870; // fuzzed, old value = 0.885036

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.876762; // fuzzed, old value = 2.936273
	FUZZ s.wbe.SingleDownAngleMax = 44.892284; // fuzzed, old value = 43.603889
	FUZZ s.wbe.SingleDownDistancesMax = 9.992270; // fuzzed, old value = 9.938159
	FUZZ s.wbe.SingleDownLengthMax = 38.620434; // fuzzed, old value = 39.071484
	FUZZ s.wbe.SingleUpRatioEps = 1.957127; // fuzzed, old value = 1.924171
	FUZZ s.wbe.SingleUpDefCoeff = 0.267500; // fuzzed, old value = 0.267885
	FUZZ s.wbe.SingleUpIncCoeff = 0.433192; // fuzzed, old value = 0.433088
	FUZZ s.wbe.SingleUpIncLengthTresh = 36.428205; // fuzzed, old value = 37.085863
	FUZZ s.wbe.SingleUpInterpolateEps = 0.061148; // fuzzed, old value = 0.059369
	FUZZ s.wbe.SingleUpMagicAddition = 0.215826; // fuzzed, old value = 0.213558
	FUZZ s.wbe.SingleUpS2Divisor = 1.857182; // fuzzed, old value = 1.834904
	FUZZ s.wbe.SingleUpMinATresh = 1.764370; // fuzzed, old value = 1.795022
	FUZZ s.wbe.SingleUpSquareRatio = 0.568118; // fuzzed, old value = 0.581403
	FUZZ s.wbe.SingleUpAngleTresh = 0.069205; // fuzzed, old value = 0.067395
	FUZZ s.wbe.SomeTresh = 0.096025; // fuzzed, old value = 0.094680
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = true
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.063898; // fuzzed, old value = 1.083790
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.189764; // fuzzed, old value = 1.177962
	FUZZ s.characters.WriteEasyFactor = 0.939331; // fuzzed, old value = 0.945338
	FUZZ s.characters.WriteVeryEasyFactor = 0.800745; // fuzzed, old value = 0.825320
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.106801; // fuzzed, old value = 3.106952
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.291968; // fuzzed, old value = 3.387974
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.090755; // fuzzed, old value = 0.091338
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.417801; // fuzzed, old value = 2.413388
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.769212; // fuzzed, old value = 3.736050
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.931412; // fuzzed, old value = 0.930491
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.302461; // fuzzed, old value = 0.305480
	FUZZ s.characters.HW_Line = 1.721978; // fuzzed, old value = 1.687232
	FUZZ s.characters.HW_F = 3.226847; // fuzzed, old value = 3.283401
	FUZZ s.characters.HW_Tricky = 2.612951; // fuzzed, old value = 2.603006
	FUZZ s.characters.HW_Hard = 4.218492; // fuzzed, old value = 4.292818
	FUZZ s.characters.HW_Other = 3.911752; // fuzzed, old value = 3.928408

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.482964; // fuzzed, old value = 0.497646
	FUZZ s.csr.DeleteBadTriangles = 2.124101; // fuzzed, old value = 2.071333
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.472190; // fuzzed, old value = 1.504132

	FUZZ s.graph.MinimalDistTresh = 1.854608; // fuzzed, old value = 1.841037
	FUZZ s.graph.RatioSub = 1.005202; // fuzzed, old value = 0.984469
	FUZZ s.graph.RatioTresh = 0.402732; // fuzzed, old value = 0.405648

	FUZZ s.utils.SlashLineDensity = 0.480961; // fuzzed, old value = 0.493247
	FUZZ s.utils.TestPlusDensity = 0.417797; // fuzzed, old value = 0.410542
	FUZZ s.utils.TestPlusSq = 0.427328; // fuzzed, old value = 0.424974
	FUZZ s.utils.TestMinusRatio = 0.368049; // fuzzed, old value = 0.363149
	FUZZ s.utils.TestMinusDensity = 0.616128; // fuzzed, old value = 0.622435
	FUZZ s.utils.TestMinusHeightFactor = 0.789442; // fuzzed, old value = 0.801175

	FUZZ s.separator.hu_1_1 = 0.189831; // fuzzed, old value = 0.190007
	FUZZ s.separator.hu_1_2 = 0.079148; // fuzzed, old value = 0.078733
	FUZZ s.separator.hu_0_1 = 0.241533; // fuzzed, old value = 0.248770
	FUZZ s.separator.hu_1_3 = 0.088320; // fuzzed, old value = 0.087239
	FUZZ s.separator.hu_0_2 = 0.250102; // fuzzed, old value = 0.247747
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.523744; // fuzzed, old value = 0.510414
	FUZZ s.separator.capHeightMax = 1.337355; // fuzzed, old value = 1.372942
	FUZZ s.separator.gdConst = 1.520337; // fuzzed, old value = 1.484899
	FUZZ s.separator.SurfCoef = 2.811615; // fuzzed, old value = 2.789485
	FUZZ s.separator.capHeightRatio = 0.248671; // fuzzed, old value = 0.248155
	FUZZ s.separator.capHeightRatio2 = 1.817621; // fuzzed, old value = 1.798248
	FUZZ s.separator.getRatio1 = 0.869905; // fuzzed, old value = 0.860610
	FUZZ s.separator.getRatio2 = 1.107858; // fuzzed, old value = 1.082034
	FUZZ s.separator.testSlashLine1 = 3.056236; // fuzzed, old value = 3.053940
	FUZZ s.separator.testSlashLine2 = 2.947643; // fuzzed, old value = 2.932124
	FUZZ s.separator.minDensity = 0.209188; // fuzzed, old value = 0.203940
	FUZZ s.separator.maxDensity = 0.874702; // fuzzed, old value = 0.863266
	FUZZ s.separator.extCapHeightMin = 0.307440; // fuzzed, old value = 0.301081
	FUZZ s.separator.extCapHeightMax = 2.050196; // fuzzed, old value = 2.038997
	FUZZ s.separator.extRatioMin = 0.277232; // fuzzed, old value = 0.277035
	FUZZ s.separator.extRatioMax = 1.432846; // fuzzed, old value = 1.457489
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.487118; // fuzzed, old value = 0.475771
	FUZZ s.labels.weightUnderline = 0.315205; // fuzzed, old value = 0.309763
	FUZZ s.labels.ratioBase = 0.827268; // fuzzed, old value = 0.847879
	FUZZ s.labels.ratioWeight = 0.307824; // fuzzed, old value = 0.302202
	FUZZ s.labels.adjustDec = 1.268716; // fuzzed, old value = 1.265408
	FUZZ s.labels.adjustInc = 0.867507; // fuzzed, old value = 0.843477
	FUZZ s.labels.sameLineEps = 0.119324; // fuzzed, old value = 0.119477
	FUZZ s.labels.heightRatio = 0.846923; // fuzzed, old value = 0.822444
	FUZZ s.labels.medHeightFactor = 0.481943; // fuzzed, old value = 0.479269
	FUZZ s.labels.capHeightError = 0.503494; // fuzzed, old value = 0.514391

	FUZZ s.lcomb.MaximalSymbolDistance = 2.636896; // fuzzed, old value = 2.625318
	FUZZ s.lcomb.TestSlashLineEps = 3.053863; // fuzzed, old value = 3.117265
	FUZZ s.lcomb.TestMinHeightFactor = 0.470017; // fuzzed, old value = 0.459007
	FUZZ s.lcomb.TestMaxHeightFactor = 1.132022; // fuzzed, old value = 1.140889
	FUZZ s.lcomb.RectHeightRatio = 0.524815; // fuzzed, old value = 0.514783
	FUZZ s.lcomb.H1SuperscriptSpace = 1.141495; // fuzzed, old value = 1.135982
	FUZZ s.lcomb.H2LowercaseSpace = 0.502550; // fuzzed, old value = 0.508634
	FUZZ s.lcomb.H3LowercaseSpace = 0.510556; // fuzzed, old value = 0.506255
	FUZZ s.lcomb.H4SubscriptSpace = 0.515064; // fuzzed, old value = 0.523707
	FUZZ s.lcomb.FillLabelFactor1 = 0.502598; // fuzzed, old value = 0.492685
	FUZZ s.lcomb.FillLabelFactor2 = 0.493979; // fuzzed, old value = 0.482821
}

