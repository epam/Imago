#pragma once

namespace imago
{
	// most generic image interface
	class ImageInterface
	{
	public:
		// check intenisty (or something) value is passed some bounds
		virtual bool isFilled(int x, int y) const = 0;

		// get raw intensity value 0..255
		virtual unsigned char getIntensity(int x, int y) const = 0; 

		// get the image dimensions
		virtual int width() const = 0;
		virtual int height() const = 0;
	};
}

