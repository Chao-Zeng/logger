#ifndef _LOGGER_LOGGER_H_
#define _LOGGER_LOGGER_H_

#include <sys/syscall.h>
#include <unistd.h>

#include <cstdint>
#include <cstdarg>
#include <cstdio>
#include <sstream>
#include <thread>

#include "core/log_manager.h"

namespace logger{

inline void init_logger(const std::string& path, const std::string& filename, uint64_t filesize/*M*/);

inline void set_log_level(SeverityLevel level);

inline void write_log(SeverityLevel level, const char* format, ...);


void init_logger(const std::string& path, const std::string& filename, uint64_t filesize)
{
    LogManager<>::instance().init(path, filename, filesize * 1024 * 1024);
    LogManager<>::instance().set_log_level(INFO);
}

void set_log_level(SeverityLevel level)
{
    LogManager<>::instance().set_log_level(level);
}

void write_log(SeverityLevel level, const char* format, ...)
{
    char log_message[4096] = {0};
    va_list arg_list;
    va_start(arg_list, format);
    vsnprintf(log_message, sizeof(log_message), format, arg_list);
    Record record;
    gettimeofday(&record.time, NULL);
    record.level = level;
    record.pid = getpid();
    record.tid = syscall(SYS_gettid);
    record.message = log_message;

    LogManager<>::instance().write_log(record);
}

} //namespace logger

using logger::TRACE;
using logger::DEBUG;
using logger::INFO;
using logger::WARNING;
using logger::ERROR;
using logger::FATAL;

#endif // _LOGGER_LOGGER_H_
