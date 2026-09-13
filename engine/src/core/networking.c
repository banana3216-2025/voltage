#include "networking.h"
#include "core/logger.h"
#include "platform/platform.h"

void *sockets[128];

int next_socket_id = 0;
int find_next_socket_id() {
    int original_next_socket = next_socket_id;
    next_socket_id++;
    if (next_socket_id > (sizeof(sockets) / sizeof(void *))) {
        VERROR("Out of new networking sockets reached limit of 128");
    }

    return original_next_socket;
}

void network_host(int port, char *host_string, void *output) {
    platform_networking_host(port, host_string, output);
}

b8 network_initialize(platform_state *plat_state) {
    platform_networking_startup(plat_state);
    return TRUE;
}

void network_shutdown() { platform_networking_shutdown(); }

int network_socket(int port) {
    int socket_id = find_next_socket_id();
    b8 result = platform_networking_socket(port, &sockets[socket_id]);
    if (result != TRUE) {
        VERROR("failed to create new networking socket");
        return -1;
    }

    VINFO("opened socket on port: %i", port);
    return socket_id;
}

void network_socket_close(int socket_id) {
    platform_networking_close(&sockets[socket_id]);
}

b8 network_send_packet(int socket_id, void *buffer, int buffer_length,
                       void *target_host) {
    if (platform_networking_send_packet(&sockets[socket_id], buffer,
                                        buffer_length, target_host) < 0) {
        return FALSE;
    }

    VINFO("sent a packet on socket_id of %i", socket_id);

    return TRUE;
}

b8 network_receive_packet(int socket_id, void *buffer, int buffer_length,
                          void *origin_host) {
    if (platform_networking_recive_packet(&sockets[socket_id], buffer,
                                          buffer_length,
                                          (struct sockaddr *)origin_host) < 0) {
        return FALSE;
    }

    return TRUE;
}
