#ifndef _prefilter_h_
#define _prefilter_h_

#include <vector>
namespace imago
{
   class Image;

   void prefilterFile(const char *filename, Image &image);
   void prefilterFile(const std::vector<unsigned char> &data, Image &image);
   bool isCircle (Image &seg);
}
#endif /* _prefilter_h_ */
