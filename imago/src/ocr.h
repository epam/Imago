#ifndef _ocr_h_
#define _ocr_h_

#include <deque>
#include <string>

namespace imago
{
   class Output;

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
      virtual void load( /*Input*/const std::string &filename ) = 0;

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
      virtual void _getSuspects( const Sample &sample, int count,
                                 std::deque<Suspect> &s ) const = 0;
      bool _trained;
   };

   class Image;
   typedef IClassificationMethod<Image, char> IOCRClassification;
}

#endif /* _ocr_h_ */
