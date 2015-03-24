#include <logger/logger.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
    init_logger();

    write_log(INFO, "%s:%d this is a test message", __FILE__, __LINE__);
    write_log(TRACE, "this message shouldn't print");

    set_log_level(TRACE);
    write_log(TRACE, "this is a trace message");

    getchar();
    return 0;
}
