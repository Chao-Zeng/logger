#ifndef _LOGGER_LOGGER_H_
#define _LOGGER_LOGGER_H_

#include <logger/src/core/log_manager.h>

using namespace logger;

//user need to implement this function to configure logger what they want
void init_logger();

void set_log_level(SeverityLevel level);

void write_log(SeverityLevel level, const char* format, ...);
#endif // _LOGGER_LOGGER_H_
