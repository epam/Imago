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
    class Vectorize
    {
        const Image& SourceImage;
        ImageMap  Map;
        PContours AllContours;        
        Triangles RecTriangles;
        Polylines RecLines;   
        PContours RecOther;

    public:
        Vectorize(const Image& image);
        virtual ~Vectorize();

        const  ImageMap& getImageMap() const { return Map; }
        
        const Triangles& getTriangles() const { return RecTriangles; }
        const Polylines& getLines() const { return RecLines; }
        const PContours& getOtherContours() const { return RecOther; }
        
    private:
        void getContours();
        void extractConsistent();
        void recognizeLines();
        void regroupLines();
        void extractTriangles();
    };
}


