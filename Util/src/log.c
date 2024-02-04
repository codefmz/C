#include "log.h"
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOG_NAME "logger"
#define ERRLOG_FILENAME "err.log"
#define INFOLOG_FILENAME "info.log"

const char* g_levelStr[2] = { "INFO", "ERROR" };

#ifdef __cplusplus
extern "C" {
#endif
/* 获取年月日，时分秒 */
char* GetCurTimeStr(void)
{
    time_t mytime = time(NULL);
    static char s[50];
    struct tm curr = *localtime(mytime);

    if (curr.tm_year > 50) {
        sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d",
            curr.tm_year + 1900, curr.tm_mon + 1, curr.tm_mday,
            curr.tm_hour, curr.tm_min, curr.tm_sec);
    } else {
        sprintf(s, "%04d-%02d-%02d %02d:%02d:%02d",
            curr.tm_year + 2000, curr.tm_mon + 1, curr.tm_mday,
            curr.tm_hour, curr.tm_min, curr.tm_sec);
    }
    return s;
}

/* 获取年月日 */
char* GetCurDateStr(void)
{
    time_t mytime = time(NULL);
    static char s[50];

    struct tm curr = *localtime(mytime);
    if (curr.tm_year > 50) {
        sprintf(s, "%04d%02d%02d",
            curr.tm_year + 1900, curr.tm_mon + 1, curr.tm_mday);
    } else {
        sprintf(s, "%04d%02d%02d",
            curr.tm_year + 2000, curr.tm_mon + 1, curr.tm_mday);
    }
    return s;
}

void Log2File(LOG_LEVEL level, int32_t line, const char* fun, const char* file, char* fmt, ...)
{
    char logFileName[128] = { 0 };
    char log[256] = { 0 };

    va_list pArgs;
    va_start(pArgs, fmt);
    vsnprintf(log, 256, fmt, pArgs);
    snprintf(logFileName, 128, "./log/%s_%s.log", g_levelStr[level], GetCurShortDateStr());
    FILE* pFile = fopen(logFileName, "a+");
    if (pFile != NULL) {
        fprintf_s(pFile, "[%s][%s]%s:%d[%s]:%s\n", GetCurDateTimeStr(), g_levelStr[level], file, line, fun, log);
        fflush(pFile);
        fclose(pFile);
    }
}
#ifdef __cplusplus
}
#endif