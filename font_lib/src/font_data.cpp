#include "character_recognizer_data.h"
namespace imago
{
	CharacterRecognizerData::CharacterRecognizerData()
	{
		_loaded = false;
		_count = 0;
	}

   void CharacterRecognizerData::initializeHandwrittenFont()
   {
      #include "ff.font.inc"
      _loaded = true;
   }

   FontRecognizerData::FontRecognizerData()
   {
	   _count = 0;
   }

	#define FONT_INIT(ch)                                 \
   do                                                 \
   {                                                  \
      _symbols.push_back(FontItem());                 \
      FontItem *fi = &(_symbols[_symbols.size() - 1]);\
      const char *str = #ch;                          \
      fi->sym = str[0];                               \
      double *arr_ptr;                                \
      arr_ptr = descr_##ch;                           \
      _mapping[fi->sym] = _symbols.size() - 1;        \
      fi->features.descriptors.resize(2 * _count);    \
      fi->features.inner_contours_count = -1;         \
      for (int i = 0; i < _count * 2; i++)            \
         fi->features.descriptors[i] = arr_ptr[i];    \
   } while (0);

	void FontRecognizerData::initializeArial()
	{
	   _mapping.resize(255);
		#include "arial.font.inc"
	}

	void FontRecognizerData::initializeArialBold()
	{
	   _mapping.resize(255);
		#include "arial_bold.font.inc"
	}

	void FontRecognizerData::initializeSerif()
	{
	   _mapping.resize(255);
		#include "serif.font.inc"
	}


}
