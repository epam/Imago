#ifndef _prefilter_h_
#define _prefilter_h_

#include <vector>
namespace imago
{
   class Image;

   void prefilterFile(const char *filename, Image &image, const CharacterRecognizer &cr);
   void prefilterFile(const std::vector<unsigned char> &data, Image &image, const CharacterRecognizer &cr );
   void prefilterImage( Image &image, const CharacterRecognizer &cr );
   bool isCircle (Image &seg);
}
#endif /* _prefilter_h_ */
