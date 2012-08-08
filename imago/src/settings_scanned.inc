
void updateSettingsScanned(Settings &s)
{
	s.general.UseProbablistics = false;
	s.p_estimator.UsePerimeterNormalization = true; 

	FUZZ s.separator.ext2charRatio = 1.774531; // fuzzed, old value = 1.743581
	FUZZ s.separator.SymProbabilityThresh = 0.594290; // fuzzed, old value = 0.593205

	FUZZ s.molecule.LengthFactor_long = 0.353589; // fuzzed, old value = 0.355735
	FUZZ s.molecule.LengthFactor_medium = 0.391335; // fuzzed, old value = 0.389131
	FUZZ s.molecule.LengthFactor_default = 0.458738; // fuzzed, old value = 0.462193
	FUZZ s.molecule.LengthValue_long = 103.489779; // fuzzed, old value = 108.109000
	FUZZ s.molecule.LengthValue_medium = 91.834592; // fuzzed, old value = 95.312191
	FUZZ s.molecule.SpaceMultiply = 1.187321; // fuzzed, old value = 1.231943
	FUZZ s.molecule.AngleTreshold = 0.270732; // fuzzed, old value = 0.272188
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.792724; // fuzzed, old value = 17.194822
	FUZZ s.estimation.LineThickness = 7.225357; // fuzzed, old value = 7.079233
	FUZZ s.estimation.AvgBondLength = 28.462608; // fuzzed, old value = 29.416510
	FUZZ s.estimation.AddVertexEps = 4.995724; // fuzzed, old value = 5.016030
	FUZZ s.estimation.MaxSymRatio = 1.107000; // fuzzed, old value = 1.069893
	FUZZ s.estimation.MinSymRatio = 0.285846; // fuzzed, old value = 0.285072
	FUZZ s.estimation.ParLinesEps = 0.552002; // fuzzed, old value = 0.536698
	FUZZ s.estimation.SymHeightErr = 27.969571; // fuzzed, old value = 29.022566
	FUZZ s.estimation.CapitalHeightError = 0.732853; // fuzzed, old value = 0.760701
	FUZZ s.estimation.DoubleBondDist = 20; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.333673; // fuzzed, old value = 0.326633
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.161271; // fuzzed, old value = 0.156462
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 97; // fuzzed, old value = 99
	FUZZ s.mbond.LongErr = 0.358157; // fuzzed, old value = 0.353414
	FUZZ s.mbond.MediumBond = 84; // fuzzed, old value = 83
	FUZZ s.mbond.MediumErr = 0.478652; // fuzzed, old value = 0.469626
	FUZZ s.mbond.DefaultErr = 0.580151; // fuzzed, old value = 0.584307
	FUZZ s.mbond.ParBondsEps = 0.371063; // fuzzed, old value = 0.362610
	FUZZ s.mbond.DoubleRatioTresh = 7.014460; // fuzzed, old value = 7.061581
	FUZZ s.mbond.DoubleCoef = 0.084084; // fuzzed, old value = 0.083859
	FUZZ s.mbond.DoubleMagic1 = 0.793018; // fuzzed, old value = 0.829009
	FUZZ s.mbond.DoubleMagic2 = 0.894817; // fuzzed, old value = 0.914577
	FUZZ s.mbond.DoubleTreshMin = 0.101762; // fuzzed, old value = 0.099368
	FUZZ s.mbond.DoubleTreshMax = 0.679261; // fuzzed, old value = 0.666836
	FUZZ s.mbond.MaxLen1 = 162.757846; // fuzzed, old value = 163.553226
	FUZZ s.mbond.MaxLen2 = 133.088873; // fuzzed, old value = 137.180163
	FUZZ s.mbond.MaxLen3 = 107.205894; // fuzzed, old value = 104.423302
	FUZZ s.mbond.MaxLen4 = 116.339139; // fuzzed, old value = 119.117034
	FUZZ s.mbond.MaxLen5 = 74.485371; // fuzzed, old value = 72.624597
	FUZZ s.mbond.MinLen1 = 77.318967; // fuzzed, old value = 80.577400
	FUZZ s.mbond.MinLen2 = 82.623997; // fuzzed, old value = 80.076680
	FUZZ s.mbond.mbe1 = 0.072101; // fuzzed, old value = 0.072552
	FUZZ s.mbond.mbe2 = 0.161936; // fuzzed, old value = 0.158933
	FUZZ s.mbond.mbe3 = 0.170567; // fuzzed, old value = 0.167420
	FUZZ s.mbond.mbe4 = 0.153941; // fuzzed, old value = 0.151161
	FUZZ s.mbond.mbe5 = 0.179342; // fuzzed, old value = 0.179908
	FUZZ s.mbond.mbe6 = 0.206701; // fuzzed, old value = 0.216604
	FUZZ s.mbond.mbe7 = 0.405372; // fuzzed, old value = 0.413698
	FUZZ s.mbond.mbe_def = 0.555370; // fuzzed, old value = 0.538936
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.394318; // fuzzed, old value = 0.401010
	FUZZ s.mbond.DoubleRightLengthTresh = 0.333874; // fuzzed, old value = 0.333789
	FUZZ s.mbond.TripleLeftLengthTresh = 0.266706; // fuzzed, old value = 0.265374
	FUZZ s.mbond.TripleRightLengthTresh = 0.234583; // fuzzed, old value = 0.228064
	FUZZ s.mbond.Case1LengthTresh = 91.059909; // fuzzed, old value = 92.881280
	FUZZ s.mbond.Case1Factor = 0.350568; // fuzzed, old value = 0.350847
	FUZZ s.mbond.Case2LengthTresh = 88.513132; // fuzzed, old value = 84.715577
	FUZZ s.mbond.Case2Factor = 0.656119; // fuzzed, old value = 0.671213
	FUZZ s.mbond.Case3Factor = 0.911078; // fuzzed, old value = 0.916945
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.105446; // fuzzed, old value = 0.107111
	FUZZ s.skeleton.BaseSmallErr = 0.142150; // fuzzed, old value = 0.142183
	FUZZ s.skeleton.ShortBondLen = 23; // fuzzed, old value = 22
	FUZZ s.skeleton.ShortMul = 0.319675; // fuzzed, old value = 0.324503
	FUZZ s.skeleton.MediumBondLen = 97; // fuzzed, old value = 96
	FUZZ s.skeleton.MediumMul = 0.174741; // fuzzed, old value = 0.183817
	FUZZ s.skeleton.MediumSmallErr = 0.130133; // fuzzed, old value = 0.134083
	FUZZ s.skeleton.LongBondLen = 92; // fuzzed, old value = 95
	FUZZ s.skeleton.LongMul = 0.143128; // fuzzed, old value = 0.142501
	FUZZ s.skeleton.LongSmallErr = 0.058402; // fuzzed, old value = 0.059993
	FUZZ s.skeleton.BrokenRepairFactor = 3.530762; // fuzzed, old value = 3.575462
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.051655; // fuzzed, old value = 1.062723
	FUZZ s.skeleton.BrokenRepairCoef2 = 3.183927; // fuzzed, old value = 3.258597
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.177702; // fuzzed, old value = 0.176828
	FUZZ s.skeleton.DissolveMinErr = 0.193186; // fuzzed, old value = 0.196044
	FUZZ s.skeleton.ConnectBlockS = 9.737110; // fuzzed, old value = 9.771269
	FUZZ s.skeleton.ConnectFactor = 2.567178; // fuzzed, old value = 2.512766
	FUZZ s.skeleton.JoinVerticiesConst = 0.100176; // fuzzed, old value = 0.102945
	FUZZ s.skeleton.DissolveConst = 0.099488; // fuzzed, old value = 0.101335
	FUZZ s.skeleton.Dissolve2Const = 0.204460; // fuzzed, old value = 0.207443
	FUZZ s.skeleton.Join2Const = 0.218853; // fuzzed, old value = 0.223819
	FUZZ s.skeleton.Join3Const = 0.158067; // fuzzed, old value = 0.164641
	FUZZ s.skeleton.DistTreshLimFactor = 2.011705; // fuzzed, old value = 2.059933
	FUZZ s.skeleton.SlopeFact1 = 0.084126; // fuzzed, old value = 0.086924
	FUZZ s.skeleton.SlopeFact2 = 0.171282; // fuzzed, old value = 0.166295
	FUZZ s.skeleton.ShrinkEps = 0.148880; // fuzzed, old value = 0.147193
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	
	FUZZ s.routines.Circle_GapRadiusMax = 1.219945; // fuzzed, old value = 1.240496
	FUZZ s.routines.Circle_GapAngleMax = 0.211626; // fuzzed, old value = 0.203999
	FUZZ s.routines.Circle_MinRadius = 6.056196; // fuzzed, old value = 6.317388
	FUZZ s.routines.Circle_MaxDeviation = 0.009138; // fuzzed, old value = 0.008787
	FUZZ s.routines.Circle_AsCharFactor = 1.087470; // fuzzed, old value = 1.058451
	FUZZ s.routines.Algebra_IntersectionEps = 0.012304; // fuzzed, old value = 0.012047
	FUZZ s.routines.Algebra_SameLineEps = 0.218254; // fuzzed, old value = 0.225165
	FUZZ s.routines.Approx_Eps1 = 0.960157; // fuzzed, old value = 0.970654
	FUZZ s.routines.Approx_Eps2 = 0.825622; // fuzzed, old value = 0.802213
	FUZZ s.routines.Approx_CalcLineTresh = 0.802077; // fuzzed, old value = 0.811790
	FUZZ s.routines.Contour_Eps1 = 0.980031; // fuzzed, old value = 0.988044
	FUZZ s.routines.Contour_Eps2 = 0.652436; // fuzzed, old value = 0.628422

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.586511; // fuzzed, old value = 2.561631
	FUZZ s.wbe.SingleDownAngleMax = 49.546430; // fuzzed, old value = 47.478388
	FUZZ s.wbe.SingleDownDistancesMax = 10.507451; // fuzzed, old value = 10.151706
	FUZZ s.wbe.SingleDownLengthMax = 50.707336; // fuzzed, old value = 51.932546
	FUZZ s.wbe.SomeTresh = 0.129289; // fuzzed, old value = 0.133258

	FUZZ s.wbe.SingleUpRatioEps = 1.531990; // fuzzed, old value = 1.549140
	FUZZ s.wbe.SingleUpDefCoeff = 0.289316; // fuzzed, old value = 0.283414
	FUZZ s.wbe.SingleUpIncCoeff = 0.447693; // fuzzed, old value = 0.428110
	FUZZ s.wbe.SingleUpIncLengthTresh = 34.588540; // fuzzed, old value = 34.415397
	FUZZ s.wbe.SingleUpInterpolateEps = 0.071319; // fuzzed, old value = 0.072223
	FUZZ s.wbe.SingleUpMagicAddition = 0.211217; // fuzzed, old value = 0.206708
	FUZZ s.wbe.SingleUpS2Divisor = 1.613958; // fuzzed, old value = 1.558116
	FUZZ s.wbe.SingleUpMinATresh = 1.624018; // fuzzed, old value = 1.613488
	FUZZ s.wbe.SingleUpSquareRatio = 0.573586; // fuzzed, old value = 0.565263
	FUZZ s.wbe.SingleUpAngleTresh = 0.075966; // fuzzed, old value = 0.075684
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = false;
	FUZZ s.characters.MaximalEndpointsUse = 6; // fuzzed, old value = 6
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.055716; // fuzzed, old value = 1.029738
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.164232; // fuzzed, old value = 1.195352
	FUZZ s.characters.WriteEasyFactor = 1.008169; // fuzzed, old value = 0.987334
	FUZZ s.characters.WriteVeryEasyFactor = 1.027080; // fuzzed, old value = 1.015028
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 2.946004; // fuzzed, old value = 2.996088
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.302985; // fuzzed, old value = 3.173687
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.089897; // fuzzed, old value = 0.085981
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.633044; // fuzzed, old value = 2.710389
	FUZZ s.characters.DescriptorsEvenFactorStrong = 4.163078; // fuzzed, old value = 4.133139
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.972565; // fuzzed, old value = 0.967056
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.268273; // fuzzed, old value = 0.267291
	FUZZ s.characters.X_Quality = 0.109278; // fuzzed, old value = 0.104308
	FUZZ s.characters.MinEndpointsPossible = 4; // fuzzed, old value = 4
	
	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.502633; // fuzzed, old value = 0.523496
	FUZZ s.csr.DeleteBadTriangles = 2.008064; // fuzzed, old value = 2.009109
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.574297; // fuzzed, old value = 1.501167

	FUZZ s.graph.MinimalDistTresh = 2.466159; // fuzzed, old value = 2.367689
	FUZZ s.graph.RatioSub = 0.893443; // fuzzed, old value = 0.870463
	FUZZ s.graph.RatioTresh = 0.477176; // fuzzed, old value = 0.500043

	FUZZ s.utils.SlashLineDensity = 0.411511; // fuzzed, old value = 0.430484
	FUZZ s.utils.TestPlusDensity = 0.457418; // fuzzed, old value = 0.436217
	FUZZ s.utils.TestPlusSq = 0.507304; // fuzzed, old value = 0.524485
	FUZZ s.utils.TestMinusRatio = 0.303036; // fuzzed, old value = 0.302269
	FUZZ s.utils.TestMinusDensity = 0.590034; // fuzzed, old value = 0.573194
	FUZZ s.utils.TestMinusHeightFactor = 0.843076; // fuzzed, old value = 0.858968

	FUZZ s.separator.hu_1_1 = 0.217657; // fuzzed, old value = 0.221018
	FUZZ s.separator.hu_1_2 = 0.092536; // fuzzed, old value = 0.095080
	FUZZ s.separator.hu_0_1 = 0.181678; // fuzzed, old value = 0.176212
	FUZZ s.separator.hu_1_3 = 0.099738; // fuzzed, old value = 0.101366
	FUZZ s.separator.hu_0_2 = 0.239692; // fuzzed, old value = 0.237451
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.487291; // fuzzed, old value = 0.492599
	FUZZ s.separator.capHeightMax = 1.585603; // fuzzed, old value = 1.645412
	FUZZ s.separator.gdConst = 1.528281; // fuzzed, old value = 1.544403
	FUZZ s.separator.SurfCoef = 3.231201; // fuzzed, old value = 3.243341
	FUZZ s.separator.capHeightRatio = 0.331877; // fuzzed, old value = 0.339706
	FUZZ s.separator.capHeightRatio2 = 2.171431; // fuzzed, old value = 2.128121
	FUZZ s.separator.getRatio1 = 0.963598; // fuzzed, old value = 0.944537
	FUZZ s.separator.getRatio2 = 1.329942; // fuzzed, old value = 1.302321
	FUZZ s.separator.testSlashLine1 = 2.803440; // fuzzed, old value = 2.818022
	FUZZ s.separator.testSlashLine2 = 2.426928; // fuzzed, old value = 2.530549
	FUZZ s.separator.minDensity = 0.192539; // fuzzed, old value = 0.189583
	FUZZ s.separator.maxDensity = 0.951803; // fuzzed, old value = 0.919619
	FUZZ s.separator.extCapHeightMin = 0.307928; // fuzzed, old value = 0.293347
	FUZZ s.separator.extCapHeightMax = 2.234919; // fuzzed, old value = 2.197903
	FUZZ s.separator.extRatioMin = 0.299709; // fuzzed, old value = 0.287754
	FUZZ s.separator.extRatioMax = 1.354984; // fuzzed, old value = 1.412397
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 9; // fuzzed, old value = 9
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = false; // fuzzed, old value = false

	FUZZ s.labels.underlinePos = 0.429213; // fuzzed, old value = 0.411072
	FUZZ s.labels.weightUnderline = 0.280091; // fuzzed, old value = 0.272381
	FUZZ s.labels.ratioBase = 0.662331; // fuzzed, old value = 0.668668
	FUZZ s.labels.ratioWeight = 0.261594; // fuzzed, old value = 0.272612
	FUZZ s.labels.adjustDec = 1.339033; // fuzzed, old value = 1.293263
	FUZZ s.labels.adjustInc = 0.804306; // fuzzed, old value = 0.839069
	FUZZ s.labels.sameLineEps = 0.094947; // fuzzed, old value = 0.096047
	FUZZ s.labels.heightRatio = 0.772778; // fuzzed, old value = 0.775791
	FUZZ s.labels.medHeightFactor = 0.616474; // fuzzed, old value = 0.591175
	FUZZ s.labels.capHeightError = 0.497631; // fuzzed, old value = 0.518909

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.582944; // fuzzed, old value = 2.586887
	FUZZ s.lcomb.MaximalDistanceFactor = 0.570641; // fuzzed, old value = 0.573271
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.208459; // fuzzed, old value = 0.215002
	FUZZ s.lcomb.FillLabelFactor1 = 0.487336; // fuzzed, old value = 0.502944
	FUZZ s.lcomb.FillLabelFactor2 = 0.539997; // fuzzed, old value = 0.537351

	FUZZ s.p_estimator.DefaultApriority = 0.546622; // fuzzed, old value = 0.522938
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.737595; // fuzzed, old value = 0.754731
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.259158; // fuzzed, old value = 0.264833
	FUZZ s.p_estimator.LogisticScale = 0.993478; // fuzzed, old value = 1.031566
	FUZZ s.p_estimator.LogisticLocation = 0.908998; // fuzzed, old value = 0.952955
}
