#pragma once

#include "recognition_distance.h"
#include <vector>

namespace imago
{	
	class CharacterRecognitionEntry
	{
	public:
		char selected_character;
		RecognitionDistance alternatives;

		CharacterRecognitionEntry(const RecognitionDistance& src);
	};

	class CharactersRecognitionGroup : public std::vector<CharacterRecognitionEntry>
	{
	};
}
