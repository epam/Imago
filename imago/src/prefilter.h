#ifndef _prefilter_h_
#define _prefilter_h_

#include <vector>

namespace imago
{
   class Image;

   struct PrefilterParams
   {
	   bool logSteps;
	   bool adaptiveThresh;
	   bool strongThresh;
	   bool reduceImage;
	   bool binarizeImage;
	   PrefilterParams()
	   {
		   logSteps = reduceImage = binarizeImage = true;
		   adaptiveThresh = strongThresh = false;
	   }
   };

   void prefilterKernel( const Image &raw, Image &image, const PrefilterParams& p = PrefilterParams());

   bool isAlreadyBinarized(Image &image);
   bool resampleImage(Image &image, int MAX_RESOLUTION = 1560);

   void prefilterFile(const char *filename, Image &image, const CharacterRecognizer &cr);
   void prefilterPngData(const std::vector<unsigned char> &data, Image &image, const CharacterRecognizer &cr );
   void prefilterImage( Image &image, const CharacterRecognizer &cr );
   
   void prefilterCV(Image& raw);

   void _copyMatToImage (Image &img, const cv::Mat &mat);

   bool isCircle (Image &seg);
   int estimateLineThickness(Image &bwimg, int grid = 10);
}
#endif /* _prefilter_h_ */
