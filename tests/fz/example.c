#include <stdio.h>

#include "imago_c.h"

#define IMAGO_CALL(func) \
   res = func; \
   if (res == 0 ) \
   { \
      printf("Something bad happened: %s", imagoGetLastError()); \
      break; \
   } 

int main( int argc, char *argv[] )
{
   char filename[100];
   qword id = imagoAllocSessionId();
   imagoSetSessionId(id);

   while (1)
   {
     int res;
     printf("Type image filename:\n");
     scanf("%s", filename);

     IMAGO_CALL(imagoLoadJpgImageFromFile(filename));
     IMAGO_CALL(imagoResetLog());
     IMAGO_CALL(imagoFilterImage());
     IMAGO_CALL(imagoRecognize());
     IMAGO_CALL(imagoSaveMolToFile("result.mol"));
   }

   imagoReleaseSessionId(id);
    
   return 0;
}
