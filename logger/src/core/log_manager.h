#ifndef _LOGGER_LOG_MANAGER_H_
#define _LOGGER_LOG_MANAGER_H_

namespace logger
{

    class LogManager
    {
    public:
        bool set_writer();
        bool reset_writer();
        bool set_formatter();
        bool reset_formatter();
        bool set_filter();
        bool reset_filter();
    private:
    };

} // namespace logger

#endif // _LOGGER_LOG_MANAGER_H_
