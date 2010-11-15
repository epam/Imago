#include <stdio.h>
#include "../src/Image/Image.h"
#include "../src/Image/FilePNG.h"


using namespace std;
using namespace gga;


int main(int argc, char* argv[])
{
    FilePNG png;
    Image   img;

    {
        Image i;
        i.setSize(640, 480, IT_BW);
        i.clear();

        i.drawLine(38, 38, 21 , 140);

        i.drawLine(40, 40, 300, 400, LineDefinition(172, 2));
//        i.drawLine(41, 40, 301, 400);

        i.drawLine(40, 40, 10 , 10);
        i.drawLine(40, 40, 10 , 100);

        i.drawLine(40, 40, 40 , 200);
        i.drawLine(40, 40, 200,  40, LineDefinition(127, 2));

        i.drawCircle(320, 240, 20, LineDefinition(127, 3));
        i.drawCircle(320, 240, 200);

        png.save(string("igraph-1.png"), i);
        return 0;
    }
}