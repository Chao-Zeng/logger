#ifndef _LOGGER_FILE_WRITER_H_
#define _LOGGER_FILE_WRITER_H_

#include <cstdint>

#include <string>
#include <fstream>

namespace logger
{

class FileWriter
{
public:
    FileWriter();

    ~FileWriter();

    bool write_log(const std::string& log);

    inline void set_file_path(const std::string& path);

    inline void set_file_name(const std::string& filename);

private:
    bool write_line(const std::string& line);
    bool check_file();
    bool create_file(const std::string& fullpath_name);
    bool get_fullpath_name();
    std::string get_time_string() const;

    // delete copy constructor
    FileWriter(const FileWriter&);

    // delete operator =
    FileWriter& operator= (const FileWriter&);

private:
    std::string m_path;
    std::string m_filename;
    uint32_t m_file_size;
    std::fstream m_file_handler;
};

} // namespace logger

#endif // _LOGGER_FILE_WRITER_H_
