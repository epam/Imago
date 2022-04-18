#include <map>
#include <mutex>

#include "recognition_context.h"

namespace imago
{
   typedef std::map<qword, RecognitionContext *> ContextMap;
   static ContextMap _contexts;
   static std::mutex _contexts_mutex;

   RecognitionContext *getContextForSession( qword sessionId )
   {
      std::lock_guard<std::mutex> lock(_contexts_mutex);
      ContextMap::iterator it;
      if ((it = _contexts.find(sessionId)) == _contexts.end())
         return NULL;

      return it->second;
   }

   void setContextForSession( qword sessionId, RecognitionContext *context )
   {
      std::lock_guard<std::mutex> lock(_contexts_mutex);
      ContextMap::iterator it;
      if ((it = _contexts.find(sessionId)) == _contexts.end())
         _contexts.insert(std::make_pair(sessionId, context));
      else 
         it->second = context;
   }

   void deleteRecognitionContext(qword sessionId, RecognitionContext *context)
   {
      std::lock_guard<std::mutex> lock(_contexts_mutex);
      delete context;
      _contexts.erase(_contexts.find(sessionId));
   }

   struct _ContextCleanup
   {
      ~_ContextCleanup()
      {
         for(ContextMap::value_type item: _contexts)
         {
            delete item.second;
         }
      }
   };

   static _ContextCleanup _deleter;
}