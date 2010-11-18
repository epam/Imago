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

#include <deque>
#include <vector>
#include "boost/foreach.hpp"

#include "rectangle.h"
#include "segment.h"
#include "vec2d.h"
#include "fourier_descriptors_extractor.h"
#include "segmentator.h"
#include "output.h"
#include "png_saver.h"

using namespace imago;

Segment::Segment()
{
   _density = _ratio = -1;
}

void Segment::copy( const Segment &s )
{
   Image::copy(s);
   _x = s._x;
   _y = s._y;

   _features = s._features;
}

/** 
* @brief Getter for x
* 
* @return const reference to _x
*/
int Segment::getX() const
{
   return _x;
}

/** 
* @brief Getter for y
* 
* @return const reference to _y
*/
int Segment::getY() const
{
   return _y;
}

/** 
* @brief Getter for x
* 
* @return const reference to _x
*/
int &Segment::getX()
{
   return _x;
}

/** 
* @brief Getter for y
* 
* @return const reference to _y
*/
int &Segment::getY()
{
   return _y;
}

Rectangle Segment::getRectangle() const
{
   return Rectangle(_x, _y, _width, _height);
}

double Segment::getRatio() const
{
   if (_ratio < 0)
      return (double)getWidth() / getHeight();

   return _ratio;
}

double Segment::getRatio()
{
   if (_ratio < 0)
   {
      _ratio = getWidth();
      _ratio /= getHeight();
   }

   return _ratio;
}

Vec2d Segment::getCenter() const
{
   return Vec2d(_x + (_width >> 1), _y + (_height >> 1));
}

double Segment::getDensity() const
{
   if (_density < 0)
      return density();

   return _density;
}

double Segment::getDensity()
{
   if (_density < 0)
      _density = density();

   return _density;
}

SymbolFeatures &Segment::getFeatures() const
{
   return _features;
}

SymbolFeatures &Segment::getFeatures()
{
   return _features;
}

void Segment::initFeatures( int descriptorsCount ) const
{
   if (_features.isInit())
      if ((int)_features.descriptors.size() / 2 >=  descriptorsCount)
         return;
   
   FourierDescriptorsExtractor::getDescriptors(this, descriptorsCount,
                                               _features.descriptors);

   //Searching for inner contours

   SegmentDeque segments;
   Segmentator::segmentate(*this, segments, 3, 255); //all white parts

   int x, y, w, h;
   int total = 0;
   int i = 0;
   BOOST_FOREACH(Segment * &seg, segments)
   {
      FileOutput fout("output/seg_%d.png", i++);
      PngSaver(fout).saveImage(*seg);
      
      x = seg->getX(), y = seg->getY();
      w = seg->getWidth(), h = seg->getHeight();

      if (x == 0 || y == 0 || x + w == _width || y + h == _height)
      {
         delete seg;
         seg = 0;
      }
      else
      {
         total++;
      }
   }

   _features.inner_contours_count = total;
   _features.inner_descriptors.resize(total);

   i = 0;
   BOOST_FOREACH(Segment * &seg, segments)
   {
      if (seg != 0)
      {
         std::vector<double> &descr = _features.inner_descriptors[i++];
         FourierDescriptorsExtractor::getDescriptors(seg, descriptorsCount, descr);
      }
   }
   
   _features.init = true;
}

void Segment::splitVert(int x, Segment &left, Segment &right) const
{
   Image::splitVert(x, left, right);
   
   left._x = _x;
   right._x = _x + x;
   left._y = right._y = _y;
}

void Segment::crop()
{
   int w = getWidth(), h = getHeight(), i, j;
   int t = -1, l = -1;

   for (i = 0; i < w * h && t == -1; i++)
      if (this->operator [](i) != 255)
         t = i / w;
   
   for (i = 0; i < w && l == -1; i++)
      for (j = 0; j < h && l == -1; j++)
         if(this->operator [](j * w + i) != 255)
            l = i;

   Image::crop();
   
   _x += l;
   _y += t;
   
}

Segment::~Segment()
{

}
