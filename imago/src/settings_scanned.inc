
void updateSettingsScanned(Settings &s)
{
	s.general.UseProbablistics = false;
	s.p_estimator.UsePerimeterNormalization = true; 

	FUZZ s.separator.ext2charRatio = 1.721844; // fuzzed, old value = 1.805172
	FUZZ s.separator.SymProbabilityThresh = 0.558107; // fuzzed, old value = 0.56

	FUZZ s.molecule.LengthFactor_long = 0.352160; // fuzzed, old value = 0.345425
	FUZZ s.molecule.LengthFactor_medium = 0.401267; // fuzzed, old value = 0.404470
	FUZZ s.molecule.LengthFactor_default = 0.482321; // fuzzed, old value = 0.474696
	FUZZ s.molecule.LengthValue_long = 107.793862; // fuzzed, old value = 110.810921
	FUZZ s.molecule.LengthValue_medium = 89.909311; // fuzzed, old value = 89.450280
	FUZZ s.molecule.SpaceMultiply = 1.350377; // fuzzed, old value = 1.370527
	FUZZ s.molecule.AngleTreshold = 0.259147; // fuzzed, old value = 0.256855
	//NormalizeBySide(LengthValue_long, LongestSide);
	//NormalizeBySide(LengthValue_medium, LongestSide);

	FUZZ s.main.DissolvingsFactor = 9; // fuzzed, old value = 9
	FUZZ s.main.WarningsRecalcTreshold = 2; // fuzzed, old value = 2

	FUZZ s.estimation.CapitalHeight = 16.611869; // fuzzed, old value = 16.553142
	FUZZ s.estimation.LineThickness = 7.156527; // fuzzed, old value = 6.943756
	FUZZ s.estimation.AvgBondLength = 29.796779; // fuzzed, old value = 31.017772
	FUZZ s.estimation.AddVertexEps = 5.055912; // fuzzed, old value = 4.999934
	FUZZ s.estimation.MaxSymRatio = 1.095033; // fuzzed, old value = 1.135008
	FUZZ s.estimation.MinSymRatio = 0.289979; // fuzzed, old value = 0.302848
	FUZZ s.estimation.ParLinesEps = 0.558454; // fuzzed, old value = 0.581103
	FUZZ s.estimation.SymHeightErr = 28.536392; // fuzzed, old value = 27.732812
	FUZZ s.estimation.CapitalHeightError = 0.857533; // fuzzed, old value = 0.885080
	FUZZ s.estimation.DoubleBondDist = 21; // fuzzed, old value = 20
	FUZZ s.estimation.SegmentVerEps = 4; // fuzzed, old value = 4
	FUZZ s.estimation.CharactersSpaceCoeff = 0.365433; // fuzzed, old value = 0.381779
	FUZZ s.estimation.MaxSymbolHeightPercentsOfImage = 0.148202; // fuzzed, old value = 0.155142
	//NormalizeBySide(SymHeightErr, LongestSide);

	FUZZ s.mbond.LongBond = 101; // fuzzed, old value = 102
	FUZZ s.mbond.LongErr = 0.318531; // fuzzed, old value = 0.333770
	FUZZ s.mbond.MediumBond = 82; // fuzzed, old value = 84
	FUZZ s.mbond.MediumErr = 0.467008; // fuzzed, old value = 0.457432
	FUZZ s.mbond.DefaultErr = 0.627619; // fuzzed, old value = 0.657912
	FUZZ s.mbond.ParBondsEps = 0.340908; // fuzzed, old value = 0.337930
	FUZZ s.mbond.DoubleRatioTresh = 6.461200; // fuzzed, old value = 6.601718
	FUZZ s.mbond.DoubleCoef = 0.083382; // fuzzed, old value = 0.081201
	FUZZ s.mbond.DoubleMagic1 = 0.860304; // fuzzed, old value = 0.882326
	FUZZ s.mbond.DoubleMagic2 = 0.977216; // fuzzed, old value = 0.973134
	FUZZ s.mbond.DoubleTreshMin = 0.104760; // fuzzed, old value = 0.105704
	FUZZ s.mbond.DoubleTreshMax = 0.717559; // fuzzed, old value = 0.738936
	FUZZ s.mbond.MaxLen1 = 148.558779; // fuzzed, old value = 153.418088
	FUZZ s.mbond.MaxLen2 = 135.237630; // fuzzed, old value = 130.365677
	FUZZ s.mbond.MaxLen3 = 101.455050; // fuzzed, old value = 103.528817
	FUZZ s.mbond.MaxLen4 = 117.175670; // fuzzed, old value = 122.510428
	FUZZ s.mbond.MaxLen5 = 80.989472; // fuzzed, old value = 80.687697
	FUZZ s.mbond.MinLen1 = 91.662640; // fuzzed, old value = 90.497281
	FUZZ s.mbond.MinLen2 = 76.491748; // fuzzed, old value = 73.628036
	FUZZ s.mbond.mbe1 = 0.077466; // fuzzed, old value = 0.075109
	FUZZ s.mbond.mbe2 = 0.161516; // fuzzed, old value = 0.161531
	FUZZ s.mbond.mbe3 = 0.188653; // fuzzed, old value = 0.182512
	FUZZ s.mbond.mbe4 = 0.162364; // fuzzed, old value = 0.157249
	FUZZ s.mbond.mbe5 = 0.171136; // fuzzed, old value = 0.165944
	FUZZ s.mbond.mbe6 = 0.206076; // fuzzed, old value = 0.203663
	FUZZ s.mbond.mbe7 = 0.372578; // fuzzed, old value = 0.372383
	FUZZ s.mbond.mbe_def = 0.501411; // fuzzed, old value = 0.496090
	FUZZ s.mbond.DoubleLeftLengthTresh = 0.372657; // fuzzed, old value = 0.372862
	FUZZ s.mbond.DoubleRightLengthTresh = 0.296716; // fuzzed, old value = 0.302374
	FUZZ s.mbond.TripleLeftLengthTresh = 0.261473; // fuzzed, old value = 0.255417
	FUZZ s.mbond.TripleRightLengthTresh = 0.224651; // fuzzed, old value = 0.227683
	FUZZ s.mbond.Case1LengthTresh = 91.230233; // fuzzed, old value = 89.891611
	FUZZ s.mbond.Case1Factor = 0.355266; // fuzzed, old value = 0.368014
	FUZZ s.mbond.Case2LengthTresh = 88.573698; // fuzzed, old value = 88.640922
	FUZZ s.mbond.Case2Factor = 0.723072; // fuzzed, old value = 0.708888
	FUZZ s.mbond.Case3Factor = 1.056506; // fuzzed, old value = 1.050544
	//NormalizeBySide(LongBond, LongestSide);
	//NormalizeBySide(MediumBond, LongestSide);
	//NormalizeBySide(MaxLen1, LongestSide);
	//NormalizeBySide(MaxLen2, LongestSide);
	//NormalizeBySide(MaxLen3, LongestSide);
	//NormalizeBySide(MaxLen4, LongestSide);
	//NormalizeBySide(MaxLen5, LongestSide);
	//NormalizeBySide(MinLen1, LongestSide);
	//NormalizeBySide(MinLen2, LongestSide);

	FUZZ s.skeleton.BaseMult = 0.113355; // fuzzed, old value = 0.112319
	FUZZ s.skeleton.BaseSmallErr = 0.143047; // fuzzed, old value = 0.150004
	FUZZ s.skeleton.ShortBondLen = 23; // fuzzed, old value = 23
	FUZZ s.skeleton.ShortMul = 0.321287; // fuzzed, old value = 0.329297
	FUZZ s.skeleton.MediumBondLen = 88; // fuzzed, old value = 90
	FUZZ s.skeleton.MediumMul = 0.171538; // fuzzed, old value = 0.169881
	FUZZ s.skeleton.MediumSmallErr = 0.141399; // fuzzed, old value = 0.136375
	FUZZ s.skeleton.LongBondLen = 99; // fuzzed, old value = 97
	FUZZ s.skeleton.LongMul = 0.151645; // fuzzed, old value = 0.149354
	FUZZ s.skeleton.LongSmallErr = 0.059003; // fuzzed, old value = 0.060373
	FUZZ s.skeleton.BrokenRepairFactor = 3.319331; // fuzzed, old value = 3.493696
	FUZZ s.skeleton.BrokenRepairCoef1 = 1.029268; // fuzzed, old value = 1.052535
	FUZZ s.skeleton.BrokenRepairCoef2 = 3.261531; // fuzzed, old value = 3.138162
	FUZZ s.skeleton.BrokenRepairAngleEps = 0.202036; // fuzzed, old value = 0.197968
	FUZZ s.skeleton.DissolveMinErr = 0.191520; // fuzzed, old value = 0.185845
	FUZZ s.skeleton.ConnectBlockS = 10.418718; // fuzzed, old value = 10.027128
	FUZZ s.skeleton.ConnectFactor = 2.295041; // fuzzed, old value = 2.187095
	FUZZ s.skeleton.JoinVerticiesConst = 0.107138; // fuzzed, old value = 0.106399
	FUZZ s.skeleton.DissolveConst = 0.096498; // fuzzed, old value = 0.093640
	FUZZ s.skeleton.Dissolve2Const = 0.185350; // fuzzed, old value = 0.179050
	FUZZ s.skeleton.Join2Const = 0.234319; // fuzzed, old value = 0.246172
	FUZZ s.skeleton.Join3Const = 0.178144; // fuzzed, old value = 0.180037
	FUZZ s.skeleton.DistTreshLimFactor = 2.037179; // fuzzed, old value = 1.987990
	FUZZ s.skeleton.SlopeFact1 = 0.089529; // fuzzed, old value = 0.090321
	FUZZ s.skeleton.SlopeFact2 = 0.158778; // fuzzed, old value = 0.162888
	FUZZ s.skeleton.ShrinkEps = 0.144569; // fuzzed, old value = 0.140918
	//NormalizeBySide(ShortBondLen, LongestSide);
	//NormalizeBySide(MediumBondLen, LongestSide);
	//NormalizeBySide(LongBondLen, LongestSide);

	FUZZ s.routines.LineThick_Grid = 10; // fuzzed, old value = 10
	
	FUZZ s.routines.Circle_GapRadiusMax = 1.097124; // fuzzed, old value = 1.068727
	FUZZ s.routines.Circle_GapAngleMax = 0.207296; // fuzzed, old value = 0.210368
	FUZZ s.routines.Circle_MinRadius = 6.583221; // fuzzed, old value = 6.663209
	FUZZ s.routines.Circle_MaxDeviation = 0.009302; // fuzzed, old value = 0.009640
	FUZZ s.routines.Circle_AsCharFactor = 1.006757; // fuzzed, old value = 1.044749
	FUZZ s.routines.Algebra_IntersectionEps = 0.011660; // fuzzed, old value = 0.011934
	FUZZ s.routines.Algebra_SameLineEps = 0.220043; // fuzzed, old value = 0.228245
	FUZZ s.routines.Approx_Eps1 = 1.091801; // fuzzed, old value = 1.086365
	FUZZ s.routines.Approx_Eps2 = 0.842341; // fuzzed, old value = 0.863947
	FUZZ s.routines.Approx_CalcLineTresh = 0.867360; // fuzzed, old value = 0.833776
	FUZZ s.routines.Contour_Eps1 = 0.975154; // fuzzed, old value = 0.967737
	FUZZ s.routines.Contour_Eps2 = 0.663702; // fuzzed, old value = 0.664549

	FUZZ s.wbe.PointsCompareDist = 3; // fuzzed, old value = 3
	FUZZ s.wbe.SingleDownCompareDist = 2; // fuzzed, old value = 2
	FUZZ s.wbe.SingleDownEps = 2.580686; // fuzzed, old value = 2.491594
	FUZZ s.wbe.SingleDownAngleMax = 41.421052; // fuzzed, old value = 40.973083
	FUZZ s.wbe.SingleDownDistancesMax = 10.188181; // fuzzed, old value = 10.308659
	FUZZ s.wbe.SingleDownLengthMax = 51.130274; // fuzzed, old value = 49.904925
	FUZZ s.wbe.SingleUpRatioEps = 1.583230; // fuzzed, old value = 1.538003
	FUZZ s.wbe.SingleUpDefCoeff = 0.271136; // fuzzed, old value = 0.280094
	FUZZ s.wbe.SingleUpIncCoeff = 0.452343; // fuzzed, old value = 0.470713
	FUZZ s.wbe.SingleUpIncLengthTresh = 37.111073; // fuzzed, old value = 37.082158
	FUZZ s.wbe.SingleUpInterpolateEps = 0.070060; // fuzzed, old value = 0.067357
	FUZZ s.wbe.SingleUpMagicAddition = 0.221938; // fuzzed, old value = 0.233279
	FUZZ s.wbe.SingleUpS2Divisor = 1.422550; // fuzzed, old value = 1.477468
	FUZZ s.wbe.SingleUpMinATresh = 1.692852; // fuzzed, old value = 1.622350
	FUZZ s.wbe.SingleUpSquareRatio = 0.603343; // fuzzed, old value = 0.631715
	FUZZ s.wbe.SingleUpAngleTresh = 0.072782; // fuzzed, old value = 0.071741
	FUZZ s.wbe.SomeTresh = 0.108277; // fuzzed, old value = 0.104236
	//NormalizeBySide(SingleDownDistancesMax, LongestSide);
	//NormalizeBySide(SingleUpIncLengthTresh, LongestSide);

	s.characters.HackFor3Use = false;
	FUZZ s.characters.MaximalEndpointsUse = 7; // fuzzed, old value = 7
	FUZZ s.characters.ImpossibleToWriteDelta = 1; // fuzzed, old value = 1
	FUZZ s.characters.WriteProbablyImpossibleFactor = 1.038981; // fuzzed, old value = 1.024380
	FUZZ s.characters.WriteSurelyImpossibleFactor = 1.184305; // fuzzed, old value = 1.128651
	FUZZ s.characters.WriteEasyFactor = 1.022486; // fuzzed, old value = 1.021107
	FUZZ s.characters.WriteVeryEasyFactor = 1.010747; // fuzzed, old value = 1.009046
	FUZZ s.characters.DefaultFourierClassesUse = 3; // fuzzed, old value = 3
	FUZZ s.characters.PossibleCharacterDistanceStrong = 3.017781; // fuzzed, old value = 3.096650
	FUZZ s.characters.PossibleCharacterDistanceWeak = 3.170995; // fuzzed, old value = 3.039395
	FUZZ s.characters.PossibleCharacterMinimalQuality = 0.096058; // fuzzed, old value = 0.095338
	FUZZ s.characters.DescriptorsOddFactorStrong = 2.616859; // fuzzed, old value = 2.539117
	FUZZ s.characters.DescriptorsEvenFactorStrong = 4.018976; // fuzzed, old value = 4.094864
	FUZZ s.characters.DescriptorsOddFactorWeak = 1.047401; // fuzzed, old value = 1.030703
	FUZZ s.characters.DescriptorsEvenFactorWeak = 0.277706; // fuzzed, old value = 0.289909
	FUZZ s.characters.X_Quality = 0.102177; // fuzzed, old value = 0.1
	FUZZ s.characters.MinEndpointsPossible = 4; // fuzzed, old value = 4
	
	s.csr.UseDPApproximator = false;
	FUZZ s.csr.Dissolve = 0.559782; // fuzzed, old value = 0.543054
	FUZZ s.csr.DeleteBadTriangles = 1.988957; // fuzzed, old value = 2.047202
	FUZZ s.csr.WeakSegmentatorDist = 1; // fuzzed, old value = 1
	FUZZ s.csr.LineVectorizationFactor = 1.613840; // fuzzed, old value = 1.668864

	FUZZ s.graph.MinimalDistTresh = 2.184707; // fuzzed, old value = 2.087633
	FUZZ s.graph.RatioSub = 0.937079; // fuzzed, old value = 0.933951
	FUZZ s.graph.RatioTresh = 0.496236; // fuzzed, old value = 0.503967

	FUZZ s.utils.SlashLineDensity = 0.387595; // fuzzed, old value = 0.379186
	FUZZ s.utils.TestPlusDensity = 0.448531; // fuzzed, old value = 0.446697
	FUZZ s.utils.TestPlusSq = 0.469925; // fuzzed, old value = 0.465995
	FUZZ s.utils.TestMinusRatio = 0.310788; // fuzzed, old value = 0.312516
	FUZZ s.utils.TestMinusDensity = 0.585519; // fuzzed, old value = 0.562346
	FUZZ s.utils.TestMinusHeightFactor = 0.871132; // fuzzed, old value = 0.845162

	FUZZ s.separator.hu_1_1 = 0.224024; // fuzzed, old value = 0.226258
	FUZZ s.separator.hu_1_2 = 0.092263; // fuzzed, old value = 0.089869
	FUZZ s.separator.hu_0_1 = 0.196952; // fuzzed, old value = 0.191728
	FUZZ s.separator.hu_1_3 = 0.089943; // fuzzed, old value = 0.091566
	FUZZ s.separator.hu_0_2 = 0.226211; // fuzzed, old value = 0.218593
	FUZZ s.separator.ltFactor1 = 3; // fuzzed, old value = 3
	FUZZ s.separator.capHeightMin = 0.509979; // fuzzed, old value = 0.518936
	FUZZ s.separator.capHeightMax = 1.641508; // fuzzed, old value = 1.579394
	FUZZ s.separator.gdConst = 1.490490; // fuzzed, old value = 1.510097
	FUZZ s.separator.SurfCoef = 3.262848; // fuzzed, old value = 3.259183
	FUZZ s.separator.capHeightRatio = 0.300382; // fuzzed, old value = 0.297791
	FUZZ s.separator.capHeightRatio2 = 1.933113; // fuzzed, old value = 1.891563
	FUZZ s.separator.getRatio1 = 1.013084; // fuzzed, old value = 1.047529
	FUZZ s.separator.getRatio2 = 1.328188; // fuzzed, old value = 1.267302
	FUZZ s.separator.testSlashLine1 = 2.873089; // fuzzed, old value = 2.895111
	FUZZ s.separator.testSlashLine2 = 2.640398; // fuzzed, old value = 2.540979
	FUZZ s.separator.minDensity = 0.198133; // fuzzed, old value = 0.200926
	FUZZ s.separator.maxDensity = 0.899596; // fuzzed, old value = 0.942821
	FUZZ s.separator.extCapHeightMin = 0.269355; // fuzzed, old value = 0.280090
	FUZZ s.separator.extCapHeightMax = 2.202052; // fuzzed, old value = 2.121082
	FUZZ s.separator.extRatioMin = 0.305427; // fuzzed, old value = 0.318446
	FUZZ s.separator.extRatioMax = 1.471484; // fuzzed, old value = 1.545460
	FUZZ s.separator.minApproxSegsStrong = 4; // fuzzed, old value = 4
	FUZZ s.separator.minApproxSegsWeak = 8; // fuzzed, old value = 8
	FUZZ s.separator.specialSegmentsTreat = 4; // fuzzed, old value = 4
	FUZZ s.separator.UseVoteArray = false; // fuzzed, old value = false

	FUZZ s.labels.underlinePos = 0.386020; // fuzzed, old value = 0.371780
	FUZZ s.labels.weightUnderline = 0.290492; // fuzzed, old value = 0.280021
	FUZZ s.labels.ratioBase = 0.700501; // fuzzed, old value = 0.698628
	FUZZ s.labels.ratioWeight = 0.294784; // fuzzed, old value = 0.291219
	FUZZ s.labels.adjustDec = 1.312375; // fuzzed, old value = 1.264434
	FUZZ s.labels.adjustInc = 0.808223; // fuzzed, old value = 0.780241
	FUZZ s.labels.sameLineEps = 0.104295; // fuzzed, old value = 0.109436
	FUZZ s.labels.heightRatio = 0.701298; // fuzzed, old value = 0.693774
	FUZZ s.labels.medHeightFactor = 0.541747; // fuzzed, old value = 0.524710
	FUZZ s.labels.capHeightError = 0.465932; // fuzzed, old value = 0.483663

	FUZZ s.lcomb.MaximalSymbolRecognitionDistance = 2.795659; // fuzzed, old value = 2.822539
	FUZZ s.lcomb.MaximalDistanceFactor = 0.604300; // fuzzed, old value = 0.617346
	FUZZ s.lcomb.MaximalYDistanceFactor = 0.222588; // fuzzed, old value = 0.230155
	FUZZ s.lcomb.FillLabelFactor1 = 0.472901; // fuzzed, old value = 0.471232
	FUZZ s.lcomb.FillLabelFactor2 = 0.562545; // fuzzed, old value = 0.588245

	FUZZ s.p_estimator.DefaultApriority = 0.485358; // fuzzed, old value = 0.502855
	FUZZ s.p_estimator.ApriorProb4SymbolCase = 0.821146; // fuzzed, old value = 0.799481
	FUZZ s.p_estimator.MinRatio2ConsiderGrPr = 0.237681; // fuzzed, old value = 0.248840
	FUZZ s.p_estimator.LogisticScale = 1.059356; // fuzzed, old value = 1.017224
	FUZZ s.p_estimator.LogisticLocation = 1.051756; // fuzzed, old value = 1.066357
}
