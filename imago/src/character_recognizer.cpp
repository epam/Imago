/****************************************************************************
 * Copyright (C) 2009-2012 GGA Software Services LLC
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

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
#include <map>
#include <cmath>
#include <cfloat>
#include <deque>

#include "stl_fwd.h"
#include "character_recognizer.h"
#include "segment.h"
#include "exception.h"
#include "scanner.h"
#include "segmentator.h"
#include "thin_filter2.h"
#include "image_utils.h"
#include "log_ext.h"
#include "recognition_tree.h"
#include "character_endpoints.h"
#include "settings.h"
#include "fonts_list.h"



using namespace imago;
//const std::string CharacterRecognizer::unusual = "$%^&#+-=";
const std::string CharacterRecognizer::upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ$%^&#=";
const std::string CharacterRecognizer::lower = "abcdefghijklmnopqrstuvwxyz";
const std::string CharacterRecognizer::digits = "0123456789";
const std::string CharacterRecognizer::charges = "+-";
const std::string CharacterRecognizer::all = CharacterRecognizer::upper + CharacterRecognizer::lower + CharacterRecognizer::digits + CharacterRecognizer::charges;
const std::string CharacterRecognizer::like_bonds = "lL1iIVv";

bool imago::CharacterRecognizer::isPossibleCharacter(const Settings& vars, const Segment& seg, bool loose_cmp, char* result)
{
	RecognitionDistance rd = recognize(vars, seg, CharacterRecognizer::all, false);

	
	
	double best_dist;
	char ch = rd.getBest(&best_dist);

	if (result)
		*result = ch;

	if(ch == '(' || ch == ')' || ch == '[' || ch == ']')
		return true;

	if (std::find(CharacterRecognizer::like_bonds.begin(), CharacterRecognizer::like_bonds.end(), ch) != CharacterRecognizer::like_bonds.end())
	{
		Points2i endpoints = SegmentTools::getEndpoints(seg);
		if ((int)endpoints.size() < vars.characters.MinEndpointsPossible)
		{
			return false;
		}
	}
	if (best_dist < vars.characters.PossibleCharacterDistanceStrong && 
		rd.getQuality() > vars.characters.PossibleCharacterMinimalQuality) 
		return true;

	if (loose_cmp && (best_dist < vars.characters.PossibleCharacterDistanceWeak 
		          && rd.getQuality() > vars.characters.PossibleCharacterMinimalQuality))
		return true;

	return false;
}

CharacterRecognizer::CharacterRecognizer( int classesCount ) : _classesCount(classesCount)
{
   logEnterFunction();

   FontEntries fe = getFontsList();

   for (size_t u = 0; u < fe.size(); u++)
   { 
	   getLogExt().append("Load font", fe[u].name);
	   std::istringstream in(fe[u].data);
	   LoadData(in);
   }
}

CharacterRecognizer::CharacterRecognizer( int classesCount, const std::string &filename) : _classesCount(classesCount)
{
   logEnterFunction();

   getLogExt().append("Load font file", filename);

   std::ifstream in(filename.c_str());
   if (in == 0)
      throw FileNotFoundException(filename.c_str());

   LoadData(in);
   in.close();
}

CharacterRecognizer::~CharacterRecognizer()
{
}

double CharacterRecognizer::_compareDescriptors(const Settings& vars,  const std::vector<double> &d1,
                                                 const std::vector<double> &d2 )
{
   size_t size = std::min(d1.size(), d2.size());
   double d = 0;
   double r;
   double weight = 1;

   for (size_t i = 0; i < size; i++)
   {
      r = d1[i] - d2[i];

      if (i < size / 2)
      {
         if (i % 2)
			 weight = vars.characters.DescriptorsOddFactorStrong;
         else
			 weight = vars.characters.DescriptorsEvenFactorStrong;
      }
      else
      {
         if (i % 2)
			 weight = vars.characters.DescriptorsOddFactorWeak;
         else
			 weight = vars.characters.DescriptorsEvenFactorWeak;
      }
      d += absolute(weight * r);
   }

   return d;
}

double CharacterRecognizer::_compareFeatures(const Settings& vars,  const SymbolFeatures &f1,
                                              const SymbolFeatures &f2 )
{
	if (f1.inner_contours_count != f2.inner_contours_count)
      return DBL_MAX;

   double d = _compareDescriptors(vars, f1.descriptors, f2.descriptors);

   if (f1.inner_contours_count == -1 || f2.inner_contours_count == -1)
      return sqrt(d);

   for (int i = 0; i < f1.inner_contours_count; i++)
      if (f1.inner_descriptors[i].size() != 0 &&
          f2.inner_descriptors[i].size() != 0)
         d += _compareDescriptors(vars, f1.inner_descriptors[i], f2.inner_descriptors[i]);

   return sqrt(d);
}


bool IsBracket(ComplexContour &cc, double LineThickness, bool &isLeft)
{
	int maxInd = -1, maxInd2 = -1;
	double maxLength = 0, 
		maxLength2 = 0;

	// find indices with max norm
	for(int i = 0; i < cc.Size(); i++)
	{
		double length = cc.getContour(i).getRadius();
		if( length > maxLength)		
		{
			maxInd2 = maxInd;
			maxLength2 = maxLength;

			maxInd = i;
			maxLength = length;
		}

		if( length > maxLength2 && length < maxLength)
		{
			maxInd2 = i;
			maxLength2 = length;
		}
	}

	// check if contour with max length is vertical
	if( imago::absolute( cc.getContour(maxInd).getAngle() ) < PI / 3)
		return false;

	// check if contour with second max length is parallel to contour with max length
	if( imago::absolute( cc.getContour(maxInd2).getAngle() ) < PI / 3)
		return false;

	// confirm that between maximal contours are other smaller contours
	if( imago::absolute( maxInd - maxInd2) - 1 < 2 || 
		imago::absolute( cc.Size() + (maxInd > maxInd2 ? maxInd2 : maxInd ) - ((maxInd < maxInd2 ? maxInd2 : maxInd )) - 1) < 2  ) // TODO: check
		return false;

	// check if adjacent contours are on the same side from contour with max length
	if( cc.getContour(maxInd - 1).getReal() * cc.getContour(maxInd + 1).getReal()  > 0.0 ||
		cc.getContour(maxInd2 - 1).getReal() * cc.getContour(maxInd2 + 1).getReal()  > 0.0)
		return false;

	std::vector<ComplexNumber> coordinates;
	coordinates.push_back( ComplexNumber(0, 0) );

	for( int i = 0; i < cc.Size(); i++)
	{
		ComplexNumber curr = cc.getContour(i);
		ComplexNumber cpred = coordinates[coordinates.size() - 1];
		coordinates.push_back( cpred + curr);
	}


	int startInterval1 = (maxInd > maxInd2 ? maxInd2 : maxInd ) + 2,
		endInterval1 = (maxInd < maxInd2 ? maxInd2 : maxInd ),
		startInterval2 = (maxInd < maxInd2 ? maxInd2 : maxInd ) + 2,
		endInterval2 = cc.Size() + (maxInd > maxInd2 ? maxInd2 : maxInd ) ;

	double max1 = -DIST_INF, min1 = imago::DIST_INF, max2 = -DIST_INF, min2 = DIST_INF;

	double accum = coordinates[maxInd].getReal(),
		accum1 = coordinates[maxInd2].getReal();

	if( absolute(accum - accum1) > LineThickness * 1.5 )
		return false;

	if( maxLength2 > (maxLength - LineThickness) ||
		maxLength2 < (maxLength - 3 * LineThickness) )
		return false;

	for(int i = startInterval1; i < endInterval1; i++)
	{
		double curr = coordinates[i].getReal();
		//accum += curr;
		
		if(max1 < curr )
			max1  = curr;
		if(min1 > curr)
			min1 = curr;
	}

	for(int i = startInterval2; i < endInterval2; i++)
	{
		int ind = i % coordinates.size();
		double curr = coordinates[ind].getReal();
		//accum1 += curr;
		if(max2 < curr )
			max2  = curr;
		if(min2 > curr)
			min2 = curr;
	}

	
	if( ((accum < accum1) && (absolute(max1 - max2) > accum1 - accum  )) ||
		((accum > accum1) && (absolute(min1 - min2) > accum - accum1  ))
		)
		return false;

	if(accum < accum1)
		isLeft = true;
	else
		isLeft = false;
	return true;
}

bool CharacterRecognizer::IsParenthesis(const Settings& vars, ComplexContour &cc, bool &isLeft) const
{
	std::vector<int> acuteAngleInds;
	// find two acute angles; if more then return false
	for(int i = 0; i < cc.Size() ; i++)
	{
		Vec2d e1(cc.getContour(i).getReal(), cc.getContour(i).getImaginary());
		Vec2d e2(cc.getContour(i + 1).getReal(), cc.getContour(i + 1).getImaginary());
		
		double angle = Vec2d::angle(e1, e2);
		angle = PI - angle;

		if( angle < ( PI / 2 ) )
			acuteAngleInds.push_back(i); // push back the preceding edge
	}

	if( acuteAngleInds.size() != 2 )
		return false;

	// check that angles are on the top and bottom
	std::vector<ComplexNumber> coordinates;
	coordinates.push_back( ComplexNumber(0, 0) );

	for( int i = 0; i < cc.Size(); i++)
	{
		ComplexNumber curr = cc.getContour(i);
		ComplexNumber cpred = coordinates[coordinates.size() - 1];
		coordinates.push_back( ComplexNumber( cpred.getReal() + curr.getReal(),
			cpred.getImaginary() + curr.getImaginary()));
	}

	double min = coordinates[acuteAngleInds[0] + 1].getImaginary() < coordinates[acuteAngleInds[1] + 1].getImaginary() ? 
		coordinates[acuteAngleInds[0] + 1].getImaginary() : coordinates[acuteAngleInds[1] + 1].getImaginary();
	double max  = coordinates[acuteAngleInds[0] + 1].getImaginary() > coordinates[acuteAngleInds[1] + 1].getImaginary() ? 
		coordinates[acuteAngleInds[0] + 1].getImaginary() : coordinates[acuteAngleInds[1] + 1].getImaginary();
	
	for (size_t i = 0; i < coordinates.size(); i++)
	{
		double y = coordinates[i].getImaginary();

		if( i != ( acuteAngleInds[0] + 1 ) && 
			i != ( acuteAngleInds[1] + 1 ) &&
			( y < min || y > max) )
			return false;
	}

	//check that contours are convex with the center of radius on the same side
	int startInt1 = (acuteAngleInds[0] + 1) < (acuteAngleInds[1] + 1 ) ? (acuteAngleInds[0] + 1) : (acuteAngleInds[1] + 1),
		endInt1 = (acuteAngleInds[0] + 1) > (acuteAngleInds[1] + 1 ) ? (acuteAngleInds[0] + 1) : (acuteAngleInds[1] + 1);
	int startInt2 = endInt1 + 1,
		endInt2 = coordinates.size() + startInt1;

	int result = 0;
	for( int i = (startInt1 + 1); i < endInt1; i++)
	{
		Vec2d p1(coordinates[i - 1].getReal(), coordinates[i - 1].getImaginary());
		Vec2d p2(coordinates[i].getReal(), coordinates[i].getImaginary());
		Vec2d p3(coordinates[i + 1].getReal(), coordinates[i + 1].getImaginary());
		Vec2d p11, p22;
		p11.middle(p1, p2);
		p22.middle(p2, p3);
		Line l1 = Algebra::points2line(p11, Vec2d(p11.x + (p2.y - p1.y), p11.y - (p2.x - p1.x)));
		Line l2 = Algebra::points2line(p22, Vec2d(p22.x + (p3.y - p2.y), p22.y - (p3.x - p2.x)));
		int curres = 0;

		try
		{
			Vec2d inter = Algebra::linesIntersection(vars, l1, l2);
		
			curres = inter.x < p2.x ? -1 : 1;
		}catch(DivizionByZeroException e)
		{
		}

		if(result != 0 )
		{
			
			if(curres * result < 0 )
				return false;
		}
		else
			result = curres;
		
	}

	int result1 = 0;
	for( int i = (startInt2 + 1) ; i < endInt2; i++)
	{
		int ind1 = (i-1) % coordinates.size();
		int ind2 = i % coordinates.size();
		int ind3 = (i+1) % coordinates.size();
		Vec2d p1(coordinates[ind1].getReal(), coordinates[ind1].getImaginary());
		Vec2d p2(coordinates[ind2].getReal(), coordinates[ind2].getImaginary());
		Vec2d p3(coordinates[ind3].getReal(), coordinates[ind3].getImaginary());
		double const1 = (p2.y - p1.y) * (p1.x + p2.x) / (p1.x - p2.x) / 2 + (p1.y - p3.y)/2 + (p2.y - p3.y) / (p2.x - p3.x) * (p2.x + p3.x) / 2;
		double const2 = (p3.y - p2.y) / (p2.x - p3.x) - (p2.y - p1.y) / (p1.x - p2.x);
		double x = const1 / const2;
		int curres = x < p2.x ? -1 : 1;
		if(result1 != 0 )
		{
			
			if(curres * result1 < 0 )
				return false;
		}
		else
			result1 = curres;
	}
	
	if(result != result1 || (result == 0 && result1 == 0))
		return false;
	isLeft = result == 1;
	return true;
}

RecognitionDistance CharacterRecognizer::recognize(const Settings& vars, const Segment &seg, const std::string &candidates, bool can_adjust) const
{
   logEnterFunction();

   qword segHash = 0, shift = 0;
   
   // hash against the source candidates
   for (size_t i = 0; i < candidates.size(); i++)
	   segHash ^= (candidates[i] << (i % (64-8)));
   
   // hash against the source pixels
   for (int y = 0; y < seg.getHeight(); y++)
   {
	   for (int x = 0; x < seg.getWidth(); x++)
		   if (seg.getByte(x,y) == 0) // ink
		   {
			   shift = (shift << 1) + x * 3 + y * 7;
			   segHash ^= shift;
		   }
   }
		   
   getLogExt().appendSegment("Source segment", seg);
   getLogExt().append("Candidates", candidates);

   RecognitionDistance rec;
   getLogExt().append("Segment hash", segHash);
   
   if (vars.caches.PCacheClean &&
	   vars.caches.PCacheClean->find(segHash) != vars.caches.PCacheClean->end())
   {
	   rec = (*vars.caches.PCacheClean)[segHash];
	   getLogExt().appendText("Used cache: clean");
   }
   else
   {	
	   if(seg.getRatio() < 0.6)
	   {
		   
		   imago::Image img;
		   img.copy(seg);
		   ComplexContour cc = ComplexContour::RetrieveContour(vars, img, true);
		   
		   
		    bool left = false;
			if(IsBracket(cc, vars.dynamic.LineThickness, left))
			{
			   char crec = left ? '[':']';
			   rec.clear();
			   rec[crec] = 0;
			   return rec;
			}

			
		 
		   if(IsParenthesis(vars, cc, left))
		   {
			   char crec = left ? '(':')';
			   rec.clear();
			   rec[crec] = 0;
			   return rec;
		   }
		   
	   }
	   seg.initFeatures(_count, vars.characters.Contour_Eps1, vars.characters.Contour_Eps2);
	   rec = _recognize(vars, seg.getFeatures(), candidates, true);

	   double radius;
	   Segment thinseg;
	   thinseg.copy(seg);
	   ThinFilter2 tf(thinseg);
	   tf.apply();
	   if (ImageUtils::isThinCircle(vars, thinseg, radius, true))
	   {
		   if (radius < vars.dynamic.CapitalHeight * vars.separator.capHeightMax)
		   {
			   double v = vars.characters.PossibleCharacterDistanceWeak;
			   // the small-O has very low probability, so ignore it
			   if (rec.find('O') == rec.end())
				   rec['O'] = v;
			   else if (rec['O'] > v)
				   rec['O'] = v;
			   getLogExt().appendText("Updated distance for O");
		   }
	   }
	   
	   getLogExt().appendMap("Distance map for source", rec);

	   if (vars.caches.PCacheClean)
	   {
		   (*vars.caches.PCacheClean)[segHash] = rec;
		   getLogExt().appendText("Filled cache: clean");
	   }
   }

	if (can_adjust)
	{
		if (vars.caches.PCacheAdjusted &&
			vars.caches.PCacheAdjusted->find(segHash) != vars.caches.PCacheAdjusted->end())
		{
			rec = (*vars.caches.PCacheAdjusted)[segHash];
			getLogExt().appendText("Used cache: adjusted");
		}
		else
		{
			static EndpointsData endpointsHandler;
			if (endpointsHandler.adjustByEndpointsInfo(vars, seg, rec))
			{
				getLogExt().appendMap("Adjusted (result) distance map", rec);
				if (vars.caches.PCacheAdjusted)
				{
				   (*vars.caches.PCacheAdjusted)[segHash] = rec;
				   getLogExt().appendText("Filled cache: adjusted");
			   }
			}
		}
	}

	if (getLogExt().loggingEnabled())
	{
		getLogExt().append("Result candidates", rec.getBest());
		getLogExt().append("Recognition quality", rec.getQuality());
	}

   return rec;
}


 RecognitionDistance CharacterRecognizer::_recognize(const Settings& vars,  const SymbolFeatures &features,
                                                        const std::string &candidates, bool full_range) const
{
   if (!_loaded)
      throw OCRException("Font is not loaded");
   double d;

   std::vector<boost::tuple<char, int, double> > nearest;

   BOOST_FOREACH( char c, candidates )
   {
      int ind = _mapping[c];
      const SymbolClass &cls = _classes[ind];
      for (size_t i = 0; i < cls.shapes.size(); i++)
      {
         d = _compareFeatures(vars, features, cls.shapes[i]);

		 if (d > 1000.0) // avoid to add some trash
			 continue;

		 if (full_range || (int)nearest.size() < _classesCount)
            nearest.push_back(boost::make_tuple(c, i, d));
         else
         {
            double far = boost::get<2>(nearest[0]), f;
            int far_ind = 0;
            for (int j = 1; j < _classesCount; j++)
            {
               if ((f = boost::get<2>(nearest[j])) > far)
               {
                  far = f;
                  far_ind = j;
               }
            }

            if (d < far)
               nearest[far_ind] = boost::make_tuple(c, i, d);
         }
      }
   }

   typedef boost::tuple<char, int, double> NearestType;
   typedef std::map<char, boost::tuple<int, double> > ResultsMapType;
   ResultsMapType results;
   ResultsMapType::iterator it;
   int max = 1, x;
   BOOST_FOREACH(const NearestType &t, nearest)
   {
      char c = boost::get<0>(t);
      it = results.find(c);
      if (it == results.end())
      {
         results.insert(
            std::make_pair(c, boost::make_tuple(1, boost::get<2>(t))));
      }
      else
      {
         if ((x = ++boost::get<0>(it->second)) > max)
            max = x;

         boost::get<1>(it->second) = std::min(boost::get<1>(it->second),
                                              boost::get<2>(t));
      }
   }

   RecognitionDistance result;

   BOOST_FOREACH(ResultsMapType::value_type &t, results)
   {
	   if (full_range || boost::get<0>(t.second) == max)
		   result[t.first] = boost::get<1>(t.second);
   }

   return result;
}

