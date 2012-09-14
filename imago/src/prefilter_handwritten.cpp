/****************************************************************************
 * Copyright (C) 2009-2012 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#include <opencv2/opencv.hpp>
#include <boost/foreach.hpp>

#include "prefilter_handwritten.h"
#include "image.h"
#include "log_ext.h"
#include "exception.h"
#include "segmentator.h"
#include "output.h"
#include "convolver.h"
#include "image_utils.h"
#include "stat_utils.h"
#include "thin_filter2.h"
#include "segment.h"
#include "image_utils.h"
#include "segment_tools.h"

namespace imago
{

	class HistogramTools
	{
	public:
		HistogramTools(cv::Mat &img, float saturation = 0.0)			
		{
			_percent_saturation = saturation;
			img.copyTo(_image);
			GetStretchLimits(_lowLim, _hiLim);
		}

		~HistogramTools(void)
		{
		}

		void ImageAdjust(cv::Mat &result, bool Sigmoid = false)
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


	private:
		void GetStretchLimits(float &lowLim, float &highLim)
		{
			int channels[] = {0}, histsize[] = {256};
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

		float _lowLim, _hiLim, _percent_saturation;
		cv::Mat _image;
	};


inline static void _blur (Image &img, int radius)
{
   int w = img.getWidth(), h = img.getHeight();
   cv::Mat mat(h, w, CV_8U);
   for (int i = 0; i < w; i++)
      for (int j = 0; j < h; j++)
         mat.at<unsigned char>(j, i) = img.getByte(i, j);

   cv::Mat dst;
   radius = 2 * radius + 1;
   cv::blur(mat, dst, cv::Size(radius, radius));
   img.clear();
   ImageUtils::copyMatToImage(dst, img);
}


static void _unsharpMask (Image &img, int radius, float amount, int threshold)
{
   int  w, h;

   w = img.getWidth();
   h = img.getHeight();

   Image blur;
   blur.copy(img);
   
   _blur(blur, radius);
   
   int i, j;

   for (i = 0; i < w; i++)
      for (j = 0; j < h; j++)
      {
         unsigned char val, valc;
         val = img.getByte(i, j);
         valc = blur.getByte(i, j);

         int diff = round(val - valc);

         if (diff < threshold && diff > -threshold)
            diff = 0;

         int newval = round(val + diff * amount);
         if (newval > 255)
            newval = 255;
         if (newval < 0)
            newval = 0;

         img.getByte(i, j) = newval;
      }
}

void _removeSpots (const Settings& vars, Image &img, int validcolor, int max_size)
{
   SegmentDeque segments;
   int i, j;

   Segmentator::segmentate(img, segments, vars.prefilter.SpotsWindowSize, validcolor);

   for (SegmentDeque::iterator it = segments.begin(); it != segments.end(); ++it)
   {
      Segment *seg = *it;

      int sw = seg->getWidth();
      int sh = seg->getHeight();

      int sum_x = 0, sum_y = 0;
      int npoints = 0;

      for (i = 0; i < sw; i++)
         for (j = 0; j < sh; j++)
         {
            byte val = seg->getByte(i, j);
            if (val == 0)
            {
               sum_x += i;
               sum_y += j;
               npoints++;
            }
         }
      if (npoints > 0) // (can not be zero)
      {
         if (npoints < max_size)
         {
            #ifdef DEBUG
            fprintf(stderr, "removing segment of color %d, npoints = %d\n",
                    validcolor, npoints);
            #endif
            for (i = 0; i < sw; i++)
               for (j = 0; j < sh; j++)
               {
                  byte val = seg->getByte(i, j);
                  if (val == 0)
                     img.getByte(seg->getX() + i, seg->getY() + j) = 255 - validcolor;
               }
         }
      }
   }

   BOOST_FOREACH( Segment *s, segments )
      delete s;
   segments.clear();
}


void CombineWeakStrong(SegmentDeque &weak_segments, SegmentDeque &strong_segments, Image &image)//const Image &weakimg, const Image &strongimg
{
	logEnterFunction();

	getLogExt().append("Weak segments count", weak_segments.size());
	getLogExt().append("Strong segments count", strong_segments.size());

   image.fillWhite();

   int i, j;
   for (SegmentDeque::iterator it = strong_segments.begin();
        it != strong_segments.end(); ++it)
   {
      Segment *seg = *it;

      int sw = seg->getWidth();
      int sh = seg->getHeight();

      int sum_x = 0, sum_y = 0;
      int npoints = 0;
      bool found = false;

      for (i = 0; i < sw; i++)
      {
         for (j = 0; j < sh; j++)
         {
            byte val = seg->getByte(i, j);
            if (val == 0)
            {
               int xpos = seg->getX() + i;
               int ypos = seg->getY() + j;
               for (SegmentDeque::iterator wit = weak_segments.begin();
                    wit != weak_segments.end(); ++wit)
               {
                  Segment *wseg = *wit;
                  int wxpos = xpos - wseg->getX();
                  int wypos = ypos - wseg->getY();

                  if (wxpos >= 0 &&
                      wxpos < wseg->getWidth() &&
                      wypos >= 0 && wypos < wseg->getHeight())
                  {
                     if (wseg->getByte(wxpos, wypos) == 0)
                     {
                        int wi, wj;
                        for (wi = 0; wi < wseg->getWidth(); wi++)
                           for (wj = 0; wj < wseg->getHeight(); wj++)
                           {
                              if (wseg->getByte(wi, wj) == 0)
                                 image.getByte(wi + wseg->getX(),
                                               wj + wseg->getY()) = 0;
                           }
                        found = true;
                        break;
                     }
                  }
               }
            }
            if (found)
               break;
         }
         if (found)
            break;
      }
      if (!found)
      {
         // should not happen
         //if (debug_session)
         //   fprintf(stderr, "weak segment not found\n");
		  getLogExt().appendText("Weak segment not found");
      }
   }
}

void _wiener2(cv::Mat &mat, int size)
{
	logEnterFunction();
   
	cv::Mat dmat;
	mat.convertTo(dmat, CV_64F, 1.0/255);
	
	//calculate local mean
	cv::Mat localMean;
	cv::Mat kernel1 = cv::Mat::ones(size, size, CV_64F);
	
	cv::filter2D(dmat, localMean, -1, kernel1);
	localMean = localMean / kernel1.total();

	imago::Image im2;
	localMean.convertTo(mat, CV_8U, 255.0);
	ImageUtils::copyMatToImage(mat, im2);

	//calculate local variance
	cv::Mat localVar;
	cv::pow(dmat, 2.0, localVar);//, localVar);
	cv::filter2D(localVar, localVar, -1, kernel1);
	localVar = localVar / kernel1.total();	
	//cv::blur(localVar, localVar, cv::Size(5, 5));

	cv::Mat temp;
	cv::pow(localMean, 2.0, temp);
	//cv::subtract(localVar, temp, localVar);
	localVar = localVar - temp;
	im2.clear();
	localVar.convertTo(mat, CV_8U, 255.0);
	ImageUtils::copyMatToImage(mat, im2);
	
	//getLogExt().appendImage("Wiener local var", im2);
	//calculate noise
	cv::Scalar vnoise = cv::mean(localVar);
	double noise = 2 * vnoise[0];
	
	cv::Mat f;
	f = dmat - localMean;
	cv::Mat g;
	g = localVar - noise;
	g = cv::max(g, 0.0);

	localVar = max(localVar, noise);

	cv::divide(f, localVar, f);
	
	cv::multiply(f, g, f);
	f = f + localMean;
	f.convertTo(mat, CV_8U, 255.0);
}

int greyThresh(const Settings& vars, cv::Mat mat, bool strong)
{
	cv::Mat dmat, cmat;

	int channels[] = {0}, histsize[] = {256};
	float sranges[] = { 0, 256 };
	const float* ranges[] = { sranges };
	cv::Mat hist;
	if(strong)
	{
		mat.convertTo(dmat, CV_64F, 1.0/255);
		for(int i=0;i<dmat.cols;i++)
			for(int j=0;j<dmat.rows;j++)
				dmat.at<double>(j, i)= log( 1 + dmat.at<double>(j, i));
		dmat.convertTo(cmat, CV_8U, 255.0);
	}
	else
		cmat = mat;
	cv::calcHist(&cmat, 1, channels, cv::Mat(),  hist, 1, histsize, ranges);
	double cumsum[256]; 
	double sum = 0;

	cv::Scalar ssum = cv::sum(hist);
	sum = ssum[0];
  
	for(int i=0;i<256;i++)
	{
		float val=hist.at<float>(i);
		cumsum[i] = val/sum;
	}
	cv::Mat omega(1, 256, CV_64F);
	double acumsum = 0, acumsum2 = 0;
	for(int i=0;i<256;i++)
	{
		double value = cumsum[i];
		acumsum += value;
		acumsum2 += value * (i + 1);
		omega.at<double>(i) = acumsum;
		cumsum[i] = acumsum2;
	}
	double mu_t = cumsum[255];

	//sigma_b_squared = (mu_t * omega - mu).^2 ./ (omega .* (1 - omega));

	cv::Mat sigma_b_squared(1, 256, CV_64F, cumsum);
	cv::pow((mu_t*omega - sigma_b_squared), 2.0, sigma_b_squared); 
	cv::multiply(omega, 1-omega, omega);
	divide(sigma_b_squared, omega, sigma_b_squared);
	double min, max;
	cv::Point maxLoc;
	cv::minMaxLoc(sigma_b_squared, &min, &max, NULL, &maxLoc);
	double tmax = max + 1;
	std::vector<int> bins;
	do{
		bins.push_back(maxLoc.x);
		sigma_b_squared.at<double>(maxLoc.x) = 0;
		cv::minMaxLoc(sigma_b_squared, &min, &tmax, NULL, &maxLoc);
	} while(tmax < max * vars.prefilter.GreyTreshMaxF && tmax > max * vars.prefilter.GreyTreshMinF);

	std::vector<int>::iterator it;
	int cnt = 0;
	for(it = bins.begin();it != bins.end(); it++)
		cnt += *it;
	cnt = cnt / bins.size();
	return cnt;
}


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


void prefilterKernel(const Settings& vars, const Image &raw, Image &image, const PrefilterParams& p)
{
	logEnterFunction();

	int w = raw.getWidth();
	int h = raw.getHeight();
   
	cv::Mat mat, rmat;
	Image img, cimg;
   
	int maxside = (w < h) ? h : w;
	
	img.copy(raw);
	
	if (p.logSteps)
		getLogExt().appendImage("Source image", img);
	
	//convert to gray scale
	ImageUtils::copyImageToMat(img, mat);
	bool reduced = false;
	cv::Mat matred((mat.rows+1)/2, (mat.cols+1)/2, CV_8U);
	if (p.reduceImage)
	{
		if(maxside > vars.prefilter.ReduceImageDim)
		{
			//Pydramid reduce
			cv::pyrDown(mat, matred);
			reduced = true;
		}
		else
		{
			if(p.strongThresh)
			{
				cv::GaussianBlur(mat, matred, cv::Size(vars.prefilter.GaussianKernelSize, vars.prefilter.GaussianKernelSize),
					   1, 1, cv::BORDER_REPLICATE);
			}
			else
			{
				cv::bilateralFilter(mat, matred, vars.prefilter.Bilateral_d, vars.prefilter.BilateralSpace, vars.estimation.dynamic.LineThickness);
			}
		}
	}
	else
	{
		mat.copyTo(matred);
	}
   
	if(getLogExt().loggingEnabled())
	{
		ImageUtils::copyMatToImage(matred, cimg);
		if (p.logSteps)
			getLogExt().appendImage("Pyr down", cimg);
	}

	//make edges stronger
	//min area = 1296, coeff =  5.7870e-005
	cv::Mat crmat;
	/*if(matred.total() >= 51840)
	{
		int bsize = matred.total() *  5.7870e-005;
		cv::blur(matred, crmat, cv::Size(bsize, bsize));
		cv::subtract(matred, crmat, crmat);
		cv::add(crmat, matred, matred);
	}*/

	if(getLogExt().loggingEnabled())// debug_session)
	{
		cimg.clear();
		ImageUtils::copyMatToImage(matred, cimg);
		if (p.logSteps)
		getLogExt().appendImage("Stronger edges", cimg);
	}

	//build structuring element
	//min area = 36, coefficient = 3.4722e-004
	int minA = 8640*3;
	if(matred.total() > (size_t)minA )
	{
		int ssize = (int)(matred.total() * 3.4722e-004 / 3.0); // round?
		ssize = ssize < vars.prefilter.MinSSize ? vars.prefilter.MinSSize : ssize;
		cv::Mat strel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(ssize, ssize));
		matred = 255 - matred;
		//perform tophat transformation
		cv::morphologyEx(matred, matred, cv::MORPH_TOPHAT, strel, cv::Point(-1, -1), 1, cv::BORDER_REPLICATE);
		matred = 255 - matred;
	}

	img.clear();
	ImageUtils::copyMatToImage(matred, img);
	//if(strongThresh)
	_unsharpMask(img, vars.prefilter.UnsharpSize, (float)vars.prefilter.UnsharpAmount, 0);
	ImageUtils::copyImageToMat(img, matred);
	img.clear();
   
	if(getLogExt().loggingEnabled()) // debug_session)
	{
		cimg.clear();
		ImageUtils::copyMatToImage(matred, cimg);
		if (p.logSteps)
			getLogExt().appendImage("Tophat", cimg);
	}

	//Compute histogram limits to adjust the image
	HistogramTools ht(matred);
	ht.ImageAdjust(matred);

	if (getLogExt().loggingEnabled())// debug_session)
	{
		cimg.clear();
		ImageUtils::copyMatToImage(matred, cimg);
		if (p.logSteps)
			getLogExt().appendImage("Imadjust", cimg);
	}

	//wiener filter
	if(!p.strongThresh)
	{
		int blockS = (int)vars.estimation.dynamic.LineThickness;
		blockS = (blockS % 2) == 0 ? blockS+1 : blockS;
		_wiener2(matred, blockS);
	}
	else
	{
		_wiener2(matred, vars.prefilter.WienerSize);
	}
	
	cimg.clear();
	ImageUtils::copyMatToImage(matred, cimg);


	if (p.logSteps)
		getLogExt().appendImage("Wiener", cimg);

	
	//sharp edges
		imago::Convolver cfilt(cimg);
		cfilt.initSharp();
		cfilt.apply();
	
	/*_unsharpMask(cimg, 4, 2, 0);
	_copyImageToMat(cimg, matred);
	*/

	ImageUtils::copyImageToMat(cimg, matred);
	
	if(reduced)
		cv::pyrUp(matred, mat);
	else
		mat = matred;
	int thresh = greyThresh(vars, mat, true);
	int wthresh = greyThresh(vars, mat, false);

	if(p.strongThresh)
		wthresh = round(vars.prefilter.TreshFactor*thresh + (1.0-vars.prefilter.TreshFactor)*wthresh);

	if (p.binarizeImage)
	{
		//Perform binary thresholding using Otsu procedure
		//thresh = thresh - 16 > 0 ? thresh - 16 : 0; 
		if(p.adaptiveThresh)
		{
			//HistogramTools ht2(mat);
			//ht2.ImageAdjust(mat, true);
			int blockS = (int)vars.estimation.dynamic.LineThickness;
			blockS = (blockS % 2) == 0 ? blockS +1:blockS;
			cv::adaptiveThreshold(mat, mat, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, blockS*vars.prefilter.BlockSAdaptive, vars.prefilter.BlockSAdaptive);
		}
		else
			cv::threshold(mat, mat, wthresh, 255, cv::THRESH_BINARY);//cv::THRESH_OTSU|
	}

	cv::Mat strel;
	if(reduced)
	{
		strel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	}
	else
	{
		uchar dstruct[] = {0,0,0,
							0,1,1,
							0,1,1}; 
		strel = cv::Mat(3, 3, CV_8U, dstruct);//cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
	}

	cimg.clear();
	ImageUtils::copyMatToImage(mat, cimg);

	if (p.logSteps)
		getLogExt().appendImage("After pref", cimg);

	image.copy(cimg);

	//LPRINT(0, "Filtering done");
}

bool isSplash(const Settings& vars, Segment *s, double lineSize)
{
	Image img;
	if(s->getWidth() < lineSize && s->getHeight() < lineSize)
		return true;
	s->extract(0, 0, s->getWidth(), s->getHeight(), img);
	double ls = ImageUtils::estimateLineThickness(img, vars.routines.LineThick_Grid);
	if(ls > vars.prefilter.MaxLSSplah * lineSize || ls < 1.0)
		return true;
	return false;
}

bool SegCompare (Segment *i, Segment *j) 
{ 
	int area1 = i->getWidth() * i->getHeight();
	int area2 = j->getWidth() * j->getHeight();
	return (area1 < area2); 
}

bool prefilterHandwritten(Settings& vars, Image &image )
{
   logEnterFunction();

   Image raw, cimg;
   
   raw.copy(image);
   cimg.copy(image);
   int w = raw.getWidth();
   int h = raw.getHeight();
   int imMean = raw.mean();

   image.clear();

   PrefilterParams p;
   p.strongThresh = true;
   prefilterKernel(vars, raw, image, p);

   double lineThickness = ImageUtils::estimateLineThickness(image, vars.routines.LineThick_Grid);

   if(lineThickness < 1)
	   throw ImagoException("Image prefiltering failed");

   vars.estimation.dynamic.LineThickness = lineThickness;
   
   SegmentDeque segs, psegs;
   imago::Segmentator::segmentate(image, segs, (int)(std::min(lineThickness, 3.0)));
   SegmentDeque::iterator sit;
   int xmin=raw.getWidth(), xmax=0, 
	   ymin=raw.getHeight(), ymax=0;
   
   std::sort(segs.begin(), segs.end(), SegCompare); 
   
   int maxArea = segs[segs.size() -1]->getWidth() * segs[segs.size() -1]->getHeight();
   int maxDensity = (int)(maxArea * segs[segs.size() -1]->density());
   float dists = 0;
   Vec2d center(0, 0);
   int accumSize = 0;
   for(sit = segs.begin(); sit != segs.end(); sit++)
   {
	  Segment *s = *sit;
	   int sx = s->getX();
	   int sy = s->getY();
	   int sw = s->getWidth();
	   int sh = s->getHeight();

	   if(sx == 0 || sy == 0 || (sx + sw) >= w || (sy + sh) >= h || isSplash(vars, s, lineThickness))
	   {
		   imago::ImageUtils::cutSegment(cimg, *s, true, imMean);
		   continue;
	   }

	   Image p;
	   cimg.extract(sx, sy, sx + sw, sy + sh, p); 
	   
	   Image cs(p.getWidth(), p.getHeight());
	   //_prefilterInternal3(p, cs, cr); 

		if(xmin > sx)
			xmin = sx;
		if(xmax < (sx + sw))
			xmax = (sx + sw);
		if(ymin > sy)
			ymin = sy;
		if(ymax < (sy + sh))
			ymax = (sy +sh);
		double sarea = (s->getHeight()*s->getWidth()*s->getDensity()) / maxDensity;
		if(sarea > vars.prefilter.SAreaTresh)
		{
			center.add( s->getCenter());
			accumSize++;
		}
		psegs.push_back(s);
   }

   center.scale((double)(1.0/accumSize));

   IntVector distsFromCenter;
   SegmentDeque tsegs;
   int dis;
   for(sit = psegs.begin();sit != psegs.end(); sit++)
   {
	   Segment *s = *sit;
	   dis = (int)Vec2d::distance(center, s->getCenter());
	   //int dweight = maxArea / (s->getWidth() * s->getHeight());
	   distsFromCenter.push_back(dis);
	   tsegs.push_back(s);
   }

   std::sort(distsFromCenter.begin(), distsFromCenter.end());
   int medInd = distsFromCenter.size();
   int median = medInd % 2 != 0? distsFromCenter[medInd>>1]:(distsFromCenter[medInd>>1] + distsFromCenter[(medInd>>1) - 1])/2;

   IntVector deviations;
   for(size_t k=0;k<distsFromCenter.size();k++)
   {
	   int value = distsFromCenter[k] - median;
	   if(value < 0)
		   value = -value;
	   deviations.push_back(value);
   }
   std::sort(deviations.begin(), deviations.end());
   int mad = medInd % 2 != 0? deviations[medInd>>1]:(deviations[medInd>>1] + deviations[(medInd>>1) - 1])/2;

   psegs.clear();
   double koeff = vars.prefilter.MagicCoeff;

   if (std::max(image.getWidth(), image.getHeight()) < 300) koeff *= 2.0;

   for(sit = tsegs.begin();sit != tsegs.end(); sit++)
   {
	   Segment *s = *sit;
	   double dis = Vec2d::distance(center, s->getCenter());
	   double density = s->getWidth() * s->getHeight() * s->getDensity();
	   double dweight = (double)maxDensity / density;
	   bool condition = (lineThickness*lineThickness*4 > density) && dis > distsFromCenter[3*distsFromCenter.size()/4];
	   double est =  condition ? dis*dweight : dis;
	   
	   getLogExt().appendSegment("Segment", *s);
	   getLogExt().append("est", est);
	   double lessthan = (median + koeff*mad);
	   getLogExt().append("shall be less than", lessthan);

	   if(est < lessthan)
		   psegs.push_back(s);
   }


   SegmentDeque::reverse_iterator rsit;

    for(rsit = psegs.rbegin(); rsit != psegs.rend(); rsit++)
	{
		Segment *s = *rsit;
		getLogExt().appendSegment("Segment", *s);
	}

   cimg.clear();
   cimg.copy(raw);

   Image cs(cimg.getWidth(), cimg.getHeight());
   
   PrefilterParams p2;
   //p2.reduceImage = false;

   prefilterKernel(vars, cimg, cs, p2);

	getLogExt().appendImage("After _prefilterInternal3", cs);
	
   
	SegmentDeque weak_segments;
   Segmentator::segmentate(cs, weak_segments);

   cimg.clear();
   cimg.init(cs.getWidth(), cs.getHeight());

   if (vars.prefilter.MakeSegmentsConnected)
   {
    for(rsit = weak_segments.rbegin(); rsit != weak_segments.rend(); rsit++)
	{		
		Segment *s = *rsit;		
		SegmentTools::makeSegmentConnected(*s, raw, 0.5);		
	}
   }

	if(psegs.size() > 0)
		CombineWeakStrong(weak_segments, psegs, cimg);
	else
		cimg.copy(cs);

   getLogExt().appendImage("Pref3 final", cimg);
   
   BOOST_FOREACH(Segment *s, weak_segments)
	   delete s;
   BOOST_FOREACH( Segment *s, segs )
      delete s;
   segs.clear();
   psegs.clear();
   weak_segments.clear();
   image.copy(cimg);

   return true;
}
	

}

