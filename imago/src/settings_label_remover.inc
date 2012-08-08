
LabelRemoverSettings::LabelRemoverSettings()
{
	FUZZ MinCapitalHeight = 5; // fuzzed, old value = 5
	FUZZ MaxCapitalHeight = 33; // fuzzed, old value = 32
	FUZZ MinLabelChars = 3; // fuzzed, old value = 3
	FUZZ MaxLabelLines = 5; // fuzzed, old value = 5
	FUZZ HeightFactor = 1.186464; // fuzzed, old value = 1.216931
	FUZZ CenterShiftMax = 5.885325; // fuzzed, old value = 5.967248
	FUZZ PixGapX = 1; // fuzzed, old value = 1
	FUZZ PixGapY = 2; // fuzzed, old value = 2
	FUZZ MinimalDensity = 0.106531; // fuzzed, old value = 0.105470
}
