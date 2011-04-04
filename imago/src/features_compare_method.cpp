#include <cstdio>

#include "features_compare_method.h"
#include "exception.h"
#include "output.h"
#include "scanner.h"

namespace imago
{
   FeaturesCompareMethod::~FeaturesCompareMethod()
   {
      std::vector<SymbolClass>::iterator it_c;
      std::deque<IFeatures*>::iterator it_f;
      for (it_c = _classes.begin(); it_c != _classes.end(); ++it_c)
         for (it_f = it_c->second.begin(); it_f != it_c->second.end(); ++it_f)
            delete *it_f;
   }

   void FeaturesCompareMethod::train( const TrainSet &ts )
   {
      TrainSet::const_iterator it;
      for (it = ts.begin(); it != ts.end(); ++it)
      {
         SymbolClass *cls = 0;
         if (_mapping[it->second] == -1)
         {
            _classes.push_back(std::vector<SymbolClass>::value_type());
            _mapping[it->second] = _classes.size() - 1;
            cls = &_classes.back();
            cls->first = it->second;
         }
         else
            cls = &_classes[_mapping[it->second]];

         cls->second.push_back(_extract(*it->first));
      }
      _trained = true;
   }

   void FeaturesCompareMethod::save( Output &o ) const
   {
      _writeHeader(o);
      o.writeCR();
      std::vector<SymbolClass>::const_iterator cit;
      std::deque<IFeatures*>::const_iterator fit;
      o.printf("%d\n", _classes.size());
      for (cit = _classes.begin(); cit != _classes.end(); ++cit)
         o.printf("%c %d ", cit->first, cit->second.size());
      o.writeCR();
      for (cit = _classes.begin(); cit != _classes.end(); ++cit)
         for (fit = cit->second.begin(); fit != cit->second.end(); ++fit)
            (*fit)->write(o);
   }

   void FeaturesCompareMethod::load( Scanner &s )
   {
      _readHeader(s);
      s.readChar(); //"\n"

      int n = s.readInt();
      s.readChar();
      //fscanf(fi, "%d\n", &n);
      _classes.resize(n);
      for (int i = 0; i < n; i++)
      {
         char c; int d;
         c = s.readChar();
         d = s.readInt();
         s.readChar();
         //fscanf(fi, "%c %d ", &c, &d);
         _classes[i].first = c;
         _classes[i].second.resize(d);
         _mapping[c] = i;
      }

      for (int i = 0; i < n; i++)
         for (int j = 0; j < (int)_classes[i].second.size(); j++)
            _classes[i].second[j] = _readFeatures(s);

      //fclose(fi);
      _trained = true;
   }

   void FeaturesCompareMethod::_getSuspectsFrom( const Image &img,
                                                 const std::deque<char> &valid,
                                                 int count,
                                                 std::deque<Suspect> &s ) const
   {
      if (!_trained)
         throw LogicException("Classifier is not trained!");

      s.clear();

      IFeatures *features = _extract(img);

      std::deque<char>::const_iterator vit;
      std::deque<IFeatures*>::const_iterator fit;
      std::deque<Suspect>::iterator sit;

      for (vit = valid.begin(); vit != valid.end(); ++vit)
      {
         const SymbolClass &cls = _classes[_mapping[*vit]];
         for (fit = cls.second.begin(); fit != cls.second.end(); ++fit)
         {
            double d = features->compare(*fit);
            if (s.size() == 0)
               s.push_back(std::make_pair(cls.first, d));
            else if (d < s.back().second)
            {
               for (sit = s.begin(); sit != s.end(); ++sit)
                  if (d < sit->second)
                     s.insert(sit, std::make_pair(cls.first, d));

               if (s.size() > count)
                  s.pop_back();
            }
         }
      }
   }

   void FeaturesCompareMethod::_getSuspects( const Image &img, int count,
                                             std::deque<Suspect> &s ) const
   {
      std::deque<char> all;
      std::vector<SymbolClass>::const_iterator cit;
      for (cit = _classes.begin(); cit != _classes.end(); ++cit)
         all.push_back(cit->first);
      _getSuspectsFrom(img, all, count, s);
   }
}
