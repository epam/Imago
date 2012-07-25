
void updateSettingsScanned(Settings &s)
{
	s.general.UseProbablistics = false;
	s.p_estimator.UsePerimeterNormalization = true; 

	FUZZ s.separator.ext2charRatio = 1.769256; // fuzzed, old value = 1.721844
	FUZZ s.separator.SymProbabilityThresh = 0.582931; // fuzzed, old value = 0.558107

	FUZZ s.molecule.LengthFactor_long = 0.351291; // fuzzed, old value = 0.352160
	FUZZ s.molecule.LengthFactor_medium = 0.404442; // fuzzed, old value = 0.401267
	FUZZ s.molecule.LengthFactor_default = 0.470038; // fuzzed, old value = 0.482321
	FUZZ s.molecule.LengthValue_long = 109.107607; // fuzzed, old value = 107.793862
	FUZZ s.molecule.LengthValue_medium = 93.887277; // fuzzed, old value = 89.909311
	FUZZ s.molecule.SpaceMultiply = 1.337344; // fuzzed, old value = 1.350377
	FUZZ s.molecule.AngleTreshold = 0.270375; // fuzzed, old value = 0.259147
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 15.871465; // fuzzed, old value = 16.611869
	FUZZ s.estimation.LineThickness = 7.153437; // fuzzed, old value = 7.156527
	FUZZ s.estimation.AvgBondLength = 30.459016; // fuzzed, old value = 29.796779
	FUZZ s.estimation.AddVertexEps = 5.030846; // fuzzed, old value = 5.055912
	FUZZ s.estimation.MaxSymRatio = 1.079929; // fuzzed, old value = 1.095033
	FUZZ s.estimation.MinSymRatio = 0.300973; // fuzzed, old value = 0.289979
	FUZZ s.estimation.ParLinesEps = 0.555687; // fuzzed, old value = 0.558454
	FUZZ s.estimation.SymHeightErr = 27.777021; // fuzzed, old value = 28.536392
	FUZZ s.estimation.CapitalHeightError = 0.840118; // fuzzed, old value = 0.857533
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 21
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.354178; // fuzzed, old value = 0.365433
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.154351; // fuzzed, old value = 0.148202
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 99; // fuzzed, old value = 101
	FUZZ s.mbond.LongErr = 0.330418; // fuzzed, old value = 0.318531
	FUZZ s.mbond.MediumBond = 83; // fuzzed, old value = 82
	FUZZ s.mbond.MediumErr = 0.467820; // fuzzed, old value = 0.467008
	FUZZ s.mbond.DefaultErr = 0.646498; // fuzzed, old value = 0.627619
	FUZZ s.mbond.ParBondsEps = 0.336024; // fuzzed, old value = 0.340908
	FUZZ s.mbond.DoubleRatioTresh = 6.783767; // fuzzed, old value = 6.461200
	FUZZ s.mbond.DoubleCoef = 0.079666; // fuzzed, old value = 0.083382
	FUZZ s.mbond.DoubleMagic1 = 0.877534; // fuzzed, old value = 0.860304
	FUZZ s.mbond.DoubleMagic2 = 0.982159; // fuzzed, old value = 0.977216
	FUZZ s.mbond.DoubleTreshMin = 0.104439; // fuzzed, old value = 0.104760
	FUZZ s.mbond.DoubleTreshMax = 0.703464; // fuzzed, old value = 0.717559
	FUZZ s.mbond.MaxLen1 = 149.019639; // fuzzed, old value = 148.558779
	FUZZ s.mbond.MaxLen2 = 137.313844; // fuzzed, old value = 135.237630
	FUZZ s.mbond.MaxLen3 = 100.285129; // fuzzed, old value = 101.455050
	FUZZ s.mbond.MaxLen4 = 121.342278; // fuzzed, old value = 117.175670
	FUZZ s.mbond.MaxLen5 = 77.494396; // fuzzed, old value = 80.989472
	FUZZ s.mbond.MinLen1 = 88.886633; // fuzzed, old value = 91.662640
	FUZZ s.mbond.MinLen2 = 73.254266; // fuzzed, old value = 76.491748
	FUZZ s.mbond.mbe1 = 0.076981; // fuzzed, old value = 0.077466
	FUZZ s.mbond.mbe2 = 0.160999; // fuzzed, old value = 0.161516
	FUZZ s.mbond.mbe3 = 0.183111; // fuzzed, old value = 0.188653
	FUZZ s.mbond.mbe4 = 0.162348; // fuzzed, old value = 0.162364
	FUZZ s.mbond.mbe5 = 0.172933; // fuzzed, old value = 0.171136
	FUZZ s.mbond.mbe6 = 0.202205; // fuzzed, old value = 0.206076
	FUZZ s.mbond.mbe7 = 0.379333; // fuzzed, old value = 0.372578
	FUZZ s.mbond.mbe_def = 0.521695; // fuzzed, old value = 0.501411
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.366550; // fuzzed, old value = 0.372657
	FUZZ s.mbond.DoubleRightLengthTresh = 0.310290; // fuzzed, old value = 0.296716
	FUZZ s.mbond.TripleLeftLengthTresh = 0.253222; // fuzzed, old value = 0.261473
	FUZZ s.mbond.TripleRightLengthTresh = 0.218196; // fuzzed, old value = 0.224651
	FUZZ s.mbond.Case1LengthTresh = 91.730416; // fuzzed, old value = 91.230233
	FUZZ s.mbond.Case1Factor = 0.340534; // fuzzed, old value = 0.355266
	FUZZ s.mbond.Case2LengthTresh = 91.324005; // fuzzed, old value = 88.573698
	FUZZ s.mbond.Case2Factor = 0.702939; // fuzzed, old value = 0.723072
	FUZZ s.mbond.Case3Factor = 1.016236; // fuzzed, old value = 1.056506
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.117493; // fuzzed, old value = 0.113355
	FUZZ s.skeleton.BaseSmallErr = 0.140523; // fuzzed, old value = 0.143047
	FUZZ s.skeleton.ShortBondLen = 23; // fuzzed, old value = 23
	FUZZ s.skeleton.ShortMul = 0.314905; // fuzzed, old value = 0.321287
	FUZZ s.skeleton.MediumBondLen = 89; // fuzzed, old value = 88
	FUZZ s.skeleton.MediumMul = 0.175681; // fuzzed, old value = 0.171538
	FUZZ s.skeleton.MediumSmallErr = 0.146688; // fuzzed, old value = 0.141399
	FUZZ s.skeleton.LongBondLen = 97; // fuzzed, old value = 99
	FUZZ s.skeleton.LongMul = 0.151669; // fuzzed, old value = 0.151645
	FUZZ s.skeleton.LongSmallErr = 0.056926; // fuzzed, old value = 0.059003
	FUZZ s.skeleton.BrokenRepairFactor = 3.447391; // fuzzed, old value = 3.319331
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.059048; // fuzzed, old value = 1.029268
	FUZZ s.skeleton.BrokenRepairCoef2 = 3.354175; // fuzzed, old value = 3.261531
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.192246; // fuzzed, old value = 0.202036
	FUZZ s.skeleton.DissolveMinErr = 0.185388; // fuzzed, old value = 0.191520
	FUZZ s.skeleton.ConnectBlockS = 9.996446; // fuzzed, old value = 10.418718
	FUZZ s.skeleton.ConnectFactor = 2.335045; // fuzzed, old value = 2.295041
	FUZZ s.skeleton.JoinVerticiesConst = 0.110547; // fuzzed, old value = 0.107138
	FUZZ s.skeleton.DissolveConst = 0.098174; // fuzzed, old value = 0.096498
	FUZZ s.skeleton.Dissolve2Const = 0.193516; // fuzzed, old value = 0.185350
	FUZZ s.skeleton.Join2Const = 0.223900; // fuzzed, old value = 0.234319
	FUZZ s.skeleton.Join3Const = 0.173121; // fuzzed, old value = 0.178144
	FUZZ s.skeleton.DistTreshLimFactor = 2.128537; // fuzzed, old value = 2.037179
	FUZZ s.skeleton.SlopeFact1 = 0.088477; // fuzzed, old value = 0.089529
	FUZZ s.skeleton.SlopeFact2 = 0.164530; // fuzzed, old value = 0.158778
	FUZZ s.skeleton.ShrinkEps = 0.146069; // fuzzed, old value = 0.144569
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	
	FUZZ s.routines.Circle_GapRadiusMax = 1.141885; // fuzzed, old value = 1.097124
	FUZZ s.routines.Circle_GapAngleMax = 0.215571; // fuzzed, old value = 0.207296
	FUZZ s.routines.Circle_MinRadius = 6.428329; // fuzzed, old value = 6.583221
	FUZZ s.routines.Circle_MaxDeviation = 0.009418; // fuzzed, old value = 0.009302
	FUZZ s.routines.Circle_AsCharFactor = 0.981736; // fuzzed, old value = 1.006757
	FUZZ s.routines.Algebra_IntersectionEps = 0.011680; // fuzzed, old value = 0.011660
	FUZZ s.routines.Algebra_SameLineEps = 0.230627; // fuzzed, old value = 0.220043
	FUZZ s.routines.Approx_Eps1 = 1.060099; // fuzzed, old value = 1.091801
	FUZZ s.routines.Approx_Eps2 = 0.880628; // fuzzed, old value = 0.842341
	FUZZ s.routines.Approx_CalcLineTresh = 0.829363; // fuzzed, old value = 0.867360
	FUZZ s.routines.Contour_Eps1 = 0.956695; // fuzzed, old value = 0.975154
	FUZZ s.routines.Contour_Eps2 = 0.667673; // fuzzed, old value = 0.663702

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.543398; // fuzzed, old value = 2.580686
	FUZZ s.wbe.SingleDownAngleMax = 43.264439; // fuzzed, old value = 41.421052
	FUZZ s.wbe.SingleDownDistancesMax = 10.653749; // fuzzed, old value = 10.188181
	FUZZ s.wbe.SingleDownLengthMax = 48.948885; // fuzzed, old value = 51.130274
	FUZZ s.wbe.SingleUpRatioEps = 1.549400; // fuzzed, old value = 1.583230
	FUZZ s.wbe.SingleUpDefCoeff = 0.268526; // fuzzed, old value = 0.271136
	FUZZ s.wbe.SingleUpIncCoeff = 0.472888; // fuzzed, old value = 0.452343
	FUZZ s.wbe.SingleUpIncLengthTresh = 37.410696; // fuzzed, old value = 37.111073
	FUZZ s.wbe.SingleUpInterpolateEps = 0.069428; // fuzzed, old value = 0.070060
	FUZZ s.wbe.SingleUpMagicAddition = 0.225687; // fuzzed, old value = 0.221938
	FUZZ s.wbe.SingleUpS2Divisor = 1.427519; // fuzzed, old value = 1.422550
	FUZZ s.wbe.SingleUpMinATresh = 1.753776; // fuzzed, old value = 1.692852
	FUZZ s.wbe.SingleUpSquareRatio = 0.576619; // fuzzed, old value = 0.603343
	FUZZ s.wbe.SingleUpAngleTresh = 0.073703; // fuzzed, old value = 0.072782
	FUZZ s.wbe.SomeTresh = 0.112642; // fuzzed, old value = 0.108277
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = false;
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.087160; // fuzzed, old value = 1.038981
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.220392; // fuzzed, old value = 1.184305
	FUZZ s.characters.WriteEasyFactor = 1.020712; // fuzzed, old value = 1.022486
	FUZZ s.characters.WriteVeryEasyFactor = 0.981309; // fuzzed, old value = 1.010747
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 2.918605; // fuzzed, old value = 3.017781
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.088471; // fuzzed, old value = 3.170995
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.092541; // fuzzed, old value = 0.096058
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.615505; // fuzzed, old value = 2.616859
	FUZZ s.characters.DescriptorsEvenFactorStrong = 4.122759; // fuzzed, old value = 4.018976
	FUZZ s.characters.DescriptorsOddFactorWeak = 0.995146; // fuzzed, old value = 1.047401
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.276531; // fuzzed, old value = 0.277706
	FUZZ s.characters.X_Quality = 0.098890; // fuzzed, old value = 0.102177
	FUZZ s.characters.MinEndpointsPossible = 4; // fuzzed, old value = 4
	
	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.580034; // fuzzed, old value = 0.559782
	FUZZ s.csr.DeleteBadTriangles = 1.975545; // fuzzed, old value = 1.988957
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.576224; // fuzzed, old value = 1.613840

	FUZZ s.graph.MinimalDistTresh = 2.176209; // fuzzed, old value = 2.184707
	FUZZ s.graph.RatioSub = 0.954494; // fuzzed, old value = 0.937079
	FUZZ s.graph.RatioTresh = 0.519574; // fuzzed, old value = 0.496236

	FUZZ s.utils.SlashLineDensity = 0.391473; // fuzzed, old value = 0.387595
	FUZZ s.utils.TestPlusDensity = 0.456812; // fuzzed, old value = 0.448531
	FUZZ s.utils.TestPlusSq = 0.481167; // fuzzed, old value = 0.469925
	FUZZ s.utils.TestMinusRatio = 0.309565; // fuzzed, old value = 0.310788
	FUZZ s.utils.TestMinusDensity = 0.597853; // fuzzed, old value = 0.585519
	FUZZ s.utils.TestMinusHeightFactor = 0.828293; // fuzzed, old value = 0.871132

	FUZZ s.separator.hu_1_1 = 0.226285; // fuzzed, old value = 0.224024
	FUZZ s.separator.hu_1_2 = 0.096703; // fuzzed, old value = 0.092263
	FUZZ s.separator.hu_0_1 = 0.187522; // fuzzed, old value = 0.196952
	FUZZ s.separator.hu_1_3 = 0.093465; // fuzzed, old value = 0.089943
	FUZZ s.separator.hu_0_2 = 0.219675; // fuzzed, old value = 0.226211
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.496290; // fuzzed, old value = 0.509979
	FUZZ s.separator.capHeightMax = 1.580132; // fuzzed, old value = 1.641508
	FUZZ s.separator.gdConst = 1.419209; // fuzzed, old value = 1.490490
	FUZZ s.separator.SurfCoef = 3.408475; // fuzzed, old value = 3.262848
	FUZZ s.separator.capHeightRatio = 0.309119; // fuzzed, old value = 0.300382
	FUZZ s.separator.capHeightRatio2 = 1.941788; // fuzzed, old value = 1.933113
	FUZZ s.separator.getRatio1 = 1.012415; // fuzzed, old value = 1.013084
	FUZZ s.separator.getRatio2 = 1.300935; // fuzzed, old value = 1.328188
	FUZZ s.separator.testSlashLine1 = 2.905606; // fuzzed, old value = 2.873089
	FUZZ s.separator.testSlashLine2 = 2.772313; // fuzzed, old value = 2.640398
	FUZZ s.separator.minDensity = 0.203843; // fuzzed, old value = 0.198133
	FUZZ s.separator.maxDensity = 0.869230; // fuzzed, old value = 0.899596
	FUZZ s.separator.extCapHeightMin = 0.271218; // fuzzed, old value = 0.269355
	FUZZ s.separator.extCapHeightMax = 2.094510; // fuzzed, old value = 2.202052
	FUZZ s.separator.extRatioMin = 0.303654; // fuzzed, old value = 0.305427
	FUZZ s.separator.extRatioMax = 1.418671; // fuzzed, old value = 1.471484
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = false; // fuzzed, old value = false

	FUZZ s.labels.underlinePos = 0.377250; // fuzzed, old value = 0.386020
	FUZZ s.labels.weightUnderline = 0.290914; // fuzzed, old value = 0.290492
	FUZZ s.labels.ratioBase = 0.698448; // fuzzed, old value = 0.700501
	FUZZ s.labels.ratioWeight = 0.289062; // fuzzed, old value = 0.294784
	FUZZ s.labels.adjustDec = 1.370973; // fuzzed, old value = 1.312375
	FUZZ s.labels.adjustInc = 0.793203; // fuzzed, old value = 0.808223
	FUZZ s.labels.sameLineEps = 0.105948; // fuzzed, old value = 0.104295
	FUZZ s.labels.heightRatio = 0.724848; // fuzzed, old value = 0.701298
	FUZZ s.labels.medHeightFactor = 0.542632; // fuzzed, old value = 0.541747
	FUZZ s.labels.capHeightError = 0.480263; // fuzzed, old value = 0.465932

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.802531; // fuzzed, old value = 2.795659
	FUZZ s.lcomb.MaximalDistanceFactor = 0.594233; // fuzzed, old value = 0.604300
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.218836; // fuzzed, old value = 0.222588
	FUZZ s.lcomb.FillLabelFactor1 = 0.480044; // fuzzed, old value = 0.472901
	FUZZ s.lcomb.FillLabelFactor2 = 0.561935; // fuzzed, old value = 0.562545

	FUZZ s.p_estimator.DefaultApriority = 0.503351; // fuzzed, old value = 0.485358
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.835807; // fuzzed, old value = 0.821146
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.249019; // fuzzed, old value = 0.237681
	FUZZ s.p_estimator.LogisticScale = 1.078106; // fuzzed, old value = 1.059356
	FUZZ s.p_estimator.LogisticLocation = 0.999942; // fuzzed, old value = 1.051756
}
