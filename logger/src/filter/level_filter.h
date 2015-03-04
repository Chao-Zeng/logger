#ifndef _LOGGER_LEVEL_FILTER_H_
#define _LOGGER_LEVEL_FILTER_H_

class LevelFilter
{
public:
    LevelFilter();
    ~LevelFilter();

    bool operator() (SeverityLevel log_level, SeverityLevel filter_level)
    {
        if (log_level > filter_level)
        {
            return true;
        }

        return false;
    }
};

#endif // _LOGGER_LEVEL_FILTER_H_
