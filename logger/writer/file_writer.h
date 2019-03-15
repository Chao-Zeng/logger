#ifndef _LOGGER_FILE_WRITER_H_
#define _LOGGER_FILE_WRITER_H_

//linux platform
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstdint>

#include <string>
#include <fstream>

namespace logger
{

class FileWriter
{
public:
    FileWriter() :
        m_file_size_max(0)
        {}

    ~FileWriter()
    {
        if (m_file_handler.is_open())
        {
            m_file_handler.flush();
            m_file_handler.close();
            m_file_handler.clear();
        }
    }

    bool write_log(const std::string& log)
    {
        if (!check_file())
        {
            m_file_handler.flush();
            m_file_handler.close();
            m_file_handler.clear();

            m_fullpath_filename_with_time = m_path + m_filename + get_time_string();
            if (!create_file(m_fullpath_filename_with_time))
            {
                return false;
            }        
        }

        return write_line(log);
    }

    void set_file_path(const std::string& path)
    {
        m_path = path;
    }

    void set_file_name(const std::string& filename)
    {
        m_filename = filename;
    }

    void set_file_size(uint64_t file_size)
    {
        m_file_size_max = file_size;
    }

private:
    bool write_line(const std::string& line)
    {
        m_file_handler.write(line.c_str(), line.length());
        m_file_handler.write("\n", 1);

        if (m_file_handler.fail())
        {
            return false;
        }

        m_file_handler.flush();
        
        return true;
    }

    bool check_file()
    {
        if (!m_file_handler.is_open())
        {
            return false;
        }

        int64_t filesize = get_file_size(m_fullpath_filename_with_time.c_str());

        if (filesize < 0 || filesize >(int64_t)m_file_size_max)
        {
            return false;
        }

        return true;
    }

    bool create_file(const std::string& fullpath_name)
    {
        m_file_handler.open(fullpath_name.c_str(), std::fstream::out | std::fstream::app);

        if (m_file_handler.fail())
        {
            m_file_handler.close();
            m_file_handler.clear();
            return false;
        }

        return true;
    }

    std::string get_time_string() const
    {
        time_t rawtime;
        struct tm* timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        //YYYYMMDDHHMMSS
        strftime(buffer, 80, "%Y%m%d%H%M%S", timeinfo);

        return std::string(buffer);
    }

    int64_t get_file_size(const char* filename) const
    {
        struct stat file_state;
        if (stat(filename, &file_state) < 0)
        {
            return -1;
        }

        return file_state.st_size;
    }

    // delete copy constructor
    FileWriter(const FileWriter&) = delete;

    // delete copy assignment
    FileWriter& operator=(const FileWriter&) = delete;

private:
    std::string m_path;
    std::string m_filename;
    std::string m_fullpath_filename_with_time;
    uint64_t m_file_size_max;
    std::fstream m_file_handler;
};

} // namespace logger

#endif // _LOGGER_FILE_WRITER_H_
