#ifndef _LOGGER_RECORD_H_
#define _LOGGER_RECORD_H_

//#include <unistd.h>
#include <sys/time.h>

#include <cstdint>
#include <string>

namespace logger
{

enum SeverityLevel
{
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

const char* const severity_level_name[] =
{
    "TRACE",
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL"
};

class Record
{
public:
	struct timeval time;
	SeverityLevel level;
	int pid;
	int tid_pthread;
    int tid_lwp;
	std::string message;
	std::string filename;
	uint32_t line;
	std::string function_name;

    Record() : time(timeval()), level(INFO), pid(0), tid_pthread(0),
        tid_lwp(0), message(""), filename(""), line(0), function_name("")
    {}
};

} // namespace logger

#endif // _LOGGER_RECORD_H_
