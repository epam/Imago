#include "allheaders.h"
#include "image.h"
#include "log.h"
#include "current_session.h"
#include "exception.h"
#include "segmentator.h"
#include "output.h"
#include "png_saver.h"

namespace imago
{

void _unsharpMask (PIX *pix, int radius, float amount, int threshold)
{
   l_int32  w, h, d;
   PIX     *pixc;
   
   pixGetDimensions(pix, &w, &h, &d);

   if (d != 8)
      throw Exception("image not 8bpp, unsharp mask failed");
   
   if ((pixc = pixBlockconvGray(pix, NULL, radius, radius)) == NULL)
      throw Exception("gaussian blur failed");

   int i, j;
   
   for (i = 0; i < w; i++)
      for (j = 0; j < h; j++)
      {
         l_uint32 val, valc;
         if (pixGetPixel(pix, i, j, &val) != 0)
            throw Exception("leptonica getpixel");
         if (pixGetPixel(pixc, i, j, &valc) != 0)
            throw Exception("leptonica getpixel (2)");
         
         int diff = (int)val - (int)valc;

         if (diff < threshold && diff > -threshold)
            diff = 0;

         int newval = (int)val + diff * amount;
         if (newval > 255)
            newval = 255;
         if (newval < 0)
            newval = 0;
            
         pixSetPixel(pix, i, j, newval);
      }
   pixDestroy(&pixc);
}

void _binarize (PIX *pix, int threshold)
{
   int w = pixGetWidth(pix);
   int h = pixGetHeight(pix);

   int i, j;
   for (i = 0; i < w; i++)
      for (j = 0; j < h; j++)
      {
         l_uint32 val;
         if (pixGetPixel(pix, i, j, &val) != 0)
            throw Exception("leptonica getpixel (4)");
         
         if (val < threshold)
            val = 0;
         else
            val = 255;
         
         pixSetPixel(pix, i, j, val);
      }
}

void _copyPixToImage (Image &img, PIX *pix)
{
   int w = pixGetWidth(pix);
   int h = pixGetHeight(pix);

   img.init(w, h);
   int i, j;

   for (i = 0; i < w; i++)
      for (j = 0; j < h; j++)
      {
         l_uint32 val;
         if (pixGetPixel(pix, i, j, &val) != 0)
            throw Exception("leptonica getpixel (3)");
         
         img.getByte(i, j) = val;
      }
}

void prefilterFile (const char *filename, Image &img)
{
   PIX * pix = pixReadJpeg(filename, 0, 1, 0);

   if (pix == NULL)
      throw Exception("pixReadJpeg failed");
   
   int w = pixGetWidth(pix);
   int h = pixGetHeight(pix);
   LPRINT(0, "loaded image %d x %d", w, h);
   int maxside = (w < h) ? h : w;
   int n = maxside / 800;
   if (n > 1)
   {
      LPRINT(0, "resizing down %d times", n);
      PIX *newpix = pixScaleByIntSubsampling(pix, n);
      if (newpix == NULL)
         throw Exception("pixScaleByIntSubsampling failed");
      pixDestroy(&pix);
      pix = newpix;
   }
   {
      LPRINT(0, "converting to gray");
      PIX *newpix = pixConvertRGBToLuminance(pix);
      if (newpix == NULL)
         throw Exception("pixConvertRGBToLuminance failed");
      pixDestroy(&pix);
      pix = newpix;
      pixWritePng("01_after_subsampling.png", pix, 1);
   }
   
   {
      LPRINT(0, "blurring");
      PIX *newpix = pixBlockconvGray(pix, NULL, 1, 1);
      if (newpix == NULL)
         throw Exception("gaussian blur failed");
      pixDestroy(&pix);
      pix = newpix;
      pixWritePng("02_after_blur.png", pix, 1);
   }

   w = pixGetWidth(pix);
   h = pixGetHeight(pix);

   {
      l_float32 avg;

      if (pixGetAverageMasked(pix, 0, 0, 0, 1, L_MEAN_ABSVAL, &avg) != 0)
         throw Exception("pixGetAverageMasked failed");
      
      fprintf(stderr, "average brightness = %f\n", avg);
      if (avg < 164)
      {
         LPRINT(0, "adding constant gray");
         if (pixAddConstantGray(pix, 164 - avg) != 0)
            throw Exception("pixAddConstantGray failed");
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

   pixWritePng("03_after_normalization.png", pix, 1);

   PIX *weakpix = pixCopy(NULL, pix);

   {
      LPRINT(0, "unsharp mask (strong)");
      _unsharpMask(pix, 10, 5, 0);
      pixWritePng("04_after_strong_unsharp_mask.png", pix, 1);
   }

   {
      _binarize(pix, 16);
      pixWritePng("05_after_strong_binarization.png", pix, 1);
   }
   
   {
      LPRINT(0, "unsharp mask (weak)");
      _unsharpMask(weakpix, 10, 10, 0);
      pixWritePng("06_after_weak_unsharp_mask.png", weakpix, 1);
   }

   {
      _binarize(weakpix, 128);
      pixWritePng("07_after_weak_binarization.png", weakpix, 1);
   }

   Image strongimg;
   Image weakimg;

   _copyPixToImage(strongimg, pix);
   _copyPixToImage(weakimg, weakpix);

   SegmentDeque weak_segments;
   SegmentDeque strong_segments;
   Segmentator::segmentate(weakimg, weak_segments);
   Segmentator::segmentate(strongimg, strong_segments);

   fprintf(stderr, "%d weak segments\n", weak_segments.size());
   fprintf(stderr, "%d strong segments\n", strong_segments.size());

   img.init(w, h);
   int i, j;

   for (i = 0; i < w; i++)
      for (j = 0; j < h; j++)
         img.getByte(i, j) = 255;

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
                                 img.getByte(wi + wseg->getX(),
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
         fprintf(stderr, "weak segment not found\n");
      }
   }

   /*
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
         float avg_x = sum_x / (float)npoints;
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
         disp /= npoints;
         if (radius < 1 || (npoints < 20))
         {
            fprintf(stderr, "removing segment: npoints = %d, radius = %f, stddev = %f\n", npoints, radius, sqrt(disp));
            for (i = 0; i < sw; i++)
               for (j = 0; j < sh; j++)
               {
                  byte val = seg->getByte(i, j);
                  if (val == 0)
                     img.getByte(seg->getX() + i, seg->getY() + j) = 255;
               }
         }
      }
   }
   FileOutput output("06_after_spots_removal.png");*/

   FileOutput output("08_final.png");
   PngSaver saver(output);
   saver.saveImage(img);

}

}
