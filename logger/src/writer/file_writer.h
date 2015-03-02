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
    FileWriter(const std::string path, const std::string filename, uint64_t filesize);

    ~FileWriter();

    bool write_log(const std::string& log);

    inline void set_file_path(const std::string& path);

    inline void set_file_name(const std::string& filename);

    inline void set_file_size(uint64_t file_size);

private:
    bool write_line(const std::string& line);
    bool check_file();
    bool create_file(const std::string& fullpath_name);
    std::string get_time_string() const;
    int64_t get_file_size(const char* filename) const;

    // delete copy constructor
    FileWriter(const FileWriter&);

    // delete operator =
    FileWriter& operator= (const FileWriter&);

private:
    std::string m_path;
    std::string m_filename;
    std::string m_fullpath_filename_with_time;
    uint64_t m_file_size_max;
    std::fstream m_file_handler;
};

} // namespace logger

#endif // _LOGGER_FILE_WRITER_H_
