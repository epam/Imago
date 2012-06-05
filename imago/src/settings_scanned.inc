
void updateSettingsScanned(Settings &s)
{
	FUZZ s.general.UseProbablistics = false; // fuzzed, old value = false

	FUZZ s.separator.ext2charRatio = 1.801949; // fuzzed, old value = 1.844019

	FUZZ s.molecule.LengthFactor_long = 0.335862; // fuzzed, old value = 0.325770
	FUZZ s.molecule.LengthFactor_medium = 0.389189; // fuzzed, old value = 0.372015
	FUZZ s.molecule.LengthFactor_default = 0.465457; // fuzzed, old value = 0.445776
	FUZZ s.molecule.LengthValue_long = 112.933161; // fuzzed, old value = 107.557580
	FUZZ s.molecule.LengthValue_medium = 83.114573; // fuzzed, old value = 83.795200
	FUZZ s.molecule.SpaceMultiply = 1.361398; // fuzzed, old value = 1.415498
	FUZZ s.molecule.AngleTreshold = 0.264694; // fuzzed, old value = 0.266317
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.945373; // fuzzed, old value = 17.780515
	FUZZ s.estimation.LineThickness = 6.763095; // fuzzed, old value = 6.598500
	FUZZ s.estimation.AvgBondLength = 29.843751; // fuzzed, old value = 30.785777
	FUZZ s.estimation.AddVertexEps = 4.710084; // fuzzed, old value = 4.957394
	FUZZ s.estimation.MaxSymRatio = 1.215313; // fuzzed, old value = 1.178012
	FUZZ s.estimation.MinSymRatio = 0.310935; // fuzzed, old value = 0.321194
	FUZZ s.estimation.ParLinesEps = 0.572737; // fuzzed, old value = 0.567387
	FUZZ s.estimation.SymHeightErr = 26.815725; // fuzzed, old value = 26.747686
	FUZZ s.estimation.CapitalHeightError = 0.837840; // fuzzed, old value = 0.825556
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.377078; // fuzzed, old value = 0.385587
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 108; // fuzzed, old value = 112
	FUZZ s.mbond.LongErr = 0.327663; // fuzzed, old value = 0.343127
	FUZZ s.mbond.MediumBond = 83; // fuzzed, old value = 82
	FUZZ s.mbond.MediumErr = 0.450931; // fuzzed, old value = 0.452962
	FUZZ s.mbond.DefaultErr = 0.655651; // fuzzed, old value = 0.689375
	FUZZ s.mbond.ParBondsEps = 0.354030; // fuzzed, old value = 0.352178
	FUZZ s.mbond.DoubleRatioTresh = 6.471163; // fuzzed, old value = 6.315967
	FUZZ s.mbond.DoubleCoef = 0.078614; // fuzzed, old value = 0.075761
	FUZZ s.mbond.DoubleMagic1 = 0.891524; // fuzzed, old value = 0.904452
	FUZZ s.mbond.DoubleMagic2 = 0.928943; // fuzzed, old value = 0.903106
	FUZZ s.mbond.DoubleTreshMin = 0.099657; // fuzzed, old value = 0.095658
	FUZZ s.mbond.DoubleTreshMax = 0.803022; // fuzzed, old value = 0.789355
	FUZZ s.mbond.MaxLen1 = 153.667882; // fuzzed, old value = 157.904020
	FUZZ s.mbond.MaxLen2 = 139.066632; // fuzzed, old value = 135.630039
	FUZZ s.mbond.MaxLen3 = 110.001959; // fuzzed, old value = 114.728601
	FUZZ s.mbond.MaxLen4 = 126.194351; // fuzzed, old value = 127.339423
	FUZZ s.mbond.MaxLen5 = 80.040507; // fuzzed, old value = 77.026965
	FUZZ s.mbond.MinLen1 = 88.318249; // fuzzed, old value = 89.843982
	FUZZ s.mbond.MinLen2 = 72.751407; // fuzzed, old value = 75.049951
	FUZZ s.mbond.mbe1 = 0.075620; // fuzzed, old value = 0.078946
	FUZZ s.mbond.mbe2 = 0.157523; // fuzzed, old value = 0.158379
	FUZZ s.mbond.mbe3 = 0.194205; // fuzzed, old value = 0.195539
	FUZZ s.mbond.mbe4 = 0.170373; // fuzzed, old value = 0.174750
	FUZZ s.mbond.mbe5 = 0.155364; // fuzzed, old value = 0.150039
	FUZZ s.mbond.mbe6 = 0.216894; // fuzzed, old value = 0.223369
	FUZZ s.mbond.mbe7 = 0.378093; // fuzzed, old value = 0.394304
	FUZZ s.mbond.mbe_def = 0.542036; // fuzzed, old value = 0.529134
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.349551; // fuzzed, old value = 0.366719
	FUZZ s.mbond.DoubleRightLengthTresh = 0.299133; // fuzzed, old value = 0.298243
	FUZZ s.mbond.TripleLeftLengthTresh = 0.235897; // fuzzed, old value = 0.246036
	FUZZ s.mbond.TripleRightLengthTresh = 0.228166; // fuzzed, old value = 0.231797
	FUZZ s.mbond.Case1LengthTresh = 89.931276; // fuzzed, old value = 94.348981
	FUZZ s.mbond.Case1Factor = 0.370707; // fuzzed, old value = 0.375548
	FUZZ s.mbond.Case2LengthTresh = 84.293508; // fuzzed, old value = 85.735338
	FUZZ s.mbond.Case2Factor = 0.688291; // fuzzed, old value = 0.692787
	FUZZ s.mbond.Case3Factor = 1.015964; // fuzzed, old value = 0.976425
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.104889; // fuzzed, old value = 0.105426
	FUZZ s.skeleton.BaseSmallErr = 0.159795; // fuzzed, old value = 0.158554
	FUZZ s.skeleton.ShortBondLen = 21; // fuzzed, old value = 21
	FUZZ s.skeleton.ShortMul = 0.330679; // fuzzed, old value = 0.340184
	FUZZ s.skeleton.MediumBondLen = 87; // fuzzed, old value = 90
	FUZZ s.skeleton.MediumMul = 0.170096; // fuzzed, old value = 0.166588
	FUZZ s.skeleton.MediumSmallErr = 0.129541; // fuzzed, old value = 0.134749
	FUZZ s.skeleton.LongBondLen = 99; // fuzzed, old value = 97
	FUZZ s.skeleton.LongMul = 0.140841; // fuzzed, old value = 0.144725
	FUZZ s.skeleton.LongSmallErr = 0.063159; // fuzzed, old value = 0.065124
	FUZZ s.skeleton.BrokenRepairFactor = 3.381710; // fuzzed, old value = 3.279799
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.972795; // fuzzed, old value = 0.935507
	FUZZ s.skeleton.BrokenRepairCoef2 = 3.071458; // fuzzed, old value = 2.933075
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.214970; // fuzzed, old value = 0.206637
	FUZZ s.skeleton.DissolveMinErr = 0.172985; // fuzzed, old value = 0.170083
	FUZZ s.skeleton.ConnectBlockS = 9.835867; // fuzzed, old value = 10.205617
	FUZZ s.skeleton.ConnectFactor = 2.043158; // fuzzed, old value = 2.029947
	FUZZ s.skeleton.JoinVerticiesConst = 0.103958; // fuzzed, old value = 0.100070
	FUZZ s.skeleton.DissolveConst = 0.095547; // fuzzed, old value = 0.097222
	FUZZ s.skeleton.Dissolve2Const = 0.190304; // fuzzed, old value = 0.188352
	FUZZ s.skeleton.Join2Const = 0.265372; // fuzzed, old value = 0.278459
	FUZZ s.skeleton.Join3Const = 0.180264; // fuzzed, old value = 0.182380
	FUZZ s.skeleton.DistTreshLimFactor = 2.077342; // fuzzed, old value = 2.029662
	FUZZ s.skeleton.SlopeFact1 = 0.091046; // fuzzed, old value = 0.095759
	FUZZ s.skeleton.SlopeFact2 = 0.164744; // fuzzed, old value = 0.173057
	FUZZ s.skeleton.ShrinkEps = 0.139524; // fuzzed, old value = 0.138586
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	
	FUZZ s.routines.Circle_GapRadiusMax = 1.064082; // fuzzed, old value = 1.020928
	FUZZ s.routines.Circle_GapAngleMax = 0.199859; // fuzzed, old value = 0.197631
	FUZZ s.routines.Circle_MinRadius = 6.872153; // fuzzed, old value = 7.0
	FUZZ s.routines.Circle_MaxDeviation = 0.010489; // fuzzed, old value = 0.010001
	FUZZ s.routines.Circle_AsCharFactor = 1.081005; // fuzzed, old value = 1.05

	FUZZ s.routines.Algebra_IntersectionEps = 0.011607; // fuzzed, old value = 0.011165
	FUZZ s.routines.Algebra_SameLineEps = 0.225538; // fuzzed, old value = 0.223550
	FUZZ s.routines.Approx_Eps1 = 1.134037; // fuzzed, old value = 1.151786
	FUZZ s.routines.Approx_Eps2 = 0.836914; // fuzzed, old value = 0.828235
	FUZZ s.routines.Approx_CalcLineTresh = 0.929779; // fuzzed, old value = 0.919022
	FUZZ s.routines.Contour_Eps1 = 0.962720; // fuzzed, old value = 0.955250
	FUZZ s.routines.Contour_Eps2 = 0.672058; // fuzzed, old value = 0.699570

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.580276; // fuzzed, old value = 2.626996
	FUZZ s.wbe.SingleDownAngleMax = 42.926033; // fuzzed, old value = 43.894630
	FUZZ s.wbe.SingleDownDistancesMax = 10.174664; // fuzzed, old value = 9.878713
	FUZZ s.wbe.SingleDownLengthMax = 49.781544; // fuzzed, old value = 48.034367
	FUZZ s.wbe.SingleUpRatioEps = 1.633464; // fuzzed, old value = 1.571272
	FUZZ s.wbe.SingleUpDefCoeff = 0.270767; // fuzzed, old value = 0.275489
	FUZZ s.wbe.SingleUpIncCoeff = 0.484214; // fuzzed, old value = 0.492325
	FUZZ s.wbe.SingleUpIncLengthTresh = 35.761314; // fuzzed, old value = 36.776896
	FUZZ s.wbe.SingleUpInterpolateEps = 0.066089; // fuzzed, old value = 0.063786
	FUZZ s.wbe.SingleUpMagicAddition = 0.248928; // fuzzed, old value = 0.250076
	FUZZ s.wbe.SingleUpS2Divisor = 1.426453; // fuzzed, old value = 1.437891
	FUZZ s.wbe.SingleUpMinATresh = 1.680023; // fuzzed, old value = 1.767134
	FUZZ s.wbe.SingleUpSquareRatio = 0.629596; // fuzzed, old value = 0.654213
	FUZZ s.wbe.SingleUpAngleTresh = 0.068342; // fuzzed, old value = 0.067372
	FUZZ s.wbe.SomeTresh = 0.102460; // fuzzed, old value = 0.102724
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = false
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 0.992208; // fuzzed, old value = 0.979192
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.091860; // fuzzed, old value = 1.140911
	FUZZ s.characters.WriteEasyFactor = 0.978938; // fuzzed, old value = 0.965983
	FUZZ s.characters.WriteVeryEasyFactor = 0.946090; // fuzzed, old value = 0.935621
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.200350; // fuzzed, old value = 3.319964
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.068206; // fuzzed, old value = 3.078508
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.100781; // fuzzed, old value = 0.098097
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.553011; // fuzzed, old value = 2.561254
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.849573; // fuzzed, old value = 3.809630
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.957791; // fuzzed, old value = 0.926533
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.295325; // fuzzed, old value = 0.286662
	FUZZ s.characters.HW_Line = 1.517041; // fuzzed, old value = 1.495987
	FUZZ s.characters.HW_F = 3.372959; // fuzzed, old value = 3.453994
	FUZZ s.characters.HW_Tricky = 3.054108; // fuzzed, old value = 3.068666
	FUZZ s.characters.HW_Hard = 4.319891; // fuzzed, old value = 4.209693
	FUZZ s.characters.HW_Other = 3.555703; // fuzzed, old value = 3.534641

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.512755; // fuzzed, old value = 0.513915
	FUZZ s.csr.DeleteBadTriangles = 1.964928; // fuzzed, old value = 1.902779
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.762646; // fuzzed, old value = 1.704608

	FUZZ s.graph.MinimalDistTresh = 1.961281; // fuzzed, old value = 2.029322
	FUZZ s.graph.RatioSub = 0.986495; // fuzzed, old value = 0.999274
	FUZZ s.graph.RatioTresh = 0.464300; // fuzzed, old value = 0.450309

	FUZZ s.utils.SlashLineDensity = 0.376036; // fuzzed, old value = 0.395425
	FUZZ s.utils.TestPlusDensity = 0.443502; // fuzzed, old value = 0.453565
	FUZZ s.utils.TestPlusSq = 0.430330; // fuzzed, old value = 0.446065
	FUZZ s.utils.TestMinusRatio = 0.328968; // fuzzed, old value = 0.339020
	FUZZ s.utils.TestMinusDensity = 0.608755; // fuzzed, old value = 0.609794
	FUZZ s.utils.TestMinusHeightFactor = 0.861454; // fuzzed, old value = 0.862917

	FUZZ s.separator.hu_1_1 = 0.222657; // fuzzed, old value = 0.213720
	FUZZ s.separator.hu_1_2 = 0.083639; // fuzzed, old value = 0.080000
	FUZZ s.separator.hu_0_1 = 0.210165; // fuzzed, old value = 0.212832
	FUZZ s.separator.hu_1_3 = 0.089135; // fuzzed, old value = 0.090430
	FUZZ s.separator.hu_0_2 = 0.214314; // fuzzed, old value = 0.210287
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.533280; // fuzzed, old value = 0.530980
	FUZZ s.separator.capHeightMax = 1.468531; // fuzzed, old value = 1.415177
	FUZZ s.separator.gdConst = 1.594182; // fuzzed, old value = 1.614444
	FUZZ s.separator.SurfCoef = 3.175393; // fuzzed, old value = 3.149856
	FUZZ s.separator.capHeightRatio = 0.276716; // fuzzed, old value = 0.269188
	FUZZ s.separator.capHeightRatio2 = 1.963837; // fuzzed, old value = 1.967274
	FUZZ s.separator.getRatio1 = 1.029899; // fuzzed, old value = 1.007940
	FUZZ s.separator.getRatio2 = 1.239054; // fuzzed, old value = 1.207576
	FUZZ s.separator.testSlashLine1 = 3.062637; // fuzzed, old value = 3.049334
	FUZZ s.separator.testSlashLine2 = 2.571696; // fuzzed, old value = 2.574961
	FUZZ s.separator.minDensity = 0.191277; // fuzzed, old value = 0.197233
	FUZZ s.separator.maxDensity = 0.919266; // fuzzed, old value = 0.902829
	FUZZ s.separator.extCapHeightMin = 0.293890; // fuzzed, old value = 0.304347
	FUZZ s.separator.extCapHeightMax = 2.101175; // fuzzed, old value = 2.182021
	FUZZ s.separator.extRatioMin = 0.337869; // fuzzed, old value = 0.321910
	FUZZ s.separator.extRatioMax = 1.529181; // fuzzed, old value = 1.511297
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = false; // fuzzed, old value = false

	FUZZ s.labels.underlinePos = 0.391654; // fuzzed, old value = 0.387511
	FUZZ s.labels.weightUnderline = 0.276944; // fuzzed, old value = 0.280123
	FUZZ s.labels.ratioBase = 0.756460; // fuzzed, old value = 0.790043
	FUZZ s.labels.ratioWeight = 0.284394; // fuzzed, old value = 0.276040
	FUZZ s.labels.adjustDec = 1.253712; // fuzzed, old value = 1.303607
	FUZZ s.labels.adjustInc = 0.775452; // fuzzed, old value = 0.771535
	FUZZ s.labels.sameLineEps = 0.110600; // fuzzed, old value = 0.116347
	FUZZ s.labels.heightRatio = 0.744500; // fuzzed, old value = 0.766878
	FUZZ s.labels.medHeightFactor = 0.540594; // fuzzed, old value = 0.520234
	FUZZ s.labels.capHeightError = 0.495467; // fuzzed, old value = 0.495840

	FUZZ s.lcomb.MaximalSymbolDistance = 2.797372; // fuzzed, old value = 2.747865
	FUZZ s.lcomb.TestSlashLineEps = 3.539937; // fuzzed, old value = 3.431774
	FUZZ s.lcomb.TestMinHeightFactor = 0.596755; // fuzzed, old value = 0.579268
	FUZZ s.lcomb.TestMaxHeightFactor = 1.106172; // fuzzed, old value = 1.083503
	FUZZ s.lcomb.RectHeightRatio = 0.476973; // fuzzed, old value = 0.465003
	FUZZ s.lcomb.H1SuperscriptSpace = 1.048816; // fuzzed, old value = 1.029819
	FUZZ s.lcomb.H2LowercaseSpace = 0.451700; // fuzzed, old value = 0.473407
	FUZZ s.lcomb.H3LowercaseSpace = 0.453821; // fuzzed, old value = 0.432355
	FUZZ s.lcomb.H4SubscriptSpace = 0.504323; // fuzzed, old value = 0.518284
	FUZZ s.lcomb.FillLabelFactor1 = 0.504135; // fuzzed, old value = 0.519768
	FUZZ s.lcomb.FillLabelFactor2 = 0.554126; // fuzzed, old value = 0.534072

	FUZZ s.p_estimator.DefaultApriority = 0.515750; // fuzzed, old value = 0.5
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.795885; // fuzzed, old value = 0.8
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.253013; // fuzzed, old value = 0.25
	FUZZ s.p_estimator.LogisticScale = 0.959909; // fuzzed, old value = 1.0
	FUZZ s.p_estimator.LogisticLocation = 1.004289; // fuzzed, old value = 1.0
}
