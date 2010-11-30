#pragma once

#define DEBUG

namespace gga
{
    class Parameters
    {
        unsigned int LineWidth;
    public:
        Parameters() { setLineWidth(4); }

        /* call the prepareImageForVectorization() method? */
        bool isClearImageRequired() const { return true; }
        
        /* Minimal allowed rotation angle on rotation correction for text recognize */
        int getMinimalAllowedRotationAngle() const { return 5; }

        // ---------------------- line & area sizes ---------------------- //
        /* update the line width value */
        void setLineWidth(unsigned int value) { LineWidth = value; }
        
        /* average ink line width, pixels */
        unsigned int getLineWidth() const { return LineWidth; }

        /* minimal consistent line length, pixels */
        unsigned int getMinimalLineLength() const { return 4 * LineWidth; }

        /* all coherent image parts with area less that constant will be ignored, pixels^2 */
        unsigned int getMinimalConsistentArea() const { return LineWidth * getMinimalLineLength(); }
        
        // ---------------------- vectorization consts ---------------------- //
        /* minimal distance between Y coordinates of line points to evaluate angle coefficient:
         * k = (x-x0)/(y-yo) */
        unsigned int getLinearApproximationStep() const { return 2 * LineWidth; }
        
        /* target groups count for classification algorithm in linear approximator, groups */
        unsigned int getTargetGroupsCount() const { return 10; }
        
        /* maximal distance between first and last triangle segment endpoints, pixels */
        unsigned int getMaxTriangleBreakDistance() const { return 5 * LineWidth; }
        
        /* minimal ratio longer/smaller side for determine triangle is up-side link */
        double getTriangleSideRatio() const { return 1.5; }
        
        /* maximal std.dev. value for lines */
        double getDeviationThreshold() const { return 0.4; }
    };
    
    Parameters& getGlobalParams();
}



