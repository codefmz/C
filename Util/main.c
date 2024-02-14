#include "log.h"

void main(int argc, char** argv)
{
    LOG_ERROR("hello %d", 2024);
    LOG_ERROR("hello %d", 2024);
    LOG_ERROR("hello %d", 2024);
    LOG_ERROR("hello %d", 2024);
    LOG_INFO("info log %d, %s", 2024, "haha");
}