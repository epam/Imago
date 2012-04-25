#pragma once

namespace imago
{
	class Image;
	
	// returns true if result image is binarized
	// may change some pixels inensity if image is already binarized
	bool isBinarized(Image &image);

	// returns true if image was modified
	bool resampleImage(Image &image);   
  
	// returns false if image cann't be correctly filtered
	bool prefilterCV(Image& raw);
}
