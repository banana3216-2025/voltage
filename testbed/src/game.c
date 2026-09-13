#include "game.h"
#include "core/vmemory.h"

#include <core/logger.h>
#include <core/networking.h>

int socket_id = 0;

void *host;

int packet_size =
    sizeof("From Windows, Why does man create? Is it man's purpose on earth to "
           "express himself, to bring form to thought, and to "
           "discover meaning in experience? Or is it just");

b8 game_initialize(game *game_inst) {
    VDEBUG("Game_initialized called");

    socket_id = network_socket(6767);
    VINFO("socket_id of %i", socket_id);

    host = vallocate(64, MEMORY_TAG_NETWORK);
    network_host(6767, "127.0.0.1", host);

    return TRUE;
}

b8 game_update(game *game_inst, f32 delta_time) {
    network_send_packet(
        socket_id,
        "From Windows, Why does man create? Is it man's purpose on earth to "
        "express himself, to bring form to thought, and to "
        "discover meaning in experience? Or is it just",
        packet_size, host);
    return TRUE;
}
b8 game_render(game *game_inst, f32 delta_time) { return TRUE; }

void game_on_resize(game *game_inst, u32 width, u32 height) {}
