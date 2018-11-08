#include <logger/logger.h>

#include <sys/syscall.h>
#include <unistd.h>

#include <stdint.h>
#include <cstdarg>
#include <cstdio>
#include <sstream>

const uint64_t log_file_size_limit = 100 * 1024 * 1024; // 100M

void init_logger()
{
    LogManager<>::instance()->init("./", "log", log_file_size_limit);
    LogManager<>::instance()->set_log_level(INFO);
}

void set_log_level(SeverityLevel level)
{
    LogManager<>::instance()->set_log_level(level);
}

void write_log(SeverityLevel level, const char* format, ...)
{
    char log_message[4096] = {0};
    va_list arg_list;
    va_start(arg_list, format);
    vsprintf(log_message, format, arg_list);
    Record record;
    gettimeofday(&record.time, NULL);
    record.level = level;
    record.pid = getpid();
    record.tid = syscall(SYS_gettid);
    record.message = log_message;

    LogManager<>::instance()->write_log(record);
}

