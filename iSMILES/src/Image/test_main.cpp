#include <stdio.h>
#include "FileJPG.h"
#include "FilePNG.h"
#include "ImageFilter.h"

using namespace std;
using namespace gga;
char cmd[256];

int main(int argc, char* argv[])
{
    FileJPG jpg;
    FilePNG png;
    Image   img;
/*
    {
        Image i;
        i.setSize(640, 480, IT_BW);
        i.clear();

        i.drawLine(7, 7, 7, 7);
        i.drawLine(-1, 700, 3, 70);

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
//        return 0;
    }
*/
    {
//prepareImageForVectorization:
        if(!jpg.load(argv[1], &img))
        {
            if(!png.load(argv[1], &img))
                return -1;
        }
        size_t r = 4;
        size_t bg, maxh;

        unsharpMaskImage(&img, 85, 1., 7., 72);
        png.save(string(argv[1])+".out10_unsharp-mask.png", img);

//        blurImage(&img, r);
//        png.save(string(argv[1])+".out02_blur.png", img);

        std::vector<size_t> histogram;
        maxh = makeHistogram (img, &histogram);
        size_t maxColor = 0, maxN = 0;
        size_t minColor = 0, minN =-1;
        for(size_t i = 0; i < histogram.size(); i++)
        {
            if(histogram[i] >= maxN)
            {
                maxColor = i;
                maxN = histogram[i];
            }
            if(histogram[i] < minN)
            {
                minColor = i;
                minN = histogram[i];
            }
        }
        bg = getBackgroundValue(img);
        stretchImageHistogram(&img, minColor, maxColor);
        png.save(string(argv[1])+".out30_stretched.png", img);
            for(size_t v = 32; v < histogram.size() && histogram[v] < maxh; v++)
                printf("%3d: %d %s\n", v, histogram[v], v==bg ? "------------ BACKGROUND CutOff -------------" : "");
            printf("bg=%d (%d) minColor=%d maxColor=%d\n", bg, getBackgroundValue(img), minColor, maxColor);
        blurImage(&img, 5);
        png.save(string(argv[1])+".out40_stretched-blur.png", img);

        bg = getBackgroundValue(img);
        convertGrayscaleToBlackWhite(img, bg);
        png.save(string(argv[1])+".out50_BW.png", img);

        r=32;   //21
        clearCorners (img, r);
        png.save(string(argv[1])+".out60_cleared-corners.png", img);
        eraseSmallDirts (img, 4);
        png.save(string(argv[1])+".out61_cleared-dirts.png", img);
        cropImageToPicture(img);
        png.save(string(argv[1])+".out99_cropped.png", img);
//scanf("%s", cmd);
//        return 0;
    }

    {
        if(!jpg.load(argv[1], &img))
        {
            if(!png.load(argv[1], &img))
                return -1;
        }
        ImageFilter flt(img);
        flt.prepareImageForVectorization();
        png.save(string(argv[1])+".out.png", img);
        std::vector<size_t> whistogram;
        gga::Coord w = flt.computeLineWidthHistogram(&whistogram);
        printf("Width = %d\n", (int)w);
        return 0;
    }
/*
    {
        if(!png.load(argv[1], &img))
        {
            return -1;
        }

        size_t r = 4;
        blurImage(&img, r);
    
        { //trace:
            std::vector<size_t> histogram;
            size_t maxh = makeHistogram (img, &histogram);
            size_t bg   = getBackgroundValue(img);

            for(size_t v = 32; v < histogram.size() && histogram[v] < maxh; v++)
                printf("%3d: %d %s\n", v, histogram[v], v==bg ? "------------ BACKGROUND CutOff -------------" : "");
        }

        size_t bg = getBackgroundValue(img);
        convertGrayscaleToBlackWhite(img, bg);
        printf("bg=%d, \n", bg);

        img.crop(4, 4, img.getWidth()-4, img.getHeight()-4);
        png.save(string(argv[1])+".test-out.png", img);

    }
*/
//    scanf("%s", cmd);
}
