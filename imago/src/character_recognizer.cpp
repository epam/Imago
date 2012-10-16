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

