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

#ifndef _convolver_h
#define _convolver_h

#include "filter.h"

namespace imago
{
   class Convolver : public Filter
   {
   public:
      Convolver( Image &img );

      bool isInit();
      void deInit();

      void initSharp();
      void initGauss();
      void initSobelX();
      void initSobelY();

      void apply();
      ~Convolver();

   private:

      void _init( int rows, int cols, double _invBias, const int *kernel );

      int *_kernel;
      int _rows, _cols;
      double _invBias;
   };
}


#endif /* _convolver_h */