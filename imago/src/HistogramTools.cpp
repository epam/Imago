
#include "HistogramTools.h"
#include "image.h"
#include <opencv/cv.h>


using namespace imago;

HistogramTools::HistogramTools(cv::Mat &img)
{
	img.copyTo(_image);
	GetStretchLimits(_lowLim, _hiLim);
}

void HistogramTools::ImageAdjust(cv::Mat &result)
{
	unsigned char lmap[256];
	for(int i=0;i<256;i++)
		lmap[i] = ( i - 256 * _lowLim)/( _hiLim - _lowLim);

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
   double min = 0, max=1.0;
   
   _lowLim=0, _hiLim=255;
   for(int i=0;i<256;i++)
	   if(cumsum[i] > min)
	   {
		   _lowLim = i;
		   break;
	   }

	for(int i=0;i<256;i++)
		if(cumsum[i] >= max)
		{
			_hiLim = i;
			break;
		}
	_lowLim /= 255;
	_hiLim /= 255;
}