#include <stdio.h>
#include <string>
#include "../src/Parameters.h"
#include "../src/Timer.h"
#include "../src/Image/Image.h"
#include "../src/Image/ImageFilter.h"
#include "../src/Image/FilePNG.h"
#include "../src/Image/FileJPG.h"
#include "../src/Vectorization/Vectorize.h"
#include "../src/Vectorization/SegmentParams.h"
#include "Draw.h"

using namespace gga;


class Tester
{
    gga::Image Image;
    std::string ImagePath;
    std::vector<std::string> Files;
    
    private:
        void Save(std::string type, const gga::Image& data)
        {
            char filename[1024] = {0};
            sprintf(filename, "temp_%i_%s.png", Files.size(), type.c_str());
            FilePNG().save(filename, data);
            Files.push_back(filename);    
        }
        
        void SetupLineWidth(ImageFilter& flt)
        {
            std::vector<size_t> w_histogram;
            Coord w = flt.computeLineWidthHistogram(&w_histogram);
            printf("Line width = %d\n", (int)w);
            GlobalParams.setLineWidth(w);
        }
        
        void PrepareImage(ImageFilter& flt)
        {
            Timer timer;
            flt.prepareImageForVectorization();
            printf("PrepareImageForVectorization taken %f ms\n", 1000.0*timer.getElapsedTime());
            printf("Image cleared '%s': %ix%i pixels\n", ImagePath.c_str(), Image.getWidth(), Image.getHeight());
            Save("clear", Image);
        }
        
        bool LoadImage()
        {
            if(FilePNG().load(ImagePath, &Image))
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
        
        Polylines VectorizeTest()
        {
            Timer timer;
            Vectorize vectorized(Image);
            printf("Vectorize taken %f ms\n", 1000.0*timer.getElapsedTime());
            timer.reset();  
            
            for (Triangles::const_iterator it = vectorized.getTriangles().begin(); it != vectorized.getTriangles().end(); it++)
                Save("triangle", Draw::TriangleToImage(*it));
            
            for (Polylines::const_iterator it = vectorized.getLines().begin(); it != vectorized.getLines().end(); it++)
                Save("line", Draw::LineToImage(*it));

            for (PContours::const_iterator it = vectorized.getOtherContours().begin(); it != vectorized.getOtherContours().end(); it++)
                 Save("other", Draw::PointsToImage(*(*it)));

            printf("Total: %i consistent parts (Save taken %f ms)\n", Files.size(), 1000.0*timer.getElapsedTime());            
            
            return vectorized.getLines();
        }
        
        void RotateImage0(const Polylines& lines)
        {
            SegmentParams segParams(lines);
            int angle = -segParams.getRotationAngle();
            printf("Average line length: %ipx; Image rotation required: %i*\n", segParams.getAverageLineLength(), angle);
            if ( fabs(angle) > GlobalParams.getMinimalAllowedRotationAngle() )
            {
                gga::Image rotated;
                rotateImage(Image, angle, &rotated);
                Save("rotate", rotated);
                Image = rotated;
            }
        }

    public:
        Tester(std::string path)
        {
            ImagePath = path;
            if (LoadImage())
            {            
                ImageFilter flt(Image); 
                if (GlobalParams.isClearImageRequired())
                    PrepareImage(flt);
                SetupLineWidth(flt);
                const Polylines& lines = VectorizeTest();
                RotateImage0(lines);
            }
        }
        
        void DeleteFiles()
        {
            for (size_t u = 0; u < Files.size(); u++)
                remove(Files[u].c_str());
        }
};




int main(int argc, char* argv[])
{
    std::string ImagePath = (argc > 1) ? argv[1] : "../../Data/Sample3_.png";
    
    Tester imgTester(ImagePath);

    if (argc <= 1)
    {
        printf("Press [ENTER] to delete temporary files and close application.\n");
        char buf[80];
        scanf("%c", buf);
        imgTester.DeleteFiles();
    }
    
    return 0;
}
