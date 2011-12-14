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

#include <algorithm>
#include <vector>
#include <cfloat>

#include "boost/foreach.hpp"
//#include "boost/bind.hpp"
#include "boost/graph/connected_components.hpp"

#include "label_combiner.h"
#include "recognition_settings.h"
#include "current_session.h"
//#include "font.h"
#include "character_recognizer.h"
#include "rng_builder.h"
#include "segments_graph.h"
#include "image_utils.h"
#include "image_draw_utils.h"
#include "output.h"
#include "png_saver.h"
#include "algebra.h"

using namespace imago;

LabelCombiner::LabelCombiner( SegmentDeque &symbols_layer,
                              SegmentDeque &other_layer, int cap_height,
                              const CharacterRecognizer &cr ) :
   _symbols_layer(symbols_layer),
   _cr(cr),
   _cap_height(cap_height)
{
   RecognitionSettings &rs = getSettings();
   setParameters((double)rs["CapHeightErr"], (double)rs["MaxSymRatio"],
                 (double)rs["MinSymRatio"]);

   _imgWidth = rs["imgWidth"];
   _imgHeight = rs["imgHeight"];

   _cap_height = _findCapitalHeight();
   rs["CapitalHeight"] = _cap_height;

   if (cap_height != -1)
   {
      _cap_height_error = (double)rs["CapHeightErr"];
      _space = _cap_height >> 1;

      _fetchSymbols(other_layer);

      _locateLabels();
      BOOST_FOREACH(Label &l, _labels)
         _fillLabelInfo(l);
   }
}

void LabelCombiner::setParameters( double capHeightError, double maxSymRatio,
                                   double minSymRatio )
{
   _cap_height_error = capHeightError;
   _maxSymRatio = maxSymRatio;
   _minSymRatio = minSymRatio;
}

int LabelCombiner::_findCapitalHeight()
{
   //TODO: If it belongs here then rewrite
   int mean_height = 0, seg_height, cap_height = -1;
   BOOST_FOREACH(Segment *seg, _symbols_layer)
      mean_height += seg->getHeight();
   mean_height /= _symbols_layer.size();

   double d = DBL_MAX, min_d = DBL_MAX;
   BOOST_FOREACH(Segment *seg, _symbols_layer)
   {
      try
      {
         char c = _cr.recognize(*seg, CharacterRecognizer::upper, &d);
      }
      catch(OCRException &e)
      {}
      seg_height = seg->getHeight();
      
      if (d < min_d && seg_height >= mean_height)
         min_d = d, cap_height = seg_height;
   }

   //TODO: temporary!
   //if (cap_height == -1)
     // throw LogicException("Cannot determine CapHeight");
   
   return cap_height;
}

void LabelCombiner::_fetchSymbols( SegmentDeque &layer )
{
   SegmentDeque::iterator cur_s, next_s;
   SegmentDeque::iterator cur_l;
   int count = 0;
   for (cur_s = layer.begin(); cur_s != layer.end(); cur_s = next_s)
   {
      next_s = cur_s + 1;

      if (getSettings()["DebugSession"])
         ImageUtils::saveImageToFile(**cur_s, "output/tmp_fetch.png");

      if ((*cur_s)->getHeight() > _cap_height + (int)getSettings()["SymHeightErr"])
         continue;

      int angle;
      ImageUtils::testVertHorLine(**cur_s, angle);

      Rectangle seg_rect = (*cur_s)->getRectangle();
      double r = (*cur_s)->getRatio();

      if (angle != -1)
      {
         bool minus = ImageUtils::testMinus(**cur_s, _cap_height);
         bool plus = ImageUtils::testPlus(**cur_s);

         if (minus)
            puts("MINUS!!!");

         if (plus)
            puts("PLUS!!!");

         if (!plus && !minus)
         {
            if (ImageUtils::testSlashLine(**cur_s, 0, 3.3)) //TODO: Handwriting, original 1.3
               continue;   
            if ((seg_rect.height < 0.45 * _cap_height || seg_rect.height > 1.2 * _cap_height || //0.65 //0.42
                r > _maxSymRatio || r < _minSymRatio))
               continue;
         }
      }

      for (cur_l = _symbols_layer.begin(); cur_l != _symbols_layer.end(); ++cur_l)
      {
         //if (Vec2d::distance2rect(center, cur_l->x, cur_l->y, cur_l->width,
         //                         cur_l->height) < _space)
         Rectangle rect = (*cur_l)->getRectangle();
         if (Rectangle::distance(seg_rect, rect) > _space)
            continue;

         int h1 = (int)absolute(rect.y - seg_rect.y - 0.5 * seg_rect.height); //TODO: Handwriting. Original 0.4
         int h2 = (int)absolute(rect.y + 0.5 * rect.height - seg_rect.y);
         int h3 = (int)absolute(rect.y + rect.height - seg_rect.y -
                                seg_rect.height);
         int h4 = (int)absolute(rect.y + rect.height - seg_rect.y -
                                0.5 * seg_rect.height);

         if (h1 > 1.1 * _space && //TODO: Handwriting.Original 0.5 //superscript
             (h2 > 0.6 * _space || h3 > 0.5 * _space) && //lowercase letter
             h4 > 0.5 * _space)                          //subscript
            continue;
         
         _symbols_layer.push_back(*cur_s);
         std::swap(*(layer.begin() + (count++)), *cur_s); //Do i need next?
         break;
      }
   }
   layer.erase(layer.begin(), layer.begin() + count);
}

void LabelCombiner::extractLabels( std::deque<Label> &labels )
{
   labels.assign(_labels.begin(), _labels.end());
}

void LabelCombiner::_locateLabels()
{
   using namespace segments_graph;

   SegmentsGraph seg_graph;
   add_segment_range(_symbols_layer.begin(), _symbols_layer.end(), seg_graph);

   RNGBuilder::build(seg_graph);
   
   VertexPosMap::type positions = get(boost::vertex_pos, seg_graph);
   SegmentsGraph::edge_iterator ei, ei_end, next;
   tie(ei, ei_end) = boost::edges(seg_graph);

   RecognitionSettings &rs = getSettings();

   for (next = ei; ei != ei_end; ei = next)
   {
      Vec2d b_pos = positions[boost::source(*ei, seg_graph)],
            e_pos = positions[boost::target(*ei, seg_graph)];
      
      double length = Vec2d::distance(b_pos, e_pos);
      ++next;
      //TODO: Find an appropriate length!
      if (length > (_space * 0.5 + 1.25 * _cap_height)) // ||
          //(fabs(k) > _parLinesEps && fabs(fabs(k) - PI) > _parLinesEps &&
          // fabs(k - PI_2) > _parLinesEps &&
          // fabs(fabs(k - PI_2) - PI) > _parLinesEps))
         boost::remove_edge(*ei, seg_graph);
   }
   
   if (rs["DebugSession"])
   {
      Image img(_imgWidth, _imgHeight);
      img.fillWhite();
      ImageDrawUtils::putGraph(img, seg_graph);
      ImageUtils::saveImageToFile(img, "output/lc_rng.png");
   }

   std::vector<int> _components(boost::num_vertices(seg_graph));
   int cc = boost::connected_components(seg_graph, &_components[0]);
   std::vector<std::vector<int> > components(cc);
   for (int i = 0; i < (int)_components.size(); i++)
      components[_components[i]].push_back(i);

   boost::property_map<segments_graph::SegmentsGraph, boost::vertex_seg_ptr_t>::
                   type seg_ptrs = boost::get(boost::vertex_seg_ptr, seg_graph);
   _labels.resize(cc);
   for (int i = 0; i < (int)components.size(); i++)
   {
      //printf("Component %d\n\t", i);
      _labels[i].symbols.resize(components[i].size());
      for (int j = 0; j < (int)components[i].size(); j++)
      {
         //printf("%d ", components[i][j]);
         _labels[i].symbols[j] = boost::get(seg_ptrs, boost::vertex(
                                            components[i][j], seg_graph));
      }
      //printf("\n");
   }
}

void LabelCombiner::_fillLabelInfo( Label &l )
{
   std::vector<Segment*> &symbols = l.symbols;
   int size = symbols.size();
   std::sort(symbols.begin(), symbols.end(), _segmentsComparator);

   int first_line_y = -1;
   int new_line_sep = -1;
   for (int i = 0, first_cap = -1; i < size; i++)
   {
      if (first_cap < 0 && symbols[i]->getHeight() > _cap_height_error *
                                                       _cap_height)
      {
         first_cap = i;
         first_line_y = symbols[i]->getY() + symbols[i]->getHeight();
         continue;
      }
      
      if (first_cap >= 0)
      {
         int mid = (int)(symbols[i]->getY() +
                         0.5 * symbols[i]->getHeight());

         if (mid - first_line_y > _space)
         {
            new_line_sep = i;
            break;
         }
      }
   }

   if (new_line_sep > 0)
   {
      const Segment *seg1, *seg2;

      l.rect.y = symbols[0]->getY();
      std::sort(symbols.begin(), symbols.begin() + new_line_sep, _segmentsCompareX);
      l.rect.x = symbols[0]->getX();

      seg1 = symbols[size - 1];
      l.rect.height = seg1->getY() + seg1->getHeight() - l.rect.y;
      std::sort(symbols.begin() + new_line_sep, symbols.end(), _segmentsCompareX);
      
      seg1 = symbols[new_line_sep - 1];
      seg2 = symbols[size - 1];
      l.rect.width = std::max(seg1->getX() + seg1->getWidth(),
                              seg2->getX() + seg2->getWidth()) - l.rect.x;

      l.line_y = first_line_y;
      l.multi_begin = new_line_sep;
      for (int i = new_line_sep; i < size; i++)
      {
         if (symbols[i]->getHeight() > _cap_height_error * _cap_height)
         {
            l.multi_line_y = symbols[i]->getY() + symbols[i]->getHeight();
            break;
         }
      }
   } 
   else
   {
      const Segment *seg1;
      l.rect.y = symbols[0]->getY();
      seg1 = symbols[size - 1];
      l.rect.height = seg1->getY() + seg1->getHeight() - l.rect.y;

      std::sort(symbols.begin(), symbols.end(), _segmentsCompareX);

      l.rect.x = symbols[0]->getX();
      seg1 = symbols[size - 1];
      l.rect.width = seg1->getX() + seg1->getWidth() - l.rect.x;

      l.line_y = first_line_y;
   }

   /*for (int j = 0, end = sep; j < (int)l.symbols.size(); j = sep, end = l.symbols.size())
   {
      for (int i = j; i < end; i++)
      {

      }
   }*/
}

bool LabelCombiner::_segmentsComparator( const Segment* const &a,
                                         const Segment* const &b )
{
   if (a->getY() < b->getY())
      return true;
   else if (a->getY() == b->getY())
   {
      if (a->getX() < b->getX())
         return true;
   }
   
   return false;      
}

bool LabelCombiner::_segmentsCompareX( const Segment* const &a,
                                       const Segment* const &b )
{
   if (a->getX() < b->getX())
      return true;

   return false;
}


LabelCombiner::~LabelCombiner()
{
}
