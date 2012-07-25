
LabelRemoverSettings::LabelRemoverSettings()
{
	FUZZ MinCapitalHeight = 5; // fuzzed, old value = 5
	FUZZ MaxCapitalHeight = 32; // fuzzed, old value = 31
	FUZZ MinLabelChars = 3; // fuzzed, old value = 3
	FUZZ MaxLabelLines = 5; // fuzzed, old value = 5
	FUZZ HeightFactor = 1.216931; // fuzzed, old value = 1.248731
	FUZZ CenterShiftMax = 5.967248; // fuzzed, old value = 5.895397
	FUZZ PixGapX = 1; // fuzzed, old value = 1
	FUZZ PixGapY = 2; // fuzzed, old value = 2
	FUZZ MinimalDensity = 0.105470; // fuzzed, old value = 0.101090
}
