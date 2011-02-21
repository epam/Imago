#include "allheaders.h"
#include "image.h"
#include "log.h"
#include "current_session.h"
#include "exception.h"
#include "segmentator.h"
#include "output.h"
#include "png_saver.h"
#include "orientation_finder.h"

#undef DEBUG

namespace imago
{

static int _cmp_float (const void *p1, const void *p2)
{
   float f1 = *(const float *)p1;
   float f2 = *(const float *)p2;

   if (f1 < f2)
      return -1;
   return 1;
}


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
      
      #ifdef DEBUG
      fprintf(stderr, "average brightness = %f\n", avg);
      #endif
      if (avg < 155)
      {
         LPRINT(0, "adding constant gray");
         if (pixAddConstantGray(pix, 155 - avg) != 0)
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
      _unsharpMask(pix, 8, 4, 0);
      pixWritePng("04_after_strong_unsharp_mask.png", pix, 1);
   }

   {
      _binarize(pix, 32);
      pixWritePng("05_after_strong_binarization.png", pix, 1);
   }

   Image strongimg;

   _copyPixToImage(strongimg, pix);

   _removeSpots(strongimg, 0, 10);
   {
      FileOutput output("06_after_spots_removal.png");
      PngSaver saver(output);
      saver.saveImage(strongimg);
   }


   {
      LPRINT(0, "unsharp mask (weak)");
      _unsharpMask(weakpix, 10, 12, 0);
      pixWritePng("07_after_weak_unsharp_mask.png", weakpix, 1);
   }

   {
      _binarize(weakpix, 80);
      pixWritePng("08_after_weak_binarization.png", weakpix, 1);
   }

   Image weakimg;
   _copyPixToImage(weakimg, weakpix);

   SegmentDeque weak_segments;
   SegmentDeque strong_segments;
   Segmentator::segmentate(weakimg, weak_segments);
   Segmentator::segmentate(strongimg, strong_segments);

   #ifdef DEBUG
   fprintf(stderr, "%d weak segments\n", weak_segments.size());
   fprintf(stderr, "%d strong segments\n", strong_segments.size());
   #endif

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
         #ifdef DEBUG
         fprintf(stderr, "weak segment not found\n");
         #endif
      }
   }

   _removeSpots(img, 255, 2);
   
   OrientationFinder of(_cr);
   int rotation = of.findFromImage(img);
   if (rotation != 0)
   {
      LPRINT(0, "Found rotation %d", 90 * (4 - rotation));
      switch (rotation)
      {
         case 1:
            img.rotate90();
            break;
         case 2:
            img.rotate180();
            break;
         case 3:
            img.rotate90(false);
      }
   
   }

   {
      FileOutput output("09_final.png");
      PngSaver saver(output);
      saver.saveImage(img);
   }

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
   
   float *angles = new float[npoints + 1];
   float *radii = new float[npoints];
   int k = 0;
   float avg_radius = 0;
      
   for (i = 0; i < w; i++)
      for (j = 0; j < h; j++)
      {
         if (seg.getByte(i, j) == 0)
         {
            float radius = sqrt((i - centerx) * (i - centerx) +
                                (j - centery) * (j - centery));
            radii[k] = radius;
            avg_radius += radius;
            float cosine = (i - centerx) / radius;
            float sine = (centery - j) / radius;
            float ang = (float)atan2(sine, cosine);
            if (ang < 0)
               ang += 2 * M_PI;
            angles[k] = ang;
            k++;
         }
      }

   qsort(angles, npoints, sizeof(float), _cmp_float);
   angles[npoints] = angles[0] + 2 * M_PI;

   for (i = 0; i < npoints; i++)
   {
      float gap = angles[i + 1] - angles[i];
      if (gap > 1.0)
      {
         #ifdef DEBUG
         printf("large gap: %3f at %3f\n", gap, angles[i]);
         #endif
         return false;
      }
      if (gap > M_PI / 8 && (angles[i] < M_PI / 8 || angles[i] > 7 * M_PI / 4))
      {
         #ifdef DEBUG
         printf("C-like gap: %3f at %3f\n", gap, angles[i]);
         #endif
         return false;
      }
   }

   avg_radius /= npoints;
   
   if (avg_radius < 0.0001)
   {
      #ifdef DEBUG
      printf("degenerate\n");
      #endif
      return false;
   }

   float disp = 0;
   
   for (i = 0; i < npoints; i++)
      disp += (radii[i] - avg_radius) * (radii[i] - avg_radius);
   
   disp /= npoints;
   float ratio = sqrt(disp) / avg_radius;
      
   #ifdef DEBUG
   printf("avgr %.3f dev %.3f ratio %.3f\n",
          avg_radius, sqrt(disp), ratio);
   #endif

   delete[] radii;
   if (ratio > 0.3) 
      return false; // not a circle
   return true;
}

}
