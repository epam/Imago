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
#include "log_ext.h"

using namespace imago;

MultipleBondChecker::MultipleBondChecker(const Settings& vars, Skeleton &s ) : _s(s), _g(_s.getGraph())
{
   _avgBondLength = _s.bondLength();

   if (_avgBondLength > vars.mbond.LongBond)
	   _multiBondErr = vars.mbond.LongErr; 
   else if (_avgBondLength > vars.mbond.MediumBond)
	   _multiBondErr = vars.mbond.MediumErr;
   else
	   _multiBondErr = vars.mbond.DefaultErr; 
   
   _parLinesEps = vars.mbond.ParBondsEps;
}

MultipleBondChecker::~MultipleBondChecker()
{
}

bool MultipleBondChecker::checkDouble(const Settings& vars, Edge frst, Edge scnd )
{
   first = frst, second = scnd;
   bf = _s.getBondInfo(first); bs = _s.getBondInfo(second);

   fb = first.m_source; fe = first.m_target;
   sb = second.m_source; se = second.m_target;

   fb_pos = _g.getVertexPosition(fb);
   fe_pos = _g.getVertexPosition(fe);
   sb_pos = _g.getVertexPosition(sb);
   se_pos = _g.getVertexPosition(se);

   double d;
   double dd;
   if (!Algebra::segmentsParallel(fb_pos, fe_pos, sb_pos, se_pos, _parLinesEps, &dd))
      return false;
   
   Vec2d p1, p2;
   Vec2d m1, m2;
   double dm, db, de;
   double ratio;
   if (bf.length > bs.length)
   {
      std::tie(p1, p2) = Algebra::segmentProjection(sb_pos, se_pos, fb_pos, fe_pos);
      m1.middle(p1, p2);
      m2.middle(sb_pos, se_pos);

      p1.middle(sb_pos, se_pos);
      dm = Algebra::distance2segment(p1, fb_pos, fe_pos);
      de = Vec2d::distance(p1, fe_pos);
      db = Vec2d::distance(p1, fb_pos);
      ratio = bf.length / bs.length;
   }
   else
   {
      std::tie(p1, p2) = Algebra::segmentProjection(fb_pos, fe_pos, sb_pos, se_pos);
      m1.middle(p1, p2);
      m2.middle(fb_pos, fe_pos);

      p1.middle(fb_pos, fe_pos);
      dm = Algebra::distance2segment(p1, sb_pos, se_pos);
      de = Vec2d::distance(p1, se_pos);
      db = Vec2d::distance(p1, sb_pos);
      ratio = bs.length / bf.length;
   }

   if (ratio > vars.mbond.DoubleRatioTresh)
      return false;

   double dbb = Vec2d::distance(fb_pos, sb_pos) + Vec2d::distance(fe_pos, se_pos),
      dbe = Vec2d::distance(fb_pos, se_pos) + Vec2d::distance(fe_pos, sb_pos);

   if (dbe < dbb)
   {
      std::swap(sb, se);
      std::swap(sb_pos, se_pos);
   }

   if (fe == sb || fb == se)
      return false;
   
   if (fe != se && fb != sb)
   {
      if (_g.getEdge(fb, se).second ||
          _g.getEdge(fe, sb).second)
         return false;

      dd = Vec2d::distance(m1, m2); 
	  if (dd < vars.mbond.DoubleCoef * _avgBondLength)      
         return false;
   }

   if (db < de)
      std::swap(db, de);

   if (bf.length < bs.length)
      d = 0.5 * (Algebra::distance2segment(fb_pos, sb_pos, se_pos) + // average
                 Algebra::distance2segment(fe_pos, sb_pos, se_pos));
   else
      d = 0.5 * (Algebra::distance2segment(sb_pos, fb_pos, fe_pos) + // average
                 Algebra::distance2segment(se_pos, fb_pos, fe_pos));

   
   if (!(dm < vars.mbond.DoubleMagic1 * de && dm < vars.mbond.DoubleMagic2 * db))
   {
      return false;
   }
   
   for (Graph::vertex_iterator begin = _g.vertexBegin(), end = _g.vertexEnd(); begin != end; ++begin)
   {
      Graph::vertex_descriptor v = *begin;
      if (v == fb || v == fe || v == sb || v == se)
         continue;

      Vec2d v_pos = _g.getVertexPosition(v);
      double d1 = Algebra::distance2segment(v_pos, fb_pos, fe_pos);
      double d2 = Algebra::distance2segment(v_pos, sb_pos, se_pos);

      double coef;
      if (bf.length < bs.length)
         coef = Algebra::pointProjectionCoef(v_pos, fb_pos, fe_pos);
      else
         coef = Algebra::pointProjectionCoef(v_pos, sb_pos, se_pos);

      if (d1 > d || d2 > d)
         continue;
      
	  if (coef > vars.mbond.DoubleTreshMin && coef < vars.mbond.DoubleTreshMax)
      {
         return false;
      }
   }
   
   double maxLength, minLength;
   if (bf.length > bs.length)
   {
      maxLength = bf.length;
      minLength = bs.length;
   }
   else
   {
      maxLength = bs.length;
      minLength = bf.length;
   }

   // TODO: depends on hard-set constants (something more adaptive required here)

   if (maxLength > vars.mbond.MaxLen1)
	   _multiBondErr = vars.mbond.mbe1;
   else if (maxLength > vars.mbond.MaxLen2)
   {
	   if (minLength > vars.mbond.MinLen1)
         _multiBondErr = vars.mbond.mbe2;
      else
         _multiBondErr = vars.mbond.mbe3;
   }
   else if (maxLength > vars.mbond.MaxLen3)
      _multiBondErr = vars.mbond.mbe4;
   else if (maxLength > vars.mbond.MaxLen4)
   {
	   if (minLength > vars.mbond.MinLen2)
         _multiBondErr = vars.mbond.mbe5;
      else
         _multiBondErr = vars.mbond.mbe6;
   }
   else if (maxLength > vars.mbond.MaxLen5)
      _multiBondErr = vars.mbond.mbe7;
   else
	   _multiBondErr = vars.mbond.mbe_def;

#ifdef DEBUG
   printf("DC:%d; %lf\nDC: %lf < %lf\n", maxLength, _multiBondErr, d, _multiBondErr * maxLength);
#endif
   
   if (d > _multiBondErr * maxLength)
      return false;
   
#ifdef DEBUG
   LPRINT(0, "found double bond:"); 
   LPRINT(0, "(%.1lf %.1lf) - (%.1lf %.1lf)", fb_pos.x, fb_pos.y, fe_pos.x, fe_pos.y);
   LPRINT(0, "(%.1lf %.1lf) - (%.1lf %.1lf)", sb_pos.x, sb_pos.y, se_pos.x, se_pos.y);
#endif /* DEBUG */

   return true;
}

bool MultipleBondChecker::checkTriple(const Settings& vars, Edge thrd )
{
   third = thrd;
   bt = _s.getBondInfo(third);

   tb = third.m_source; te = third.m_target;
   tb_pos = _g.getVertexPosition(tb);
   te_pos = _g.getVertexPosition(te);
   
   double dtf, dts;
   if (!Algebra::segmentsParallel(tb_pos, te_pos, fb_pos, fe_pos, _parLinesEps, &dtf) &&
       !Algebra::segmentsParallel(tb_pos, te_pos, sb_pos, se_pos, _parLinesEps, &dts))
      return false;

   Vec2d fm, sm;
   Vec2d p1, p2;
   if (bf.length > bs.length)
   {
      std::tie(p1, p2) = Algebra::segmentProjection(sb_pos, se_pos, fb_pos, fe_pos);
      fm.middle(p1, p2);
      sm.middle(sb_pos, se_pos);
   }
   else
   {
      std::tie(p1, p2) = Algebra::segmentProjection(fb_pos, fe_pos, sb_pos, se_pos);
      sm.middle(p1, p2);
      fm.middle(fb_pos, fe_pos);
   }
   double ddf = Algebra::distance2segment(fm, tb_pos, te_pos),
      dds = Algebra::distance2segment(sm, tb_pos, te_pos);

   Edge mid_bond, far_bond;
   Vertex midb, mide, farb, fare;
   int degs = (int)(_g.getDegree(tb) + _g.getDegree(te));

   double d;
   if (ddf < dds)
   {
      mid_bond = first, far_bond = second, d = ddf;
      midb = fb, mide = fe, farb = sb, fare = se;
      degs += (int)(_g.getDegree(sb) + _g.getDegree(se));
   }
   else
   {
      mid_bond = second, far_bond = first, d = dds;
      midb = sb, mide = se, farb = fb, fare = fe;
      degs += (int)(_g.getDegree(fb) + _g.getDegree(fe));
   }

   if (degs != 4)
   {
      Vertex vv, v;
      if (_g.getDegree(tb) == 1)
         vv = te;
      else if (_g.getDegree(te) == 1)
         vv = tb;
      else
         return false;
                     
      if(vv == midb)
      {
         v = midb;
         degs += 1 - (int)_g.getDegree(v);
      }
      else if(vv == mide)
      {
         v = mide;
         degs += 1 - (int)_g.getDegree(v);
      }
      
      if (_g.getDegree(farb) == 1)
         vv = fare;
      else if (_g.getDegree(fare) == 1)
         vv = farb;
      else
         return false;

      if(vv == midb)
      {
         v = midb;
         degs += 1 - (int)_g.getDegree(v);
      }
      else if(vv == mide)
      {
         v = mide;
         degs += 1 - (int)_g.getDegree(v);
      }

      if (degs != 4)
         return false;
   }

   if (d > _multiBondErr * _avgBondLength)
      return false;

   return true;
}
