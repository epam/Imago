
void updateSettingsScanned(Settings &s)
{
	FUZZ s.general.UseProbablistics = false; // fuzzed, old value = false

	FUZZ s.separator.ext2charRatio = 1.844019; // fuzzed, old value = 1.817831

	FUZZ s.molecule.LengthFactor_long = 0.325770; // fuzzed, old value = 0.315152
	FUZZ s.molecule.LengthFactor_medium = 0.372015; // fuzzed, old value = 0.389830
	FUZZ s.molecule.LengthFactor_default = 0.445776; // fuzzed, old value = 0.449027
	FUZZ s.molecule.LengthValue_long = 107.557580; // fuzzed, old value = 105.508872
	FUZZ s.molecule.LengthValue_medium = 83.795200; // fuzzed, old value = 80.993297
	FUZZ s.molecule.SpaceMultiply = 1.415498; // fuzzed, old value = 1.429923
	FUZZ s.molecule.AngleTreshold = 0.266317; // fuzzed, old value = 0.263010
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.780515; // fuzzed, old value = 18.573252
	FUZZ s.estimation.LineThickness = 6.598500; // fuzzed, old value = 6.299226
	FUZZ s.estimation.AvgBondLength = 30.785777; // fuzzed, old value = 29.895446
	FUZZ s.estimation.AddVertexEps = 4.957394; // fuzzed, old value = 5.050122
	FUZZ s.estimation.MaxSymRatio = 1.178012; // fuzzed, old value = 1.168082
	FUZZ s.estimation.MinSymRatio = 0.321194; // fuzzed, old value = 0.322742
	FUZZ s.estimation.ParLinesEps = 0.567387; // fuzzed, old value = 0.545863
	FUZZ s.estimation.SymHeightErr = 26.747686; // fuzzed, old value = 26.091749
	FUZZ s.estimation.CapitalHeightError = 0.825556; // fuzzed, old value = 0.852278
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.385587; // fuzzed, old value = 0.401027
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 112; // fuzzed, old value = 112
	FUZZ s.mbond.LongErr = 0.343127; // fuzzed, old value = 0.350717
	FUZZ s.mbond.MediumBond = 82; // fuzzed, old value = 86
	FUZZ s.mbond.MediumErr = 0.452962; // fuzzed, old value = 0.437198
	FUZZ s.mbond.DefaultErr = 0.689375; // fuzzed, old value = 0.673239
	FUZZ s.mbond.ParBondsEps = 0.352178; // fuzzed, old value = 0.343600
	FUZZ s.mbond.DoubleRatioTresh = 6.315967; // fuzzed, old value = 6.413808
	FUZZ s.mbond.DoubleCoef = 0.075761; // fuzzed, old value = 0.076054
	FUZZ s.mbond.DoubleMagic1 = 0.904452; // fuzzed, old value = 0.902185
	FUZZ s.mbond.DoubleMagic2 = 0.903106; // fuzzed, old value = 0.928028
	FUZZ s.mbond.DoubleTreshMin = 0.095658; // fuzzed, old value = 0.094928
	FUZZ s.mbond.DoubleTreshMax = 0.789355; // fuzzed, old value = 0.815465
	FUZZ s.mbond.MaxLen1 = 157.904020; // fuzzed, old value = 152.490507
	FUZZ s.mbond.MaxLen2 = 135.630039; // fuzzed, old value = 133.330018
	FUZZ s.mbond.MaxLen3 = 114.728601; // fuzzed, old value = 116.978601
	FUZZ s.mbond.MaxLen4 = 127.339423; // fuzzed, old value = 123.764210
	FUZZ s.mbond.MaxLen5 = 77.026965; // fuzzed, old value = 75.254072
	FUZZ s.mbond.MinLen1 = 89.843982; // fuzzed, old value = 89.185441
	FUZZ s.mbond.MinLen2 = 75.049951; // fuzzed, old value = 71.636468
	FUZZ s.mbond.mbe1 = 0.078946; // fuzzed, old value = 0.077716
	FUZZ s.mbond.mbe2 = 0.158379; // fuzzed, old value = 0.158104
	FUZZ s.mbond.mbe3 = 0.195539; // fuzzed, old value = 0.205715
	FUZZ s.mbond.mbe4 = 0.174750; // fuzzed, old value = 0.174596
	FUZZ s.mbond.mbe5 = 0.150039; // fuzzed, old value = 0.156193
	FUZZ s.mbond.mbe6 = 0.223369; // fuzzed, old value = 0.224181
	FUZZ s.mbond.mbe7 = 0.394304; // fuzzed, old value = 0.413945
	FUZZ s.mbond.mbe_def = 0.529134; // fuzzed, old value = 0.519528
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.366719; // fuzzed, old value = 0.369505
	FUZZ s.mbond.DoubleRightLengthTresh = 0.298243; // fuzzed, old value = 0.304404
	FUZZ s.mbond.TripleLeftLengthTresh = 0.246036; // fuzzed, old value = 0.254558
	FUZZ s.mbond.TripleRightLengthTresh = 0.231797; // fuzzed, old value = 0.236216
	FUZZ s.mbond.Case1LengthTresh = 94.348981; // fuzzed, old value = 94.473679
	FUZZ s.mbond.Case1Factor = 0.375548; // fuzzed, old value = 0.394970
	FUZZ s.mbond.Case2LengthTresh = 85.735338; // fuzzed, old value = 89.005933
	FUZZ s.mbond.Case2Factor = 0.692787; // fuzzed, old value = 0.676557
	FUZZ s.mbond.Case3Factor = 0.976425; // fuzzed, old value = 0.992474
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.105426; // fuzzed, old value = 0.103365
	FUZZ s.skeleton.BaseSmallErr = 0.158554; // fuzzed, old value = 0.160245
	FUZZ s.skeleton.ShortBondLen = 21; // fuzzed, old value = 21
	FUZZ s.skeleton.ShortMul = 0.340184; // fuzzed, old value = 0.334081
	FUZZ s.skeleton.MediumBondLen = 90; // fuzzed, old value = 88
	FUZZ s.skeleton.MediumMul = 0.166588; // fuzzed, old value = 0.161867
	FUZZ s.skeleton.MediumSmallErr = 0.134749; // fuzzed, old value = 0.138174
	FUZZ s.skeleton.LongBondLen = 97; // fuzzed, old value = 95
	FUZZ s.skeleton.LongMul = 0.144725; // fuzzed, old value = 0.150246
	FUZZ s.skeleton.LongSmallErr = 0.065124; // fuzzed, old value = 0.062965
	FUZZ s.skeleton.BrokenRepairFactor = 3.279799; // fuzzed, old value = 3.388874
	FUZZ s.skeleton.BrokenRepairCoef1 = 0.935507; // fuzzed, old value = 0.902884
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.933075; // fuzzed, old value = 2.798138
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.206637; // fuzzed, old value = 0.198789
	FUZZ s.skeleton.DissolveMinErr = 0.170083; // fuzzed, old value = 0.170569
	FUZZ s.skeleton.ConnectBlockS = 10.205617; // fuzzed, old value = 9.833995
	FUZZ s.skeleton.ConnectFactor = 2.029947; // fuzzed, old value = 2.027852
	FUZZ s.skeleton.JoinVerticiesConst = 0.100070; // fuzzed, old value = 0.097398
	FUZZ s.skeleton.DissolveConst = 0.097222; // fuzzed, old value = 0.093940
	FUZZ s.skeleton.Dissolve2Const = 0.188352; // fuzzed, old value = 0.188921
	FUZZ s.skeleton.Join2Const = 0.278459; // fuzzed, old value = 0.286146
	FUZZ s.skeleton.Join3Const = 0.182380; // fuzzed, old value = 0.190007
	FUZZ s.skeleton.DistTreshLimFactor = 2.029662; // fuzzed, old value = 2.034017
	FUZZ s.skeleton.SlopeFact1 = 0.095759; // fuzzed, old value = 0.094975
	FUZZ s.skeleton.SlopeFact2 = 0.173057; // fuzzed, old value = 0.173540
	FUZZ s.skeleton.ShrinkEps = 0.138586; // fuzzed, old value = 0.133261
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	s.routines.Contour_Eps1 = 1.130985;
	s.routines.Contour_Eps2 = 0.680156; 
	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	
	FUZZ s.routines.Circle_GapRadiusMax = 1.020928; // fuzzed, old value = 1.05
	FUZZ s.routines.Circle_GapAngleMax = 0.197631; // fuzzed, old value = 0.2
	FUZZ s.routines.Circle_MinRadius = 10.219260; // fuzzed, old value = 10.0
	FUZZ s.routines.Circle_MaxDeviation = 0.010001; // fuzzed, old value = 0.01
	FUZZ s.routines.Circle_AsCharFactor = 1.05;

	FUZZ s.routines.Algebra_IntersectionEps = 0.011165; // fuzzed, old value = 0.011089
	FUZZ s.routines.Algebra_SameLineEps = 0.223550; // fuzzed, old value = 0.229721
	FUZZ s.routines.Approx_Eps1 = 1.151786; // fuzzed, old value = 1.114736
	FUZZ s.routines.Approx_Eps2 = 0.828235; // fuzzed, old value = 0.853248
	FUZZ s.routines.Approx_CalcLineTresh = 0.919022; // fuzzed, old value = 0.945804
	FUZZ s.routines.Contour_Eps1 = 0.955250; // fuzzed, old value = 0.975754
	FUZZ s.routines.Contour_Eps2 = 0.699570; // fuzzed, old value = 0.682406

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.626996; // fuzzed, old value = 2.751391
	FUZZ s.wbe.SingleDownAngleMax = 43.894630; // fuzzed, old value = 43.151557
	FUZZ s.wbe.SingleDownDistancesMax = 9.878713; // fuzzed, old value = 10.024443
	FUZZ s.wbe.SingleDownLengthMax = 48.034367; // fuzzed, old value = 49.693731
	FUZZ s.wbe.SingleUpRatioEps = 1.571272; // fuzzed, old value = 1.640030
	FUZZ s.wbe.SingleUpDefCoeff = 0.275489; // fuzzed, old value = 0.289574
	FUZZ s.wbe.SingleUpIncCoeff = 0.492325; // fuzzed, old value = 0.491721
	FUZZ s.wbe.SingleUpIncLengthTresh = 36.776896; // fuzzed, old value = 36.262785
	FUZZ s.wbe.SingleUpInterpolateEps = 0.063786; // fuzzed, old value = 0.064918
	FUZZ s.wbe.SingleUpMagicAddition = 0.250076; // fuzzed, old value = 0.244908
	FUZZ s.wbe.SingleUpS2Divisor = 1.437891; // fuzzed, old value = 1.398371
	FUZZ s.wbe.SingleUpMinATresh = 1.767134; // fuzzed, old value = 1.720929
	FUZZ s.wbe.SingleUpSquareRatio = 0.654213; // fuzzed, old value = 0.684612
	FUZZ s.wbe.SingleUpAngleTresh = 0.067372; // fuzzed, old value = 0.067938
	FUZZ s.wbe.SomeTresh = 0.102724; // fuzzed, old value = 0.104934
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.HackFor3Use = false; // fuzzed, old value = false
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 0.979192; // fuzzed, old value = 1.014210
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.140911; // fuzzed, old value = 1.177124
	FUZZ s.characters.WriteEasyFactor = 0.965983; // fuzzed, old value = 0.992805
	FUZZ s.characters.WriteVeryEasyFactor = 0.935621; // fuzzed, old value = 0.948974
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.319964; // fuzzed, old value = 3.194507
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.078508; // fuzzed, old value = 3.059400
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.098097; // fuzzed, old value = 0.096811
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.561254; // fuzzed, old value = 2.609470
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.809630; // fuzzed, old value = 3.738476
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.926533; // fuzzed, old value = 0.927528
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.286662; // fuzzed, old value = 0.294104
	FUZZ s.characters.HW_Line = 1.495987; // fuzzed, old value = 1.537709
	FUZZ s.characters.HW_F = 3.453994; // fuzzed, old value = 3.332573
	FUZZ s.characters.HW_Tricky = 3.068666; // fuzzed, old value = 3.014611
	FUZZ s.characters.HW_Hard = 4.209693; // fuzzed, old value = 4.350860
	FUZZ s.characters.HW_Other = 3.534641; // fuzzed, old value = 3.704123

	s.csr.UseSimpleApproximator = false;
	FUZZ s.csr.Dissolve = 0.513915; // fuzzed, old value = 0.522418
	FUZZ s.csr.DeleteBadTriangles = 1.902779; // fuzzed, old value = 1.926071
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.704608; // fuzzed, old value = 1.666288

	FUZZ s.graph.MinimalDistTresh = 2.029322; // fuzzed, old value = 2.069352
	FUZZ s.graph.RatioSub = 0.999274; // fuzzed, old value = 1.036255
	FUZZ s.graph.RatioTresh = 0.450309; // fuzzed, old value = 0.449162

	FUZZ s.utils.SlashLineDensity = 0.395425; // fuzzed, old value = 0.398294
	FUZZ s.utils.TestPlusDensity = 0.453565; // fuzzed, old value = 0.436384
	FUZZ s.utils.TestPlusSq = 0.446065; // fuzzed, old value = 0.445527
	FUZZ s.utils.TestMinusRatio = 0.339020; // fuzzed, old value = 0.338805
	FUZZ s.utils.TestMinusDensity = 0.609794; // fuzzed, old value = 0.592761
	FUZZ s.utils.TestMinusHeightFactor = 0.862917; // fuzzed, old value = 0.888058

	FUZZ s.separator.hu_1_1 = 0.213720; // fuzzed, old value = 0.215473
	FUZZ s.separator.hu_1_2 = 0.080000; // fuzzed, old value = 0.076792
	FUZZ s.separator.hu_0_1 = 0.212832; // fuzzed, old value = 0.205034
	FUZZ s.separator.hu_1_3 = 0.090430; // fuzzed, old value = 0.087845
	FUZZ s.separator.hu_0_2 = 0.210287; // fuzzed, old value = 0.208118
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.530980; // fuzzed, old value = 0.547635
	FUZZ s.separator.capHeightMax = 1.415177; // fuzzed, old value = 1.389777
	FUZZ s.separator.gdConst = 1.614444; // fuzzed, old value = 1.563537
	FUZZ s.separator.SurfCoef = 3.149856; // fuzzed, old value = 3.104292
	FUZZ s.separator.capHeightRatio = 0.269188; // fuzzed, old value = 0.262520
	FUZZ s.separator.capHeightRatio2 = 1.967274; // fuzzed, old value = 2.015533
	FUZZ s.separator.getRatio1 = 1.007940; // fuzzed, old value = 1.046155
	FUZZ s.separator.getRatio2 = 1.207576; // fuzzed, old value = 1.245533
	FUZZ s.separator.testSlashLine1 = 3.049334; // fuzzed, old value = 2.940416
	FUZZ s.separator.testSlashLine2 = 2.574961; // fuzzed, old value = 2.694239
	FUZZ s.separator.minDensity = 0.197233; // fuzzed, old value = 0.207364
	FUZZ s.separator.maxDensity = 0.902829; // fuzzed, old value = 0.889576
	FUZZ s.separator.extCapHeightMin = 0.304347; // fuzzed, old value = 0.301238
	FUZZ s.separator.extCapHeightMax = 2.182021; // fuzzed, old value = 2.173322
	FUZZ s.separator.extRatioMin = 0.321910; // fuzzed, old value = 0.317737
	FUZZ s.separator.extRatioMax = 1.511297; // fuzzed, old value = 1.549829
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4

	FUZZ s.labels.underlinePos = 0.387511; // fuzzed, old value = 0.399110
	FUZZ s.labels.weightUnderline = 0.280123; // fuzzed, old value = 0.292984
	FUZZ s.labels.ratioBase = 0.790043; // fuzzed, old value = 0.808756
	FUZZ s.labels.ratioWeight = 0.276040; // fuzzed, old value = 0.273840
	FUZZ s.labels.adjustDec = 1.303607; // fuzzed, old value = 1.281131
	FUZZ s.labels.adjustInc = 0.771535; // fuzzed, old value = 0.787364
	FUZZ s.labels.sameLineEps = 0.116347; // fuzzed, old value = 0.119902
	FUZZ s.labels.heightRatio = 0.766878; // fuzzed, old value = 0.793881
	FUZZ s.labels.medHeightFactor = 0.520234; // fuzzed, old value = 0.505379
	FUZZ s.labels.capHeightError = 0.495840; // fuzzed, old value = 0.503738

	FUZZ s.lcomb.MaximalSymbolDistance = 2.747865; // fuzzed, old value = 2.627132
	FUZZ s.lcomb.TestSlashLineEps = 3.431774; // fuzzed, old value = 3.280245
	FUZZ s.lcomb.TestMinHeightFactor = 0.579268; // fuzzed, old value = 0.553344
	FUZZ s.lcomb.TestMaxHeightFactor = 1.083503; // fuzzed, old value = 1.061835
	FUZZ s.lcomb.RectHeightRatio = 0.465003; // fuzzed, old value = 0.472451
	FUZZ s.lcomb.H1SuperscriptSpace = 1.029819; // fuzzed, old value = 1.077203
	FUZZ s.lcomb.H2LowercaseSpace = 0.473407; // fuzzed, old value = 0.497997
	FUZZ s.lcomb.H3LowercaseSpace = 0.432355; // fuzzed, old value = 0.437745
	FUZZ s.lcomb.H4SubscriptSpace = 0.518284; // fuzzed, old value = 0.512326
	FUZZ s.lcomb.FillLabelFactor1 = 0.519768; // fuzzed, old value = 0.524486
	FUZZ s.lcomb.FillLabelFactor2 = 0.534072; // fuzzed, old value = 0.545255
}
