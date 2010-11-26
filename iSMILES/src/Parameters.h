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
        bool isClearImageRequired() const { return false; }

        // ---------------------- line & area sizes ---------------------- //
        /* update line width value */
        void setLineWidth(unsigned int value) { LineWidth = value; }
        
        /* average ink line width, pixels */
        unsigned int getLineWidth() const { return LineWidth; }

        /* minimal consistent line length, pixels */
        unsigned int getMinimalLineLength() const { return 4 * LineWidth; }

        /* all coherent image parts with area less that constant will be ignored, pixels^2 */
        unsigned int getMinimalConsistentArea() const { return LineWidth * getMinimalLineLength(); }
        
        // ---------------------- linearization consts ---------------------- //
        /* minimal distance between Y coordinates of line points to evaluate angle coefficient:
         * k = (x-x0)/(y-yo) */
        unsigned int getLinearApproximationStep() const { return 2 * LineWidth; }
        
        /* target groups count for classification algorithm in linear approximator */
        unsigned int getTargetGroupsCount() const { return 10; }
    };
    
    static Parameters GlobalParams;
}



