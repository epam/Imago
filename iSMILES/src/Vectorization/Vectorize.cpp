#include "Vectorize.h"
#include "ContourSplit.h"
#include "../Parameters.h"
#ifdef DEBUG
#include <stdio.h> // printf "log"
#endif

namespace gga
{
    Vectorize::Vectorize(const Image& image) 
    : SourceImage(image), Map(image.getWidth(), image.getHeight())
    {
        getContours();
        extractConsistent();
        recognizeLines();
        regroupLines();
        extractTriangles();        
    }
    
    void Vectorize::getContours()
    {
        Point p(0,0); // line-by-line scan to extract contours of objects
        for (p.Y = 0; p.Y < SourceImage.getHeight(); p.Y++)
        {
            for (p.X = 0; p.X < SourceImage.getWidth(); p.X++)
            {
                if (SourceImage.isFilled(p) && !Map.isAssigned(p))
                {
                    // that pixel is unprocessed yet, so extract the contour starting from it
                    Contour* c = new Contour(SourceImage, Map, p);
                    // add new contour
                    AllContours.push_back(c);
                }
            }
        }
    }
    
    void Vectorize::extractConsistent()
    {
        for (size_t u = 0; u < AllContours.size(); u++)
        {
            if (Bounds(*AllContours[u]).getArea() >= getGlobalParams().getMinimalConsistentArea())
                RecOther.push_back(AllContours[u]);
        }
    }
    
    void Vectorize::recognizeLines()
    {
        for (size_t u = 0; u < RecOther.size(); )
        {
            ContourSplit cs(*RecOther[u]);
            
            bool AllGood = true;
            for (ContourSplit::Contours::const_iterator it = cs.getSplit().begin(); it != cs.getSplit().end(); it++)
            {            
                LinearApproximation line(*it);
                if (line.isGood())
                {
                    RecLines.push_back(line.getLine());                    
                }
                else
                {
                    AllGood = false;
                }                    
            }
            
            if (AllGood)
            {
                RecOther.erase(RecOther.begin() + u);                
            }
            else
            {
                u++;                
            }
        }
    }
    
    void Vectorize::regroupLines()
    {
        VertexRegroup regroup(RecLines);
        RecLines = regroup.getResult();
    }
    
    void Vectorize::extractTriangles()
    {
        for (size_t u = 0; u < RecLines.size(); )
        {
            TriangleRecognize triangle(RecLines[u], Map);
            if (triangle.isGood())
            {
                RecTriangles.push_back(triangle.getTriangle());
                RecLines.erase(RecLines.begin() + u);
            }
            else
                u++;
        }
    }
    
    Vectorize::~Vectorize()
    {
        for (size_t u = 0; u < AllContours.size(); u++)
            delete AllContours[u];
    }
}

