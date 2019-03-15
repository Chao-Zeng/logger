#ifndef _LOGGER_FILTER_H_
#define _LOGGER_FILTER_H_

#include "core/record.h"

namespace logger{

class LevelFilter
{
public:
    bool filter(SeverityLevel log_level, SeverityLevel filter_level)
    {
        if (log_level >= filter_level)
        {
            return true;
        }

        return false;
    }
};

} // namespace logger

#endif // _LOGGER_FILTER_H_
