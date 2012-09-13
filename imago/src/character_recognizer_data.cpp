#include "character_recognizer_data.h"
#include <algorithm>

namespace imago
{
	CharacterRecognizerData::CharacterRecognizerData()
	{
		ClearData();
	}

	void CharacterRecognizerData::ClearData()
	{
		_loaded = false;
		_mapping.resize(255, -1);
		_count = 0;
		_classes.clear();
	}

	void CharacterRecognizerData::LoadData( std::istream &in )
	{
		int letters_count;
		in >> _count >> letters_count;
		
		for (int u = 0; u < letters_count; u++)
		{
			char symbol;
			int fonts_count;
			in >> symbol >> fonts_count;

			int index = -1;

			if (_mapping[symbol] == -1)
			{
				_classes.push_back(SymbolClass());
				index = _classes.size() - 1; // last item
				_mapping[symbol] = index;
			}
			else
			{
				index = _mapping[symbol];
			}


			SymbolClass &cls = _classes[index];
			cls.sym = symbol;
						
			for (int t = 0; t < fonts_count; t++)
			{
				cls.shapes.push_back(SymbolFeatures());
				int j = cls.shapes.size() - 1;
				SymbolFeatures &sf = cls.shapes[j];

				in >> sf.inner_contours_count;
				sf.descriptors.resize(2 * _count);
				for (int k = 0; k < 2 * _count; k++)
				in >> sf.descriptors[k];

				sf.inner_descriptors.resize(sf.inner_contours_count);
				for (int k = 0; k < sf.inner_contours_count; k++)
				{
					sf.inner_descriptors[k].resize(2 * _count);
					for (int l = 0; l < 2 * _count; l++)
						in >> sf.inner_descriptors[k][l];
				}
			}
		}

		_loaded = true;
	}
}
