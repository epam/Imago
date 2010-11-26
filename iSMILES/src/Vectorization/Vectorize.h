#pragma once
#include <vector>
#include "../Image/Image.h"
#include "Bounds.h"
#include "ImageMap.h"
#include "Contour.h"
#include "RangeArray.h"
#include "LinearApproximation.h"
#include "VertexRegroup.h"
#include "TriangleRecognize.h"

namespace gga
{
    typedef std::vector<Triangle> Triangles;
    typedef std::vector<Contour*> PContours;
    
    class Vectorize
    {
        const Image& SourceImage;
        ImageMap   Imagemap;
        PContours Contours;
        
    private:
        Triangles RecTriangles;
        Polylines RecLines;   
        PContours RecOther;

    public:
        Vectorize(const Image& image);
        ~Vectorize();

        const  ImageMap& getImageMap() const { return Imagemap; }
        
        const Triangles& getTriangles() const { return RecTriangles; }
        const Polylines& getLines() const { return RecLines; }
        const PContours& getOtherContours() const { return RecOther; }
    };
}


