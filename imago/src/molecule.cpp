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
#include "log_ext.h"
#include "recognition_settings.h"

using namespace imago;

#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

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

bool testNear(Vec2d &point, Rectangle &rec, int margin)
{
	int top = rec.y - margin;//std::max<int>(0, rec.y - margin);
	int left = rec.x - margin;//std::max<int>(0, rec.x - margin);

	return point.x < (rec.x + rec.width + margin) &&
		point.x > left && 
		point.y < (rec.y + rec.height + margin) &&
		point.y > top;
}

//returns true if edge is directed to rectangle
// end is the closest point to rectangle
bool testCollision(Vec2d &beg, Vec2d &end, Rectangle &rec)
{
	Vec2d perp(-(end.y - beg.y), end.x - beg.x);
	try{
		perp = perp.getNormalized();
	}catch(DivizionByZeroException &e)
	{
		return false;
	}
	//perp.diff(perp, end);

	Vec2d vec1(rec.x, rec.y), vec2(rec.x + rec.width, rec.y),
		vec3(rec.x, rec.y + rec.height), vec4(rec.x+rec.width, rec.y+rec.height);
	vec1.diff(vec1, end);
	vec2.diff(vec2, end);
	vec3.diff(vec3, end);
	vec4.diff(vec4, end);

	double a1 = Vec2d::dot(perp, vec1);
	double a2 = Vec2d::dot(perp, vec2);
	double a3 = Vec2d::dot(perp, vec3);
	double a4 = Vec2d::dot(perp, vec4);

	double min = std::min<double>(a1, 
		std::min<double>(a2, 
		std::min(a3, a4)));
	double max = std::max<double>(a1, 
		std::max<double>(a2, 
		std::max(a3, a4)));
	return min*max < 0;
}

void Molecule::mapLabels( std::deque<Label> &unmapped_labels )
{
   double space, space2;
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
#ifdef DEBUG
      printf("LABELS: %d %d\n", l.rect.x, l.rect.y);
#endif


      nearest.clear();
	  space = l.MaxSymbolWidth() * 1.5;
	  space2 = l.rect.width < l.rect.height ? l.rect.width : l.rect.height;
	   
	     boost::property_map<SkeletonGraph, boost::vertex_pos_t>::type
                              positions = boost::get(boost::vertex_pos, _g);

      BGL_FORALL_EDGES(e, _g, SkeletonGraph)
      {
         double d1, d2;
         d1 = d2 = 1e16;

		 if(boost::degree(boost::source(e, _g), _g) > 1 &&
			 boost::degree(boost::target(e, _g), _g) > 1)
			 continue;

		 if (boost::degree(boost::source(e, _g), _g) == 1)
            d1 = Algebra::distance2rect(boost::get(positions,
                                                 boost::source(e, _g)), l.rect);

         if (boost::degree(boost::target(e, _g), _g) == 1)
            d2 = Algebra::distance2rect(boost::get(positions,
                                                 boost::target(e, _g)), l.rect);

		 if (d1 <= d2 && ((testCollision(boost::get(positions, boost::target(e, _g)), boost::get(positions, boost::source(e, _g)), l.rect) &&
			 testNear(boost::get(positions, boost::source(e, _g)), l.rect, space)) ||
			 testNear(boost::get(positions, boost::source(e, _g)), l.rect, space2/2)))
            nearest.push_back(boost::source(e, _g));
         else if (d2 < d1 && ((testCollision(boost::get(positions, boost::source(e, _g)), boost::get(positions, boost::target(e, _g)), l.rect) &&
			 testNear(boost::get(positions, boost::target(e, _g)), l.rect, space)) ||
			 testNear(boost::get(positions, boost::target(e, _g)), l.rect, space2/2)))
            nearest.push_back(boost::target(e, _g));
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

void Molecule::_connectBridgedBonds()
{
	logEnterFunction();
	std::vector<float> kFactor;
	std::vector<std::vector<Edge>> edge_groups_k;
	//group all parallel edges by similar factors
	BGL_FORALL_EDGES(edge, _g, SkeletonGraph)
	{
		Bond f = boost::get(boost::edge_type, _g, edge);
		Vec2d p1 = getVertexPos(getBondBegin(edge));
		Vec2d p2 = getVertexPos(getBondEnd(edge));
		double slope = Algebra::slope(p1, p2);
		if(f.type == imago::BondType::SINGLE)
		{
			bool found_kFactor = false;
			for(int i=0 ; i < kFactor.size() ; i++)
			{
				if(fabs(slope - kFactor[i]) < 0.1)
				{
					edge_groups_k[i].push_back(edge);
					found_kFactor = true;
					break;
				}
			}

			if(!found_kFactor)
			{
				edge_groups_k.push_back(std::vector<Edge>());
				edge_groups_k[edge_groups_k.size() - 1].push_back(edge);
				kFactor.push_back(slope);
			}
		}
	}
	getLogExt().append("Group size of edges which could bridge:", edge_groups_k.size());
	std::deque<std::pair<Edge, Edge>> edges_to_connect;

	//check edges to be connected
	for(int i=0;i<edge_groups_k.size();i++)
	{
		int gr_count = edge_groups_k[i].size();
		if( gr_count == 1)
			continue;
		for(int k=0;k<gr_count;k++)
		{
			Vec2d p1 = getVertexPos(getBondBegin(edge_groups_k[i][k]));
			Vec2d p2 = getVertexPos(getBondEnd(edge_groups_k[i][k]));

			for(int l = k + 1;l<gr_count;l++)
			{
				Vec2d sp1 = getVertexPos(getBondBegin(edge_groups_k[i][l]));
				Vec2d sp2 = getVertexPos(getBondEnd(edge_groups_k[i][l]));

				double d1 = Algebra::distance2segment(p1, sp1, sp2);
				double d2 = Algebra::distance2segment(p2, sp1, sp2);

				double min = d1 < d2 ? d1 : d2;

				double LineS = getSettings()["LineThickness"];
				double blockS = LineS * 10.0;

				Line l1 = Algebra::points2line(p1, p2);
				Line l2 = Algebra::points2line(sp1, sp2);

				if(sign(l1.A) != sign(l2.A))
				{
					l2.A *= -1.0;
					l2.B *= -1.0;
					l2.C *= -1.0;
				}

				double slope1 = fabs(l1.B) < 0.001 ? 1 : l1.A / l1.B;
				double slope2 = fabs(l2.B) < 0.001 ? 1 : l2.A / l2.B;

				if(min < blockS && min > 2*LineS && fabs(l1.C - l2.C) < 2.1*LineS)
				{
					getLogExt().appendText("Candidate edges for bridge connections");
					getLogExt().append("Edge 1 slope", slope1);
					getLogExt().append("Edge 2 slope", slope2);
					getLogExt().append("Edge 1 C", l1.C);
					getLogExt().append("Edge 2 C", l2.C);
					edges_to_connect.push_back(std::pair<Edge, Edge>(edge_groups_k[i][l], edge_groups_k[i][k]));
				}
			}
		
		}
	}


	//connect edges
	std::deque<std::pair<Edge, Edge>>::iterator eit;
	for(eit = edges_to_connect.begin(); eit != edges_to_connect.end(); eit++)
	{
		Edge e1 = (*eit).first,
			e2 = (*eit).second;
		Vertex v1, v2, v3, v4;
		Vec2d p1 = getVertexPos(getBondBegin(e1));
		Vec2d p2 = getVertexPos(getBondEnd(e1));

		Vec2d sp1 = getVertexPos(getBondBegin(e2));
		Vec2d sp2 = getVertexPos(getBondEnd(e2));

		double d1 = Algebra::distance2segment(p1, sp1, sp2);
		double d2 = Algebra::distance2segment(p2, sp1, sp2);

		if(d1 < d2)
		{
			v1 = getBondBegin(e1);
			v3 = getBondEnd(e1);
			if(Vec2d::distance(p1, sp1) < Vec2d::distance(p1, sp2))
			{
				v2 = getBondBegin(e2);
				v4 = getBondEnd(e2);
			}
			else
			{
				v2 = getBondEnd(e2);
				v4 = getBondBegin(e2);
			}
		}
		else
		{
			v1 = getBondEnd(e1);
			v3 = getBondBegin(e1);
			if(Vec2d::distance(p2, sp1) < Vec2d::distance(p2, sp2))
			{
				v2 = getBondBegin(e2);
				v4 = getBondEnd(e2);
			}
			else
			{
				v2 = getBondEnd(e2);
				v4 = getBondBegin(e2);
			}
		}

		if(boost::degree(v1, _g) > 1 ||
			boost::degree(v2, _g) > 1 || 
			_mapping[v1] != NULL || _mapping[v2] != NULL)
		{
			continue;
		}

		addBond(v3, v4, SINGLE);
		boost::clear_vertex(v1, _g); 
		boost::remove_vertex(v1, _g);

		boost::clear_vertex(v2, _g); 
		boost::remove_vertex(v2, _g);
	}
}


Molecule::~Molecule()
{
   clear();
}
