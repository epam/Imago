#include "boost/foreach.hpp"
#include "boost/tuple/tuple.hpp"
#include <map>
#include <cmath>
#include <cfloat>
#include <cstdio>
#include <deque>

#include "character_recognizer.h"
#include "segment.h"
#include "exception.h"
#include "scanner.h"
#include "png_loader.h"
#include "segmentator.h"
#include "stl_fwd.h"
#include "thin_filter2.h"

using namespace imago;
const std::string CharacterRecognizer::upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string CharacterRecognizer::lower = "abcdefghijklmnopqrstuvwxyz";
const std::string CharacterRecognizer::digits = "0123456789";

CharacterRecognizer::CharacterRecognizer( int k ) : _loaded(false), _k(k)
{
   _mapping.resize(255, -1);
   _loadBuiltIn();
}

CharacterRecognizer::CharacterRecognizer( int k, const std::string &filename) :
   _loaded(false), _k(k)
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

      if (i < s / 2)
      {
         if (i % 2)
            weight = 2.5;
         else
            weight = 3.5;
      }
      else
      {
         if (i % 2)
            weight = 0.9;
         else
            weight = 0.3;
      }
      d += weight * r * r;
   }

   return d;
}

double CharacterRecognizer::_compareFeatures( const SymbolFeatures &f1,
                                              const SymbolFeatures &f2 )
{
   double d = _compareDescriptors(f1.descriptors, f2.descriptors);

   if (f1.inner_contours_count == -1 || f2.inner_contours_count == -1)
      return sqrt(d);

   if (f1.inner_contours_count != f2.inner_contours_count)
      return DBL_MAX;
   
   for (int i = 0; i < f1.inner_contours_count; i++)
      if (f1.inner_descriptors[i].size() != 0 &&
          f2.inner_descriptors[i].size() != 0)
         d += _compareDescriptors(f1.inner_descriptors[i],
                                  f2.inner_descriptors[i]);

   return sqrt(d);
}

char CharacterRecognizer::recognize( const Segment &seg,
                                     const std::string &candidates,
                                     double *dist ) const
{
   seg.initFeatures(_count);
   return recognize(seg.getFeatures(), candidates, dist);
}

char CharacterRecognizer::recognize( const SymbolFeatures &features,
                                     const std::string &candidates,
                                     double *dist ) const
{
   if (!_loaded)
      throw OCRException("Font is not loaded");
   double d;

   std::vector<boost::tuple<char, int, double> > nearest;
   nearest.reserve(_k);

   BOOST_FOREACH( char c, candidates )
   {
      int ind = _mapping[c];
      const SymbolClass &cls = _classes[ind];
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
      //printf("%c %lf %d\n", c, boost::get<2>(t), boost::get<1>(t));
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
   _loaded = true;
}

void CharacterRecognizer::_loadBuiltIn()
{
#ifdef IMAGO_FONT_BUILT_IN
   #include "TEST4.font.inc"
   _loaded = true;
#endif
}

HWCharacterRecognizer::HWCharacterRecognizer () : _cr(3)
{
   try
   {
      {
         _readFile("h1.png", features_h1);
         _readFile("h2.png", features_h2);
         _readFile("h3.png", features_h3);
         _readFile("h4.png", features_h4);
         _readFile("n1.png", features_n1);
         _readFile("n2.png", features_n2);
         _readFile("n3.png", features_n3);
         _readFile("n4.png", features_n4);
      }
   }
   catch (Exception &e)
   {
      fprintf(stderr, "%s\n", e.what());
      return;
   }
}

void HWCharacterRecognizer::_readFile(const char *filename, SymbolFeatures &features)
{
   FileScanner scanner(filename);
   PngLoader loader(scanner);
   Image img;
      
   loader.loadImage(img);
   SegmentDeque segments;
      
   Segmentator::segmentate(img, segments, 3, 0);
   Segment &seg = **segments.begin();
   seg.initFeatures(25);
   features = seg.getFeatures();
}

int HWCharacterRecognizer::recognize (Segment &seg)
{
   seg.initFeatures(25);
   SymbolFeatures &features = seg.getFeatures();

   Segment thinseg;
   thinseg.copy(seg);
   ThinFilter2 tf(thinseg);
   tf.apply();

   printf(" (%d ic)", features.inner_contours_count);
   
   if (isCircle(thinseg))
   {
      printf(" circle ");
      return 'O';
   }

   double errh1 = CharacterRecognizer::_compareFeatures(features, features_h1);
   double errh2 = CharacterRecognizer::_compareFeatures(features, features_h2);
   double errh3 = CharacterRecognizer::_compareFeatures(features, features_h3);
   double errh4 = CharacterRecognizer::_compareFeatures(features, features_h4);
   double errn1 = CharacterRecognizer::_compareFeatures(features, features_n1);
   double errn2 = CharacterRecognizer::_compareFeatures(features, features_n2);
   double errn3 = CharacterRecognizer::_compareFeatures(features, features_n3);
   double errn4 = CharacterRecognizer::_compareFeatures(features, features_n4);

   double err_h[] = {errh1, errh2, errh3, errh4};
   double err_n[] = {errn1, errn2, errn3, errn4};

   int min_h = 0, min_n = 0;

   for (int i = 1; i < 4; i++)
   {
      if (err_h[i] < err_h[min_h])
         min_h = i;
      if (err_n[i] < err_n[min_n])
         min_n = i;
   }

   if (err_h[min_h] > 100)
      err_h[min_h] = 100;
   if (err_n[min_n] > 100)
      err_n[min_n] = 100;

   printf(" h %.2lf", err_h[min_h]);
   printf(" n %.2lf", err_n[min_n]);
   
   if (err_n[min_n] < 1.8)
   {
      if (err_h[min_h] < err_n[min_n])
         return 'H';
      return 'N';
   }

   static const std::string candidates =
      "ABCDFGHIKMNPRS"
      "aehiklnru"
      "1236";
   
   double err;
   char c = _cr.recognize(seg, candidates, &err);

   if (c != 0)
      printf(" [%c] %.2lf ", c, err);

   bool line = (c == 'l' || c == 'i' || c == '1');
   bool tricky = (c == 'r');
   bool hard = (c == 'R' || c == 'S');

   if (line && err < 0.5)
      return c;

   if (tricky && err < 1.0)
      return c;

   if (!line && !tricky && err < 1.8)
      return c;

   if (hard && err < 2.5)
      return c;

   return -1;
}
