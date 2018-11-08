#ifndef _LOGGER_LOGGER_H_
#define _LOGGER_LOGGER_H_

#include <logger/src/core/log_manager.h>

using namespace logger;

void init_logger(const std::string& path, const std::string& filename, uint64_t filesize/*M*/);

void set_log_level(SeverityLevel level);

void write_log(SeverityLevel level, const char* format, ...);
#endif // _LOGGER_LOGGER_H_
