#include "ismiles_c.h"

#include "Image.h"
#include "ImageFilter.h"
#include "FileJPG.h"
#include "Point.h"

#include <stdio.h>

using namespace gga;

CEXPORT unsigned char *loadAndProcessJPGImage( const char *filename, int *width, int *height )
{
   Image img;

   FileJPG().load(filename, &img);

   printf("\n");
   printf("got image %d x %d\n", img.getWidth(), img.getHeight());
   int maxside =  img.getWidth() > img.getHeight() ?
      img.getWidth() : img.getHeight();

   int n = maxside / 800;

   if (n > 1)
   {
      printf("resizing down %d times\n", n);
      img.resizeLinear(n);
      printf("now the image is %d x %d\n", img.getWidth(), img.getHeight());
   }

   int angle = 0;

   printf("orientation: %d\n", img.getOrientation());

   switch(img.getOrientation())
   {
      case 1: // standard orientation, do nothing
      case 2: // flipped right-left
         break;
      case 3: // rotated 180
         angle = 180;
         break;
      case 4: // flipped top-bottom
      case 5: // flipped diagonally around '\'
         break;
      case 6: // 90 CW
         angle = 90;
         break;
      case 7: // flipped diagonally around '/'
         break;
      case 8: // 90 CCW
         angle = 270;
         break;
      case -1:    //not found
      default:    // shouldn't happen
         break;
   }
      
   if (angle != 0)
   {
      printf("rotating the image, angle = %f\n", (float)angle);
      const Image src(img);
      rotateImage(src, (float)angle, &img);
   }
      
   printf("filtering the image\n");
   ImageFilter flt(img);
   flt.Parameters.ImageSize = 10000;
   flt.prepareImageForVectorization();
   printf("now the image is %d x %d\n", img.getWidth(), img.getHeight());
   printf("\n");

   unsigned char *buf = new unsigned char[img.getWidth() * img.getHeight()];

   *height = img.getHeight();
   *width = img.getWidth();

   for (int j = 0; j != img.getHeight(); j++)
   {
      int offset = j * img.getWidth();

      for (int i = 0; i != img.getWidth(); i++)
      {
         buf[offset + i] = img.getPixel(i, j).Value;
      }
   }

   return buf;
}
