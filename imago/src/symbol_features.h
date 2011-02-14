/****************************************************************************
 * Copyright (C) 2009-2010 GGA Software Services LLC
 * 
 * This file is part of Imago toolkit.
 * 
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 3 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 ***************************************************************************/

#ifndef _symbol_features_h
#define _symbol_features_h

#include <vector>

namespace imago
{
    class SymbolFeatures
    {
       friend class Segment;
    public:
       bool recognizable;

       std::vector<double> descriptors; //for outter contour
       int inner_contours_count;
       //descriptors for inner contours (ordered up -> down, left -> right)
       std::vector<std::vector<double> > inner_descriptors;

       SymbolFeatures()
       {
          recognizable = true;
          inner_contours_count = 0;
          init = false;
       };
       
       SymbolFeatures( const SymbolFeatures &other )
       {
          descriptors = other.descriptors;
          inner_contours_count = other.inner_contours_count;
          inner_descriptors = other.inner_descriptors;
          init = other.init;
       }
       bool isInit() { return init; }
    //private:
       bool init;
    };
}

#endif  /* _symbol_features_h */

