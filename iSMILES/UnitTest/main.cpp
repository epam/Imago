#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "../src/Logger.h"
#include "../src/Parameters.h"
#include "../src/Timer.h"
#include "../src/Image/Image.h"
#include "../src/Image/ImageFilter.h"
#include "../src/Image/FilePNG.h"
#include "../src/Image/FileJPG.h"
#include "../src/Vectorization/Vectorization.h"
#include "../src/Vectorization/SegmentParams.h"
#include "Draw.h"

using namespace gga;


class Tester
{
    gga::Image Image;
    std::string ImagePath;
    std::vector<std::string> Files;
    
    private:
        void saveImage(std::string type, const gga::Image& data)
        {
            char filename[1024] = {0};
            sprintf(filename, "temp_%i_%s.png", Files.size(), type.c_str());
            FilePNG().save(filename, data);
            Files.push_back(filename);    
        }
        
        void setupLineWidth(ImageFilter& flt)
        {
            std::vector<size_t> w_histogram;
            Coord w = flt.computeLineWidthHistogram(&w_histogram);            
            getGlobalParams().setLineWidth(w);
        }
        
        void prepareImage(ImageFilter& flt)
        {
            Timer timer;
            flt.prepareImageForVectorization();
            printf("Prepare image taken %f ms\n", 1000.0*timer.getElapsedTime());
            saveImage("clear", Image);
        }
        
        bool loadImage()
        {
            if(FilePNG().load(ImagePath, &Image) || FileJPG().load(ImagePath, &Image))
            {
                printf("Image loaded '%s': %ix%i pixels\n", ImagePath.c_str(), Image.getWidth(), Image.getHeight());
                return true;
            }
            else
            {
                printf("Failed to load image '%s'.\n", ImagePath.c_str());
                return false;
            }
        }
        
        Polylines vectorizeTest()
        {
            Timer timer;
            Vectorization vectorized(Image);
            printf("Vectorize taken %f ms\n", 1000.0*timer.getElapsedTime());
            timer.reset();  
            
            for (Triangles::const_iterator it = vectorized.getTriangles().begin(); it != vectorized.getTriangles().end(); it++)
                saveImage("triangle", Draw::TriangleToImage(*it));
            
            gga::Image lined = Image;
            for (Polylines::const_iterator it = vectorized.getLines().begin(); it != vectorized.getLines().end(); it++)
                Draw::LineToImage(*it, lined);
            saveImage("lined", lined);

            return vectorized.getLines();
        }
        
        void normalizeImageRotation(const Polylines& lines)
        {
            SegmentParams segParams(lines);
            int angle = -segParams.getRotationAngle();
            printf("Average line length: %ipx, width: %ipx; Image rotation required: %i*\n", 
                segParams.getAverageLineLength(), getGlobalParams().getLineWidth(), angle);
            if (abs(angle) > getGlobalParams().getMinimalAllowedRotationAngle())
            {
                gga::Image rotated;
                rotateImage(Image, (float)angle, &rotated);
                saveImage("rotate", rotated);
                Image = rotated;
            }
        }

    public:
        Tester(std::string path)
        {
            ImagePath = path;
            if (loadImage())
            {            
                ImageFilter flt(Image); 
                if (getGlobalParams().isClearImageRequired())
                    prepareImage(flt);
                setupLineWidth(flt);
                const Polylines& lines = vectorizeTest();
                normalizeImageRotation(lines);
            }
        }
        
        void deleteFiles()
        {
            for (size_t u = 0; u < Files.size(); u++)
                remove(Files[u].c_str());
        }
};


int main(int argc, char* argv[])
{
    remove(LOGFILE);
    std::string ImagePath = (argc > 1) ? argv[1] : "../Data/Raw/IMG_0007.JPG";
    
    Tester imgTester(ImagePath);

    if (argc <= 1)
    {
        printf("Press [ENTER] to delete temporary files and close application.\n");
        char buf[80];
        scanf("%c", buf);
        imgTester.deleteFiles();
    }
    
    return 0;
}
