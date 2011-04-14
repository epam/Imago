#include <stdio.h>

#include "imago_c.h"

int main( int argc, char *argv[] )
{
   qword id = imagoAllocSessionId();
   imagoSetSessionId(id);

   char filename[100];

   while (1)
   {
     printf("Type image filename:\n");
     scanf("%s", filename);
     imagoLoadAndFilterJpgFile(filename);
     imagoRecognize();
     imagoSaveMolToFile("result.mol");
   }

   imagoReleaseSessionId(id);
    
   return 0;
}
