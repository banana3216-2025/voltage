#pragma once

#include "defines.h"

typedef struct platform_state {
    void *internal_state;
} platform_state;

b8 platform_startup(platform_state *plat_state, const char *appication_name,
                    i32 x, i32 y, i32 width, i32 height);

void platform_shutdown(platform_state *plat_stat);

b8 platform_pump_messages(platform_state *plat_state);

void *platform_allocate(u64 size, b8 aligned);
void platform_free(void *block, b8 aligned);
void *platform_zero_memory(void *block, u64 size);
void *platform_copy_memory(void *dest, const void *source, u64 size);
void *platform_set_memory(void *dest, i32 value, u64 size);

void platform_console_write(const char *message, u8 color);
void platform_console_write_error(const char *message, u8 color);

f64 platform_get_absolute_time();

void platform_sleep(u64 ms);

b8 platform_networking_startup(platform_state *plat_state);
void platform_networking_shutdown();
b8 platform_networking_socket(int port, void *socket_pointer);
void platform_networking_close(void *socket_pointer);

void platform_networking_host(int port, char *host_string, void *);

// Return values
//  x > 0 : OK
//  x < 0 : failed to reach host
int platform_networking_send_packet(void *socket_pointer, void *buffer,
                                    int buffer_length, void *target_host);
int platform_networking_recive_packet(void *socket_pointer, void *buffer,
                                      int buffer_length, void *origin_host);
