#ifndef _LOGGER_RECORD_H_
#define _LOGGER_RECORD_H_

#include <sys/types.h>
#include <unistd.h>

#include <stdint.h>
#include <sys/time.h>

#include <string>

#include <logger/logger.h>

namespace logger
{

class Record
{
public:
	struct timeval time;
	SeverityLevel level;
	pid_t pid;
	pid_t tid;
	std::string message;
	std::string filename;
	uint32_t line;
	std::string function_name;

    Record() : time(0, 0), level(INFO), pid(0), tid(0),
        message(""), filename(""), line(0), function_name("")
    {}
};

} // namespace logger

#endif // _LOGGER_RECORD_H_
