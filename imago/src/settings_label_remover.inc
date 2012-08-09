
LabelRemoverSettings::LabelRemoverSettings()
{
	FUZZ MinCapitalHeight = 5; // fuzzed, old value = 5
	FUZZ MaxCapitalHeight = 35; // fuzzed, old value = 33
	FUZZ MinLabelChars = 3; // fuzzed, old value = 3
	FUZZ MaxLabelLines = 5; // fuzzed, old value = 5
	FUZZ HeightFactor = 1.228994; // fuzzed, old value = 1.173160
	FUZZ CenterShiftMax = 5.646999; // fuzzed, old value = 5.508128
	FUZZ PixGapX = 1; // fuzzed, old value = 1
	FUZZ PixGapY = 2; // fuzzed, old value = 2
	FUZZ MinimalDensity = 0.102187; // fuzzed, old value = 0.105676
}
