#ifndef _LOGGER_LOGGER_H_
#define _LOGGER_LOGGER_H_

#include <cstdio>
#include <cstdarg>

#include <iostream>
#include <sstream>

namespace logger
{

//user need to implement this function to configure logger what they want
void init_logger();

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
    "trace",
    "debug",
    "info",
    "warning",
    "error",
    "fatal"
};

#define LOG(log_level, format, ...) \
    do \
    { \
    } while (0)

//used before logger initialization, write log to console
#define LOG_CONSOLE(log_level, format, ...) \
    do \
    { \
        stringstream ss; \
        ss << "[" << severity_level_name[log_level] << "]"; \
        ss << " : "; \
        fprintf(ss, format, ##__VA_ARGS__); \
        std::cout << ss << "\n"; \
    } while(0)

} // namespace logger

#endif // _LOGGER_LOGGER_H_
