#include <stdio.h>

#include "../src/Parameters.h"
#include "../src/Timer.h"

#include "../src/Image/Image.h"
#include "../src/Image/ImageFilter.h"
#include "../src/Image/FilePNG.h"
#include "../src/Image/FileJPG.h"

#include "../src/Vectorization/Vectorize.h"

#include "Draw.h"


using namespace gga;

int main(int argc, char* argv[])
{
    Image img;
	bool automaticMode = false;
	
	const char* ImagePath = "../../Data/Sample0.png";
    if(argc > 1)
	{
        ImagePath = argv[1];
		automaticMode = true;
	}

    if(FilePNG().load(ImagePath, &img))
    {
        printf("Image loaded '%s': %ix%i pixels\n", ImagePath, img.getWidth(), img.getHeight());
    }
    else
    {
		printf("Failed to load image '%s'.\n", ImagePath);
        return -1;
    }
	
    if (GlobalParams.isClearImageRequired())
    {
        ImageFilter flt(img); 
        flt.prepareImageForVectorization();
        printf("Image cleared '%s': %ix%i pixels\n", ImagePath, img.getWidth(), img.getHeight());
        FilePNG().save(std::string(ImagePath) + ".clear.png", img);
    }
	
	Timer t;
	Vectorize vectorized(img);
	printf("Parts: %i (Vectorize taken %f ms)\n", vectorized.getContoursCount(), 1000.0*t.getElapsedTime());
    
    
    size_t parts = 0;
	t.reset();
	std::vector<std::string> files;
	for (size_t u = 0; u < vectorized.getContoursCount(); u++)
	{
		const Contour& contour = vectorized.getContour(u);

		if (Bounds(contour).getArea() >= GlobalParams.getMinimalConsistentArea())
		{
            printf("----------> Contour (idx %i) %p (inner for %p)\n", u, &contour, contour.getOuterContour());
            
			char filename[1024] = {0};
						
			LinearApproximation line(contour);            
			if (line.isGood())
            {
                TriangleRecognition triangle(line.getLine(), vectorized.getImageMap());
                if (triangle.isGood())
                {
                    sprintf(filename, "temp_%i_triangle.png", parts);
                    FilePNG().save(filename, Draw::LineToImage(line));
                    files.push_back(filename);
                }
                else
                {
                    sprintf(filename, "temp_%i_line.png", parts);
                    FilePNG().save(filename, Draw::LineToImage(line));
                    files.push_back(filename);                    
                }
            }
            else
            {
                sprintf(filename, "temp_%i_other.png", parts);
                FilePNG().save(filename, Draw::PointsToImage(contour));
                files.push_back(filename);
            }

			parts++;
		}
	}
    printf("-------------------------\n");
	printf("Total: %i consistent parts (Save & recognize taken %f ms)\n", parts, 1000.0*t.getElapsedTime());
	
	if (!automaticMode)
	{
		printf("Press [ENTER] to delete temporary files and close application.\n");
		char buf[80];
		scanf("%c", buf);
		
		for (size_t u = 0; u < files.size(); u++)
			remove(files[u].c_str());
	}
	
	return 0;
}
