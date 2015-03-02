#ifndef _LOGGER_WRITER_H_
#define _LOGGER_WRITER_H_

#include <string>

namespace logger
{

template <typename impl_type>
class writer
{
public:
    writer(impl_type* impl)
    {
        impl_ = impl;
    }

    bool write_log(const std::string& log)
    {
        return impl_->write_log(log);
    }

private:
    impl_type* impl_;
};

}

#endif // _LOGGER_WRITER_H_
