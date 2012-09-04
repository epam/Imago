
void updateSettingsHighResolution(Settings &s)
{
	s.general.UseProbablistics = false;
	s.p_estimator.UsePerimeterNormalization = true;
	s.csr.StableDecorner = true;

	FUZZ s.separator.ext2charRatio = 1.233508; // fuzzed, old value = 1.200453
	FUZZ s.separator.SymProbabilityThresh = 0.584908; // fuzzed, old value = 0.56

	FUZZ s.molecule.LengthFactor_long = 0.327436; // fuzzed, old value = 0.328246
	FUZZ s.molecule.LengthFactor_medium = 0.437937; // fuzzed, old value = 0.434499
	FUZZ s.molecule.LengthFactor_default = 0.469373; // fuzzed, old value = 0.481638
	FUZZ s.molecule.LengthValue_long = 94.012240; // fuzzed, old value = 92.880256
	FUZZ s.molecule.LengthValue_medium = 88.048144; // fuzzed, old value = 84.317579
	FUZZ s.molecule.SpaceMultiply = 1.540680; // fuzzed, old value = 1.555695
	FUZZ s.molecule.AngleTreshold = 0.267297; // fuzzed, old value = 0.256197
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 15.582445; // fuzzed, old value = 16.309366
	FUZZ s.estimation.LineThickness = 5.870793; // fuzzed, old value = 5.873329
	FUZZ s.estimation.AvgBondLength = 32.607258; // fuzzed, old value = 31.898315
	FUZZ s.estimation.AddVertexEps = 5.178645; // fuzzed, old value = 5.204447
	FUZZ s.estimation.MaxSymRatio = 0.985538; // fuzzed, old value = 0.999321
	FUZZ s.estimation.MinSymRatio = 0.348109; // fuzzed, old value = 0.335394
	FUZZ s.estimation.ParLinesEps = 0.557212; // fuzzed, old value = 0.559987
	FUZZ s.estimation.SymHeightErr = 27.080202; // fuzzed, old value = 27.820523
	FUZZ s.estimation.CapitalHeightError = 0.789661; // fuzzed, old value = 0.806030
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.536390; // fuzzed, old value = 0.553435
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.201760; // fuzzed, old value = 0.193722
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 120; // fuzzed, old value = 123
	FUZZ s.mbond.LongErr = 0.423357; // fuzzed, old value = 0.408126
	FUZZ s.mbond.MediumBond = 94; // fuzzed, old value = 93
	FUZZ s.mbond.MediumErr = 0.397535; // fuzzed, old value = 0.396845
	FUZZ s.mbond.DefaultErr = 0.647771; // fuzzed, old value = 0.628855
	FUZZ s.mbond.ParBondsEps = 0.367490; // fuzzed, old value = 0.372832
	FUZZ s.mbond.DoubleRatioTresh = 7.447213; // fuzzed, old value = 7.093099
	FUZZ s.mbond.DoubleCoef = 0.077177; // fuzzed, old value = 0.080777
	FUZZ s.mbond.DoubleMagic1 = 0.899047; // fuzzed, old value = 0.881395
	FUZZ s.mbond.DoubleMagic2 = 1.014083; // fuzzed, old value = 1.008979
	FUZZ s.mbond.DoubleTreshMin = 0.091417; // fuzzed, old value = 0.091698
	FUZZ s.mbond.DoubleTreshMax = 0.824802; // fuzzed, old value = 0.841328
	FUZZ s.mbond.MaxLen1 = 145.654964; // fuzzed, old value = 145.204510
	FUZZ s.mbond.MaxLen2 = 123.405693; // fuzzed, old value = 121.539774
	FUZZ s.mbond.MaxLen3 = 117.266256; // fuzzed, old value = 118.634278
	FUZZ s.mbond.MaxLen4 = 111.818446; // fuzzed, old value = 107.978864
	FUZZ s.mbond.MaxLen5 = 80.099075; // fuzzed, old value = 83.711625
	FUZZ s.mbond.MinLen1 = 83.505798; // fuzzed, old value = 86.113757
	FUZZ s.mbond.MinLen2 = 70.416622; // fuzzed, old value = 73.528694
	FUZZ s.mbond.mbe1 = 0.074522; // fuzzed, old value = 0.074992
	FUZZ s.mbond.mbe2 = 0.156895; // fuzzed, old value = 0.157399
	FUZZ s.mbond.mbe3 = 0.201522; // fuzzed, old value = 0.207621
	FUZZ s.mbond.mbe4 = 0.179681; // fuzzed, old value = 0.179698
	FUZZ s.mbond.mbe5 = 0.165146; // fuzzed, old value = 0.163430
	FUZZ s.mbond.mbe6 = 0.196148; // fuzzed, old value = 0.199903
	FUZZ s.mbond.mbe7 = 0.420262; // fuzzed, old value = 0.412779
	FUZZ s.mbond.mbe_def = 0.530891; // fuzzed, old value = 0.510249
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.303896; // fuzzed, old value = 0.308959
	FUZZ s.mbond.DoubleRightLengthTresh = 0.343151; // fuzzed, old value = 0.328139
	FUZZ s.mbond.TripleLeftLengthTresh = 0.258187; // fuzzed, old value = 0.266600
	FUZZ s.mbond.TripleRightLengthTresh = 0.230297; // fuzzed, old value = 0.237110
	FUZZ s.mbond.Case1LengthTresh = 97.946465; // fuzzed, old value = 97.412387
	FUZZ s.mbond.Case1Factor = 0.426406; // fuzzed, old value = 0.444853
	FUZZ s.mbond.Case2LengthTresh = 80.611937; // fuzzed, old value = 78.184234
	FUZZ s.mbond.Case2Factor = 0.640124; // fuzzed, old value = 0.658458
	FUZZ s.mbond.Case3Factor = 0.790094; // fuzzed, old value = 0.821403
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.090017; // fuzzed, old value = 0.086847
	FUZZ s.skeleton.BaseSmallErr = 0.137371; // fuzzed, old value = 0.139838
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.321144; // fuzzed, old value = 0.327652
	FUZZ s.skeleton.MediumBondLen = 88; // fuzzed, old value = 87
	FUZZ s.skeleton.MediumMul = 0.200498; // fuzzed, old value = 0.195770
	FUZZ s.skeleton.MediumSmallErr = 0.144592; // fuzzed, old value = 0.139379
	FUZZ s.skeleton.LongBondLen = 103; // fuzzed, old value = 105
	FUZZ s.skeleton.LongMul = 0.129582; // fuzzed, old value = 0.129561
	FUZZ s.skeleton.LongSmallErr = 0.051026; // fuzzed, old value = 0.052888
	FUZZ s.skeleton.BrokenRepairFactor = 3.332148; // fuzzed, old value = 3.208369
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.076325; // fuzzed, old value = 1.046059
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.630517; // fuzzed, old value = 2.557861
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.191512; // fuzzed, old value = 0.201264
	FUZZ s.skeleton.DissolveMinErr = 0.186532; // fuzzed, old value = 0.192701
	FUZZ s.skeleton.ConnectBlockS = 9.368520; // fuzzed, old value = 9.764267
	FUZZ s.skeleton.ConnectFactor = 2.047254; // fuzzed, old value = 2.012180
	FUZZ s.skeleton.JoinVerticiesConst = 0.097658; // fuzzed, old value = 0.094646
	FUZZ s.skeleton.DissolveConst = 0.103419; // fuzzed, old value = 0.101654
	FUZZ s.skeleton.Dissolve2Const = 0.225730; // fuzzed, old value = 0.216204
	FUZZ s.skeleton.Join2Const = 0.319053; // fuzzed, old value = 0.333901
	FUZZ s.skeleton.Join3Const = 0.192724; // fuzzed, old value = 0.198315
	FUZZ s.skeleton.DistTreshLimFactor = 1.867937; // fuzzed, old value = 1.787764
	FUZZ s.skeleton.SlopeFact1 = 0.104090; // fuzzed, old value = 0.105327
	FUZZ s.skeleton.SlopeFact2 = 0.195491; // fuzzed, old value = 0.188657
	FUZZ s.skeleton.ShrinkEps = 0.124762; // fuzzed, old value = 0.123481
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10

	FUZZ s.routines.Circle_GapRadiusMax = 1.387337; // fuzzed, old value = 1.332954
	FUZZ s.routines.Circle_GapAngleMax = 0.511778; // fuzzed, old value = 0.492134
	FUZZ s.routines.Circle_MinRadius = 10.057468; // fuzzed, old value = 10.299804
	FUZZ s.routines.Circle_MaxDeviation = 0.194776; // fuzzed, old value = 0.192373
	FUZZ s.routines.Circle_AsCharFactor = 1.375256; // fuzzed, old value = 1.410306

	FUZZ s.routines.Algebra_IntersectionEps = 0.010450; // fuzzed, old value = 0.010432
	FUZZ s.routines.Algebra_SameLineEps = 0.203707; // fuzzed, old value = 0.194358
	FUZZ s.routines.Approx_Eps1 = 1.082805; // fuzzed, old value = 1.115186
	FUZZ s.routines.Approx_Eps2 = 0.878486; // fuzzed, old value = 0.840292
	FUZZ s.routines.Approx_CalcLineTresh = 0.813260; // fuzzed, old value = 0.850519

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.624039; // fuzzed, old value = 2.705028
	FUZZ s.wbe.SingleDownAngleMax = 45.093693; // fuzzed, old value = 45.137292
	FUZZ s.wbe.SingleDownDistancesMax = 8.898740; // fuzzed, old value = 9.029203
	FUZZ s.wbe.SingleDownLengthMax = 45.641642; // fuzzed, old value = 43.696969
	FUZZ s.wbe.SingleUpRatioEps = 1.995285; // fuzzed, old value = 1.908091
	FUZZ s.wbe.SingleUpDefCoeff = 0.266429; // fuzzed, old value = 0.278302
	FUZZ s.wbe.SingleUpIncCoeff = 0.397800; // fuzzed, old value = 0.406486
	FUZZ s.wbe.SingleUpIncLengthTresh = 31.939996; // fuzzed, old value = 32.250473
	FUZZ s.wbe.SingleUpInterpolateEps = 0.071380; // fuzzed, old value = 0.068279
	FUZZ s.wbe.SingleUpMagicAddition = 0.217056; // fuzzed, old value = 0.215318
	FUZZ s.wbe.SingleUpS2Divisor = 1.746593; // fuzzed, old value = 1.762490
	FUZZ s.wbe.SingleUpMinATresh = 1.601084; // fuzzed, old value = 1.574485
	FUZZ s.wbe.SingleUpSquareRatio = 0.596954; // fuzzed, old value = 0.594876
	FUZZ s.wbe.SingleUpAngleTresh = 0.073534; // fuzzed, old value = 0.070980
	FUZZ s.wbe.SomeTresh = 0.105959; // fuzzed, old value = 0.110870
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = true; 
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 0.944551; // fuzzed, old value = 0.972401
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.133258; // fuzzed, old value = 1.183425
	FUZZ s.characters.WriteEasyFactor = 0.959730; // fuzzed, old value = 0.917198
	FUZZ s.characters.WriteVeryEasyFactor = 0.822119; // fuzzed, old value = 0.797809
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 2.910332; // fuzzed, old value = 2.997639
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.415417; // fuzzed, old value = 3.534799
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.090902; // fuzzed, old value = 0.093991
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.378703; // fuzzed, old value = 2.442262
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.318532; // fuzzed, old value = 3.444646
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.074265; // fuzzed, old value = 1.074821
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.326074; // fuzzed, old value = 0.317866
	FUZZ s.characters.X_Quality = 0.285033; // fuzzed, old value = 0.3
	FUZZ s.characters.MinEndpointsPossible = 4; // fuzzed, old value = 4

	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.436823; // fuzzed, old value = 0.451340
	FUZZ s.csr.DeleteBadTriangles = 1.919825; // fuzzed, old value = 1.957555
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.412654; // fuzzed, old value = 1.422244

	FUZZ s.graph.MinimalDistTresh = 2.007512; // fuzzed, old value = 2.039565
	FUZZ s.graph.RatioSub = 0.963659; // fuzzed, old value = 0.986657
	FUZZ s.graph.RatioTresh = 0.423065; // fuzzed, old value = 0.424717

	FUZZ s.utils.SlashLineDensity = 0.434589; // fuzzed, old value = 0.426660
	FUZZ s.utils.TestPlusDensity = 0.465840; // fuzzed, old value = 0.444915
	FUZZ s.utils.TestPlusSq = 0.423429; // fuzzed, old value = 0.419234
	FUZZ s.utils.TestMinusRatio = 0.353658; // fuzzed, old value = 0.347247
	FUZZ s.utils.TestMinusDensity = 0.568938; // fuzzed, old value = 0.555646
	FUZZ s.utils.TestMinusHeightFactor = 0.724989; // fuzzed, old value = 0.727853

	FUZZ s.separator.hu_1_1 = 0.190948; // fuzzed, old value = 0.187009
	FUZZ s.separator.hu_1_2 = 0.085573; // fuzzed, old value = 0.089999
	FUZZ s.separator.hu_0_1 = 0.230040; // fuzzed, old value = 0.227741
	FUZZ s.separator.hu_1_3 = 0.088198; // fuzzed, old value = 0.084149
	FUZZ s.separator.hu_0_2 = 0.253422; // fuzzed, old value = 0.266166
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.564456; // fuzzed, old value = 0.581250
	FUZZ s.separator.capHeightMax = 1.325015; // fuzzed, old value = 1.358266
	FUZZ s.separator.gdConst = 1.477026; // fuzzed, old value = 1.517767
	FUZZ s.separator.SurfCoef = 2.496531; // fuzzed, old value = 2.593501
	FUZZ s.separator.capHeightRatio = 0.227267; // fuzzed, old value = 0.238682
	FUZZ s.separator.capHeightRatio2 = 2.052168; // fuzzed, old value = 1.964489
	FUZZ s.separator.getRatio1 = 1.023946; // fuzzed, old value = 0.995006
	FUZZ s.separator.getRatio2 = 1.109026; // fuzzed, old value = 1.104071
	FUZZ s.separator.testSlashLine1 = 3.244093; // fuzzed, old value = 3.246238
	FUZZ s.separator.testSlashLine2 = 2.969373; // fuzzed, old value = 3.031578
	FUZZ s.separator.minDensity = 0.206412; // fuzzed, old value = 0.204102
	FUZZ s.separator.maxDensity = 0.846352; // fuzzed, old value = 0.806080
	FUZZ s.separator.extCapHeightMin = 0.315310; // fuzzed, old value = 0.306478
	FUZZ s.separator.extCapHeightMax = 2.024779; // fuzzed, old value = 2.095513
	FUZZ s.separator.extRatioMin = 0.276775; // fuzzed, old value = 0.274874
	FUZZ s.separator.extRatioMax = 1.464954; // fuzzed, old value = 1.540172
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = true; // fuzzed, old value = true

	FUZZ s.labels.underlinePos = 0.467135; // fuzzed, old value = 0.476853
	FUZZ s.labels.weightUnderline = 0.297020; // fuzzed, old value = 0.286072
	FUZZ s.labels.ratioBase = 0.801965; // fuzzed, old value = 0.820609
	FUZZ s.labels.ratioWeight = 0.303360; // fuzzed, old value = 0.302920
	FUZZ s.labels.adjustDec = 1.270500; // fuzzed, old value = 1.274235
	FUZZ s.labels.adjustInc = 0.856470; // fuzzed, old value = 0.873424
	FUZZ s.labels.sameLineEps = 0.147512; // fuzzed, old value = 0.141207
	FUZZ s.labels.heightRatio = 0.855507; // fuzzed, old value = 0.871707
	FUZZ s.labels.medHeightFactor = 0.460674; // fuzzed, old value = 0.453486
	FUZZ s.labels.capHeightError = 0.540322; // fuzzed, old value = 0.522767

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.825574; // fuzzed, old value = 2.820964
	FUZZ s.lcomb.MaximalDistanceFactor = 0.732750; // fuzzed, old value = 0.710885
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.283490; // fuzzed, old value = 0.282795
	FUZZ s.lcomb.FillLabelFactor1 = 0.491807; // fuzzed, old value = 0.500139
	FUZZ s.lcomb.FillLabelFactor2 = 0.517075; // fuzzed, old value = 0.525941

	FUZZ s.p_estimator.DefaultApriority = 0.496084; // fuzzed, old value = 0.488702
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.735240; // fuzzed, old value = 0.736039
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.251302; // fuzzed, old value = 0.242319
	FUZZ s.p_estimator.LogisticScale = 1.021508; // fuzzed, old value = 1.003589
	FUZZ s.p_estimator.LogisticLocation = 0.953877; // fuzzed, old value = 0.910447
}

