
void updateSettingsHighResolution(Settings &s)
{
	FUZZ s.molecule.LengthFactor_long = 0.325504; // fuzzed, old value = 0.316981
	FUZZ s.molecule.LengthFactor_medium = 0.422746; // fuzzed, old value = 0.426186
	FUZZ s.molecule.LengthFactor_default = 0.502907; // fuzzed, old value = 0.481170
	FUZZ s.molecule.LengthValue_long = 100.372344; // fuzzed, old value = 103.962175
	FUZZ s.molecule.LengthValue_medium = 87.508113; // fuzzed, old value = 84.220093
	FUZZ s.molecule.SpaceMultiply = 1.522845; // fuzzed, old value = 1.462494
	FUZZ s.molecule.AngleTreshold = 0.261905; // fuzzed, old value = 0.252597
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.427625; // fuzzed, old value = 16.0
	FUZZ s.estimation.LineThickness = 6.271123; // fuzzed, old value = 6.0
	FUZZ s.estimation.AvgBondLength = 29.187307; // fuzzed, old value = 30.0
	FUZZ s.estimation.AddVertexEps = 5.338316; // fuzzed, old value = 5.171899
	FUZZ s.estimation.MaxSymRatio = 1.075217; // fuzzed, old value = 1.073283
	FUZZ s.estimation.MinSymRatio = 0.324970; // fuzzed, old value = 0.332828
	FUZZ s.estimation.ParLinesEps = 0.500045; // fuzzed, old value = 0.512849
	FUZZ s.estimation.SymHeightErr = 29.986198; // fuzzed, old value = 28.737111
	FUZZ s.estimation.CapitalHeightError = 0.849581; // fuzzed, old value = 0.849315
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.527501; // fuzzed, old value = 0.510033
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 120; // fuzzed, old value = 119
	FUZZ s.mbond.LongErr = 0.379442; // fuzzed, old value = 0.362768
	FUZZ s.mbond.MediumBond = 92; // fuzzed, old value = 90
	FUZZ s.mbond.MediumErr = 0.374411; // fuzzed, old value = 0.392199
	FUZZ s.mbond.DefaultErr = 0.633215; // fuzzed, old value = 0.635246
	FUZZ s.mbond.ParBondsEps = 0.347403; // fuzzed, old value = 0.336346
	FUZZ s.mbond.DoubleRatioTresh = 7.301635; // fuzzed, old value = 7.338240
	FUZZ s.mbond.DoubleCoef = 0.080239; // fuzzed, old value = 0.082408
	FUZZ s.mbond.DoubleMagic1 = 0.912245; // fuzzed, old value = 0.946310
	FUZZ s.mbond.DoubleMagic2 = 1.014773; // fuzzed, old value = 1.015646
	FUZZ s.mbond.DoubleTreshMin = 0.097689; // fuzzed, old value = 0.100697
	FUZZ s.mbond.DoubleTreshMax = 0.877638; // fuzzed, old value = 0.882991
	FUZZ s.mbond.MaxLen1 = 158.294993; // fuzzed, old value = 164.156731
	FUZZ s.mbond.MaxLen2 = 125.479342; // fuzzed, old value = 122.830393
	FUZZ s.mbond.MaxLen3 = 110.907276; // fuzzed, old value = 109.414501
	FUZZ s.mbond.MaxLen4 = 107.998827; // fuzzed, old value = 109.194680
	FUZZ s.mbond.MaxLen5 = 88.239751; // fuzzed, old value = 85.838948
	FUZZ s.mbond.MinLen1 = 86.865383; // fuzzed, old value = 86.382026
	FUZZ s.mbond.MinLen2 = 74.074407; // fuzzed, old value = 76.351772
	FUZZ s.mbond.mbe1 = 0.081638; // fuzzed, old value = 0.082278
	FUZZ s.mbond.mbe2 = 0.153054; // fuzzed, old value = 0.152398
	FUZZ s.mbond.mbe3 = 0.201820; // fuzzed, old value = 0.200465
	FUZZ s.mbond.mbe4 = 0.186926; // fuzzed, old value = 0.184519
	FUZZ s.mbond.mbe5 = 0.160446; // fuzzed, old value = 0.158265
	FUZZ s.mbond.mbe6 = 0.213536; // fuzzed, old value = 0.209079
	FUZZ s.mbond.mbe7 = 0.397030; // fuzzed, old value = 0.391566
	FUZZ s.mbond.mbe_def = 0.523376; // fuzzed, old value = 0.519814
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.336214; // fuzzed, old value = 0.330903
	FUZZ s.mbond.DoubleRightLengthTresh = 0.301899; // fuzzed, old value = 0.310036
	FUZZ s.mbond.TripleLeftLengthTresh = 0.268002; // fuzzed, old value = 0.255772
	FUZZ s.mbond.TripleRightLengthTresh = 0.233726; // fuzzed, old value = 0.228044
	FUZZ s.mbond.Case1LengthTresh = 104.470016; // fuzzed, old value = 102.074306
	FUZZ s.mbond.Case1Factor = 0.440431; // fuzzed, old value = 0.438170
	FUZZ s.mbond.Case2LengthTresh = 76.500471; // fuzzed, old value = 78.284797
	FUZZ s.mbond.Case2Factor = 0.707674; // fuzzed, old value = 0.699134
	FUZZ s.mbond.Case3Factor = 0.908999; // fuzzed, old value = 0.912423
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.095487; // fuzzed, old value = 0.095546
	FUZZ s.skeleton.BaseSmallErr = 0.152690; // fuzzed, old value = 0.151619
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 21
	FUZZ s.skeleton.ShortMul = 0.325208; // fuzzed, old value = 0.311016
	FUZZ s.skeleton.MediumBondLen = 88; // fuzzed, old value = 84
	FUZZ s.skeleton.MediumMul = 0.182107; // fuzzed, old value = 0.175004
	FUZZ s.skeleton.MediumSmallErr = 0.139697; // fuzzed, old value = 0.139131
	FUZZ s.skeleton.LongBondLen = 104; // fuzzed, old value = 102
	FUZZ s.skeleton.LongMul = 0.150157; // fuzzed, old value = 0.149453
	FUZZ s.skeleton.LongSmallErr = 0.060531; // fuzzed, old value = 0.062468
	FUZZ s.skeleton.BrokenRepairFactor = 3.026944; // fuzzed, old value = 2.958580
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.000749; // fuzzed, old value = 0.969769
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.690325; // fuzzed, old value = 2.674973
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.202691; // fuzzed, old value = 0.204331
	FUZZ s.skeleton.DissolveMinErr = 0.179633; // fuzzed, old value = 0.173591
	FUZZ s.skeleton.ConnectBlockS = 10.121119; // fuzzed, old value = 10.342266
	FUZZ s.skeleton.ConnectFactor = 2.095784; // fuzzed, old value = 1.996873
	FUZZ s.skeleton.JoinVerticiesConst = 0.101323; // fuzzed, old value = 0.099156
	FUZZ s.skeleton.DissolveConst = 0.099845; // fuzzed, old value = 0.097573
	FUZZ s.skeleton.Dissolve2Const = 0.199018; // fuzzed, old value = 0.200409
	FUZZ s.skeleton.Join2Const = 0.348574; // fuzzed, old value = 0.340481
	FUZZ s.skeleton.Join3Const = 0.183421; // fuzzed, old value = 0.188169
	FUZZ s.skeleton.DistTreshLimFactor = 1.911499; // fuzzed, old value = 2.006374
	FUZZ s.skeleton.SlopeFact1 = 0.099213; // fuzzed, old value = 0.099698
	FUZZ s.skeleton.SlopeFact2 = 0.189956; // fuzzed, old value = 0.193475
	FUZZ s.skeleton.ShrinkEps = 0.124760; // fuzzed, old value = 0.124536
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	FUZZ s.routines.Circle_Eps = 0.000009; // fuzzed, old value = 0.000009
	FUZZ s.routines.Circle_GapMin = 0.099827; // fuzzed, old value = 0.096100
	FUZZ s.routines.Circle_GapMax = 0.891744; // fuzzed, old value = 0.925721
	FUZZ s.routines.Circle_RMax = 1.976824; // fuzzed, old value = 2.025760
	FUZZ s.routines.Circle_AvgRadius = 0.000108; // fuzzed, old value = 0.000109
	FUZZ s.routines.Circle_MaxRatio = 0.321716; // fuzzed, old value = 0.321018
	FUZZ s.routines.Algebra_IntersectionEps = 0.010061; // fuzzed, old value = 0.010066
	FUZZ s.routines.Algebra_SameLineEps = 0.203622; // fuzzed, old value = 0.211599
	FUZZ s.routines.Approx_Eps1 = 1.194374; // fuzzed, old value = 1.167437
	FUZZ s.routines.Approx_Eps2 = 0.891238; // fuzzed, old value = 0.888855
	FUZZ s.routines.Approx_CalcLineTresh = 0.910738; // fuzzed, old value = 0.910098

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.965677; // fuzzed, old value = 2.967701
	FUZZ s.wbe.SingleDownAngleMax = 44.299925; // fuzzed, old value = 44.790036
	FUZZ s.wbe.SingleDownDistancesMax = 9.848462; // fuzzed, old value = 9.483096
	FUZZ s.wbe.SingleDownLengthMax = 45.311027; // fuzzed, old value = 43.273222
	FUZZ s.wbe.SingleUpRatioEps = 1.780768; // fuzzed, old value = 1.852297
	FUZZ s.wbe.SingleUpDefCoeff = 0.275792; // fuzzed, old value = 0.271484
	FUZZ s.wbe.SingleUpIncCoeff = 0.405128; // fuzzed, old value = 0.422746
	FUZZ s.wbe.SingleUpIncLengthTresh = 34.609693; // fuzzed, old value = 35.707890
	FUZZ s.wbe.SingleUpInterpolateEps = 0.061981; // fuzzed, old value = 0.061760
	FUZZ s.wbe.SingleUpMagicAddition = 0.224210; // fuzzed, old value = 0.223457
	FUZZ s.wbe.SingleUpS2Divisor = 1.730414; // fuzzed, old value = 1.674376
	FUZZ s.wbe.SingleUpMinATresh = 1.698006; // fuzzed, old value = 1.713060
	FUZZ s.wbe.SingleUpSquareRatio = 0.653076; // fuzzed, old value = 0.643772
	FUZZ s.wbe.SingleUpAngleTresh = 0.065977; // fuzzed, old value = 0.067078
	FUZZ s.wbe.SomeTresh = 0.098673; // fuzzed, old value = 0.096287
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = true; // fuzzed, old value = true
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.072382; // fuzzed, old value = 1.083217
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.149205; // fuzzed, old value = 1.173916
	FUZZ s.characters.WriteEasyFactor = 0.940425; // fuzzed, old value = 0.927424
	FUZZ s.characters.WriteVeryEasyFactor = 0.832404; // fuzzed, old value = 0.838911
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 2.959878; // fuzzed, old value = 2.947747
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.356067; // fuzzed, old value = 3.417408
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.099669; // fuzzed, old value = 0.098672
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.556935; // fuzzed, old value = 2.525097
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.595237; // fuzzed, old value = 3.674343
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.995833; // fuzzed, old value = 0.985313
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.306773; // fuzzed, old value = 0.299341
	FUZZ s.characters.HW_Line = 1.651793; // fuzzed, old value = 1.652416
	FUZZ s.characters.HW_F = 3.274989; // fuzzed, old value = 3.195723
	FUZZ s.characters.HW_Tricky = 2.759822; // fuzzed, old value = 2.636925
	FUZZ s.characters.HW_Hard = 4.318216; // fuzzed, old value = 4.313760
	FUZZ s.characters.HW_Other = 3.600776; // fuzzed, old value = 3.627372

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.493647; // fuzzed, old value = 0.514321
	FUZZ s.csr.DeleteBadTriangles = 1.891627; // fuzzed, old value = 1.966536
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.513964; // fuzzed, old value = 1.531569

	FUZZ s.graph.MinimalDistTresh = 2.096127; // fuzzed, old value = 2.004029
	FUZZ s.graph.RatioSub = 0.945973; // fuzzed, old value = 0.984608
	FUZZ s.graph.RatioTresh = 0.413262; // fuzzed, old value = 0.412152

	FUZZ s.utils.SlashLineDensity = 0.486265; // fuzzed, old value = 0.474664
	FUZZ s.utils.TestPlusDensity = 0.429479; // fuzzed, old value = 0.410279
	FUZZ s.utils.TestPlusSq = 0.418347; // fuzzed, old value = 0.428529
	FUZZ s.utils.TestMinusRatio = 0.362805; // fuzzed, old value = 0.373873
	FUZZ s.utils.TestMinusDensity = 0.605758; // fuzzed, old value = 0.621663
	FUZZ s.utils.TestMinusHeightFactor = 0.783296; // fuzzed, old value = 0.823575

	FUZZ s.separator.hu_1_1 = 0.198042; // fuzzed, old value = 0.206236
	FUZZ s.separator.hu_1_2 = 0.086904; // fuzzed, old value = 0.082857
	FUZZ s.separator.hu_0_1 = 0.243071; // fuzzed, old value = 0.247124
	FUZZ s.separator.hu_1_3 = 0.081547; // fuzzed, old value = 0.083077
	FUZZ s.separator.hu_0_2 = 0.257670; // fuzzed, old value = 0.252649
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.536388; // fuzzed, old value = 0.526091
	FUZZ s.separator.capHeightMax = 1.395258; // fuzzed, old value = 1.462641
	FUZZ s.separator.gdConst = 1.512571; // fuzzed, old value = 1.508315
	FUZZ s.separator.SurfCoef = 2.878732; // fuzzed, old value = 2.967974
	FUZZ s.separator.capHeightRatio = 0.244646; // fuzzed, old value = 0.252671
	FUZZ s.separator.capHeightRatio2 = 1.886779; // fuzzed, old value = 1.883936
	FUZZ s.separator.getRatio1 = 0.914414; // fuzzed, old value = 0.927556
	FUZZ s.separator.getRatio2 = 1.081077; // fuzzed, old value = 1.055364
	FUZZ s.separator.testSlashLine1 = 2.875854; // fuzzed, old value = 3.019029
	FUZZ s.separator.testSlashLine2 = 2.928962; // fuzzed, old value = 2.839300
	FUZZ s.separator.minDensity = 0.199450; // fuzzed, old value = 0.205953
	FUZZ s.separator.maxDensity = 0.862675; // fuzzed, old value = 0.869689
	FUZZ s.separator.extCapHeightMin = 0.300420; // fuzzed, old value = 0.299702
	FUZZ s.separator.extCapHeightMax = 2.050456; // fuzzed, old value = 1.993425
	FUZZ s.separator.extRatioMin = 0.286860; // fuzzed, old value = 0.279701
	FUZZ s.separator.extRatioMax = 1.472377; // fuzzed, old value = 1.454048
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.479917; // fuzzed, old value = 0.458077
	FUZZ s.labels.weightUnderline = 0.295936; // fuzzed, old value = 0.295327
	FUZZ s.labels.ratioBase = 0.826168; // fuzzed, old value = 0.850364
	FUZZ s.labels.ratioWeight = 0.293752; // fuzzed, old value = 0.281577
	FUZZ s.labels.adjustDec = 1.241252; // fuzzed, old value = 1.236935
	FUZZ s.labels.adjustInc = 0.828367; // fuzzed, old value = 0.828826
	FUZZ s.labels.sameLineEps = 0.133123; // fuzzed, old value = 0.130081
	FUZZ s.labels.heightRatio = 0.815722; // fuzzed, old value = 0.784089
	FUZZ s.labels.medHeightFactor = 0.470264; // fuzzed, old value = 0.469961
	FUZZ s.labels.capHeightError = 0.555360; // fuzzed, old value = 0.553314

	FUZZ s.lcomb.MaximalSymbolDistance = 2.803218; // fuzzed, old value = 2.695199
	FUZZ s.lcomb.TestSlashLineEps = 2.937016; // fuzzed, old value = 3.084827
	FUZZ s.lcomb.TestMinHeightFactor = 0.520408; // fuzzed, old value = 0.505587
	FUZZ s.lcomb.TestMaxHeightFactor = 1.140217; // fuzzed, old value = 1.166178
	FUZZ s.lcomb.RectHeightRatio = 0.488442; // fuzzed, old value = 0.497129
	FUZZ s.lcomb.H1SuperscriptSpace = 1.147570; // fuzzed, old value = 1.151222
	FUZZ s.lcomb.H2LowercaseSpace = 0.518076; // fuzzed, old value = 0.527924
	FUZZ s.lcomb.H3LowercaseSpace = 0.472786; // fuzzed, old value = 0.494933
	FUZZ s.lcomb.H4SubscriptSpace = 0.523799; // fuzzed, old value = 0.538893
	FUZZ s.lcomb.FillLabelFactor1 = 0.485908; // fuzzed, old value = 0.488917
	FUZZ s.lcomb.FillLabelFactor2 = 0.519166; // fuzzed, old value = 0.519302
}

