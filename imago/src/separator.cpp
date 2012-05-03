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
#include <stack>
#include <queue>

#include "boost/foreach.hpp"
#include <opencv/cv.h>

#include "approximator.h"
#include "comdef.h"
#include "current_session.h"
#include "log_ext.h"
#include "graphics_detector.h"
#include "exception.h"
#include "image.h"
#include "image_utils.h"
#include "image_draw_utils.h"
#include "separator.h"
#include "segment.h"
#include "segmentator.h"
#include "stat_utils.h"
#include "thin_filter2.h"
#include "recognition_settings.h"
#include "graph_extractor.h"
#include "stat_utils.h"
#include "algebra.h"
#include "constants.h"

using namespace imago;

Separator::Separator( SegmentDeque &segs, const Image &img ) : _segs(segs), _img(img)
{
   std::sort(_segs.begin(), _segs.end(), _segmentsComparator);

   RecognitionSettings &rs = gSession.get()->settings();

   rs.set("SegmentVerEps", consts::Separator::SegmentVerEps);
   rs.set("SymHeightErr", consts::Separator::SymHeightErr);
   rs.set("DoubleBondDist", consts::Separator::DoubleBondDist);   
}

void _getHuMomentsC(const Image &img, double hu[7])
{
   int w = img.getWidth(), h = img.getHeight();
   cv::Mat mat(h, w, CV_8U);
   for (int k = 0; k < h; k++)
   {
      for (int l = 0; l < w; l++)
      {
         mat.at<imago::byte> (k, l) = 255 - img.getByte(l, k);
      }
   }
   cv::Moments moments = cv::moments(mat, true);
   cv::HuMoments(moments, hu);
}

int Separator::HuClassifier(double hu[7])
{
	if (hu[1] > consts::Separator::hu_1_1 || (hu[1] < consts::Separator::hu_1_2 && hu[0] < consts::Separator::hu_0_1))
		return SEP_BOND;
	if (hu[1] < consts::Separator::hu_1_3 && hu[0] > consts::Separator::hu_0_2)
		return SEP_SYMBOL;

	return SEP_SUSPICIOUS;
}

bool Separator::_bIsTextContext(SegmentDeque &layer_symbols, imago::Rectangle rec)
{
	Segment* firstNear = NULL,
		*secNear = NULL;
	double dist1 = imago::MAX_LINE,
		dist2 = imago::MAX_LINE;
	RecognitionSettings &rs = getSettings();
	int sym_height_err = rs["SymHeightErr"], cap_height = rs["CapitalHeight"];;
    double susp_seg_density = rs["SuspSegDensity"],
            adequate_ratio_max = rs["MaxSymRatio"],
            adequate_ratio_min = rs["MinSymRatio"],
			line_thickness = rs["LineThickness"];

	//find first pair of symbols closer to rec
	BOOST_FOREACH(Segment *s, layer_symbols)
	{
		imago::Rectangle srec = s->getRectangle();
		Vec2i sc = s->getCenter();
		Vec2i cntr(rec.x + rec.width/2, rec.y+rec.height/2);

		double dist = Vec2i::distance(sc, cntr);

		if(dist < dist1)
		{
			dist1= dist;
			firstNear = s;
		}

		if(dist > dist1 && dist< dist2)
		{
			dist2 = dist;
			secNear = s;
		}
	}

	if(firstNear == NULL && secNear == NULL)
		return false;

	bool xfirstSeparable = Algebra::rangesSeparable(rec.x, rec.x+rec.width, firstNear->getX(), firstNear->getX() + firstNear->getWidth());
	bool yfirstSeparable = Algebra::rangesSeparable(rec.y, rec.y+rec.height, firstNear->getY(), firstNear->getX() + firstNear->getHeight());

	if((xfirstSeparable || yfirstSeparable) && 
		rec.height < cap_height + consts::Separator::ltFactor1 * line_thickness && 
		rec.height > cap_height * consts::Separator::capHeightMin &&
		dist1 < consts::Separator::capHeightMax * cap_height)
		return true;
	return false;
}

void Separator::SeparateStuckedSymbols(SegmentDeque &layer_symbols, SegmentDeque &layer_graphics )
{
	logEnterFunction();

	// TODO: more logging here

	Molecule mol;
	Points2d lsegments;
	 double lnThickness = getSettings()["LineThickness"];
    CvApproximator cvApprox;
	imago::Skeleton graph;
    GraphicsDetector gd(&cvApprox, lnThickness * consts::Separator::gdConst);

	Image timg(_img.getWidth(), _img.getHeight());
	timg.fillWhite();

	SegmentDeque::iterator sit;
	// put the graphic layer on the image
	for(sit = layer_graphics.begin();sit != layer_graphics.end(); sit++)
	{
		ImageUtils::putSegment(timg, *(*sit));
	}
	//approximate graphics with line segments
	gd.detect(timg, lsegments);

	if(lsegments.empty())
		return;
	
	double avg_size = 0;

	std::vector<double> lengths;
	// find the minimum and max of the line segments
	for (size_t i = 0; i < lsegments.size() / 2; i++)
	{
      Vec2d &p1 = lsegments[2 * i];
      Vec2d &p2 = lsegments[2 * i + 1];

      double dist = Vec2d::distance(p1, p2);
	  lengths.push_back(dist);
   }

	double min = timg.getHeight() * timg.getWidth();  //*(std::min(lengths.begin(), lengths.end()));
	double max = 0;
	for(size_t i=0;i<lengths.size();i++)
	{
		if(lengths[i] < min)
			min = lengths[i];
		if(lengths[i] > max)
			max = lengths[i];
	}
	if(fabs(min - max) < 0.01) // eps
		return;

	//avg_size = StatUtils::Median(lengths.begin(), lengths.end());
	
	// Clustering line segments in 2 groups
	double c1 = min, c2 = max, c1_o = min, c2_o = max;
	IntVector classes;
	for (size_t i = 0; i < lsegments.size() / 2; i++)
		classes.push_back(0);
	int count1 = 0, count2=0;

	do
	{
		c1_o = c1;
		c2_o = c2;

		for (size_t i = 0; i < lsegments.size() / 2; i++)
		{
		  Vec2d &p1 = lsegments[2 * i];
		  Vec2d &p2 = lsegments[2 * i + 1];

		  double dist = Vec2d::distance(p1, p2);
		  double dc1 = fabs(dist - c1);
		  double dc2 = fabs(dist - c2);
		  if(dc1 < dc2)
			  classes[i] = 0;
		  else
			  classes[i] = 1;
		}
		count1 = 0;
		count2=0;
		
		double sum1=0, sum2 = 0;
		
		for(size_t i=0;i<classes.size();i++)
			if(classes[i] == 0)
			{
				count1++;
				sum1 += Vec2d::distance(lsegments[2*i], lsegments[2*i+1]);
			}
			else
			{
				count2++;
				sum2 += Vec2d::distance(lsegments[2*i], lsegments[2*i+1]);
			}
		c1 = sum1 / count1;
		c2 = sum2 / count2;
	
	}while(fabs(c1 - c1_o) > 0.1 || fabs(c2 - c2_o) > 0.1); // eps

	if(count1 == 0 || count2 == 0)
		return;

	
	std::vector<Rectangle> symbRects;
	IntVector LineCount;
	std::vector<bool> visited;
	for(size_t i=0;i<classes.size(); i++)
		visited.push_back(false);
	int ri = -1;
	RecognitionSettings &rs = getSettings();
	double line_thick = rs["LineThickness"];

	PriorityQueue pq;
	IntDeque symInds;
	for(size_t i = 0;i<classes.size();i++)
		if(classes[i] == 0)
		{
			symInds.push_back(i);
			Vec2d p1 = lsegments[2 * i];
			Vec2d p2 = lsegments[2 * i + 1];
			SegmentIndx si;
			si._indx = i;
			si._lineSegment.first = p1;
			si._lineSegment.second = p2;
			pq.push(si);
		}
	for(size_t i=0;i<symInds.size(); i++)
		visited.push_back(false);

	typedef std::deque<Vec2d> polygon;

	std::deque<polygon> RectPoints;

	// integrate the results by joining close to each other segments
	//for(int i=0;i<classes.size();i++)
	int i = -1, currInd;
	int ncount;

	do
	{
		i++;
		if(i == symInds.size())
			break;
		currInd = symInds[i];
		
		if(visited[currInd])
			continue;
		
		Vec2d &p1 = lsegments[2 * currInd];
		Vec2d &p2 = lsegments[2 * currInd + 1];

		double d_x = p1.x < p2.x ? p1.x : p2.x;
		double d_y = p1.y < p2.y? p1.y:p2.y;
		double d_w = absolute(p1.x - p2.x) + 1;
		double d_h = absolute(p1.y - p2.y) + 1;
		Rectangle rec(round(d_x), round(d_y), round(d_w), round(d_h));

		symbRects.push_back(rec);
		RectPoints.push_back(polygon());
		LineCount.push_back(1);
		ri++;
		RectPoints[ri].push_back(p1);
		RectPoints[ri].push_back(p2);

		bool added = false;
		visited[currInd] = true;

		//pq.SetRectangle(symbRects[ri]);
		pq.UpdateComparer(RectPoints[ri]);
		int j = 0;
		//for(int j=0; j < classes.size(); j++)
		do{

			added = false;
			if(pq.empty())
				break;
			//for(j=0;j< symInds.size();j++)
			{
				SegmentIndx si = pq.top();

				int currInd2 = si._indx;//symInds[j];
				if(visited[currInd2] || currInd == currInd2)
				{
					pq.pop();
					added = true;
					continue;
				}
			
				Vec2d &sp1 = lsegments[2 * currInd2];
				Vec2d &sp2 = lsegments[2 * currInd2 + 1];

				double dist1 = Algebra::distance2rect(sp1, symbRects[ri]);
				double dist2 = Algebra::distance2rect(sp2, symbRects[ri]);
			
				//update rectangle
				if(dist1 < line_thick || dist2 < line_thick)
				{
					double left = symbRects[ri].x < sp1.x ? symbRects[ri].x : sp1.x; 
					left = left < sp2.x ? left : sp2.x;
				
					double right = (symbRects[ri].x + symbRects[ri].width) > sp1.x ? (symbRects[ri].x  + symbRects[ri].width): sp1.x; 
					right = right > sp2.x ? right : sp2.x;

					double top = symbRects[ri].y < sp1.y ?  symbRects[ri].y : sp1.y; 
					top = top < sp2.y ? symbRects[ri].y : sp2.y;

					double bottom = (symbRects[ri].y + symbRects[ri].height) > sp1.y ? (symbRects[ri].y + symbRects[ri].height):sp1.y;
					bottom = bottom > sp2.y ? bottom : sp2.y;

					int r_l = round(left);
					int r_t = round(top);
					int r_w = round(right) - r_l + 1;
					int r_h = round(bottom) - r_t + 1;

					symbRects[ri] = Rectangle(r_l, r_t, r_w, r_h);

					RectPoints[ri].push_back(sp1);
					RectPoints[ri].push_back(sp2);
					LineCount[ri]++;
					visited[currInd2] = true;
					pq.UpdateComparer(RectPoints[ri]);
					pq.pop();

					added = true;
				}
			}

		}while(added);
		
		ncount = 0;
		for(size_t nc=0;nc<visited.size();nc++)
			ncount += visited[nc];

	}while(ncount !=  symInds.size());

		if(symbRects.empty())
			return;

		bool found_symbol = false;
		
			
		int sym_height_err = rs["SymHeightErr"], cap_height = rs["CapitalHeight"];
		double susp_seg_density = rs["SuspSegDensity"],
			adequate_ratio_max = rs["MaxSymRatio"],
			adequate_ratio_min = rs["MinSymRatio"];

		for(size_t i=0;i< symbRects.size(); i++)
		{
			bool isTextContext = _bIsTextContext(layer_symbols, symbRects[i]);

			if(LineCount[i] < 2 && !isTextContext)// && !(symbRects[i].height < cap_height +line_thick && symbRects[i].height > (cap_height - 1.2 * line_thick)))
				continue;
			if(LineCount[i] == 2 )
			{
				if(Algebra::segmentsParallel(RectPoints[i][0], RectPoints[i][1],
					RectPoints[i][2], RectPoints[i][3], 0.1))
					continue;
				Vec2d p1 = RectPoints[i][0];
				Vec2d p2 = RectPoints[i][1];
				if(Algebra::distance2segment(p1, RectPoints[i][2], RectPoints[i][3]) > line_thick &&
					Algebra::distance2segment(p2, RectPoints[i][2], RectPoints[i][3]) > line_thick)
					continue;
				Line l1 = Algebra::points2line(p1, p2);
				Line l2 = Algebra::points2line(RectPoints[i][2], RectPoints[i][3]);
				Vec2d pintersect = Algebra::linesIntersection(l1, l2);
				if(absolute(pintersect.y - symbRects[i].y) < (symbRects[i].height / 2) )
					continue;

			}

			if(LineCount[i] == 3)
			{
				if(Algebra::segmentsParallel(RectPoints[i][0], RectPoints[i][1],
					RectPoints[i][2], RectPoints[i][3], 0.13) || 
					Algebra::segmentsParallel(RectPoints[i][4], RectPoints[i][5],
					RectPoints[i][2], RectPoints[i][3], 0.13) || 
					Algebra::segmentsParallel(RectPoints[i][0], RectPoints[i][1],
					RectPoints[i][4], RectPoints[i][5], 0.13))
					continue;
			}

			int left = round(  (symbRects[i].x - line_thick < 0) ? 0 : (symbRects[i].x - line_thick));
			int top =  round(  (symbRects[i].y - line_thick < 0) ? 0 : (symbRects[i].y - line_thick));
			int right = round( (symbRects[i].x + symbRects[i].width + line_thick > timg.getWidth()) ? timg.getWidth() :
				               (symbRects[i].x + symbRects[i].width + line_thick) );
			int bottom = round((symbRects[i].y + symbRects[i].height + line_thick > timg.getHeight()) ? timg.getHeight() :
				               (symbRects[i].y + symbRects[i].height  + line_thick) );

			Image extracted(right - left+1, bottom - top+1),
				_2BClassified(right - left+1, bottom - top+1);
			extracted.fillWhite();
			_2BClassified.fillWhite();


			timg.extract(left, top, right, bottom, extracted); 
			
			SegmentDeque segs;
			Segment *s = NULL;
			Segmentator::segmentate(extracted, segs);

			for(SegmentDeque::iterator it = segs.begin(); it!=segs.end(); it++)
			{

				for(size_t n=0;n<RectPoints[i].size();n++)
				{
					Vec2d pt = RectPoints[i][n];
					int dx = round(pt.x - left);
					int dy = round(pt.y - top);
					
					if((*it)->getX() < dx && ((*it)->getWidth() + (*it)->getX()) > dx && 
						(*it)->getY() < dy && ((*it)->getHeight() + (*it)->getY()) > dy)
					{
						int sx = dx - (*it)->getX();
						int sy = dy - (*it)->getY();

						if((*it)->getByte(sx, sy) == 0)
						{
							ImageUtils::putSegment(_2BClassified, *(*it));
							break;
						}
					}
				}
					

				/*int area = (*it)->density() * (*it)->getWidth() * (*it)->getHeight();

				int tarea = s != NULL ? (*it)->density() * (*it)->getWidth() * (*it)->getHeight():
					0;
				if(tarea < area)
				{
					s = new Segment();
					s->copy(**it);
					s->getX() += left;
					s->getY() += top;
				}*/
				delete *it;
			}

			segs.clear();

			//_2BClassified.crop();
			s = new Segment();
			s ->init( _2BClassified.getWidth(),  _2BClassified.getHeight());
			memcpy(s->getData(),  _2BClassified.getData(), sizeof(byte) *  _2BClassified.getWidth() *  _2BClassified.getHeight());
			s->getX() = left;
			s->getY() = top;
			
			int mark;
			
			//	classify object
				
				getLogExt().appendSegment("segment", *s);

				double hu[7];
			
				_getHuMomentsC(*s, hu);

				mark = HuClassifier(hu);
				getLogExt().append("mark", mark);



				double surf_coeff = consts::Separator::SurfCoef;

				 if(extracted.getHeight() < consts::Separator::capHeightRatio *cap_height || (symbRects[i].height * symbRects[i].width > surf_coeff * cap_height * cap_height))
				 {
					mark = SEP_SUSPICIOUS;
					getLogExt().appendText("mark -> SEP_SUSPICIOUS");
				 }

				 mark = (mark == SEP_SUSPICIOUS)  && isTextContext ? SEP_SYMBOL : mark;
				 
				 /*if (mark == SEP_SUSPICIOUS)
				 {
					 if (isPossibleCharacter(*s))
					 {
						 mark = SEP_SYMBOL;
						 getLogExt().appendText("mark -> SEP_SYMBOL");
					 }
				 }*/
		
				/*if (rs["DebugSession"])
				{
					Image test(timg.getWidth(), timg.getHeight());

					test.fillWhite();

					imago::ImageUtils::putSegment(test, *s);
					ImageUtils::saveImageToFile(test, "output/tmp.png");
				}*/				

				if(mark == SEP_SUSPICIOUS || mark == SEP_BOND)
				{
				
				 if (s->getHeight() >= cap_height - sym_height_err && 
					 s->getHeight() <= cap_height + sym_height_err &&
					 s->getHeight() <= cap_height * 2 &&
					 s->getWidth() <= consts::Separator::capHeightRatio2 * cap_height) 
				 {
					 if (s->getRatio() > consts::Separator::getRatio1 && s->getRatio() < consts::Separator::getRatio2)
					{
					   if (_analyzeSpecialSegment(s, layer_graphics, layer_symbols))
					   {
						  mark = SEP_BOND;//layer_graphics.push_back(s);
						  continue;
					   }
					}
					if (s->getRatio() > adequate_ratio_max)
						if (ImageUtils::testSlashLine(*s, 0, consts::Separator::testSlashLine1))
						  mark = SEP_BOND;
					   else
						  mark = (LineCount[i] != 4) ? SEP_SYMBOL : SEP_BOND;
					else
					   if (s->getRatio() < adequate_ratio_min)
						  if (_testDoubleBondV(*s))
							 mark = SEP_BOND;
						  else
							 mark = SEP_SUSPICIOUS;
					   else
						  if (ImageUtils::testSlashLine(*s, 0, consts::Separator::testSlashLine2))
							 mark = SEP_BOND;
						  else 
							 mark = SEP_SUSPICIOUS;
				 }
				 else
					mark = SEP_BOND;
				} 
				 				

				 if(mark == SEP_SYMBOL)
				 {
					 imago::ImageUtils::cutSegment(timg, *s, false, 255);
					 layer_symbols.push_back(s);
					 found_symbol = true;					 
				 }
				 else
					 delete s;
		}

		if(found_symbol)
		{
			layer_graphics.clear();
			
			Segmentator::segmentate(timg, layer_graphics);
		}
	
}

void Separator::firstSeparation( SegmentDeque &layer_symbols, 
   SegmentDeque &layer_graphics )
{
	logEnterFunction();

   int cap_height;
   IntVector suspicious_segments;
   RecognitionSettings &rs = getSettings();
   SegmentDeque layer_suspicious;

#ifdef DEBUG
   puts("************");
#endif

   if (_segs.size() == 0)
   {
	   getLogExt().appendText("Warning, _segs.size is 0!");
      cap_height = -1;
   }
   else
      cap_height = _estimateCapHeight();   

#ifdef DEBUG
   printf("CH: %d\n", cap_height);
   puts("************");
#endif

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

         //if (rs["DebugSession"])
         //   ImageUtils::saveImageToFile(*s, "output/tmp.png");

		 getLogExt().appendSegment("Segment", *s);

		 //thin segment
		 Image temp;
		 s->extract(0, 0, s->getWidth(), s->getHeight(), temp);
		 
		  double hu[7];
		_getHuMomentsC(temp, hu);

		mark = HuClassifier(hu);		

		if(mark == SEP_SYMBOL && 
			(!(s->getHeight() >= cap_height - sym_height_err && s->getHeight() <= cap_height + sym_height_err && s->getHeight() <= cap_height * 2 && s->getWidth() <= cap_height)
			|| s->getHeight() < consts::Separator::capHeightRatio *cap_height)
			)
			mark = SEP_SUSPICIOUS;
		
		getLogExt().append("mark", mark);

		 if(mark == SEP_SUSPICIOUS || mark == SEP_BOND)
		 {
			 ThinFilter2 tfilt(temp);
			  tfilt.apply();

			  Segment *thinseg = new Segment();
			  thinseg->copy(*s);
			  //memcpy(thinseg->getData(), temp.getData(), temp.getWidth()*temp.getHeight() *sizeof(byte));

			 if (s->getHeight() >= cap_height - sym_height_err && 
				 s->getHeight() <= cap_height + sym_height_err &&
				 s->getHeight() <= cap_height * 2 &&
				 s->getWidth() <= consts::Separator::capHeightRatio2 * cap_height) 
			 {
				 if (thinseg->getRatio() > consts::Separator::getRatio1 && thinseg->getRatio() < consts::Separator::getRatio2)
				{
				   if (_analyzeSpecialSegment(thinseg, layer_graphics, layer_symbols))
				   {
					  layer_graphics.push_back(s);
					  continue;
				   }
				}
				if (thinseg->getRatio() > adequate_ratio_max)
					if (ImageUtils::testSlashLine(*thinseg, 0, consts::Separator::testSlashLine1))
					  mark = SEP_BOND;
				   else
					  mark = SEP_SPECIAL;
				else
				   if (thinseg->getRatio() < adequate_ratio_min)
					  if (_testDoubleBondV(*thinseg))
						 mark = SEP_BOND;
					  else
						 mark = SEP_SUSPICIOUS;
				   else
					   if (ImageUtils::testSlashLine(*thinseg, 0, consts::Separator::testSlashLine2))
						 mark = SEP_BOND;
					  else 
						 mark = SEP_SYMBOL;
			 }
			 else
				mark = SEP_BOND;
			 delete thinseg;
		 }


				if (mark != SEP_SYMBOL && 
					s->getHeight() > consts::Separator::extCapHeightMin * cap_height && 
					s->getHeight() < consts::Separator::extCapHeightMax * cap_height &&
					s->getWidth() / s->getHeight() > consts::Separator::extRatioMin && 
					s->getWidth() / s->getHeight() < consts::Separator::extRatioMax )
				{
					int segs = _getApproximationSegmentsCount(s) - 1;
					getLogExt().append("Approx segs", segs);
					if (segs > consts::Separator::minApproxSegsStrong && isPossibleCharacter(*s) ||
						segs > consts::Separator::minApproxSegsWeak && isPossibleCharacter(*s, true))
					{
						getLogExt().appendText("Segment moved to layer_symbols");
						mark = SEP_SYMBOL;
					}			
				}				

         switch (mark)
         {
         case SEP_BOND:
            layer_graphics.push_back(s);
            break;
         case SEP_SYMBOL:
            layer_symbols.push_back(s);
            break;
         case SEP_SPECIAL:
            //if (_analyzeSpecialSegment(s, layer_graphics, layer_symbols))
               layer_graphics.push_back(s);
            //else
            //   layer_symbols.push_back(s);

            /*if ((s)->getDensity() < susp_seg_density)
               layer_graphics.push_back(s);
            else
               layer_symbols.push_back(s);*/
            break;
         case SEP_SUSPICIOUS:
            layer_graphics.push_back(s);//layer_suspicious.push_back(s);
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

   SeparateStuckedSymbols(layer_symbols, layer_graphics);

   std::sort(layer_symbols.begin(), layer_symbols.end(), _segmentsComparator);

}

int Separator::_getApproximationSegmentsCount( Segment *seg /*, SegmentDeque &layer_graphics, SegmentDeque &layer_symbols*/ )
{
   Image tmp;
   CvApproximator cvApprox;
   double lnThickness = getSettings()["LineThickness"];
   GraphicsDetector gd(&cvApprox, lnThickness * consts::Separator::gdConst);
   Points2d lsegments;
   tmp.copy(*seg);
   gd.detect(tmp, lsegments);
   return lsegments.size();
}

bool Separator::_isSuspiciousSymbol( Segment *cur_seg, SegmentDeque &layer_symbols, int cap_height )
{
   BOOST_FOREACH( Segment *s, layer_symbols)
   {
      int sym_y1 = s->getY(), sym_y2 = s->getY() + s->getHeight(),
         seg_y1 = cur_seg->getY(), seg_y2 = cur_seg->getY() + cur_seg->getHeight();

      if (absolute(sym_y2 - seg_y1) <= cap_height / 2 || absolute(sym_y1 - seg_y2) <= cap_height / 2)
      {
         int sym_x = s->getX(), seg_x = cur_seg->getX();

         if (absolute(sym_x - seg_x) < s->getWidth())
            return false;
      }
   }

   return true;
}

int Separator::_estimateCapHeight()
{
	logEnterFunction();

   typedef std::vector<IntPair> PairIntVector; 
   PairIntVector seq_pairs;
   IntVector heights, seq_lengths;
   IntPair p;
   RecognitionSettings &rs = gSession.get()->settings();

   /*IntVector goodHeights;

   BOOST_FOREACH( Segment *s, _segs )
   {
	   double dist = getDistanceCapital(*s);
	   if (_getApproximationSegmentsCount(s) > 4 && dist < 3.5)
	   {
		   goodHeights.push_back(s->getHeight());
	   }
   }

   if (goodHeights.size() > 2)
   {
	   double avg = 0.0;
	   for (size_t u = 0; u < goodHeights.size(); u++)
		   avg += goodHeights[u];
	   int result = avg / goodHeights.size();
	   getLogExt().append("Return (v2)", result);
	   return result;
   }*/

   BOOST_FOREACH( Segment *s, _segs )
   {
      heights.push_back(s->getHeight());
#ifdef DEBUG
      printf("%d ", s->getHeight());
#endif
   }

   getLogExt().appendVector("Heights", heights);   

#ifdef DEBUG
   puts("");
#endif

   int seg_ver_eps = rs["SegmentVerEps"];
   getLogExt().append("Seg_ver_eps", seg_ver_eps);

   for (size_t i = 0; i < heights.size(); )
   {
      size_t j = i + 1;
      for (; j < heights.size(); j++)
      {
         if (absolute(heights[j - 1] - heights[j]) > seg_ver_eps) 
            break;
      }

      p.first = i;
      p.second = j;

#ifdef DEBUG
      printf("%d %d\n", i, j);
#endif

      seq_pairs.push_back(p);

      i += j - i;
   }

   seq_lengths.resize(seq_pairs.size());

   for (size_t i = 0; i < seq_pairs.size(); i++)
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

   for (size_t i = 0; i < symbols_found.size(); i++)
      if (symbols_graphics[symbols_found[i]].first > count)
      {
         symbols_seq = i;
         count = symbols_graphics[symbols_found[i]].first;
      }

   if (count == 0)
      return -1;


   double temp = StatUtils::interMean(heights.begin() + seq_pairs[symbols_found[symbols_seq]].first, 
                                      heights.begin() + seq_pairs[symbols_found[symbols_seq]].second);    
#ifdef DEBUG
   printf("SSQ: %d\nTEMP: %lf", symbols_seq, temp);
#endif
   int cap_height = (int)temp;

   double cur_density = densities[symbols_seq];

   for (size_t i = 0; i < symbols_found.size(); i++)
   {
      if (absolute(count - symbols_graphics[symbols_found[i]].first) < 2)
      {  
         if (densities[i] > cur_density)
         {
            symbols_seq = i;
            cap_height = (int)(StatUtils::interMean(heights.begin() + seq_pairs[symbols_found[symbols_seq]].first, 
                                              heights.begin() + seq_pairs[symbols_found[symbols_seq]].second)); 
            cur_density = densities[i];
         }
      }
   }

   getLogExt().append("Return", cap_height);

   return cap_height;
}

bool Separator::_checkSequence( IntPair &checking, IntPair &symbols_graphics, double &density )
{
   RecognitionSettings &rs = gSession.get()->settings();
   
   //TODO: consider to be dirty hack
   if (checking.second - checking.first == 1)
   {
	   if (_segs[checking.first]->getDensity() < consts::Separator::minDensity)
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
	   if (_segs[i]->getDensity() > consts::Separator::maxDensity && (_segs[i]->getHeight() > _segs[i]->getWidth()))
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
	logEnterFunction();

   int double_bond_dist;
   double adequate_ratio_min;
   bool ret = false;
   SegmentList segs;
   Segment tmp, segment_tmp;
   RecognitionSettings &rs = gSession.get()->settings();

   //if (rs["DebugSession"])
   //   ImageUtils::saveImageToFile(segment, "output/tmp_seg.png");
   getLogExt().appendSegment("segment", segment);

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

   BOOST_FOREACH( Segment *s, segs )
      delete s;

   segs.clear();

   return ret;
}

bool Separator::_segmentsComparator( Segment *a, Segment *b )
{
   return a->getHeight() < b->getHeight();
}
