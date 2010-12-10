#pragma once
#include <sstream>
#include <stdio.h>
#include <iostream>
#include "Timer.h"

#define LOGFILE  "./output-log.txt"
#define LOG  gga::Logger(LOGFILE, true)

namespace gga
{
    class Logger
    {
    private:
        std::stringstream stream;
        std::string output;
        bool show_time;
    public:
        Logger(std::string _output, bool _show_time = true)
        {
          output = _output;
          show_time = _show_time;
        }

        ~Logger()
        {
            FILE* out = fopen(output.c_str(), "a");
            if (out != NULL)
            {
                if (show_time)
                {
                    static Timer t;
                    double time = t.getElapsedTime();
                    time -= ((int)(time+0.5) / 10) * 10;
                    fprintf(out, "[%.3f] %s\n", time, stream.str().c_str());                    
                }
                else
                    fprintf(out, "%s\n", stream.str().c_str());
                fflush(out);
                fclose(out);
            }
        }

        template <typename T>Logger& operator<<(T value)
        {
            stream << value;
            return *this;
        }
    };
}


