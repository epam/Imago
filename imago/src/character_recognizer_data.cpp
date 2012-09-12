#include "character_recognizer_data.h"

namespace imago
{

	void CharacterRecognizerData::LoadData( std::istream &in )
	{
		int fonts_count, letters_count;
		in >> _count >> letters_count;
		_classes.resize(letters_count);
		for (int i = 0; i < letters_count; i++)
		{
			SymbolClass &cls = _classes[i];
			in >> cls.sym >> fonts_count;
			_mapping[cls.sym] = i;
			cls.shapes.resize(fonts_count);
			for (int j = 0; j < fonts_count; j++)
			{
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
