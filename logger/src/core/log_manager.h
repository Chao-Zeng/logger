#ifndef _LOGGER_LOG_MANAGER_H_
#define _LOGGER_LOG_MANAGER_H_

//platform header
#include <pthread.h>

//project header
#include <logger/src/core/condition_queue.h>
#include <logger/src/core/record.h>
#include <logger/src/writer/file_writer.h>
#include <logger/src/formatter/formatter.h>
#include <logger/src/filter/filter.h>

namespace logger
{

class LogManager
{
public:
    static LogManager* instance();

    bool init(const std::string& path, const std::string& filename, uint64_t filesize);

    void set_log_level(SeverityLevel log_level)
    {
        m_log_level = log_level;
    }

    void write_log(const Record& record);

private:
    static void* log_thread(void* arg);

private:
    LogManager() : m_tid(0), m_log_level(INFO)
    {
    }

    //delete copy constructor
    LogManager(const LogManager&);
    //delete assign operator
    LogManager operator= (const LogManager&);

private:
    static LogManager* m_instance;
    pthread_t m_tid;
    SeverityLevel m_log_level;

    ConditionQueue<Record> m_log_queue;    
    FileWriter m_writer;
    LevelFilter m_filter;
    DefaultFormmater m_formatter;
};

} // namespace logger

#endif // _LOGGER_LOG_MANAGER_H_
