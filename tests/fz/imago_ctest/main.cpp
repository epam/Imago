#include <cstdio>
#include <cstring>

#include "imago_c.h"

void testInterface( const char *Input, const char *Output )
{
   qword a = imagoAllocSessionId();

   if (!imagoLoadPngImageFromFile(Input))
   {
      puts(imagoGetLastError());
      return;
   }

   if (!imagoRecognize())
   {
      puts(imagoGetLastError());
      return;
   }

   if (!imagoSaveMolToFile(Output))
   {
      puts(imagoGetLastError());
      return;
   }

   imagoReleaseSessionId(a);
}

int main( void )
{
   char Buf[100];

   strcpy(Buf, "../../../data/mol_images/hello!.PNG");
   testInterface(Buf, "mol1.mol");

   strcpy(Buf, "../../../data/mol_images/image115.png");
   testInterface(Buf, "mol2.mol");
}
