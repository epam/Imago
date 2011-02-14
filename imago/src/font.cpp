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

#include <cstring>
#include <cmath>
#include <cfloat>
#include <deque>
#include <vector>

#include "boost/foreach.hpp"

#include "exception.h"
#include "font.h"
#include "fourier_descriptors.h"
#include "png_loader.h"
#include "image.h"
#include "segment.h"
#include "image_utils.h"
#include "segmentator.h"

using namespace imago;

Font::Font( const char *filename, int descCount )
{
   _count = descCount;
   int s = 0;
   s = strlen(filename);
   while (filename[s - 1] != '.')
      s--;

   if (strcmp(filename + s, "png") == 0)
      _loadFromImage(filename);
   else if (strcmp(filename + s, "font") == 0)
      _loadFromFile(filename);
   else
      throw LogicException("Unsupported font file format: %s", filename);
}

Font::Font( int font_id )
{
   if (font_id >= 0 && font_id < MAX_FONTS)
   {
      switch (font_id)
      {
      case ARIAL:
         _loadArial();
         break;
      case ARIAL_BOLD:
         _loadArialBold();
         break;
      case SERIF:
         _loadSerif();
         break;
      }
   }
   else
      throw LogicException("Undefinded built in font specified: %d", font_id);
}
Font::~Font()
{
}

#define FONT_INIT(ch)                                 \
   do                                                 \
   {                                                  \
      _symbols.push_back(FontItem());                 \
      FontItem *fi = &(_symbols[_symbols.size() - 1]);\
      const char *str = #ch;                          \
      fi->sym = str[0];                               \
      double *arr_ptr;                                \
      arr_ptr = descr_##ch;                           \
      _mapping[fi->sym] = _symbols.size() - 1;        \
      fi->features.descriptors.resize(2 * _count);    \
      fi->features.inner_contours_count = -1;         \
      for (int i = 0; i < _count * 2; i++)            \
         fi->features.descriptors[i] = arr_ptr[i];    \
   } while (0);

void Font::_loadArial()
{
   _mapping.resize(255);
#include "arial.font.inc"
}

void Font::_loadArialBold()
{
   _mapping.resize(255);
#include "arial_bold.font.inc"
}

void Font::_loadSerif()
{
   _mapping.resize(255);
#include "serif.font.inc"
}

#undef FONT_INIT

void Font::_loadFromFile( const char *filename )
{
   FILE *fin = fopen(filename, "r");
   _mapping.resize(255);
   fscanf(fin, "%d\n", &_count);
   for (;;)
   {
      if (feof(fin))
         break;

      _symbols.push_back(FontItem());
      FontItem *fi = &_symbols[_symbols.size() - 1];
      fscanf(fin, "%c %d\n", &fi->sym, &fi->features.inner_contours_count);
      _mapping[fi->sym] = _symbols.size() - 1;
      fi->features.descriptors.resize(2 * _count);
      for (int i = 0; i < 2 * _count; i++)
      {
         fscanf(fin, "%lf ", &fi->features.descriptors[i]);
      }
      fscanf(fin, "\n");
      fi->features.inner_descriptors.resize(fi->features.inner_contours_count);
      for (int i = 0; i < fi->features.inner_contours_count; i++)
      {
         fi->features.inner_descriptors[i].resize(2 * _count);
         for (int j = 0; j < 2 * _count; j++)
         {
            fscanf(fin, " %lf", &fi->features.inner_descriptors[i][j]);
         }
         fscanf(fin, "\n");
      }
   }
   fclose(fin);
}

char Font::findBest( const SymbolFeatures &features, int begin, int end,
                     double *dist ) const
{
   char res = 0;
   double d, min_d = DBL_MAX;
   
   for (int i = begin; i < end; i++)
   {
      d = _compare(i, features);

      if (d < min_d)
      {
         res = _symbols[i].sym;
         min_d = d;
      }
   }

   if (dist)
      *dist = min_d;

   return res;
}

char Font::findBest( const Segment *img, int begin, int end,
                     double *dist ) const
{
   img->initFeatures(_count);
   return findBest(img->getFeatures(), begin, end, dist);
}

char Font::findBest( const Segment *img, const std::string &letters,
                     double *dist ) const
{
   char res = 0;
   double d, min_d = 1e10;
   int ind;

   img->initFeatures(_count);
   
   for (int i = 0; i < (int)letters.size(); i++)
   {
      ind = _mapping[letters[i]];
      d = _compare(ind, img->getFeatures());

      if (d < min_d)
      {
         res = _symbols[ind].sym;
         min_d = d;
      }
   }

   if (dist)
      *dist = min_d;
   
   return res;
}

int Font::findCapitalHeight( SegmentDeque &segments ) const
{
   int cap_height = 0;
   int mean_height = 0;
   int seg_height;
   double d, min_d = 1e10;
   int k = 0;

   BOOST_FOREACH( Segment *s, segments )
      mean_height += s->getHeight();
   
   mean_height = mean_height / segments.size();

   BOOST_FOREACH( Segment *seg, segments )
   {
      seg->initFeatures(_count);
      
      for (int i = 0; i < (int)_symbols.size(); i++)
      {
         if (_symbols[i].sym >= 'A' && _symbols[i].sym <= 'Z')
         {         
            d = _compare(i, seg->getFeatures());
            seg_height = seg->getHeight();
            
            if (d < min_d && seg_height >= mean_height)
            {
               min_d = d;
               cap_height = seg_height;
            }
         }
      }
      k++;
   }

   return cap_height;
}

double Font::_compareDescriptors( const std::vector<double> &d1,
                                  const std::vector<double> &d2 )
{
   int s = (int)std::min(d1.size(), d2.size());
   double d = 0;
   double r;
   double weight = 1;
   
   for (int i = 0; i < s; i++)
   {
      r = d1[i] - d2[i];

      if (i % 2)
         weight = 0.5;
      else
         weight = 1.5;
      
      d += weight * r * r;
   }

   return d;
}

double Font::_compare( int ind, const SymbolFeatures &features ) const
{
   double d ;
   
   d = _compareDescriptors(_symbols[ind].features.descriptors,
                           features.descriptors);

   if (_symbols[ind].features.inner_contours_count < 0)
      return sqrt(d);
   
   if (_symbols[ind].features.inner_contours_count !=
       features.inner_contours_count)
      return DBL_MAX;

   for (int i = 0; i < _symbols[ind].features.inner_contours_count; i++)
      d += _compareDescriptors(_symbols[ind].features.inner_descriptors[i],
                               features.inner_descriptors[i]);
   return sqrt(d);
}
   
void Font::_loadFromImage( const char *imgname )
{
   Image img;
   SegmentDeque segments;

   ImageUtils::loadImageFromFile(img, imgname);
   Segmentator::segmentate(img, segments);

   _mapping.resize(255);
   SegmentDeque::iterator it = segments.begin();
   for (int i = 0; i < (int)segments.size() - 2; i++)
   {      
      if (i == 34 || i == 35)
         ++it;

      _symbols.push_back(FontItem());
      FontItem *fi = &_symbols[_symbols.size() - 1];
      Segment *segment = *it;

      ++it;

      segment->initFeatures(_count);   
      fi->features = segment->getFeatures();

      if (i < 26) //"Constants", not config maybe ?
         fi->sym = 'A' + i;
      else if (i < 52)
         fi->sym = 'a' + (i - 26);
      else if (i < 62)
         fi->sym = '0' + (i - 52);

      _mapping[fi->sym] = _symbols.size() - 1;
   }
}
