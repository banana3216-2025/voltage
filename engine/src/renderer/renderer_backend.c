#include "renderer_backend.h"

b8 renderer_backend_create(renderer_backend_type type,
                           struct platform_state *plat_state,
                           renderer_backend *out_renderer_backend) {
    out_renderer_backend->plat_state = plat_state;

    switch (type) {
    case RENDERER_BACKEND_TYPE_VULKAN:
        // TODO: Fill out(assign function pointers)
        return TRUE;
    default:
        break;
    }

    return FALSE;
}

void renderer_backend_destroy(renderer_backend *renderer_backend) {
    renderer_backend->initialize = 0;
    renderer_backend->shutdown = 0;
    renderer_backend->begin_frame = 0;
    renderer_backend->end_frame = 0;
    renderer_backend->resize = 0;
}
