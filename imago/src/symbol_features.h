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
    public:
        std::vector<double> descriptors;
        std::vector<double> lines;
        bool recognizable;
        SymbolFeatures() : recognizable(true) {};
    };
}

#endif  /* _symbol_features_h */

