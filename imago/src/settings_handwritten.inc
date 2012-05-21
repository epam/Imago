
void updateSettingsHandwritten(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.302570; // fuzzed, old value = 0.316981
	FUZZ s.molecule.LengthFactor_medium = 0.429750; // fuzzed, old value = 0.426186
	FUZZ s.molecule.LengthFactor_default = 0.457307; // fuzzed, old value = 0.481170
	FUZZ s.molecule.LengthValue_long = 106.867957; // fuzzed, old value = 103.962175
	FUZZ s.molecule.LengthValue_medium = 83.519308; // fuzzed, old value = 84.220093
	FUZZ s.molecule.SpaceMultiply = 1.519979; // fuzzed, old value = 1.462494
	FUZZ s.molecule.AngleTreshold = 0.264299; // fuzzed, old value = 0.252597
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 15.974145; // fuzzed, old value = 16.0
	FUZZ s.estimation.LineThickness = 5.899060; // fuzzed, old value = 6.0
	FUZZ s.estimation.AvgBondLength = 30.880261; // fuzzed, old value = 30.0
	FUZZ s.estimation.AddVertexEps = 4.984631; // fuzzed, old value = 5.171899
	FUZZ s.estimation.MaxSymRatio = 1.038869; // fuzzed, old value = 1.073283
	FUZZ s.estimation.MinSymRatio = 0.334174; // fuzzed, old value = 0.332828
	FUZZ s.estimation.ParLinesEps = 0.506164; // fuzzed, old value = 0.512849
	FUZZ s.estimation.SymHeightErr = 28.848799; // fuzzed, old value = 28.737111
	FUZZ s.estimation.CapitalHeightError = 0.839008; // fuzzed, old value = 0.849315
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.507296; // fuzzed, old value = 0.510033
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 119; // fuzzed, old value = 119
	FUZZ s.mbond.LongErr = 0.350911; // fuzzed, old value = 0.362768
	FUZZ s.mbond.MediumBond = 89; // fuzzed, old value = 90
	FUZZ s.mbond.MediumErr = 0.400463; // fuzzed, old value = 0.392199
	FUZZ s.mbond.DefaultErr = 0.637521; // fuzzed, old value = 0.635246
	FUZZ s.mbond.ParBondsEps = 0.322765; // fuzzed, old value = 0.336346
	FUZZ s.mbond.DoubleRatioTresh = 7.175416; // fuzzed, old value = 7.338240
	FUZZ s.mbond.DoubleCoef = 0.084322; // fuzzed, old value = 0.082408
	FUZZ s.mbond.DoubleMagic1 = 0.908658; // fuzzed, old value = 0.946310
	FUZZ s.mbond.DoubleMagic2 = 0.974999; // fuzzed, old value = 1.015646
	FUZZ s.mbond.DoubleTreshMin = 0.099414; // fuzzed, old value = 0.100697
	FUZZ s.mbond.DoubleTreshMax = 0.882526; // fuzzed, old value = 0.882991
	FUZZ s.mbond.MaxLen1 = 165.689986; // fuzzed, old value = 164.156731
	FUZZ s.mbond.MaxLen2 = 123.345638; // fuzzed, old value = 122.830393
	FUZZ s.mbond.MaxLen3 = 109.877477; // fuzzed, old value = 109.414501
	FUZZ s.mbond.MaxLen4 = 112.082755; // fuzzed, old value = 109.194680
	FUZZ s.mbond.MaxLen5 = 87.080020; // fuzzed, old value = 85.838948
	FUZZ s.mbond.MinLen1 = 83.925172; // fuzzed, old value = 86.382026
	FUZZ s.mbond.MinLen2 = 78.760091; // fuzzed, old value = 76.351772
	FUZZ s.mbond.mbe1 = 0.084229; // fuzzed, old value = 0.082278
	FUZZ s.mbond.mbe2 = 0.149796; // fuzzed, old value = 0.152398
	FUZZ s.mbond.mbe3 = 0.198819; // fuzzed, old value = 0.200465
	FUZZ s.mbond.mbe4 = 0.179832; // fuzzed, old value = 0.184519
	FUZZ s.mbond.mbe5 = 0.164799; // fuzzed, old value = 0.158265
	FUZZ s.mbond.mbe6 = 0.212412; // fuzzed, old value = 0.209079
	FUZZ s.mbond.mbe7 = 0.374982; // fuzzed, old value = 0.391566
	FUZZ s.mbond.mbe_def = 0.528189; // fuzzed, old value = 0.519814
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.330274; // fuzzed, old value = 0.330903
	FUZZ s.mbond.DoubleRightLengthTresh = 0.311757; // fuzzed, old value = 0.310036
	FUZZ s.mbond.TripleLeftLengthTresh = 0.254836; // fuzzed, old value = 0.255772
	FUZZ s.mbond.TripleRightLengthTresh = 0.231319; // fuzzed, old value = 0.228044
	FUZZ s.mbond.Case1LengthTresh = 107.139393; // fuzzed, old value = 102.074306
	FUZZ s.mbond.Case1Factor = 0.457630; // fuzzed, old value = 0.438170
	FUZZ s.mbond.Case2LengthTresh = 78.505911; // fuzzed, old value = 78.284797
	FUZZ s.mbond.Case2Factor = 0.710168; // fuzzed, old value = 0.699134
	FUZZ s.mbond.Case3Factor = 0.923961; // fuzzed, old value = 0.912423
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.092088; // fuzzed, old value = 0.095546
	FUZZ s.skeleton.BaseSmallErr = 0.149822; // fuzzed, old value = 0.151619
	FUZZ s.skeleton.ShortBondLen = 21; // fuzzed, old value = 21
	FUZZ s.skeleton.ShortMul = 0.318942; // fuzzed, old value = 0.311016
	FUZZ s.skeleton.MediumBondLen = 81; // fuzzed, old value = 84
	FUZZ s.skeleton.MediumMul = 0.183055; // fuzzed, old value = 0.175004
	FUZZ s.skeleton.MediumSmallErr = 0.139798; // fuzzed, old value = 0.139131
	FUZZ s.skeleton.LongBondLen = 99; // fuzzed, old value = 102
	FUZZ s.skeleton.LongMul = 0.144092; // fuzzed, old value = 0.149453
	FUZZ s.skeleton.LongSmallErr = 0.061874; // fuzzed, old value = 0.062468
	FUZZ s.skeleton.BrokenRepairFactor = 2.961979; // fuzzed, old value = 2.958580
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.013235; // fuzzed, old value = 0.969769
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.681059; // fuzzed, old value = 2.674973
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.197867; // fuzzed, old value = 0.204331
	FUZZ s.skeleton.DissolveMinErr = 0.172400; // fuzzed, old value = 0.173591
	FUZZ s.skeleton.ConnectBlockS = 10.180931; // fuzzed, old value = 10.342266
	FUZZ s.skeleton.ConnectFactor = 1.916476; // fuzzed, old value = 1.996873
	FUZZ s.skeleton.JoinVerticiesConst = 0.099035; // fuzzed, old value = 0.099156
	FUZZ s.skeleton.DissolveConst = 0.097487; // fuzzed, old value = 0.097573
	FUZZ s.skeleton.Dissolve2Const = 0.191943; // fuzzed, old value = 0.200409
	FUZZ s.skeleton.Join2Const = 0.346176; // fuzzed, old value = 0.340481
	FUZZ s.skeleton.Join3Const = 0.196397; // fuzzed, old value = 0.188169
	FUZZ s.skeleton.DistTreshLimFactor = 1.956994; // fuzzed, old value = 2.006374
	FUZZ s.skeleton.SlopeFact1 = 0.101623; // fuzzed, old value = 0.099698
	FUZZ s.skeleton.SlopeFact2 = 0.191559; // fuzzed, old value = 0.193475
	FUZZ s.skeleton.ShrinkEps = 0.119830; // fuzzed, old value = 0.124536
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.096791; // fuzzed, old value = 0.096100
	FUZZ s.routines.Circle_GapMax = 0.880749; // fuzzed, old value = 0.925721
	FUZZ s.routines.Circle_RMax = 2.009627; // fuzzed, old value = 2.025760
	FUZZ s.routines.Circle_AvgRadius = 0.000111; // fuzzed, old value = 0.000109
	FUZZ s.routines.Circle_MaxRatio = 0.331571; // fuzzed, old value = 0.321018
	FUZZ s.routines.Algebra_IntersectionEps = 0.010347; // fuzzed, old value = 0.010066
	FUZZ s.routines.Algebra_SameLineEps = 0.215903; // fuzzed, old value = 0.211599
	FUZZ s.routines.Approx_Eps1 = 1.175569; // fuzzed, old value = 1.167437
	FUZZ s.routines.Approx_Eps2 = 0.902789; // fuzzed, old value = 0.888855
	FUZZ s.routines.Approx_CalcLineTresh = 0.866157; // fuzzed, old value = 0.910098

	FUZZ s.weak_seg.SubpixelDraw = 0.501652; // fuzzed, old value = 0.5
	FUZZ s.weak_seg.RectangularCropAreaTreshold = 0.294521; // fuzzed, old value = 0.300326
	FUZZ s.weak_seg.RectangularCropFitTreshold = 1.033818; // fuzzed, old value = 1.067597
	FUZZ s.weak_seg.RefineWidth = 0.908987; // fuzzed, old value = 0.867841
	FUZZ s.weak_seg.MinDistanceDraw = 1.419009; // fuzzed, old value = 1.378518

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 3.038015; // fuzzed, old value = 2.967701
	FUZZ s.wbe.SingleDownAngleMax = 43.691917; // fuzzed, old value = 44.790036
	FUZZ s.wbe.SingleDownDistancesMax = 9.426010; // fuzzed, old value = 9.483096
	FUZZ s.wbe.SingleDownLengthMax = 41.390064; // fuzzed, old value = 43.273222
	FUZZ s.wbe.SingleUpRatioEps = 1.937846; // fuzzed, old value = 1.852297
	FUZZ s.wbe.SingleUpDefCoeff = 0.271987; // fuzzed, old value = 0.271484
	FUZZ s.wbe.SingleUpIncCoeff = 0.440233; // fuzzed, old value = 0.422746
	FUZZ s.wbe.SingleUpIncLengthTresh = 36.095242; // fuzzed, old value = 35.707890
	FUZZ s.wbe.SingleUpInterpolateEps = 0.059636; // fuzzed, old value = 0.061760
	FUZZ s.wbe.SingleUpMagicAddition = 0.218935; // fuzzed, old value = 0.223457
	FUZZ s.wbe.SingleUpS2Divisor = 1.754114; // fuzzed, old value = 1.674376
	FUZZ s.wbe.SingleUpMinATresh = 1.757950; // fuzzed, old value = 1.713060
	FUZZ s.wbe.SingleUpSquareRatio = 0.614713; // fuzzed, old value = 0.643772
	FUZZ s.wbe.SingleUpAngleTresh = 0.066609; // fuzzed, old value = 0.067078
	FUZZ s.wbe.SomeTresh = 0.096693; // fuzzed, old value = 0.096287
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = false; // fuzzed, old value = true
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.076521; // fuzzed, old value = 1.083217
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.147492; // fuzzed, old value = 1.173916
	FUZZ s.characters.WriteEasyFactor = 0.930771; // fuzzed, old value = 0.927424
	FUZZ s.characters.WriteVeryEasyFactor = 0.857479; // fuzzed, old value = 0.838911
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 2.991472; // fuzzed, old value = 2.947747
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.377354; // fuzzed, old value = 3.417408
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.096137; // fuzzed, old value = 0.098672
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.467374; // fuzzed, old value = 2.525097
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.658874; // fuzzed, old value = 3.674343
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.964310; // fuzzed, old value = 0.985313
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.300146; // fuzzed, old value = 0.299341
	FUZZ s.characters.HW_Line = 1.644108; // fuzzed, old value = 1.652416
	FUZZ s.characters.HW_F = 3.285562; // fuzzed, old value = 3.195723
	FUZZ s.characters.HW_Tricky = 2.742649; // fuzzed, old value = 2.636925
	FUZZ s.characters.HW_Hard = 4.296007; // fuzzed, old value = 4.313760
	FUZZ s.characters.HW_Other = 3.719947; // fuzzed, old value = 3.627372

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.503491; // fuzzed, old value = 0.514321
	FUZZ s.csr.DeleteBadTriangles = 2.048394; // fuzzed, old value = 1.966536
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.548225; // fuzzed, old value = 1.531569

	FUZZ s.graph.MinimalDistTresh = 1.937857; // fuzzed, old value = 2.004029
	FUZZ s.graph.RatioSub = 1.026251; // fuzzed, old value = 0.984608
	FUZZ s.graph.RatioTresh = 0.411047; // fuzzed, old value = 0.412152

	FUZZ s.utils.SlashLineDensity = 0.476448; // fuzzed, old value = 0.474664
	FUZZ s.utils.TestPlusDensity = 0.400710; // fuzzed, old value = 0.410279
	FUZZ s.utils.TestPlusSq = 0.433178; // fuzzed, old value = 0.428529
	FUZZ s.utils.TestMinusRatio = 0.377853; // fuzzed, old value = 0.373873
	FUZZ s.utils.TestMinusDensity = 0.603671; // fuzzed, old value = 0.621663
	FUZZ s.utils.TestMinusHeightFactor = 0.790771; // fuzzed, old value = 0.823575

	FUZZ s.separator.hu_1_1 = 0.202631; // fuzzed, old value = 0.206236
	FUZZ s.separator.hu_1_2 = 0.082376; // fuzzed, old value = 0.082857
	FUZZ s.separator.hu_0_1 = 0.254429; // fuzzed, old value = 0.247124
	FUZZ s.separator.hu_1_3 = 0.086610; // fuzzed, old value = 0.083077
	FUZZ s.separator.hu_0_2 = 0.254119; // fuzzed, old value = 0.252649
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.521925; // fuzzed, old value = 0.526091
	FUZZ s.separator.capHeightMax = 1.456631; // fuzzed, old value = 1.462641
	FUZZ s.separator.gdConst = 1.481872; // fuzzed, old value = 1.508315
	FUZZ s.separator.SurfCoef = 2.856586; // fuzzed, old value = 2.967974
	FUZZ s.separator.capHeightRatio = 0.240552; // fuzzed, old value = 0.252671
	FUZZ s.separator.capHeightRatio2 = 1.880725; // fuzzed, old value = 1.883936
	FUZZ s.separator.getRatio1 = 0.884586; // fuzzed, old value = 0.927556
	FUZZ s.separator.getRatio2 = 1.095497; // fuzzed, old value = 1.055364
	FUZZ s.separator.testSlashLine1 = 2.972579; // fuzzed, old value = 3.019029
	FUZZ s.separator.testSlashLine2 = 2.960105; // fuzzed, old value = 2.839300
	FUZZ s.separator.minDensity = 0.213319; // fuzzed, old value = 0.205953
	FUZZ s.separator.maxDensity = 0.891239; // fuzzed, old value = 0.869689
	FUZZ s.separator.extCapHeightMin = 0.297519; // fuzzed, old value = 0.299702
	FUZZ s.separator.extCapHeightMax = 2.015420; // fuzzed, old value = 1.993425
	FUZZ s.separator.extRatioMin = 0.268058; // fuzzed, old value = 0.279701
	FUZZ s.separator.extRatioMax = 1.386231; // fuzzed, old value = 1.454048
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.480650; // fuzzed, old value = 0.458077
	FUZZ s.labels.weightUnderline = 0.309821; // fuzzed, old value = 0.295327
	FUZZ s.labels.ratioBase = 0.835451; // fuzzed, old value = 0.850364
	FUZZ s.labels.ratioWeight = 0.290683; // fuzzed, old value = 0.281577
	FUZZ s.labels.adjustDec = 1.283240; // fuzzed, old value = 1.236935
	FUZZ s.labels.adjustInc = 0.823409; // fuzzed, old value = 0.828826
	FUZZ s.labels.sameLineEps = 0.124217; // fuzzed, old value = 0.130081
	FUZZ s.labels.heightRatio = 0.785186; // fuzzed, old value = 0.784089
	FUZZ s.labels.medHeightFactor = 0.451621; // fuzzed, old value = 0.469961
	FUZZ s.labels.capHeightError = 0.531481; // fuzzed, old value = 0.553314

	FUZZ s.lcomb.MaximalSymbolDistance = 2.562948; // fuzzed, old value = 2.695199
	FUZZ s.lcomb.TestSlashLineEps = 3.055779; // fuzzed, old value = 3.084827
	FUZZ s.lcomb.TestMinHeightFactor = 0.482815; // fuzzed, old value = 0.505587
	FUZZ s.lcomb.TestMaxHeightFactor = 1.183110; // fuzzed, old value = 1.166178
	FUZZ s.lcomb.RectHeightRatio = 0.506928; // fuzzed, old value = 0.497129
	FUZZ s.lcomb.H1SuperscriptSpace = 1.124392; // fuzzed, old value = 1.151222
	FUZZ s.lcomb.H2LowercaseSpace = 0.509743; // fuzzed, old value = 0.527924
	FUZZ s.lcomb.H3LowercaseSpace = 0.513256; // fuzzed, old value = 0.494933
	FUZZ s.lcomb.H4SubscriptSpace = 0.542061; // fuzzed, old value = 0.538893
	FUZZ s.lcomb.FillLabelFactor1 = 0.492518; // fuzzed, old value = 0.488917
	FUZZ s.lcomb.FillLabelFactor2 = 0.496152; // fuzzed, old value = 0.519302
}

