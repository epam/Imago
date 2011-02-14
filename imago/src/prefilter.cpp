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
         throw Exception("pixConvertRGBToLuminance failed");
      pixDestroy(&pix);
      pix = newpix;
      pixWritePng("01_after_subsampling.png", pix, 1);
   }

   w = pixGetWidth(pix);
   h = pixGetHeight(pix);

   {
      LPRINT(0, "adding constant gray");
      if (pixAddConstantGray(pix, 64) != 0)
         throw Exception("pixAddConstantGray failed");
      pixWritePng("03_after_adding_constant_gray.png", pix, 1);
   }

   {
      LPRINT(0, "unsharp mask");
      _unsharpMask(pix, 10, 4, 0);
      pixWritePng("04_after_unsharp_mask.png", pix, 1);
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
      pixWritePng("05_after_binarization.png", pix, 1);
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
