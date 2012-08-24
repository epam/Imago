
void updateSettingsScanned(Settings &s)
{
	s.general.UseProbablistics = false;
	s.p_estimator.UsePerimeterNormalization = true; 

	FUZZ s.separator.ext2charRatio = 1.743581; // fuzzed, old value = 1.769256
	FUZZ s.separator.SymProbabilityThresh = 0.593205; // fuzzed, old value = 0.582931

	FUZZ s.molecule.LengthFactor_long = 0.355735; // fuzzed, old value = 0.351291
	FUZZ s.molecule.LengthFactor_medium = 0.389131; // fuzzed, old value = 0.404442
	FUZZ s.molecule.LengthFactor_default = 0.462193; // fuzzed, old value = 0.470038
	FUZZ s.molecule.LengthValue_long = 108.109000; // fuzzed, old value = 109.107607
	FUZZ s.molecule.LengthValue_medium = 95.312191; // fuzzed, old value = 93.887277
	FUZZ s.molecule.SpaceMultiply = 1.231943; // fuzzed, old value = 1.337344
	FUZZ s.molecule.AngleTreshold = 0.272188; // fuzzed, old value = 0.270375
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 17.194822; // fuzzed, old value = 15.871465
	FUZZ s.estimation.LineThickness = 7.079233; // fuzzed, old value = 7.153437
	FUZZ s.estimation.AvgBondLength = 29.416510; // fuzzed, old value = 30.459016
	FUZZ s.estimation.AddVertexEps = 5.016030; // fuzzed, old value = 5.030846
	FUZZ s.estimation.MaxSymRatio = 1.069893; // fuzzed, old value = 1.079929
	FUZZ s.estimation.MinSymRatio = 0.285072; // fuzzed, old value = 0.300973
	FUZZ s.estimation.ParLinesEps = 0.536698; // fuzzed, old value = 0.555687
	FUZZ s.estimation.SymHeightErr = 29.022566; // fuzzed, old value = 27.777021
	FUZZ s.estimation.CapitalHeightError = 0.760701; // fuzzed, old value = 0.840118
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.326633; // fuzzed, old value = 0.354178
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.156462; // fuzzed, old value = 0.154351
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 99; // fuzzed, old value = 99
	FUZZ s.mbond.LongErr = 0.353414; // fuzzed, old value = 0.330418
	FUZZ s.mbond.MediumBond = 83; // fuzzed, old value = 83
	FUZZ s.mbond.MediumErr = 0.469626; // fuzzed, old value = 0.467820
	FUZZ s.mbond.DefaultErr = 0.584307; // fuzzed, old value = 0.646498
	FUZZ s.mbond.ParBondsEps = 0.362610; // fuzzed, old value = 0.336024
	FUZZ s.mbond.DoubleRatioTresh = 7.061581; // fuzzed, old value = 6.783767
	FUZZ s.mbond.DoubleCoef = 0.083859; // fuzzed, old value = 0.079666
	FUZZ s.mbond.DoubleMagic1 = 0.829009; // fuzzed, old value = 0.877534
	FUZZ s.mbond.DoubleMagic2 = 0.914577; // fuzzed, old value = 0.982159
	FUZZ s.mbond.DoubleTreshMin = 0.099368; // fuzzed, old value = 0.104439
	FUZZ s.mbond.DoubleTreshMax = 0.666836; // fuzzed, old value = 0.703464
	FUZZ s.mbond.MaxLen1 = 163.553226; // fuzzed, old value = 149.019639
	FUZZ s.mbond.MaxLen2 = 137.180163; // fuzzed, old value = 137.313844
	FUZZ s.mbond.MaxLen3 = 104.423302; // fuzzed, old value = 100.285129
	FUZZ s.mbond.MaxLen4 = 119.117034; // fuzzed, old value = 121.342278
	FUZZ s.mbond.MaxLen5 = 72.624597; // fuzzed, old value = 77.494396
	FUZZ s.mbond.MinLen1 = 80.577400; // fuzzed, old value = 88.886633
	FUZZ s.mbond.MinLen2 = 80.076680; // fuzzed, old value = 73.254266
	FUZZ s.mbond.mbe1 = 0.072552; // fuzzed, old value = 0.076981
	FUZZ s.mbond.mbe2 = 0.158933; // fuzzed, old value = 0.160999
	FUZZ s.mbond.mbe3 = 0.167420; // fuzzed, old value = 0.183111
	FUZZ s.mbond.mbe4 = 0.151161; // fuzzed, old value = 0.162348
	FUZZ s.mbond.mbe5 = 0.179908; // fuzzed, old value = 0.172933
	FUZZ s.mbond.mbe6 = 0.216604; // fuzzed, old value = 0.202205
	FUZZ s.mbond.mbe7 = 0.413698; // fuzzed, old value = 0.379333
	FUZZ s.mbond.mbe_def = 0.538936; // fuzzed, old value = 0.521695
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.401010; // fuzzed, old value = 0.366550
	FUZZ s.mbond.DoubleRightLengthTresh = 0.333789; // fuzzed, old value = 0.310290
	FUZZ s.mbond.TripleLeftLengthTresh = 0.265374; // fuzzed, old value = 0.253222
	FUZZ s.mbond.TripleRightLengthTresh = 0.228064; // fuzzed, old value = 0.218196
	FUZZ s.mbond.Case1LengthTresh = 92.881280; // fuzzed, old value = 91.730416
	FUZZ s.mbond.Case1Factor = 0.350847; // fuzzed, old value = 0.340534
	FUZZ s.mbond.Case2LengthTresh = 84.715577; // fuzzed, old value = 91.324005
	FUZZ s.mbond.Case2Factor = 0.671213; // fuzzed, old value = 0.702939
	FUZZ s.mbond.Case3Factor = 0.916945; // fuzzed, old value = 1.016236
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.107111; // fuzzed, old value = 0.117493
	FUZZ s.skeleton.BaseSmallErr = 0.142183; // fuzzed, old value = 0.140523
	FUZZ s.skeleton.ShortBondLen = 22; // fuzzed, old value = 23
	FUZZ s.skeleton.ShortMul = 0.324503; // fuzzed, old value = 0.314905
	FUZZ s.skeleton.MediumBondLen = 96; // fuzzed, old value = 89
	FUZZ s.skeleton.MediumMul = 0.183817; // fuzzed, old value = 0.175681
	FUZZ s.skeleton.MediumSmallErr = 0.134083; // fuzzed, old value = 0.146688
	FUZZ s.skeleton.LongBondLen = 95; // fuzzed, old value = 97
	FUZZ s.skeleton.LongMul = 0.142501; // fuzzed, old value = 0.151669
	FUZZ s.skeleton.LongSmallErr = 0.059993; // fuzzed, old value = 0.056926
	FUZZ s.skeleton.BrokenRepairFactor = 3.575462; // fuzzed, old value = 3.447391
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.062723; // fuzzed, old value = 1.059048
	FUZZ s.skeleton.BrokenRepairCoef2 = 3.258597; // fuzzed, old value = 3.354175
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.176828; // fuzzed, old value = 0.192246
	FUZZ s.skeleton.DissolveMinErr = 0.196044; // fuzzed, old value = 0.185388
	FUZZ s.skeleton.ConnectBlockS = 9.771269; // fuzzed, old value = 9.996446
	FUZZ s.skeleton.ConnectFactor = 2.512766; // fuzzed, old value = 2.335045
	FUZZ s.skeleton.JoinVerticiesConst = 0.102945; // fuzzed, old value = 0.110547
	FUZZ s.skeleton.DissolveConst = 0.101335; // fuzzed, old value = 0.098174
	FUZZ s.skeleton.Dissolve2Const = 0.207443; // fuzzed, old value = 0.193516
	FUZZ s.skeleton.Join2Const = 0.223819; // fuzzed, old value = 0.223900
	FUZZ s.skeleton.Join3Const = 0.164641; // fuzzed, old value = 0.173121
	FUZZ s.skeleton.DistTreshLimFactor = 2.059933; // fuzzed, old value = 2.128537
	FUZZ s.skeleton.SlopeFact1 = 0.086924; // fuzzed, old value = 0.088477
	FUZZ s.skeleton.SlopeFact2 = 0.166295; // fuzzed, old value = 0.164530
	FUZZ s.skeleton.ShrinkEps = 0.147193; // fuzzed, old value = 0.146069
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	
	FUZZ s.routines.Circle_GapRadiusMax = 1.240496; // fuzzed, old value = 1.141885
	FUZZ s.routines.Circle_GapAngleMax = 0.203999; // fuzzed, old value = 0.215571
	FUZZ s.routines.Circle_MinRadius = 6.317388; // fuzzed, old value = 6.428329
	FUZZ s.routines.Circle_MaxDeviation = 0.008787; // fuzzed, old value = 0.009418
	FUZZ s.routines.Circle_AsCharFactor = 1.058451; // fuzzed, old value = 0.981736
	FUZZ s.routines.Algebra_IntersectionEps = 0.012047; // fuzzed, old value = 0.011680
	FUZZ s.routines.Algebra_SameLineEps = 0.225165; // fuzzed, old value = 0.230627
	FUZZ s.routines.Approx_Eps1 = 0.970654; // fuzzed, old value = 1.060099
	FUZZ s.routines.Approx_Eps2 = 0.802213; // fuzzed, old value = 0.880628
	FUZZ s.routines.Approx_CalcLineTresh = 0.811790; // fuzzed, old value = 0.829363
	FUZZ s.routines.Contour_Eps1 = 0.988044; // fuzzed, old value = 0.956695
	FUZZ s.routines.Contour_Eps2 = 0.628422; // fuzzed, old value = 0.667673

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.561631; // fuzzed, old value = 2.543398
	FUZZ s.wbe.SingleDownAngleMax = 47.478388; // fuzzed, old value = 43.264439
	FUZZ s.wbe.SingleDownDistancesMax = 10.151706; // fuzzed, old value = 10.653749
	FUZZ s.wbe.SingleDownLengthMax = 51.932546; // fuzzed, old value = 48.948885
	FUZZ s.wbe.SomeTresh = 0.133258; // fuzzed, old value = 0.12642

	FUZZ s.wbe.SingleUpRatioEps = 1.549140; // fuzzed, old value = 1.549400
	FUZZ s.wbe.SingleUpDefCoeff = 0.283414; // fuzzed, old value = 0.268526
	FUZZ s.wbe.SingleUpIncCoeff = 0.428110; // fuzzed, old value = 0.472888
	FUZZ s.wbe.SingleUpIncLengthTresh = 34.415397; // fuzzed, old value = 37.410696
	FUZZ s.wbe.SingleUpInterpolateEps = 0.2; //0.072223; // fuzzed, old value = 0.069428
	FUZZ s.wbe.SingleUpMagicAddition = 0.206708; // fuzzed, old value = 0.225687
	FUZZ s.wbe.SingleUpS2Divisor = 1.558116; // fuzzed, old value = 1.427519
	FUZZ s.wbe.SingleUpMinATresh = 1.613488; // fuzzed, old value = 1.753776
	FUZZ s.wbe.SingleUpSquareRatio = 0.565263; // fuzzed, old value = 0.576619
	FUZZ s.wbe.SingleUpAngleTresh = 0.075684; // fuzzed, old value = 0.073703
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = false;
	FUZZ s.characters.MaximalEndpointsUse = 6; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.029738; // fuzzed, old value = 1.087160
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.195352; // fuzzed, old value = 1.220392
	FUZZ s.characters.WriteEasyFactor = 0.987334; // fuzzed, old value = 1.020712
	FUZZ s.characters.WriteVeryEasyFactor = 1.015028; // fuzzed, old value = 0.981309
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 2.996088; // fuzzed, old value = 2.918605
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.173687; // fuzzed, old value = 3.088471
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.085981; // fuzzed, old value = 0.092541
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.710389; // fuzzed, old value = 2.615505
	FUZZ s.characters.DescriptorsEvenFactorStrong = 4.133139; // fuzzed, old value = 4.122759
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.967056; // fuzzed, old value = 0.995146
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.267291; // fuzzed, old value = 0.276531
	FUZZ s.characters.X_Quality = 0.104308; // fuzzed, old value = 0.098890
	FUZZ s.characters.MinEndpointsPossible = 4; // fuzzed, old value = 4
	
	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.523496; // fuzzed, old value = 0.580034
	FUZZ s.csr.DeleteBadTriangles = 2.009109; // fuzzed, old value = 1.975545
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.501167; // fuzzed, old value = 1.576224

	FUZZ s.graph.MinimalDistTresh = 2.367689; // fuzzed, old value = 2.176209
	FUZZ s.graph.RatioSub = 0.870463; // fuzzed, old value = 0.954494
	FUZZ s.graph.RatioTresh = 0.500043; // fuzzed, old value = 0.519574

	FUZZ s.utils.SlashLineDensity = 0.430484; // fuzzed, old value = 0.391473
	FUZZ s.utils.TestPlusDensity = 0.436217; // fuzzed, old value = 0.456812
	FUZZ s.utils.TestPlusSq = 0.524485; // fuzzed, old value = 0.481167
	FUZZ s.utils.TestMinusRatio = 0.302269; // fuzzed, old value = 0.309565
	FUZZ s.utils.TestMinusDensity = 0.573194; // fuzzed, old value = 0.597853
	FUZZ s.utils.TestMinusHeightFactor = 0.858968; // fuzzed, old value = 0.828293

	FUZZ s.separator.hu_1_1 = 0.221018; // fuzzed, old value = 0.226285
	FUZZ s.separator.hu_1_2 = 0.095080; // fuzzed, old value = 0.096703
	FUZZ s.separator.hu_0_1 = 0.176212; // fuzzed, old value = 0.187522
	FUZZ s.separator.hu_1_3 = 0.101366; // fuzzed, old value = 0.093465
	FUZZ s.separator.hu_0_2 = 0.237451; // fuzzed, old value = 0.219675
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.492599; // fuzzed, old value = 0.496290
	FUZZ s.separator.capHeightMax = 1.645412; // fuzzed, old value = 1.580132
	FUZZ s.separator.gdConst = 1.544403; // fuzzed, old value = 1.419209
	FUZZ s.separator.SurfCoef = 3.243341; // fuzzed, old value = 3.408475
	FUZZ s.separator.capHeightRatio = 0.339706; // fuzzed, old value = 0.309119
	FUZZ s.separator.capHeightRatio2 = 2.128121; // fuzzed, old value = 1.941788
	FUZZ s.separator.getRatio1 = 0.944537; // fuzzed, old value = 1.012415
	FUZZ s.separator.getRatio2 = 1.302321; // fuzzed, old value = 1.300935
	FUZZ s.separator.testSlashLine1 = 2.818022; // fuzzed, old value = 2.905606
	FUZZ s.separator.testSlashLine2 = 2.530549; // fuzzed, old value = 2.772313
	FUZZ s.separator.minDensity = 0.189583; // fuzzed, old value = 0.203843
	FUZZ s.separator.maxDensity = 0.919619; // fuzzed, old value = 0.869230
	FUZZ s.separator.extCapHeightMin = 0.293347; // fuzzed, old value = 0.271218
	FUZZ s.separator.extCapHeightMax = 2.197903; // fuzzed, old value = 2.094510
	FUZZ s.separator.extRatioMin = 0.287754; // fuzzed, old value = 0.303654
	FUZZ s.separator.extRatioMax = 1.412397; // fuzzed, old value = 1.418671
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 9; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = false; // fuzzed, old value = false

	FUZZ s.labels.underlinePos = 0.411072; // fuzzed, old value = 0.377250
	FUZZ s.labels.weightUnderline = 0.272381; // fuzzed, old value = 0.290914
	FUZZ s.labels.ratioBase = 0.668668; // fuzzed, old value = 0.698448
	FUZZ s.labels.ratioWeight = 0.272612; // fuzzed, old value = 0.289062
	FUZZ s.labels.adjustDec = 1.293263; // fuzzed, old value = 1.370973
	FUZZ s.labels.adjustInc = 0.839069; // fuzzed, old value = 0.793203
	FUZZ s.labels.sameLineEps = 0.096047; // fuzzed, old value = 0.105948
	FUZZ s.labels.heightRatio = 0.775791; // fuzzed, old value = 0.724848
	FUZZ s.labels.medHeightFactor = 0.591175; // fuzzed, old value = 0.542632
	FUZZ s.labels.capHeightError = 0.518909; // fuzzed, old value = 0.480263

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.586887; // fuzzed, old value = 2.802531
	FUZZ s.lcomb.MaximalDistanceFactor = 0.573271; // fuzzed, old value = 0.594233
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.215002; // fuzzed, old value = 0.218836
	FUZZ s.lcomb.FillLabelFactor1 = 0.502944; // fuzzed, old value = 0.480044
	FUZZ s.lcomb.FillLabelFactor2 = 0.537351; // fuzzed, old value = 0.561935

	FUZZ s.p_estimator.DefaultApriority = 0.522938; // fuzzed, old value = 0.503351
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.754731; // fuzzed, old value = 0.835807
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.264833; // fuzzed, old value = 0.249019
	FUZZ s.p_estimator.LogisticScale = 1.031566; // fuzzed, old value = 1.078106
	FUZZ s.p_estimator.LogisticLocation = 0.952955; // fuzzed, old value = 0.999942
}
