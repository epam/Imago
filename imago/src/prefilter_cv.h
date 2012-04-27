#pragma once

namespace imago
{
	class Image;
	
	// returns true if result image is binarized
	// may change some pixels inensity if image is already binarized
	bool isBinarized(Image &image);

	// returns true if image was modified
	bool resampleImage(Image &image);   
  
	// filters image using cv adaptive filtering and cross-correlation
	void prefilterCV(Image& raw);
}
