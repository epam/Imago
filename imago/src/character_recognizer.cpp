#include "boost/foreach.hpp"
#include "boost/tuple/tuple.hpp"
#include <map>
#include <cmath>
#include <cfloat>
#include <cstdio>

#include "character_recognizer.h"
#include "segment.h"

using namespace imago;

std::string CharacterRecognizer::upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string CharacterRecognizer::lower = "abcdefghijklmnopqrstuvwxyz";
std::string CharacterRecognizer::digits = "0123456789";

CharacterRecognizer::CharacterRecognizer( int k ) : _k(k)
{
   _mapping.resize(255, -1);
   _loadBuiltIn();
}

CharacterRecognizer::CharacterRecognizer( int k,
                                          const std::string &filename) : _k(k)
{
   _mapping.resize(255, -1);
   _loadFromFile(filename);
}

CharacterRecognizer::~CharacterRecognizer()
{
}

double CharacterRecognizer::_compareDescriptors( const std::vector<double> &d1,
                                                 const std::vector<double> &d2 )
{
   int s = (int)std::min(d1.size(), d2.size());
   double d = 0;
   double r;
   double weight = 1;

   for (int i = 0; i < s; i++)
   {
      r = d1[i] - d2[i];

      if (i % 2)
         weight = 0.5;
      else
         weight = 1.5;

      d += weight * r * r;
   }

   return d;
}

double CharacterRecognizer::_compareFeatures( const SymbolFeatures &f1,
                                              const SymbolFeatures &f2 )
{
   if (f1.inner_contours_count != f2.inner_contours_count)
      return DBL_MAX;
   
   double d = _compareDescriptors(f1.descriptors, f2.descriptors);

   for (int i = 0; i < f1.inner_contours_count; i++)
      d += _compareDescriptors(f1.inner_descriptors[i],
                               f2.inner_descriptors[i]);

   return sqrt(d);
}

char CharacterRecognizer::recognize( const Segment &seg,
                                     const std::string &candidates,
                                     double *dist )
{
   seg.initFeatures(_count);
   return recognize(seg.getFeatures(), candidates, dist);
}

char CharacterRecognizer::recognize( const SymbolFeatures &features,
                                     const std::string &candidates,
                                     double *dist )
{
   double d;

   std::vector<boost::tuple<char, int, double> > nearest;
   nearest.reserve(_k);

   BOOST_FOREACH( char c, candidates )
   {
      int ind = _mapping[c];
      SymbolClass &cls = _classes[ind];
      for (int i = 0; i < (int)cls.shapes.size(); i++)
      {
         d = _compareFeatures(features, cls.shapes[i]);

         if ((int)nearest.size() < _k)
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

   char res = 0;
   d = DBL_MAX;
   BOOST_FOREACH(ResultsMapType::value_type &t, results)
   {
      if (boost::get<0>(t.second) == max)
         if (boost::get<1>(t.second) < d)
            d = boost::get<1>(t.second), res = t.first;
   }

   if (dist)
      *dist = d;
   
   return res;
}

void CharacterRecognizer::_loadFromFile( const std::string &filename )
{
   FILE *f = fopen(filename.c_str(), "r");
   int fonts_count, letters_count;
   fscanf(f, "%d %d %d\n", &_count, &fonts_count, &letters_count);
   _classes.resize(letters_count);
   for (int i = 0; i < letters_count; i++)
   {
      SymbolClass &cls = _classes[i];
      fscanf(f, "%c\n", &cls.sym);
      _mapping[cls.sym] = i;
      cls.shapes.resize(fonts_count);
      for (int j = 0; j < fonts_count; j++)
      {
         SymbolFeatures &sf = cls.shapes[j];
         fscanf(f, "%d\n", &sf.inner_contours_count);
         sf.descriptors.resize(2 * _count);
         for (int k = 0; k < 2 * _count; k++)
            fscanf(f, "%lf ", &sf.descriptors[k]);

         sf.inner_descriptors.resize(sf.inner_contours_count);
         for (int k = 0; k < sf.inner_contours_count; k++)
         {
            sf.inner_descriptors[k].resize(2 * _count);
            for (int l = 0; l < 2 * _count; l++)
               fscanf(f, "%lf ", &sf.inner_descriptors[k][l]);
         }
      }
   }

   fclose(f);
}

void CharacterRecognizer::_loadBuiltIn()
{
   #include "TEST.font.inc"
}
