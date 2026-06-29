#include "applications.h"
#include "game_types.h"

#include "core/event.h"
#include "core/inputs.h"
#include "core/logger.h"
#include "core/vmemory.h"
#include "platform/platform.h"

typedef struct application_state {
    game *game_inst;
    b8 is_running;
    b8 is_suspended;
    platform_state platform;
    i16 width;
    i16 height;
    f64 last_time;
} application_state;

static b8 initialized = FALSE;
static application_state app_state;

// Event handlers
b8 application_on_event(u16 code, void *sender, void *listner_inst,
                        event_context context);
b8 application_on_key(u16 code, void *sender, void *listner_inst,
                      event_context context);

b8 application_create(game *game_inst) {
    if (initialized) {
        VERROR("application create called more than once");
        return FALSE;
    }

    app_state.game_inst = game_inst;

    // Initialize subsystems
    initialize_logger();
    input_initialize();

    // TODO: remove this
    VFATEL("A test message: %f", 3.14);
    VERROR("A test message: %f", 3.14);
    VWARN("A test message: %f", 3.14);
    VINFO("A test message: %f", 3.14);
    VDEBUG("A test message: %f", 3.14);
    VTRACE("A test message: %f", 3.14);

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    if (!event_initialize()) {
        VERROR("Event system failed to initialize Application Cannot Continue");
        return FALSE;
    }

    event_register(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
    event_register(EVENT_CODE_KEY_PRESSED, 0, application_on_key);

    if (!platform_startup(&app_state.platform, game_inst->app_config.name,
                          game_inst->app_config.start_pos_x,
                          game_inst->app_config.start_pos_y,
                          game_inst->app_config.start_width,
                          game_inst->app_config.start_height)) {
        return FALSE;
    }

    if (!app_state.game_inst->initialize(app_state.game_inst)) {
        VFATEL("Game failed to initialize.");
        return FALSE;
    }

    app_state.game_inst->on_resize(app_state.game_inst, app_state.width,
                                   app_state.height);

    initialized = TRUE;
    return TRUE;
}

b8 application_run() {
    VINFO(get_memory_useage_str());
    while (app_state.is_running) {
        if (!platform_pump_messages(&app_state.platform))
            app_state.is_running = FALSE;

        if (!app_state.is_suspended) {
            // TODO: add delta time input
            if (!app_state.game_inst->update(app_state.game_inst, (f32)0)) {
                VFATEL("Game update failed, shutting down.");
                app_state.is_running = FALSE;
                break;
            }

            // TODO: add delta time input
            if (!app_state.game_inst->render(app_state.game_inst, (f32)0)) {
                VFATEL("Game render failed, shutting down");
                app_state.is_running = FALSE;
                break;
            }

            // INFO: Input should be processed during frame but only take affect
            // on the next frame
            input_update(0);
        }
    }

    app_state.is_running = FALSE;
    platform_shutdown(&app_state.platform);
    event_shutdown();

    event_unregister(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
    event_unregister(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
    input_shutdown();

    return TRUE;
}

b8 application_on_event(u16 code, void *sender, void *listner_inst,
                        event_context context) {
    switch (code) {
    case EVENT_CODE_APPLICATION_QUIT: {
        VINFO("EVENT_CODE_APPLICATION_QUIT recieved, shutting down");
        app_state.is_running = FALSE;
        return TRUE;
    }
    }

    return FALSE;
}

b8 application_on_key(u16 code, void *sender, void *listner_inst,
                      event_context context) {
    if (code == EVENT_CODE_KEY_PRESSED) {
        u16 key_code = context.u16[0];
        if (key_code == KEY_ESCAPE) {
            // NOTE: Technically firing an event to itself, but there may be
            // other listeners.
            event_context data = {};
            event_fire(EVENT_CODE_APPLICATION_QUIT, 0, data);

            // Block anything else from processing this.
            return TRUE;
        } else if (key_code == KEY_A) {
            // Example on checking for a key
            VDEBUG("Explicit - A key pressed!");
        } else {
            VDEBUG("'%c' key pressed in window.", key_code);
        }
    } else if (code == EVENT_CODE_KEY_RELEASED) {
        u16 key_code = context.u16[0];
        if (key_code == KEY_B) {
            // Example on checking for a key
            VDEBUG("Explicit - B key released!");
        } else {
            VDEBUG("'%c' key released in window.", key_code);
        }
    }

    VDEBUG("test");

    return FALSE;
}
