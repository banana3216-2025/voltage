#include "logger.h"
#include "asserts.h"
#include "platform/platform.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line) {
    log_output(LOG_LEVEL_FATEL, "Assertion Failure: %s, message: %s, in file: %s, line: %d", expression, message, file, line);
}

b8 initialize_logger() {
    // TODO: create log file
    return TRUE;
}

void shutdown_logger() {
    // TODO: cleanup logging queured entries
}

void log_output(log_level level, const char* message, ...) {
    const char* level_strings[6] = {"[FATEL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    b8 is_error = level < LOG_LEVEL_WARN;

    const i32 msg_length = 32000;
    
    // Move messages off the stack to avoid memory overalap causing va args to not work
    static char out_message[32000];
    static char out_message2[32000];

    memset(out_message, 0, msg_length);
    memset(out_message2, 0, msg_length);

    va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, msg_length - 1, message, arg_ptr);
    va_end(arg_ptr);

    snprintf(out_message2, msg_length - 1, "%s%s\n", level_strings[level], out_message);

    if (is_error) {
        platform_console_write_error(out_message2, level);
    } else {
        platform_console_write(out_message2, level);
    }
}