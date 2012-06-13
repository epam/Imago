
void updateSettingsHandwritten(Settings &s)
{
	s.general.UseProbablistics = false; 

	FUZZ s.separator.ext2charRatio = 1.228457; // fuzzed, old value = 1.2

	FUZZ s.molecule.LengthFactor_long = 0.318252; // fuzzed, old value = 0.306684
	FUZZ s.molecule.LengthFactor_medium = 0.413917; // fuzzed, old value = 0.407360
	FUZZ s.molecule.LengthFactor_default = 0.471411; // fuzzed, old value = 0.482723
	FUZZ s.molecule.LengthValue_long = 103.912509; // fuzzed, old value = 105.177678
	FUZZ s.molecule.LengthValue_medium = 86.036397; // fuzzed, old value = 87.223215
	FUZZ s.molecule.SpaceMultiply = 1.537888; // fuzzed, old value = 1.522718
	FUZZ s.molecule.AngleTreshold = 0.252735; // fuzzed, old value = 0.257235
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 15.169151; // fuzzed, old value = 15.346966
	FUZZ s.estimation.LineThickness = 5.677534; // fuzzed, old value = 5.799111
	FUZZ s.estimation.AvgBondLength = 33.627685; // fuzzed, old value = 32.193297
	FUZZ s.estimation.AddVertexEps = 4.686013; // fuzzed, old value = 4.892114
	FUZZ s.estimation.MaxSymRatio = 1.047183; // fuzzed, old value = 1.077101
	FUZZ s.estimation.MinSymRatio = 0.315310; // fuzzed, old value = 0.326936
	FUZZ s.estimation.ParLinesEps = 0.520771; // fuzzed, old value = 0.501992
	FUZZ s.estimation.SymHeightErr = 26.968339; // fuzzed, old value = 28.286315
	FUZZ s.estimation.CapitalHeightError = 0.867297; // fuzzed, old value = 0.867746
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.518941; // fuzzed, old value = 0.498218
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.192857; // fuzzed, old value = 0.2
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 113; // fuzzed, old value = 116
	FUZZ s.mbond.LongErr = 0.376113; // fuzzed, old value = 0.360990
	FUZZ s.mbond.MediumBond = 91; // fuzzed, old value = 93
	FUZZ s.mbond.MediumErr = 0.396442; // fuzzed, old value = 0.396389
	FUZZ s.mbond.DefaultErr = 0.636280; // fuzzed, old value = 0.625824
	FUZZ s.mbond.ParBondsEps = 0.320627; // fuzzed, old value = 0.306788
	FUZZ s.mbond.DoubleRatioTresh = 7.605677; // fuzzed, old value = 7.460718
	FUZZ s.mbond.DoubleCoef = 0.082399; // fuzzed, old value = 0.083551
	FUZZ s.mbond.DoubleMagic1 = 0.908335; // fuzzed, old value = 0.944548
	FUZZ s.mbond.DoubleMagic2 = 0.997451; // fuzzed, old value = 0.975316
	FUZZ s.mbond.DoubleTreshMin = 0.098354; // fuzzed, old value = 0.100047
	FUZZ s.mbond.DoubleTreshMax = 0.879415; // fuzzed, old value = 0.875361
	FUZZ s.mbond.MaxLen1 = 154.921735; // fuzzed, old value = 157.699414
	FUZZ s.mbond.MaxLen2 = 128.045368; // fuzzed, old value = 125.498590
	FUZZ s.mbond.MaxLen3 = 114.537037; // fuzzed, old value = 109.304008
	FUZZ s.mbond.MaxLen4 = 114.416588; // fuzzed, old value = 111.437231
	FUZZ s.mbond.MaxLen5 = 87.748438; // fuzzed, old value = 87.849379
	FUZZ s.mbond.MinLen1 = 82.429623; // fuzzed, old value = 80.348392
	FUZZ s.mbond.MinLen2 = 72.965395; // fuzzed, old value = 76.314382
	FUZZ s.mbond.mbe1 = 0.078724; // fuzzed, old value = 0.082287
	FUZZ s.mbond.mbe2 = 0.139495; // fuzzed, old value = 0.146037
	FUZZ s.mbond.mbe3 = 0.205260; // fuzzed, old value = 0.207969
	FUZZ s.mbond.mbe4 = 0.178341; // fuzzed, old value = 0.182796
	FUZZ s.mbond.mbe5 = 0.154538; // fuzzed, old value = 0.152938
	FUZZ s.mbond.mbe6 = 0.212197; // fuzzed, old value = 0.213147
	FUZZ s.mbond.mbe7 = 0.382867; // fuzzed, old value = 0.366129
	FUZZ s.mbond.mbe_def = 0.524099; // fuzzed, old value = 0.520742
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.313287; // fuzzed, old value = 0.327004
	FUZZ s.mbond.DoubleRightLengthTresh = 0.331798; // fuzzed, old value = 0.316236
	FUZZ s.mbond.TripleLeftLengthTresh = 0.277898; // fuzzed, old value = 0.265782
	FUZZ s.mbond.TripleRightLengthTresh = 0.231822; // fuzzed, old value = 0.238093
	FUZZ s.mbond.Case1LengthTresh = 105.443901; // fuzzed, old value = 104.640582
	FUZZ s.mbond.Case1Factor = 0.469945; // fuzzed, old value = 0.474073
	FUZZ s.mbond.Case2LengthTresh = 80.193117; // fuzzed, old value = 79.216539
	FUZZ s.mbond.Case2Factor = 0.675191; // fuzzed, old value = 0.677224
	FUZZ s.mbond.Case3Factor = 0.866118; // fuzzed, old value = 0.902808
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.086508; // fuzzed, old value = 0.087032
	FUZZ s.skeleton.BaseSmallErr = 0.141151; // fuzzed, old value = 0.146661
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.332156; // fuzzed, old value = 0.329981
	FUZZ s.skeleton.MediumBondLen = 86; // fuzzed, old value = 83
	FUZZ s.skeleton.MediumMul = 0.192742; // fuzzed, old value = 0.184914
	FUZZ s.skeleton.MediumSmallErr = 0.136981; // fuzzed, old value = 0.137804
	FUZZ s.skeleton.LongBondLen = 100; // fuzzed, old value = 99
	FUZZ s.skeleton.LongMul = 0.135336; // fuzzed, old value = 0.138933
	FUZZ s.skeleton.LongSmallErr = 0.059091; // fuzzed, old value = 0.062113
	FUZZ s.skeleton.BrokenRepairFactor = 3.034957; // fuzzed, old value = 2.907540
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.014748; // fuzzed, old value = 0.968157
	FUZZ s.skeleton.BrokenRepairCoef2 = 2.592298; // fuzzed, old value = 2.652422
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.189301; // fuzzed, old value = 0.198932
	FUZZ s.skeleton.DissolveMinErr = 0.175746; // fuzzed, old value = 0.170885
	FUZZ s.skeleton.ConnectBlockS = 10.785240; // fuzzed, old value = 10.860028
	FUZZ s.skeleton.ConnectFactor = 1.942177; // fuzzed, old value = 1.979539
	FUZZ s.skeleton.JoinVerticiesConst = 0.104121; // fuzzed, old value = 0.102296
	FUZZ s.skeleton.DissolveConst = 0.098362; // fuzzed, old value = 0.096910
	FUZZ s.skeleton.Dissolve2Const = 0.194633; // fuzzed, old value = 0.190231
	FUZZ s.skeleton.Join2Const = 0.334515; // fuzzed, old value = 0.339420
	FUZZ s.skeleton.Join3Const = 0.214479; // fuzzed, old value = 0.208102
	FUZZ s.skeleton.DistTreshLimFactor = 1.767427; // fuzzed, old value = 1.822734
	FUZZ s.skeleton.SlopeFact1 = 0.105068; // fuzzed, old value = 0.108766
	FUZZ s.skeleton.SlopeFact2 = 0.177636; // fuzzed, old value = 0.181641
	FUZZ s.skeleton.ShrinkEps = 0.113700; // fuzzed, old value = 0.117740
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10

	FUZZ s.routines.Circle_GapRadiusMax = 1.238708; // fuzzed, old value = 1.2
	FUZZ s.routines.Circle_GapAngleMax = 0.478777; // fuzzed, old value = 0.5
	FUZZ s.routines.Circle_MinRadius = 4.912908; // fuzzed, old value = 5.0
	FUZZ s.routines.Circle_MaxDeviation = 0.202378; // fuzzed, old value = 0.2
	FUZZ s.routines.Circle_AsCharFactor = 1.454969; // fuzzed, old value = 1.4

	FUZZ s.routines.Algebra_IntersectionEps = 0.010440; // fuzzed, old value = 0.010698
	FUZZ s.routines.Algebra_SameLineEps = 0.199966; // fuzzed, old value = 0.206971
	FUZZ s.routines.Approx_Eps1 = 1.122353; // fuzzed, old value = 1.149482
	FUZZ s.routines.Approx_Eps2 = 0.872298; // fuzzed, old value = 0.865320
	FUZZ s.routines.Approx_CalcLineTresh = 0.826057; // fuzzed, old value = 0.861870

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.765285; // fuzzed, old value = 2.876762
	FUZZ s.wbe.SingleDownAngleMax = 45.966879; // fuzzed, old value = 44.892284
	FUZZ s.wbe.SingleDownDistancesMax = 9.887962; // fuzzed, old value = 9.992270
	FUZZ s.wbe.SingleDownLengthMax = 37.614879; // fuzzed, old value = 38.620434
	FUZZ s.wbe.SingleUpRatioEps = 1.956981; // fuzzed, old value = 1.957127
	FUZZ s.wbe.SingleUpDefCoeff = 0.258282; // fuzzed, old value = 0.267500
	FUZZ s.wbe.SingleUpIncCoeff = 0.452763; // fuzzed, old value = 0.433192
	FUZZ s.wbe.SingleUpIncLengthTresh = 36.641491; // fuzzed, old value = 36.428205
	FUZZ s.wbe.SingleUpInterpolateEps = 0.060408; // fuzzed, old value = 0.061148
	FUZZ s.wbe.SingleUpMagicAddition = 0.218206; // fuzzed, old value = 0.215826
	FUZZ s.wbe.SingleUpS2Divisor = 1.856176; // fuzzed, old value = 1.857182
	FUZZ s.wbe.SingleUpMinATresh = 1.789007; // fuzzed, old value = 1.764370
	FUZZ s.wbe.SingleUpSquareRatio = 0.580176; // fuzzed, old value = 0.568118
	FUZZ s.wbe.SingleUpAngleTresh = 0.071043; // fuzzed, old value = 0.069205
	FUZZ s.wbe.SomeTresh = 0.099948; // fuzzed, old value = 0.096025
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = true;
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.042811; // fuzzed, old value = 1.063898
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.200793; // fuzzed, old value = 1.189764
	FUZZ s.characters.WriteEasyFactor = 0.966019; // fuzzed, old value = 0.939331
	FUZZ s.characters.WriteVeryEasyFactor = 0.768024; // fuzzed, old value = 0.800745
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.084192; // fuzzed, old value = 3.106801
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.385517; // fuzzed, old value = 3.291968
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.086253; // fuzzed, old value = 0.090755
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.310488; // fuzzed, old value = 2.417801
	FUZZ s.characters.DescriptorsEvenFactorStrong = 3.774555; // fuzzed, old value = 3.769212
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.935876; // fuzzed, old value = 0.931412
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.316648; // fuzzed, old value = 0.302461

	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.478222; // fuzzed, old value = 0.482964
	FUZZ s.csr.DeleteBadTriangles = 2.172035; // fuzzed, old value = 2.124101
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.479794; // fuzzed, old value = 1.472190

	FUZZ s.graph.MinimalDistTresh = 1.821545; // fuzzed, old value = 1.854608
	FUZZ s.graph.RatioSub = 1.014226; // fuzzed, old value = 1.005202
	FUZZ s.graph.RatioTresh = 0.419309; // fuzzed, old value = 0.402732

	FUZZ s.utils.SlashLineDensity = 0.480276; // fuzzed, old value = 0.480961
	FUZZ s.utils.TestPlusDensity = 0.434167; // fuzzed, old value = 0.417797
	FUZZ s.utils.TestPlusSq = 0.429271; // fuzzed, old value = 0.427328
	FUZZ s.utils.TestMinusRatio = 0.375310; // fuzzed, old value = 0.368049
	FUZZ s.utils.TestMinusDensity = 0.598837; // fuzzed, old value = 0.616128
	FUZZ s.utils.TestMinusHeightFactor = 0.771482; // fuzzed, old value = 0.789442

	FUZZ s.separator.hu_1_1 = 0.182200; // fuzzed, old value = 0.189831
	FUZZ s.separator.hu_1_2 = 0.080232; // fuzzed, old value = 0.079148
	FUZZ s.separator.hu_0_1 = 0.243055; // fuzzed, old value = 0.241533
	FUZZ s.separator.hu_1_3 = 0.091750; // fuzzed, old value = 0.088320
	FUZZ s.separator.hu_0_2 = 0.260262; // fuzzed, old value = 0.250102
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.535419; // fuzzed, old value = 0.523744
	FUZZ s.separator.capHeightMax = 1.331047; // fuzzed, old value = 1.337355
	FUZZ s.separator.gdConst = 1.494774; // fuzzed, old value = 1.520337
	FUZZ s.separator.SurfCoef = 2.690169; // fuzzed, old value = 2.811615
	FUZZ s.separator.capHeightRatio = 0.248689; // fuzzed, old value = 0.248671
	FUZZ s.separator.capHeightRatio2 = 1.816786; // fuzzed, old value = 1.817621
	FUZZ s.separator.getRatio1 = 0.868547; // fuzzed, old value = 0.869905
	FUZZ s.separator.getRatio2 = 1.112853; // fuzzed, old value = 1.107858
	FUZZ s.separator.testSlashLine1 = 3.190627; // fuzzed, old value = 3.056236
	FUZZ s.separator.testSlashLine2 = 2.961420; // fuzzed, old value = 2.947643
	FUZZ s.separator.minDensity = 0.204792; // fuzzed, old value = 0.209188
	FUZZ s.separator.maxDensity = 0.835935; // fuzzed, old value = 0.874702
	FUZZ s.separator.extCapHeightMin = 0.298221; // fuzzed, old value = 0.307440
	FUZZ s.separator.extCapHeightMax = 2.078549; // fuzzed, old value = 2.050196
	FUZZ s.separator.extRatioMin = 0.280485; // fuzzed, old value = 0.277232
	FUZZ s.separator.extRatioMax = 1.448039; // fuzzed, old value = 1.432846
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = true; // fuzzed, old value = true

	FUZZ s.labels.underlinePos = 0.463312; // fuzzed, old value = 0.487118
	FUZZ s.labels.weightUnderline = 0.315862; // fuzzed, old value = 0.315205
	FUZZ s.labels.ratioBase = 0.862996; // fuzzed, old value = 0.827268
	FUZZ s.labels.ratioWeight = 0.293834; // fuzzed, old value = 0.307824
	FUZZ s.labels.adjustDec = 1.289963; // fuzzed, old value = 1.268716
	FUZZ s.labels.adjustInc = 0.859068; // fuzzed, old value = 0.867507
	FUZZ s.labels.sameLineEps = 0.118423; // fuzzed, old value = 0.119324
	FUZZ s.labels.heightRatio = 0.811731; // fuzzed, old value = 0.846923
	FUZZ s.labels.medHeightFactor = 0.467762; // fuzzed, old value = 0.481943
	FUZZ s.labels.capHeightError = 0.488753; // fuzzed, old value = 0.503494

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.662893; // fuzzed, old value = 2.636896
	FUZZ s.lcomb.MaximalDistanceFactor = 0.683355; // fuzzed, old value = 0.7
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.290503; // fuzzed, old value = 0.3
	FUZZ s.lcomb.FillLabelFactor1 = 0.523083; // fuzzed, old value = 0.502598
	FUZZ s.lcomb.FillLabelFactor2 = 0.474184; // fuzzed, old value = 0.493979

	FUZZ s.p_estimator.DefaultApriority = 0.497449; // fuzzed, old value = 0.5
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.765935; // fuzzed, old value = 0.8
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.245732; // fuzzed, old value = 0.25
	FUZZ s.p_estimator.LogisticScale = 0.971043; // fuzzed, old value = 1.0
	FUZZ s.p_estimator.LogisticLocation = 0.951224; // fuzzed, old value = 1.0
}

