#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <fstream>

namespace cubesnake
{
    class Logger
    {
    public:
        Logger(std::string _filename)
            : filename(_filename)
        {}

        void AddMessage(std::string msg)
        {
            log_stream.open(filename, std::ios::out | std::ios::app);
            log_stream << msg << std::endl;
            log_stream.close();
        }
    private:
        std::string filename;
        std::ofstream log_stream;
    };
}

#endif /* __LOGGER_H__ */
