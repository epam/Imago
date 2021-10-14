/****************************************************************************
* Copyright (C) from 2009 to Present EPAM Systems.
*
* This file is part of Imago toolkit.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***************************************************************************/

#pragma once
#ifndef _pixel_boundings_h
#define _pixel_boundings_h

#include "vec2d.h"
#include "stl_fwd.h"
#include "rectangle.h"

namespace imago
{	
	class RectShapedBounding
	{
	public:
		RectShapedBounding(const RectShapedBounding& src);
		RectShapedBounding(const Points2i& pts);

		inline const Rectangle& getBounding() const { return bound; }

	private:
		Rectangle bound;
	};
}

#endif //_pixel_boundings_h
