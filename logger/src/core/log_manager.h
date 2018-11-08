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

template<typename Writer = FileWriter,
    typename Filter = LevelFilter,
    typename Formmater = DefaultFormmater>
class LogManager
{
public:
    static LogManager* instance()
    {
        if (NULL == m_instance)
        {
            m_instance = new LogManager;
        }

        return m_instance;
    }

    bool init(const std::string& path, const std::string& filename, uint64_t filesize)
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

    void set_log_level(SeverityLevel log_level)
    {
        m_log_level = log_level;
    }

    void write_log(const Record& record)
    {
        if (!m_filter.filter(record.level, m_log_level))
		{
			return;
		}

		m_log_queue.push(record);
    }

private:
    static void* log_thread(void* arg)
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
    Writer m_writer;
    Filter m_filter;
    Formmater m_formatter;
};


template<typename Writer,
    typename Filter,
    typename Formmater>
LogManager<Writer, Filter, Formmater>* LogManager<Writer, Filter, Formmater>::m_instance = NULL;

} // namespace logger

#endif // _LOGGER_LOG_MANAGER_H_
