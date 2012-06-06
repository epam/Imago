
void updateSettingsScanned(Settings &s)
{
	FUZZ s.general.UseProbablistics = false; // fuzzed, old value = false

	FUZZ s.separator.ext2charRatio = 1.771798; // fuzzed, old value = 1.801949

	FUZZ s.molecule.LengthFactor_long = 0.338853; // fuzzed, old value = 0.335862
	FUZZ s.molecule.LengthFactor_medium = 0.397616; // fuzzed, old value = 0.389189
	FUZZ s.molecule.LengthFactor_default = 0.468480; // fuzzed, old value = 0.465457
	FUZZ s.molecule.LengthValue_long = 110.844809; // fuzzed, old value = 112.933161
	FUZZ s.molecule.LengthValue_medium = 82.817862; // fuzzed, old value = 83.114573
	FUZZ s.molecule.SpaceMultiply = 1.390003; // fuzzed, old value = 1.361398
	FUZZ s.molecule.AngleTreshold = 0.263779; // fuzzed, old value = 0.264694
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.542347; // fuzzed, old value = 16.945373
	FUZZ s.estimation.LineThickness = 6.901316; // fuzzed, old value = 6.763095
	FUZZ s.estimation.AvgBondLength = 30.471534; // fuzzed, old value = 29.843751
	FUZZ s.estimation.AddVertexEps = 4.667805; // fuzzed, old value = 4.710084
	FUZZ s.estimation.MaxSymRatio = 1.186188; // fuzzed, old value = 1.215313
	FUZZ s.estimation.MinSymRatio = 0.304743; // fuzzed, old value = 0.310935
	FUZZ s.estimation.ParLinesEps = 0.563354; // fuzzed, old value = 0.572737
	FUZZ s.estimation.SymHeightErr = 27.409354; // fuzzed, old value = 26.815725
	FUZZ s.estimation.CapitalHeightError = 0.834278; // fuzzed, old value = 0.837840
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.378156; // fuzzed, old value = 0.377078
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.153076; // fuzzed, old value = 0.15
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 106; // fuzzed, old value = 108
	FUZZ s.mbond.LongErr = 0.321693; // fuzzed, old value = 0.327663
	FUZZ s.mbond.MediumBond = 82; // fuzzed, old value = 83
	FUZZ s.mbond.MediumErr = 0.456050; // fuzzed, old value = 0.450931
	FUZZ s.mbond.DefaultErr = 0.665182; // fuzzed, old value = 0.655651
	FUZZ s.mbond.ParBondsEps = 0.358454; // fuzzed, old value = 0.354030
	FUZZ s.mbond.DoubleRatioTresh = 6.332510; // fuzzed, old value = 6.471163
	FUZZ s.mbond.DoubleCoef = 0.076883; // fuzzed, old value = 0.078614
	FUZZ s.mbond.DoubleMagic1 = 0.873083; // fuzzed, old value = 0.891524
	FUZZ s.mbond.DoubleMagic2 = 0.951512; // fuzzed, old value = 0.928943
	FUZZ s.mbond.DoubleTreshMin = 0.102096; // fuzzed, old value = 0.099657
	FUZZ s.mbond.DoubleTreshMax = 0.800839; // fuzzed, old value = 0.803022
	FUZZ s.mbond.MaxLen1 = 153.323071; // fuzzed, old value = 153.667882
	FUZZ s.mbond.MaxLen2 = 138.763497; // fuzzed, old value = 139.066632
	FUZZ s.mbond.MaxLen3 = 109.301081; // fuzzed, old value = 110.001959
	FUZZ s.mbond.MaxLen4 = 125.160190; // fuzzed, old value = 126.194351
	FUZZ s.mbond.MaxLen5 = 79.612238; // fuzzed, old value = 80.040507
	FUZZ s.mbond.MinLen1 = 88.889324; // fuzzed, old value = 88.318249
	FUZZ s.mbond.MinLen2 = 72.571954; // fuzzed, old value = 72.751407
	FUZZ s.mbond.mbe1 = 0.076154; // fuzzed, old value = 0.075620
	FUZZ s.mbond.mbe2 = 0.160425; // fuzzed, old value = 0.157523
	FUZZ s.mbond.mbe3 = 0.189353; // fuzzed, old value = 0.194205
	FUZZ s.mbond.mbe4 = 0.166404; // fuzzed, old value = 0.170373
	FUZZ s.mbond.mbe5 = 0.155661; // fuzzed, old value = 0.155364
	FUZZ s.mbond.mbe6 = 0.211763; // fuzzed, old value = 0.216894
	FUZZ s.mbond.mbe7 = 0.380054; // fuzzed, old value = 0.378093
	FUZZ s.mbond.mbe_def = 0.531358; // fuzzed, old value = 0.542036
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.346371; // fuzzed, old value = 0.349551
	FUZZ s.mbond.DoubleRightLengthTresh = 0.303215; // fuzzed, old value = 0.299133
	FUZZ s.mbond.TripleLeftLengthTresh = 0.240531; // fuzzed, old value = 0.235897
	FUZZ s.mbond.TripleRightLengthTresh = 0.225971; // fuzzed, old value = 0.228166
	FUZZ s.mbond.Case1LengthTresh = 90.183296; // fuzzed, old value = 89.931276
	FUZZ s.mbond.Case1Factor = 0.368570; // fuzzed, old value = 0.370707
	FUZZ s.mbond.Case2LengthTresh = 84.376922; // fuzzed, old value = 84.293508
	FUZZ s.mbond.Case2Factor = 0.695911; // fuzzed, old value = 0.688291
	FUZZ s.mbond.Case3Factor = 1.010147; // fuzzed, old value = 1.015964
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.106559; // fuzzed, old value = 0.104889
	FUZZ s.skeleton.BaseSmallErr = 0.156184; // fuzzed, old value = 0.159795
	FUZZ s.skeleton.ShortBondLen = 21; // fuzzed, old value = 21
	FUZZ s.skeleton.ShortMul = 0.324988; // fuzzed, old value = 0.330679
	FUZZ s.skeleton.MediumBondLen = 89; // fuzzed, old value = 87
	FUZZ s.skeleton.MediumMul = 0.166926; // fuzzed, old value = 0.170096
	FUZZ s.skeleton.MediumSmallErr = 0.128049; // fuzzed, old value = 0.129541
	FUZZ s.skeleton.LongBondLen = 98; // fuzzed, old value = 99
	FUZZ s.skeleton.LongMul = 0.142736; // fuzzed, old value = 0.140841
	FUZZ s.skeleton.LongSmallErr = 0.062092; // fuzzed, old value = 0.063159
	FUZZ s.skeleton.BrokenRepairFactor = 3.405501; // fuzzed, old value = 3.381710
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.967483; // fuzzed, old value = 0.972795
	FUZZ s.skeleton.BrokenRepairCoef2 = 3.087550; // fuzzed, old value = 3.071458
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.209671; // fuzzed, old value = 0.214970
	FUZZ s.skeleton.DissolveMinErr = 0.176070; // fuzzed, old value = 0.172985
	FUZZ s.skeleton.ConnectBlockS = 9.625256; // fuzzed, old value = 9.835867
	FUZZ s.skeleton.ConnectFactor = 2.077395; // fuzzed, old value = 2.043158
	FUZZ s.skeleton.JoinVerticiesConst = 0.105085; // fuzzed, old value = 0.103958
	FUZZ s.skeleton.DissolveConst = 0.097277; // fuzzed, old value = 0.095547
	FUZZ s.skeleton.Dissolve2Const = 0.191600; // fuzzed, old value = 0.190304
	FUZZ s.skeleton.Join2Const = 0.264572; // fuzzed, old value = 0.265372
	FUZZ s.skeleton.Join3Const = 0.183748; // fuzzed, old value = 0.180264
	FUZZ s.skeleton.DistTreshLimFactor = 2.105590; // fuzzed, old value = 2.077342
	FUZZ s.skeleton.SlopeFact1 = 0.091244; // fuzzed, old value = 0.091046
	FUZZ s.skeleton.SlopeFact2 = 0.161702; // fuzzed, old value = 0.164744
	FUZZ s.skeleton.ShrinkEps = 0.140281; // fuzzed, old value = 0.139524
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	
	FUZZ s.routines.Circle_GapRadiusMax = 1.050731; // fuzzed, old value = 1.064082
	FUZZ s.routines.Circle_GapAngleMax = 0.203439; // fuzzed, old value = 0.199859
	FUZZ s.routines.Circle_MinRadius = 6.900335; // fuzzed, old value = 6.872153
	FUZZ s.routines.Circle_MaxDeviation = 0.010575; // fuzzed, old value = 0.010489
	FUZZ s.routines.Circle_AsCharFactor = 1.077311; // fuzzed, old value = 1.081005

	FUZZ s.routines.Algebra_IntersectionEps = 0.011465; // fuzzed, old value = 0.011607
	FUZZ s.routines.Algebra_SameLineEps = 0.224437; // fuzzed, old value = 0.225538
	FUZZ s.routines.Approx_Eps1 = 1.141541; // fuzzed, old value = 1.134037
	FUZZ s.routines.Approx_Eps2 = 0.851725; // fuzzed, old value = 0.836914
	FUZZ s.routines.Approx_CalcLineTresh = 0.914830; // fuzzed, old value = 0.929779
	FUZZ s.routines.Contour_Eps1 = 0.965831; // fuzzed, old value = 0.962720
	FUZZ s.routines.Contour_Eps2 = 0.683620; // fuzzed, old value = 0.672058

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.542952; // fuzzed, old value = 2.580276
	FUZZ s.wbe.SingleDownAngleMax = 43.126895; // fuzzed, old value = 42.926033
	FUZZ s.wbe.SingleDownDistancesMax = 10.048758; // fuzzed, old value = 10.174664
	FUZZ s.wbe.SingleDownLengthMax = 50.556936; // fuzzed, old value = 49.781544
	FUZZ s.wbe.SingleUpRatioEps = 1.605023; // fuzzed, old value = 1.633464
	FUZZ s.wbe.SingleUpDefCoeff = 0.273551; // fuzzed, old value = 0.270767
	FUZZ s.wbe.SingleUpIncCoeff = 0.494887; // fuzzed, old value = 0.484214
	FUZZ s.wbe.SingleUpIncLengthTresh = 35.194914; // fuzzed, old value = 35.761314
	FUZZ s.wbe.SingleUpInterpolateEps = 0.065090; // fuzzed, old value = 0.066089
	FUZZ s.wbe.SingleUpMagicAddition = 0.251085; // fuzzed, old value = 0.248928
	FUZZ s.wbe.SingleUpS2Divisor = 1.459195; // fuzzed, old value = 1.426453
	FUZZ s.wbe.SingleUpMinATresh = 1.693127; // fuzzed, old value = 1.680023
	FUZZ s.wbe.SingleUpSquareRatio = 0.624043; // fuzzed, old value = 0.629596
	FUZZ s.wbe.SingleUpAngleTresh = 0.067596; // fuzzed, old value = 0.068342
	FUZZ s.wbe.SomeTresh = 0.101527; // fuzzed, old value = 0.102460
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = false; // fuzzed, old value = true
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 0.985291; // fuzzed, old value = 0.992208
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.098267; // fuzzed, old value = 1.091860
	FUZZ s.characters.WriteEasyFactor = 0.962507; // fuzzed, old value = 0.978938
	FUZZ s.characters.WriteVeryEasyFactor = 0.965804; // fuzzed, old value = 0.946090
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.138903; // fuzzed, old value = 3.200350
	FUZZ s.characters.PossibleCharacterDistanceWeak = 2.994244; // fuzzed, old value = 3.068206
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.098364; // fuzzed, old value = 0.100781
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.553251; // fuzzed, old value = 2.553011
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.801960; // fuzzed, old value = 3.849573
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.978328; // fuzzed, old value = 0.957791
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.288967; // fuzzed, old value = 0.295325
	FUZZ s.characters.HW_Line = 1.538010; // fuzzed, old value = 1.517041
	FUZZ s.characters.HW_F = 3.433685; // fuzzed, old value = 3.372959
	FUZZ s.characters.HW_Tricky = 3.087902; // fuzzed, old value = 3.054108
	FUZZ s.characters.HW_Hard = 4.238485; // fuzzed, old value = 4.319891
	FUZZ s.characters.HW_Other = 3.554941; // fuzzed, old value = 3.555703

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.513776; // fuzzed, old value = 0.512755
	FUZZ s.csr.DeleteBadTriangles = 1.987894; // fuzzed, old value = 1.964928
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.787322; // fuzzed, old value = 1.762646

	FUZZ s.graph.MinimalDistTresh = 1.967968; // fuzzed, old value = 1.961281
	FUZZ s.graph.RatioSub = 0.997638; // fuzzed, old value = 0.986495
	FUZZ s.graph.RatioTresh = 0.472818; // fuzzed, old value = 0.464300

	FUZZ s.utils.SlashLineDensity = 0.377128; // fuzzed, old value = 0.376036
	FUZZ s.utils.TestPlusDensity = 0.449545; // fuzzed, old value = 0.443502
	FUZZ s.utils.TestPlusSq = 0.438382; // fuzzed, old value = 0.430330
	FUZZ s.utils.TestMinusRatio = 0.320861; // fuzzed, old value = 0.328968
	FUZZ s.utils.TestMinusDensity = 0.617105; // fuzzed, old value = 0.608755
	FUZZ s.utils.TestMinusHeightFactor = 0.841425; // fuzzed, old value = 0.861454

	FUZZ s.separator.hu_1_1 = 0.226956; // fuzzed, old value = 0.222657
	FUZZ s.separator.hu_1_2 = 0.085619; // fuzzed, old value = 0.083639
	FUZZ s.separator.hu_0_1 = 0.211932; // fuzzed, old value = 0.210165
	FUZZ s.separator.hu_1_3 = 0.089489; // fuzzed, old value = 0.089135
	FUZZ s.separator.hu_0_2 = 0.217154; // fuzzed, old value = 0.214314
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.544131; // fuzzed, old value = 0.533280
	FUZZ s.separator.capHeightMax = 1.482986; // fuzzed, old value = 1.468531
	FUZZ s.separator.gdConst = 1.574764; // fuzzed, old value = 1.594182
	FUZZ s.separator.SurfCoef = 3.126147; // fuzzed, old value = 3.175393
	FUZZ s.separator.capHeightRatio = 0.281610; // fuzzed, old value = 0.276716
	FUZZ s.separator.capHeightRatio2 = 1.921472; // fuzzed, old value = 1.963837
	FUZZ s.separator.getRatio1 = 1.030272; // fuzzed, old value = 1.029899
	FUZZ s.separator.getRatio2 = 1.228747; // fuzzed, old value = 1.239054
	FUZZ s.separator.testSlashLine1 = 3.101050; // fuzzed, old value = 3.062637
	FUZZ s.separator.testSlashLine2 = 2.550970; // fuzzed, old value = 2.571696
	FUZZ s.separator.minDensity = 0.195769; // fuzzed, old value = 0.191277
	FUZZ s.separator.maxDensity = 0.926268; // fuzzed, old value = 0.919266
	FUZZ s.separator.extCapHeightMin = 0.288028; // fuzzed, old value = 0.293890
	FUZZ s.separator.extCapHeightMax = 2.058896; // fuzzed, old value = 2.101175
	FUZZ s.separator.extRatioMin = 0.330762; // fuzzed, old value = 0.337869
	FUZZ s.separator.extRatioMax = 1.546139; // fuzzed, old value = 1.529181
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = false; // fuzzed, old value = false

	FUZZ s.labels.underlinePos = 0.399299; // fuzzed, old value = 0.391654
	FUZZ s.labels.weightUnderline = 0.279264; // fuzzed, old value = 0.276944
	FUZZ s.labels.ratioBase = 0.743367; // fuzzed, old value = 0.756460
	FUZZ s.labels.ratioWeight = 0.282293; // fuzzed, old value = 0.284394
	FUZZ s.labels.adjustDec = 1.282061; // fuzzed, old value = 1.253712
	FUZZ s.labels.adjustInc = 0.777948; // fuzzed, old value = 0.775452
	FUZZ s.labels.sameLineEps = 0.113361; // fuzzed, old value = 0.110600
	FUZZ s.labels.heightRatio = 0.757841; // fuzzed, old value = 0.744500
	FUZZ s.labels.medHeightFactor = 0.536691; // fuzzed, old value = 0.540594
	FUZZ s.labels.capHeightError = 0.494046; // fuzzed, old value = 0.495467

	FUZZ s.lcomb.MaximalSymbolDistance = 2.802787; // fuzzed, old value = 2.797372
	FUZZ s.lcomb.TestSlashLineEps = 3.522082; // fuzzed, old value = 3.539937
	FUZZ s.lcomb.TestMinHeightFactor = 0.588148; // fuzzed, old value = 0.596755
	FUZZ s.lcomb.TestMaxHeightFactor = 1.110332; // fuzzed, old value = 1.106172
	FUZZ s.lcomb.RectHeightRatio = 0.480207; // fuzzed, old value = 0.476973
	FUZZ s.lcomb.H1SuperscriptSpace = 1.066519; // fuzzed, old value = 1.048816
	FUZZ s.lcomb.H2LowercaseSpace = 0.441986; // fuzzed, old value = 0.451700
	FUZZ s.lcomb.H3LowercaseSpace = 0.451438; // fuzzed, old value = 0.453821
	FUZZ s.lcomb.H4SubscriptSpace = 0.497856; // fuzzed, old value = 0.504323
	FUZZ s.lcomb.FillLabelFactor1 = 0.492940; // fuzzed, old value = 0.504135
	FUZZ s.lcomb.FillLabelFactor2 = 0.555682; // fuzzed, old value = 0.554126

	FUZZ s.p_estimator.DefaultApriority = 0.521156; // fuzzed, old value = 0.515750
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.791410; // fuzzed, old value = 0.795885
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.248403; // fuzzed, old value = 0.253013
	FUZZ s.p_estimator.LogisticScale = 0.957780; // fuzzed, old value = 0.959909
	FUZZ s.p_estimator.LogisticLocation = 1.008000; // fuzzed, old value = 1.004289
}
