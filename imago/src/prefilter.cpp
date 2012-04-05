#include <opencv/cv.h>

#include <boost/foreach.hpp>

#include "image.h"
#include "log.h"
#include "current_session.h"
#include "log_ext.h"
#include "exception.h"
#include "segmentator.h"
#include "output.h"
#include "convolver.h"
#include "image_utils.h"
#include "binarizer.h"
#include "stat_utils.h"
#include "thin_filter2.h"
#include "segment.h"
#include "HistogramTools.h"
#include "prefilter.h"

namespace imago
{

struct _AngRadius
{
   float ang;
   float radius;
};

static int _cmp_ang (const void *p1, const void *p2)
{
   const _AngRadius &f1 = *(const _AngRadius *)p1;
   const _AngRadius &f2 = *(const _AngRadius *)p2;

   if (f1.ang < f2.ang)
      return -1;
   return 1;
}

static void _blur (Image &img, int radius);
   
static void _blur2 (Image &img, int radius)
{
   Image res;
   res.emptyCopy(img);
   
   int w = img.getWidth(), h = img.getHeight();
   int r = radius, val;
   radius = radius * 2 + 1;

   std::vector<int> div(255 * radius);
   for (int i = 0; i < 255 * radius; ++i)
      div[i] = i / radius;
   
   byte *row = img.getData();
   byte *dst = res.getData();
   for (int y = 0; y < h; ++y)
   {
      for (int x = 0; x < w; ++x)
      {
         val = 0;
         for (int i = -r; i <= r; ++i)
         {
            int ind = x + i;
            if (ind < 0)
               ind = 0;
            if (ind >= w)
               ind = w - 1;
            
            val += row[ind];
         }
         //val /= radius;
         
         *dst = div[val];
         ++dst;
      }
      row += w;
   }

   res.rotate90();
   img.rotate90();
   
   row = res.getData();
   dst = img.getData();
   for (int y = 0; y < w; ++y)
   {
      for (int x = 0; x < h; ++x)
      {
         val = 0;
         for (int i = -r; i <= r; ++i)
         {
            int ind = x + i;
            if (ind < 0)
               ind = 0;
            if (ind >= h)
               ind = h - 1;
            
            val += row[ind];
         }
         //val /= radius;
         
         *dst = div[val];
         ++dst;
      }
      row += h;
   }

   img.rotate90(false);
}

static void _unsharpMask (Image &img, int radius, float amount, int threshold)
{
   int  w, h;

   w = img.getWidth();
   h = img.getHeight();

   Image blur;
   blur.copy(img);
   
   TIME(_blur(blur, radius), "Blur");
   //TIME(_blur2(blur, radius), "Blur");
   
   int i, j;

   for (i = 0; i < w; i++)
      for (j = 0; j < h; j++)
      {
         unsigned char val, valc;
         val = img.getByte(i, j);
         valc = blur.getByte(i, j);

         int diff = (int)val - (int)valc;

         if (diff < threshold && diff > -threshold)
            diff = 0;

         int newval = (int)val + diff * amount;
         if (newval > 255)
            newval = 255;
         if (newval < 0)
            newval = 0;

         img.getByte(i, j) = newval;
      }
}


inline static void _copyMatToImage (Image &img, const cv::Mat &mat)
{
   int w = mat.cols;
   int h = mat.rows;

   img.init(w, h);
   int i, j;

   for (i = 0; i < w; i++)
      for (j = 0; j < h; j++)
         img.getByte(i, j) = mat.at<unsigned char>(j, i);
}

inline static void _copyImageToMat ( const Image &img, cv::Mat &mat)
{
   int w = img.getWidth();
   int h = img.getHeight();

   mat.create(h, w, CV_8U);
   int i, j;

   for (i = 0; i < w; i++)
      for (j = 0; j < h; j++)
         mat.at<unsigned char>(j, i) = img.getByte(i, j);
}

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
   _copyMatToImage(img, dst);
}
/*
inline static void _blur (Image &img, int radius)
{
   int w = img.getWidth(), h = img.getHeight();
   Image blur;
   blur.copy(img);
   double bias = 1.0 / (4 * radius * radius + 4 * radius + 1);
   byte *dblur = blur.getData();
   for (int y = 0; y < h; y++)
   {
      for (int x = 0; x < w; x++)
      {
         double total = 0;
         for (int k = -radius; k <= radius; k++)
         {
            for (int l = -radius; l <= radius; l++)
            {
               int xx = x + l, yy = y + k;
               if (xx >= 0 && xx < w && yy >= 0 && yy < h)
                  total += dblur[yy * w + xx];
               else
                  total += dblur[y * w + x];
            }
         }
         total *= bias;

         if (total < 0)
            total = 0;
         if (total > 255)
            total = 255;

         img.getByte(x, y) = (byte)total;
      }
   }
}*/


void _removeSpots (Image &img, int validcolor, int max_size)
{
   SegmentDeque segments;
   int i, j;

   Segmentator::segmentate(img, segments, 3, validcolor);

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
         /*float avg_x = sum_x / (float)npoints;
         float avg_y = sum_y / (float)npoints;
         float radius = 0;
         float disp = 0;

         for (i = 0; i < sw; i++)
            for (j = 0; j < sh; j++)
            {
               byte val = seg->getByte(i, j);
               if (val == 0)
               {
                  float sqrdist = (i - avg_x) * (i - avg_x) + (j - avg_y) * (j - avg_y);
                  if (radius < sqrt(sqrdist))
                     radius = sqrt(sqrdist);
                  disp += sqrdist;
               }
            }
            disp /= npoints;*/
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



static void _prefilterInternal( const Image &raw, Image &image, const CharacterRecognizer &_cr )
{
	logEnterFunction();

	getLogExt().appendImage("Source image", image);

   int w = raw.getWidth();
   int h = raw.getHeight();
   LPRINT(0, "loaded image %d x %d", w, h);
   int maxside = (w < h) ? h : w;
   int n = maxside / 800;
   //bool debug_session = getSettings()["DebugSession"];
   Image img;

   if (n > 1)
   {
		  cv::Mat mat;
		  _copyImageToMat(raw, mat);
		  LPRINT(0, "resizing down %d times", n);
		  cv::Mat dst;
		  cv::resize(mat, dst, cv::Size(), 1.0 / n, 1.0 / n);
		  _copyMatToImage(img, dst);

	   //if (debug_session)
		 // ImageUtils::saveImageToFile(img, "output/01_after_subsampling.png");
	   
	   getLogExt().appendImage("After subsampling", img);
   }
   else
      img.copy(raw);

   {
      LPRINT(0, "blurring");
      _blur(img, 1);

      //if (debug_session)
      //   ImageUtils::saveImageToFile(img, "output/02_after_blur.png");

	  getLogExt().appendImage("After blurring", img);
   }


   w = img.getWidth();
   h = img.getHeight();

   {
      int avg = img.mean();

      //if (debug_session)
      //   fprintf(stderr, "average brightness = %d\n", avg);

	  getLogExt().append("Average brightness", avg);
      
      if (avg < 155)
      {
         LPRINT(0, "adding constant gray");
         byte *data = img.getData();
         for (int i = 0; i < w * h; i++)
            data[i] += 155 - avg;
      }
   }

   /*{
      LPRINT(0, "normalization");
      PIX *newpix = pixBackgroundNorm(pix, NULL, NULL, 200, 200, 0, 40000, 164, 2, 2);
      if (newpix == NULL)
         throw Exception("background norm failed");
      //pixDestroy(&pix);
      pix = newpix;
      }*/
   //if (debug_session)
   //   ImageUtils::saveImageToFile(img, "output/03_after_normalization.png");
   getLogExt().appendImage("After normalization", img);

   Image weakimg;
   weakimg.copy(img);

   {
      LPRINT(0, "unsharp mask (strong)");

      _unsharpMask(img, 8, 4, 0);
      
      //if (debug_session)
      //   ImageUtils::saveImageToFile(img, "output/04_after_strong_unsharp_mask.png");
	  getLogExt().appendImage("After unsharp mask", img);
   }

   {
      Binarizer b(img, 50); //32
      b.apply();

      //if (debug_session)
      //   ImageUtils::saveImageToFile(img, "output/05_after_strong_binarization.png");
	  getLogExt().appendImage("After strong binarization", img);
   }

   Image strongimg;
   strongimg.copy(img);
   _removeSpots(strongimg, 0, 10);

   //if (debug_session)
   //   ImageUtils::saveImageToFile(img, "output/06_after_spots_removal.png");
   getLogExt().appendImage("After spots removal", img);

   {
      LPRINT(0, "unsharp mask (weak)");
      _unsharpMask(weakimg, 10, 8, 0); //10 12
      
      //if (debug_session)
      //   ImageUtils::saveImageToFile(weakimg, "output/07_after_weak_unsharp_mask.png");
	  getLogExt().appendImage("After weak unsharp mask", weakimg);
   }

   {
      Binarizer b(weakimg, 75);
      b.apply();
      //if (debug_session)
      //   ImageUtils::saveImageToFile(weakimg, "output/08_after_weak_binarization.png");
	  getLogExt().appendImage("After weak binarization", weakimg);
   }

   SegmentDeque weak_segments;
   SegmentDeque strong_segments;
   Segmentator::segmentate(weakimg, weak_segments);
   Segmentator::segmentate(strongimg, strong_segments);

   //if (debug_session)
   //{
   //   fprintf(stderr, "%d weak segments\n", weak_segments.size());
   //   fprintf(stderr, "%d strong segments\n", strong_segments.size());
   //}
   getLogExt().append("Weak segments count", weak_segments.size());
   getLogExt().append("Strong segments count", strong_segments.size());

   image.init(w, h);
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
		 getLogExt().appendText("Weak segment not found!");
      }
   }

   BOOST_FOREACH( Segment *s, weak_segments )
      delete s;

   BOOST_FOREACH( Segment *s, strong_segments )
      delete s;

   weak_segments.clear();
   strong_segments.clear();

   _removeSpots(image, 255, 2);

   //OrientationFinder of(_cr);
   //LMARK;
   //int rotation = of.findFromImage(image);
   ////int rotation = 1;
   //LPRINT(1, "OrientationFinder");

   //if (rotation != 0)
   //{
   //   LPRINT(0, "Found rotation %d", 90 * (4 - rotation));
   //   switch (rotation)
   //   {
   //      case 1:
   //         image.rotate90();
   //         break;
   //      case 2:
   //         image.rotate180();
   //         break;
   //      case 3:
   //         image.rotate90(false);
   //   }

   //}

   LPRINT(0, "Filtering done");

   //if (debug_session)
   //   ImageUtils::saveImageToFile(image, "output/09_final.png");
   getLogExt().appendImage("Final image", image);

}

int EstimateLineThickness(Image &bwimg, int grid)
{
	int w = bwimg.getWidth();
	int h = bwimg.getHeight();
	int d = grid; // 10 pixel grid

	IntVector lthick;

	if(w < d)
		d = std::max<int>(w >>1, 1) ; 
	{
		int startseg = -1;
		for(int i = 0; i < w ; i += d)
		{
			for(int j = 0; j < h; j++)
			{
				byte val = bwimg.getByte(i, j);
				if(val == 0 && (startseg == -1))
					startseg = j;
				if((val > 0 || j==(h-1)) && startseg != -1)
				{
					lthick.push_back(j - startseg + 1);
					startseg = -1;
				}
			}
		}
	}

	if(h > d)
		d = grid;
	else
		d = std::max<int>(h >>1, 1) ; 

	{
		int startseg = -1;
		for(int j = 0; j< h; j+=d)
		{
			for(int i = 0; i < w; i++)
			{
				byte val = bwimg.getByte(i, j);
				if(val == 0 && (startseg == -1))
					startseg = i;
				if((val > 0 || i==(w-1)) && startseg != -1)
				{
					lthick.push_back(i - startseg + 1);
					startseg = -1;
				}
			}
		}
	}
	std::sort(lthick.begin(), lthick.end());
	double thickness = 0;
	if(lthick.size() > 0)
		thickness = StatUtils::interMean(lthick.begin(), lthick.end());
	
	return thickness;
}

void CombineWeakStrong(SegmentDeque &weak_segments, SegmentDeque &strong_segments, Image &image)//const Image &weakimg, const Image &strongimg
{
	logEnterFunction();
   //bool debug_session = getSettings()["DebugSession"];

   //if (debug_session)
   //{
   //   fprintf(stderr, "%d weak segments\n", weak_segments.size());
   //   fprintf(stderr, "%d strong segments\n", strong_segments.size());
   //}
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

void _prefilterInternal2( Image &img )
{
   /*cv::Mat mat;
   _copyImageToMat(img, mat);

   mat = 255 - mat;
   cv::Mat background, strel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(46, 46));

   cv::morphologyEx(mat, mat, cv::MORPH_TOPHAT, strel);
   mat = 255 - mat;

   //cv::GaussianBlur(mat, mat, cv::Size(3, 3), 9.0);
   cv::GaussianBlur(mat, mat, cv::Size(5, 5), 5.0);
   //cv::GaussianBlur(mat, mat, cv::Size(5, 5), 5.0);
   
   cv::medianBlur(mat, mat, 3.0);
   
   cv::threshold(mat, mat, 0, 255, cv::THRESH_OTSU);

   img.clear();
   _copyMatToImage(img, mat);*/
}

void _wiener2(cv::Mat &mat)
{
	logEnterFunction();
   //bool debug_session = getSettings()["DebugSession"];
   
	cv::Mat dmat;
	mat.convertTo(dmat, CV_64F, 1.0/255);
	
	//calculate local mean
	cv::Mat localMean;
	double ones[] = {1, 1, 1, 1, 1, 1, 1,
					 1, 1, 1, 1, 1, 1, 1,
					 1, 1, 1, 1, 1, 1, 1,
					 1, 1, 1, 1, 1, 1, 1,
					 1, 1, 1, 1, 1, 1, 1,
					 1, 1, 1, 1, 1, 1, 1,
					 1, 1, 1, 1, 1, 1, 1};
	cv::Mat kernel1(7, 7, CV_64F, ones);// = cv::Mat::ones(5, 5, CV_32F);
	cv::filter2D(dmat, localMean, -1, kernel1);
	localMean = localMean / kernel1.total();

	imago::Image im2;
	localMean.convertTo(mat, CV_8U, 255.0);
   _copyMatToImage(im2, mat);
   //if (debug_session)
   //   ImageUtils::saveImageToFile(im2, "output/pref3_wienerLocalMean.png");
   getLogExt().appendImage("Wiener local mean", im2);
	//cv::blur(dmat, localMean, cv::Size(3, 3));

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
   _copyMatToImage(im2, mat);
   //if (debug_session)
    //  ImageUtils::saveImageToFile(im2, "output/pref3_wienerLocalVar.png");
   getLogExt().appendImage("Wiener local var", im2);
	//calculate noise
	cv::Scalar vnoise = cv::mean(localVar);
	double noise = 2 * vnoise[0];
	
	/*for(int i=0;i<localVar.cols;i++)
		for(int j=0;j<localVar.rows;j++)
		noise += localVar.at<double>(j, i);
	noise /= (localVar.cols*localVar.rows);*/
	
	cv::Mat f;
	f = dmat - localMean;
	//g = localVar - noise; 
	cv::Mat g;
	g = localVar - noise;
//g = max(g, 0);
	g = cv::max(g, 0.0);

//localVar = max(localVar, noise);
	localVar = max(localVar, noise);

//f = f ./ localVar;
	cv::divide(f, localVar, f);
	
//f = f .* g;
	cv::multiply(f, g, f);
//f = f + localMean;
	//cv::add(f, localMean, f);
	f = f + localMean;
	f.convertTo(mat, CV_8U, 255.0);
}

int greyThresh(cv::Mat mat, bool strong)
{
	cv::Mat dmat, cmat;
	


	int channels[] = {0},
	   histsize[] = {256};
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
   }while(tmax < max * 1.01 && tmax > max *0.99);

   std::vector<int>::iterator it;
   int cnt = 0;
   for(it = bins.begin();it != bins.end(); it++)
	   cnt += *it;
   cnt = cnt / bins.size();
   return cnt;
}

void doWiener(Image &img)
{
	logEnterFunction();

	cv::Mat mat;

	_unsharpMask(img, 7, 4, 0);
	_copyImageToMat(img, mat);
   	HistogramTools ht(mat);
	ht.ImageAdjust(mat);
	_wiener2(mat);
	
	img.clear();
	_copyMatToImage(img, mat);
}

void _prefilterInternal3( const Image &raw, Image &image, const CharacterRecognizer &_cr, bool adaptiveThresh=false, bool strongThresh=false)
{
	logEnterFunction();

	int w = raw.getWidth();
	int h = raw.getHeight();
   
	LPRINT(0, "loaded image %d x %d", w, h);

	cv::Mat mat, rmat;
	Image img, cimg;
	//bool debug_session = getSettings()["DebugSession"];

   
	int maxside = (w < h) ? h : w;
	int n = maxside / 800;

	img.copy(raw);
	getLogExt().appendImage("Source image", img);
	
	//convert to gray scale
	_copyImageToMat(img, mat);
	bool reduced = false;
   cv::Mat matred((mat.rows+1)/2, (mat.cols+1)/2, CV_8U);
   if(maxside > 300)
   {
   //Pydramid reduce
	cv::pyrDown(mat, matred);
	reduced = true;
   }
   else
	   if(strongThresh)
		cv::GaussianBlur(mat, matred, cv::Size(5, 5), 1, 1, cv::BORDER_REPLICATE);
	   else
	   {
		   double lt = getSettings()["LineThickness"];
		   cv::bilateralFilter(mat, matred, 5, 20, lt);
	   }

   
   if(getLogExt().loggingEnabled()) // debug_session)
   {
	   _copyMatToImage(cimg, matred);
	   //ImageUtils::saveImageToFile(cimg, "output/pref3_pyrDown.png");
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
	   _copyMatToImage(cimg, matred);
	   //ImageUtils::saveImageToFile(cimg, "output/pref3_strongerEdges.png");
	   getLogExt().appendImage("Stronger edges", cimg);
   }

   //build structuring element
   //min area = 36, coefficient = 3.4722e-004
   int minA = 8640*3;
   if(matred.total() > (size_t)minA )
   {
	   int ssize = matred.total() * 3.4722e-004 / 3;
	   ssize = ssize < 20 ? 20 : ssize;
	   cv::Mat strel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(ssize, ssize));
	   matred = 255 - matred;
	   //perform tophat transformation
	   cv::morphologyEx(matred, matred, cv::MORPH_TOPHAT, strel, cv::Point(-1, -1), 1, cv::BORDER_REPLICATE);
	   matred = 255 - matred;
   }

    img.clear();
   _copyMatToImage(img, matred);
   //if(strongThresh)
   _unsharpMask(img, 7, 4, 0);
   _copyImageToMat(img, matred);
   img.clear();
   
   if(getLogExt().loggingEnabled()) // debug_session)
   {
	   cimg.clear();
	   _copyMatToImage(cimg, matred);
	   //ImageUtils::saveImageToFile(cimg, "output/pref3_tophat.png");
	   getLogExt().appendImage("Tophat", cimg);
   }

   //Compute histogram limits to adjust the image
   HistogramTools ht(matred);
   ht.ImageAdjust(matred);

   if (getLogExt().loggingEnabled())// debug_session)
	{
		cimg.clear();
		_copyMatToImage(cimg, matred);
		//ImageUtils::saveImageToFile(cimg, "output/pref3_imadjust.png");
		getLogExt().appendImage("Imadjust", cimg);
	}

	//wiener filter
	_wiener2(matred);
	
	cimg.clear();
	_copyMatToImage(cimg, matred);


	//if (debug_session)
	//{
	//	ImageUtils::saveImageToFile(cimg, "output/pref3_wiener.png");
	//}
	getLogExt().appendImage("Wiener", cimg);

	
	//sharp edges
		imago::Convolver cfilt(cimg);
		cfilt.initSharp();
		cfilt.apply();
	
   /*_unsharpMask(cimg, 4, 2, 0);
   _copyImageToMat(cimg, matred);
   */

	_copyImageToMat(cimg, matred);
	
	if(reduced)
		cv::pyrUp(matred, mat);
	else
		mat = matred;
	int thresh = greyThresh(mat, true);
	int wthresh = greyThresh(mat, false);

	if(strongThresh)
		wthresh = 0.2*thresh+0.8*wthresh;

	//Perform binary thresholding using Otsu procedure
	//thresh = thresh - 16 > 0 ? thresh - 16 : 0; 
	if(adaptiveThresh )//|| !strongThresh
	{
		//HistogramTools ht2(mat);
		//ht2.ImageAdjust(mat, true);
		double blockS = getSettings()["LineThickness"];
		blockS = ((int)blockS % 2) == 0 ? blockS +1:blockS;
		cv::adaptiveThreshold(mat, mat, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, (int)blockS*7, 7);
	}
	else
	cv::threshold(mat, mat, wthresh, 255, cv::THRESH_BINARY);//cv::THRESH_OTSU|

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

	   //mat = 255 - mat;
	   //perform open transformation
	   //cv::morphologyEx(mat, mat, cv::MORPH_OPEN, strel, cv::Point(-1, -1), 1, cv::BORDER_REPLICATE);
	   //mat = 255 - mat;
	

	cimg.clear();
	_copyMatToImage(cimg, mat);

	//if (debug_session)
	//{	
	//	ImageUtils::saveImageToFile(cimg, "output/pref3_after_pref.png");
	//}
	getLogExt().appendImage("After pref", cimg);

	image.copy(cimg);

	/*ThinFilter2 filt(image);
	filt.apply();

	if (debug_session)
	{
		ImageUtils::saveImageToFile(image, "output/pref3_after_prefthinning.png");
	}
*/
	LPRINT(0, "Filtering done");
}

bool isSplash(Segment *s, int lineSize)
{
	Image img;
	if(s->getWidth() < lineSize && s->getHeight() < lineSize)
		return true;
	s->extract(0, 0, s->getWidth(), s->getHeight(), img);
	int ls = EstimateLineThickness(img);
	if(ls > 3* lineSize || ls < 1)
		return true;
	return false;
}

bool SegCompare (Segment *i, Segment *j) 
{ 
	int area1 = i->getWidth() * i->getHeight();
	int area2 = j->getWidth() * j->getHeight();
	return (area1 < area2); 
}

void prefilterImage( Image &image, const CharacterRecognizer &cr )
{
	logEnterFunction();

	{
		bool binarized = true;
		for (int y = 0; y < image.getHeight() && binarized; y++)
			for (int x = 0; x < image.getWidth() && binarized; x++)
				binarized &= image.getByte(x, y) == 0 || image.getByte(x, y) == 255;
		if (binarized)
		{
			getLogExt().appendText("Image is already binarized, skip");
			return;
		}
	}

   Image raw, cimg;
   
   raw.copy(image);
   cimg.copy(image);
   int w = raw.getWidth();
   int h = raw.getHeight();
   int imMean = raw.mean();

   image.clear();
   //_prefilterInternal2(image);

   //_prefilterInternal(raw, image, cr);
   _prefilterInternal3(raw, image, cr, false, true);


   double lineThickness = EstimateLineThickness(image);

   if(lineThickness < 1)
	   throw Exception("Image prefiltering failed");

   getSettings()["LineThickness"] = lineThickness;
   
   //Image outImg(raw.getWidth(), raw.getHeight());
   //outImg.fillWhite();

   SegmentDeque segs, psegs;
   imago::Segmentator::segmentate(image, segs, std::min<double>(lineThickness, 3));
   SegmentDeque::iterator sit;
   int xmin=raw.getWidth(), xmax=0, 
	   ymin=raw.getHeight(), ymax=0;
   
   std::sort(segs.begin(), segs.end(), SegCompare); 
   
   int maxArea = segs[segs.size() -1]->getWidth() * segs[segs.size() -1]->getHeight();
   int maxDensity = maxArea *segs[segs.size() -1]->density();
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

	   if(sx == 0 || sy == 0 || (sx + sw) == w || (sy + sh) == h || isSplash(s, lineThickness))
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
		float sarea = (s->getHeight()*s->getWidth()*s->getDensity()) / maxDensity;
		if(sarea > 0.3)
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
   float koeff = 8.0;
   for(sit = tsegs.begin();sit != tsegs.end(); sit++)
   {
	   Segment *s = *sit;
	   int dis = (int)Vec2d::distance(center, s->getCenter());
	   int density = s->getWidth() * s->getHeight() * s->getDensity();
	   int dweight = maxDensity / density;
	   int est = //dis > (median+2.3*mad ) || 
		   ((lineThickness*lineThickness*4 > density) && dis > distsFromCenter[3*distsFromCenter.size()/4])? dis*dweight:dis;
	   
	   if(est < (median + koeff*mad))
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
	_prefilterInternal3(cimg, cs, cr); 
   //if(getSettings()["DebugSession"])
	//		ImageUtils::saveImageToFile(cs, "output/pref3_final.png");
	getLogExt().appendImage("After _prefilterInternal3", cs);
	
   
	SegmentDeque weak_segments;
   Segmentator::segmentate(cs, weak_segments);

   cimg.clear();
   cimg.init(cs.getWidth(), cs.getHeight());

#if 0
    for(rsit = weak_segments.rbegin(); rsit != weak_segments.rend(); rsit++)
	{		
		Segment *s = *rsit;		
		SegmentTools::makeSegmentConnected(*s, raw, 0.5);		
	}
#endif

	if(psegs.size() > 0)
		CombineWeakStrong(weak_segments, psegs, cimg);
	else
		cimg.copy(cs);

   //if(getSettings()["DebugSession"])
	//   ImageUtils::saveImageToFile(cimg, "output/pref3_final.png");
   getLogExt().appendImage("Pref3 final", cimg);
   
   BOOST_FOREACH(Segment *s, weak_segments)
	   delete s;
   BOOST_FOREACH( Segment *s, segs )
      delete s;
   segs.clear();
   psegs.clear();
   weak_segments.clear();
   image.copy(cimg);

}

void prefilterFile(const char *filename, Image &image, const CharacterRecognizer &cr )
{
   Image raw;

   ImageUtils::loadImageFromFile(raw, filename);

   _prefilterInternal(raw, image, cr);
   //_prefilterInternal2(raw);
}

void prefilterFile(const std::vector<unsigned char> &data, Image &image, const CharacterRecognizer &cr )
{
   LPRINT(0 , "prefilterFile");
   //Imago cannot load and resize!
   //Image raw;

   ImageUtils::loadImageFromBuffer(data, image);
   prefilterImage(image, cr);
   //_prefilterInternal(raw, image, cr);
   //_prefilterInternal2(raw);	
}
   

void prefilterPngData(const std::vector<unsigned char> &data, Image &image, const CharacterRecognizer &cr )
{
   LPRINT(0 , "prefilterPngData");
      
   LPRINT(0, "data size %d", data.size());
   ImageUtils::loadImageFromBuffer(data, image);
//   BufferScanner scanner(&data[0], data.size());
//   PngLoader(scanner).loadImage(image);
   prefilterImage(image, cr);
}

	
// NOTE: the input image must be thinned
bool isCircle (Image &seg)
{
   int w = seg.getWidth();
   int h = seg.getHeight();
   int i, j;
   float centerx = 0, centery = 0;
   int npoints = 0;

   for (j = 0; j < h; j++)
   {
      for (i = 0; i < w; i++)
      {
         if (seg.getByte(i, j) == 0)
         {
            centerx += i;
            centery += j;
            npoints++;
         }
      }
   }

   if (npoints == 0)
      throw Exception("empty fragment?");

   centerx /= npoints;
   centery /= npoints;

   _AngRadius *points = new _AngRadius[npoints + 1];
   int k = 0;
   float avg_radius = 0;

   for (i = 0; i < w; i++)
      for (j = 0; j < h; j++)
      {
         if (seg.getByte(i, j) == 0)
         {
            float radius = sqrt((i - centerx) * (i - centerx) +
                                (j - centery) * (j - centery));
            points[k].radius = radius;
            avg_radius += radius;
            float cosine = (i - centerx) / radius;
            float sine = (centery - j) / radius;
            float ang = (float)atan2(sine, cosine);
            if (ang < 0)
               ang += 2 * PI;
            points[k].ang = ang;
            k++;
         }
      }

   qsort(points, npoints, sizeof(_AngRadius), _cmp_ang);
   
   points[npoints].ang = points[0].ang + 2 * PI;
   points[npoints].radius = points[0].radius;

   for (i = 0; i < npoints; i++)
   {
      float gap = points[i + 1].ang - points[i].ang;
      float r1 = fabs(points[i].radius);
      float r2 = fabs(points[i + 1].radius);
      float gapr = 1.f;

      if (r1 > r2 && r2 > 0.00001)
         gapr = r1 / r2;
      else if (r2 < r1 && r1 > 0.00001)
         gapr = r2 / r1;

      if (gap < 0.1 && gapr > 2)
      {
         #ifdef DEBUG
         printf("large radios gap: %3f -> %3f at %3f\n", r1, r2, points[i].ang);
         #endif
         delete[] points;
         return false;
      }

      if (gap > 1.0)
      {
         #ifdef DEBUG
         printf("large gap: %3f at %3f\n", gap, points[i].ang);
         #endif
         delete[] points;
         return false;
      }
      if (gap > PI / 8 && (points[i].ang < PI / 8 || points[i].ang > 7 * PI / 4))
      {
         #ifdef DEBUG
         printf("C-like gap: %3f at %3f\n", gap, points[i].ang);
         #endif
         delete[] points;
         return false;
      }
   }

   avg_radius /= npoints;

   if (avg_radius < 0.0001)
   {
      #ifdef DEBUG
      printf("degenerate\n");
      #endif
      delete[] points;
      return false;
   }

   float disp = 0;

   for (i = 0; i < npoints; i++)
      disp += (points[i].radius - avg_radius) * (points[i].radius - avg_radius);

   disp /= npoints;
   float ratio = sqrt(disp) / avg_radius;

   #ifdef DEBUG
   printf("avgr %.3f dev %.3f ratio %.3f\n",
          avg_radius, sqrt(disp), ratio);
   #endif

   delete[] points;
   if (ratio > 0.3)
      return false; // not a circle
   return true;
}

}

