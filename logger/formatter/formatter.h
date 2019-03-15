#ifndef _LOGGER_FORMMATER_H_
#define _LOGGER_FORMMATER_H_

#include <ctime>
#include <string>
#include <sstream>

#include "core/record.h"

namespace logger{

class DefaultFormmater
{
public:
    //2015-03-04 15:28:30 [DEBUG] 19284:19318 main.cpp:10 main() : log message example
    std::string format(Record record)
    {
        std::stringstream ss;

        ss << get_time_str(record.time) << " ";
        ss << "[" << severity_level_name[record.level] << "]" << " ";
        ss << record.pid << ":" << record.tid << " ";
        
        if (!record.filename.empty() && 0 != record.line)
        {
            ss << record.filename << ":" << record.line << " ";
        }

       if (!record.function_name.empty())
       {
           ss << record.function_name << " ";
       }

        ss << ": " << record.message;

        return ss.str();
    }

private:
    //YYYY-MM-DD HH:MM:SS:US
    std::string get_time_str(timeval time)
    {
        struct tm* timeinfo = localtime(&time.tv_sec);
        char buffer[80] = { 0 };
        
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

        std::string time_str(buffer);
        std::stringstream ss;
        ss << time_str << ":" << time.tv_usec;

        return ss.str();
    }
};

} // namespace logger

#endif // _LOGGER_FORMMATER_H_
