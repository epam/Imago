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

/**
 * @file filter.cpp
 * 
 * @brief   Implements the filter class
 */

#include "filter.h"
#include "exception.h"
#include "image.h"

using namespace imago;

Filter::Filter( Image &I ) : _img(I)
{
   if (!_img.isInit())
      throw LogicException("Invalid image");
}

void Filter::apply( Image &res )
{
}

Filter::~Filter()
{
}