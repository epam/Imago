#include "recognition_tree.h"
#include "log_ext.h"

namespace imago
{
	CharacterRecognitionEntry::CharacterRecognitionEntry(const RecognitionDistance& src)
	{
		alternatives = src;
		selected_character = src.getBest();
	}
}