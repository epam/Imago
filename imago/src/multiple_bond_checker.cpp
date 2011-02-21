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

#include "multiple_bond_checker.h"
#include "algebra.h"
#include "current_session.h"

using namespace imago;

MultipleBondChecker::MultipleBondChecker( Skeleton &s ) : _s(s), _g(_s.getGraph())
{
   _avgBondLength = _s.bondLength();

   if (_avgBondLength > 125)
      _multiBondErr = 0.35; //0.18; //handwriting
   else if (_avgBondLength > 85)
      _multiBondErr = 0.4;
   else
      _multiBondErr = 0.7; //TODO: handwriting, original: 0.4
   _parLinesEps = getSettings()["ParLinesEps"];
}

MultipleBondChecker::~MultipleBondChecker()
{
}

bool MultipleBondChecker::checkDouble( Edge frst, Edge scnd )
{
   first = frst, second = scnd;
   bf = _s.getBondInfo(first); bs = _s.getBondInfo(second);

   fb = boost::source(first, _g); fe = boost::target(first, _g);
   sb = boost::source(second, _g); se = boost::target(second, _g);

   fb_pos = boost::get(boost::vertex_pos, _g, fb);
   fe_pos = boost::get(boost::vertex_pos, _g, fe);
   sb_pos = boost::get(boost::vertex_pos, _g, sb);
   se_pos = boost::get(boost::vertex_pos, _g, se);

   double d;
   double dd;
   if (!Algebra::segmentsParallel(fb_pos, fe_pos, sb_pos, se_pos, _parLinesEps, &dd))
      return false;

   Vec2d p1, p2;
   Vec2d m1, m2;
   double dm, db, de;
   if (bf.length > bs.length)
   {
      boost::tie(p1, p2) = Algebra::segmentProjection(sb_pos, se_pos, fb_pos, fe_pos);
      m1.middle(p1, p2);
      m2.middle(sb_pos, se_pos);

      p1.middle(sb_pos, se_pos);
      dm = Algebra::distance2segment(p1, fb_pos, fe_pos);
      de = Vec2d::distance(p1, fe_pos);
      db = Vec2d::distance(p1, fb_pos);
   }
   else
   {
      boost::tie(p1, p2) = Algebra::segmentProjection(fb_pos, fe_pos, sb_pos, se_pos);
      m1.middle(p1, p2);
      m2.middle(fb_pos, fe_pos);

      p1.middle(fb_pos, fe_pos);
      dm = Algebra::distance2segment(p1, sb_pos, se_pos);
      de = Vec2d::distance(p1, se_pos);
      db = Vec2d::distance(p1, sb_pos);
   }

   double dbb = Vec2d::distance(fb_pos, sb_pos) + Vec2d::distance(fe_pos, se_pos),
      dbe = Vec2d::distance(fb_pos, se_pos) + Vec2d::distance(fe_pos, sb_pos);

   if (dbe < dbb)
   {
      std::swap(sb, se);
      std::swap(sb_pos, se_pos);
   }

   if (fe == sb || fb == se)
      return false;

   // DP: DID NOT UNDERSTAND AND COMMENTED OUT
   /*if (fe != se && fb != sb)
   {
      if (boost::edge(fb, se, _g).second ||
          boost::edge(fe, sb, _g).second)
         return false;

      dd = Vec2d::distance(m1, m2); 
      if (dd < 0.09 * _avgBondLength)
         return false;
         }*/

   if (db < de)
      std::swap(db, de);

   if (!(dm < 0.98 * de && dm < 0.98 * db))
      return false;
   
   if (bf.length < bs.length)
      d = 0.5 * (Algebra::distance2segment(fb_pos, sb_pos, se_pos) +
                 Algebra::distance2segment(fe_pos, sb_pos, se_pos));
   else
      d = 0.5 * (Algebra::distance2segment(sb_pos, fb_pos, fe_pos) +
                 Algebra::distance2segment(se_pos, fb_pos, fe_pos));

   if (d > bf.length * 0.9)
      return false;
   if (d > bs.length * 0.9)
      return false;

  //if (d > _multiBondErr * _avgBondLength)
    //return false;

   return true;
}

bool MultipleBondChecker::checkTriple( Edge thrd )
{
   third = thrd;
   bt = _s.getBondInfo(third);

   tb = boost::source(third, _g); te = boost::target(third, _g);
   tb_pos = boost::get(boost::vertex_pos, _g, tb);
   te_pos = boost::get(boost::vertex_pos, _g, te);
   
   double dtf, dts;
   if (!Algebra::segmentsParallel(tb_pos, te_pos, fb_pos, fe_pos, _parLinesEps, &dtf) &&
       !Algebra::segmentsParallel(tb_pos, te_pos, sb_pos, se_pos, _parLinesEps, &dts))
      return false;

   Vec2d fm, sm;
   Vec2d p1, p2;
   if (bf.length > bs.length)
   {
      boost::tie(p1, p2) = Algebra::segmentProjection(sb_pos, se_pos, fb_pos, fe_pos);
      fm.middle(p1, p2);
      sm.middle(sb_pos, se_pos);
   }
   else
   {
      boost::tie(p1, p2) = Algebra::segmentProjection(fb_pos, fe_pos, sb_pos, se_pos);
      sm.middle(p1, p2);
      fm.middle(fb_pos, fe_pos);
   }
   double ddf = Algebra::distance2segment(fm, tb_pos, te_pos),
      dds = Algebra::distance2segment(sm, tb_pos, te_pos);

   Edge mid_bond, far_bond;
   Vertex midb, mide, farb, fare;
   int degs = boost::degree(tb, _g) +
      boost::degree(te, _g);

   double d;
   if (ddf < dds)
   {
      mid_bond = first, far_bond = second, d = ddf;
      midb = fb, mide = fe, farb = sb, fare = se;
      degs += boost::degree(sb, _g) + boost::degree(se, _g);
   }
   else
   {
      mid_bond = second, far_bond = first, d = dds;
      midb = sb, mide = se, farb = fb, fare = fe;
      degs += boost::degree(fb, _g) + boost::degree(fe, _g);
   }

   if (degs != 4)
   {
      Vertex vv, v;
      if (boost::degree(tb, _g) == 1)
         vv = te;
      else if (boost::degree(te, _g) == 1)
         vv = tb;
      else
         return false;
                     
      if (vv == midb)
         v = midb, degs += 1 - boost::degree(v, _g);
      else if (vv == mide)
         v = mide, degs += 1 - boost::degree(v, _g);
      
      if (boost::degree(farb, _g) == 1)
         vv = fare;
      else if (boost::degree(fare, _g) == 1)
         vv = farb;
      else
         return false;

      if (vv == midb)
         v = midb, degs += 1 - boost::degree(v, _g);
      else if (vv == mide)
         v = mide, degs += 1 - boost::degree(v, _g);

      if (degs != 4)
         return false;
   }

   if (d > _multiBondErr * _avgBondLength)
      return false;

   return true;
}
