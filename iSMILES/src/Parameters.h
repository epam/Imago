#pragma once

namespace gga
{
    class Parameters
    {
        unsigned int LineWidth;
    public:
        Parameters() { setLineWidth(4); }

        /* call the prepareImageForVectorization() method? */
        bool isClearImageRequired() const { return true; }
        
        /* minimal allowed rotation angle on rotation correction for text recognize, degrees */
        int getMinimalAllowedRotationAngle() const { return 5; }

        // ---------------------- line & area sizes ---------------------- //
        /* update the line width value */
        void setLineWidth(unsigned int value) { LineWidth = value; }
        
        /* average ink line width, pixels */
        // affects most following methods
        // affects ContourSplit.reduceIndexCount()
        unsigned int getLineWidth() const { return LineWidth; }

        /* minimal consistent line length, pixels */
        // affects getMinimalConsistentArea() 
        // affects ContourSplit.intersectIndexes()
        unsigned int getMinimalLineLength() const { return 4 * LineWidth; }

        /* all coherent image parts with area less that constant will be ignored, pixels^2 */
        // affects Vectorization.extractConsistent()
        unsigned int getMinimalConsistentArea() const { return LineWidth * getMinimalLineLength(); }
        
        // ---------------------- vectorization consts ---------------------- //
        /* minimal distance between Y coordinates of line points to evaluate angle coefficient:
         * k = (x-x0)/(y-yo) */
        // affects LinearApproximation.calculateHistogram()
        unsigned int getLinearApproximationStep() const { return 2 * LineWidth; }
        
        /* target groups count for classification algorithm in linear approximator, groups */
        // affects LinearApproximation.calculateHistogram()
        unsigned int getTargetGroupsCount() const { return 10; }

        /* maximal std.dev. value for object to be recognized as line */
        // affects LinearApproximation
        double getDeviationThreshold() const { return 0.5; }
        
        /* each split increments result std.dev. by this factor: */
        // affects LinearApproximation
        double getSplitStdDevFactor() const { return 1.5; }
        
        // ---------------------- vertex regroup params ---------------------- //
        
        /* maximal distance between first and last line segment to concatenate, pixels */
        // affects VertexRegroup.concatenateLines()
        unsigned int getMaxLineBreakDistance() const { return LineWidth; }

        /* maximal distance between possible one line duplicates */
        // affects VertexRegroup.removeDuplicates()
        unsigned int getMaxDuplicateDistance() const { return 2 * LineWidth; }

        /* maximal angle to be eliminated between two neighbor segments in polyline, degrees */
        // affects VertexRegroup.reduceFractures()
        int getMaxFractureAngle() const { return 20; }
        
        // ---------------------- triangle recognition ---------------------- //
        /* maximal distance between first and last triangle segment endpoints, pixels */
        // affects TriangleRecognition
        unsigned int getMaxTriangleBreakDistance() const { return 3 * LineWidth; }
        
        /* minimal ratio longer/smaller side for determine triangle is up-side link */
        // affects TriangleRecognition
        double getTriangleSideRatio() const { return 1.0; } // previosly was 1.5
    };
    
    Parameters& getGlobalParams();
}



