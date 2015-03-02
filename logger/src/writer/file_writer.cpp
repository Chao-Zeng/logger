#include <logger/src/writer/file_writer.h>

//linux platform
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <ctime>

namespace logger
{
    
FileWriter::FileWriter() : m_path(std::string()), m_filename(std::string()),
    m_fullpath_filename_with_time(std::string()), m_file_size_max(0), m_file_handler(std::fstream())
{
}

FileWriter::FileWriter(const std::string path, const std::string filename, uint64_t filesize)
    : m_path(path), m_filename(filename), m_fullpath_filename_with_time(std::string()),
      m_file_size_max(filesize), m_file_handler(std::fstream())
{
}

FileWriter::~FileWriter()
{
    if (m_file_handler.is_open())
    {
        m_file_handler.flush();
        m_file_handler.close();
        m_file_handler.clear();
    }
}

bool FileWriter::write_log(const std::string& log)
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

void FileWriter::set_file_path(const std::string& path)
{
    m_path = path;
}

void FileWriter::set_file_name(const std::string& filename)
{
    m_filename = filename;
}

void FileWriter::set_file_size(uint64_t file_size)
{
    m_file_size_max = file_size;
}


bool FileWriter::write_line(const std::string& line)
{
    std::string line_data(line);
    line_data.append("\n");

    m_file_handler.write(line_data.c_str(), line_data.length());

    if (m_file_handler.fail())
    {
        return false;
    }
    
    return true;
}

bool FileWriter::create_file(const std::string& fullpath_name)
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

std::string FileWriter::get_time_string() const
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

bool FileWriter::check_file()
{
    if (!m_file_handler.is_open())
    {
        return false;
    }

    int64_t filesize = get_file_size(m_fullpath_filename_with_time.c_str());

    if (filesize < 0 || filesize > m_file_size_max)
    {
        return false;
    }

    return true;
}

int64_t FileWriter::get_file_size(const char* filename) const
{
    struct stat file_state;
    if (stat(filename, &file_state) < 0)
    {
        return -1;
    }

    return file_state.st_size;
}

} // namespace logger
