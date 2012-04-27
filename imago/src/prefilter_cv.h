#pragma once
#include "image_interface.h"
#include "image.h"

namespace imago
{
	// required for prefilterCV implementation
	class ImgAdapter :  public ImageInterface
	{
	public:
		ImgAdapter(const Image& _raw, const Image& _bin) : raw(_raw), bin(_bin)
		{
		}

		virtual bool isFilled(int x, int y) const
		{
			return bin.getByte(x,y) == 0;
		}		
	
		virtual unsigned char getIntensity(int x, int y) const
		{
			return raw.getByte(x,y);
		}

		virtual int width() const 
		{
			return std::min(raw.getWidth(), bin.getWidth());
		}
	
		virtual int height() const
		{
			return std::min(raw.getHeight(), bin.getHeight());
		}
	private:
		const Image& raw;
		const Image& bin;
	};
	
	// returns true if result image is binarized
	// may change some pixels inensity if image is already binarized
	bool isBinarized(Image &image);

	// returns true if image was modified
	bool resampleImage(Image &image);   
  
	// filters image using cv adaptive filtering and cross-correlation
	void prefilterCV(Image& raw);
}
