
LabelRemoverSettings::LabelRemoverSettings()
{
	FUZZ MinCapitalHeight = 5; // fuzzed, old value = 5
	FUZZ MaxCapitalHeight = 30; // fuzzed, old value = 30
	FUZZ MinLabelChars = 3; // fuzzed, old value = 3
	FUZZ MaxLabelLines = 5;
	FUZZ HeightFactor = 1.243440; // fuzzed, old value = 1.270926
	FUZZ CenterShiftMax = 5.413963; // fuzzed, old value = 5.222350
	FUZZ PixGapX = 1; // fuzzed, old value = 1
	FUZZ PixGapY = 2; // fuzzed, old value = 2
	FUZZ MinimalDensity = 0.10;
}
