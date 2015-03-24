#include <logger/src/core/log_manager.h>

namespace logger{

LogManager* LogManager::m_instance = NULL;

LogManager* LogManager::instance()
{
    if (NULL == m_instance)
    {
        m_instance = new LogManager;
    }

    return m_instance;
}

bool LogManager::init(const std::string& path, const std::string& filename, uint64_t filesize)
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

void LogManager::write_log(const Record& record)
{
    if (!m_filter.filter(record.level, m_log_level))
    {
        return;
    }

    m_log_queue.push(record);
}

void* LogManager::log_thread(void* arg)
{
    if (NULL == arg)
    {
        return NULL;
    }

    LogManager* p_this = (LogManager*)arg;

    while (true)
    {
        Record log_record = p_this->m_log_queue.pop();
        std::string log_string = p_this->m_formatter.format(log_record);
        p_this->m_writer.write_log(log_string);
    }

    return NULL;
}

} //namespace logger
