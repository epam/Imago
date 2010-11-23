#include <stdio.h>
#include <string>
#include "../src/Parameters.h"
#include "../src/Timer.h"
#include "../src/Image/Image.h"
#include "../src/Image/ImageFilter.h"
#include "../src/Image/FilePNG.h"
#include "../src/Image/FileJPG.h"
#include "../src/Vectorization/Vectorize.h"
#include "Draw.h"

using namespace gga;

static std::vector<std::string> files;

void Save(std::string type, const Image& data)
{
    char filename[1024] = {0};
    sprintf(filename, "temp_%i_%s.png", files.size(), type.c_str());
    FilePNG().save(filename, data);
    files.push_back(filename);    
}

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
	
	Timer timer;
	Vectorize vectorized(img);
	printf("Vectorize taken %f ms\n", 1000.0*timer.getElapsedTime());
	timer.reset();	
    
    for (Triangles::const_iterator it = vectorized.getTriangles().begin(); 
        it != vectorized.getTriangles().end(); it++)
            Save("triangle", Draw::TriangleToImage(*it));
    
    for (Polylines::const_iterator it = vectorized.getLines().begin(); 
        it != vectorized.getLines().end(); it++)
            Save("line", Draw::LineToImage(*it));

    for (PContours::const_iterator it = vectorized.getOtherContours().begin(); 
         it != vectorized.getOtherContours().end(); it++)
             Save("other", Draw::PointsToImage(*(*it)));

	printf("Total: %i consistent parts (Save taken %f ms)\n", files.size(), 1000.0*timer.getElapsedTime());
	
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
