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

#include "boost/foreach.hpp"
#include "boost/graph/iteration_macros.hpp"

#include "algebra.h"
#include "molecule.h"
#include "skeleton.h"
#include "exception.h"
#include "segment.h"

using namespace imago;

Molecule::Molecule()
{
}

const Molecule::ChemMapping &Molecule::getMappedLabels() const
{
   return _mapping;
}

Molecule::ChemMapping &Molecule::getMappedLabels()
{
   return _mapping;
}

const std::deque<Label> &Molecule::getLabels() const
{
   return _labels;
}

std::deque<Label> &Molecule::getLabels()
{
   return _labels;
}

const Skeleton::SkeletonGraph & Molecule::getSkeleton() const
{
   return _g;
}

Skeleton::SkeletonGraph & Molecule::getSkeleton()
{
   return _g;
}

void Molecule::mapLabels( std::deque<Label> &unmapped_labels )
{
   double space;
   double bl = bondLength();
   if (bl > 100.0)
      space = 0.3 * bl; //0.3
   else if (bl > 85)
      space = 0.4 * bl; //0.5
   else
      space = 0.46 * bl; //0.7

//   printf("****: %lf %lf\n", bl, space);

   std::vector<Skeleton::Vertex> nearest;

   std::set<Skeleton::Vertex> only_nearest;
   labels.assign(_labels.begin(), _labels.end());
   for (int i = 0; i < labels.size(); ++i)
   {
      Label &l = labels[i];
      boost::property_map<SkeletonGraph, boost::vertex_pos_t>::type
                              positions = boost::get(boost::vertex_pos, _g);
	  
	  space = l.MaxSymbolWidth() * 1.5;
                     
      int nearest = 0;    
      Skeleton::Vertex nearest_vertex;           
      BGL_FORALL_EDGES(e, _g, SkeletonGraph)
      {
         double d1, d2;
         d1 = d2 = 1e16;

   //TODO: image209 double bond disappears somewhere here

         if (boost::degree(boost::source(e, _g), _g) == 1)
            d1 = Algebra::distance2rect(boost::get(positions,
                                                 boost::source(e, _g)), l.rect);

         if (boost::degree(boost::target(e, _g), _g) == 1)
            d2 = Algebra::distance2rect(boost::get(positions,
                                                 boost::target(e, _g)), l.rect);
		 

         if (d1 <= d2 && d1 < space)
         {
            nearest++;
            nearest_vertex = boost::source(e, _g);
         }
         else if (d2 < d1 && d2 < space)
         {
            nearest++;
            nearest_vertex = boost::target(e, _g);
         }
      }
      if (nearest == 1)
         only_nearest.insert(nearest_vertex);
   }

//   BOOST_FOREACH(Label &l, _labels)
   for (int i = 0; i < labels.size(); ++i)
   {
      Label &l = labels[i];
#ifdef DEBUG
      printf("LABELS: %d %d\n", l.rect.x, l.rect.y);
#endif
      nearest.clear();
	  space = l.MaxSymbolWidth() * 1.5;
      //TODO: check if it's needed to do on each iteration
      boost::property_map<SkeletonGraph, boost::vertex_pos_t>::type
                              positions = boost::get(boost::vertex_pos, _g);

      BGL_FORALL_EDGES(e, _g, SkeletonGraph)
      {
         double d1, d2;
         d1 = d2 = 1e16;

   //TODO: image209 double bond disappears somewhere here

         if (boost::degree(boost::source(e, _g), _g) == 1)
            d1 = Algebra::distance2rect(boost::get(positions,
                                                 boost::source(e, _g)), l.rect);

         if (boost::degree(boost::target(e, _g), _g) == 1)
            d2 = Algebra::distance2rect(boost::get(positions,
                                                 boost::target(e, _g)), l.rect);

         if (d1 <= d2 && d1 < space)
            nearest.push_back(boost::source(e, _g));
         else if (d2 < d1 && d2 < space)
            nearest.push_back(boost::target(e, _g));
      }

      if (nearest.size() > 1)
      {
         for (std::vector<Skeleton::Vertex>::iterator it = nearest.begin(),
              end = nearest.end(); it != nearest.end();)// || nearest.size() != 1;)
         {
            if (only_nearest.find(*it) == only_nearest.end())
               ++it;
            else
            {
               it = nearest.erase(it);
            }
         }
      }

      int s = nearest.size();
      if (s == 0)
      {
         unmapped_labels.push_back(l);
         continue;
      }

      if (s == 1)
      {
         _mapping[nearest[0]] = &l;
         continue;
      }

      Vec2d middle;
      for (int j = 0; j < s; j++)
      {
         for (int k = j + 1; k < s; k++)
         {
            Skeleton::Vertex a, b;
            Skeleton::Vertex c, d;
            a = nearest[j];
            b = nearest[k];
            c = *boost::adjacent_vertices(a, _g).first;
            d = *boost::adjacent_vertices(b, _g).first;

            Vec2d n1, n2;
            Vec2d v_a, v_b, v_c, v_d;
            v_a = boost::get(positions, a);
            v_b = boost::get(positions, b);
            v_c = boost::get(positions, c);
            v_d = boost::get(positions, d);
            n1.diff(v_a, v_c);
            n2.diff(v_b, v_d);

            Vec2d m;
            //TODO: Check whether this is right
            try
            {
               double ang = Vec2d::angle(n1, n2);
               if (fabs(ang) < 0.25 ||
                   fabs(ang - PI) < 0.25)
                  throw Exception("Jumping to catch");
               else
                  m.copy(Algebra::linesIntersection(v_a, v_c, v_b, v_d));
            } catch (Exception &)
            {
               m.middle(v_a, v_b);
            }

            middle.add(m);
         }
      }
      
      middle.scale(2.0 / (s * (s - 1)));
      Vertex newVertex = addVertex(middle);
      for (int j = 0; j < s; j++)
      {
         Vertex e = nearest[j];
         Vertex b = *boost::adjacent_vertices(e, _g).first;
         Edge bond = boost::edge(e, b, _g).first;
         BondType t = boost::get(boost::edge_type, _g, bond).type;

         boost::remove_edge(bond, _g);
         boost::remove_vertex(e, _g);
         addBond(b, newVertex, t);
      }
      _mapping[newVertex] = &l;
   }

   std::deque<Skeleton::Vertex> deck;

   //Removing dots without labels
   

   BGL_FORALL_VERTICES(v, _g, SkeletonGraph)
   {
      if (boost::degree(v, _g) == 0 && _mapping.find(v) == _mapping.end())
         deck.push_back(v);
   }
   


   BOOST_FOREACH(Skeleton::Vertex v, deck)
      boost::remove_vertex(v, _g);
}

void Molecule::aromatize( Points2d &aromatic_centers )
{      
   BOOST_FOREACH( Vec2d arom_center, aromatic_centers )
   {
      Vertex begin_vertex = (Vertex)0; 
      double distance = 1e10;
  
      BGL_FORALL_VERTICES(v, _g, SkeletonGraph)
      {
         double tmp = Vec2d::distance(arom_center, getVertexPos(v));
   
         if (tmp < distance)
         {
            distance = tmp;
            begin_vertex = v;
         }
      }

      Vertex cur_vertex = begin_vertex, prev_vertex = (Vertex)0, next_vertex = (Vertex)0;
   
      std::vector<Edge> aromatized_bonds;

      do
      {         
         distance = 1e10;

         BGL_FORALL_ADJ(cur_vertex, u, _g, SkeletonGraph)
         {
            Vec2d bond_middle;
            bond_middle.middle(getVertexPos(cur_vertex), getVertexPos(u));
            double tmp = Vec2d::distance(arom_center, bond_middle); 

            if (tmp < distance)
            {
               if (u != prev_vertex)
               {
                  distance = tmp;
                  next_vertex = u;
               }
            }
         } 

         if (next_vertex == cur_vertex || next_vertex == (Vertex)NULL)
            break;

         std::pair<Edge, bool> p = boost::edge(cur_vertex, next_vertex, _g);

         if (p.second)
            aromatized_bonds.push_back(p.first);

         if ((int)aromatized_bonds.size() >= getEdgesCount())
            break;

         prev_vertex = cur_vertex;
         cur_vertex = next_vertex;

      } while (cur_vertex != begin_vertex);

      //TODO: Aromatizing only closed contours! Not sure if it's true.
      if (cur_vertex == begin_vertex)
         BOOST_FOREACH( Edge e, aromatized_bonds )
            setBondType(e, AROMATIC);

      aromatized_bonds.clear();
   }
}

void Molecule::clear()
{
   Skeleton::clear();
   _labels.clear();
   _mapping.clear();
}

Molecule::~Molecule()
{
   clear();
}
