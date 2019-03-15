#ifndef _LOGGER_LOG_MANAGER_H_
#define _LOGGER_LOG_MANAGER_H_

#include <thread>

//project header
#include "condition_queue.h"
#include "record.h"
#include "writer/file_writer.h"
#include "formatter/formatter.h"
#include "filter/filter.h"

namespace logger
{

template<typename Writer = FileWriter,
    typename Filter = LevelFilter,
    typename Formmater = DefaultFormmater>
class LogManager
{
public:
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;
    LogManager(LogManager&&) = delete;
    LogManager& operator=(LogManager&&) = delete;

    static LogManager& instance()
    {
        static LogManager m_instance;
        return m_instance;
    }

    bool init(const std::string& path, const std::string& filename, uint64_t filesize)
    {
        m_writer.set_file_path(path);
		m_writer.set_file_name(filename);
		m_writer.set_file_size(filesize);

		std::thread t(&LogManager::log_thread, this);
        t.detach();

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
    void log_thread()
    {
		while (true)
		{
			Record log_record = m_log_queue.pop();
			std::string log_string = m_formatter.format(log_record);
			m_writer.write_log(log_string);
		}
    }

private:
    LogManager() : m_tid(0), m_log_level(INFO)
    {
    }

    ~LogManager() = default;

private:
    std::thread::id m_tid;
    SeverityLevel m_log_level;

    ConditionQueue<Record> m_log_queue;    
    Writer m_writer;
    Filter m_filter;
    Formmater m_formatter;
};

} // namespace logger

#endif // _LOGGER_LOG_MANAGER_H_
