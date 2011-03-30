#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "image.h"
#include "log.h"
#include "current_session.h"
#include "exception.h"
#include "segmentator.h"
#include "output.h"
#include "png_saver.h"
#include "orientation_finder.h"
#include "convolver.h"
#include "image_utils.h"
#include "binarizer.h"

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
void _unsharpMask (Image &img, int radius, float amount, int threshold)
{
   int  w, h;

   w = img.getWidth();
   h = img.getHeight();

   Image blur;
   blur.copy(img);

   TIME(_blur(blur, radius), "Blur");

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

void _copyMatToImage (Image &img, const cv::Mat &mat)
{
   int w = mat.cols;
   int h = mat.rows;

   img.init(w, h);
   int i, j;

   for (i = 0; i < w; i++)
      for (j = 0; j < h; j++)
         img.getByte(i, j) = mat.at<unsigned char>(j, i);
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
}

static CharacterRecognizer _cr(3); // not really used

void prefilterFile (const char *filename, Image &image)
{
   //Imago cannot load and resize!
   cv::Mat mat = cv::imread(filename, 0); //load and make grayscale

   if (mat.data == NULL)
      throw Exception("imload failed");

   int w = mat.cols;
   int h = mat.rows;
   LPRINT(0, "loaded image %d x %d", w, h);
   int maxside = (w < h) ? h : w;
   int n = maxside / 800;
   if (n > 1)
   {
      LPRINT(0, "resizing down %d times", n);
      cv::Mat dst;
      cv::resize(mat, dst, cv::Size(), 1.0 / n, 1.0 / n);
      mat = dst;
#ifdef DEBUG
      cv::imwrite("01_after_subsampling.png", mat);
#endif
   }

   Image img;
   _copyMatToImage(img, mat);


   {
      LPRINT(0, "blurring");
      _blur(img, 1);
#ifdef DEBUG
      ImageUtils::saveImageToFile(img, "02_after_blur.png");
#endif
   }


   w = img.getWidth();
   h = img.getHeight();

   {
      int avg = img.mean();

      #ifdef DEBUG
      fprintf(stderr, "average brightness = %d\n", avg);
      #endif
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
#ifdef DEBUG
   ImageUtils::saveImageToFile(img, "03_after_normalization.png");
#endif


   Image weakimg;
   weakimg.copy(img);

   {
      LPRINT(0, "unsharp mask (strong)");

      _unsharpMask(img, 8, 4, 0);
#ifdef DEBUG
      ImageUtils::saveImageToFile(img, "04_after_strong_unsharp_mask.png");
#endif
   }

   {
      Binarizer b(img, 32);
      b.apply();
#ifdef DEBUG
      ImageUtils::saveImageToFile(img, "05_after_strong_binarization.png");
#endif
   }

   Image strongimg;
   strongimg.copy(img);
   _removeSpots(strongimg, 0, 10);
#ifdef DEBUG
   ImageUtils::saveImageToFile(img, "06_after_spots_removal.png");
#endif

   {
      LPRINT(0, "unsharp mask (weak)");
      _unsharpMask(weakimg, 10, 12, 0);
#ifdef DEBUG
      ImageUtils::saveImageToFile(weakimg, "07_after_weak_unsharp_mask.png");
#endif
   }

   {
      Binarizer b(weakimg, 80);
      b.apply();
#ifdef DEBUG
      ImageUtils::saveImageToFile(weakimg, "08_after_weak_binarization.png");
#endif
   }

   SegmentDeque weak_segments;
   SegmentDeque strong_segments;
   Segmentator::segmentate(weakimg, weak_segments);
   Segmentator::segmentate(strongimg, strong_segments);

   #ifdef DEBUG
   fprintf(stderr, "%d weak segments\n", weak_segments.size());
   fprintf(stderr, "%d strong segments\n", strong_segments.size());
   #endif

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
         #ifdef DEBUG
         fprintf(stderr, "weak segment not found\n");
         #endif
      }
   }

   _removeSpots(image, 255, 2);

   OrientationFinder of(_cr);
   int rotation = of.findFromImage(image);
   if (rotation != 0)
   {
      LPRINT(0, "Found rotation %d", 90 * (4 - rotation));
      switch (rotation)
      {
         case 1:
            image.rotate90();
            break;
         case 2:
            image.rotate180();
            break;
         case 3:
            image.rotate90(false);
      }

   }

   LPRINT(0, "Filtering done");
#ifdef DEBUG
   ImageUtils::saveImageToFile(image, "09_final.png");
#endif
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

