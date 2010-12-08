#pragma once
#ifdef WIN32
    #include <windows.h>
#else
    #include <sys/time.h>
#endif

namespace gga
{
    inline unsigned long long getTimeMicroseconds ()
    {
    #ifdef WIN32
        unsigned long long now;
        QueryPerformanceCounter((LARGE_INTEGER*)&now);
        return (unsigned long long)now;
    #else
        struct timeval t;
        struct timezone tz;
        gettimeofday(&t, &tz);
        return t.tv_usec + t.tv_sec * 1000000ULL;
    #endif
    }

    inline double getTimerFrequency ()
    {
    #ifdef WIN32
        unsigned long long f;
        QueryPerformanceFrequency((LARGE_INTEGER*)&f);
        return (double)f;
    #else
        return 1000000.0;
    #endif
    }

    class Timer
    {
        unsigned long long StartTime;
    public:
        inline Timer ()         { reset(); }
        inline void   reset ()  { StartTime = getTimeMicroseconds(); }
        static inline double getNowTime() // in seconds
        {
            return getTimeMicroseconds() / getTimerFrequency();
        }
        inline double getElapsedTime ()const // in seconds
        {
           return (getTimeMicroseconds() - StartTime) / getTimerFrequency();
        }
    };

}


