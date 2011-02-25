#include "character_recognizer.h"
namespace imago
{
   void CharacterRecognizer::_loadBuiltIn()
   {
      #ifdef IMAGO_FONT_BUILT_IN
      #include "TEST4.font.inc"
      _loaded = true;
      #endif
   }
}
