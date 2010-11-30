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

#include <list>
#include <vector>
#include <algorithm>
#include <deque>
#include <cstdio>
#include <cmath>

#include "boost/foreach.hpp"

#include "comdef.h"
#include "current_session.h"
#include "exception.h"
#include "image.h"
#include "image_utils.h"
#include "image_draw_utils.h"
#include "separator.h"
#include "segment.h"
#include "segmentator.h"
#include "stat_utils.h"
#include "recognition_settings.h"

using namespace imago;

Separator::Separator( SegmentDeque &segs, const Image &img ) : _segs(segs), _img(img)
{
   std::sort(_segs.begin(), _segs.end(), _segmentsComparator);

   RecognitionSettings &rs = gSession.get()->settings();

   rs.set("SegmentVerEps", 4);
   rs.set("SymHeightErr", 6);
   rs.set("DoubleBondDist", 20);   
}

void Separator::firstSeparation( SegmentDeque &layer_symbols, 
   SegmentDeque &layer_graphics )
{
   int cap_height;
   IntVector suspicious_segments;
   RecognitionSettings &rs = getSettings();
   SegmentDeque layer_suspicious;

   cap_height = _estimateCapHeight();   

   rs.set("CapitalHeight", cap_height);

   //Assume that there are no symbols in the picture
   if (cap_height == -1)
   {
      BOOST_FOREACH( Segment *s, _segs )
         layer_graphics.push_back(s);
   }
   else
   {
      int sym_height_err = rs["SymHeightErr"];
      double susp_seg_density = rs["SuspSegDensity"],
             adequate_ratio_max = rs["MaxSymRatio"],
             adequate_ratio_min = rs["MinSymRatio"];
      IntVector seg_marks, suspicious_segments;
      
      /* Classification procedure */
      BOOST_FOREACH( Segment *s, _segs )
      {
         int mark;

         if (rs["DebugSession"])
            ImageUtils::saveImageToFile(*s, "output/tmp.png");

         if (s->getHeight() >= cap_height - sym_height_err && 
             s->getHeight() <= cap_height + sym_height_err) 
            if (s->getRatio() > adequate_ratio_max)
               if (ImageUtils::testSlashLine(*s, 0, 3.2)) //TODO: To rs immediately. Original is 1.0
                  mark = SEP_BOND;
               else
                  mark = SEP_SPECIAL;
            else
               if (s->getRatio() < adequate_ratio_min)
                  if (_testDoubleBondV(*s))
                     mark = SEP_BOND;
                  else
                     mark = SEP_SUSPICIOUS;
                     
               else
                  if (ImageUtils::testSlashLine(*s, 0, 7.0)) //TODO: To rs immediately. Original is 1.3 
                     mark = SEP_BOND;
                  else 
                     mark = SEP_SYMBOL;
         else
            mark = SEP_BOND;

         switch (mark)
         {
         case SEP_BOND:
            layer_graphics.push_back(s);
            break;
         case SEP_SYMBOL:
            layer_symbols.push_back(s);
            break;
         case SEP_SPECIAL:
            if ((s)->getDensity() < susp_seg_density)
               layer_graphics.push_back(s);
            else
               layer_symbols.push_back(s);
            break;
         case SEP_SUSPICIOUS:
            layer_suspicious.push_back(s);
         }
      }
   }

   BOOST_FOREACH( Segment *s, layer_suspicious )
   {
      //TODO: Handwriting
     // if (!_isSuspiciousSymbol(s, layer_symbols, cap_height))
         layer_graphics.push_back(s);
      //else
        // layer_symbols.push_back(s);
   }

   std::sort(layer_symbols.begin(), layer_symbols.end(), _segmentsComparator);
}

bool Separator::_isSuspiciousSymbol( Segment *cur_seg, SegmentDeque &layer_symbols, int cap_height )
{
   BOOST_FOREACH( Segment *s, layer_symbols)
   {
      int sym_y1 = s->getY(), sym_y2 = s->getY() + s->getHeight(),
         seg_y1 = cur_seg->getY(), seg_y2 = cur_seg->getY() + cur_seg->getHeight();

      if (abs(sym_y2 - seg_y1) <= cap_height * 0.5 || abs(sym_y1 - seg_y2) <= cap_height * 0.5)
      {
         int sym_x = s->getX(), seg_x = cur_seg->getX();

         if (abs(sym_x - seg_x) < s->getWidth())
            return false;
      }
   }

   return true;
}

int Separator::_estimateCapHeight()
{
   typedef std::vector<IntPair> PairIntVector; 
   PairIntVector seq_pairs;
   IntVector heights, seq_lengths;
   IntPair p;
   RecognitionSettings &rs = gSession.get()->settings();

   BOOST_FOREACH( Segment *s, _segs )
      heights.push_back(s->getHeight());

   int seg_ver_eps = rs["SegmentVerEps"];



   for (int i = 0; i != (int)heights.size();)
   {
      int j = i + 1;
      for (; j != (int)heights.size(); j++)
      {
         if (absolute(heights[j - 1] - heights[j]) > seg_ver_eps) 
            break;
      }

      p.first = i;
      p.second = j;

      seq_pairs.push_back(p);

      i += j - i;
   }

   seq_lengths.resize(seq_pairs.size());

   for (int i = 0; i != (int)seq_pairs.size(); i++)
   {      
      seq_lengths[i] = seq_pairs[i].second - seq_pairs[i].first;
   }

   IntVector symbols_found;
   DoubleVector densities(symbols_found.size(), 0.0);
   PairIntVector symbols_graphics(seq_pairs.size());

   int symbols_seq = -1, max_seq_length_i;

   while (true)
   {
      int maximum;
      double density;
      IntPair p;
      IntVector::iterator iter = std::max_element(seq_lengths.begin(), seq_lengths.end());
      
      maximum = *iter;
      max_seq_length_i = std::distance(seq_lengths.begin(), iter);

      if (maximum == -1)
         break;

      seq_lengths[max_seq_length_i] = -1;
      p = seq_pairs[max_seq_length_i];

      density = 0;
      
      if (_checkSequence(p, symbols_graphics[max_seq_length_i], density))
      {
         densities.push_back(density);
         symbols_found.push_back(max_seq_length_i);
      }
   }

   int count = 0;
   symbols_seq = -1;

   for (int i = 0; i != (int)symbols_found.size(); i++)
      if (symbols_graphics[symbols_found[i]].first > count)
      {
         symbols_seq = i;
         count = symbols_graphics[symbols_found[i]].first;
      }

   if (count == 0)
      return -1;

   int cap_height = StatUtils::interMean(heights.begin() + seq_pairs[symbols_found[symbols_seq]].first, 
                                         heights.begin() + seq_pairs[symbols_found[symbols_seq]].second);    

   double cur_density = densities[symbols_seq];

   for (int i = 0; i != (int)symbols_found.size(); i++)
   {
      if (absolute(count - symbols_graphics[symbols_found[i]].first) < 2)
      {  
         if (densities[i] > cur_density)
         {
            symbols_seq = i;
            cap_height = StatUtils::interMean(heights.begin() + seq_pairs[symbols_found[symbols_seq]].first, 
                                              heights.begin() + seq_pairs[symbols_found[symbols_seq]].second); 
            cur_density = densities[i];
         }
      }
   }

   return cap_height;
}

bool Separator::_checkSequence( IntPair &checking, IntPair &symbols_graphics, double &density )
{
   RecognitionSettings &rs = gSession.get()->settings();
   
   //TODO: consider to be dirty hack
   if (checking.second - checking.first == 1)
   {
      if (_segs[checking.first]->getDensity() < 0.2)
      {
         symbols_graphics.first = 1;
         symbols_graphics.second = 0;
         density += _segs[checking.first]->getDensity();

         return true;
      }
   }

   double adequate_ratio_max = rs["MaxSymRatio"],
          adequate_ratio_min = rs["MinSymRatio"];

   for (int i = checking.first; i < checking.second; i++)
   {
      if (_segs[i]->getDensity() > 0.9 && (_segs[i]->getHeight() > _segs[i]->getWidth()))
      {
         if (!_testDoubleBondV(*_segs[i]))
         {
            symbols_graphics.first++;
            density += _segs[i]->getDensity();
         }
      }

      if (_segs[i]->getRatio() >= adequate_ratio_min && 
         _segs[i]->getRatio() <= adequate_ratio_max)
      {         
         if (!ImageUtils::testSlashLine(*_segs[i], 0, 1))
         {
            symbols_graphics.first++;
            density += _segs[i]->getDensity();
         }
         else
            symbols_graphics.second++;
      }
   }

   //Some symbols found in sequence
   if (symbols_graphics.first)
   {
      density /= symbols_graphics.first;
      return true;
   }
   else
      return false;
}

bool Separator::_testDoubleBondV( Segment &segment )
{
   int double_bond_dist;
   double adequate_ratio_min;
   bool ret = false;
   SegmentList segs;
   Segment tmp, segment_tmp;
   RecognitionSettings &rs = gSession.get()->settings();

   adequate_ratio_min = rs["MinSymRatio"];
   double_bond_dist = rs["DoubleBondDist"];

   segment_tmp.emptyCopy(segment);
   segment_tmp.getY() = 0;
   segment_tmp.getX() = segment.getX();
   tmp.init(_img.getWidth(), segment.getHeight());

   {
      int x, y, rows = tmp.getHeight(), cols = tmp.getWidth(),
         y0 = segment.getY();

      for (y = 0; y < rows; y++)
         for (x = 0; x < cols; x++)
            tmp.getByte(x, y) = _img.getByte(x, y + y0);
   }

   ImageUtils::putSegment(tmp, segment_tmp, false);
   Segmentator::segmentate(tmp, segs);

   BOOST_FOREACH( Segment *s, segs )
   {
      if (s->getRatio() <= adequate_ratio_min)
         if (absolute(s->getX() - segment.getX()) < double_bond_dist) 
         {
            ret = true;
            break;
         }
   }

   return ret;
}

bool Separator::_segmentsComparator( Segment *a, Segment *b )
{
   return a->getHeight() < b->getHeight();
}
