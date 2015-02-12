#ifndef _LOGGER_WRITER_H_
#define _LOGGER_WRITER_H_

namespace logger
{

template <typename impl_type>
class writer
{
public:
    bool write_log()
    {
        return impl_->write_log();
    }

private:
    impl_type* impl_;
};

}

#endif // _LOGGER_WRITER_H_
