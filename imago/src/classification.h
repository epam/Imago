#ifndef _classification_h_
#define _classification_h_

#include <deque>
#include <string>

namespace imago
{
   class Output;
   class Scanner;

   template<class Sample, class Response>
   class IClassificationMethod
   {
   public:
      IClassificationMethod(): _trained(false)
      {};
      virtual ~IClassificationMethod()
      {};

      typedef std::deque<std::pair<const Sample*, Response> > TrainSet;
      virtual void train( const TrainSet &ts ) = 0;

      virtual void save( Output &o ) const = 0;
      virtual void load( Scanner &s ) = 0;

      virtual bool getBestFrom( const Sample &sample,
                                const std::deque<Response> &valid,
                                Response &response, double *err = 0 )
      {
         std::deque<Suspect> s;
         _getSuspectsFrom(sample, valid, 1, s);

         if (s.size() == 0)
            return false;

         response = s[0].first;
         if (err) *err = s[0].second;
         return true;
      }

      virtual bool getBest( const Sample &sample, Response &response,
                            double *err = 0 )
      {
         std::deque<Suspect> s;
         _getSuspects(sample, 1, s);

         if (s.size() == 0)
            return false;

         response = s[0].first;
         if (err) *err = s[0].second;
         return true;
      }
   protected:
      typedef std::pair<Response, double> Suspect;
      virtual void _getSuspectsFrom( const Sample &sample,
                                     const std::deque<Response> &valid, int count,
                                     std::deque<Suspect> &s ) const = 0;
      virtual void _getSuspects( const Sample &sample, int count,
                                 std::deque<Suspect> &s ) const = 0;
      bool _trained;
   };

   class Image;
   typedef IClassificationMethod<Image, char> IOCRClassification;
}

#endif /* _classification_h_ */
