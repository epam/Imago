
LabelRemoverSettings::LabelRemoverSettings()
{
	FUZZ MinCapitalHeight = 5; // fuzzed, old value = 5
	FUZZ MaxCapitalHeight = 31; // fuzzed, old value = 31
	FUZZ MinLabelChars = 3; // fuzzed, old value = 3
	FUZZ MaxLabelLines = 5; // fuzzed, old value = 5
	FUZZ HeightFactor = 1.248731; // fuzzed, old value = 1.228989
	FUZZ CenterShiftMax = 5.895397; // fuzzed, old value = 6.060404
	FUZZ PixGapX = 1; // fuzzed, old value = 1
	FUZZ PixGapY = 2; // fuzzed, old value = 2
	FUZZ MinimalDensity = 0.101090; // fuzzed, old value = 0.100196
}
