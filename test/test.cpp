#include <logger.h>

#include <thread>
#include <stdio.h>

void func()
{
    logger::write_log(INFO, "new thread");
}

int main(int argc, char* argv[])
{
    logger::init_logger("./log/", "log_", 100);

    logger::write_log(INFO, "%s:%d this is a test message", __FILE__, __LINE__);
    logger::write_log(TRACE, "this message shouldn't print");

    logger::set_log_level(TRACE);
    logger::write_log(TRACE, "this is a trace message");

    std::thread t(func);
    t.join()
    
    getchar();
    return 0;
}
