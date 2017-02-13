#ifndef __LOG_H__
#define __LOG_H__

/**
 * Log Level:
 * - VERBOSE
 * - INFO
 * - DEBUG
 * - WARN
 * - ERROR
 *
 * Priority increase from VERBOSE to ERROR<br>
 * Lower priority log level will include higher priority log<br>
 */

/* WARN/ERROR log default ON */
#ifndef LOG_LEVEL_WARN
#define LOG_LEVEL_WARN
#endif
#ifndef LOG_LEVEL_ERROR
#define LOG_LEVEL_ERROR
#endif

/* Turn off all level log if UART not enabled */
#if (!defined HAL_UART || HAL_UART == FALSE)
#undef  LOG_LEVEL_VERBOSE
#undef  LOG_LEVEL_INFO
#undef  LOG_LEVEL_DEBUG
#undef  LOG_LEVEL_WARN
#undef  LOG_LEVEL_ERROR
#ifndef LOG_LEVEL_NONE
#define LOG_LEVEL_NONE
#endif
#endif

#if   defined LOG_LEVEL_NONE    // NONE
#undef  LOG_LEVEL_VERBOSE
#undef  LOG_LEVEL_INFO
#undef  LOG_LEVEL_DEBUG
#undef  LOG_LEVEL_WARN
#undef  LOG_LEVEL_ERROR
#elif defined LOG_LEVEL_VERBOSE // VERBOSE
#define LOG_LEVEL_INFO
#define LOG_LEVEL_DEBUG
#elif defined LOG_LEVEL_INFO    // INFO
#undef  LOG_LEVEL_VERBOSE
#define LOG_LEVEL_DEBUG
#elif defined LOG_LEVEL_DEBUG   // DEBUG
#undef  LOG_LEVEL_VERBOSE
#undef  LOG_LEVEL_INFO
#elif defined LOG_LEVEL_WARN    // WARN
#undef  LOG_LEVEL_VERBOSE
#undef  LOG_LEVEL_INFO
#undef  LOG_LEVEL_DEBUG
#elif defined LOG_LEVEL_ERROR   // ERROR
#undef  LOG_LEVEL_VERBOSE
#undef  LOG_LEVEL_INFO
#undef  LOG_LEVEL_DEBUG
#undef  LOG_LEVEL_WARN
#else                           // DEFAULT
#undef  LOG_LEVEL_VERBOSE
#undef  LOG_LEVEL_INFO
#undef  LOG_LEVEL_DEBUG
#endif

#define LOG_LEVEL_SYMBOL_VERBOSE        "V"
#define LOG_LEVEL_SYMBOL_INFO           "I"
#define LOG_LEVEL_SYMBOL_DEBUG          "D"
#define LOG_LEVEL_SYMBOL_WARN           "W"
#define LOG_LEVEL_SYMBOL_ERROR          "E"

#ifdef LOG_LEVEL_NONE
#define LOG(fmt, arg...)
#else
#define LOG(fmt, arg...)                logPrintf(fmt, ##arg)
#endif

#ifdef LOG_LEVEL_VERBOSE
#define LOGV(tag, fmt, arg...)          logPrintf(LOG_LEVEL_SYMBOL_VERBOSE ## "\t" ## tag ## "\t" fmt, ## arg)
#else
#define LOGV(tag, fmt, arg...)
#endif

#ifdef LOG_LEVEL_INFO
#define LOGI(tag, fmt, arg...)          logPrintf(LOG_LEVEL_SYMBOL_INFO    ## "\t" ## tag ## "\t" fmt, ## arg)
#else
#define LOGI(tag, fmt, arg...)
#endif

#ifdef LOG_LEVEL_DEBUG
#define LOGD(tag, fmt, arg...)          logPrintf(LOG_LEVEL_SYMBOL_DEBUG   ## "\t" ## tag ## "\t" fmt, ## arg)
#else
#define LOGD(tag, fmt, arg...)
#endif

#ifdef LOG_LEVEL_WARN
#define LOGW(tag, fmt, arg...)          logPrintf(LOG_LEVEL_SYMBOL_WARN    ## "\t" ## tag ## "\t" fmt, ## arg)
#else
#define LOGW(tag, fmt, arg...)
#endif

#ifdef LOG_LEVEL_ERROR
#define LOGE(tag, fmt, arg...)          logPrintf(LOG_LEVEL_SYMBOL_ERROR   ## "\t" ## tag ## "\t" fmt, ## arg)
#else
#define LOGE(tag, fmt, arg...)
#endif

/*
 * Another API for disable log in code level.
 * It will not output log in trace.
 */
#define __LOG(fmt, arg...)
#define __LOGV(tag, fmt, arg...)
#define __LOGI(tag, fmt, arg...)
#define __LOGD(tag, fmt, arg...)
#define __LOGW(tag, fmt, arg...)
#define __LOGE(tag, fmt, arg...)

/**
 * Another API for quick debug
 * It will output line and function name
 */
#define D()                             logPrintf("* L%d, %s\r\n", __LINE__, __FUNCTION__)
#define DD(fmt, arg...)                 logPrintf("* L%d, %s: " fmt, __LINE__, __FUNCTION__, ##arg)
#define DDD(fmt, arg...)                logPrintf("* L%d: " fmt, __LINE__, ##arg)

#define DEBUG_UART_PORT                 UART_PORT

/* Public API for log */
int logPrintf(const char *format, ...);

#endif /* __LOG_H__ */

/* vim: set ts=2 sw=2 tw=0 list : */
