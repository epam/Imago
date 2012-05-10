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
#include "boost/graph/connected_components.hpp"

#include "label_combiner.h"
#include "log_ext.h"
#include "character_recognizer.h"
#include "rng_builder.h"
#include "segments_graph.h"
#include "image_utils.h"
#include "image_draw_utils.h"
#include "output.h"
#include "algebra.h"
#include "constants.h"

using namespace imago;

LabelCombiner::LabelCombiner( SegmentDeque &symbols_layer, SegmentDeque &other_layer, const CharacterRecognizer &cr ) :
   _symbols_layer(symbols_layer), _cr(cr)
   
{
	vars.estimation.CapitalHeight = _findCapitalHeight();

	if (vars.estimation.CapitalHeight > 0.0)
   {
      _locateLabels();
      BOOST_FOREACH(Label &l, _labels)
         _fillLabelInfo(l);
   }
}


int LabelCombiner::_findCapitalHeight()
{
	logEnterFunction();

   //TODO: If it belongs here then rewrite
   int mean_height = 0, seg_height, cap_height = -1;
   BOOST_FOREACH(Segment *seg, _symbols_layer)
   {
	   getLogExt().append("Height", seg->getHeight());
	   mean_height += seg->getHeight();
   }
   mean_height /= _symbols_layer.size();
   getLogExt().append("Mean height", mean_height);

   double d = DBL_MAX, min_d = DBL_MAX;
   BOOST_FOREACH(Segment *seg, _symbols_layer)
   {
	  char c = 0;
      try
      {
		  c = _cr.recognize(*seg, CharacterRecognizer::all, &d);
      }
	  catch(ImagoException &e)
      {
		  logEnterFunction();
		  getLogExt().appendText(e.what());
	  }
	  if (CharacterRecognizer::upper.find(c) != std::string::npos)
	  {
		seg_height = seg->getHeight();
		getLogExt().append("Segment height", seg_height);
      
		if (d < min_d && seg_height >= mean_height)
		{
			 min_d = d;
			 cap_height = seg_height;
		} 
		else if (d < min_d && seg_height > cap_height 
			     && (d < vars.lcomb.MaximalSymbolDistance && c != 'O') )
		{
			min_d = d;
			cap_height = seg_height;
		}
	  }
   }

   //TODO: temporary!
   //if (cap_height == -1)
     // throw LogicException("Cannot determine CapHeight");
   
   getLogExt().append("Capital height", cap_height);

   return cap_height;
}

void LabelCombiner::_fetchSymbols( SegmentDeque &layer )
{
	logEnterFunction();

   SegmentDeque::iterator cur_s, next_s;
   SegmentDeque::iterator cur_l;
   int count = 0;
   for (cur_s = layer.begin(); cur_s != layer.end(); cur_s = next_s)
   {
      next_s = cur_s + 1;

	  getLogExt().appendSegment("Work segment", **cur_s);

	  if ((*cur_s)->getHeight() > (int)(vars.estimation.CapitalHeight + vars.estimation.SymHeightErr))
         continue;

      int angle;
      ImageUtils::testVertHorLine(**cur_s, angle);

      Rectangle seg_rect = (*cur_s)->getRectangle();
      double r = (*cur_s)->getRatio();

      if (angle != -1)
      {
		  bool minus = ImageUtils::testMinus(**cur_s, (int)vars.estimation.CapitalHeight);
         bool plus = ImageUtils::testPlus(**cur_s);

         if (minus)
			 getLogExt().appendText("Minus detected");

         if (plus)
			 getLogExt().appendText("Plus detected");

         if (!plus && !minus)
         {
			 if (ImageUtils::testSlashLine(**cur_s, 0, vars.lcomb.TestSlashLineEps))
               continue;   
			 if (seg_rect.height < vars.lcomb.TestMinHeightFactor * vars.estimation.CapitalHeight 
				 || seg_rect.height > vars.lcomb.TestMaxHeightFactor * vars.estimation.CapitalHeight 
				 || r > vars.estimation.MaxSymRatio|| r < vars.estimation.MinSymRatio)
               continue;
         }
      }

      for (cur_l = _symbols_layer.begin(); cur_l != _symbols_layer.end(); ++cur_l)
      {
         //if (Vec2d::distance2rect(center, cur_l->x, cur_l->y, cur_l->width,
         //                         cur_l->height) < _space)
         Rectangle rect = (*cur_l)->getRectangle();
		 if (Rectangle::distance(seg_rect, rect) > vars.estimation.CharactersSpaceCoeff * vars.estimation.CapitalHeight)
            continue;

		 int h1 = (int)absolute(rect.y - seg_rect.y 
			                    - vars.lcomb.RectHeightRatio * seg_rect.height); 
         int h2 = (int)absolute(rect.y + vars.lcomb.RectHeightRatio * rect.height - seg_rect.y);
         int h3 = (int)absolute(rect.y + rect.height - seg_rect.y -
                                seg_rect.height);
         int h4 = (int)absolute(rect.y + rect.height - seg_rect.y -
                                vars.lcomb.RectHeightRatio * seg_rect.height);

		 double space = vars.estimation.CharactersSpaceCoeff * vars.estimation.CapitalHeight;

		 if (h1 > vars.lcomb.H1SuperscriptSpace * space  &&
			 (h2 > vars.lcomb.H2LowercaseSpace * space || h3 > vars.lcomb.H3LowercaseSpace * space) &&
			 h4 > vars.lcomb.H4SubscriptSpace * space)
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
	logEnterFunction();

   using namespace segments_graph;

   SegmentsGraph seg_graph;
   add_segment_range(_symbols_layer.begin(), _symbols_layer.end(), seg_graph);

   RNGBuilder::build(seg_graph);
   
   VertexPosMap::type positions = get(boost::vertex_pos, seg_graph);
   SegmentsGraph::edge_iterator ei, ei_end, next;
   boost::tie(ei, ei_end) = boost::edges(seg_graph);


   boost::property_map<segments_graph::SegmentsGraph, boost::vertex_seg_ptr_t>::
	   type img_ptrs = boost::get(boost::vertex_seg_ptr, seg_graph);

   
   for (next = ei; ei != ei_end; ei = next)
   {
      Vec2d b_pos = positions[boost::source(*ei, seg_graph)],
            e_pos = positions[boost::target(*ei, seg_graph)];
	  Vec2d dif; 
	  dif.diff(e_pos, b_pos);
	  dif = dif.getNormalized();
	  double sign_x = dif.x>0 ? 1:-1;
	  double sign_y = dif.y>0 ? 1:-1;

	  Segment *s_b = boost::get(img_ptrs, boost::vertex(boost::source(*ei, seg_graph), seg_graph));
	  Segment *s_e = boost::get(img_ptrs, boost::vertex(boost::target(*ei, seg_graph), seg_graph));
      
	  double width_b = s_b->getWidth();
	  double width_e = s_e->getWidth();
	  double width = (width_b+2*width_e)/3;
	  double height = std::min(s_b->getHeight(), s_e->getHeight());

	  double x_b = width_b * sign_x / 2.0 + b_pos.x; 
	  double x_e = -width_e * sign_x / 2.0  + e_pos.x; 

	  double y_b = s_b->getHeight() * sign_y / 2.0  + b_pos.y;
	  double y_e = -s_e->getHeight() * sign_y / 2.0  + e_pos.y;
		
	  if((s_b->getCenter().y < s_e->getCenter().y && s_e->getCenter().y > y_b - height/2 && s_e->getCenter().y < y_b + height/2) ||
		  (s_e->getCenter().y < s_b->getCenter().y && s_b->getCenter().y > y_e - height/2 && s_b->getCenter().y < y_e + height/2))//(height > 3*_cap_height/4)
		  height =std::max(s_b->getHeight(), s_e->getHeight());
	  else
		  height /= 2.0;
      //double length = Vec2d::distance(b_pos, e_pos);
      ++next;
      //TODO: Find an appropriate length!
	  // TODO!
	  if ((fabs(y_e - y_b) < width && fabs((double)(s_b->getCenter().x - s_e->getCenter().x)) < width/2) || 
		  (fabs(x_e - x_b) < width && fabs((double)(s_b->getCenter().y - s_e->getCenter().y)) < height))
          //(fabs(k) > _parLinesEps && fabs(fabs(k) - PI) > _parLinesEps &&
          // fabs(k - PI_2) > _parLinesEps &&
          // fabs(fabs(k - PI_2) - PI) > _parLinesEps))
		  continue;
	  else
         boost::remove_edge(*ei, seg_graph);
   }
   
   getLogExt().appendGraph("seg_graph", seg_graph);

   std::vector<int> _components(boost::num_vertices(seg_graph));
   int cc = boost::connected_components(seg_graph, &_components[0]);
   std::vector<std::vector<int> > components(cc);
   for (size_t i = 0; i < _components.size(); i++)
      components[_components[i]].push_back(i);

   boost::property_map<segments_graph::SegmentsGraph, boost::vertex_seg_ptr_t>::
                   type seg_ptrs = boost::get(boost::vertex_seg_ptr, seg_graph);
   _labels.resize(cc);
   for (size_t i = 0; i < components.size(); i++)
   {      
	   getLogExt().append("Component", i);
	   getLogExt().appendVector("Subcomponents", components[i]);
      _labels[i].symbols.resize(components[i].size());
      for (int j = 0; j < (int)components[i].size(); j++)
      {
         _labels[i].symbols[j] = boost::get(seg_ptrs, boost::vertex(
                                            components[i][j], seg_graph));
      }
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
	   if (first_cap < 0 && symbols[i]->getHeight() > 
		   vars.estimation.CapitalHeightError * vars.lcomb.FillLabelFactor1 * vars.estimation.CapitalHeight)
      {
         first_cap = i;
         first_line_y = symbols[i]->getY() + symbols[i]->getHeight();
         continue;
      }
      
      if (first_cap >= 0)
      {
		  int mid = round(symbols[i]->getY() + vars.lcomb.FillLabelFactor2 * symbols[i]->getHeight());

		  if (mid - first_line_y > vars.estimation.CapitalHeight * vars.estimation.CharactersSpaceCoeff)
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
		  if (symbols[i]->getHeight() > vars.estimation.CapitalHeightError * vars.estimation.CapitalHeight)
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
