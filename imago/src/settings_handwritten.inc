
void updateSettingsHandwritten(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.301284; // fuzzed, old value = 0.302570
	FUZZ s.molecule.LengthFactor_medium = 0.413086; // fuzzed, old value = 0.429750
	FUZZ s.molecule.LengthFactor_default = 0.462752; // fuzzed, old value = 0.457307
	FUZZ s.molecule.LengthValue_long = 105.214238; // fuzzed, old value = 106.867957
	FUZZ s.molecule.LengthValue_medium = 87.259669; // fuzzed, old value = 83.519308
	FUZZ s.molecule.SpaceMultiply = 1.555491; // fuzzed, old value = 1.519979
	FUZZ s.molecule.AngleTreshold = 0.258607; // fuzzed, old value = 0.264299
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 15.462677; // fuzzed, old value = 15.974145
	FUZZ s.estimation.LineThickness = 5.724547; // fuzzed, old value = 5.899060
	FUZZ s.estimation.AvgBondLength = 31.784183; // fuzzed, old value = 30.880261
	FUZZ s.estimation.AddVertexEps = 4.883766; // fuzzed, old value = 4.984631
	FUZZ s.estimation.MaxSymRatio = 1.060198; // fuzzed, old value = 1.038869
	FUZZ s.estimation.MinSymRatio = 0.317908; // fuzzed, old value = 0.334174
	FUZZ s.estimation.ParLinesEps = 0.486001; // fuzzed, old value = 0.506164
	FUZZ s.estimation.SymHeightErr = 28.804558; // fuzzed, old value = 28.848799
	FUZZ s.estimation.CapitalHeightError = 0.867180; // fuzzed, old value = 0.839008
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.510833; // fuzzed, old value = 0.507296
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 117; // fuzzed, old value = 119
	FUZZ s.mbond.LongErr = 0.351540; // fuzzed, old value = 0.350911
	FUZZ s.mbond.MediumBond = 91; // fuzzed, old value = 89
	FUZZ s.mbond.MediumErr = 0.399829; // fuzzed, old value = 0.400463
	FUZZ s.mbond.DefaultErr = 0.634570; // fuzzed, old value = 0.637521
	FUZZ s.mbond.ParBondsEps = 0.311104; // fuzzed, old value = 0.322765
	FUZZ s.mbond.DoubleRatioTresh = 7.339204; // fuzzed, old value = 7.175416
	FUZZ s.mbond.DoubleCoef = 0.082216; // fuzzed, old value = 0.084322
	FUZZ s.mbond.DoubleMagic1 = 0.921396; // fuzzed, old value = 0.908658
	FUZZ s.mbond.DoubleMagic2 = 0.986674; // fuzzed, old value = 0.974999
	FUZZ s.mbond.DoubleTreshMin = 0.101219; // fuzzed, old value = 0.099414
	FUZZ s.mbond.DoubleTreshMax = 0.895620; // fuzzed, old value = 0.882526
	FUZZ s.mbond.MaxLen1 = 162.869661; // fuzzed, old value = 165.689986
	FUZZ s.mbond.MaxLen2 = 128.577862; // fuzzed, old value = 123.345638
	FUZZ s.mbond.MaxLen3 = 110.670699; // fuzzed, old value = 109.877477
	FUZZ s.mbond.MaxLen4 = 115.370121; // fuzzed, old value = 112.082755
	FUZZ s.mbond.MaxLen5 = 89.336149; // fuzzed, old value = 87.080020
	FUZZ s.mbond.MinLen1 = 80.575157; // fuzzed, old value = 83.925172
	FUZZ s.mbond.MinLen2 = 78.591956; // fuzzed, old value = 78.760091
	FUZZ s.mbond.mbe1 = 0.082326; // fuzzed, old value = 0.084229
	FUZZ s.mbond.mbe2 = 0.145100; // fuzzed, old value = 0.149796
	FUZZ s.mbond.mbe3 = 0.204717; // fuzzed, old value = 0.198819
	FUZZ s.mbond.mbe4 = 0.183307; // fuzzed, old value = 0.179832
	FUZZ s.mbond.mbe5 = 0.156813; // fuzzed, old value = 0.164799
	FUZZ s.mbond.mbe6 = 0.221646; // fuzzed, old value = 0.212412
	FUZZ s.mbond.mbe7 = 0.365801; // fuzzed, old value = 0.374982
	FUZZ s.mbond.mbe_def = 0.520314; // fuzzed, old value = 0.528189
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.330767; // fuzzed, old value = 0.330274
	FUZZ s.mbond.DoubleRightLengthTresh = 0.305574; // fuzzed, old value = 0.311757
	FUZZ s.mbond.TripleLeftLengthTresh = 0.260135; // fuzzed, old value = 0.254836
	FUZZ s.mbond.TripleRightLengthTresh = 0.240125; // fuzzed, old value = 0.231319
	FUZZ s.mbond.Case1LengthTresh = 108.371592; // fuzzed, old value = 107.139393
	FUZZ s.mbond.Case1Factor = 0.474674; // fuzzed, old value = 0.457630
	FUZZ s.mbond.Case2LengthTresh = 79.011083; // fuzzed, old value = 78.505911
	FUZZ s.mbond.Case2Factor = 0.678957; // fuzzed, old value = 0.710168
	FUZZ s.mbond.Case3Factor = 0.920534; // fuzzed, old value = 0.923961
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.089899; // fuzzed, old value = 0.092088
	FUZZ s.skeleton.BaseSmallErr = 0.146932; // fuzzed, old value = 0.149822
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 21
	FUZZ s.skeleton.ShortMul = 0.329058; // fuzzed, old value = 0.318942
	FUZZ s.skeleton.MediumBondLen = 84; // fuzzed, old value = 81
	FUZZ s.skeleton.MediumMul = 0.183025; // fuzzed, old value = 0.183055
	FUZZ s.skeleton.MediumSmallErr = 0.140212; // fuzzed, old value = 0.139798
	FUZZ s.skeleton.LongBondLen = 98; // fuzzed, old value = 99
	FUZZ s.skeleton.LongMul = 0.141836; // fuzzed, old value = 0.144092
	FUZZ s.skeleton.LongSmallErr = 0.063755; // fuzzed, old value = 0.061874
	FUZZ s.skeleton.BrokenRepairFactor = 2.869102; // fuzzed, old value = 2.961979
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.977036; // fuzzed, old value = 1.013235
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.620605; // fuzzed, old value = 2.681059
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.196705; // fuzzed, old value = 0.197867
	FUZZ s.skeleton.DissolveMinErr = 0.164861; // fuzzed, old value = 0.172400
	FUZZ s.skeleton.ConnectBlockS = 10.597200; // fuzzed, old value = 10.180931
	FUZZ s.skeleton.ConnectFactor = 1.918836; // fuzzed, old value = 1.916476
	FUZZ s.skeleton.JoinVerticiesConst = 0.103564; // fuzzed, old value = 0.099035
	FUZZ s.skeleton.DissolveConst = 0.095666; // fuzzed, old value = 0.097487
	FUZZ s.skeleton.Dissolve2Const = 0.188169; // fuzzed, old value = 0.191943
	FUZZ s.skeleton.Join2Const = 0.338141; // fuzzed, old value = 0.346176
	FUZZ s.skeleton.Join3Const = 0.201158; // fuzzed, old value = 0.196397
	FUZZ s.skeleton.DistTreshLimFactor = 1.897177; // fuzzed, old value = 1.956994
	FUZZ s.skeleton.SlopeFact1 = 0.104391; // fuzzed, old value = 0.101623
	FUZZ s.skeleton.SlopeFact2 = 0.183071; // fuzzed, old value = 0.191559
	FUZZ s.skeleton.ShrinkEps = 0.116091; // fuzzed, old value = 0.119830
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.095234; // fuzzed, old value = 0.096791
	FUZZ s.routines.Circle_GapMax = 0.915234; // fuzzed, old value = 0.880749
	FUZZ s.routines.Circle_RMax = 1.941688; // fuzzed, old value = 2.009627
	FUZZ s.routines.Circle_AvgRadius = 0.000107; // fuzzed, old value = 0.000111
	FUZZ s.routines.Circle_MaxRatio = 0.342852; // fuzzed, old value = 0.331571
	FUZZ s.routines.Algebra_IntersectionEps = 0.010676; // fuzzed, old value = 0.010347
	FUZZ s.routines.Algebra_SameLineEps = 0.209587; // fuzzed, old value = 0.215903
	FUZZ s.routines.Approx_Eps1 = 1.136856; // fuzzed, old value = 1.175569
	FUZZ s.routines.Approx_Eps2 = 0.865361; // fuzzed, old value = 0.902789
	FUZZ s.routines.Approx_CalcLineTresh = 0.893882; // fuzzed, old value = 0.866157

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.940418; // fuzzed, old value = 3.038015
	FUZZ s.wbe.SingleDownAngleMax = 43.392633; // fuzzed, old value = 43.691917
	FUZZ s.wbe.SingleDownDistancesMax = 9.820762; // fuzzed, old value = 9.426010
	FUZZ s.wbe.SingleDownLengthMax = 39.544267; // fuzzed, old value = 41.390064
	FUZZ s.wbe.SingleUpRatioEps = 1.910000; // fuzzed, old value = 1.937846
	FUZZ s.wbe.SingleUpDefCoeff = 0.267276; // fuzzed, old value = 0.271987
	FUZZ s.wbe.SingleUpIncCoeff = 0.430513; // fuzzed, old value = 0.440233
	FUZZ s.wbe.SingleUpIncLengthTresh = 37.334897; // fuzzed, old value = 36.095242
	FUZZ s.wbe.SingleUpInterpolateEps = 0.058723; // fuzzed, old value = 0.059636
	FUZZ s.wbe.SingleUpMagicAddition = 0.216021; // fuzzed, old value = 0.218935
	FUZZ s.wbe.SingleUpS2Divisor = 1.817237; // fuzzed, old value = 1.754114
	FUZZ s.wbe.SingleUpMinATresh = 1.808883; // fuzzed, old value = 1.757950
	FUZZ s.wbe.SingleUpSquareRatio = 0.588303; // fuzzed, old value = 0.614713
	FUZZ s.wbe.SingleUpAngleTresh = 0.067465; // fuzzed, old value = 0.066609
	FUZZ s.wbe.SomeTresh = 0.095932; // fuzzed, old value = 0.096693
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = false
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.083744; // fuzzed, old value = 1.076521
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.185928; // fuzzed, old value = 1.147492
	FUZZ s.characters.WriteEasyFactor = 0.945353; // fuzzed, old value = 0.930771
	FUZZ s.characters.WriteVeryEasyFactor = 0.817677; // fuzzed, old value = 0.857479
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.069717; // fuzzed, old value = 2.991472
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.362290; // fuzzed, old value = 3.377354
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.092454; // fuzzed, old value = 0.096137
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.440465; // fuzzed, old value = 2.467374
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.779521; // fuzzed, old value = 3.658874
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.927754; // fuzzed, old value = 0.964310
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.307776; // fuzzed, old value = 0.300146
	FUZZ s.characters.HW_Line = 1.700824; // fuzzed, old value = 1.644108
	FUZZ s.characters.HW_F = 3.307657; // fuzzed, old value = 3.285562
	FUZZ s.characters.HW_Tricky = 2.610371; // fuzzed, old value = 2.742649
	FUZZ s.characters.HW_Hard = 4.300786; // fuzzed, old value = 4.296007
	FUZZ s.characters.HW_Other = 3.871023; // fuzzed, old value = 3.719947

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.496762; // fuzzed, old value = 0.503491
	FUZZ s.csr.DeleteBadTriangles = 2.096970; // fuzzed, old value = 2.048394
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.505216; // fuzzed, old value = 1.548225

	FUZZ s.graph.MinimalDistTresh = 1.849841; // fuzzed, old value = 1.937857
	FUZZ s.graph.RatioSub = 0.978650; // fuzzed, old value = 1.026251
	FUZZ s.graph.RatioTresh = 0.400267; // fuzzed, old value = 0.411047

	FUZZ s.utils.SlashLineDensity = 0.497735; // fuzzed, old value = 0.476448
	FUZZ s.utils.TestPlusDensity = 0.416094; // fuzzed, old value = 0.400710
	FUZZ s.utils.TestPlusSq = 0.427280; // fuzzed, old value = 0.433178
	FUZZ s.utils.TestMinusRatio = 0.362671; // fuzzed, old value = 0.377853
	FUZZ s.utils.TestMinusDensity = 0.617397; // fuzzed, old value = 0.603671
	FUZZ s.utils.TestMinusHeightFactor = 0.812755; // fuzzed, old value = 0.790771

	FUZZ s.separator.hu_1_1 = 0.192638; // fuzzed, old value = 0.202631
	FUZZ s.separator.hu_1_2 = 0.079029; // fuzzed, old value = 0.082376
	FUZZ s.separator.hu_0_1 = 0.248488; // fuzzed, old value = 0.254429
	FUZZ s.separator.hu_1_3 = 0.088236; // fuzzed, old value = 0.086610
	FUZZ s.separator.hu_0_2 = 0.251211; // fuzzed, old value = 0.254119
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.508121; // fuzzed, old value = 0.521925
	FUZZ s.separator.capHeightMax = 1.386347; // fuzzed, old value = 1.456631
	FUZZ s.separator.gdConst = 1.486596; // fuzzed, old value = 1.481872
	FUZZ s.separator.SurfCoef = 2.765933; // fuzzed, old value = 2.856586
	FUZZ s.separator.capHeightRatio = 0.248339; // fuzzed, old value = 0.240552
	FUZZ s.separator.capHeightRatio2 = 1.804413; // fuzzed, old value = 1.880725
	FUZZ s.separator.getRatio1 = 0.865066; // fuzzed, old value = 0.884586
	FUZZ s.separator.getRatio2 = 1.095616; // fuzzed, old value = 1.095497
	FUZZ s.separator.testSlashLine1 = 3.033029; // fuzzed, old value = 2.972579
	FUZZ s.separator.testSlashLine2 = 2.929910; // fuzzed, old value = 2.960105
	FUZZ s.separator.minDensity = 0.206885; // fuzzed, old value = 0.213319
	FUZZ s.separator.maxDensity = 0.871496; // fuzzed, old value = 0.891239
	FUZZ s.separator.extCapHeightMin = 0.303222; // fuzzed, old value = 0.297519
	FUZZ s.separator.extCapHeightMax = 2.055723; // fuzzed, old value = 2.015420
	FUZZ s.separator.extRatioMin = 0.276259; // fuzzed, old value = 0.268058
	FUZZ s.separator.extRatioMax = 1.451684; // fuzzed, old value = 1.386231
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.471671; // fuzzed, old value = 0.480650
	FUZZ s.labels.weightUnderline = 0.312722; // fuzzed, old value = 0.309821
	FUZZ s.labels.ratioBase = 0.858557; // fuzzed, old value = 0.835451
	FUZZ s.labels.ratioWeight = 0.300167; // fuzzed, old value = 0.290683
	FUZZ s.labels.adjustDec = 1.266265; // fuzzed, old value = 1.283240
	FUZZ s.labels.adjustInc = 0.841056; // fuzzed, old value = 0.823409
	FUZZ s.labels.sameLineEps = 0.119673; // fuzzed, old value = 0.124217
	FUZZ s.labels.heightRatio = 0.814846; // fuzzed, old value = 0.785186
	FUZZ s.labels.medHeightFactor = 0.473773; // fuzzed, old value = 0.451621
	FUZZ s.labels.capHeightError = 0.508258; // fuzzed, old value = 0.531481

	FUZZ s.lcomb.MaximalSymbolDistance = 2.637298; // fuzzed, old value = 2.562948
	FUZZ s.lcomb.TestSlashLineEps = 3.130045; // fuzzed, old value = 3.055779
	FUZZ s.lcomb.TestMinHeightFactor = 0.462420; // fuzzed, old value = 0.482815
	FUZZ s.lcomb.TestMaxHeightFactor = 1.148579; // fuzzed, old value = 1.183110
	FUZZ s.lcomb.RectHeightRatio = 0.520647; // fuzzed, old value = 0.506928
	FUZZ s.lcomb.H1SuperscriptSpace = 1.141253; // fuzzed, old value = 1.124392
	FUZZ s.lcomb.H2LowercaseSpace = 0.510965; // fuzzed, old value = 0.509743
	FUZZ s.lcomb.H3LowercaseSpace = 0.499333; // fuzzed, old value = 0.513256
	FUZZ s.lcomb.H4SubscriptSpace = 0.517426; // fuzzed, old value = 0.542061
	FUZZ s.lcomb.FillLabelFactor1 = 0.495811; // fuzzed, old value = 0.492518
	FUZZ s.lcomb.FillLabelFactor2 = 0.485855; // fuzzed, old value = 0.496152
}

