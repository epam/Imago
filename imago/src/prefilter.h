#ifndef _prefilter_h_
#define _prefilter_h_

#include <vector>
namespace imago
{
   class Image;

   void prefilterFile(const char *filename, Image &image, const CharacterRecognizer &cr);
   void prefilterPngData(const std::vector<unsigned char> &data, Image &image, const CharacterRecognizer &cr );
   void prefilterImage( Image &image, const CharacterRecognizer &cr );
   bool isCircle (Image &seg);
   int EstimateLineThickness(Image &bwimg, int grid = 10);
}
#endif /* _prefilter_h_ */
