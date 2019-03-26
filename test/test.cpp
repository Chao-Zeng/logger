#include <logger.h>

#include <thread>
#include <stdio.h>

void func()
{
    LOG_INFO("new thread");
}

int main(int argc, char* argv[])
{
    logger::init_logger("./log/", "log_", 100);

    LOG_INFO("%s:%d this is a test message", __FILE__, __LINE__);
    LOG_TRACE("this message shouldn't print");

    logger::set_log_level(TRACE);
    LOG_TRACE("this is a trace message");

    std::thread t(func);
    t.join();
    
    getchar();
    return 0;
}
