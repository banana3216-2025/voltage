#pragma once

#include "defines.h"
#include "platform/platform.h"
#include <stdint.h>

VAPI void network_host(int port, char *host_string, void *);

b8 network_initialize(platform_state *plat_state);
void network_shutdown();

VAPI int network_socket(int port);
VAPI void network_socket_close(int socket_id);

// This type must be used for every packet send and also in the packet must be
// casted to a uint32_t
typedef enum __attribute__((packed)) packet_type : uint32_t {
    NETWORK_PACKET_TYPE_NO_TYPE,
    NETOWRK_PACKET_TYPE_MAX_TYPE
} packet_type;

VAPI b8 network_send_packet(int socket_id, void *buffer, int buffer_length,
                            void *target_host);
VAPI b8 network_receive_packet(int socket_id, void *buffer, int buffer_length,
                               void *origin_host);
