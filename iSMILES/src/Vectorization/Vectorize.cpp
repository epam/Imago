#include "Vectorize.h"
#include "../Parameters.h"
#include "SegmentParams.h"
#ifdef DEBUG
#include <stdio.h> // printf "log"
#endif

namespace gga
{
    Vectorize::Vectorize(const Image& image) 
                : SourceImage(image), 
                  Imagemap(image.getWidth(), image.getHeight())
    {
        // step 1. line-by-line scan to extract contours of objects
        Point p(0,0);
        for (p.Y = 0; p.Y < SourceImage.getHeight(); p.Y++)
        {
            for (p.X = 0; p.X < SourceImage.getWidth(); p.X++)
            {
                if (SourceImage.isFilled(p) && !Imagemap.isAssigned(p))
                {
                    // that pixel is unprocessed yet, so extract the contour starting from it
                    Contour* c = new Contour(SourceImage, Imagemap, p);
                    // add new contour
                    Contours.push_back(c);
                }
            } // for x
        } //for y
        
        // step 2. extract consistent parts only
        for (size_t u = 0; u < Contours.size(); u++)
        {
            if (Bounds(*Contours[u]).getArea() >= GlobalParams.getMinimalConsistentArea())
                RecOther.push_back(Contours[u]);
        }
        
        // step 3. extract lines
        for (size_t u = 0; u < RecOther.size(); )
        {
            LinearApproximation line(*RecOther[u]);
            if (line.isGood())
            {
                RecLines.push_back(line.getLine());
                RecOther.erase(RecOther.begin() + u);
            }
            else
                u++;
        }
        
        // step 4.1. extract some segment params
        SegmentParams segParams(RecLines);
        #ifdef DEBUG
            printf("[i] Average line length: %ipx; Image rotation required: %i*\n", 
                segParams.getAverageLineLength(), segParams.getCompensationAngle());
        #endif
        
        // step 4.2. regroup lines
        VertexRegroup regroup(RecLines);
        RecLines = regroup.getResult();
        
        // step 5. extract triangles
        for (size_t u = 0; u < RecLines.size(); )
        {
            TriangleRecognize triangle(RecLines[u], Imagemap);
            if (triangle.isGood())
            {
                RecTriangles.push_back(triangle.getTriangle());
                RecLines.erase(RecLines.begin() + u);
            }
            else
                u++;
        }        
        // that's all.
    }
    
    Vectorize::~Vectorize()
    {
        for (size_t u = 0; u < Contours.size(); u++)
            delete Contours[u];
    }
}

