#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
#include <map>
#include <cmath>
#include <cfloat>
#include <deque>

#include "character_recognizer.h"
#include "segment.h"
#include "exception.h"
#include "scanner.h"
#include "segmentator.h"
#include "stl_fwd.h"
#include "thin_filter2.h"
#include "image_utils.h"
#include "log_ext.h"
#include "recognition_tree.h"
#include "character_endpoints.h"
#include "prefilter.h" // line thickness estimation, isCircle
#include "settings.h"

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
	RecognitionDistance rd = recognize_all(vars, seg, CharacterRecognizer::all, false);
	
	double best_dist;
	char ch = rd.getBest(&best_dist);

	if (result)
		*result = ch;

	if (std::find(CharacterRecognizer::like_bonds.begin(), CharacterRecognizer::like_bonds.end(), ch) != CharacterRecognizer::like_bonds.end())
	{
		Points2i endpoints = SegmentTools::getEndpoints(seg);
		if (endpoints.size() < 4) // TODO
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

CharacterRecognizer::CharacterRecognizer( int k ) : _k(k)
{
   _mapping.resize(255, -1);
   std::string fontdata;
   extern const char *_imago_fontdata[];
   for (int i = 0; _imago_fontdata[i] != 0; ++i)
      fontdata += _imago_fontdata[i];

   std::istringstream in(fontdata);
   _loadData(in);
}

CharacterRecognizer::CharacterRecognizer( int k, const std::string &filename) : _k(k)
{
   _mapping.resize(255, -1);
   std::ifstream in(filename.c_str());
   if (in == 0)
      throw FileNotFoundException(filename.c_str());

   _loadData(in);
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

   double d = _compareDescriptors(vars, f1.descriptors, f2.descriptors);

   if (f1.inner_contours_count == -1 || f2.inner_contours_count == -1)
      return sqrt(d);

   if (f1.inner_contours_count != f2.inner_contours_count)
      return DBL_MAX;
   
   for (int i = 0; i < f1.inner_contours_count; i++)
      if (f1.inner_descriptors[i].size() != 0 &&
          f2.inner_descriptors[i].size() != 0)
         d += _compareDescriptors(vars, f1.inner_descriptors[i], f2.inner_descriptors[i]);

   return sqrt(d);
}

RecognitionDistance CharacterRecognizer::recognize_all(const Settings& vars, const Segment &seg, const std::string &candidates, bool can_adjust) const
{
   logEnterFunction();

   __int64 segHash = 0, shift = 0;
   
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
   
   if (vars.characters.PCacheClean &&
	   vars.characters.PCacheClean->find(segHash) != vars.characters.PCacheClean->end())
   {
	   rec = (*vars.characters.PCacheClean)[segHash];
	   getLogExt().appendText("Used cache: clean");
   }
   else
   {
	   seg.initFeatures(vars, _count);
	   rec = recognize(vars, seg.getFeatures(), candidates, true);

	   double radius;
	   Segment thinseg;
	   thinseg.copy(seg);
	   ThinFilter2 tf(thinseg);
	   tf.apply();
	   if (isCircle(vars, thinseg, radius, true))
	   {
		   if (radius < vars.estimation.CapitalHeight * vars.separator.capHeightMax)
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

	   if (vars.characters.PCacheClean)
	   {
		   (*vars.characters.PCacheClean)[segHash] = rec;
		   getLogExt().appendText("Filled cache: clean");
	   }
   }

	if (can_adjust)
	{
		if (vars.characters.PCacheAdjusted &&
			vars.characters.PCacheAdjusted->find(segHash) != vars.characters.PCacheAdjusted->end())
		{
			rec = (*vars.characters.PCacheAdjusted)[segHash];
			getLogExt().appendText("Used cache: adjusted");
		}
		else
		{
			Points2i endpoints = SegmentTools::getEndpoints(seg);

			SegmentTools::logEndpoints(seg, endpoints);

			std::string probably, surely;
			static EndpointsData endpointsHandler;

			if ((int)endpoints.size() <= vars.characters.MaximalEndpointsUse)
			{
				endpointsHandler.getImpossibleToWrite(vars, endpoints.size(), probably, surely);
				rec.adjust(vars.characters.WriteProbablyImpossibleFactor, probably);
				rec.adjust(vars.characters.WriteSurelyImpossibleFactor, surely);
			}
	
			// easy-to-write adjust
			switch(endpoints.size())
			{
			case 0:
				rec.adjust(vars.characters.WriteVeryEasyFactor, "0oO");
				break;
			case 1:
				rec.adjust(vars.characters.WriteEasyFactor, "Ppe");
				break;
			case 2:
				rec.adjust(vars.characters.WriteEasyFactor, "ILNSsZz");
				break;
			case 3:
				rec.adjust(vars.characters.WriteVeryEasyFactor, "3");
				rec.adjust(vars.characters.WriteEasyFactor, "F");
				break;
			case 4:
				rec.adjust(vars.characters.WriteEasyFactor, "fHK");
				break;
			case 6:
				rec.adjust(vars.characters.WriteEasyFactor, "^");
				break;
			};

		   getLogExt().appendMap("Adjusted (result) distance map", rec);

		   if (vars.characters.PCacheAdjusted)
		   {
			   (*vars.characters.PCacheAdjusted)[segHash] = rec;
			   getLogExt().appendText("Filled cache: adjusted");
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

char CharacterRecognizer::recognize(const Settings& vars,  const Segment &seg,
                                     const std::string &candidates,
                                     double *dist ) const
{
   return recognize_all(vars, seg, candidates).getBest(dist);
}


 RecognitionDistance CharacterRecognizer::recognize(const Settings& vars,  const SymbolFeatures &features,
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

         if (full_range || (int)nearest.size() < _k)
            nearest.push_back(boost::make_tuple(c, i, d));
         else
         {
            double far = boost::get<2>(nearest[0]), f;
            int far_ind = 0;
            for (int j = 1; j < _k; j++)
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

void CharacterRecognizer::_loadData( std::istream &in )
{
   int fonts_count, letters_count;
   in >> _count >> letters_count;
   _classes.resize(letters_count);
   for (int i = 0; i < letters_count; i++)
   {
      SymbolClass &cls = _classes[i];
      in >> cls.sym >> fonts_count;
      _mapping[cls.sym] = i;
      cls.shapes.resize(fonts_count);
      for (int j = 0; j < fonts_count; j++)
      {
         SymbolFeatures &sf = cls.shapes[j];
         in >> sf.inner_contours_count;
         sf.descriptors.resize(2 * _count);
         for (int k = 0; k < 2 * _count; k++)
            in >> sf.descriptors[k];

         sf.inner_descriptors.resize(sf.inner_contours_count);
         for (int k = 0; k < sf.inner_contours_count; k++)
         {
            sf.inner_descriptors[k].resize(2 * _count);
            for (int l = 0; l < 2 * _count; l++)
               in >> sf.inner_descriptors[k][l];
         }
      }
   }

   _loaded = true;
}
