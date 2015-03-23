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

template
<
typename WritePolicy = FileWriter,
typename FilterPolicy = LevelFilter,
typename FormatPolicy = DefaultFormmater
>
class LogManager
{
public:
    static LogManager* instance();

    bool init(const std::string& path, const std::string& filename, uint64_t filesize);

    void write_log(const Record& record);

private:
    static void* log_thread(void* arg);

private:
    LogManager() : m_instance(NULL), m_tid(0)
    {
    }

    //delete copy constructor
    LogManager(const LogManager&);
    //delete assign operator
    LogManager operator= (const LogManager&);

private:
    static LogManager* m_instance;
    pthread_t m_tid;

    ConditionQueue<Record> m_log_queue;    
    WritePolicy m_writer;
    FilterPolicy m_filter;
    FormatPolicy m_formatter;
};


////////////////////////////////////////////////////////////////////////////////
//implementation

template
<
typename WritePolicy /*= FileWriter*/,
typename FilterPolicy /*= LevelFilter*/,
typename FormatPolicy /*= DefaultFormmater
*/>
LogManager* LogManager<WritePolicy, FilterPolicy, FormatPolicy>::instance()
{
    if (NULL == m_instance)
    {
        m_instance = new LogManager<WritePolicy, FilterPolicy, FormatPolicy>;
    }

    return m_instance;
}

template
<
typename WritePolicy /*= FileWriter*/,
typename FilterPolicy /*= LevelFilter*/,
typename FormatPolicy /*= DefaultFormmater
*/>
bool LogManager<WritePolicy, FilterPolicy, FormatPolicy>::init(const std::string& path, const std::string& filename, uint64_t filesize)
{
    m_writer.set_file_path(path);
    m_writer.set_file_name(filename);
    m_writer.set_file_size(filesize);

    pthread_attr_t  attr;
    if (0 != pthread_attr_init(&attr))
    {
        return false;
    }

    if (0 != pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
    {
        pthread_attr_destroy(&attr);
        return false;
    }

    if (0 != pthread_create(&m_tid, &attr, log_thread, this))
    {
        pthread_attr_destroy(&attr);
        return false;
    }

    pthread_attr_destroy(&attr);

    return true;
}


template
<
typename WritePolicy /*= FileWriter*/,
typename FilterPolicy /*= LevelFilter*/,
typename FormatPolicy /*= DefaultFormmater
*/>
void LogManager<WritePolicy, FilterPolicy, FormatPolicy>::write_log(const Record& record)
{
    if (!m_filter.filter(record))
    {
        return;
    }

    m_log_queue.push(record);
}


template
<
typename WritePolicy /*= FileWriter*/,
typename FilterPolicy /*= LevelFilter*/,
typename FormatPolicy /*= DefaultFormmater
 */>
 void* LogManager<WritePolicy, FilterPolicy, FormatPolicy>::log_thread(void* arg)
{
     if (NULL == arg)
     {
         return NULL;
     }

     LogManager* p_this = (LogManager*)arg;

     while (true)
     {
         Record log_record = m_log_queue.pop();
         std::string log_string = m_formatter.format(log_record);
         m_writer.write_log(log_string);
     }

     return NULL;
}




} // namespace logger

#endif // _LOGGER_LOG_MANAGER_H_
