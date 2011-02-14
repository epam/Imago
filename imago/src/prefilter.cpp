#include "allheaders.h"
#include "image.h"
#include "log.h"
#include "current_session.h"
#include "exception.h"

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
         throw Exception("pixScaleByIntSubsampling failed");
      pixDestroy(&pix);
      pix = newpix;
      pixWritePng("01_after_subsampling.png", pix, 1);
   }

   w = pixGetWidth(pix);
   h = pixGetHeight(pix);

   {
      _unsharpMask(pix, 7, 2.1, 0);
      pixWritePng("02_after_unsharp.png", pix, 1);
   }

   {
      int radius = 3;
      LPRINT(0, "blurring");
      PIX *newpix = pixBlockconvGray(pix, NULL, radius, radius);
      if (newpix == NULL)
         throw Exception("pixBlockconvGray failed");
      pixDestroy(&pix);
      pix = newpix;
      pixWritePng("03_after_blur.png", pix, 1);
   }

   {
      LPRINT(0, "increasing contrast");
      NUMA *na = pixGetGrayHistogram(pix, 1);
      int hsize = numaGetCount(na);
      l_int32 * histogram = numaGetIArray(na);
      int min_color = 0, max_color = hsize - 1, maxn = histogram[max_color];
      int i, j;

      for (i = 0; i < hsize; i++)
      {
         if (i > 32 && histogram[i] >= maxn)
         {
            max_color = i;
            maxn = histogram[i];
         }
         if (min_color == 0 && histogram[i] >= 100)
            min_color = i;
      }
      
      if (max_color > min_color)
      {
         for (i = 0; i < w; i++)
            for (j = 0; j < h; j++)
            {
               l_uint32 val;
               if (pixGetPixel(pix, i, j, &val) != 0)
                  throw Exception("leptonica getpixel (3)");
               
               if (val < min_color)
                  val = 0;
               if (val > max_color)
                  val = 255;
               else
                  val = (l_uint32)(255.f * (val - min_color) / ((float)max_color - min_color));
               pixSetPixel(pix, i, j, val);
            }
      }
      pixWritePng("04_after_contrast.png", pix, 1);
   }
   
   {
      int radius = 3;
      LPRINT(0, "blurring again");
      PIX *newpix = pixBlockconvGray(pix, NULL, radius, radius);
      if (newpix == NULL)
         throw Exception("pixBlockconvGray failed");
      pixDestroy(&pix);
      pix = newpix;
      pixWritePng("05_after_second_blur.png", pix, 1);
   }

   {
      _unsharpMask(pix, 40, 9.f, 100);
      pixWritePng("06_after_second_unsharp.png", pix, 1);
   }

   {
      int i, j;
      for (i = 0; i < w; i++)
         for (j = 0; j < h; j++)
         {
            l_uint32 val;
            if (pixGetPixel(pix, i, j, &val) != 0)
               throw Exception("leptonica getpixel (4)");
            
            if (val < 64)
               val = 0;
            else
               val = 255;

            pixSetPixel(pix, i, j, val);
         }
      pixWritePng("07_after_binarization.png", pix, 1);
   }

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

   pixDestroy(&pix);
}

}
