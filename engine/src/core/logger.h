#pragma once

#include "defines.h"

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Disable Trace and debug for release builds
#if VRELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

typedef enum log_level {
    LOG_LEVEL_FATEL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5
} log_level;

b8 initialize_logger();
void shutdown_logger();

// FIXED: Added the explicit printf format tracker so modern Clang maps XMM float registers safely
VAPI void log_output(log_level level, const char* message, ...) __attribute__((format(printf, 2, 3)));

#define VFATEL(message, ...) log_output(LOG_LEVEL_FATEL, message, ##__VA_ARGS__);

#ifndef VERROR
#define VERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
#define VWARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
#define VWARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define VINFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
#define VINFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define VDEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
#define VDEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define VTRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
#define VTRACE(message, ...)
#endif