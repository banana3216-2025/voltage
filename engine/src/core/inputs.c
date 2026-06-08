#include "core/inputs.h"
#include "core/event.h"
#include "core/logger.h"
#include "core/vmemory.h"
#include "defines.h"

typedef struct keyboard_state {
    b8 keys[256];
} keyboard_state;

typedef struct mouse_state {
    i16 x;
    i16 y;
    b8 buttons[BUTTON_MAX_BUTTONS];
} mouse_state;

typedef struct input_state {
    keyboard_state keyboard_current;
    keyboard_state keyboard_pervious;

    mouse_state mouse_current;
    mouse_state mouse_pervious;
} input_state;

static b8 initialized = FALSE;
static input_state state = {};

void input_initialize() {
    vzero_memory(&state, sizeof(input_state));
    initialized = TRUE;
    VINFO("Input subsystem initialized");
};

void input_shutdown() {
    // TODO: Add shutdwon routines when needed.
    initialized = FALSE;
};

void input_update(f64 delta_time) {
    if (!initialized)
        return;

    vcopy_memory(&state.keyboard_pervious, &state.keyboard_current,
                 sizeof(keyboard_state));
    vcopy_memory(&state.mouse_pervious, &state.mouse_current,
                 sizeof(mouse_state));
}

// INFO: this function and other process functions are going to be used as a
// callback for OS specific libaries
void input_process_key(enum keys key, b8 pressed) {
    // Only handle inputs if state changed
    if (state.keyboard_current.keys[key] != pressed) {
        state.keyboard_current.keys[key] = pressed;

        event_context context;
        context.u16[0] = key;
        event_fire(pressed ? EVENT_CODE_KEY_PRESSED : EVENT_CODE_KEY_RELEASED,
                   0, context);
    }
}

void input_process_mouse(enum buttons button, b8 pressed) {
    // Only handle inputs if state changed
    if (state.mouse_current.buttons[button] != pressed) {
        state.mouse_current.buttons[button] = pressed;

        event_context context;
        context.u16[0] = button;
        event_fire(pressed ? EVENT_CODE_KEY_PRESSED : EVENT_CODE_KEY_RELEASED,
                   0, context);
    }
}

void input_process_mouse_move(i16 x, i16 y) {
    if (state.mouse_current.x != x || state.mouse_current.y != y) {
        // NOTE: enable this if debugging
        // VDEBUG("mouse pos, x:%i y:%i", x, y);

        state.mouse_current.x = x;
        state.mouse_current.y = y;

        event_context context;
        context.u16[0] = x;
        context.u16[1] = y;
        event_fire(EVENT_CODE_MOUSE_MOVED, 0, context);
    }
}

void input_process_mouse_wheel(i8 z_delta) {
    // NOTE: no internal state update

    event_context context;
    context.u8[0] = z_delta;
    event_fire(EVENT_CODE_MOUSE_WHEEL, 0, context);
}

b8 input_is_key_down(enum keys key) {
    if (!initialized)
        return FALSE;
    return state.keyboard_current.keys[key] == TRUE;
}

b8 input_is_key_up(enum keys key) {
    if (!initialized)
        return TRUE;
    return state.keyboard_current.keys[key] == FALSE;
}

b8 input_was_key_down(enum keys key) {
    if (!initialized)
        return FALSE;
    return state.keyboard_pervious.keys[key] == TRUE;
}

b8 input_was_key_up(enum keys key) {
    if (!initialized)
        return TRUE;
    return state.keyboard_pervious.keys[key] == FALSE;
}

b8 input_is_button_down(enum buttons button) {
    if (!initialized)
        return FALSE;
    return state.mouse_current.buttons[button] == TRUE;
}

b8 input_is_button_up(enum buttons button) {
    if (!initialized)
        return TRUE;
    return state.mouse_current.buttons[button] == FALSE;
}

b8 input_was_button_down(enum buttons button) {
    if (!initialized)
        return FALSE;
    return state.mouse_pervious.buttons[button] == TRUE;
}

b8 input_was_button_up(enum buttons button) {
    if (!initialized)
        return TRUE;
    return state.mouse_pervious.buttons[button] == FALSE;
}

void input_get_mouse_position(i32 *x, i32 *y) {
    if (!initialized) {
        *x = 0;
        *y = 0;
        return;
    }
    *x = state.mouse_current.x;
    *y = state.mouse_current.y;
}

void input_get_pervious_mouse_position(i32 *x, i32 *y) {
    if (!initialized) {
        *x = 0;
        *y = 0;
        return;
    }
    *x = state.mouse_pervious.x;
    *y = state.mouse_pervious.y;
}
