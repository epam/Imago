#include "ismiles_c.h"

#include "Image.h"
#include "ImageFilter.h"
#include "FileJPG.h"
#include "Point.h"

using namespace gga;

CEXPORT unsigned char *loadAndProcessJPGImage( const char *filename, int *width, int *height )
{
   Image img;

   FileJPG().load(filename, &img);

   int maxside = img.getWidth() > img.getHeight() ?
      img.getWidth() : img.getHeight();
   int n = maxside / 800;
   if (n > 1)
      img.resizeLinear(n);

   int angle = 0;

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
      const Image src(img);
      rotateImage(src, (float)angle, &img);
   }
      
   ImageFilter flt(img);
   flt.Parameters.ImageSize = 10000;
   flt.prepareImageForVectorization();

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
