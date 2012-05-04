
#include "HistogramTools.h"
#include "image.h"
#include <opencv/cv.h>


using namespace imago;

HistogramTools::HistogramTools(cv::Mat &img, float saturation)
{
	_percent_saturation = saturation;
	img.copyTo(_image);
	GetStretchLimits(_lowLim, _hiLim);
}

void HistogramTools::ImageAdjust(cv::Mat &result, bool Sigmoid)
{
	unsigned char lmap[256];
	byte lIn = (byte)(_lowLim * 255);
	byte hIn = (byte)(_hiLim * 255);

	for(int i = 0;i<256;i++)
		lmap[i] = i > hIn ? hIn : (i < lIn ? lIn:i);

	for(int i=0;i<256;i++)
	{
		
		lmap[i] = (byte)(( lmap[i] - lIn)/( _hiLim - _lowLim));
		if(Sigmoid)
		{
			float val = i/255.0f;
			if(val<_lowLim)
				lmap[i] = 0;
			else
				if(val<(_hiLim - _lowLim)/2)
					lmap[i] = (byte)(2.0f*((val - _lowLim)/(_hiLim - _lowLim))*((val - _lowLim)/(_hiLim - _lowLim))*255.0f);
				else 
					if(val<_hiLim)
						lmap[i] =(byte)((1.0f- 2.0f*((val - _hiLim)/(_hiLim - _lowLim))*((val - _hiLim)/(_hiLim - _lowLim)))*255.0f);
					else
						lmap[i] = 255;
		}
	}
	for(int i=0;i<result.cols;i++)
   {
	   for (int j = 0;j<result.rows;j++)
	   {
		   uchar value = result.at<uchar>(j, i);
		   result.at<uchar>(j, i) = lmap[value];
	   }
   }
}


void HistogramTools::GetStretchLimits(float &lowLim, float &hiLim)
{
	int channels[] = {0},
	   histsize[] = {256};
   float sranges[] = { 0, 256 };
   const float* ranges[] = { sranges };
   cv::Mat hist, matred = _image;

   float low_sat = _percent_saturation;
   float hi_sat = 1.0f - low_sat;
   
   if(hi_sat < low_sat)
	   throw ImagoException("Saturation level is not correct");

   cv::calcHist(&matred, 1, channels, cv::Mat(),  hist, 1, histsize, ranges);
   double cumsum[256]; 
   double sum = 0;
   for(int i=0;i<256;i++)
   {
	   sum+=hist.at<float>(i);
	   cumsum[i] = sum;
   }
   for(int i=0;i<256;i++)
	   cumsum[i]/=sum;
   double min = low_sat, max=hi_sat;
   
   _lowLim=0, _hiLim=255;
   for(int i=0;i<256;i++)
	   if(cumsum[i] > min)
	   {
		   _lowLim = (float)i;
		   break;
	   }

	for(int i=0;i<256;i++)
		if(cumsum[i] >= max)
		{
			_hiLim = (float)i;
			break;
		}

	if( _hiLim - _lowLim < 0.01)
	{
		_lowLim = 0;
		_hiLim = 255;
	}
	_lowLim /= 255;
	_hiLim /= 255;
}