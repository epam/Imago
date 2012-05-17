
void updateSettingsHandwritten(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.316981; // fuzzed, old value = 0.310291
	FUZZ s.molecule.LengthFactor_medium = 0.426186; // fuzzed, old value = 0.425901
	FUZZ s.molecule.LengthFactor_default = 0.481170; // fuzzed, old value = 0.487716
	FUZZ s.molecule.LengthValue_long = 103.962175; // fuzzed, old value = 105.474833
	FUZZ s.molecule.LengthValue_medium = 84.220093; // fuzzed, old value = 83.108601
	FUZZ s.molecule.SpaceMultiply = 1.462494; // fuzzed, old value = 1.471014
	FUZZ s.molecule.AngleTreshold = 0.252597; // fuzzed, old value = 0.248073
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.0;
	FUZZ s.estimation.LineThickness = 6.0;
	FUZZ s.estimation.AvgBondLength = 30.0;
	FUZZ s.estimation.AddVertexEps = 5.171899; // fuzzed, old value = 5.2
	FUZZ s.estimation.MaxSymRatio = 1.073283; // fuzzed, old value = 1.077193
	FUZZ s.estimation.MinSymRatio = 0.332828; // fuzzed, old value = 0.34
	FUZZ s.estimation.ParLinesEps = 0.512849; // fuzzed, old value = 0.513493
	FUZZ s.estimation.SymHeightErr = 28.737111; // fuzzed, old value = 28.206860
	FUZZ s.estimation.CapitalHeightError = 0.849315; // fuzzed, old value = 0.85
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.510033; // fuzzed, old value = 0.5
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 119; // fuzzed, old value = 118
	FUZZ s.mbond.LongErr = 0.362768; // fuzzed, old value = 0.356396
	FUZZ s.mbond.MediumBond = 90; // fuzzed, old value = 90
	FUZZ s.mbond.MediumErr = 0.392199; // fuzzed, old value = 0.387344
	FUZZ s.mbond.DefaultErr = 0.635246; // fuzzed, old value = 0.637428
	FUZZ s.mbond.ParBondsEps = 0.336346; // fuzzed, old value = 0.333194
	FUZZ s.mbond.DoubleRatioTresh = 7.338240; // fuzzed, old value = 7.273803
	FUZZ s.mbond.DoubleCoef = 0.082408; // fuzzed, old value = 0.080612
	FUZZ s.mbond.DoubleMagic1 = 0.946310; // fuzzed, old value = 0.951135
	FUZZ s.mbond.DoubleMagic2 = 1.015646; // fuzzed, old value = 0.995650
	FUZZ s.mbond.DoubleTreshMin = 0.100697; // fuzzed, old value = 0.101219
	FUZZ s.mbond.DoubleTreshMax = 0.882991; // fuzzed, old value = 0.877551
	FUZZ s.mbond.MaxLen1 = 164.156731; // fuzzed, old value = 167.283046
	FUZZ s.mbond.MaxLen2 = 122.830393; // fuzzed, old value = 122.202449
	FUZZ s.mbond.MaxLen3 = 109.414501; // fuzzed, old value = 111.537811
	FUZZ s.mbond.MaxLen4 = 109.194680; // fuzzed, old value = 108.957840
	FUZZ s.mbond.MaxLen5 = 85.838948; // fuzzed, old value = 86.211570
	FUZZ s.mbond.MinLen1 = 86.382026; // fuzzed, old value = 85.596967
	FUZZ s.mbond.MinLen2 = 76.351772; // fuzzed, old value = 75.189012
	FUZZ s.mbond.mbe1 = 0.082278; // fuzzed, old value = 0.082698
	FUZZ s.mbond.mbe2 = 0.152398; // fuzzed, old value = 0.149319
	FUZZ s.mbond.mbe3 = 0.200465; // fuzzed, old value = 0.200630
	FUZZ s.mbond.mbe4 = 0.184519; // fuzzed, old value = 0.188662
	FUZZ s.mbond.mbe5 = 0.158265; // fuzzed, old value = 0.161782
	FUZZ s.mbond.mbe6 = 0.209079; // fuzzed, old value = 0.208906
	FUZZ s.mbond.mbe7 = 0.391566; // fuzzed, old value = 0.396539
	FUZZ s.mbond.mbe_def = 0.519814; // fuzzed, old value = 0.510852
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.330903; // fuzzed, old value = 0.323348
	FUZZ s.mbond.DoubleRightLengthTresh = 0.310036; // fuzzed, old value = 0.311682
	FUZZ s.mbond.TripleLeftLengthTresh = 0.255772; // fuzzed, old value = 0.253714
	FUZZ s.mbond.TripleRightLengthTresh = 0.228044; // fuzzed, old value = 0.232986
	FUZZ s.mbond.Case1LengthTresh = 102.074306; // fuzzed, old value = 104.213876
	FUZZ s.mbond.Case1Factor = 0.438170; // fuzzed, old value = 0.447831
	FUZZ s.mbond.Case2LengthTresh = 78.284797; // fuzzed, old value = 79.384028
	FUZZ s.mbond.Case2Factor = 0.699134; // fuzzed, old value = 0.698154
	FUZZ s.mbond.Case3Factor = 0.912423; // fuzzed, old value = 0.904546
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.095546; // fuzzed, old value = 0.096488
	FUZZ s.skeleton.BaseSmallErr = 0.151619; // fuzzed, old value = 0.150201
	FUZZ s.skeleton.ShortBondLen = 21; // fuzzed, old value = 21
	FUZZ s.skeleton.ShortMul = 0.311016; // fuzzed, old value = 0.307241
	FUZZ s.skeleton.MediumBondLen = 84; // fuzzed, old value = 85
	FUZZ s.skeleton.MediumMul = 0.175004; // fuzzed, old value = 0.177298
	FUZZ s.skeleton.MediumSmallErr = 0.139131; // fuzzed, old value = 0.137212
	FUZZ s.skeleton.LongBondLen = 102; // fuzzed, old value = 104
	FUZZ s.skeleton.LongMul = 0.149453; // fuzzed, old value = 0.151405
	FUZZ s.skeleton.LongSmallErr = 0.062468; // fuzzed, old value = 0.063768
	FUZZ s.skeleton.BrokenRepairFactor = 2.958580; // fuzzed, old value = 2.965542
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.969769; // fuzzed, old value = 0.960452
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.674973; // fuzzed, old value = 2.697598
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.204331; // fuzzed, old value = 0.200919
	FUZZ s.skeleton.DissolveMinErr = 0.173591; // fuzzed, old value = 0.177721
	FUZZ s.skeleton.ConnectBlockS = 10.342266; // fuzzed, old value = 10.167484
	FUZZ s.skeleton.ConnectFactor = 1.996873; // fuzzed, old value = 2.039006
	FUZZ s.skeleton.JoinVerticiesConst = 0.099156; // fuzzed, old value = 0.100225
	FUZZ s.skeleton.DissolveConst = 0.097573; // fuzzed, old value = 0.097109
	FUZZ s.skeleton.Dissolve2Const = 0.200409; // fuzzed, old value = 0.201833
	FUZZ s.skeleton.Join2Const = 0.340481; // fuzzed, old value = 0.344747
	FUZZ s.skeleton.Join3Const = 0.188169; // fuzzed, old value = 0.185757
	FUZZ s.skeleton.DistTreshLimFactor = 2.006374; // fuzzed, old value = 1.961816
	FUZZ s.skeleton.SlopeFact1 = 0.099698; // fuzzed, old value = 0.097837
	FUZZ s.skeleton.SlopeFact2 = 0.193475; // fuzzed, old value = 0.197422
	FUZZ s.skeleton.ShrinkEps = 0.124536; // fuzzed, old value = 0.125378
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.096100; // fuzzed, old value = 0.096720
	FUZZ s.routines.Circle_GapMax = 0.925721; // fuzzed, old value = 0.948295
	FUZZ s.routines.Circle_RMax = 2.025760; // fuzzed, old value = 2.070044
	FUZZ s.routines.Circle_AvgRadius = 0.000109; // fuzzed, old value = 0.000107
	FUZZ s.routines.Circle_MaxRatio = 0.321018; // fuzzed, old value = 0.320620
	FUZZ s.routines.Algebra_IntersectionEps = 0.010066; // fuzzed, old value = 0.010024
	FUZZ s.routines.Algebra_SameLineEps = 0.211599; // fuzzed, old value = 0.213441
	FUZZ s.routines.Approx_Eps1 = 1.167437; // fuzzed, old value = 1.172875
	FUZZ s.routines.Approx_Eps2 = 0.888855; // fuzzed, old value = 0.888022
	FUZZ s.routines.Approx_CalcLineTresh = 0.910098; // fuzzed, old value = 0.896885

	FUZZ s.weak_seg.SubpixelDraw = 0.5;
	FUZZ s.weak_seg.RectangularCropAreaTreshold = 0.300326; // fuzzed, old value = 0.303089
	FUZZ s.weak_seg.RectangularCropFitTreshold = 1.067597; // fuzzed, old value = 1.047984
	FUZZ s.weak_seg.RefineWidth = 0.867841; // fuzzed, old value = 0.878408
	FUZZ s.weak_seg.MinDistanceDraw = 1.378518; // fuzzed, old value = 1.359330

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.967701; // fuzzed, old value = 2.986749
	FUZZ s.wbe.SingleDownAngleMax = 44.790036; // fuzzed, old value = 44.686832
	FUZZ s.wbe.SingleDownDistancesMax = 9.483096; // fuzzed, old value = 9.723407
	FUZZ s.wbe.SingleDownLengthMax = 43.273222; // fuzzed, old value = 43.390249
	FUZZ s.wbe.SingleUpRatioEps = 1.852297; // fuzzed, old value = 1.817359
	FUZZ s.wbe.SingleUpDefCoeff = 0.271484; // fuzzed, old value = 0.276434
	FUZZ s.wbe.SingleUpIncCoeff = 0.422746; // fuzzed, old value = 0.420674
	FUZZ s.wbe.SingleUpIncLengthTresh = 35.707890; // fuzzed, old value = 36.248318
	FUZZ s.wbe.SingleUpInterpolateEps = 0.061760; // fuzzed, old value = 0.060273
	FUZZ s.wbe.SingleUpMagicAddition = 0.223457; // fuzzed, old value = 0.220682
	FUZZ s.wbe.SingleUpS2Divisor = 1.674376; // fuzzed, old value = 1.652226
	FUZZ s.wbe.SingleUpMinATresh = 1.713060; // fuzzed, old value = 1.732313
	FUZZ s.wbe.SingleUpSquareRatio = 0.643772; // fuzzed, old value = 0.651217
	FUZZ s.wbe.SingleUpAngleTresh = 0.067078; // fuzzed, old value = 0.066675
	FUZZ s.wbe.SomeTresh = 0.096287; // fuzzed, old value = 0.096837
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = false
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.083217; // fuzzed, old value = 1.059999
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.173916; // fuzzed, old value = 1.172434
	FUZZ s.characters.WriteEasyFactor = 0.927424; // fuzzed, old value = 0.915540
	FUZZ s.characters.WriteVeryEasyFactor = 0.838911; // fuzzed, old value = 0.840880
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 2.947747; // fuzzed, old value = 2.979810
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.417408; // fuzzed, old value = 3.471420
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.098672; // fuzzed, old value = 0.100693
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.525097; // fuzzed, old value = 2.509563
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.674343; // fuzzed, old value = 3.688597
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.985313; // fuzzed, old value = 0.961806
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.299341; // fuzzed, old value = 0.297176
	FUZZ s.characters.HW_Line = 1.652416; // fuzzed, old value = 1.662506
	FUZZ s.characters.HW_F = 3.195723; // fuzzed, old value = 3.234215
	FUZZ s.characters.HW_Tricky = 2.636925; // fuzzed, old value = 2.665344
	FUZZ s.characters.HW_Hard = 4.313760; // fuzzed, old value = 4.224281
	FUZZ s.characters.HW_Other = 3.627372; // fuzzed, old value = 3.687904

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.514321; // fuzzed, old value = 0.506744
	FUZZ s.csr.DeleteBadTriangles = 1.966536; // fuzzed, old value = 1.922332
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.531569; // fuzzed, old value = 1.570169

	FUZZ s.graph.MinimalDistTresh = 2.004029; // fuzzed, old value = 1.977390
	FUZZ s.graph.RatioSub = 0.984608; // fuzzed, old value = 0.974303
	FUZZ s.graph.RatioTresh = 0.412152; // fuzzed, old value = 0.404344

	FUZZ s.utils.SlashLineDensity = 0.474664; // fuzzed, old value = 0.472121
	FUZZ s.utils.TestPlusDensity = 0.410279; // fuzzed, old value = 0.407646
	FUZZ s.utils.TestPlusSq = 0.428529; // fuzzed, old value = 0.418509
	FUZZ s.utils.TestMinusRatio = 0.373873; // fuzzed, old value = 0.381624
	FUZZ s.utils.TestMinusDensity = 0.621663; // fuzzed, old value = 0.620425
	FUZZ s.utils.TestMinusHeightFactor = 0.823575; // fuzzed, old value = 0.824377

	FUZZ s.separator.hu_1_1 = 0.206236; // fuzzed, old value = 0.206212
	FUZZ s.separator.hu_1_2 = 0.082857; // fuzzed, old value = 0.081201
	FUZZ s.separator.hu_0_1 = 0.247124; // fuzzed, old value = 0.244022
	FUZZ s.separator.hu_1_3 = 0.083077; // fuzzed, old value = 0.083327
	FUZZ s.separator.hu_0_2 = 0.252649; // fuzzed, old value = 0.246898
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.526091; // fuzzed, old value = 0.523632
	FUZZ s.separator.capHeightMax = 1.462641; // fuzzed, old value = 1.489373
	FUZZ s.separator.gdConst = 1.508315; // fuzzed, old value = 1.488979
	FUZZ s.separator.SurfCoef = 2.967974; // fuzzed, old value = 2.950396
	FUZZ s.separator.capHeightRatio = 0.252671; // fuzzed, old value = 0.247625
	FUZZ s.separator.capHeightRatio2 = 1.883936; // fuzzed, old value = 1.846762
	FUZZ s.separator.getRatio1 = 0.927556; // fuzzed, old value = 0.929616
	FUZZ s.separator.getRatio2 = 1.055364; // fuzzed, old value = 1.064626
	FUZZ s.separator.testSlashLine1 = 3.019029; // fuzzed, old value = 3.065937
	FUZZ s.separator.testSlashLine2 = 2.839300; // fuzzed, old value = 2.846517
	FUZZ s.separator.minDensity = 0.205953; // fuzzed, old value = 0.203749
	FUZZ s.separator.maxDensity = 0.869689; // fuzzed, old value = 0.870391
	FUZZ s.separator.extCapHeightMin = 0.299702; // fuzzed, old value = 0.292781
	FUZZ s.separator.extCapHeightMax = 1.993425; // fuzzed, old value = 2.030029
	FUZZ s.separator.extRatioMin = 0.279701; // fuzzed, old value = 0.283704
	FUZZ s.separator.extRatioMax = 1.454048; // fuzzed, old value = 1.467740
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4;

	FUZZ s.labels.underlinePos = 0.458077; // fuzzed, old value = 0.455822
	FUZZ s.labels.weightUnderline = 0.295327; // fuzzed, old value = 0.298289
	FUZZ s.labels.ratioBase = 0.850364; // fuzzed, old value = 0.836667
	FUZZ s.labels.ratioWeight = 0.281577; // fuzzed, old value = 0.280956
	FUZZ s.labels.adjustDec = 1.236935; // fuzzed, old value = 1.241587
	FUZZ s.labels.adjustInc = 0.828826; // fuzzed, old value = 0.831224
	FUZZ s.labels.sameLineEps = 0.130081; // fuzzed, old value = 0.129109
	FUZZ s.labels.heightRatio = 0.784089; // fuzzed, old value = 0.803107
	FUZZ s.labels.medHeightFactor = 0.469961; // fuzzed, old value = 0.480666
	FUZZ s.labels.capHeightError = 0.553314; // fuzzed, old value = 0.552481

	FUZZ s.lcomb.MaximalSymbolDistance = 2.695199; // fuzzed, old value = 2.669409
	FUZZ s.lcomb.TestSlashLineEps = 3.084827; // fuzzed, old value = 3.010708
	FUZZ s.lcomb.TestMinHeightFactor = 0.505587; // fuzzed, old value = 0.514248
	FUZZ s.lcomb.TestMaxHeightFactor = 1.166178; // fuzzed, old value = 1.176732
	FUZZ s.lcomb.RectHeightRatio = 0.497129; // fuzzed, old value = 0.491839
	FUZZ s.lcomb.H1SuperscriptSpace = 1.151222; // fuzzed, old value = 1.134113
	FUZZ s.lcomb.H2LowercaseSpace = 0.527924; // fuzzed, old value = 0.524777
	FUZZ s.lcomb.H3LowercaseSpace = 0.494933; // fuzzed, old value = 0.488424
	FUZZ s.lcomb.H4SubscriptSpace = 0.538893; // fuzzed, old value = 0.538443
	FUZZ s.lcomb.FillLabelFactor1 = 0.488917; // fuzzed, old value = 0.495971
	FUZZ s.lcomb.FillLabelFactor2 = 0.519302; // fuzzed, old value = 0.526847
}

